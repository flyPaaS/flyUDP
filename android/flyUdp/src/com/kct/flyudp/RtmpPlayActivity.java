package com.kct.flyudp;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.RelativeLayout;
import android.widget.TextView;
import cn.nodemedia.NodePlayer;
import cn.nodemedia.NodePlayerDelegate;
import cn.nodemedia.NodePlayerView;

public class RtmpPlayActivity extends Activity implements NodePlayerDelegate {
	// 
	public NodePlayer np = null;
	
	private String streamId = "";
    private String dstIp = "";
    private String dstPort = "";
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
		this.requestWindowFeature(Window.FEATURE_NO_TITLE);
		setContentView(R.layout.activity_rtmp_play);
		//
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
        
        TextView title = (TextView)findViewById(R.id.rl_text);
        String str = "RtmpPull(" + streamId + ")";
        title.setText(str);
		
		// 创建NodePlayer实例
		np = new NodePlayer(this);

		// 查询播放视图
		NodePlayerView npv = (NodePlayerView) findViewById(R.id.live_player_view);
		// 设置播放视图的渲染器模式,可以使用SurfaceView或TextureView. 默认SurfaceView
		npv.setRenderType(NodePlayerView.RenderType.SURFACEVIEW);
		// 设置视图的内容缩放模式
		npv.setUIViewContentMode(NodePlayerView.UIViewContentMode.ScaleAspectFill);

		// 将播放视图绑定到播放器
		np.setPlayerView(npv);

		// 设置事件回调代理
		np.setNodePlayerDelegate(this);

		// 开启硬件解码,支持4.3以上系统,初始化失败自动切为软件解码,默认开启.
		np.setHWEnable(true);

		/**
		 * 设置启动缓冲区时长,单位毫秒.此参数关系视频流连接成功开始获取数据后缓冲区存在多少毫秒后开始播放
		 */
		np.setBufferTime(0);

		/**
		 * 设置最大缓冲区时长,单位毫秒.此参数关系视频最大缓冲时长.
		 * RTMP基于TCP协议不丢包,网络抖动且缓冲区播完,之后仍然会接受到抖动期的过期数据包.
		 * 设置改参数,sdk内部会自动清理超出部分的数据包以保证不会存在累计延迟,始终与直播时间线保持最大maxBufferTime的延迟
		 */
		np.setMaxBufferTime(0);

		/**
		 * 设置连接超时时长,单位毫秒.默认一直等待. 连接部分RTMP服务器,握手并连接成功后,当播放一个不存在的流地址时,会一直等待下去.
		 * 如需超时,设置该值.超时后返回1006状态码.
		 */
		np.setConnectWaitTimeout(10 * 1000);

		/**
		 * 设置播放直播视频url
		 */
		String playUrl = "rtmp://" + dstIp + ":" + dstPort + "/live/" + streamId;
		np.setInputUrl(playUrl);

		/**
		 * 开始播放直播视频
		 */
		np.start();
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		/**
         * 停止播放
         */
        np.stop();

        /**
         * 释放资源
         */
        np.release();
		// 
		if (MainApplication.getInstance().mMainActivity != null) {
			MainApplication.getInstance().mMainActivity.mHandler.sendEmptyMessage(1004);
		}
	}

	@Override
	public void onEventCallback(NodePlayer arg0, int arg1, String arg2) {
		Log.i("KC", "onEventCallback:" + arg1 + " msg:" + arg2);
		switch (arg1) {
		case 1000:
			// 正在连接视频
			break;
		case 1001:
			// 视频连接成功
			break;
		case 1002:
			// 视频连接失败 流地址不存在，或者本地网络无法和服务端通信，回调这里。5秒后重连， 可停止
			// nodePlayer.stopPlay();
			break;
		case 1003:
			// 视频开始重连,自动重连总开关
			// nodePlayer.stopPlay();
			break;
		case 1004:
			// 视频播放结束
			break;
		case 1005:
			// 网络异常,播放中断,播放中途网络异常，回调这里。1秒后重连，如不需要，可停止
			// nodePlayer.stopPlay();
			break;
		case 1006:
			// RTMP连接播放超时
			break;
		case 1100:
			// 播放缓冲区为空
			// System.out.println("NetStream.Buffer.Empty");
			break;
		case 1101:
			// 播放缓冲区正在缓冲数据,但还没达到设定的bufferTime时长
			// System.out.println("NetStream.Buffer.Buffering");
			break;
		case 1102:
			// 播放缓冲区达到bufferTime时长,开始播放.
			// 如果视频关键帧间隔比bufferTime长,并且服务端没有在缓冲区间内返回视频关键帧,会先开始播放音频.直到视频关键帧到来开始显示画面.
			// System.out.println("NetStream.Buffer.Full");
			break;
		case 1103:
			// System.out.println("Stream EOF");
			// 客户端明确收到服务端发送来的 StreamEOF 和 NetStream.Play.UnpublishNotify时回调这里
			// 注意:不是所有云cdn会发送该指令,使用前请先测试
			// 收到本事件，说明：此流的发布者明确停止了发布，或者因其网络异常，被服务端明确关闭了流
			// 本sdk仍然会继续在1秒后重连，如不需要，可停止
			// nodePlayer.stopPlay();
			break;
		case 1104:
			// 解码后得到的视频高宽值 格式为:{width}x{height}
			break;
		default:
			break;
		}
	}
}
