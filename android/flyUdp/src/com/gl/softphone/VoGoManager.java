package com.gl.softphone;

import android.content.Context;
import android.util.Log;

import com.gl.softphone.UGoAPIParam.AudioInfo;
import com.gl.softphone.UGoAPIParam.LogTracePara;
import com.gl.softphone.UGoAPIParam.MediaFilePlayPara;
import com.gl.softphone.UGoAPIParam.EmodelInfo;
import com.gl.softphone.UGoAPIParam.EmodelValue;
import com.gl.softphone.UGoAPIParam.MediaFileRecordPara;

/**
 * @author： Rambo.fu
 * @date： 2014-4-8
 * @description：
 */
public class VoGoManager {
    final private static String TAG = "VoGoManager";

    private native int voeLoadMediaEngine();

    private native void voeSetAndroidContext(Context context);
    //private native int setAndroidApi(int level);

    private native int voeInit();

    private native void voeDestroy();

    private native int voeCreateAudioStream();

    private native void voeDeleteAudioStream();

    private native void voeSetAudioStream(AudioInfo audioInfo);

    private native void voeEnableAudioPlayout(boolean enable);//

    private native void voeEnableAudioSend(boolean enable);//

    native void voeEnableAudioReceive(boolean enable);//

    private native int voeSetState(int state);

    private native int voeGetState();

    private native int voeSetMicMute(boolean enable);

    private native boolean voeGetMicMute();

    private native int voeSetMicVoulme(int volume);

    private native int voeSetLoudSpeakerStatus(boolean enable);

    private native boolean voeGetLoudSpeakerStatus();

    private native int voeSetSpeakerVolume(int volume);

    private native void voeSendDTMF(char dtmf);

    private native int voeSetLogCfg(LogTracePara cfg);

    private native int voePlayFile(MediaFilePlayPara param);

    private native int voeStopFile();
    
    private native int voeStartRecord(MediaFileRecordPara para);
    
    private native int voeStopRecord();

    private native String voeGetVersion();

    private native int voeSetConfig(int moduleID, Object object, int version);

    private native int voeGetConfig(int moduleID, Object object, int version);

    private native int voeGetEmodelValue(EmodelInfo mos, EmodelInfo tr, EmodelInfo ppl, EmodelInfo burstr, EmodelInfo ie);

    private native int voeSetAndroidApi(int level);

    private native void Callbacks(IVoGoCallbacks cb);

    IVoGoCallbacks VoGoCallbacks;
    public static VoGoManager Single = null;

    public static VoGoManager getInstance(IVoGoCallbacks cb) {
        if (Single == null) {
            Log.i(TAG, "VoGoManager.getInstance()");
            Single = new VoGoManager();
            Single.VoGoCallbacks = cb;
            int apiLevel = Integer.parseInt(android.os.Build.VERSION.SDK);
            if (apiLevel < 9) {
                System.loadLibrary("OpenSLES");
            }
            System.loadLibrary("VoGo");
            return Single;
        } else {
            return Single;
        }
    }

    private VoGoManager() {

    }

    /**
     * Init voice engine
     *
     * @return 0 success, -1 failed
     */
    public synchronized int pub_VoGoInit() {
        //set callback function
        if ( VoGoCallbacks != null ) {
            Callbacks(VoGoCallbacks);
        }
        return voeInit();
    }

    /**
     * Destory voice engine
     */
    public synchronized void pub_VoGoDestroy() {
        voeDestroy();
    }

    /**
     * Set voice engine state
     * state value is  (0 Done, 1 Init OK, 2 Idle, 3 Running, 4 Connected)
     */
    public synchronized void pub_VoGoSetState(int state) {
        voeSetState(state);
    }

    /**
     * Get voice engine state
     *
     * @return 0 Done, 1 Init OK, 2 Idle, 3 Running, 4 Connected
     */
    public synchronized int pub_VoGoGetState() {
        return voeGetState();
    }

    /**
     * Send DTMF Tone
     *
     * @param dtmf DTMF value（0-9，*，#）
     */
    public synchronized void pub_VoGoSendDTMF(char dtmf) {
        voeSendDTMF(dtmf);
    }

    /*add by charlie yuan 2014.06.10 */
    public synchronized int pub_VoGoSetLogCfg(LogTracePara cfg) {
        return voeSetLogCfg(cfg);
    }

    public synchronized String pub_VoGoGetVersion() {
        return voeGetVersion();
    }

    public synchronized int pub_VoGoSetConfig(int methodID, Object config, int version) {
        return voeSetConfig( methodID, config, version);
    }

    public synchronized int pub_VoGoGetConfig(int methodID, Object config, int version) {
        return voeGetConfig(methodID, config, version);
    }

    public synchronized int pub_VoGoGetEmodelValue(EmodelValue ev) {
        return voeGetEmodelValue(ev.emodel_mos, ev.emodel_tr, ev.emodel_ppl, ev.emodel_burstr, ev.emodel_ie);
    }

    //add by charlie yuan 2014.06.09
    public synchronized int pub_VoGoLoadMediaEngine() {
        return voeLoadMediaEngine();
    }

    /**
     * Set Android Context
     *
     * @param context Application Context
     */
    public synchronized void pub_VoGoSetAndroidContext(Context context) {
        voeSetAndroidContext(context);
    }

    public synchronized int pub_VoGoSetAndroidApi(int level) {
        return voeSetAndroidApi(level);
    }

    public synchronized int pub_VoGoCreateAudioStream() {
        return voeCreateAudioStream();
    }

    public synchronized void pub_VoGoDeleteAudioStream() {
        voeDeleteAudioStream();
    }

    public synchronized void pub_VoGoSetAudioStream(AudioInfo audioInfo) {
        voeSetAudioStream(audioInfo);
    }

    public synchronized void pub_VoGoEnableAudioPlayout(boolean enable) {
        voeEnableAudioPlayout(enable);
    }

    public synchronized void pub_VoGoEnableAudioSend(boolean enable) {
        voeEnableAudioSend(enable);
    }

    public synchronized void pub_VoGoEnableAudioReceive(boolean enable) {
        voeEnableAudioReceive(enable);
    }

    public synchronized void pub_VoGoSetMicMute(boolean enable) {
        voeSetMicMute(enable);
    }

    public synchronized boolean pub_VoGoGetMicMute() {
        return voeGetMicMute();
    }

    public synchronized int pub_VoGoSetMicVoulme(int volume) {
        return voeSetMicVoulme(volume);
    }

    public synchronized void pub_VoGoSetLoudSpeakerStatus(boolean enable) {
    	voeSetLoudSpeakerStatus(enable);
    }

    public synchronized boolean pub_VoGoGetLoudSpeakerStatus() {
        return voeGetLoudSpeakerStatus();
    }

    public synchronized int pub_VoGoSetSpeakerVolume(int volume) {
        return voeSetSpeakerVolume(volume);
    }

    public synchronized int pub_VoGoPlayFile(MediaFilePlayPara param) {
        return voePlayFile(param);
    }

    public synchronized int pub_VoGoStopFile() {
        return voeStopFile();
    }
    
    public synchronized int pub_VoGoRecordStart(MediaFileRecordPara para) {
    	return voeStartRecord(para);
    }
    
    public synchronized int pub_VoGoRecordStop() {
    	return voeStopRecord();
    }
    //end add by charlie yuan 2014.06.09

    public static abstract interface IVoGoCallbacks {
        public abstract void eventCallback(int ev_type, int ev_reason, String something, String param);

        public abstract void sendCallback(int media_type, int data_type, byte[] message, int len);

        public abstract void traceCallback(String summary, String detail, int level);
    }

}
