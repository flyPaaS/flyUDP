package com.kct.flyudp;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.res.Configuration;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.Surface;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;
import cn.nodemedia.LivePublisher;
import cn.nodemedia.LivePublisherDelegate;

public class RtmpVideoActivity extends Activity implements View.OnClickListener, LivePublisherDelegate {
	// 控件
	private GLSurfaceView glsv;
	private Button micBtn, swtBtn, videoBtn, flashBtn, camBtn;
	private boolean isStarting = false;
	private boolean isMicOn = true;
	private boolean isCamOn = true;
	private boolean isFlsOn = true;

	private String streamId = "";
	private String dstIp = "";
	private String dstPort = "";

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
		this.requestWindowFeature(Window.FEATURE_NO_TITLE);
		setContentView(R.layout.activity_rtmp_video);
		// 初始化控件
		isStarting = false;
		glsv = (GLSurfaceView) findViewById(R.id.camera_preview);
		micBtn = (Button) findViewById(R.id.button_mic);
		swtBtn = (Button) findViewById(R.id.button_sw);
		videoBtn = (Button) findViewById(R.id.button_video);
		flashBtn = (Button) findViewById(R.id.button_flash);
		camBtn = (Button) findViewById(R.id.button_cam);

		micBtn.setOnClickListener(this);
		swtBtn.setOnClickListener(this);
		videoBtn.setOnClickListener(this);
		flashBtn.setOnClickListener(this);
		camBtn.setOnClickListener(this);

		streamId = getIntent().getStringExtra("stream");
		dstIp = getIntent().getStringExtra("dstIp");
		dstPort = getIntent().getStringExtra("dstPort");

