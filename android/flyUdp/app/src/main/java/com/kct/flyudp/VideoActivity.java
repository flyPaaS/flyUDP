package com.kct.flyudp;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Color;
import android.media.AudioManager;
import android.os.Bundle;
import android.os.PowerManager;
import android.os.SystemClock;
import android.text.method.ScrollingMovementMethod;
import android.util.DisplayMetrics;
import android.view.SurfaceView;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.gl.softphone.UGoAPIParam;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.webrtc.videoengine.ViERenderer;
import org.webrtc.videoengine.VideoCaptureAndroid;

import java.util.ArrayList;

/**
 * Created by zhouwq on 2017/6/12/012.
 * 视频通话页面
 */

public class VideoActivity extends Activity implements View.OnClickListener {
    // 启动开关
    public boolean bOpen = false;
    // 视频窗口
    public TextView mTextTips = null;
    public RelativeLayout mLocalWnd = null;
    public RelativeLayout mRemoteWnd = null;
    public SurfaceView localSurfaceView = null;
    public SurfaceView remoteSurfaceView = null;
    // 按键
    private Button spkBtn = null;
    private Button camBtn = null;
    private boolean isMicOn = false;
	private boolean isCamOn = true;

    // 屏幕锁
    private PowerManager.WakeLock mWakeLock = null;

