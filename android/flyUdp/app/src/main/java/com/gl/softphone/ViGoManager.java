package com.gl.softphone;

import android.content.Context;
import android.util.Log;

import com.gl.softphone.UGoAPIParam.LogTracePara;
import com.gl.softphone.UGoAPIParam.AudioInfo;
import com.gl.softphone.UGoAPIParam.VideoInfo;
import com.gl.softphone.UGoAPIParam.VideoCameraPara;
import com.gl.softphone.UGoAPIParam.LogCfg;
import java.util.Objects;

/**
 * @author： Vinton.Liu
 * @date： 2014-9-23
 * @description： 
 */
public class ViGoManager {
    final private static String TAG = "ViGoManager";

    private native int vieLoadMediaEngine();
    private native void vieSetAndroidContext(Context context);
    private native int vieInit();
    private native int vieDestroy();
    private native int vieSetState(int state);
    private native int vieGetState();
    private native int vieSetLogCfg(LogTracePara cfg);
    private native int vieSetLoudSpeakerStatus(boolean enable);
    private native boolean vieGetLoudSpeakerStatus();
    private native int vieSetConfig(int methodID, Object config, int version);
    private native int vieGetConfig(int methodID, Object config, int version);
    private native String vieGetVersion();
    private native int vieCreateAudioStream();
    private native int vieDeleteAudioStream();
    private native int vieSetAudioStream(AudioInfo audioInfo);
    private native int vieEnableAudioPlayout(boolean enable);//
    private native int vieEnableAudioSend(boolean enable);//
    private native int vieEnableAudioReceive(boolean enable);//
    private native int vieCreateVideoStream();
    private native int vieDeleteVideoStream();
    private native int vieSetVideoStream(VideoInfo videoInfo);
    private native int vieStartVideo(int type);
    private native int vieStopVideo(int type);
    private native int vieGetCameraCount();
    private native int vieGetCameraParam(VideoCameraPara para);
    private native int vieSetCameraParam(VideoCameraPara para);
    private native int vieSetMicMute(boolean enable);
    private native boolean vieGetMicMute();

    private native void Callbacks(IViGoCallbacks cb);
    private native int vieSetApi(int level);
    private native int vieSetLogFile(LogTracePara para, int version);

	//all callback function address
	IViGoCallbacks ViGoCallbacks;

	public static ViGoManager Single = null;

	public static ViGoManager getInstance(IViGoCallbacks cb) {
		if (Single == null) {
			Single = new ViGoManager();
			Single.ViGoCallbacks = cb;
			int apiLevel = Integer.parseInt(android.os.Build.VERSION.SDK);
			if(apiLevel < 9)
			{
				System.loadLibrary("OpenSLES");
			}

			System.loadLibrary("ViGo");

			return Single;
		} else {
            Log.i(TAG, "Instance have already exist.");
			return Single;
		}
	}

	private ViGoManager() {
		
	}

    public synchronized int pub_ViGoLoadMediaEngine( )
    {
        return vieLoadMediaEngine();
    }

    public synchronized int pub_ViGoInit() {
        //set callback function
        if ( ViGoCallbacks != null ) {
            Callbacks(ViGoCallbacks);
        }

        return vieInit();
    }

    public synchronized int pub_ViGoDestroy()
    {
        return vieDestroy();
    }

    public synchronized void pub_ViGoSetAndroidContext(Context context) {
        vieSetAndroidContext(context);
    }

    public synchronized String pub_ViGoGetVersion()	{
        return vieGetVersion();
    }

    public synchronized int pub_ViGoSetLogCfg(LogTracePara cfg) {
        return vieSetLogCfg(cfg);
    }

    public synchronized int pub_ViGoCreateAudioStream() {
        return vieCreateAudioStream();
    }

    public synchronized int pub_ViGoDeleteAudioStream() {
        return vieDeleteAudioStream();
    }

    public synchronized int pub_ViGoSetAudioStream(AudioInfo audioInfo ) {
        return vieSetAudioStream(audioInfo);
    }

    public synchronized int pub_ViGoEnableAudioPlayout(boolean enable) {
        return vieEnableAudioPlayout(enable);
    }

    public synchronized int pub_ViGoEnableAudioSend(boolean enable) {
        return vieEnableAudioSend(enable);
    }

    public synchronized int pub_ViGoEnableAudioReceive(boolean enable) {
        return vieEnableAudioReceive(enable);
    }

    public synchronized int pub_ViGoCreateVideoStream() {
        return vieCreateVideoStream();
    }

    public synchronized int pub_ViGoDeleteVideoStream() {
        return vieDeleteVideoStream();
    }

    public synchronized int pub_ViGoSetVideoStream(VideoInfo videoInfo ) {
        return vieSetVideoStream(videoInfo);
    }

    public synchronized int pub_ViGoStartVideo(int type)	{
        return vieStartVideo(type);
    }

    public synchronized int pub_ViGoStopVideo(int type) {
        return vieStopVideo(type);
    }

    public synchronized int pub_ViGoGetCameraCount() {
        return vieGetCameraCount();
    }

    public synchronized int pub_ViGoGetCameraParam(VideoCameraPara para) {
        return vieGetCameraParam(para);
    }

    public synchronized int pub_ViGoSetCameraParam(VideoCameraPara para) {
        return vieSetCameraParam(para);
    }

    public synchronized int pub_ViGoSetState( int state ) { return  vieSetState(state); }

    public synchronized int pub_ViGoGetState()
    {
        return vieGetState();
    }

    public synchronized int pub_ViGoSetLoudSpeakerStatus(boolean enable) {
        return vieSetLoudSpeakerStatus(enable);
    }

    public synchronized boolean pub_ViGoGetLoudSpeakerStatus() {
        return vieGetLoudSpeakerStatus();
    }

    public synchronized int pub_ViGoSetConfig(int methodID, Object config, int version) {
        return vieSetConfig(methodID, config, version);
    }

    public synchronized int pub_ViGoGetConfig(int method, Object config, int version)	{
        return vieGetConfig(method,config,version);
    }

    public synchronized int pub_ViGoSetLogFile(LogTracePara para, int version) {
		return vieSetLogFile(para, version);
	}

    public synchronized int pub_ViGoSetApi(int level) {
		return vieSetApi(level);
	}

	public synchronized int pub_ViGoSetMicMute(boolean enable) {
		return vieSetMicMute(enable);
	}

    public synchronized boolean pub_ViGoGetMicMute() {
        return vieGetMicMute();
    }

	public static abstract interface IViGoCallbacks {
		public abstract void eventCallback(int ev_type, int ev_reason, String message, String param);
		public abstract void sendCallback(int media_type, int data_type, byte[] message, int len);
		public abstract void traceCallback(String summary, String detail, int level);
	}

}
