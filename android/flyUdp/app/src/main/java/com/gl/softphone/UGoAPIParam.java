package com.gl.softphone;

/**
 * @author: Rambo.Fu
 * @date: 2014-4-3
 * @description: all api params/macro/enum definitions
 */
public class UGoAPIParam {
    /**
     * *UGo module state****
     */
    public static final int eUGo_STATE_WAIT = 0;        //wait
    public static final int eUGo_STATE_INVITE = 1;        //invite
    public static final int eUGo_STATE_RINGING = 2;     //ringing
    public static final int eUGo_STATE_CONNECT = 3;        //connect
    public static final int eUGo_STATE_PUSHACTIVE = 4;    //ios push call active
    public static final int eUGo_STATE_SYSACTIVE = 5;    //system call active

    /**
     * *UGo event type******
     */
    public enum EventTypeEnum {
        eME_RTP_TIMEOUT_EV,		// RTP timeout
        eME_RTP_UPSINGLEPASS_EV,// UP RTP single pass
        eME_RTP_DNSINGLEPASS_EV,// DN RTP single pass
        eME_NETWORK_STATE_EV,	// networt state ("general", "nice" ,"bad")
        eME_VIDEO_NETWORK_STATE_EV,	// networt state ("general", "nice" ,"bad")
        eME_EARLY_MEDIA_EV,		// early media (ringing)
        eME_DEVICE_EV,			// device status info
        eME_LOG_TRACE_EV,		// trace log
        eME_GET_DTMF_EV,		// dtmf event
        eME_FILE_PLAY_TO_ENDED,      // file play to end
        eME_VIDEO_EV,
        eME_REMOTE_VIDEO_STATE_NOTIFY_EV
    }
    
    /**
     * *network state reason******
     */
    public static final int eUGo_NETWORK_NICE = 0;           // nice, very good
    public static final int eUGo_NETWORK_WELL = 1;           // well, good
    public static final int eUGo_NETWORK_GENERAL = 2;        // general
    public static final int eUGo_NETWORK_POOR = 3;           // poor
    public static final int eUGo_NETWORK_BAD = 4;             // bad

    /**
     * *the reason for singlepass event**
     */
    public static final int eUGo_NETWORK_ERROR = 0;                //network problem
    public static final int eUGo_AUDIO_DEVICE_INIT = 1;            //local device init failed
    public static final int eUGo_START_SEND = 2;                //start send failed
    public static final int eUGo_START_RECEIVE_FAIL = 3;        //start receive failed
    public static final int eUGo_SET_LOCAL_RECEIVER_FAIL = 4;    //receive failed


    /****UGo event reason: begin*****/
    /**
     * success reason 0*
     */
    public static final int eUGo_Reason_Success = 0;    //success

    /*public reason 1~29*/
    public static final int eUGo_Reason_NotAccept = 1;    //not accept
    public static final int eUGo_Reason_RtppTimeOut = 2;    //RTPP RTP timeout
    public static final int eUGo_Reason_NoBalance = 3;    //nobalance
    public static final int eUGo_Reason_UpdateMediaFail = 4;    //update media fail
    public static final int eUGo_Reason_Busy = 5;    //busy
    public static final int eUGo_Reason_Reject = 6;    //reject
    public static final int eUGo_Reason_NotFind = 7;    //not find
    public static final int eUGo_Reason_TooShort = 8;    //Forbidden(callee too short)
    public static final int eUGo_Reason_CalleeFrozen = 9;    //callee have been frozen
    public static final int eUGo_Reason_Freeze = 10;    //caller have been frozen
    public static final int eUGo_Reason_Expired = 11;    //caller expired
    public static final int eUGo_Reason_Cancel = 12;    //Terminater for Cancel
    public static final int eUGo_Reason_Forbidden = 13;    //Forbidden(caller binding number)
    public static final int eUGo_Reason_NoResponse = 14;    //no response timeout
    public static final int eUGo_Reason_NetworkDisable = 15;   //The network is not supported
    public static final int eUGo_Reason_UnReachable = 16;   //Signaling inaccessible(NACK)
    public static final int eUGo_Reason_UnableToPush = 17;   //ios unable to push
    public static final int eUGo_Reason_CallidNotExist = 18;   //callid is not exist
    public static final int eUGo_Reason_NoAnswer = 19;    //callee have no answer
    public static final int eUGo_Reason_ConnectFaild = 20;    //connect faild
    public static final int eUGo_Reason_BlackList    = 23;     // blacklist