    // 用于打开网络信息的连击动作时间列表
    private boolean bShowNetMsg = true;
    ArrayList<Long> clickList = new ArrayList<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // 全屏显示
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.activity_video);
        // 控件
        mLocalWnd = (RelativeLayout)findViewById(R.id.locallayout);
        mRemoteWnd = (RelativeLayout)findViewById(R.id.remotelayout);
        mTextTips = (TextView) findViewById(R.id.videotips);
        mTextTips.setMovementMethod(ScrollingMovementMethod.getInstance());
        spkBtn = (Button) findViewById(R.id.button_mic);
		camBtn = (Button) findViewById(R.id.button_sw);
		spkBtn.setOnClickListener(this);
		camBtn.setOnClickListener(this);
		
        // 标题
        RelativeLayout rl_back = (RelativeLayout) findViewById(R.id.rl_back);
        rl_back.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                finish();
            }
        });

        //int nMode = getIntent().getIntExtra("mode", 0);
        String strName = getIntent().getStringExtra("name");
        String stream = getIntent().getStringExtra("stream");
        TextView title = (TextView)findViewById(R.id.rl_text);
        String str = strName + "(" + stream + ")";
        title.setText(str);
        // 关闭扬声器
        SetSpeaker(false);
        // 注册广播
        IntentFilter mIntentFilter = new IntentFilter();
        mIntentFilter.addAction(UIData.ACTION_NETWORK_STATE);
        registerReceiver(mBroadcastReceiver, mIntentFilter);
        // 处理Tip显示隐藏
        mLocalWnd.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                if (bShowNetMsg) {
                    // 当前为打开状态则单击关闭
                    bShowNetMsg = false;
                    mTextTips.setText("");
                    mTextTips.setVisibility(View.GONE);
                    return;
                }
                clickList.add(SystemClock.uptimeMillis());
                if (clickList.size() == 3) {
                    //3次连击打开
                    if (clickList.get(clickList.size() - 1) - clickList.get(0) < 2000) {
                        clickList.clear();
                        bShowNetMsg = true;
                        mTextTips.setText("");
                        mTextTips.setVisibility(View.VISIBLE);
                    } else {
                        Long tmp = clickList.get(clickList.size() - 1);
                        clickList.clear();
                        clickList.add(tmp);
                    }
                }
            }
        });
    }

    @SuppressWarnings("deprecation")
	@Override
    protected void onResume() {
        super.onResume();
        PowerManager pManager = ((PowerManager) getSystemService(POWER_SERVICE));
        mWakeLock = pManager.newWakeLock(PowerManager.ACQUIRE_CAUSES_WAKEUP | PowerManager.SCREEN_DIM_WAKE_LOCK, "VideoLock");
        mWakeLock.acquire();
        //
        StartVideo();
    }

    @Override
    protected void onPause() {
        super.onPause();
        if (mWakeLock != null) {
            mWakeLock.release();
            mWakeLock = null;
        }
        StopVideo();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        unregisterReceiver(mBroadcastReceiver);
        StopVideo();
        //
        if (MainApplication.getInstance().mMainActivity != null) {
        	MainApplication.getInstance().mMainActivity.mHandler.sendEmptyMessage(1004);
        }
    }
    
    @Override
	public void onClick(View v) {
    	switch (v.getId()) {
		case R.id.button_mic:
			if (bOpen) {
				isMicOn = !isMicOn;
				SetSpeaker(isMicOn);
				if (isMicOn) {
					spkBtn.setBackgroundResource(R.mipmap.ic_spk_on);
				} else {
					spkBtn.setBackgroundResource(R.mipmap.ic_spk_off);
				}
			}
			break;
		case R.id.button_sw:
			if (bOpen) {
				isCamOn = !isCamOn;
				if (isCamOn) {
					SetCamera(1);
				} else {
					SetCamera(0);
				}
			}
			break;
		default:
			break;
		}
	}

    // 处理广播
    private BroadcastReceiver mBroadcastReceiver = new BroadcastReceiver() {

        @Override
        public void onReceive(Context context, Intent intent) {
            String strAction = intent.getAction();
            if (strAction.equals(UIData.ACTION_NETWORK_STATE)) {
                String strKey = intent.getStringExtra(UIData.ACTION_KEY);
                if (strKey != null && !strKey.equals("")) {
                    // 显示网络参数
                    try {
                        JSONObject obj = new JSONObject(strKey);
                        String strNet = "unknown";
                        switch (obj.getInt("ns")) {
                            case UGoAPIParam.eUGo_NETWORK_NICE:
                                strNet = "nice";
                                break;
                            case UGoAPIParam.eUGo_NETWORK_WELL:
                                strNet = "well";
                                break;
                            case UGoAPIParam.eUGo_NETWORK_GENERAL:
                                strNet = "general";
                                break;
                            case UGoAPIParam.eUGo_NETWORK_POOR:
                                strNet = "poor";
                                break;
                            case UGoAPIParam.eUGo_NETWORK_BAD:
                                strNet = "bad";
                                break;
                            default:
                                break;
                        }

                        String strMsg = "vie state:" + strNet
                                + "\r\nice:" + obj.getInt("ice") + ",rtt:" + obj.getInt("rtt")
                                + "\r\nlost:" + obj.getInt("ul") + "(s) " + obj.getInt("dl") + "(r)"
                                + "\r\nrate:" + obj.getInt("sb") + "(s) " + obj.getInt("rb") + "(r)"
                                + "\r\nres: " + obj.getInt("sw") + "x" + obj.getInt("sh") + "(s) " + obj.getInt("dw") + "x" + obj.getInt("dh") + "(r)"
                                + "\r\nframe:" + obj.getInt("sf") + "(s) " + obj.getInt("df") + "(r)"
                                + "\r\npt:" + obj.getInt("ep") + "(s) " + obj.getInt("dp") + "(r)"
                                + "\r\ncodec: " + obj.getString("eCodec") + " (s)" + obj.getString("dCodec") + "(r)";

                        int rtPOT_nCount = obj.getInt("nCnt");
                        strMsg = strMsg + "\r\nRelayCnt: " + obj.getInt("nCnt");
                        if (rtPOT_nCount > 0) {
                            JSONArray jrtPOTarray = obj.getJSONArray("rtPOT");
                            for (int i = 0; i < jrtPOTarray.length(); i++) {
                                JSONObject jsonObj = jrtPOTarray.getJSONObject(i);
                                int sIP = jsonObj.getInt("sIP");
                                int rIP = jsonObj.getInt("rIP");
                                int sFlow_a = jsonObj.getInt("sFlow_a");
                                int rFlow_a = jsonObj.getInt("rFlow_a");
                                int sFlow_v = jsonObj.getInt("sFlow_v");
                                int rFlow_v = jsonObj.getInt("rFlow_v");

                                strMsg = strMsg + "\r\nRelay_" + i + ": " + sIP + " (s) " + rIP + "(r)" +
                                        "\nFlow_a_" + i + ": " + sFlow_a + " KB (s) " + rFlow_a + " KB (r)" +
                                        "\nFlow_v_" + i + ": " + sFlow_v + " KB (s) " + rFlow_v + " KB (r)";
                            }
                        }
                        // 设置TIPS
                        mTextTips.setTextColor(Color.rgb(255, 0, 0));
                        mTextTips.setText(strMsg);
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                }
            }
        }
    };

    public void StartVideo() {
        StopVideo();
        // 设置音频参数
        UGoAPIParam.getInstance().stAudioInfo.playload = 111;
        UGoAPIParam.getInstance().stAudioInfo.remote_ip = MainApplication.getInstance().strIp;
        UGoAPIParam.getInstance().stAudioInfo.local_port = Integer.valueOf(MainApplication.getInstance().straPort);
        UGoAPIParam.getInstance().stAudioInfo.remote_port = Integer.valueOf(MainApplication.getInstance().straPort);
        UGoAPIParam.getInstance().stAudioInfo.ucExTransportEnable = false;
        MainApplication.getInstance().mViGoManager.pub_ViGoCreateAudioStream();
        MainApplication.getInstance().mViGoManager.pub_ViGoSetAudioStream(UGoAPIParam.getInstance().stAudioInfo);
        MainApplication.getInstance().mViGoManager.pub_ViGoEnableAudioPlayout(true);
        MainApplication.getInstance().mViGoManager.pub_ViGoEnableAudioReceive(true);
        MainApplication.getInstance().mViGoManager.pub_ViGoEnableAudioSend(true);
        MainApplication.getInstance().mViGoManager.pub_ViGoSetState(4);
        // 设置视频参数
        UGoAPIParam.getInstance().stVideoInfo.playload = 121;
        UGoAPIParam.getInstance().stVideoInfo.remote_ip = MainApplication.getInstance().strIp;
        UGoAPIParam.getInstance().stVideoInfo.local_port = Integer.valueOf(MainApplication.getInstance().strvPort);
        UGoAPIParam.getInstance().stVideoInfo.remote_port = Integer.valueOf(MainApplication.getInstance().strvPort);
        UGoAPIParam.getInstance().stVideoInfo.ucExTransportEnable = false;
        MainApplication.getInstance().mViGoManager.pub_ViGoCreateVideoStream();
        MainApplication.getInstance().mViGoManager.pub_ViGoSetVideoStream(UGoAPIParam.getInstance().stVideoInfo);

        // 创建视频渲染窗口
        remoteSurfaceView = ViERenderer.CreateRenderer(this, true);
        localSurfaceView = ViERenderer.CreateRenderer(this, true);
        VideoCaptureAndroid.setLocalPreview(null);

        mLocalWnd.removeAllViews();
        mLocalWnd.addView(localSurfaceView);
        localSurfaceView.setZOrderOnTop(true);

        mRemoteWnd.removeAllViews();
        mRemoteWnd.addView(remoteSurfaceView);
        // 设置视频渲染参数
        MainApplication.getInstance().mViGoManager.pub_ViGoGetConfig(UGoAPIParam.ME_VIDEO_RENDER_CFG_MODULE_ID, UGoAPIParam.getInstance().stVideoRenderCfg, 0);
        UGoAPIParam.getInstance().stVideoRenderCfg.pWindowLocal = localSurfaceView;
        UGoAPIParam.getInstance().stVideoRenderCfg.pWindowRemote = remoteSurfaceView;
        UGoAPIParam.getInstance().stVideoRenderCfg.remoteWidth = getScreenWidth();
        UGoAPIParam.getInstance().stVideoRenderCfg.remoteHeight = getScreenHeight();
        MainApplication.getInstance().mViGoManager.pub_ViGoSetConfig(UGoAPIParam.ME_VIDEO_RENDER_CFG_MODULE_ID, UGoAPIParam.getInstance().stVideoRenderCfg, 0);
        // 启动视频
        MainApplication.getInstance().mViGoManager.pub_ViGoStartVideo(31);
        // 设置标记
        bOpen = true;
    }

    public void StopVideo() {
        if (bOpen) {
            mLocalWnd.removeAllViews();
            mRemoteWnd.removeAllViews();
            MainApplication.getInstance().mViGoManager.pub_ViGoStopVideo(31);
            MainApplication.getInstance().mViGoManager.pub_ViGoDeleteAudioStream();
            MainApplication.getInstance().mViGoManager.pub_ViGoDeleteVideoStream();
            bOpen = false;
        }
    }
    
    // 获得屏幕密度
    public int getScreenWidth() {
		DisplayMetrics metric = new DisplayMetrics();
		getWindowManager().getDefaultDisplay().getMetrics(metric);
        return metric.widthPixels;
	}

	// 获得屏幕高度
	public int getScreenHeight() {
		DisplayMetrics metric = new DisplayMetrics();
		getWindowManager().getDefaultDisplay().getMetrics(metric);
        return metric.heightPixels;
	}
	
	// 设置摄像头
	public void SetCamera(int nIndex) {
        MainApplication.getInstance().mViGoManager.pub_ViGoGetCameraParam(UGoAPIParam.getInstance().stVideoDevicePara);
        UGoAPIParam.getInstance().stVideoDevicePara.usCameraIdx = nIndex;
        UGoAPIParam.getInstance().stVideoDevicePara.iRotateAngle = -1;
        UGoAPIParam.getInstance().stVideoDevicePara.ucMaxFps = 30;
        UGoAPIParam.getInstance().stVideoDevicePara.usWidth = 480;
        UGoAPIParam.getInstance().stVideoDevicePara.usHeight = 640;
        MainApplication.getInstance().mViGoManager.pub_ViGoSetCameraParam(UGoAPIParam.getInstance().stVideoDevicePara);
	}
	
	// 设置扬声器
	public void SetSpeaker(boolean bOpen) {
		try {
			AudioManager audioManager = (AudioManager) getSystemService(Context.AUDIO_SERVICE);
			if (audioManager != null) {
				audioManager.setSpeakerphoneOn(bOpen);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
