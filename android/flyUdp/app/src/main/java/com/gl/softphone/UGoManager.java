package com.gl.softphone;

import com.gl.softphone.UGoAPIParam.CallDialPara;
import com.gl.softphone.UGoAPIParam.ConferenceCallDialPara;//add by wuzhaoyang20140721

import com.gl.softphone.UGoAPIParam.CallInfo;
import com.gl.softphone.UGoAPIParam.EmodelInfo;
import com.gl.softphone.UGoAPIParam.EmodelValue;
import com.gl.softphone.UGoAPIParam.LogTracePara;
import com.gl.softphone.UGoAPIParam.MediaFilePlayPara;
import com.gl.softphone.UGoAPIParam.MediaFileRecordPara;
import com.gl.softphone.UGoAPIParam.CallPushPara;
import com.gl.softphone.UGoAPIParam.RtpConfig;
import com.gl.softphone.UGoAPIParam.RtppSrvConfig;
import com.gl.softphone.UGoAPIParam.TcpRecvPara;
import com.gl.softphone.UGoAPIParam.UGoConfig;
import com.gl.softphone.UGoAPIParam.TcpConfig;
import com.gl.softphone.UGoAPIParam.IceConfig;
import com.gl.softphone.UGoAPIParam.VideoCameraPara;
import com.gl.softphone.UGoAPIParam.VqeConfig;
import com.gl.softphone.UGoAPIParam.MediaConfig;
import com.gl.softphone.UGoAPIParam.AudioInfo;


import android.content.Context;
import android.util.Log;

/**
 * @author： 唐丹阳
 * @date： 2013-1-16
 * @description： 
 */
public class UGoManager
{
	native int UGoDebugEnabled(boolean enable, String filepath);
	native int UGoInit();
	native int UGoDestroy();
	native int UGoRegister(String uid,int mode);
	native int UGoUnRegister();
	native int UGoCallPush(CallPushPara param);
	native int UGoDial(CallDialPara para);
	native int UGoConferenceDial(Object para);//add by wuzhaoyang20140721
	native int UGoConferenceInv(Object para);
	native int UGoConferenceDel(int reason);
	native int UGoAnswer();
	native int UGoHangup(int reason);
	native String UGoGetVersion();
	native int UGoTcpRecvMsg(int recvlen, byte[] recvbuf);
	//native int UGoTcpRecvMsg(TcpRecvPara tcprecv);
	native int UGoTcpUpdateState(int state);
	native int UGoUpdateSystemState(int state);
	native int UGoSetMicMute(boolean enable);
    native boolean UGoGetMicMute();
	native int UGoSetLoudSpeakerStatus(boolean enable);
    native boolean UGoGetLoudSpeakerStatus();
    native boolean UGoGetRecordingDeviceStatus();
	native int UGoSendDTMF(char dtmf);
	native void Callbacks(IUGoCallbacks cb);
	native void setAndroidContext(Context context);
	native int UGoLoadMediaEngine();
	native int UGoSetConfig(int mothed,Object config,int version);
	native int UGoGetConfig(int mothed,Object config,int version);
	native int UGoGetState();
	native int UGoSetApi(int level);
	native int UGoSetLogFile(LogTracePara para, int version);
	/*add by Rookie 20130806 for emodel interface*/
	native String UGoGetEmodelValue();
	native int UGoStartRecord(MediaFileRecordPara para);
	native int UGoStopRecord();
	native int UGoPlayFile(MediaFilePlayPara para);
	native int UGoStopFile();
	native int UGoVideoSetCamera(VideoCameraPara para);
	native int UGoStartVideo(int sendReceive);
	native int UGoStopVideo(int sendReceive);
	native int UGoVideoGetCameraState(VideoCameraPara info);
	native int UGoScreenshotStart(int islocal, int type);
	native int UGoVideoSetSendReciveRotation(int send_rotation, int recived_rotation);
	native int UGoPresetVideo(String key, String val);
	native int UGoVideoIncomingFrame(byte[]data, int len);

	final private static String TAG = "UGoManager";

	//all callback function address
	IUGoCallbacks UGoCallbacks;

	public static UGoManager Single = null;

