#ifndef _SK_TLV_APP_H_
#define _SK_TLV_APP_H_

#include "iTLVPickle.h"
//using namespace Comm;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define IGG_TYPE_DEFINE	(1024)
#define IGG_FUNC_DEFINE	(19995)

enum {
	eFuncIGGMicroMsgSKGetSelfSvnInfo = IGG_FUNC_DEFINE,
	eFuncIGGMicroMsgSKGetMetainfoFull,
	eFuncIGGMicroMsgSKGetMetainfo,
	eFuncIGGMicroMsgSKEcho
};

enum {
	eTypeIGGMicroMsgEchoInfo = Comm::eTypeSKUserDefine + IGG_TYPE_DEFINE + 1024,
	eTypeBaseRequest,
	eTypeBaseResponse,
	eTypeWebProxyInfo,
	eTypeBirthday,
	eTypeAuthRequest,
	eTypeAuthResponse,
	eTypeAuthBySKRequest,
	eTypeAuthBySKResponse,
	eTypeRtpp,
	eTypeRtppList,
	eTypeMedia,
	eTypeMediaList,
	eTypeSDP,
	eTypeCallReq,
	eTypeCallRsp,
	eTypeCallAck,
	eTypeCallRing,
	eTypeByeReq,
	eTypeUpdate,
	eTypeUpdateRsp,
	eTypeDirectNfy,
	eTypeRouteUpdate,
	eTypeDtmfInfo,
    /* add by Vinton.Liu on 2016-04-05 for add internal state passthrough signalling begin */
	eTypeInTransReq,
	eTypeInTransRsp
    /* Vinton.Liu add end */
};

typedef struct tagIGGMicroMsgEchoInfo {
	unsigned int iEchoLen;
	char * pcEchoStr;
} IGGMicroMsgEchoInfo_t;

// Auth
typedef struct tagIGGBodyHead_t 
{
	int Ret;
	unsigned int Uin;
	unsigned short CmdId;
	int ServerIdLen;
	unsigned char * ServerId;
	unsigned char DeviceId[16];
	short CompressVersion;
	short CompressAlgorithm;
	short CryptAlgorithm;
	unsigned int CompressLen;
	unsigned int CompressedLen;
}IGGBodyHead_t;

typedef struct tagIGGBaseRequest {
	char sSessionKey[36];				//SESSION KEY
	unsigned int iUin;					//UIN
	unsigned char cDeviceID[16];		//�豸ID
	int iClientVersion;					//�ͻ��˰汾��
	char sDeviceType[132];				//�豸����
	unsigned int iScene;				//������ʶ�����ο�enSceneStatus�궨�壩
	unsigned int iSeq;
} IGGBaseRequest_t;

typedef struct tagIGGAuthRequest {
	IGGBaseRequest_t tBaseRequest;
	Comm::SKBuiltinString_t tAccount;		//�˺�
	Comm::SKBuiltinString_t tPwd;			//���루��ҪMD5���������FB�û�����дTOKEN������ҪMD5��
	char * pcTimeZone;						//ʱ��
	char * pcLanguage;						//�豸����
	char * pcAuthTicket;						
	char * pcRealCountry;						//����
	Comm::SKBuiltinString_t tRandomEncryKey;	//�ͻ��˲��������������Կ
	Comm::SKBuiltinString_t tDevSid;
	Comm::SKBuiltinString_t tDevPwd;
	Comm::SKBuiltinString_t tLoginToken;
} IGGAuthRequest_t;

typedef struct tagIGGBaseResponse {
	int iRet;
	Comm::SKBuiltinString_t tErrMsg;
	unsigned int iSeq;
} IGGBaseResponse_t;

typedef struct tagIGGBirthday {
	unsigned int iYear;
	unsigned int iMonth;
	unsigned int iDay;
} IGGBirthday_t;

typedef struct tagIGGWebProxyInfo {
	int iIPCount;
	Comm::SKBuiltinString_t * ptIPList;
} IGGWebProxyInfo_t;

typedef struct tagIGGAuthResponse {
	IGGBaseResponse_t tBaseResponse;
	unsigned int iUin;							//UIN
	Comm::SKBuiltinString_t tUserName;			//�û���
	Comm::SKBuiltinString_t tNickName;			//�ǳ�
	Comm::SKBuiltinString_t tBindEmail;
	Comm::SKBuiltinString_t tBindMobile;
	unsigned int iStatus;
	char sSessionKey[36];						//SESSION KEY
	Comm::SKBuiltinBuffer_t tImgBuf;			//ͷ��BUFF
	unsigned int iNewVersion;					//�°汾��Ϣ��0���ʾ�Ѿ�������
	unsigned int iRegType;						//ע������
	unsigned int iProfileFlag;
	unsigned int iUserSex;						//�Ա𣨲���enMMSexType�궨�壩
	unsigned int iUserStatus;					//�û�״̬enUserStatus
	Comm::SKBuiltinString_t tFirstName;			
	Comm::SKBuiltinString_t tLastName;	
	IGGBirthday_t tBirthday;
	IGGWebProxyInfo_t tWebProxyInfo;            //������IP��Ϣ
	Comm::SKBuiltinString_t tSafeUserName;		//Safe�û���
	Comm::SKBuiltinString_t tClientNumber;
	Comm::SKBuiltinString_t tAppid;
} IGGAuthResponse_t;

typedef struct tagIGGAuthBySKRequest {
	IGGBaseRequest_t tBaseRequest;				//iScene�ֶ� ��дMM_SCENE_REAUTH
} IGGAuthBySKRequest_t;