    /*client reason 30~49*/
    public static final int eUGo_Reason_HungupMyself = 30;   //call hungup by myself
    public static final int eUGo_Reason_HungupPeer = 31;   //call hungup by peer
    public static final int eUGo_Reason_HungupTCPDisconnected = 32;   //"Tcp event:Server connect failed!!!"
    public static final int eUGo_Reason_HungupRTPTimeout = 33;   //"medie engine: RTP time out!!!"
    public static final int eUGo_Reason_StartSendFailed = 34;   // start send failed
    
    /**
     * vps sever reason 50~79*
     */
    public static final int eUGo_Reason_ProxyAuth = 50;    //proxy auth
    public static final int eUGo_Reason_MsgHeadError = 51;    //message head error
    public static final int eUGo_Reason_MsgBodyError = 52;    //message body error
    public static final int eUGo_Reason_CallIDExist = 53;    //callid exist
    public static final int eUGo_Reason_MsgTimeOut = 54;    //message timeout
    public static final int eUGo_Reason_UserIdNotExist = 55;  // Called userid not exist


    /* conference reason  add by wuzhaoyang20140621 */
    public static final int eUGo_Reason_CONF_NO_EXIST = 60;  //find the conference fail
    public static final int eUGo_Reason_CONF_STATE_ERR = 61;  //conference state error
    public static final int eUGo_Reason_CONF_FULL = 62;  //conference full
    public static final int eUGo_Reason_CONF_CREATE_ERR = 63;  //create conference fail
    public static final int eUGo_Reason_CONF_CALL_FAILED = 64;  //call procedure fail
    public static final int eUGo_Reason_CONF_MEDIA_FAILED = 65;  //apply media resource fail
    public static final int eUGo_Reason_CONF_TER_UNSUPPORT = 66;  //the peer don't support
    public static final int eUGo_Reason_CONF_PARTICIPANT_OVER = 67; //too many participant
    public static final int eUGo_Reason_CONF_FINISHED = 68;  // conference finished

    /* conference reason  add by wuzhaoyang20140605 */
    public static final int eUGo_Reason_StateNotify = 70;   //conference state notify
    public static final int eUGo_Reason_ActiveModeConvert = 71;   //active change to conference mode
    public static final int eUGo_Reason_PassiveModeConvert = 72;   //passive change to conference mode

    /*temporary reason 80~98(notify:80~89,other:90~98)*/
    public static final int eUGo_Reason_NotifyPeerNotFind = 80;   //call notify peer uid not find
    public static final int eUGo_Reason_NotifyPeerOffLine = 81;   //call notify peer offline
    public static final int eUGo_Reason_NotifyPeerTimeout = 82;   //call notify free call timeout

    public static final int eUGo_Reason_Connecting = 97;    //connecting between send invite and don't receive response
    public static final int eUGo_Reason_Ringing = 98;   //Ringing response

    /**
     * video reason *
     */
    public static final int eUGo_Reason_VideoPreview = 150;
    public static final int eUGo_Reason_VideoStartSendRecive = 151;
    public static final int eUGo_Reason_VideoStartSend = 152;
    public static final int eUGo_Reason_VideoStartRecive = 153;
    public static final int eUGo_Reason_VideoStopSendRecive = 154;
    public static final int eUGo_Reason_VideoStopSend = 155;
    public static final int eUGo_Reason_VideoStopRecive = 156;
    public static final int eUGo_Reason_VideoRelease = 157;

    /**
     * unkown error 99*
     */
    public static final int eUGo_Reason_UnkownError = 99;    //unkown error
    /****UGo event reason: end*****/


    /**
     * *tcptransport state***
     */
    public static final int eUGo_TCP_DISCONNECTED = 0;
    public static final int eUGo_TCP_CONNECTED = 1;
    public static final int eUGo_TCP_RECONNECTED = 2;

    /**
     * Network type
     */
    public static final int eUGo_Network_type_WIFI = 1;
    public static final int eUGo_Network_Type_2G = 2;
    public static final int eUGo_Network_type_3G = 4;
    public static final int eUGo_Network_type_4G = 8;

    /**
     * system call state*
     */
    public static final int eUGo_SYSCALL_IDLE = 0;
    public static final int eUGo_SYSCALL_ACTIVE = 1;