	public static UGoManager getInstance(IUGoCallbacks cb) {
		if ( Single == null ) {
			Single = new  UGoManager();
			Single.UGoCallbacks = cb;
			int apiLevel = Integer.parseInt(android.os.Build.VERSION.SDK);
			if(apiLevel < 9)
			{
				System.loadLibrary("OpenSLES");
			}
			try {
				System.loadLibrary("H264Encoder");
				System.loadLibrary("H264Decoder");
			} catch (Throwable e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
//			System.loadLibrary("ViGo");	
//			System.loadLibrary("VoGo");	
			System.loadLibrary("UGo");
			return Single;
		} else {
			Single.UGoCallbacks = cb;
            Log.i(TAG, "getInstance: Single already exist!!");
			return Single;
		}
	}
	
	public static void ReleaseInstance() {
		if ( null != Single ) {
			Log.i(TAG, "ReleaseInstance!!");
			Single = null;
		}		
	}
	
	private UGoManager() {
		
	}	
	
	public synchronized int pub_UGoDebugEnabled(boolean enable, String filepath)	{
		return UGoDebugEnabled(enable, filepath);
	}
	
	public synchronized int pub_UGoSetLogFile(LogTracePara para, int version) {
		return UGoSetLogFile(para, version);
	}
	
	public synchronized int pub_UGoGetState() {
		return UGoGetState();
	}

    public synchronized int pub_UGoSetApi(int level) {
		return UGoSetApi(level);
	}

	public synchronized int pub_UGoSetConfig(int methodID,Object config, int version) {
		return UGoSetConfig(methodID, config,version);
	}

	public synchronized int pub_UGoGetConfig(int method,Object config, int version)	{
		return UGoGetConfig(method,config,version);
	}
	
	public synchronized int pub_UGoSendDTMF(char dtmf) {
		return UGoSendDTMF(dtmf);
	}
	
	public synchronized int pub_UGoSetMicMute(boolean enable) {
		return UGoSetMicMute(enable);
	}

    public synchronized boolean pub_UGoGetMicMute() {
        return UGoGetMicMute();
    }

	public synchronized int pub_UGoSetLoudSpeakerStatus(boolean enable)	{
		return UGoSetLoudSpeakerStatus(enable);
	}

    public synchronized boolean pub_UGoGetLoudSpeakerStatus() {
        return UGoGetLoudSpeakerStatus();
    }

    public synchronized boolean pub_UGoGetRecordingDeviceStatus() {
    	return UGoGetRecordingDeviceStatus();
    }
    
	public synchronized String pub_UGoGetEmodelValue() {
		return UGoGetEmodelValue();
	}
	
	public synchronized int pub_UGoLoadMediaEngine() {
		return UGoLoadMediaEngine();
	}
	
	public synchronized int pub_UGoInit() {
		//set callback function
		if (UGoCallbacks != null) {
			Callbacks(UGoCallbacks);
		}

		return UGoInit();
	}

    public synchronized void pub_UGoCallbacks(IUGoCallbacks cb) {
        UGoCallbacks = cb;
        Callbacks(UGoCallbacks);
    }
	
	public synchronized int pub_UGoDestroy() {
		Log.i(TAG, "java pub_UGoDestroy()");
		return UGoDestroy();
	}
	
	public synchronized int pub_UGoRegister(String uid, int mode) {
		Log.v(TAG, "java pub_UGoRegister uid= "+uid+ "  mode="+mode);
		return UGoRegister(uid,mode);
	}
	
	public synchronized int pub_UGoUnRegister()	{
		return UGoUnRegister();
	}
	
	public synchronized int pub_UGoCallPush(CallPushPara param) {
		return UGoCallPush(param);
	}
	
	public synchronized int pub_UGoDial(CallDialPara para, int version) {
		if(para!=null)
		Log.v(TAG, "java pub_UGoDial uid= "+para.uid+ "  phone="+para.phone+ "  mode="+para.mode);
		return UGoDial(para);
	}

    //add by wuzhaoyang20140721
	public synchronized int pub_UGoConferenceDial(Object para, int version) {
		if(para!=null)
		    Log.v(TAG, "java pub_UGoConferenceDial start ");
		return UGoConferenceDial(para);
	}
	
	public synchronized int pub_UGoConferenceInv(Object para, int version) {
		if ( para == null ) {
			return -1;
		}
		return UGoConferenceInv(para);
	}
	
	public synchronized int pub_UGoConferenceDel(int reason) {
		return UGoConferenceDel(reason);
	}
	
	public synchronized int pub_UGoAnswer()	{
		return UGoAnswer();
	}
	
	public synchronized int pub_UGoHangup(int reason) {
		Log.v(TAG, "java pub_UGoHangup ");
		return UGoHangup(reason);
	}

	public synchronized String pub_UGoGetVersion() {
		return UGoGetVersion();
	}

	public synchronized  int pub_UGoTcpRecvMsg(int recvlen, byte[] recvbuf)	{
		return UGoTcpRecvMsg(recvlen,recvbuf);
	}
	
	public synchronized  int pub_UGoVideoIncomingFrame(byte[]data, int len)	{
		return UGoVideoIncomingFrame(data, len);
	}
	
	public synchronized int pub_UGoTcpUpdateState(int state) {
		return UGoTcpUpdateState(state);
	}
	
	public synchronized int pub_UGoUpdateSystemState(int state)	{
		return UGoUpdateSystemState(state);
	}
	
	public synchronized void pub_setAndroidContext(Context context)	{
		setAndroidContext(context);
	}

	public synchronized int pub_UGoStartRecord(MediaFileRecordPara para) {
		return UGoStartRecord(para);
	}

	public synchronized int pub_UGoStopRecord()	{
		return UGoStopRecord();
	}

	public synchronized int pub_UGoPlayFile(MediaFilePlayPara para)	{
		return UGoPlayFile(para);
	}

	public synchronized int pub_UGoStopFile() {
		return UGoStopFile();
	}
	
	public synchronized int pub_UGoSetVideoDevice(VideoCameraPara para)	{
		return UGoVideoSetCamera(para);
	}
	
	public synchronized int pub_UGoStartVideo(int sendReceive) {
		return UGoStartVideo(sendReceive);
	}
	
	public synchronized int pub_UGoStopVideo(int sendReceive) {
		return UGoStopVideo(sendReceive);
	}
	
	public synchronized int pub_UGoScreenshotStart(int islocal, int type) {
		return UGoScreenshotStart(islocal, type);
	}
	
	public synchronized int pub_UGoVideoSetSendReciveRotation(int send_rotation, int recived_rotation) {
		return UGoVideoSetSendReciveRotation(send_rotation, recived_rotation);
	}
	
	public  synchronized int  pub_UGoVideoGetCamera(VideoCameraPara info) {
		return UGoVideoGetCameraState(info);
	}
	
	public  synchronized int  pub_UGoPresetVideo(String key, String val) {
		return UGoPresetVideo(key, val);
	}

	public static abstract interface IUGoCallbacks {
		/**
		 * The method used to report calling event for application
		 * @param ev_type calling event
		 * @param ev_reason event reason
		 * @param message event description
		 * @param param event parameters object
		 */
		public abstract void eventCallback(int ev_type,
											int ev_reason, 
											String message,
											String param);
		
		/**
		 * The method used to send signaling message 
		 * @param message
		 * @param len
		 */
		public abstract void sendCallback(byte[] message, int len);
		
		/**
		 * The method used to report key message to application
		 * @param summary
		 * @param detail
		 * @param level
		 */
		public abstract void traceCallback(String summary, String detail, int level);

        /**
         * rtp/rtcp packets encrypt callback
         * @param inMsg the original packet
         * @param outMsg the encrypted packet for to send
         * @param inLen the length of inMsg
         * @param outLen the length of outMsg
         */
        public abstract void encryptCallback(byte[] inMsg, byte[] outMsg, 
        										int inLen, int[] outLen);

        /**
         * rtp/rtcp packets decrypt callback
         * @param inMsg the packet have been encrypted
         * @param outMsg the packet decrypt from inMsg
         * @param inLen the length of inMsg
         * @param outLen the length of outMsg
         */
        public abstract void decryptCallback(byte[] inMsg, byte[] outMsg, 
        										int inLen, int[] outLen);
        
        public abstract void screenshotCallback(byte[] dst_argb, int dst_stride, 
        										int width, int height, 
        										int islocal, int screen_type);
        
        /**
         * external pcm media processing in every 10ms
         * @param inSample pcm media data should being processing
         * @param outSample pcm media data that have been processed
         * @param samples samples num in every 10 ms
         * @param freqHz sample frequency in hz
         * @param isStereo whether stereo, means channel is 2 if stereo, else channel is 1
         */
        public abstract int mediaProcCallback(short[] inSample, short[] outSample, 
        										int samples, int freqHz, boolean isStereo);
                                                
        /**
         * The method used to tell application the parameters that audio playout data would used.
         * @param sample_rate
         * @param bytes_per_sample how many bytes of one sample, always 2 bytes = 16bit
         * @param num_of_channels
         */
        public abstract void initPlayout(int sample_rate,
        									int bytes_per_sample,
        									int num_of_channels);
        
        /**
         * The method used to tell application the parameters that audio recording should used
         * @param sample_rate
         * @param bytes_per_sample how many bytes of one sample, always 2 bytes = 16bit
         * @param num_of_channels
         */
        public abstract void initRecording(int sample_rate,
											int bytes_per_sample,
											int num_of_channels);
        
        /**
         * The method used to push audio playout data periodical for application to playout
         * @param outData
         * @param outSize
         * @return 0 for success, -1 for failure. if failure, would play to internal device
         */
        public abstract int writePlayoutData(byte[] outData, int outSize);
        
        /**
         * The method used to read audio recording data periodical form application
         * @param inData
         * @param inSize
         * @return 0 for success, -1 for failure. if failure, would use internal device recording data
         */
        public abstract int readRecordingData(byte[] inData, int inSize);
	}

}