typedef struct tagIGGAuthBySKResponse {
	IGGBaseResponse_t tBaseResponse;
	unsigned int iUin;							//Uin(�ͻ����õõ����ã��ò������Բ����)
	unsigned int iNewVersion;					//�°汾��Ϣ
	IGGWebProxyInfo_t tWebProxyInfo;            //������IP��Ϣ
	unsigned int iSysTime;					//ʱ���
} IGGAuthBySKResponse_t;

// voip
typedef struct tagRtpp{
	Comm::SKBuiltinString_t	cIp;   //Ip��ַ
	int  iDelay;		       //�����ӳ�
	int	 iLost;	               //������
}Rtpp_t; 

typedef struct tagRtppList{
	int  iCount;
	Rtpp_t*  ptList;
}RtppList_t;

typedef struct tagMedia{
	short  iPr;		 //Codec���ȼ���ֵԽС����Խ��
	short  iPt;		 //�������� ilbc/speex/g729
	char   cType;	 //(a/v) ��ӦAudio/video
	int    iPort;    //����˿�
}Media_t;

typedef struct tagMediaList{
	int  iCount;
	Media_t*	  ptList;
}MediaList_t;

typedef struct tagSDP{
	Comm::SKBuiltinString_t  cConIp;	//����ip��ַ
	Comm::SKBuiltinString_t  Ver;		    //ý��汾
	RtppList_t  tRtpplist;	//Rtpp�����б�
	MediaList_t  tMedialist;	//ý�������б�
	Comm::SKBuiltinBuffer_t  cIce;		    //ice��Ϣ
    unsigned char support_v; 
    Comm::SKBuiltinString_t through;
}SDP_t;


typedef struct
{
	Comm::SKBuiltinString_t callid;        //Ψһ��ʶһ���Ự���64
	SDP_t  callsvr_sdp;
	int 	type;                    //�������� 
	Comm::SKBuiltinString_t  fuserid;      //�32
	Comm::SKBuiltinString_t  fuid;         //�32
	Comm::SKBuiltinString_t  fphone;       //�ֻ���,�32
	Comm::SKBuiltinString_t  fnickname;    //�سƣ��128
	Comm::SKBuiltinString_t  touserid;      //�32
	Comm::SKBuiltinString_t  tophone;      //�����ֻ���
	Comm::SKBuiltinString_t  ver;          //�64
	int  sflag;
	Comm::SKBuiltinString_t	 through;   //�512
	Comm::SKBuiltinString_t	 userdata;  //�512
	unsigned char  meeting;         //�Ƿ�Ϊ�������
	unsigned char  fpv;             //ƽ̨, 0: all ,1:andriod ,2:ios, 3:pc
	unsigned char  fconntype;       //��������,,1:wifi,2:2G,4:3G,8:4G
}CallReq_t;

typedef struct
{
	Comm::SKBuiltinString_t  callid;        //Ψһ��ʶһ���Ự���64
	SDP_t  callsvr_sdp;
	int 	errcode;           
	Comm::SKBuiltinString_t	 ver;
	int         sflag;
	Comm::SKBuiltinString_t	 through;
}CallRsp_t;

typedef struct
{
	Comm::SKBuiltinString_t  callid;
	SDP_t  callsvr_sdp;
	int  ice_mode;  //Transport type, 0: p2p, 1: rtpp
	int  ice_type;  //Dynamic mode, 0: support, 1: unsupport
}CallAck_t;

typedef struct
{
	Comm::SKBuiltinString_t	  callid;
	SDP_t  callsvr_sdp; 
	Comm::SKBuiltinString_t  through;
	int  sflag;
}CallRing_t;

typedef struct
{
	Comm::SKBuiltinString_t	  callid; 
	int  errcode;
	Comm::SKBuiltinString_t	  through;
}ByeReq_t;

typedef struct
{
	Comm::SKBuiltinString_t	callid;
	Comm::SKBuiltinString_t   mip;
	int                 aport;
	int                 vport;
	Comm::SKBuiltinString_t   apt;
	Comm::SKBuiltinString_t   vpt;
	Comm::SKBuiltinString_t	through;
}CallUpdate_t;

typedef struct
{
	Comm::SKBuiltinString_t	  callid;
	int                   errcode;
	int                   ice_mode;
	Comm::SKBuiltinString_t	  through;
	Comm::SKBuiltinString_t	  apt;  //�64, ��Ƶ���� �������ʱ���Զ��ŷָ� ��18,107
	Comm::SKBuiltinString_t	  vpt;  //�64, ��Ƶ���� �������ʱ���Զ��ŷָ� ��107,108
}CallUpdateRsp_t;


typedef struct
{
	Comm::SKBuiltinString_t	  callid;
	int  errcode;
	Comm::SKBuiltinString_t	  through;
}DirectNfy_t;

typedef struct
{
	Comm::SKBuiltinString_t	  callid; 
	Comm::SKBuiltinString_t	  through;
	Comm::SKBuiltinString_t	  userid;
}RouteUpdate_t;

typedef struct
{
	Comm::SKBuiltinString_t	  callid; 
	Comm::SKBuiltinString_t	  dtmf;
}DtmfInfo_t;

/* add by Vinton.Liu on 2016-04-05 for add internal state passthrough signalling begin */
typedef struct
{
    Comm::SKBuiltinString_t	  callid;
    Comm::SKBuiltinString_t	  through; 
} InTransReq_t;

typedef struct
{
	Comm::SKBuiltinString_t	  callid; 
	int  errcode;
} InTransRsp_t;
/* Vinton.Liu add end */

extern const Comm::SKMetaInfo_t g_tMetaSipexMsg;

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif 