    /**
     * **debug level **
     */
    public static final int eME_TraceNone = 0x0000;  // no trace
    public static final int eME_TraceStateInfo = 0x0001;
    public static final int eME_TraceWarning = 0x0002;
    public static final int eME_TraceError = 0x0004;
    public static final int eME_TraceDebug = 0x0800;    // debug
    public static final int eME_TraceInfo = 0x1000;  // debug info
    public static final int eME_TraceReport = 0x4000;  //calling report
    public static final int eME_TraceAll = 0xffff;

    /**
     * * call mode **
     */
    public static final int eUGo_CM_DIRECT = 4;
    public static final int eUGo_CM_AUTO = 5;
    public static final int eUGo_CM_FREE = 6;

    /**
     * * file play mode **
     */
    public static final int kME_FILE_HANDLE = 0;
    public static final int kME_FILE_STREAM = 1;
    public static final int kME_FILE_PATHNAME = 2;

    /**
     * **file format **
     */
    public static final int kME_FileFormatWavFile = 1;
    public static final int kME_FileFormatCompressedFile = 2;
    public static final int kME_FileFormatAviFile = 3;
    public static final int kME_FileFormatPreencodedFile = 4;
    public static final int kME_FileFormatPcm16kHzFile = 7;
    public static final int kME_FileFormatPcm8kHzFile = 8;
    public static final int kME_FileFormatPcm32kHzFile = 9;

    /**
     * ** record mode ** 
     */
    /** record all(double directions voice) **/
    public static final int kME_RECORD_MODE_ALL = 0;
    /** only record local microphone voice **/
    public static final int kME_RECORD_MODE_MIC = 1; 
    /** only record remote voice **/
    public static final int kME_RECORD_MODE_SPEAKER = 2;
    
    /**
     * ** method id ***
     */
    public static final int UGO_CFG_PARAM_MODULE_ID = 0;        // Corresponding  UGo module parameter configuration structure
    public static final int UGO_CFG_TCP_MODULE_ID = 1;            // corresponding  UGo module TCP configuration structure
    public static final int UGO_CFG_ICE_MODULE_ID = 2;            // Corresponding UGo module ICE configuration structure
    public static final int UGO_RTPP_CFG_MODULE_ID = 3;            //Corresponding  UGo module RTPP configuration structure
    public static final int UGO_EMODEL_MODULE_ID = 4;            //corresponds EMODEL module configuration structure (reservation)
   

    public static final int ME_CTRL_CFG_MODULE_ID = 100;            //Engine control module configuration corresponding media structure
    public static final int ME_VQE_CFG_MODULE_ID = 101;            //module configuration structure corresponding vqe
    public static final int ME_RTP_CFG_MODULE_ID = 102;            // rtp module configuration corresponding structure
    public static final int ME_ENV_CFG_MODULE_ID = 103;            //corresponding environment variables module configuration structure
    public static final int ME_VIDEO_ENC_CFG_MODULE_ID = 104; /* Encoder parameters included */
    public static final int ME_VIDEO_DEC_CFG_MODULE_ID = 105; /* Decoder parameters included */
    public static final int ME_VIDEO_RENDER_CFG_MODULE_ID = 106; /* Render parameters included */
    public static final int ME_VIDEO_PROCES_CFG_MODULE_ID = 107;  /* Image process parameters included */
    public static final int ME_CODECS_CFG_MODULE_ID       = 108;  // corresponding codec module configuration structure
    public static final int ME_VIDEO_EXTERN_CAPTURE_CFG_MODULE_ID = 109;  /* Image process parameters included */

    /*define struction*/
    public MediaConfig stMediaCfg = null;
    public RtpConfig stRTPCfg = null;


    //modity by charlie  yuan 2014.04.30
    //public static RtppSrvConfig[] astRTPSrvCfg = null;
    public RtppSrvConfig astRTPSrvCfg = null;

    public EnvConfig envConfig = null;
    public DecodeConfig decodeConfig = null;
    public UGoConfig stUGoCfg = null;
    //add by charlie yuan 2014.04.29
    public TcpConfig stTcpCfg = null;
    public IceConfig stIceCfg = null;
    //end add by charlie
    public VqeConfig stVQECfg = null;
    public VideoEncParam stVideoEncCfg = null;
    public VideoDecParam stVideodecCfg = null;

    public VideoRenderParam stVideoRenderCfg = null;
    public VideoProcess stVideoProcessCfg = null;
    public VideoExternCapture stVideoExternCapture = null;
    public EmodelInfo stEmlInfoCfg = null;
    public EmodelValue stEmlValueCfg = null;