		// 标题
		RelativeLayout rl_back = (RelativeLayout) findViewById(R.id.rl_back);
		rl_back.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				finish();
			}
		});

		TextView title = (TextView) findViewById(R.id.rl_text);
		String str = "RtmpPush(" + streamId + ")";
		title.setText(str);

		// 1.初始化
		LivePublisher.init(this);
		// 2.设置事件回调
		LivePublisher.setDelegate(this);

		/**
		 * 设置输出音频参数 bitrate 码率 32kbps aacProfile 音频编码复杂度
		 * 部分服务端不支持HE-AAC,会导致发布失败，如果服务端支持，直接用HE-AAC AAC_PROFILE_LC 低复杂度编码
		 * AAC_PROFILE_HE 高效能编码 ，能达到LC-AAC一半的码率传输相同的音质
		 */
		LivePublisher.setAudioParam(32 * 1000, LivePublisher.AAC_PROFILE_HE);

		/**
		 * 设置输出视频参数 width 视频宽 height 视频高 注意，视频最终输出的高宽和发布方向有关，这里设置
		 * 16：9的分辨率就行，sdk自动切换。
		 *
		 * fps 视频帧率 bitrate 视频码率 注意，sdk 1.0.1以后，视频码率为最大码率，可以比以前的版本值高一点，编码器自动调节
		 * avcProfile 视频编码复杂度，高中低为三者比较相对而言。可根据应用场景选择 AVC_PROFILE_BASELINE
		 * 低CPU，低画质 AVC_PROFILE_MAIN 中CPU，中画质 AVC_PROFILE_HIGH 高CPU，高画质
		 *
		 * 以下建议分辨率及比特率 不用超过1280x720 
		 * 320X180@15 ~~ 300kbps ~~ baseline 
		 * 568x320@15 ~~ 400kbps ~~ baseline
		 * 640X360@15 ~~ 500kbps ~~ main
		 * 854x480@15 ~~ 600kbps ~~ main
		 * 960x540@15 ~~ 800kbps ~~ high
		 * 1280x720@15 ~~ 1000kbps ~~ high
		 */
		
		if (UIData.nCodec == 0) {
			// 200kbps
			LivePublisher.setVideoParam(320, 180, 15, 200 * 1000, LivePublisher.AVC_PROFILE_MAIN);
		}
		if (UIData.nCodec == 1) {
			// 300kbps
			LivePublisher.setVideoParam(568, 320, 15, 300 * 1000, LivePublisher.AVC_PROFILE_MAIN);
		}
		if (UIData.nCodec == 2) {
			// 400kbps
			LivePublisher.setVideoParam(640, 360, 15, 400 * 1000, LivePublisher.AVC_PROFILE_MAIN);
		}
		if (UIData.nCodec == 3) {
			// 500kbps
			LivePublisher.setVideoParam(720, 406, 15, 500 * 1000, LivePublisher.AVC_PROFILE_MAIN);
		}
		if (UIData.nCodec == 4) {
			// 600kbps
			LivePublisher.setVideoParam(854, 480, 15, 600 * 1000, LivePublisher.AVC_PROFILE_MAIN);
		}
		if (UIData.nCodec == 5) {
			// 700kbps
			LivePublisher.setVideoParam(960, 540, 15, 700 * 1000, LivePublisher.AVC_PROFILE_MAIN);
		}
		if (UIData.nCodec == 6) {
			// 800kbps
			LivePublisher.setVideoParam(1024, 576, 15, 800 * 1000, LivePublisher.AVC_PROFILE_MAIN);
		}
		if (UIData.nCodec == 7) {
			// 1000kbps
			LivePublisher.setVideoParam(1280, 720, 15, 1000 * 1000, LivePublisher.AVC_PROFILE_MAIN);
		}

		/**
		 * 是否开启背景噪音抑制
		 */
		LivePublisher.setDenoiseEnable(true);

		/**
		 * 设置美颜等级 0-5 0就关，5最高，可随时改动
		 */
		LivePublisher.setSmoothSkinLevel(0);

		/**
		 * 设置关键帧间隔 单位秒 默认1 gop_size = fps * keyFrameInterval
		 * 注意,低关键帧间隔可以使得播放端快速显示画面,sdk默认每秒一个关键帧 提高关键帧间隔可以提供更高的数据压缩比,节省部分网络带宽
		 */
		// LivePublisher.setKeyFrameInterval(2);

		/**
		 * 开启视频编码动态自适应码率,默认关闭 开启后,sdk内部会根据发送缓冲队列的长度来动态调整视频码率以适应当前带宽
		 * 会在上传带宽不足,网络频繁波动等情况下触发码率降低,画质会变差,但流畅度得以保证. SDK内部会根据网络状况变优自动提升回设定码率.
		 */
		// LivePublisher.setDynamicRateEnable(true);

		/**
		 * 开始视频预览 cameraPreview ： 用以回显摄像头预览的GLSurfaceView对象，如果此参数传入null，则只发布音频
		 * 注意,如果做纯音频应用,请保证xml布局文件里不要放入GLSurfaceView控件,否则由于没有处理GLSurfaceView的渲染器会造成崩溃
		 *
		 * camId： 摄像头初始id，LivePublisher.CAMERA_BACK
		 * 后置，LivePublisher.CAMERA_FRONT 前置 frontMirror:
		 * 是否启用前置摄像头镜像模式。当为true时，预览画面为镜像画面。当为false时，预览画面为原始画面
		 * 镜像画面就是平时使用系统照相机切换前置摄像头时所显示的画面，就像自己照镜子看到的画面。 原始画面就是最终保存或传输到观看者所显示的画面。
		 */
		LivePublisher.startPreview(glsv, LivePublisher.CAMERA_FRONT, true);
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		LivePublisher.stopPublish(); // 停止发布
		LivePublisher.stopPreview(); // 停止预览
		//
		if (MainApplication.getInstance().mMainActivity != null) {
			MainApplication.getInstance().mMainActivity.mHandler.sendEmptyMessage(1004);
		}
	}

	@Override
	public void onConfigurationChanged(Configuration newConfig) {
		super.onConfigurationChanged(newConfig);
		// 界面方向改变，通知sdk调整摄像头方向和视频方向
		// 注意：如果你的业务方案需求只做单一方向的视频直播，可以不处理这段

		// 如果程序UI没有锁定屏幕方向，旋转手机后，请把新的界面方向传入，以调整摄像头预览方向
		LivePublisher.setCameraOrientation(getWindowManager().getDefaultDisplay().getRotation());

		// 还没有开始发布视频的时候，可以跟随界面旋转的方向设置视频与当前界面方向一致，但一经开始发布视频，视频发布方向就锁定了
		// 发布中旋转只会让预览界面跟随旋转，当停止发布后再开始发布，新的流视频方向就与界面方向一致了
		switch (getWindowManager().getDefaultDisplay().getRotation()) {
		case Surface.ROTATION_0:
			LivePublisher.setVideoOrientation(LivePublisher.VIDEO_ORI_PORTRAIT);
			break;
		case Surface.ROTATION_90:
			LivePublisher.setVideoOrientation(LivePublisher.VIDEO_ORI_LANDSCAPE);
			break;
		case Surface.ROTATION_180:
			LivePublisher.setVideoOrientation(LivePublisher.VIDEO_ORI_PORTRAIT_REVERSE);
			break;
		case Surface.ROTATION_270:
			LivePublisher.setVideoOrientation(LivePublisher.VIDEO_ORI_LANDSCAPE_REVERSE);
			break;
		}
	}

	@Override
	public void onEventCallback(int arg0, String arg1) {
		handler.sendEmptyMessage(arg0);
	}

	@Override
	public void onClick(View v) {
		switch (v.getId()) {
		case R.id.button_mic:
			if (isStarting) {
				isMicOn = !isMicOn;
				LivePublisher.setMicEnable(isMicOn); // 设置是否打开麦克风
				if (isMicOn) {
					handler.sendEmptyMessage(3101);
				} else {
					handler.sendEmptyMessage(3100);
				}
			}
			break;
		case R.id.button_sw:
			LivePublisher.switchCamera();// 切换前后摄像头
			LivePublisher.setFlashEnable(false);// 关闭闪光灯,前置不支持闪光灯
			isFlsOn = false;
			flashBtn.setBackgroundResource(R.drawable.ic_flash_off);
			break;
		case R.id.button_video:
			if (isStarting) {
				LivePublisher.stopPublish();// 停止发布
			} else {
				/**
				 * 设置视频发布的方向，此方法为可选，如果不调用，则输出视频方向跟随界面方向，如果特定指出视频方向，
				 * 在startPublish前调用设置 videoOrientation ： 视频方向 VIDEO_ORI_PORTRAIT
				 * home键在 下 的 9:16 竖屏方向 VIDEO_ORI_LANDSCAPE home键在 右 的 16:9 横屏方向
				 * VIDEO_ORI_PORTRAIT_REVERSE home键在 上 的 9:16 竖屏方向
				 * VIDEO_ORI_LANDSCAPE_REVERSE home键在 左 的 16:9 横屏方向
				 */
				// LivePublisher.setVideoOrientation(LivePublisher.VIDEO_ORI_LANDSCAPE);

				/**
				 * 设置发布模式 参考 rtmp_specification_1.0.pdf 7.2.2.6. publish
				 * LivePublisher。PUBLISH_TYPE_LIVE 'live' 发布类型
				 * LivePublisher。PUBLISH_TYPE_RECORD 'record' 发布类型
				 * LivePublisher。PUBLISH_TYPE_APPEND 'append' 发布类型
				 */
				// LivePublisher.setPublishType(LivePublisher.PUBLISH_TYPE_RECORD);

				/**
				 * 开始视频发布 rtmpUrl rtmp流地址
				 */
				String pubUrl = "rtmp://" + dstIp + ":" + dstPort + "/live/" + streamId;
				LivePublisher.startPublish(pubUrl);
			}
			break;
		case R.id.button_flash:
			int ret = -1;
			if (isFlsOn) {
				ret = LivePublisher.setFlashEnable(false);
			} else {
				ret = LivePublisher.setFlashEnable(true);
			}
			if (ret == -1) {
				// 无闪光灯,或处于前置摄像头,不支持闪光灯操作
			} else if (ret == 0) {
				// 闪光灯被关闭
				flashBtn.setBackgroundResource(R.drawable.ic_flash_off);
				isFlsOn = false;
			} else {
				// 闪光灯被打开
				flashBtn.setBackgroundResource(R.drawable.ic_flash_on);
				isFlsOn = true;
			}
			break;
		case R.id.button_cam:
			if (isStarting) {
				isCamOn = !isCamOn;
				LivePublisher.setCamEnable(isCamOn);
				if (isCamOn) {
					handler.sendEmptyMessage(3103);
				} else {
					handler.sendEmptyMessage(3102);
				}
			}
			break;
		default:
			break;
		}
	}

	@SuppressLint("HandlerLeak")
	private Handler handler = new Handler() {
		// 回调处理
		@Override
		public void handleMessage(Message msg) {
			super.handleMessage(msg);
			switch (msg.what) {
			case 2000:
				Toast.makeText(RtmpVideoActivity.this, "正在发布视频", Toast.LENGTH_SHORT).show();
				break;
			case 2001:
				Toast.makeText(RtmpVideoActivity.this, "视频发布成功", Toast.LENGTH_SHORT).show();
				videoBtn.setBackgroundResource(R.drawable.ic_video_start);
				isStarting = true;
				break;
			case 2002:
				Toast.makeText(RtmpVideoActivity.this, "视频发布失败", Toast.LENGTH_SHORT).show();
				break;
			case 2004:
				Toast.makeText(RtmpVideoActivity.this, "视频发布结束", Toast.LENGTH_SHORT).show();
				videoBtn.setBackgroundResource(R.drawable.ic_video_stop);
				isStarting = false;
				break;
			case 2005:
				Toast.makeText(RtmpVideoActivity.this, "网络异常,发布中断", Toast.LENGTH_SHORT).show();
				break;
			case 2100:
				// 发布端网络阻塞，已缓冲了2秒的数据在队列中
				Toast.makeText(RtmpVideoActivity.this, "网络阻塞，发布卡顿", Toast.LENGTH_SHORT).show();
				break;
			case 2101:
				// 发布端网络恢复畅通
				Toast.makeText(RtmpVideoActivity.this, "网络恢复，发布流畅", Toast.LENGTH_SHORT).show();
				break;
			case 2102:
				Toast.makeText(RtmpVideoActivity.this, "截图保存成功", Toast.LENGTH_SHORT).show();
				break;
			case 2103:
				Toast.makeText(RtmpVideoActivity.this, "截图保存失败", Toast.LENGTH_SHORT).show();
				break;
			case 2104:
				Toast.makeText(RtmpVideoActivity.this, "网络阻塞严重,无法继续推流,断开连接", Toast.LENGTH_SHORT).show();
				break;
			case 2300:
				Toast.makeText(RtmpVideoActivity.this, "摄像头和麦克风都不能打开,用户没有给予访问权限或硬件被占用", Toast.LENGTH_SHORT).show();
				break;
			case 2301:
				Toast.makeText(RtmpVideoActivity.this, "麦克风无法打开", Toast.LENGTH_SHORT).show();
				break;
			case 2302:
				Toast.makeText(RtmpVideoActivity.this, "摄像头无法打开", Toast.LENGTH_SHORT).show();
				break;
			case 3100:
				// mic off
				micBtn.setBackgroundResource(R.drawable.ic_mic_off);
				Toast.makeText(RtmpVideoActivity.this, "麦克风静音", Toast.LENGTH_SHORT).show();
				break;
			case 3101:
				// mic on
				micBtn.setBackgroundResource(R.drawable.ic_mic_on);
				Toast.makeText(RtmpVideoActivity.this, "麦克风恢复", Toast.LENGTH_SHORT).show();
				break;
			case 3102:
				// camera off
				camBtn.setBackgroundResource(R.drawable.ic_cam_off);
				Toast.makeText(RtmpVideoActivity.this, "摄像头传输关闭", Toast.LENGTH_SHORT).show();
				break;
			case 3103:
				// camera on
				camBtn.setBackgroundResource(R.drawable.ic_cam_on);
				Toast.makeText(RtmpVideoActivity.this, "摄像头传输打开", Toast.LENGTH_SHORT).show();
				break;
			default:
				break;
			}
		}
	};

}
