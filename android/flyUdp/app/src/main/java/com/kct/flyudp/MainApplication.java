package com.kct.flyudp;

import android.app.Application;
import android.content.Intent;
import android.util.Log;

import com.gl.softphone.UGoAPIParam;
import com.gl.softphone.ViGoManager;

import static com.gl.softphone.UGoAPIParam.EventTypeEnum.eME_VIDEO_NETWORK_STATE_EV;

/**
 * Created by zhouwq on 2017/6/12/012.
 * Application类
 */

public class MainApplication extends Application implements ViGoManager.IViGoCallbacks {
    // TAG
    public static final String TAG = "KC";
    // 操作对象
    public ViGoManager mViGoManager = null;
    public static MainApplication mMainApplication = null;

    public static MainApplication getInstance() {
        if (mMainApplication == null) {
            mMainApplication = new MainApplication();
        }
        return mMainApplication;
    }

    // RTMP 返回参数
    public String strRouteId = "";
    public String strSrcIp = "";
    public String strSrcPort = "";
    public String strDstIp = "";
    public String strDstPort = "";

    // UDP 返回参数
    public String strIp = "";
    public String straPort = "";
    public String strvPort = "";

    // 主页面对象
    public MainActivity mMainActivity = null;

    @Override
    public void onCreate() {
        super.onCreate();
        //
        LoadParam();
        mMainApplication = this;
        mViGoManager = ViGoManager.getInstance(this);
        if (mViGoManager != null) {
            // 加载引擎
            mViGoManager.pub_ViGoLoadMediaEngine();
            mViGoManager.pub_ViGoSetAndroidContext(this);
            mViGoManager.pub_ViGoInit();
            // 打开视频开关
            MainApplication.getInstance().mViGoManager.pub_ViGoGetConfig(UGoAPIParam.ME_CTRL_CFG_MODULE_ID, UGoAPIParam.getInstance().stMediaCfg, 0);
            UGoAPIParam.getInstance().stMediaCfg.ucRealTimeType = 0;
            UGoAPIParam.getInstance().stMediaCfg.ucVideoEnable = 1;
            UGoAPIParam.getInstance().stMediaCfg.ucEmodelEnable = 0;
            UGoAPIParam.getInstance().stMediaCfg.ucFecEnable = 1;
            UGoAPIParam.getInstance().stMediaCfg.ucRtpEncEnable = 0;
            UGoAPIParam.getInstance().stMediaCfg.ucExtMediaProcEn = 0;
            UGoAPIParam.getInstance().stMediaCfg.ucExtAudioTransEnable = 0;
            UGoAPIParam.getInstance().stMediaCfg.ucIPv6Enabled = 0;
            UGoAPIParam.getInstance().stMediaCfg.vieFecEnabled = false;
            UGoAPIParam.getInstance().stMediaCfg.vieNackEnabled = false;
            MainApplication.getInstance().mViGoManager.pub_ViGoSetConfig(UGoAPIParam.ME_CTRL_CFG_MODULE_ID, UGoAPIParam.getInstance().stMediaCfg, 0);
            // 设置视频编码
            MainApplication.getInstance().mViGoManager.pub_ViGoGetConfig(UGoAPIParam.ME_VIDEO_ENC_CFG_MODULE_ID, UGoAPIParam.getInstance().stVideoEncCfg, 0);
            UGoAPIParam.getInstance().stVideoEncCfg.usWidth = 360;
            UGoAPIParam.getInstance().stVideoEncCfg.usHeight = 480;
            UGoAPIParam.getInstance().stVideoEncCfg.ucmaxFramerate = 25;
            UGoAPIParam.getInstance().stVideoEncCfg.usStartBitrate = 350;
            UGoAPIParam.getInstance().stVideoEncCfg.usMaxBitrate = 2000;
            UGoAPIParam.getInstance().stVideoEncCfg.usMinBitrate = 30;
            UGoAPIParam.getInstance().stVideoEncCfg.ucUseHwEnc = 0;
            UGoAPIParam.getInstance().stVideoEncCfg.ucUseHwDec = 0;
            MainApplication.getInstance().mViGoManager.pub_ViGoSetConfig(UGoAPIParam.ME_VIDEO_ENC_CFG_MODULE_ID, UGoAPIParam.getInstance().stVideoEncCfg, 0);
            // 设置摄像头
            MainApplication.getInstance().mViGoManager.pub_ViGoGetCameraParam(UGoAPIParam.getInstance().stVideoDevicePara);
            UGoAPIParam.getInstance().stVideoDevicePara.usCameraIdx = -1;
            UGoAPIParam.getInstance().stVideoDevicePara.iRotateAngle = -1;
            UGoAPIParam.getInstance().stVideoDevicePara.ucMaxFps = 30;
            UGoAPIParam.getInstance().stVideoDevicePara.usWidth = 480;
            UGoAPIParam.getInstance().stVideoDevicePara.usHeight = 640;
            MainApplication.getInstance().mViGoManager.pub_ViGoSetCameraParam(UGoAPIParam.getInstance().stVideoDevicePara);
        }
    }

    @Override
    public void onTerminate() {
        super.onTerminate();
        if (mViGoManager != null) {
            mViGoManager.pub_ViGoDestroy();
        }
    }

    @Override
    public void eventCallback(int ev_type, int ev_reason, String message, String param) {
        Log.e(TAG, "eventCallback ev_type = " + ev_type);
        Log.e(TAG, "eventCallback ev_reason = " + ev_reason);
        Log.e(TAG, "eventCallback message = " + message);
        Log.e(TAG, "eventCallback param = " + param);

        UGoAPIParam.EventTypeEnum eventType = UGoAPIParam.EventTypeEnum.values()[ev_type];
        if (eventType == eME_VIDEO_NETWORK_STATE_EV) {
            Intent mIntent = new Intent(UIData.ACTION_NETWORK_STATE);
            mIntent.putExtra(UIData.ACTION_KEY, param);
            sendBroadcast(mIntent);
        }
    }

    @Override
    public void sendCallback(int media_type, int data_type, byte[] message, int len) {
        Log.e(TAG, "sendCallback media_type = " + media_type);
        Log.e(TAG, "sendCallback data_type = " + data_type);
    }

    @Override
    public void traceCallback(String summary, String detail, int level) {
        Log.e(TAG, "sendCallback summary = " + summary);
        Log.e(TAG, "sendCallback detail = " + detail);
        Log.e(TAG, "sendCallback level = " + level);
    }

    public void LoadParam() {
        UIData.REST_API_BASE = getSharedPreferences("REST_CFG", 1).getString("REST_API", UIData.REST_API_BASE);
        UIData.CPS_URL_BASE = getSharedPreferences("REST_CFG", 1).getString("CPS_API", UIData.CPS_URL_BASE);
    }

    public void SaveParam(String strRest, String strCps) {
        getSharedPreferences("REST_CFG", 1).edit().putString("REST_API", strRest).apply();
        getSharedPreferences("REST_CFG", 1).edit().putString("CPS_API", strCps).apply();
    }
}