    public VideoCameraPara stVideoDevicePara = null;
    public LogTracePara stLogTracePara = null;
    public CallDialPara stCallDialPara = null;
    public CallPushPara stCallPushPara = null;
    public MediaFileRecordPara MediaFileRecordPara = null;
    public TcpRecvPara stTcpRecvPara = null;
    public MediaFilePlayPara stMediaFilePlayPara = null;
    public AudioInfo stAudioInfo = null;
    public VideoInfo stVideoInfo = null;
    public LogCfg logCfg = null;

    public ConferenceTestDialPara stConferenceTestDialPara = null;
    public NoramlCallTestDialPara stNmlCallTestDialPara = null;

    public static UGoAPIParam ugoApiParam = null;
    public static UGoAPIParam getInstance() {
        if (ugoApiParam == null) {
            ugoApiParam = new UGoAPIParam();
        }
        return ugoApiParam;
    }

    public static final int MAX_VIDEO_CODEC_LIST_NUM = 10;

    public UGoAPIParam() {
        stMediaCfg = new MediaConfig();
        stRTPCfg = new RtpConfig();
        //modity by charlie yuan 2014.04.30
        //astRTPSrvCfg = new RtppSrvConfig[2];

        //astRTPSrvCfg[0] = new RtppSrvConfig();
        //astRTPSrvCfg[1] = new RtppSrvConfig();
        astRTPSrvCfg = new RtppSrvConfig();

        envConfig = new EnvConfig();
        decodeConfig = new DecodeConfig();
        stUGoCfg = new UGoConfig();
        stTcpCfg = new TcpConfig();
        stIceCfg = new IceConfig();
        //astRTPSrvCfg = new RtppSrvConfig();

        stVQECfg = new VqeConfig();
        stVideoEncCfg = new VideoEncParam();
        stVideoEncCfg.ucPlName = new String[MAX_VIDEO_CODEC_LIST_NUM];
        stVideoEncCfg.enable = new int[MAX_VIDEO_CODEC_LIST_NUM];
        stVideoEncCfg.ucPlType = new int[MAX_VIDEO_CODEC_LIST_NUM];
        stVideoEncCfg.bitrates = new int[3][3];
        stVideoEncCfg.presets = new int[3][3];
        stVideoEncCfg.fps = new int[3][3];

        
        stVideoRenderCfg = new VideoRenderParam();
        stVideodecCfg = new VideoDecParam();
        stVideoProcessCfg = new VideoProcess();
        stVideoExternCapture = new VideoExternCapture();
        
        stEmlInfoCfg = new EmodelInfo();
        stEmlValueCfg = new EmodelValue();
        stEmlValueCfg.emodel_mos = new EmodelInfo();
        stEmlValueCfg.emodel_ie = new EmodelInfo();
        stEmlValueCfg.emodel_ppl = new EmodelInfo();
        stEmlValueCfg.emodel_burstr = new EmodelInfo();
        stEmlValueCfg.emodel_tr = new EmodelInfo();
        stEmlValueCfg.emodel_delay = new EmodelInfo();
        stEmlValueCfg.emodel_jb = new EmodelInfo();
        stEmlValueCfg.callInfo = new CallInfo();
        
        stVideoDevicePara = new VideoCameraPara();
        stLogTracePara = new LogTracePara();
        stCallDialPara = new CallDialPara();
        stCallPushPara = new CallPushPara();
        MediaFileRecordPara = new MediaFileRecordPara();
        stTcpRecvPara = new TcpRecvPara();
        stMediaFilePlayPara = new MediaFilePlayPara();
        stAudioInfo = new AudioInfo();
        stVideoInfo = new VideoInfo();
        logCfg = new LogCfg();
        
        /* add by VintonLiu on 20141114 for conference auto test */
        stConferenceTestDialPara = new ConferenceTestDialPara();
        stNmlCallTestDialPara = new NoramlCallTestDialPara();
    }

    public class MediaConfig extends Object {
        public int ucRealTimeType;        	//Real time protocol type, 0: RTP 1: PRTP
        public int ucVideoEnable;        	//Video module, 0: disable 1: enable
        public int ucEmodelEnable;        	//Emodel module, 0: disable 1: enable, default 1
        public int ucFecEnable;   	 		//Fec module, 0: disable 1: enable, default 0
        public int ucRtpEncEnable;			// Rtp encrypt, 0: disabled, 1: enabled, default 0
        public int ucExtMediaProcEn;		// External pcm media processing, 0: disabled, 1: enabled, default 0
        public int ucExtAudioTransEnable;	// support external audio transport
        public int ucIPv6Enabled;        	// IPv6, 0: disabled 1: enabled, default 0
        public boolean vieFecEnabled;		// video fec enabled,  false for disabled, true for enabled, default false
        public boolean vieNackEnabled;		// video nack enabled, false for disabled, true for enabled, default false 
    }

    public class RtpConfig extends Object {
        public int uiRTPTimeout;        // rtp receive timeout. 5 -- 60s
        public boolean uiFixLowPayload;    //低码流标志，打开 ：true， 关闭: false,仅在使用私有协议时有效，当网络较差(2g)时打开（g729 60ms，silk 5k 60ms）
        								//低码流标志打开时，动态负载默认关闭
    }

    public class EnvConfig extends Object {
        public boolean status;    //open or close Speaker,0:closed the speaker, 1:open the speaker; default:0
        public int networktype;	  //network type: 0:2G; 1:3G; 2:wifi; 3:4G; the other value is invalid   
		public int dialogScene;   //dialog scene: 0: general mode; else other: meeting mode
    }

    public class DecodeConfig extends Object {
        public int codec_nums;
        public String codec_types;
        //public int decode_type[];
    }

    public class EncodeConfig extends Object {
        public int pltype;
        public String plname;
        public int enabled;
    }

    public class RtppSrvConfig extends Object {
        public int rtp_list_length;
        public String rtppcfg;
    }

    public class ConferenceCallDialPara extends Object { //add by wuzhaoyang20140721
        public int user_num;
        public  int conftype;
        public String user_attr;
        public  String roomname;
        public String roompwd;
        public  String remark;
    }

    /* add by VintonLiu on 20141114 for conference auto test */
    public class NoramlCallTestDialPara extends Object {
        public int isConfCall;         /* normal call or conference call */
        public int callRole;           /* call role, caller or called */
        public  int callCnt;            /* number of calls */
        public  int callTime;           /* the duration time per call */
        public  int callInterval;       /* interval time in every call */
        public  int mode;
        public  int video_enable;
        public  int ucalltype;          /* uxin calltype: 0:normal call 1:uxin liaoyiliao*/
        public  String uid;
        public  String phone;
    }

    public class ConferenceTestDialPara extends Object {
        public  int isConfCall;         /* normal call or conference call */
        public  int testFileIdx;        /* auto test play file index */
        public  int refFileIdx;         /* auto test reference file index, for caller */
        public  int callRole;           /* call role, caller or called */
        public  int callCnt;            /* number of calls */
        public  int callTime;           /* the duration time per call */
        public  int callInterval;       /* interval time in every call */
        public  int user_num;
        public  String user_attr;
        public  String roomname;
        public  String roompwd;
        public  String remark;
    }
    /* VintonLiu add end */

    //modity by yuanwenhai 2014.04.29
    public class UGoConfig extends Object {
        public  boolean rc4_enabled;
        public  boolean compress_enabled;  /* IM3.0 protocol compress enabled */
        public  boolean tlv_enabled;     /* IM3.0 protocol enabled */
        public  boolean ipv6_enabled;
        public  boolean csrv_enabled;    /* Customer service version enabled */
        public  int video_enabled;
        public int platform;
        public int atype;                /* Account type, 0 and 1 for im3.0, 2 for old json protocol */
        public String uid;               /* Client num */
        public String userid;            /* Userid for im3.0 */
        public String phone;
        public  String brand;
        public  String nickname;          /* Nickname */
        public  String localipaddr;       /* Local ip addr */
    }

    //add by charlie yuan 2014.04.29
    public class TcpConfig extends Object {
        public   boolean tcp_enabled;
        public   String tcp_srvaddr;
    }

    public class IceConfig extends Object {
        public boolean ice_enabled;
        public  boolean ipv6_enabled;
        public  String stun_server;
    }

    //end add by charlie yuan
    public class VqeConfig extends Object {
        public boolean Ec_enable;                	//Enable EC function on send side if TRUE, else disable
        public boolean Agc_enable;            		//Enable Agc function on send side if TRUE, else disable
        public boolean Ns_enable;                	//Enable Ns function on send side if TRUE, else disable
        public boolean Agc_Rx_enable;            	//Enable Agc function on receive side if TRUE, else disable
        public boolean Ns_Rx_enable;            	//Enable ns function on receive side if TRUE, else disable
        public int     Agc_targetDbfs;           	// agc target level,value range:1---15, default value:6,
	     											// typical value:3(high volume) 6(medium volume) 9(small volume) 
		public int 	   Agc_compressionGaindB;    	// agc compressionGain ,value range:1---30,default value 9, 
				 									// typical value:12(high volume) 9(medium volume) 6(small volume)
		public boolean Dual_Mic_Ns_enable;          //Enable dual microphone noise suppression
    }
    
    public class VideoEncParam {
        public String ucPlName[];
        public int ucPlType[];
        public int enable[];
        public int usNum;
        public  int usWidth;
        public int usHeight;
        public  int usStartBitrate;
        public   int usMaxBitrate;
        public   int usMinBitrate;
        public   int ucmaxFramerate;
        public   int ucQpMax;
        public 	int ucComplexity; /* 0-4*/
        public int ucFirstSelectedPt; /* 0-4*/
        public int ucUseHwEnc;
        public int ucUseHwDec;
        public int bitrates[][];
        public int presets[][];
        public int fps[][];
    }

    public class VideoDecParam {
        public int uiMaxDefinition;
        public int ucmaxFramerate;
    }

    public class VideoRenderParam {
        public  Object pWindowRemote;
        public Object pWindowLocal;
        public int	remoteWidth;
        public int	remoteHeight;
        public int	renderMode;
    }


    public class VideoProcess {
        public boolean deflickingEnable;
        public  boolean denoisingEnable;
        public boolean enhancementEnable;
    }
    
    public class VideoExternCapture {
        public boolean useExternCapture;
        public int     ucExternformate;
    }

    public class EmodelInfo extends Object {
        public int flag;
        public int count;
        public double total;
        public double average;
        public double min;
        public double max;
        public double current;
    }
    
    public class CallInfo extends Object {
        public String strCallid;   /* callid */
        public String strMgw;      /* ip of media gateway */
        public String strSgw;      /* ip of signalling gateway */
        public String strCodec;    /* communicate codec */
        public int    iCallMode;   /* call mode */
        public int    iTransMode;  /* transmit mode */
        public int    iCTime;      /* offset time between connecting and ringing event */
        public int    iCallState;  /* call state, eg. single pass */
        public int    iRole;       /* call role, caller or callee */
        public int    iMgwPort;    /* port for media gateway */
        public int    iPktSnd;     /* count for media packets has send */
        public int    iPktRev;     /* count for media packets has received */
        public int    iSpRsn;      /* reason for single-pass state */
        public int    isMute;     /* if mircrophone is muted when hang up */
    }

    public class EmodelValue extends Object {
        public EmodelInfo emodel_mos;
        public EmodelInfo emodel_tr;
        public EmodelInfo emodel_ppl;
        public EmodelInfo emodel_burstr;
        public EmodelInfo emodel_ie;
        public  EmodelInfo emodel_jb;
        public EmodelInfo emodel_delay;
        public CallInfo   callInfo;
    }

    public class CallDialPara {
        public String uid;
//        String fnickname;
        public String phone;
        public String userdata;
        public int mode;
        public int video_enable;
        public int ucalltype; /* uxin calltype: 0:normal call 1:uxin liaoyiliao*/
    }

    public class CallPushPara {
        public String callid;
        public int vpsid;
        public int reason;
    }
    
    public class MediaFileRecordPara {
        public String filePath;
        public int iRecordMode;  //record mode, 0: all, 1: mic, 2: speaker
        public int iFileFormat;
    }

    public class MediaFilePlayPara {
        public int mode;        //0:unused, 1:file stream mode, 2:file name mode
        public String filepath;
        public int iFileFormat;
        public int iDirect;  // 0: play to local, 1: play to remote
        public int iLoop;
        public int data_size;
        public byte[] audioData;
    }

    public class LogTracePara {
        public int level;
        public String path;
    }

    public class TcpRecvPara {
        public int recvlen;
        public byte[] recvbuf;
    }

    public class VideoCameraPara {
        public int usWidth;
        public int usHeight;
        public int iRotateAngle;
        public int usCameraIdx;
        public int ucMaxFps;
    }

    public class AudioInfo {
        public int playload;
        public String remote_ip;
        public int remote_port;
        public int local_port;
        public boolean ucExTransportEnable;
    }

    public class VideoInfo {
        public int playload;
        public String remote_ip;
        public int remote_port;
        public int local_port;
        public boolean ucExTransportEnable;
    }

    public class LogCfg {
        public String path;
        public int level;
    }
}
