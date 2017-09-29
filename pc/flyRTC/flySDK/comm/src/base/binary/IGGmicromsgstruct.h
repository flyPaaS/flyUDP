/* IGGmicromsgstruct.h

  bingchen 2014.2.19

*/

#pragma once

#include "iTLVPickle.h"

#define UPDATE_VERSION "2014-03-01:1646"

#ifdef __cplusplus
extern "C" {
#endif

#define IGG_TYPE_DEFINE	(1024)
#define IGG_FUNC_DEFINE	(19995)

enum {
	eTypeIGGMicroMsgEchoInfo = Comm::eTypeSKUserDefine + IGG_TYPE_DEFINE,
	eTypeIGGBaseRequest,
	eTypeIGGBuiltinIP,
	eTypeIGGBuiltinIPList,
	eTypeIGGCDNDnsInfo,
	eTypeIGGAuthRequest,
	eTypeIGGRegRequest,
	eTypeIGGBaseResponse,
	eTypeIGGNetworkControl,
	eTypeIGGPluginKey,
	eTypeIGGPluginKeyList,
	eTypeIGGHost,
	eTypeIGGHostList,
	eTypeIGGAuthResponse,
	eTypeIGGRegResponse,
	eTypeIGGUserInfoSetRequest,
	eTypeIGGUserInfoSetResponse,
	eTypeIGGCmdItem,
	eTypeIGGNewInitRequest,
	eTypeIGGNewInitResponse,
	eTypeIGGSnsUserInfo,
	eTypeIGGCustomizedInfo,
	eTypeIGGSearchContactRequest,
	eTypeIGGSearchContactItem,
	eTypeIGGSearchContactResponse,
	eTypeIGGVerifyUser,
	eTypeIGGVerifyUserRequest,
	eTypeIGGVerifyUserResponse,
	eTypeIGGPossibleFriend,
	eTypeIGGSyncFriendRequest,
	eTypeIGGSyncFriendResponse,
	eTypeIGGRoomInfo,
	eTypeIGGChatRoomMember,
	eTypeIGGModContact,
	eTypeIGGGetContactRequest,
	eTypeIGGGetContactResponse,
	eTypeIGGDelContact,
	eTypeIGGAuthBySKRequest,
	eTypeIGGAuthBySKResponse,
	
	//��Ϣ��� Begin 
	eTypeIGGMicroMsgRequest,
	eTypeIGGSendMsgRequest,
	eTypeIGGMicroMsgResponse,
	eTypeIGGSendMsgResponse,
	eTypeIGGKeyVal,
	eTypeIGGSyncKey,
	//��Ϣ��� End
	
	//ͬ����� Begin
	eTypeIGGAddMsg,
	eTypeIGGCmdList,
	eTypeIGGOpCmdResp,
	eTypeIGGOpCmdRespList,
	eTypeIGGNewSyncRequest,
	eTypeIGGNewSyncResponse,
	eTypeIGGSyncRequest,
	eTypeIGGSyncResponse,
	//ͬ����� End
	
	// lbs
	eTypeIGGLbsRequest,
	eTypeIGGLbsContactInfo,
	eTypeIGGLbsResponse,
	eTypeIGGGetLocationRequest,
	eTypeIGGGetLocationResponse,
	eTypeIGGLbsMatchRequest,
	eTypeIGGLbsMatchResponse,
	eTypeIGGSyncLbsMatchRequest,
	eTypeIGGSyncLbsMatchResponse,
	eTypeIGGLbsMatchContactInfo,

	eTypeIGGBatchGetHeadImgRequest,
	eTypeIGGImgPair,
	eTypeIGGBatchGetHeadImgResponse,
	eTypeIGGUploadHDHeadImgRequest,
	eTypeIGGUploadHDHeadImgResponse,
	eTypeIGGGetHDHeadImgRequest,
	eTypeIGGGetHDHeadImgResponse,
	eTypeIGGUploadVoiceRequest,
	eTypeIGGUploadVoiceResponse,
	eTypeIGGDownloadVoiceRequest,
	eTypeIGGDownloadVoiceResponse,

	eTypeIGGUploadVideoRequest,
	eTypeIGGUploadVideoResponse,
	eTypeIGGDownloadVideoRequest,
	eTypeIGGDownloadVideoResponse,
	eTypeIGGUploadMsgImgRequest,
	eTypeIGGUploadMsgImgResponse,
	eTypeIGGDownloadMsgImgRequest,
	eTypeIGGDownloadMsgImgResponse,

	eTypeIGGEmojiUploadInfoReq,
	eTypeIGGUploadEmojiRequest,
	eTypeIGGEmojiUploadInfoResp,
	eTypeIGGUploadEmojiResponse,
	eTypeIGGEmojiDownloadInfoReq,
	eTypeIGGDownloadEmojiRequest,
	eTypeIGGEmojiDownloadInfoResp,
	eTypeIGGDownloadEmojiResponse,

	//Ⱥ���begin
	eTypeIGGModChatRoomNotify,
	eTypeIGGModChatRoomMember,
	eTypeIGGQuitChatRoom,	
	eTypeIGGQuitChatRoomRequest,
	eTypeIGGQuitChatRoomResponse,
	eTypeIGGSearchChatRoom,	
	eTypeIGGSearchChatRoomRequest,
	eTypeIGGSearchChatRoomResponse,
	eTypeIGGChatRoomResult,
	eTypeIGGModChatRoomTopic,
	eTypeIGGModGroupTopic,
	eTypeIGGModChatRoomMemberDisplayName,
	eTypeIGGModChatRoomMemberFlag,

	eTypeIGGMemberReq,
	eTypeIGGMemberResp,
	eTypeIGGDelMemberReq,
	eTypeIGGDelMemberResp,
	eTypeIGGGroupCardReq,
	eTypeIGGCreateChatRoomRequest,
	eTypeIGGCreateChatRoomResponse,
	eTypeIGGAddChatRoomMemberRequest,	
	eTypeIGGAddChatRoomMemberResponse,
	eTypeIGGDelChatRoomMemberRequest,
	eTypeIGGDelChatRoomMemberResponse,

	eTypeIGGLbsChatRoomRequest,
	eTypeIGGLbsChatRoom,
	eTypeIGGLbsChatRoomResponse,
	eTypeIGGVerifyChatRoomMemberRequest,
	eTypeIGGVerifyChatRoomMemberResponse,
	eTypeIGGInviteChatRoomMemberRequest,
	eTypeIGGInviteChatRoomMemberResponse,
	eTypeIGGCloseChatRoomRequest,
	eTypeIGGCloseChatRoomResponse,
	//Ⱥ���end

	//���������begin
	eTypeIGGCreateGroupRequest,
	eTypeIGGCreateGroupResponse,
	eTypeIGGAddGroupMemberRequest,	
	eTypeIGGAddGroupMemberResponse,
	eTypeIGGDelGroupMemberRequest,
	eTypeIGGDelGroupMemberResponse,
	eTypeIGGQuitGroupRequest,
	eTypeIGGQuitGroupResponse,
	//���������end

	//GetProfile���begin
	eTypeIGGDisturbTimeSpan,
	eTypeIGGDisturbSetting,
	eTypeIGGGmailInfo,
	eTypeIGGGmailList,
	eTypeIGGFacebookInfo,
	eTypeIGGSafeDevice,
	eTypeIGGSafeDeviceList,
	eTypeIGGUserInfoExt,
	eTypeIGGModUserInfo,
	eTypeIGGGetProfileRequest,
	eTypeIGGGetProfileResponse,
	eTypeIGGUploadCoverImgRequest,
	eTypeIGGUploadCoverImgResponse,
	eTypeIGGGetCoverImgRequest,
	eTypeIGGGetCoverImgResponse,
	eTypeIGGHobby,
	eTypeIGGBirthday,
	//GetProfile���end

	//newsync���-- add by yihuang
	eTypeIGGFunctionSwitch,
	//
	//�ֻ���
	eTypeIGGMobileOptRequest,
	eTypeIGGMobileOptResponse,
	//�����
	eTypeIGGEmailOptRequest,
	eTypeIGGEmailOptResponse,
	//��������ϵ���ϴ�
	eTypeIGGUploadPlugFriendsRequest,
	eTypeIGGUploadPlugFriendsResponse,

	//�����������(Iphone token reg/unreg/sound open/close)
	eTypeIGGPushSettingRequest,
	eTypeIGGPushSettingResponse,

	//�û��޸��û���
	eTypeIGGModUserNameRequest,
	eTypeIGGModUserNameResponse,

	//�û��޸�����
	eTypeIGGModPwdRequest,
	eTypeIGGModPwdResponse,

	//�û�ͨ���ֻ��һ�����
	eTypeIGGModPwdByMobileRequest,
	eTypeIGGModPwdByMobileResponse,
	//������IP��Ϣ
	eTypeIGGWebProxyInfo,
	//add here 1

	//�ٱ�
	eTypeIGGReportProfileRequest,
	eTypeIGGReportProfileResponse,
	eTypeIGGReportGroupRequest,
	eTypeIGGReportGroupResponse,
};

enum {
	eFuncIGGMicroMsgSKGetSelfSvnInfo = IGG_FUNC_DEFINE,
	eFuncIGGMicroMsgSKGetMetainfoFull,
	eFuncIGGMicroMsgSKGetMetainfo,
	eFuncIGGMicroMsgSKEcho
};

#pragma pack(1)

#if 1

typedef struct tagIGGMicroMsgEchoInfo {
	unsigned int iEchoLen;
	char * pcEchoStr;
} IGGMicroMsgEchoInfo_t;

//////////////////////// ����/////////////////////////////////////

typedef struct tagIGGHobby {
    unsigned int iArtFlag; //Art����Ȥ���ñ�־λ�ĺϼ�����־λ������enMMArtFlag
    unsigned int iSportsFlag; //Sports����Ȥ���ñ�־λ�ĺϼ�����־λ������enMMSportsFlag
    unsigned int iSocialActivitiesFlag; //SocialActivities����Ȥ���ñ�־λ�ĺϼ�����־λ������enMMSocialActivitiesFlag
    unsigned int iTechnologyFlag; //Technology����Ȥ���ñ�־λ�ĺϼ�����־λ������enMMTechnologyFlag
    unsigned int iLifestyleFlag; //Lifestyle����Ȥ���ñ�־λ�ĺϼ�����־λ������enMMLifestyleFlag
} IGGHobby_t;

typedef struct tagIGGBirthday {
	unsigned int iYear;
	unsigned int iMonth;
	unsigned int iDay;
} IGGBirthday_t;


//////////////////////// ע�� & ��¼ ////////////////////////////

typedef struct tagIGGBaseRequest {
	char sSessionKey[36];				//SESSION KEY
	unsigned int iUin;					//UIN
	unsigned char cDeviceID[16];		//�豸ID
	int iClientVersion;					//�ͻ��˰汾��
	char sDeviceType[132];				//�豸����
	unsigned int iScene;				//������ʶ�����ο�enSceneStatus�궨�壩
	unsigned int iSeq;
} IGGBaseRequest_t;

typedef struct tagIGGBuiltinIP {
	unsigned int iType;
	unsigned int iPort;
	char sIP[128];
} IGGBuiltinIP_t;

typedef struct tagIGGBuiltinIPList {
	unsigned int iLongConnectIPCount;
	unsigned int iShortConnectIPCount;
	unsigned int iSeq;
	IGGBuiltinIP_t * ptLongConnectIPList;

	IGGBuiltinIP_t * ptShortConnectIPList;
} IGGBuiltinIPList_t;

typedef struct tagIGGCDNDnsInfo {
	unsigned int iVer;
	unsigned int iUin;
	unsigned int iExpireTime;
	int iFrontID;
	int iFrontIPCount;
	Comm::SKBuiltinString_t * ptFrontIPList;

	char * pcZoneDomain;

	Comm::SKBuiltinBuffer_t tAuthKey;
	int iZoneID;
	int iZoneIPCount;
	Comm::SKBuiltinString_t * ptZoneIPList;
} IGGCDNDnsInfo_t;

typedef struct tagIGGWebProxyInfo {
	int iIPCount;
	Comm::SKBuiltinString_t * ptIPList;
} IGGWebProxyInfo_t;

typedef struct tagIGGAuthRequest {
	IGGBaseRequest_t tBaseRequest;
	Comm::SKBuiltinString_t tAccount;		//�˺�
	Comm::SKBuiltinString_t tPwd;			//���루��ҪMD5���������FB�û�����дTOKEN������ҪMD5��
	char * pcTimeZone;						//ʱ��
	char * pcLanguage;						//�豸����
	char * pcAuthTicket;						
	char * pcRealCountry;						//����
	Comm::SKBuiltinString_t tRandomEncryKey;	//�ͻ��˲��������������Կ
} IGGAuthRequest_t;

typedef struct tagIGGRegRequest {
	IGGBaseRequest_t tBaseRequest;
	Comm::SKBuiltinString_t tAccount;	//�˺�
	Comm::SKBuiltinString_t tPwd;		//���루��ҪMD5��
	Comm::SKBuiltinString_t tTicket;
	char * pcTimeZone;				//ʱ��
	char * pcLanguage;				//�豸����
	char * pcCountry;					//����
	Comm::SKBuiltinString_t tRandomEncryKey;	//�ͻ��˲��������������Կ
} IGGRegRequest_t;

typedef struct tagIGGBaseResponse {
	int iRet;
	Comm::SKBuiltinString_t tErrMsg;
	unsigned int iSeq;
} IGGBaseResponse_t;

typedef struct tagIGGNetworkControl {
	char * pcPortList;

	char * pcTimeoutList;
} IGGNetworkControl_t;

typedef struct tagIGGPluginKey {
	char * pcKey;

	unsigned int iId;
} IGGPluginKey_t;

typedef struct tagIGGPluginKeyList {
	unsigned int iCount;
	IGGPluginKey_t * ptList;
} IGGPluginKeyList_t;

typedef struct tagIGGHost {
	char * pcOrigin;

	char * pcSubstitute;
} IGGHost_t;

typedef struct tagIGGHostList {
	unsigned int iCount;
	IGGHost_t * ptList;
} IGGHostList_t;

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
} IGGAuthResponse_t;

typedef struct tagIGGRegResponse {
	IGGBaseResponse_t tBaseResponse;
	unsigned int iUin;							//UIN
	char sSessionKey[36];						//SESSION KEY
	char * pcUserName;						//UserName
} IGGRegResponse_t;


//////////////////////////////////////////////////////////////////////////////
typedef struct tagIGGModUserNameRequest {
	IGGBaseRequest_t tBaseRequest;
	char * pcUserName;
} IGGModUserNameRequest_t;

typedef struct tagIGGModUserNameResponse{
	IGGBaseResponse_t tBaseResponse;
} IGGModUserNameResponse_t;

typedef struct tagIGGModPwdRequest {
	IGGBaseRequest_t tBaseRequest;
	char * pcOldPwd;
	char * pcNewPwd;
} IGGModPwdRequest_t;

typedef struct tagIGGModPwdResponse{
	IGGBaseResponse_t tBaseResponse;
} IGGModPwdResponse_t;

typedef struct tagIGGModPwdByMobileRequest {
	IGGBaseRequest_t tBaseRequest;
	char * pcMobile;
	char * pcTicket;
	char * pcNewPwd;
	Comm::SKBuiltinString_t tRandomEncryKey;//�ͻ��˲��������������Կ
} IGGModPwdByMobileRequest_t;

typedef struct tagIGGModPwdByMobileResponse{
	IGGBaseResponse_t tBaseResponse;
} IGGModPwdByMobileResponse_t;

typedef struct tagIGGMobileOptRequest {
	IGGBaseRequest_t tBaseRequest;
	char * pcCountryCode;
	char * pcMobile;
	int iOptCode;
	char * pcVerifycode;
	Comm::SKBuiltinString_t tRandomEncryKey;//�ͻ��˲��������������Կ
} IGGMobileOptRequest_t;

typedef struct tagIGGMobileOptResponse {
	IGGBaseResponse_t tBaseResponse;
	int iOptCode;
	char * pcTicket;
} IGGMobileOptResponse_t;

typedef struct tagIGGEmailOptRequest {
	IGGBaseRequest_t tBaseRequest;
	char * pcEmail;
	int iOptCode;
	char * pcVerifyCode;
	Comm::SKBuiltinString_t tRandomEncryKey;//�ͻ��˲��������������Կ
} IGGEmailOptRequest_t;

typedef struct tagIGGEmailOptResponse {
	IGGBaseResponse_t tBaseResponse;
	int iOptCode;
} IGGEmailOptResponse_t;

typedef struct tagIGGUploadPlugFriendsRequest {
	IGGBaseRequest_t tBaseRequest;
	unsigned int iOptCode;						
	unsigned int iFriendType;
	unsigned int iFriendCount;
	Comm::SKBuiltinString_t * pcFriendBuffer;
} IGGUploadPlugFriendsRequest_t;

typedef struct tagIGGUploadPlugFriendsResponse {
	IGGBaseResponse_t tBaseResponse;
} IGGUploadPlugFriendsResponse_t;

typedef struct tagIGGPushSettingRequest {
	IGGBaseRequest_t tBaseRequest;
	unsigned int iOptCode;						//�ο�enIGGPushSetOptö�ٶ���
	char * pcToken;							//Token
	char * pcSound;							//��Ϊ��
	unsigned int iStatus;						//��0
	char * pcVoipSound;						//��Ϊ��
} IGGPushSettingRequest_t;

typedef struct tagIGGPushSettingResponse {
	IGGBaseResponse_t tBaseResponse;
} IGGPushSettingResponse_t;
//////////////////////////////////////////////////////////////////////////////


/////////////////////// ��ʼ������ϵ���б�/������Ϣ�ȵȣ� /////////////////////////////

typedef struct tagIGGCmdItem {
	int iCmdId;
	Comm::SKBuiltinBuffer_t tCmdBuf;
} IGGCmdItem_t;

typedef struct tagIGGNewInitRequest {
	IGGBaseRequest_t tBaseRequest;
	char * pcUserName;	//����

	Comm::SKBuiltinBuffer_t tCurrentSynckey;	//��ǰkeyֵ�� �����һ�θ���ʱΪ0��֮�����˷�����Ӧֵ
	Comm::SKBuiltinBuffer_t tMaxSynckey;		//���keyֵ�� �����һ�θ���ʱΪ0��֮�����˷�����Ӧֵ
	char * pcLanguage;							//�������ͣ����������˷��ص���������
} IGGNewInitRequest_t;

typedef struct tagIGGNewInitResponse {
	IGGBaseResponse_t tBaseResponse;
	Comm::SKBuiltinBuffer_t tCurrentSynckey;
	Comm::SKBuiltinBuffer_t tMaxSynckey;
	unsigned int iContinueFlag;			// �Ƿ����ͬ����0��ʾ���ã�����ֵ����Ҫ��iContinueFlag | MM_SYNC_CONTINUE = 1��ʾcontact��Ҫͬ��
	unsigned int iSelectBitmap;			// ���µ���Ŀ��λ���� iSelectBitmap = ��(1<<6) - 1��^ (1 << (eMMSeqMsg-1)) ^ (1 << ( eMMSeqWXContact - 1 )) ^ (1 << ( eMMSeqProfile - 1 ))
	unsigned int iCmdCount;
	IGGCmdItem_t * ptCmdList;			

	unsigned int iRatio;				// ͬ�����ʣ� ����maxkey=10, curKey=5, �����Ϊ50.  ��cli_cur_key * 100 / cli_max_key;��
} IGGNewInitResponse_t;

typedef struct tagIGGKeyVal {
	unsigned int iKey;				// ���� 1:userProfile 2:msg 3:contact ��ʱֻ��3
	unsigned int iVal;				// ֵ
} IGGKeyVal_t;

typedef struct tagIGGSyncKey {
	unsigned int iKeyCount;
	IGGKeyVal_t * ptKey;
} IGGSyncKey_t;

///////////////////////// ������ϵ�� //////////////////////////

typedef struct tagIGGSnsUserInfo {
	unsigned int iSnsFlag;
	char * pcSnsBGImgID;

	unsigned long long llSnsBGObjectID;
	unsigned int iSnsFlagEx;
} IGGSnsUserInfo_t;

typedef struct tagIGGCustomizedInfo {
	unsigned int iBrandFlag;
	char * pcExternalInfo;

	char * pcBrandInfo;

	char * pcBrandIconURL;
} IGGCustomizedInfo_t;

typedef struct tagIGGSearchContactRequest {
	IGGBaseRequest_t tBaseRequest;
	Comm::SKBuiltinString_t tUserName;	// �û���������
} IGGSearchContactRequest_t;

typedef struct tagIGGSearchContactItem {
	Comm::SKBuiltinString_t tUserName;
	Comm::SKBuiltinString_t tNickName;
	Comm::SKBuiltinString_t tPYInitial;
	Comm::SKBuiltinString_t tQuanPin;
	int iSex;
	Comm::SKBuiltinBuffer_t tImgBuf;
	char * pcProvince;

	char * pcCity;

	char * pcSignature;

	unsigned int iPersonalCard;
	unsigned int iVerifyFlag;
	char * pcVerifyInfo;
	int  iNeedVerify;	// �Ƿ���Ҫ��֤  0:����Ҫ  1:��Ҫ

	char * pcWeibo;

	char * pcAlias;

	char * pcWeiboNickname;

	unsigned int iWeiboFlag;
	int iAlbumStyle;
	int iAlbumFlag;
	char * pcAlbumBGImgID;

	IGGSnsUserInfo_t tSnsUserInfo;
	char * pcCountry;

	char * pcMyBrandList;

	IGGCustomizedInfo_t tCustomizedInfo;
	char * pcBigHeadImgUrl;

	char * pcSmallHeadImgUrl;

	Comm::SKBuiltinString_t tSafeUserName;
} IGGSearchContactItem_t;

typedef struct tagIGGSearchContactResponse {
	IGGBaseResponse_t tBaseResponse;
	Comm::SKBuiltinString_t tUserName;	// �������ĵ�һ���û��� ���������Խ�Ϊ��һ���û����ԣ���IGGSearchContactItem_t�⣩
	Comm::SKBuiltinString_t tNickName;
	Comm::SKBuiltinString_t tPYInitial;
	Comm::SKBuiltinString_t tQuanPin;
	int iSex;
	Comm::SKBuiltinBuffer_t tImgBuf;
	char * pcProvince;

	char * pcCity;

	char * pcSignature;

	unsigned int iPersonalCard;
	unsigned int iVerifyFlag;
	char * pcVerifyInfo;
	int  iNeedVerify;	// �Ƿ���Ҫ��֤  0:����Ҫ  1:��Ҫ

	char * pcWeibo;

	char * pcAlias;

	char * pcWeiboNickname;

	unsigned int iWeiboFlag;
	int iAlbumStyle;
	int iAlbumFlag;
	char * pcAlbumBGImgID;

	IGGSnsUserInfo_t tSnsUserInfo;
	char * pcCountry;

	char * pcMyBrandList;

	IGGCustomizedInfo_t tCustomizedInfo;
	unsigned int iContactCount;
	IGGSearchContactItem_t * ptContactList;		// �����������û�����1ʱ�����б����ֵ��

	char * pcBigHeadImgUrl;

	char * pcSmallHeadImgUrl;

	Comm::SKBuiltinString_t tSafeUserName;
} IGGSearchContactResponse_t;

///////////////////////// ������֤ ///////////////////////////

typedef struct tagIGGVerifyUser {
	char * pcValue;

	char * pcVerifyUserTicket;
} IGGVerifyUser_t;

typedef struct tagIGGVerifyUserRequest {
	IGGBaseRequest_t tBaseRequest;
	unsigned int iOpcode;
	unsigned int iVerifyUserListSize;
	IGGVerifyUser_t * ptVerifyUserList;

	char * pcVerifyContent;

	unsigned int iSceneListCount;
	unsigned int * piSceneList;
} IGGVerifyUserRequest_t;

typedef struct tagIGGVerifyUserResponse {
	IGGBaseResponse_t tBaseResponse;
	unsigned int iOpcode;	//�ͻ����Ϸ���iOpcode
	char*  pcUserName;		//�������ptVerifyUserList�ĵ�һ���û�����
} IGGVerifyUserResponse_t;

///////////////////////// ɾ������ ///////////////////////////

typedef struct tagIGGDelContact {
	Comm::SKBuiltinString_t tUserName; 
} IGGDelContact_t;

////////////////////////// ����ͬ�� /////////////////////////

typedef struct tagIGGSyncFriendRequest {
	IGGBaseRequest_t tBaseRequest;
	Comm::SKBuiltinString_t tUserName;
	unsigned int iSyncKey;
	int iScene;
} IGGSyncFriendRequest_t;

typedef struct tagIGGSyncFriendResponse {
	IGGBaseResponse_t tBaseResponse;
	unsigned int iNewSyncKey;
	int iContinueFlag; // ͬ�����Ϊ�� | MM_NEWSYNC_FRIENDΪ1��ʾ��Ҫ����ͬ��
	unsigned int iCmdCount;
	IGGCmdItem_t * ptCmdList;
} IGGSyncFriendResponse_t;

// IGGSyncFriendResponse_t��ptCmdList����ת�ɸø�ʽ
typedef struct tagIGGPossibleFriend {
	char * pcUserName;
	char * pcNickName;
	char * pcPYInitial;
	char * pcQuanPin;
	int iSex;
	unsigned int iImgFlag;
	unsigned int iContactType;
	char * pcDomainList;
	char * pcSource;
	unsigned int iFriendScene;
	char * pcThirdID;
	int iNeedVerify; // �Ƿ���Ҫ��֤
	char* pcFBUserName;
} IGGPossibleFriend_t;

////////////////////////// ��ȡ��ϵ����ϸ��Ϣ //////////////////////////
typedef struct tagIGGRoomInfo {
	Comm::SKBuiltinString_t tUserName;
	Comm::SKBuiltinString_t tNickName;
} IGGRoomInfo_t;

typedef struct tagIGGChatRoomMember
{	
	Comm::SKBuiltinString_t tMemberName;
	Comm::SKBuiltinString_t tMemberSafeName;
	Comm::SKBuiltinString_t tNickName;
	int iSex;
	char * pcSignature;		
	char * pcCountry;
	IGGBirthday_t tBirthday; //����
} IGGChatRoomMember_t;

typedef struct tagIGGModContact {
	Comm::SKBuiltinString_t tUserName;				//�û�����ʹ���û���ͨ��BatchHeadImg��������ȡ����ͷ��
	Comm::SKBuiltinString_t tNickName;				//�ǳ�
	Comm::SKBuiltinString_t tPYInitial;
	Comm::SKBuiltinString_t tQuanPin;
	int iSex;										//�Ա�
	Comm::SKBuiltinBuffer_t tImgBuf;
	unsigned int iBitMask;
	unsigned int iBitVal;
	unsigned int iImgFlag;
	Comm::SKBuiltinString_t tRemark;
	Comm::SKBuiltinString_t tRemarkPYInitial;
	Comm::SKBuiltinString_t tRemarkQuanPin;
	unsigned int iContactType;						//�������ͣ��ο�enIGGContactType�꣬���ڶ���Ĭ��ֵIGG_CONTACT_IGG��
	unsigned int iRoomMemberCount;					// Ⱥ��Ա��
	IGGChatRoomMember_t * ptRoomMemberList;			// Ⱥ��Ա�б�

	Comm::SKBuiltinString_t tDomainList;			
	unsigned int iChatRoomNotify;					
	unsigned int iAddContactScene;					
	char * pcProvince;

	char * pcCity;									//����

	char * pcSignature;

	unsigned int iPersonalCard;
	unsigned int iHasWeiXinHdHeadImg;
	unsigned int iVerifyFlag;						//��֤��־
	char * pcVerifyInfo;

	int iLevel;
	unsigned int iSource;
	char * pcWeibo;

	char * pcVerifyContent;							//

	char * pcAlias;

	char * pcChatRoomOwner;

	char * pcWeiboNickname;

	unsigned int iWeiboFlag;
	int iAlbumStyle;
	int iAlbumFlag;
	char * pcAlbumBGImgID;

	IGGSnsUserInfo_t tSnsUserInfo;					//����Ȧ��ҳ��Ϣ����ʱ���ã�
	char * pcCountry;								//����

	char * pcBigHeadImgUrl;							//��ͷ��CND����ʱ�գ�

	char * pcSmallHeadImgUrl;						//Сͷ��CND����ʱ�գ�

	char * pcMyBrandList;							

	IGGCustomizedInfo_t tCustomizedInfo;			
	char * pcChatRoomData;							

	char * pcHeadImgMd5;							//ͷ���MD5�루ûɶ���壩
	
	Comm::SKBuiltinString_t tSafeUserName;			//SafeUserName
	IGGBirthday_t tBirthday; //����
	unsigned int iAge; //���䣬�������ռ���
	IGGHobby_t tHobby; //��Ȥ����
	unsigned int iIntentionFlag; //������Ը��������enMMIntentionFlag
	unsigned int iMaxMemberCount; // Ⱥ��Ա����
	char * pcMobile;
	unsigned long long llFBUserID;
} IGGModContact_t;

typedef struct tagIGGGetContactRequest {
	IGGBaseRequest_t tBaseRequest;
	unsigned int iUserCount;
	Comm::SKBuiltinString_t * ptUserNameList;
} IGGGetContactRequest_t;

typedef struct tagIGGGetContactResponse {
	IGGBaseResponse_t tBaseResponse;
	unsigned int iContactCount;
	IGGModContact_t * ptContactList;

	int * piRet;
} IGGGetContactResponse_t;

////////////////////////// ����֮���Զ���½ //////////////////////////

typedef struct tagIGGAuthBySKRequest {
	IGGBaseRequest_t tBaseRequest;				//iScene�ֶ� ��дMM_SCENE_REAUTH
} IGGAuthBySKRequest_t;

typedef struct tagIGGAuthBySKResponse {
	IGGBaseResponse_t tBaseResponse;
	unsigned int iUin;							//Uin(�ͻ����õõ����ã��ò������Բ����)
	unsigned int iNewVersion;					//�°汾��Ϣ
	IGGWebProxyInfo_t tWebProxyInfo;            //������IP��Ϣ
} IGGAuthBySKResponse_t;


////////////////////////// ��ȡͷ�� ////////////////////////////
typedef struct tagIGGBatchGetHeadImgRequest {
	IGGBaseRequest_t tBaseRequest;
	unsigned int iCount;						//���������֧��������ȡ��
	Comm::SKBuiltinString_t * ptUserNameList;	//�û����б�
} IGGBatchGetHeadImgRequest_t;

typedef struct tagIGGImgPair {
	Comm::SKBuiltinBuffer_t tImgBuf;			//ͷ��BUFF
	Comm::SKBuiltinString_t tUsername;			//�û���
} IGGImgPair_t;

typedef struct tagIGGBatchGetHeadImgResponse {
	IGGBaseResponse_t tBaseResponse;
	unsigned int iCount;						//ͷ�����
	IGGImgPair_t * ptImgPairList;				//ͷ����Ϣ
} IGGBatchGetHeadImgResponse_t;

//////////////////////////// �޸�ͷ����ʱ��ʹ�ã� //////////////////////////
typedef struct tagIGGModifyHeadImgRequest {
	IGGBaseRequest_t tBaseRequest;
	char * pcUserName;							//�û���
	Comm::SKBuiltinBuffer_t tImgBuf;			//ͷ��BUFF
} IGGModifyHeadImgRequest_t;

typedef struct tagIGGModifyHeadImgResponse {
	IGGBaseResponse_t tBaseResponse;
} IGGModifyHeadImgResponse_t;

///////////////////////////// �ϴ�����ͷ�� ///////////////////////////
typedef struct tagIGGUploadHDHeadImgRequest {
	IGGBaseRequest_t tBaseRequest;
	unsigned int iTotalLen;						//�ܴ�С
	unsigned int iStartPos;						//��ʼλ��
	unsigned int iHeadImgType;					//���ͣ��ο�enIGGHeadImgType�궨�壩
	Comm::SKBuiltinBuffer_t tData;				//BUFF(����+���ݳ���)
	char * pcImgHash;							//IGG_HEADIMG#UserName#time(null)

	char * pcUserName;							//�û���

	char * pcMD5;								//<MD5>
	char * pcCDNImgUrl;							//CND ͷ��URL �ݲ���
	char * pcAESKey;							//CND ��Կ
	int iEncryVer;								//CND ���
	int iCDNImgSize;							//�ϴ���CND��ͷ�����ݴ�С
} IGGUploadHDHeadImgRequest_t;

typedef struct tagIGGUploadHDHeadImgResponse {
	IGGBaseResponse_t tBaseResponse;			
	unsigned int iTotalLen;						//�ܴ�С
	unsigned int iStartPos;						//��һ��������ʼλ��

	char * pcFinalImgMd5sum;					//<MD5>
	char * pcImgHash;							//(Req)
} IGGUploadHDHeadImgResponse_t;

////////////////////////////// ���ظ���ͷ�� /////////////////////////////
typedef struct tagIGGGetHDHeadImgRequest {
	IGGBaseRequest_t tBaseRequest;
	char * pcUserName;							//�û���

	unsigned int iImgWidth;						//�ͻ���ָ�����
	unsigned int iImgHeight;					//�ͻ���ָ���߶�
	char * pcImgFormat;							//�ͻ���ָ����ʽ

	unsigned int iTotalLen;						//�ܴ�С����һ������0��
	unsigned int iStartPos;						//��ʼλ�ã���һ������0��
	unsigned int iHeadImgType;					//���ͣ��ο�enIGGHeadImgType�궨�壩
} IGGGetHDHeadImgRequest_t;

typedef struct tagIGGGetHDHeadImgResponse {
	IGGBaseResponse_t tBaseResponse;
	char * pcUserName;							//�û���

	unsigned int iTotalLen;						//�ܴ�С
	unsigned int iStartPos;						//(Req)
	Comm::SKBuiltinBuffer_t tData;				//BUFF(����+���ݳ���)
} IGGGetHDHeadImgResponse_t;

///////////////////////////// �ϴ����� ///////////////////////////
typedef struct tagIGGUploadVoiceRequest {
	char * pcFromUserName;					//�����û�

	char * pcToUserName;					//Ŀ���û����û������߷�������

	unsigned int iOffset;					//��ʼλ�ã���һ������0��
	unsigned int iLength;					//��ǰBUFF����
	char * pcClientMsgId;					//IGG_VOICE#FromeUserName#ToUser Name#time(NULL)

	unsigned int iMsgId;					//��һ������0�������İ���д���������ص�ID��
	unsigned int iVoiceLength;				//ʱ�䳤��
	Comm::SKBuiltinBuffer_t tData;			//����BUFF
	unsigned int iEndFlag;					//������־��MM_VOICE_UPLOADING|MM_VOICE_UPLOADEND��
	IGGBaseRequest_t tBaseRequest;
	unsigned int iCancelFlag;				//ȡ����־��ȡ������=1������=0��
	char * pcMsgSource;						

	unsigned int iVoiceFormat;				//������ʽ
	unsigned int iUICreateTime;				//ʱ���
	unsigned int iForwardFlag;				//��0
} IGGUploadVoiceRequest_t;

typedef struct tagIGGUploadVoiceResponse {
	char * pcFromUserName;					//��Req��

	char * pcToUserName;					//��Req��

	unsigned int iOffset;					//��һ��������ʼλ��
	unsigned int iLength;					//��Req��
	unsigned int iCreateTime;				//��ʱ����
	char * pcClientMsgId;					//��Req��

	unsigned int iMsgId;					//������������MsgId
	unsigned int iVoiceLength;				//��Req��
	unsigned int iEndFlag;					//��Req��
	IGGBaseResponse_t tBaseResponse;		
	unsigned int iCancelFlag;				//��Req��
} IGGUploadVoiceResponse_t;

//////////////////////// �������� /////////////////////////

typedef struct tagIGGDownloadVoiceRequest {
	unsigned int iMsgId;					//������notify��msgId
	unsigned int iOffset;					//��ʼλ��
	unsigned int iLength;					//���󳤶�
	char * pcClientMsgId;					//������notify��ClientMsgId

	IGGBaseRequest_t tBaseRequest;			
} IGGDownloadVoiceRequest_t;

typedef struct tagIGGDownloadVoiceResponse {
	unsigned int iMsgId;					//��req��
	unsigned int iOffset;					//��req��
	unsigned int iLength;					//ʵ�ʳ���
	unsigned int iVoiceLength;				//���ų���
	char * pcClientMsgId;					//ClientMsgId

	Comm::SKBuiltinBuffer_t tData;			//����BUFF
	unsigned int iEndFlag;					//������־
	IGGBaseResponse_t tBaseResponse;
	unsigned int iCancelFlag;				//ȡ����־
} IGGDownloadVoiceResponse_t;

///////////////////////// �ϴ���Ƶ //////////////////////////
typedef struct tagIGGUploadVideoRequest {
	IGGBaseRequest_t tBaseRequest;
	char * pcClientMsgId;					//IGG_VOICE#FromeUserName#ToUserName#time(NULL)

	char * pcFromUserName;					//�������û���

	char * pcToUserName;					//�������û���

	unsigned int iThumbTotalLen;			//����ͼ�ܴ�С
	unsigned int iThumbStartPos;			//����ͼ������ʼλ��
	Comm::SKBuiltinBuffer_t tThumbData;		//����ͼ���ݣ�����+��С��
	unsigned int iVideoTotalLen;			//��Ƶ�����ܴ�С
	unsigned int iVideoStartPos;			//��Ƶ������ʼλ��
	Comm::SKBuiltinBuffer_t tVideoData;		//��Ƶ���ݣ�����+��С��
	unsigned int iPlayLength;				//��Ƶ���ų���
	unsigned int iNetworkEnv;				//��ʱ�ò���
	unsigned int iCameraType;				//��ʱ�ò���
	unsigned int iFuncFlag;					//��ʱ�ò���
	char * pcMsgSource;						//��ʱ�ò���

	char * pcCDNVideoUrl;					//CDN URL

	char * pcAESKey;						//CDN KEY

	int iEncryVer;							//CDN��ز���
} IGGUploadVideoRequest_t;

typedef struct tagIGGUploadVideoResponse {
	IGGBaseResponse_t tBaseResponse;
	char * pcClientMsgId;					//(Req)

	unsigned int iMsgId;					//���������ɵ�msgId
	unsigned int iThumbStartPos;			//��һ��������ʼλ��
	unsigned int iVideoStartPos;			//��һ��������ʼλ��
} IGGUploadVideoResponse_t;

///////////////////////// ������Ƶ //////////////////////////////////

typedef struct tagIGGDownloadVideoRequest {
	IGGBaseRequest_t tBaseRequest;
	unsigned int iMsgId;
	unsigned int iTotalLen;
	unsigned int iStartPos;
	unsigned int iNetworkEnv;
	unsigned int iMxPackSize;
} IGGDownloadVideoRequest_t;

typedef struct tagIGGDownloadVideoResponse {
	IGGBaseResponse_t tBaseResponse;
	unsigned int iMsgId;
	unsigned int iTotalLen;
	unsigned int iStartPos;
	Comm::SKBuiltinBuffer_t tData;
} IGGDownloadVideoResponse_t;

///////////////////////// �ϴ���ϢͼƬ /////////////////////////////

typedef struct tagIGGUploadMsgImgRequest {
	IGGBaseRequest_t tBaseRequest;
	char * pcClientMsgId;						//IGG_MSGIMG#FromUserName#ToUserName#time(NULL)
	char * pcFromUserName;
	char * pcToUserName;
	unsigned int iTotalLen;						//�ܴ�С
	unsigned int iStartPos;						//��ʼλ��
	unsigned int iDataLen;						//�ò�������0
	Comm::SKBuiltinBuffer_t tData;				//BUFF������+���ݳ��ȣ�
	unsigned int iMsgType;						//��ϢͼƬ������
	char * pcMsgSource;

	unsigned int iCompressType;					//�Ƿ���ԭͼ���ͣ�MM_MSGIMG_WITH_COMPRESS(����ԭͼ)|MM_MSGIMG_WITHOUT_COMPRESS��ԭͼ��
	int iNetType;								//�ݲ���
	int iPhotoFrom;								//�ݲ���
	char * pcMediaId;							//�ݲ���

	char * pcCDNBigImgUrl;						//CDN ԭͼURL ��ʱ��

	char * pcCDNMidImgUrl;						//CND ��ͼURL �ݲ���

	char * pcAESKey;							//CND ��Կ

	int iEncryVer;								//CND ���
	int iCDNBigImgSize;							//�ϴ���CND��ԭͼ���ݴ�С
	int iCDNMidImgSize;							//�ϴ���CND�Ĵ�ͼ���ݴ�С
	char * pcMD5;								//<MD5>
} IGGUploadMsgImgRequest_t;

typedef struct tagIGGUploadMsgImgResponse {
	IGGBaseResponse_t tBaseResponse;
	unsigned int iMsgId;						//MsgId
	char * pcClientMsgId;						//(Req)
	char * pcFromUserName;						//(Req)
	char * pcToUserName;						//(Req)
	unsigned int iTotalLen;						//(Req)
	unsigned int iStartPos;						//��һ��������ʼλ��
	unsigned int iDataLen;						//(Req��
	unsigned int iCreateTime;					//��������֮�������ʱ���
} IGGUploadMsgImgResponse_t;

////////////////////////// ������ϢͼƬ///////////////////////

typedef struct tagIGGDownloadMsgImgRequest {
	IGGBaseRequest_t tBaseRequest;
	unsigned int iMsgId;						//MsgId
	char * pcFromUserName;						
	char * pcToUserName;						
	unsigned int iTotalLen;						//�ܳ��ȣ���һ����Ϊ0��
	unsigned int iStartPos;						//��ʼλ�ã���һ��Ϊ0��
	unsigned int iDataLen;						//�ò�������0
	unsigned int iCompressType;					//�Ƿ��б��������MM_MSGIMG_WITH_COMPRESS|MM_MSGIMG_WITHOUT_COMPRESS
} IGGDownloadMsgImgRequest_t;

typedef struct tagIGGDownloadMsgImgResponse {
	IGGBaseResponse_t tBaseResponse;
	unsigned int iMsgId;						//(Req)
	char * pcFromUserName;						//(Req)
	char * pcToUserName;						//(Req)
	unsigned int iTotalLen;						//�ܴ�С
	unsigned int iStartPos;						//(Req)	
	unsigned int iDataLen;						//(Req)
	Comm::SKBuiltinBuffer_t tData;				//BUFF������+���ݳ��ȣ�
} IGGDownloadMsgImgResponse_t;

////////////////////////////��ͼ���Զ�����飩//////////////////////////////

typedef struct tagIGGEmojiUploadInfoReq {
	char * pcMD5;								//�����MD5��(�ͻ��˼���õ�)

	int iStartPos;								//��ʼλ��
	int iTotalLen;								//�ܴ�С
	Comm::SKBuiltinBuffer_t tEmojiBuffer;		//BUFF������+���ݴ�С��
	int iType;									//�̶���MM_DATA_EMOJI
	char * pcToUserName;						//ToUser

	char * pcExternXML;							//�Ըñ��������

	char * pcReport;							//����

	char * pcClientMsgID;						//IGG_EMOJI#FromUserName#ToUserName#time(null)
} IGGEmojiUploadInfoReq_t;

typedef struct tagIGGUploadEmojiRequest {		
	IGGBaseRequest_t tBaseRequest;
	int iEmojiItemCount;						//��1��֧�ֶ��ļ��ϴ����ͻ�������Ӧ�����ò�����
	IGGEmojiUploadInfoReq_t * ptEmojiItem;		//���������Ϣ
} IGGUploadEmojiRequest_t;

typedef struct tagIGGEmojiUploadInfoResp {
	int iRet;									//RespCode
	int iStartPos;								//��һ��������ʼλ��
	int iTotalLen;								//(Req)
	char * pcMD5;								//(Req)
	char * pcClientMsgID;						//(Req)
	unsigned int iMsgID;						//��������������֮�������MsgId
} IGGEmojiUploadInfoResp_t;

typedef struct tagIGGUploadEmojiResponse {
	IGGBaseResponse_t tBaseResponse;
	int iEmojiItemCount;						//(Req)
	IGGEmojiUploadInfoResp_t * ptEmojiItem;		//������Ϣ
} IGGUploadEmojiResponse_t;

typedef struct tagIGGEmojiDownloadInfoReq {
	char * pcID;								//Content�е�idbuffer�ض�	������Զ���������			

	int iStartPos;								//��ʼλ��(��һ����Ϊ0)
	int iTotalLen;								//�ܴ�С(��һ����Ϊ0)
	char * pcMD5;								//����MD5��(Content���ֶ���) ��ٷ��������
} IGGEmojiDownloadInfoReq_t;

typedef struct tagIGGDownloadEmojiRequest {		//Ҳ���û�����ٷ������
	IGGBaseRequest_t tBaseRequest;
	int iEmojiItemCount;						//�������
	IGGEmojiDownloadInfoReq_t * ptEmojiItem;	//������Ϣ
} IGGDownloadEmojiRequest_t;

typedef struct tagIGGEmojiDownloadInfoResp {
	int iRet;									//RespCode
	int iStartPos;								//(Req)
	int iTotalLen;								//�ܴ�С
	Comm::SKBuiltinBuffer_t tEmojiBuffer;		//BUFF(����+���ݴ�С)
	char * pcMD5;								//(Req)

	char * pcID;								//(Req)
} IGGEmojiDownloadInfoResp_t;

typedef struct tagIGGDownloadEmojiResponse {
	IGGBaseResponse_t tBaseResponse;			
	int iEmojiItemCount;						//(Req)
	IGGEmojiDownloadInfoResp_t * ptEmojiItem;	//������Ϣ
} IGGDownloadEmojiResponse_t;

////////////////////////// ������Ϣ Begin //////////////////////////


typedef struct tagIGGMicroMsgRequest {
	Comm::SKBuiltinString_t tFromUserName;
	Comm::SKBuiltinString_t tToUserName;
	unsigned int iType;
	char * pcContent;

	unsigned int iCreateTime;
	char * pcClientMsgId;

	char * pcMsgSource;

	unsigned int iEmojiFlag;
} IGGMicroMsgRequest_t;


typedef struct tagIGGSendMsgRequest {
	IGGBaseRequest_t tBaseRequest;
	unsigned int iCount;
	IGGMicroMsgRequest_t * ptList;
} IGGSendMsgRequest_t;

typedef struct tagIGGMicroMsgResponse {
	int iRet;
	Comm::SKBuiltinString_t tFromUserName;
	Comm::SKBuiltinString_t tToUserName;
	unsigned int iMsgId;
	char * pcClientMsgId;

	unsigned int iCreateTime;
	unsigned int iType;
} IGGMicroMsgResponse_t;

typedef struct tagIGGSendMsgResponse {
	IGGBaseResponse_t tBaseResponse;
	unsigned int iCount;
	IGGMicroMsgResponse_t * ptList;
} IGGSendMsgResponse_t;


////////////////////////// ������Ϣ End //////////////////////////



////////////////////////// ͬ����Ϣ Begin //////////////////////////

typedef struct tagIGGAddMsg {
	int iMsgId;
	Comm::SKBuiltinString_t tFromUserName;
	Comm::SKBuiltinString_t tToUserName;
	int iMsgType;
	Comm::SKBuiltinString_t tContent;
	unsigned int iStatus;
	unsigned int iImgStatus;
	Comm::SKBuiltinBuffer_t tImgBuf;
	unsigned int iCreateTime;
	char * pcMsgSource;

	char * pcPushContent;
} IGGAddMsg_t;


typedef struct tagIGGCmdList {
	unsigned int iCount;
	IGGCmdItem_t * ptList;
} IGGCmdList_t;

typedef struct tagIGGOpCmdResp {
	int iCmdId;
	int iRet;
} IGGOpCmdResp_t;

typedef struct tagIGGOpCmdRespList {
	unsigned int iCount;
	IGGOpCmdResp_t * ptList;
} IGGOpCmdRespList_t;


#pragma pack(1)
typedef struct tagIGGNewSyncCheckRequest{
	unsigned int iUin;
	unsigned int iSyncKeyLen;
	Comm::SKBuiltinString_t tSyncKeyBuf;
}IGGNewSyncCheckRequest_t;
#pragma pack()


typedef struct tagIGGNewSyncRequest {
	IGGBaseRequest_t tBaseRequest;
	IGGCmdList_t tOplog;
	unsigned int iSelector;
	Comm::SKBuiltinBuffer_t tKeyBuf;
	unsigned int iScene;
} IGGNewSyncRequest_t;

typedef struct tagIGGNewSyncResponse {
	IGGBaseResponse_t tBaseResponse;
	int iRet;
	IGGCmdList_t tCmdList;
	unsigned int iContinueFlag;
	Comm::SKBuiltinBuffer_t tKeyBuf;
	unsigned int iStatus;
	IGGOpCmdRespList_t tOpCmdResp;
} IGGNewSyncResponse_t;


typedef struct tagIGGSyncRequest {
	IGGBaseRequest_t tBaseRequest;
	Comm::SKBuiltinString_t tUserName;
	unsigned int iSyncKey;
	int iScene;
	int iOption;
	IGGCmdList_t tOplog;
	char * pcKeyBuf;
} IGGSyncRequest_t;

typedef struct tagIGGSyncResponse {
	IGGBaseResponse_t tBaseResponse;
	unsigned int iNewSyncKey;
	int iContinueFlag;
	unsigned int iCmdCount;
	IGGCmdItem_t * ptCmdList;

	unsigned int iOOBCount;
	IGGCmdItem_t * ptOOBList;

	char * pcKeyBuf;
} IGGSyncResponse_t;



////////////////////////// ͬ����Ϣ End //////////////////////////

////////////////////////// ��������Begin //////////////////////////

typedef struct tagIGGLbsRequest {
	IGGBaseRequest_t tBaseRequest;
	unsigned int iOpCode;	// �������enLbsOpCode����
	float fLongitude; 		// ���� GPS����,��ȷ��С�����6λ
	float fLatitude; 		// ���� GPSγ��,��ȷ��С�����6λ
	int iPrecision;			// ��ʱ��100
	char * pcMacAddr;		// wifi�ȵ��mac��ַ���ݿ�

	char * pcCellId;		// ��վ��Ϣ���ݿ�

	int iGPSSource;			// GPS��ԴHARDWARE = 0(ʹ��GPS);  NETWORK = 1(��ʹ��GPS)

	//add by yihuang
	unsigned int iBeginAge; //��������С����
	unsigned int iEndAge;	//�������������
	unsigned int iIntentionFlag; //��������
	unsigned int iSkipCount; //�ӵڼ�����¼��ʼ����
	unsigned int iFetchCount; //Ҫ����������
	//
} IGGLbsRequest_t;

typedef struct tagIGGLbsContactInfo {
	char * pcUserName;

	char * pcNickName;

	char * pcProvince;

	char * pcCity;

	char * pcSignature;	// ����ǩ��

	char * pcDistance;	// ����

	int iSex;
	unsigned int iImgStatus;		// �Ƿ���ͷ����:3    û��:4 ����enMMContactImgFlag
	unsigned int iVerifyFlag;		// ��֤��־ �ݲ���
	char * pcVerifyInfo;			// �ݲ���

	char * pcVerifyContent;			// �ݲ���

	char * pcAlias;					// �ݲ���

	char * pcWeibo;					// �ݲ���

	char * pcWeiboNickname;			// �ݲ���

	unsigned int iWeiboFlag;		// �ݲ���
	int iHeadImgVersion;			// �ݲ���
	IGGSnsUserInfo_t tSnsUserInfo;	//(�ݲ���) ����Ȧ��Ϣ
	char * pcCountry;

	char * pcBigHeadImgUrl;			// ��ͷ��URL �ݲ���

	char * pcSmallHeadImgUrl;		// Сͷ��URL �ݲ���

	char * pcMyBrandList;			// �ݲ���

	IGGCustomizedInfo_t tCustomizedInfo;

	//add by yihuang
	IGGHobby_t tMutualHobbies;		//��ͬ��Ȥ
	
	unsigned int iMutualFriendCount;			//��ͬ������
	struct tagIGGLbsContactInfo * ptMutualFriendList;	//��ͬ����

	unsigned int iMutualGroupCount;				//��ͬȺ��
	struct tagIGGLbsContactInfo * ptMutualGroupList;	//��ͬȺ

	char * pcTime;	//ʱ��
	//

	char * pcSafeUserName;
	IGGBirthday_t tBirthday; //����
	unsigned int iAge; 		 //���䣬�������ռ���
	unsigned int iIntentionFlag; //������Ը��������enMMIntentionFlag
	unsigned int iMatchType; // �Ƿ���ʾ��
	
} IGGLbsContactInfo_t;

typedef struct tagIGGLbsResponse {
	IGGBaseResponse_t tBaseResponse;
	unsigned int iContactCount;
	IGGLbsContactInfo_t * ptContactList;

	unsigned int iState;
	unsigned int iFlushTime;		// ˢ��ʱ��
	unsigned int iIsShowRoom;		// �ݲ���
	unsigned int iRoomMemberCount;	// �ݲ���
	unsigned int iSkipCount; //�ӵڼ�����¼��ʼ����
} IGGLbsResponse_t;

typedef struct tagIGGGetLocationRequest {
	IGGBaseRequest_t tBaseRequest;
	int iLongitude;
	int iLatitude;
	int iPrecision;
	char * pcMacAddr;

	char * pcCellId;

	int iGPSSource;
} IGGGetLocationRequest_t;

typedef struct tagIGGGetLocationResponse {
	IGGBaseResponse_t tBaseResponse;
	int iLongitude;
	int iLatitude;
} IGGGetLocationResponse_t;


typedef struct tagIGGLbsMatchRequest {
	IGGBaseRequest_t tBaseRequest;
	unsigned int iOpCode;	// �������enLbsMatchOpCode����
	unsigned int iMatchListSize;// ����
	Comm::SKBuiltinString_t* pUserNameList; // ��Ҫ��Ե��û��б�(����)
} IGGLbsMatchRequest_t;

typedef struct tagIGGLbsMatchResponse {
	IGGBaseResponse_t tBaseResponse;
	unsigned int iOpCode;
	unsigned int iMatchListSize;
	Comm::SKBuiltinString_t* pUserNameList;
	int * piRet;
} IGGLbsMatchResponse_t;


typedef struct tagIGGSyncLbsMatchRequest {
	IGGBaseRequest_t tBaseRequest;
	Comm::SKBuiltinString_t tUserName;
	unsigned int iSyncKey;
} IGGSyncLbsMatchRequest_t;

typedef struct tagIGGSyncLbsMatchResponse {
	IGGBaseResponse_t tBaseResponse;
	unsigned int iNewSyncKey;
	int iContinueFlag; // ͬ�����Ϊ
	unsigned int iCmdCount;
	IGGCmdItem_t * ptCmdList;
} IGGSyncLbsMatchResponse_t;

typedef struct tagIGGLbsMatchContactInfo {
	char * pcUserName;

	char * pcNickName;

	char * pcProvince;

	char * pcCity;

	char * pcSignature;	// ����ǩ��

	int iSex;
	unsigned int iImgStatus;		// �Ƿ���ͷ����:3    û��:4 ����enMMContactImgFlag
	int iHeadImgVersion;			// �ݲ���
	IGGSnsUserInfo_t tSnsUserInfo;	//(�ݲ���) ����Ȧ��Ϣ
	char * pcCountry;

	char * pcBigHeadImgUrl;			// ��ͷ��URL �ݲ���

	char * pcSmallHeadImgUrl;		// Сͷ��URL �ݲ���
	
	char * pcSafeUserName;

	IGGBirthday_t tBirthday; //����
	unsigned int iAge; 		 //���䣬�������ռ���
	unsigned int iIntentionFlag; //������Ը��������enMMIntentionFlag
	unsigned int iMatchTime;	// ���ʱ��
	IGGHobby_t tHobbies;		//��Ȥ

} IGGLbsMatchContactInfo_t;


////////////////////////// ��������End //////////////////////////


/////////////////////////Ⱥ���Begin ////////////////////////////

typedef struct tagIGGModChatRoomNotify 
{	
	unsigned int iChatRoomId;
	unsigned int iStatus;
} IGGModChatRoomNotify_t;

typedef struct tagIGGModChatRoomMember
{	
	Comm::SKBuiltinString_t tUserName;
	Comm::SKBuiltinString_t tNickName;
	Comm::SKBuiltinString_t tPYInitial;
	Comm::SKBuiltinString_t tQuanPin;	
	int iSex;	
	Comm::SKBuiltinBuffer_t tImgBuf;
	unsigned int iImgFlag;	
	Comm::SKBuiltinString_t tRemark;
	Comm::SKBuiltinString_t tRemarkPYInitial;
	Comm::SKBuiltinString_t tRemarkQuanPin;	
	unsigned int iContactType;	
	char * pcProvince;	
	char * pcCity;	
	char * pcSignature;
	unsigned int iPersonalCard;
	unsigned int iVerifyFlag;
	char * pcVerifyInfo;	
	char * pcWeibo;	
	char * pcVerifyContent;
	char * pcWeiboNickname;
	unsigned int iWeiboFlag;
	int iAlbumStyle;	
	int iAlbumFlag;	
	char * pcAlbumBGImgID;
	char * pcAlias;
	IGGSnsUserInfo_t tSnsUserInfo;
	char * pcCountry;	
	char * pcBigHeadImgUrl;	
	char * pcSmallHeadImgUrl;	
	char * pcMyBrandList;	
	IGGCustomizedInfo_t tCustomizedInfo;
} IGGModChatRoomMember_t;


//��Ⱥ
typedef struct tagIGGQuitChatRoom 
{	
	unsigned int iChatRoomId;
	Comm::SKBuiltinString_t tUserName;
} IGGQuitChatRoom_t;

typedef struct tagIGGQuitChatRoomRequest
{	
	IGGBaseRequest_t tBaseRequest;
	IGGQuitChatRoom_t tQuitChatRoom;
}IGGQuitChatRoomRequest_t;

typedef struct tagIGGQuitChatRoomResponse
{	
	IGGBaseResponse_t tBaseResponse;
	IGGQuitChatRoom_t tQuitChatRoom;
}IGGQuitChatRoomResponse_t;

typedef struct tagIGGQuitGroupRequest
{	
	IGGBaseRequest_t tBaseRequest;
	IGGQuitChatRoom_t tQuitChatRoom;
}IGGQuitGroupRequest_t;

typedef struct tagIGGQuitGroupResponse
{	
	IGGBaseResponse_t tBaseResponse;
	IGGQuitChatRoom_t tQuitChatRoom;
}IGGQuitGroupResponse_t;



typedef struct tagIGGModChatRoomTopic 
{	
	unsigned int iChatRoomId;
	unsigned int iChatRoomType;
	Comm::SKBuiltinString_t tChatRoomName;
	Comm::SKBuiltinString_t tChatRoomTopic;
	unsigned int iNeedVerify;
} IGGModChatRoomTopic_t;

typedef struct tagIGGModGroupTopic 
{	
	unsigned int iChatRoomId;
	Comm::SKBuiltinString_t tChatRoomTopic;
} IGGModGroupTopic_t;



typedef struct tagIGGModChatRoomMemberDisplayName 
{	
	unsigned int iChatRoomId;
	char * pcUserName;	
	char * pcDisplayName;
} IGGModChatRoomMemberDisplayName_t;


typedef struct tagIGGModChatRoomMemberFlag
{	
	unsigned int iChatRoomId;	
	char * pcUserName;	
	unsigned int iFlagSwitch;	
	unsigned int iValue;
} IGGModChatRoomMemberFlag_t;



typedef struct tagIGGMemberReq 
{	
	Comm::SKBuiltinString_t tMemberName;
} IGGMemberReq_t;


typedef struct tagIGGMemberResp 
{	
	Comm::SKBuiltinString_t tMemberName;
	unsigned int iMemberStatus;	
	Comm::SKBuiltinString_t tNickName;
	Comm::SKBuiltinString_t tPYInitial;	
	Comm::SKBuiltinString_t tQuanPin;	
	int iSex;	
	Comm::SKBuiltinString_t tRemark;
	Comm::SKBuiltinString_t tRemarkPYInitial;
	Comm::SKBuiltinString_t tRemarkQuanPin;	
	unsigned int iContactType;	
	char * pcProvince;	
	char * pcCity;	
	char * pcSignature;	
	unsigned int iPersonalCard;	
	unsigned int iVerifyFlag;
	char * pcVerifyInfo;	
	char * pcCountry;
	Comm::SKBuiltinString_t tMemberSafeName;
	IGGBirthday_t tBirthday; //����
} IGGMemberResp_t;



typedef struct tagIGGDelMemberReq 
{	
	Comm::SKBuiltinString_t tMemberName;
} IGGDelMemberReq_t;


typedef struct tagIGGDelMemberResp 
{	
	Comm::SKBuiltinString_t tMemberName;
} IGGDelMemberResp_t;



 typedef struct tagIGGCreateChatRoomRequest
{	
	IGGBaseRequest_t tBaseRequest;
	Comm::SKBuiltinString_t tIntroDuce;
	unsigned int iMemberCount;	
	IGGMemberReq_t * ptMemberList;
	float fLongitude;
	float fLatitude;
	Comm::SKBuiltinString_t tChatRoomName;
	unsigned int iType;
	unsigned int iNeedVerify;
	
} IGGCreateChatRoomRequest_t;


typedef struct tagIGGCreateChatRoomResponse
{	
	IGGBaseResponse_t tBaseResponse;	
	Comm::SKBuiltinString_t tIntroDuce;
	Comm::SKBuiltinString_t tPYInitial;	
	Comm::SKBuiltinString_t tQuanPin;	
	unsigned int iMemberCount;	
	IGGMemberResp_t * ptMemberList;	
	Comm::SKBuiltinString_t tChatRoomName;
	Comm::SKBuiltinBuffer_t tImgBuf;	
	char * pcBigHeadImgUrl;	
	char * pcSmallHeadImgUrl;
	unsigned int iRoomId;
	unsigned int iType;
	unsigned int iNeedVerify;
	unsigned int iMaxMemberCount;
} IGGCreateChatRoomResponse_t;


typedef struct tagIGGCreateGroupRequest
{	
	IGGBaseRequest_t tBaseRequest;
	Comm::SKBuiltinString_t tIntroDuce;
	unsigned int iMemberCount;	
	IGGMemberReq_t * ptMemberList;
	
} IGGCreateGroupRequest_t;


typedef struct tagIGGCreateGroupResponse
{	
	IGGBaseResponse_t tBaseResponse;	
	Comm::SKBuiltinString_t tIntroDuce;
	Comm::SKBuiltinString_t tPYInitial;	
	Comm::SKBuiltinString_t tQuanPin;	
	unsigned int iMemberCount;	
	IGGMemberResp_t * ptMemberList;	
	unsigned int iChatRoomId;
	Comm::SKBuiltinBuffer_t tImgBuf;	
	char * pcBigHeadImgUrl;	
	char * pcSmallHeadImgUrl;
	unsigned int iMaxMemberCount;
} IGGCreateGroupResponse_t;


typedef struct tagIGGSearchChatRoomRequest
{	
	IGGBaseRequest_t tBaseRequest;
	unsigned int iSearchType;	
	unsigned int iChatRoomId;
	float fLongitude; 		// ���� GPS����,��ȷ��С�����6λ
	float fLatitude; 		// ���� GPSγ��,��ȷ��С�����6λ
}IGGSearchChatRoomRequest_t;

typedef struct tagIGGChatRoomResult
{	
	unsigned int iRoomID;
	char* sChatRoomName;
	char* sIntroduce;	
	unsigned int iCreateTime;
	unsigned int iActiveTime;
	unsigned int iStatus;	
	unsigned int iSeq;	
	unsigned int iOwner;
	unsigned int iOwnerIDC;
	unsigned int iUpdateTime;
	unsigned int iType; // Ⱥ����
	unsigned int iDis; // ����(��)
	unsigned int iMaxMemberCount;
	unsigned int iNeedVerify;// �Ƿ���Ҫ��֤
}IGGChatRoomResult_t;


typedef struct tagIGGSearchChatRoomResponse
{	
	IGGBaseResponse_t tBaseResponse;
	IGGChatRoomResult_t tChatRoomResult;
	unsigned int iMemberCount; // ��Ա��(����Ⱥ��)
	IGGChatRoomMember_t* ptMemberList;
}IGGSearchChatRoomResponse_t;


typedef struct tagIGGAddChatRoomMemberRequest
{	
	IGGBaseRequest_t tBaseRequest;
	unsigned int iMemberCount;	
	IGGMemberReq_t * ptMemberList;
	unsigned int iChatRoomId;
} IGGAddChatRoomMemberRequest_t;


typedef struct tagIGGAddChatRoomMemberResponse 
{	
	IGGBaseResponse_t tBaseResponse;
	unsigned int iMemberCount;	
	IGGMemberResp_t * ptMemberList;
	unsigned int iChatRoomId;
} IGGAddChatRoomMemberResponse_t;


typedef struct tagIGGAddGroupMemberRequest
{	
	IGGBaseRequest_t tBaseRequest;
	unsigned int iMemberCount;	
	IGGMemberReq_t * ptMemberList;
	unsigned int iChatRoomId;
} IGGAddGroupMemberRequest_t;


typedef struct tagIGGAddGroupMemberResponse 
{	
	IGGBaseResponse_t tBaseResponse;
	unsigned int iMemberCount;	
	IGGMemberResp_t * ptMemberList;
	unsigned int iChatRoomId;
} IGGAddGroupMemberResponse_t;



typedef struct tagIGGDelChatRoomMemberRequest 
{	
	IGGBaseRequest_t tBaseRequest;
	unsigned int iMemberCount;	
	IGGDelMemberReq_t * ptMemberList;	
	unsigned int iChatRoomId;
} IGGDelChatRoomMemberRequest_t;


typedef struct tagIGGDelChatRoomMemberResponse 
{	
	IGGBaseResponse_t tBaseResponse;
	unsigned int iMemberCount;
	IGGDelMemberResp_t * ptMemberList;
	unsigned int iChatRoomId;
} IGGDelChatRoomMemberResponse_t;


typedef struct tagIGGDelGroupMemberRequest 
{	
	IGGBaseRequest_t tBaseRequest;
	unsigned int iMemberCount;	
	IGGDelMemberReq_t * ptMemberList;	
	unsigned int iChatRoomId;
} IGGDelGroupMemberRequest_t;


typedef struct tagIGGDelGroupMemberResponse 
{	
	IGGBaseResponse_t tBaseResponse;
	unsigned int iMemberCount;
	IGGDelMemberResp_t * ptMemberList;
	unsigned int iChatRoomId;
} IGGDelGroupMemberResponse_t;


// ������Ⱥ

typedef struct tagIGGLbsChatRoomRequest {
	IGGBaseRequest_t tBaseRequest;
	float fLongitude; 		// ���� GPS����,��ȷ��С�����6λ
	float fLatitude; 		// ���� GPSγ��,��ȷ��С�����6λ
	int iGPSSource;			// GPS��ԴHARDWARE = 0(ʹ��GPS);  NETWORK = 1(��ʹ��GPS)
	unsigned int iSkipCount; //�ӵڼ�����¼��ʼ����
	unsigned int iFetchCount; //Ҫ����������
} IGGLbsChatRoomRequest_t;

typedef struct tagIGGLbsChatRoom{
	IGGChatRoomResult_t tChatRoomInfo;
	unsigned int iMemberCount;	
	IGGChatRoomMember_t * ptMemberList;	
} IGGLbsChatRoom_t;

typedef struct tagIGGLbsChatRoomResponse {
	IGGBaseResponse_t tBaseResponse;
	unsigned int iChatRoomCount;
	IGGLbsChatRoom_t * tChatRoomList;
	unsigned int iSkipCount; //�ӵڼ�����¼��ʼ����
} IGGLbsChatRoomResponse_t;

typedef struct tagIGGVerifyChatRoomMemberRequest {
	IGGBaseRequest_t tBaseRequest;
	unsigned int iOpcode;		// ������(����)
	char * pcName;				// ���� (����)
	char * pcVerifyMemberTicket;// ��֤Ticket
	char * pcVerifyContent;		// ��֤����
	unsigned int iChatRoomId; // ͬ��ʱ����
} IGGVerifyChatRoomMemberRequest_t;

typedef struct tagIGGVerifyChatRoomMemberResponse {
	IGGBaseResponse_t tBaseResponse;
	unsigned int iOpcode;		//�ͻ����Ϸ���iOpcode
	char*  pcName;		//������е�pcChatRoomName
	unsigned int iChatRoomId; //������е�iChatRoomId
} IGGVerifyChatRoomMemberResponse_t;

typedef struct tagIGGInviteChatRoomMemberRequest {
	IGGBaseRequest_t tBaseRequest;
	unsigned int iOpcode;		// ������(����)
	char * pcName;			// �����˵��û��� (���ջ�ܾ�����)
	char * pcInviteMemberTicket;// ��֤Ticket
	char * pcInviteContent;		// ���뺯
	unsigned int iChatRoomId; // ����
	
	unsigned int iUserCount; //�������û���
	Comm::SKBuiltinString_t * ptUserList; //�������û����б�
} IGGInviteChatRoomMemberRequest_t;

typedef struct tagIGGInviteChatRoomMemberResponse {
	IGGBaseResponse_t tBaseResponse;
	unsigned int iOpcode;		//�ͻ����Ϸ���iOpcode
	char*  pcName;		//������е�pcName
	unsigned int iChatRoomId; //������е�iChatRoomId

	unsigned int iUserCount; //�������û���
	Comm::SKBuiltinString_t * ptUserList; //�������û����б�
	int * piStatusList; //�������û�״̬
} IGGInviteChatRoomMemberResponse_t;

 typedef struct tagIGGCloseChatRoomRequest
{	
	IGGBaseRequest_t tBaseRequest;
	unsigned int iChatRoomId;
	Comm::SKBuiltinString_t tPwd;			//���루��ҪMD5��
	
} IGGCloseChatRoomRequest_t;


typedef struct tagIGGCloseChatRoomResponse
{	
	IGGBaseResponse_t tBaseResponse;
	unsigned int iChatRoomId;
	
} IGGCloseChatRoomResponse_t;

/////////////////////// Ⱥ��� End /////////////////////////////


////////////////////////// ��ȡ�û���ϢBegin //////////////////////////

typedef struct tagIGGDisturbTimeSpan {
	unsigned int iBeginTime;
	unsigned int iEndTime;
} IGGDisturbTimeSpan_t;

typedef struct tagIGGDisturbSetting {
	unsigned int iNightSetting;
	IGGDisturbTimeSpan_t tNightTime;
	unsigned int iAllDaySetting;
	IGGDisturbTimeSpan_t tAllDayTime;
} IGGDisturbSetting_t;

typedef struct tagIGGGmailInfo {
	char * pcGmailAcct;

	unsigned int iGmailSwitch;
	unsigned int iGmailErrCode;
} IGGGmailInfo_t;

typedef struct tagIGGGmailList {
	unsigned int iCount;
	IGGGmailInfo_t * ptList;
} IGGGmailList_t;

typedef struct tagIGGFacebookInfo {
	unsigned long long llUid;
	char * pcName;

	char * pcToken;
} IGGFacebookInfo_t;

typedef struct tagIGGSafeDevice {
	char * pcName;

	char * pcUuid;

	char * pcDeviceType;

	unsigned int iCreateTime;
} IGGSafeDevice_t;

typedef struct tagIGGSafeDeviceList {
	unsigned int iCount;
	IGGSafeDevice_t * ptList;
} IGGSafeDeviceList_t;
/////////////////////// ��һ�ε�½������Ϣ���� ////////////////////////////

typedef struct tagIGGUserInfoSetRequest {
	IGGBaseRequest_t tBaseRequest;
	Comm::SKBuiltinString_t tFirstName;		//First Name
	Comm::SKBuiltinString_t tLastName;		//Last Name
	Comm::SKBuiltinBuffer_t tImgBuf;		//ͷ��BUFF
	unsigned int iUserSex;					//�Ա𣨲���enMMSexType�궨�壩
	IGGBirthday_t tBirthday;
} IGGUserInfoSetRequest_t;

typedef struct tagIGGUserInfoSetResponse {
	IGGBaseResponse_t tBaseResponse;
} IGGUserInfoSetResponse_t;

/////////////////////////////////////////////////////////////////////////////////////

typedef struct tagIGGUserInfoExt {
	IGGSnsUserInfo_t tSnsUserInfo;
	char * pcMyBrandList;

	char * pcMsgPushSound;

	char * pcVoipPushSound;

	unsigned int iBigChatRoomSize;
	unsigned int iBigChatRoomQuota;
	unsigned int iBigChatRoomInvite;
	char * pcSafeMobile;

	char * pcBigHeadImgUrl;

	char * pcSmallHeadImgUrl;

	unsigned int iMainAcctType;
	Comm::SKBuiltinString_t tExtXml;
	IGGSafeDeviceList_t tSafeDeviceList;
	unsigned int iSafeDevice;
} IGGUserInfoExt_t;

typedef struct tagIGGModUserInfo {
	unsigned int iBitFlag;
	Comm::SKBuiltinString_t tUserName;
	Comm::SKBuiltinString_t tNickName;
	unsigned int iBindUin;
	Comm::SKBuiltinString_t tBindEmail;
	Comm::SKBuiltinString_t tBindMobile;
	unsigned int iStatus;
	unsigned int iImgLen;
	char * pcImgBuf;

	int iSex;
	char * pcProvince;

	char * pcCity;

	char * pcSignature;

	unsigned int iPersonalCard;
	IGGDisturbSetting_t tDisturbSetting;
	unsigned int iPluginFlag;
	unsigned int iVerifyFlag;
	char * pcVerifyInfo;

	int iPoint;
	int iExperience;
	int iLevel;
	int iLevelLowExp;
	int iLevelHighExp;
	char * pcWeibo;

	unsigned int iPluginSwitch;
	IGGGmailList_t tGmailList;
	char * pcAlias;

	char * pcWeiboNickname;

	unsigned int iWeiboFlag;
	unsigned int iFaceBookFlag;
	unsigned long long llFBUserID;
	char * pcFBUserName;

	int iAlbumStyle;
	int iAlbumFlag;
	char * pcAlbumBGImgID;

	unsigned int iTXNewsCategory;
	char * pcFBToken;

	char * pcCountry;

	unsigned int iGrayscaleFlag;

	//added by yihuang
	IGGBirthday_t tBirthday; //����
	unsigned int iAge; //���䣬�������ռ���
	IGGHobby_t tHobby; //��Ȥ����
	unsigned int iIntentionFlag; //������Ը��������enMMIntentionFlag

	unsigned int iPhotoCount; //��Ƭ����������ҪSetProfile��ʱ������)
	unsigned int iFriendCount; //��������(����ɾ������ʱ��Ҫ��������ֶΣ�
	unsigned int iGroupCount; //����Ⱥ�����������˳�Ⱥ��ʱ��Ҫ��������ֶΣ�
	unsigned int iMatchCount; //��Գɹ��������յ�ʾ�õ�ʱ����£�

	unsigned int iLBSVisibleState; //�Ƿ�Ը�����������������enLBSVisibleState
	unsigned int iLBSDistanceUnit; //�������˾�����ʾ��λ��������enLBSDistanceUnit
	char * pcLanguage; //����

	Comm::SKBuiltinString_t tFirstName;
	Comm::SKBuiltinString_t tLastName;
	//
} IGGModUserInfo_t;

typedef struct tagIGGGetProfileRequest {
	IGGBaseRequest_t tBaseRequest;
	char * pcUserName;
} IGGGetProfileRequest_t;

typedef struct tagIGGGetProfileResponse {
	IGGBaseResponse_t tBaseResponse;
	IGGModUserInfo_t tUserInfo;
	IGGUserInfoExt_t tUserInfoExt;
} IGGGetProfileResponse_t;

typedef struct tagIGGUploadCoverImgRequest {
	IGGBaseRequest_t tBaseRequest;
	unsigned int iTotalLen;						//�ܴ�С
	unsigned int iStartPos;						//��ʼλ��
	Comm::SKBuiltinBuffer_t tData;				//BUFF(����+���ݳ���)
	char * pcImgHash;							//IGG_HEADIMG#UserName#time(null)

	char * pcUserName;							//�û���

	char * pcMD5;								//<MD5>
	char * pcCDNImgUrl;							//CND ͷ��URL �ݲ���
	char * pcAESKey;							//CND ��Կ
	int iEncryVer;								//CND ���
	int iCDNImgSize;							//�ϴ���CND��ͷ�����ݴ�С
} IGGUploadCoverImgRequest_t;

typedef struct tagIGGUploadCoverImgResponse {
	IGGBaseResponse_t tBaseResponse;			
	unsigned int iTotalLen;						//�ܴ�С
	unsigned int iStartPos;						//��һ��������ʼλ��

	char * pcFinalImgMd5sum;					//<MD5>
	char * pcImgHash;							//(Req)
} IGGUploadCoverImgResponse_t;

typedef struct tagIGGGetCoverImgRequest {
	IGGBaseRequest_t tBaseRequest;
	char * pcUserName;							//�û���

	unsigned int iImgWidth;						//�ͻ���ָ�����
	unsigned int iImgHeight;					//�ͻ���ָ���߶�
	char * pcImgFormat;							//�ͻ���ָ����ʽ

	unsigned int iTotalLen;						//�ܴ�С����һ������0��
	unsigned int iStartPos;						//��ʼλ�ã���һ������0��
} IGGGetCoverImgRequest_t;

typedef struct tagIGGGetCoverImgResponse {
	IGGBaseResponse_t tBaseResponse;
	char * pcUserName;							//�û���

	unsigned int iTotalLen;						//�ܴ�С
	unsigned int iStartPos;						//(Req)
	Comm::SKBuiltinBuffer_t tData;				//BUFF(����+���ݳ���)
} IGGGetCoverImgResponse_t;

typedef struct tagIGGFunctionSwitch {
	unsigned int iFunctionId;
	unsigned int iSwitchValue;
} IGGFunctionSwitch_t;

typedef struct tagIGGReportProfileRequest {
	IGGBaseRequest_t tBaseRequest;
	Comm::SKBuiltinString_t tUserName;			//���ٱ��û�
	unsigned int iReportReason;					//�ٱ�����enIGGProfileReportReason
	unsigned int iReportTime;					//�ٱ�ʱ��
} IGGReportProfileRequest_t;

typedef struct tagIGGReportProfileResponse {
	IGGBaseResponse_t tBaseResponse;
} IGGReportProfileResponse_t;

typedef struct tagIGGReportGroupRequest {
	IGGBaseRequest_t tBaseRequest;
	unsigned int iChatRoomId;					//���ٱ�Ⱥ
	unsigned int iReportReason;					//�ٱ�����enIGGGroupReportReason
	unsigned int iReportTime;					//�ٱ�ʱ��
} IGGReportGroupRequest_t;

typedef struct tagIGGReportGroupResponse {
	IGGBaseResponse_t tBaseResponse;
} IGGReportGroupResponse_t;



////////////////////////// ��ȡ�û���ϢEnd //////////////////////////
//add �ṹ�嶨��

#pragma pack()

#ifndef SKMetaInfo_t
namespace Comm {
	typedef struct tagSKMetaInfo SKMetaInfo_t;
}
#endif

extern const Comm::SKMetaInfo_t * g_ptIGGMicroMsgMetaInfo;
extern const Comm::SKMetaInfoFinder * g_ptIGGMicroMsgMetaInfoFinder;

namespace Comm {
	class SKBuffer;
}

class IGGMicroMsgPickle
{
public:
	static int ToBuffer( const IGGMicroMsgEchoInfo_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGMicroMsgEchoInfo_t * ptStruct );
	static int FreeStructField( IGGMicroMsgEchoInfo_t & tStruct );
	static int DeepCopy( IGGMicroMsgEchoInfo_t * pDestStruct, const IGGMicroMsgEchoInfo_t * pSourceStruct );
	static int Diff( IGGMicroMsgEchoInfo_t * ptStruct1, IGGMicroMsgEchoInfo_t * ptStruct2 );
	static int ToBuffer( const IGGMicroMsgEchoInfo_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGMicroMsgEchoInfo_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGBaseRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGBaseRequest_t * ptStruct );
	static int FreeStructField( IGGBaseRequest_t & tStruct );
	static int DeepCopy( IGGBaseRequest_t * pDestStruct, const IGGBaseRequest_t * pSourceStruct );
	static int Diff( IGGBaseRequest_t * ptStruct1, IGGBaseRequest_t * ptStruct2 );
	static int ToBuffer( const IGGBaseRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGBaseRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGBuiltinIP_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGBuiltinIP_t * ptStruct );
	static int FreeStructField( IGGBuiltinIP_t & tStruct );
	static int DeepCopy( IGGBuiltinIP_t * pDestStruct, const IGGBuiltinIP_t * pSourceStruct );
	static int Diff( IGGBuiltinIP_t * ptStruct1, IGGBuiltinIP_t * ptStruct2 );
	static int ToBuffer( const IGGBuiltinIP_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGBuiltinIP_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGBuiltinIPList_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGBuiltinIPList_t * ptStruct );
	static int FreeStructField( IGGBuiltinIPList_t & tStruct );
	static int DeepCopy( IGGBuiltinIPList_t * pDestStruct, const IGGBuiltinIPList_t * pSourceStruct );
	static int Diff( IGGBuiltinIPList_t * ptStruct1, IGGBuiltinIPList_t * ptStruct2 );
	static int ToBuffer( const IGGBuiltinIPList_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGBuiltinIPList_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGCDNDnsInfo_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGCDNDnsInfo_t * ptStruct );
	static int FreeStructField( IGGCDNDnsInfo_t & tStruct );
	static int DeepCopy( IGGCDNDnsInfo_t * pDestStruct, const IGGCDNDnsInfo_t * pSourceStruct );
	static int Diff( IGGCDNDnsInfo_t * ptStruct1, IGGCDNDnsInfo_t * ptStruct2 );
	static int ToBuffer( const IGGCDNDnsInfo_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGCDNDnsInfo_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGAuthRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGAuthRequest_t * ptStruct );
	static int FreeStructField( IGGAuthRequest_t & tStruct );
	static int DeepCopy( IGGAuthRequest_t * pDestStruct, const IGGAuthRequest_t * pSourceStruct );
	static int Diff( IGGAuthRequest_t * ptStruct1, IGGAuthRequest_t * ptStruct2 );
	static int ToBuffer( const IGGAuthRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGAuthRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGRegRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGRegRequest_t * ptStruct );
	static int FreeStructField( IGGRegRequest_t & tStruct );
	static int DeepCopy( IGGRegRequest_t * pDestStruct, const IGGRegRequest_t * pSourceStruct );
	static int Diff( IGGRegRequest_t * ptStruct1, IGGRegRequest_t * ptStruct2 );
	static int ToBuffer( const IGGRegRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGRegRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGBaseResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGBaseResponse_t * ptStruct );
	static int FreeStructField( IGGBaseResponse_t & tStruct );
	static int DeepCopy( IGGBaseResponse_t * pDestStruct, const IGGBaseResponse_t * pSourceStruct );
	static int Diff( IGGBaseResponse_t * ptStruct1, IGGBaseResponse_t * ptStruct2 );
	static int ToBuffer( const IGGBaseResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGBaseResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGNetworkControl_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGNetworkControl_t * ptStruct );
	static int FreeStructField( IGGNetworkControl_t & tStruct );
	static int DeepCopy( IGGNetworkControl_t * pDestStruct, const IGGNetworkControl_t * pSourceStruct );
	static int Diff( IGGNetworkControl_t * ptStruct1, IGGNetworkControl_t * ptStruct2 );
	static int ToBuffer( const IGGNetworkControl_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGNetworkControl_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGPluginKey_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGPluginKey_t * ptStruct );
	static int FreeStructField( IGGPluginKey_t & tStruct );
	static int DeepCopy( IGGPluginKey_t * pDestStruct, const IGGPluginKey_t * pSourceStruct );
	static int Diff( IGGPluginKey_t * ptStruct1, IGGPluginKey_t * ptStruct2 );
	static int ToBuffer( const IGGPluginKey_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGPluginKey_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGPluginKeyList_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGPluginKeyList_t * ptStruct );
	static int FreeStructField( IGGPluginKeyList_t & tStruct );
	static int DeepCopy( IGGPluginKeyList_t * pDestStruct, const IGGPluginKeyList_t * pSourceStruct );
	static int Diff( IGGPluginKeyList_t * ptStruct1, IGGPluginKeyList_t * ptStruct2 );
	static int ToBuffer( const IGGPluginKeyList_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGPluginKeyList_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGHost_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGHost_t * ptStruct );
	static int FreeStructField( IGGHost_t & tStruct );
	static int DeepCopy( IGGHost_t * pDestStruct, const IGGHost_t * pSourceStruct );
	static int Diff( IGGHost_t * ptStruct1, IGGHost_t * ptStruct2 );
	static int ToBuffer( const IGGHost_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGHost_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGHostList_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGHostList_t * ptStruct );
	static int FreeStructField( IGGHostList_t & tStruct );
	static int DeepCopy( IGGHostList_t * pDestStruct, const IGGHostList_t * pSourceStruct );
	static int Diff( IGGHostList_t * ptStruct1, IGGHostList_t * ptStruct2 );
	static int ToBuffer( const IGGHostList_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGHostList_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGAuthResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGAuthResponse_t * ptStruct );
	static int FreeStructField( IGGAuthResponse_t & tStruct );
	static int DeepCopy( IGGAuthResponse_t * pDestStruct, const IGGAuthResponse_t * pSourceStruct );
	static int Diff( IGGAuthResponse_t * ptStruct1, IGGAuthResponse_t * ptStruct2 );
	static int ToBuffer( const IGGAuthResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGAuthResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGRegResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGRegResponse_t * ptStruct );
	static int FreeStructField( IGGRegResponse_t & tStruct );
	static int DeepCopy( IGGRegResponse_t * pDestStruct, const IGGRegResponse_t * pSourceStruct );
	static int Diff( IGGRegResponse_t * ptStruct1, IGGRegResponse_t * ptStruct2 );
	static int ToBuffer( const IGGRegResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGRegResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGUserInfoSetRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUserInfoSetRequest_t * ptStruct );
	static int FreeStructField( IGGUserInfoSetRequest_t & tStruct );
	static int DeepCopy( IGGUserInfoSetRequest_t * pDestStruct, const IGGUserInfoSetRequest_t * pSourceStruct );
	static int Diff( IGGUserInfoSetRequest_t * ptStruct1, IGGUserInfoSetRequest_t * ptStruct2 );
	static int ToBuffer( const IGGUserInfoSetRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUserInfoSetRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGUserInfoSetResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUserInfoSetResponse_t * ptStruct );
	static int FreeStructField( IGGUserInfoSetResponse_t & tStruct );
	static int DeepCopy( IGGUserInfoSetResponse_t * pDestStruct, const IGGUserInfoSetResponse_t * pSourceStruct );
	static int Diff( IGGUserInfoSetResponse_t * ptStruct1, IGGUserInfoSetResponse_t * ptStruct2 );
	static int ToBuffer( const IGGUserInfoSetResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUserInfoSetResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGCmdItem_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGCmdItem_t * ptStruct );
	static int FreeStructField( IGGCmdItem_t & tStruct );
	static int DeepCopy( IGGCmdItem_t * pDestStruct, const IGGCmdItem_t * pSourceStruct );
	static int Diff( IGGCmdItem_t * ptStruct1, IGGCmdItem_t * ptStruct2 );
	static int ToBuffer( const IGGCmdItem_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGCmdItem_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGNewInitRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGNewInitRequest_t * ptStruct );
	static int FreeStructField( IGGNewInitRequest_t & tStruct );
	static int DeepCopy( IGGNewInitRequest_t * pDestStruct, const IGGNewInitRequest_t * pSourceStruct );
	static int Diff( IGGNewInitRequest_t * ptStruct1, IGGNewInitRequest_t * ptStruct2 );
	static int ToBuffer( const IGGNewInitRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGNewInitRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGNewInitResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGNewInitResponse_t * ptStruct );
	static int FreeStructField( IGGNewInitResponse_t & tStruct );
	static int DeepCopy( IGGNewInitResponse_t * pDestStruct, const IGGNewInitResponse_t * pSourceStruct );
	static int Diff( IGGNewInitResponse_t * ptStruct1, IGGNewInitResponse_t * ptStruct2 );
	static int ToBuffer( const IGGNewInitResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGNewInitResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGSnsUserInfo_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSnsUserInfo_t * ptStruct );
	static int FreeStructField( IGGSnsUserInfo_t & tStruct );
	static int DeepCopy( IGGSnsUserInfo_t * pDestStruct, const IGGSnsUserInfo_t * pSourceStruct );
	static int Diff( IGGSnsUserInfo_t * ptStruct1, IGGSnsUserInfo_t * ptStruct2 );
	static int ToBuffer( const IGGSnsUserInfo_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSnsUserInfo_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGCustomizedInfo_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGCustomizedInfo_t * ptStruct );
	static int FreeStructField( IGGCustomizedInfo_t & tStruct );
	static int DeepCopy( IGGCustomizedInfo_t * pDestStruct, const IGGCustomizedInfo_t * pSourceStruct );
	static int Diff( IGGCustomizedInfo_t * ptStruct1, IGGCustomizedInfo_t * ptStruct2 );
	static int ToBuffer( const IGGCustomizedInfo_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGCustomizedInfo_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGSearchContactRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSearchContactRequest_t * ptStruct );
	static int FreeStructField( IGGSearchContactRequest_t & tStruct );
	static int DeepCopy( IGGSearchContactRequest_t * pDestStruct, const IGGSearchContactRequest_t * pSourceStruct );
	static int Diff( IGGSearchContactRequest_t * ptStruct1, IGGSearchContactRequest_t * ptStruct2 );
	static int ToBuffer( const IGGSearchContactRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSearchContactRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGSearchContactItem_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSearchContactItem_t * ptStruct );
	static int FreeStructField( IGGSearchContactItem_t & tStruct );
	static int DeepCopy( IGGSearchContactItem_t * pDestStruct, const IGGSearchContactItem_t * pSourceStruct );
	static int Diff( IGGSearchContactItem_t * ptStruct1, IGGSearchContactItem_t * ptStruct2 );
	static int ToBuffer( const IGGSearchContactItem_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSearchContactItem_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGSearchContactResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSearchContactResponse_t * ptStruct );
	static int FreeStructField( IGGSearchContactResponse_t & tStruct );
	static int DeepCopy( IGGSearchContactResponse_t * pDestStruct, const IGGSearchContactResponse_t * pSourceStruct );
	static int Diff( IGGSearchContactResponse_t * ptStruct1, IGGSearchContactResponse_t * ptStruct2 );
	static int ToBuffer( const IGGSearchContactResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSearchContactResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGVerifyUser_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGVerifyUser_t * ptStruct );
	static int FreeStructField( IGGVerifyUser_t & tStruct );
	static int DeepCopy( IGGVerifyUser_t * pDestStruct, const IGGVerifyUser_t * pSourceStruct );
	static int Diff( IGGVerifyUser_t * ptStruct1, IGGVerifyUser_t * ptStruct2 );
	static int ToBuffer( const IGGVerifyUser_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGVerifyUser_t * ptStruct, int iPickleType, int iPickleStatus );
	
	static int ToBuffer( const IGGVerifyUserRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGVerifyUserRequest_t * ptStruct );
	static int FreeStructField( IGGVerifyUserRequest_t & tStruct );
	static int DeepCopy( IGGVerifyUserRequest_t * pDestStruct, const IGGVerifyUserRequest_t * pSourceStruct );
	static int Diff( IGGVerifyUserRequest_t * ptStruct1, IGGVerifyUserRequest_t * ptStruct2 );
	static int ToBuffer( const IGGVerifyUserRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGVerifyUserRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGVerifyUserResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGVerifyUserResponse_t * ptStruct );
	static int FreeStructField( IGGVerifyUserResponse_t & tStruct );
	static int DeepCopy( IGGVerifyUserResponse_t * pDestStruct, const IGGVerifyUserResponse_t * pSourceStruct );
	static int Diff( IGGVerifyUserResponse_t * ptStruct1, IGGVerifyUserResponse_t * ptStruct2 );
	static int ToBuffer( const IGGVerifyUserResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGVerifyUserResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGDelContact_t* ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDelContact_t * ptStruct );
	static int FreeStructField( IGGDelContact_t & tStruct );
	static int DeepCopy( IGGDelContact_t * pDestStruct, const IGGDelContact_t * pSourceStruct );
	static int Diff( IGGDelContact_t * ptStruct1, IGGDelContact_t * ptStruct2 );
	static int ToBuffer( const IGGDelContact_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDelContact_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGSyncFriendRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSyncFriendRequest_t * ptStruct );
	static int FreeStructField( IGGSyncFriendRequest_t & tStruct );
	static int DeepCopy( IGGSyncFriendRequest_t * pDestStruct, const IGGSyncFriendRequest_t * pSourceStruct );
	static int Diff( IGGSyncFriendRequest_t * ptStruct1, IGGSyncFriendRequest_t * ptStruct2 );
	static int ToBuffer( const IGGSyncFriendRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSyncFriendRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGRoomInfo_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGRoomInfo_t * ptStruct );
	static int FreeStructField( IGGRoomInfo_t & tStruct );
	static int DeepCopy( IGGRoomInfo_t * pDestStruct, const IGGRoomInfo_t * pSourceStruct );
	static int Diff( IGGRoomInfo_t * ptStruct1, IGGRoomInfo_t * ptStruct2 );
	static int ToBuffer( const IGGRoomInfo_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGRoomInfo_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGModContact_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModContact_t * ptStruct );
	static int FreeStructField( IGGModContact_t & tStruct );
	static int DeepCopy( IGGModContact_t * pDestStruct, const IGGModContact_t * pSourceStruct );
	static int Diff( IGGModContact_t * ptStruct1, IGGModContact_t * ptStruct2 );
	static int ToBuffer( const IGGModContact_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModContact_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGSyncFriendResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSyncFriendResponse_t * ptStruct );
	static int FreeStructField( IGGSyncFriendResponse_t & tStruct );
	static int DeepCopy( IGGSyncFriendResponse_t * pDestStruct, const IGGSyncFriendResponse_t * pSourceStruct );
	static int Diff( IGGSyncFriendResponse_t * ptStruct1, IGGSyncFriendResponse_t * ptStruct2 );
	static int ToBuffer( const IGGSyncFriendResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSyncFriendResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGPossibleFriend_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGPossibleFriend_t * ptStruct );
	static int FreeStructField( IGGPossibleFriend_t & tStruct );
	static int DeepCopy( IGGPossibleFriend_t * pDestStruct, const IGGPossibleFriend_t * pSourceStruct );
	static int Diff( IGGPossibleFriend_t * ptStruct1, IGGPossibleFriend_t * ptStruct2 );
	static int ToBuffer( const IGGPossibleFriend_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGPossibleFriend_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGGetContactRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGetContactRequest_t * ptStruct );
	static int FreeStructField( IGGGetContactRequest_t & tStruct );
	static int DeepCopy( IGGGetContactRequest_t * pDestStruct, const IGGGetContactRequest_t * pSourceStruct );
	static int Diff( IGGGetContactRequest_t * ptStruct1, IGGGetContactRequest_t * ptStruct2 );
	static int ToBuffer( const IGGGetContactRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGetContactRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGGetContactResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGetContactResponse_t * ptStruct );
	static int FreeStructField( IGGGetContactResponse_t & tStruct );
	static int DeepCopy( IGGGetContactResponse_t * pDestStruct, const IGGGetContactResponse_t * pSourceStruct );
	static int Diff( IGGGetContactResponse_t * ptStruct1, IGGGetContactResponse_t * ptStruct2 );
	static int ToBuffer( const IGGGetContactResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGetContactResponse_t * ptStruct, int iPickleType, int iPickleStatus );


	static int ToBuffer( const IGGAuthBySKRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGAuthBySKRequest_t * ptStruct );
	static int FreeStructField( IGGAuthBySKRequest_t & tStruct );
	static int DeepCopy( IGGAuthBySKRequest_t * pDestStruct, const IGGAuthBySKRequest_t * pSourceStruct );
	static int Diff( IGGAuthBySKRequest_t * ptStruct1, IGGAuthBySKRequest_t * ptStruct2 );
	static int ToBuffer( const IGGAuthBySKRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGAuthBySKRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGAuthBySKResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGAuthBySKResponse_t * ptStruct );
	static int FreeStructField( IGGAuthBySKResponse_t & tStruct );
	static int DeepCopy( IGGAuthBySKResponse_t * pDestStruct, const IGGAuthBySKResponse_t * pSourceStruct );
	static int Diff( IGGAuthBySKResponse_t * ptStruct1, IGGAuthBySKResponse_t * ptStruct2 );
	static int ToBuffer( const IGGAuthBySKResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGAuthBySKResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	
	//��Ϣ��ʽ	����
	static int ToBuffer( const IGGMicroMsgRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGMicroMsgRequest_t * ptStruct );
	static int FreeStructField( IGGMicroMsgRequest_t & tStruct );
	static int DeepCopy( IGGMicroMsgRequest_t * pDestStruct, const IGGMicroMsgRequest_t * pSourceStruct );
	static int Diff( IGGMicroMsgRequest_t * ptStruct1, IGGMicroMsgRequest_t * ptStruct2 );
	static int ToBuffer( const IGGMicroMsgRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGMicroMsgRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	//������Ϣ	����
	static int ToBuffer( const IGGSendMsgRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSendMsgRequest_t * ptStruct );
	static int FreeStructField( IGGSendMsgRequest_t & tStruct );
	static int DeepCopy( IGGSendMsgRequest_t * pDestStruct, const IGGSendMsgRequest_t * pSourceStruct );
	static int Diff( IGGSendMsgRequest_t * ptStruct1, IGGSendMsgRequest_t * ptStruct2 );
	static int ToBuffer( const IGGSendMsgRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSendMsgRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	//��Ϣ��ʽ	��Ӧ
	static int ToBuffer( const IGGMicroMsgResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGMicroMsgResponse_t * ptStruct );
	static int FreeStructField( IGGMicroMsgResponse_t & tStruct );
	static int DeepCopy( IGGMicroMsgResponse_t * pDestStruct, const IGGMicroMsgResponse_t * pSourceStruct );
	static int Diff( IGGMicroMsgResponse_t * ptStruct1, IGGMicroMsgResponse_t * ptStruct2 );
	static int ToBuffer( const IGGMicroMsgResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGMicroMsgResponse_t * ptStruct, int iPickleType, int iPickleStatus );
	
	//������Ϣ	��Ӧ
	static int ToBuffer( const IGGSendMsgResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSendMsgResponse_t * ptStruct );
	static int FreeStructField( IGGSendMsgResponse_t & tStruct );
	static int DeepCopy( IGGSendMsgResponse_t * pDestStruct, const IGGSendMsgResponse_t * pSourceStruct );
	static int Diff( IGGSendMsgResponse_t * ptStruct1, IGGSendMsgResponse_t * ptStruct2 );
	static int ToBuffer( const IGGSendMsgResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSendMsgResponse_t * ptStruct, int iPickleType, int iPickleStatus );
	

	// ͬ����Ϣ 
	static int ToBuffer( const IGGAddMsg_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGAddMsg_t * ptStruct );
	static int FreeStructField( IGGAddMsg_t & tStruct );
	static int DeepCopy( IGGAddMsg_t * pDestStruct, const IGGAddMsg_t * pSourceStruct );
	static int Diff( IGGAddMsg_t * ptStruct1, IGGAddMsg_t * ptStruct2 );
	static int ToBuffer( const IGGAddMsg_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGAddMsg_t * ptStruct, int iPickleType, int iPickleStatus );

	
	static int ToBuffer( const IGGKeyVal_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGKeyVal_t * ptStruct );
	static int FreeStructField( IGGKeyVal_t & tStruct );
	static int DeepCopy( IGGKeyVal_t * pDestStruct, const IGGKeyVal_t * pSourceStruct );
	static int Diff( IGGKeyVal_t * ptStruct1, IGGKeyVal_t * ptStruct2 );
	static int ToBuffer( const IGGKeyVal_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGKeyVal_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGSyncKey_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSyncKey_t * ptStruct );
	static int FreeStructField( IGGSyncKey_t & tStruct );
	static int DeepCopy( IGGSyncKey_t * pDestStruct, const IGGSyncKey_t * pSourceStruct );
	static int Diff( IGGSyncKey_t * ptStruct1, IGGSyncKey_t * ptStruct2 );
	static int ToBuffer( const IGGSyncKey_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSyncKey_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGCmdList_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGCmdList_t * ptStruct );
	static int FreeStructField( IGGCmdList_t & tStruct );
	static int DeepCopy( IGGCmdList_t * pDestStruct, const IGGCmdList_t * pSourceStruct );
	static int Diff( IGGCmdList_t * ptStruct1, IGGCmdList_t * ptStruct2 );
	static int ToBuffer( const IGGCmdList_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGCmdList_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGOpCmdResp_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGOpCmdResp_t * ptStruct );
	static int FreeStructField( IGGOpCmdResp_t & tStruct );
	static int DeepCopy( IGGOpCmdResp_t * pDestStruct, const IGGOpCmdResp_t * pSourceStruct );
	static int Diff( IGGOpCmdResp_t * ptStruct1, IGGOpCmdResp_t * ptStruct2 );
	static int ToBuffer( const IGGOpCmdResp_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGOpCmdResp_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGOpCmdRespList_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGOpCmdRespList_t * ptStruct );
	static int FreeStructField( IGGOpCmdRespList_t & tStruct );
	static int DeepCopy( IGGOpCmdRespList_t * pDestStruct, const IGGOpCmdRespList_t * pSourceStruct );
	static int Diff( IGGOpCmdRespList_t * ptStruct1, IGGOpCmdRespList_t * ptStruct2 );
	static int ToBuffer( const IGGOpCmdRespList_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGOpCmdRespList_t * ptStruct, int iPickleType, int iPickleStatus );
	
	static int ToBuffer( const IGGNewSyncRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGNewSyncRequest_t * ptStruct );
	static int FreeStructField( IGGNewSyncRequest_t & tStruct );
	static int DeepCopy( IGGNewSyncRequest_t * pDestStruct, const IGGNewSyncRequest_t * pSourceStruct );
	static int Diff( IGGNewSyncRequest_t * ptStruct1, IGGNewSyncRequest_t * ptStruct2 );
	static int ToBuffer( const IGGNewSyncRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGNewSyncRequest_t * ptStruct, int iPickleType, int iPickleStatus );
	
	static int ToBuffer( const IGGNewSyncResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGNewSyncResponse_t * ptStruct );
	static int FreeStructField( IGGNewSyncResponse_t & tStruct );
	static int DeepCopy( IGGNewSyncResponse_t * pDestStruct, const IGGNewSyncResponse_t * pSourceStruct );
	static int Diff( IGGNewSyncResponse_t * ptStruct1, IGGNewSyncResponse_t * ptStruct2 );
	static int ToBuffer( const IGGNewSyncResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGNewSyncResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGSyncRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSyncRequest_t * ptStruct );
	static int FreeStructField( IGGSyncRequest_t & tStruct );
	static int DeepCopy( IGGSyncRequest_t * pDestStruct, const IGGSyncRequest_t * pSourceStruct );
	static int Diff( IGGSyncRequest_t * ptStruct1, IGGSyncRequest_t * ptStruct2 );
	static int ToBuffer( const IGGSyncRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSyncRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGSyncResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSyncResponse_t * ptStruct );
	static int FreeStructField( IGGSyncResponse_t & tStruct );
	static int DeepCopy( IGGSyncResponse_t * pDestStruct, const IGGSyncResponse_t * pSourceStruct );
	static int Diff( IGGSyncResponse_t * ptStruct1, IGGSyncResponse_t * ptStruct2 );
	static int ToBuffer( const IGGSyncResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSyncResponse_t * ptStruct, int iPickleType, int iPickleStatus );
	
	static int ToBuffer( const IGGBatchGetHeadImgRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGBatchGetHeadImgRequest_t * ptStruct );
	static int FreeStructField( IGGBatchGetHeadImgRequest_t & tStruct );
	static int DeepCopy( IGGBatchGetHeadImgRequest_t * pDestStruct, const IGGBatchGetHeadImgRequest_t * pSourceStruct );
	static int Diff( IGGBatchGetHeadImgRequest_t * ptStruct1, IGGBatchGetHeadImgRequest_t * ptStruct2 );
	static int ToBuffer( const IGGBatchGetHeadImgRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGBatchGetHeadImgRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGImgPair_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGImgPair_t * ptStruct );
	static int FreeStructField( IGGImgPair_t & tStruct );
	static int DeepCopy( IGGImgPair_t * pDestStruct, const IGGImgPair_t * pSourceStruct );
	static int Diff( IGGImgPair_t * ptStruct1, IGGImgPair_t * ptStruct2 );
	static int ToBuffer( const IGGImgPair_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGImgPair_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGBatchGetHeadImgResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGBatchGetHeadImgResponse_t * ptStruct );
	static int FreeStructField( IGGBatchGetHeadImgResponse_t & tStruct );
	static int DeepCopy( IGGBatchGetHeadImgResponse_t * pDestStruct, const IGGBatchGetHeadImgResponse_t * pSourceStruct );
	static int Diff( IGGBatchGetHeadImgResponse_t * ptStruct1, IGGBatchGetHeadImgResponse_t * ptStruct2 );
	static int ToBuffer( const IGGBatchGetHeadImgResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGBatchGetHeadImgResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGUploadHDHeadImgRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadHDHeadImgRequest_t * ptStruct );
	static int FreeStructField( IGGUploadHDHeadImgRequest_t & tStruct );
	static int DeepCopy( IGGUploadHDHeadImgRequest_t * pDestStruct, const IGGUploadHDHeadImgRequest_t * pSourceStruct );
	static int Diff( IGGUploadHDHeadImgRequest_t * ptStruct1, IGGUploadHDHeadImgRequest_t * ptStruct2 );
	static int ToBuffer( const IGGUploadHDHeadImgRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadHDHeadImgRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGUploadHDHeadImgResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadHDHeadImgResponse_t * ptStruct );
	static int FreeStructField( IGGUploadHDHeadImgResponse_t & tStruct );
	static int DeepCopy( IGGUploadHDHeadImgResponse_t * pDestStruct, const IGGUploadHDHeadImgResponse_t * pSourceStruct );
	static int Diff( IGGUploadHDHeadImgResponse_t * ptStruct1, IGGUploadHDHeadImgResponse_t * ptStruct2 );
	static int ToBuffer( const IGGUploadHDHeadImgResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadHDHeadImgResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGGetHDHeadImgRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGetHDHeadImgRequest_t * ptStruct );
	static int FreeStructField( IGGGetHDHeadImgRequest_t & tStruct );
	static int DeepCopy( IGGGetHDHeadImgRequest_t * pDestStruct, const IGGGetHDHeadImgRequest_t * pSourceStruct );
	static int Diff( IGGGetHDHeadImgRequest_t * ptStruct1, IGGGetHDHeadImgRequest_t * ptStruct2 );
	static int ToBuffer( const IGGGetHDHeadImgRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGetHDHeadImgRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGGetHDHeadImgResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGetHDHeadImgResponse_t * ptStruct );
	static int FreeStructField( IGGGetHDHeadImgResponse_t & tStruct );
	static int DeepCopy( IGGGetHDHeadImgResponse_t * pDestStruct, const IGGGetHDHeadImgResponse_t * pSourceStruct );
	static int Diff( IGGGetHDHeadImgResponse_t * ptStruct1, IGGGetHDHeadImgResponse_t * ptStruct2 );
	static int ToBuffer( const IGGGetHDHeadImgResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGetHDHeadImgResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGUploadVoiceRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadVoiceRequest_t * ptStruct );
	static int FreeStructField( IGGUploadVoiceRequest_t & tStruct );
	static int DeepCopy( IGGUploadVoiceRequest_t * pDestStruct, const IGGUploadVoiceRequest_t * pSourceStruct );
	static int Diff( IGGUploadVoiceRequest_t * ptStruct1, IGGUploadVoiceRequest_t * ptStruct2 );
	static int ToBuffer( const IGGUploadVoiceRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadVoiceRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGUploadVoiceResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadVoiceResponse_t * ptStruct );
	static int FreeStructField( IGGUploadVoiceResponse_t & tStruct );
	static int DeepCopy( IGGUploadVoiceResponse_t * pDestStruct, const IGGUploadVoiceResponse_t * pSourceStruct );
	static int Diff( IGGUploadVoiceResponse_t * ptStruct1, IGGUploadVoiceResponse_t * ptStruct2 );
	static int ToBuffer( const IGGUploadVoiceResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadVoiceResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGDownloadVoiceRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDownloadVoiceRequest_t * ptStruct );
	static int FreeStructField( IGGDownloadVoiceRequest_t & tStruct );
	static int DeepCopy( IGGDownloadVoiceRequest_t * pDestStruct, const IGGDownloadVoiceRequest_t * pSourceStruct );
	static int Diff( IGGDownloadVoiceRequest_t * ptStruct1, IGGDownloadVoiceRequest_t * ptStruct2 );
	static int ToBuffer( const IGGDownloadVoiceRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDownloadVoiceRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGDownloadVoiceResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDownloadVoiceResponse_t * ptStruct );
	static int FreeStructField( IGGDownloadVoiceResponse_t & tStruct );
	static int DeepCopy( IGGDownloadVoiceResponse_t * pDestStruct, const IGGDownloadVoiceResponse_t * pSourceStruct );
	static int Diff( IGGDownloadVoiceResponse_t * ptStruct1, IGGDownloadVoiceResponse_t * ptStruct2 );
	static int ToBuffer( const IGGDownloadVoiceResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDownloadVoiceResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGUploadVideoRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadVideoRequest_t * ptStruct );
	static int FreeStructField( IGGUploadVideoRequest_t & tStruct );
	static int DeepCopy( IGGUploadVideoRequest_t * pDestStruct, const IGGUploadVideoRequest_t * pSourceStruct );
	static int Diff( IGGUploadVideoRequest_t * ptStruct1, IGGUploadVideoRequest_t * ptStruct2 );
	static int ToBuffer( const IGGUploadVideoRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadVideoRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGUploadVideoResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadVideoResponse_t * ptStruct );
	static int FreeStructField( IGGUploadVideoResponse_t & tStruct );
	static int DeepCopy( IGGUploadVideoResponse_t * pDestStruct, const IGGUploadVideoResponse_t * pSourceStruct );
	static int Diff( IGGUploadVideoResponse_t * ptStruct1, IGGUploadVideoResponse_t * ptStruct2 );
	static int ToBuffer( const IGGUploadVideoResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadVideoResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGDownloadVideoRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDownloadVideoRequest_t * ptStruct );
	static int FreeStructField( IGGDownloadVideoRequest_t & tStruct );
	static int DeepCopy( IGGDownloadVideoRequest_t * pDestStruct, const IGGDownloadVideoRequest_t * pSourceStruct );
	static int Diff( IGGDownloadVideoRequest_t * ptStruct1, IGGDownloadVideoRequest_t * ptStruct2 );
	static int ToBuffer( const IGGDownloadVideoRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDownloadVideoRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGDownloadVideoResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDownloadVideoResponse_t * ptStruct );
	static int FreeStructField( IGGDownloadVideoResponse_t & tStruct );
	static int DeepCopy( IGGDownloadVideoResponse_t * pDestStruct, const IGGDownloadVideoResponse_t * pSourceStruct );
	static int Diff( IGGDownloadVideoResponse_t * ptStruct1, IGGDownloadVideoResponse_t * ptStruct2 );
	static int ToBuffer( const IGGDownloadVideoResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDownloadVideoResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGUploadMsgImgRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadMsgImgRequest_t * ptStruct );
	static int FreeStructField( IGGUploadMsgImgRequest_t & tStruct );
	static int DeepCopy( IGGUploadMsgImgRequest_t * pDestStruct, const IGGUploadMsgImgRequest_t * pSourceStruct );
	static int Diff( IGGUploadMsgImgRequest_t * ptStruct1, IGGUploadMsgImgRequest_t * ptStruct2 );
	static int ToBuffer( const IGGUploadMsgImgRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadMsgImgRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGUploadMsgImgResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadMsgImgResponse_t * ptStruct );
	static int FreeStructField( IGGUploadMsgImgResponse_t & tStruct );
	static int DeepCopy( IGGUploadMsgImgResponse_t * pDestStruct, const IGGUploadMsgImgResponse_t * pSourceStruct );
	static int Diff( IGGUploadMsgImgResponse_t * ptStruct1, IGGUploadMsgImgResponse_t * ptStruct2 );
	static int ToBuffer( const IGGUploadMsgImgResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadMsgImgResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGDownloadMsgImgRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDownloadMsgImgRequest_t * ptStruct );
	static int FreeStructField( IGGDownloadMsgImgRequest_t & tStruct );
	static int DeepCopy( IGGDownloadMsgImgRequest_t * pDestStruct, const IGGDownloadMsgImgRequest_t * pSourceStruct );
	static int Diff( IGGDownloadMsgImgRequest_t * ptStruct1, IGGDownloadMsgImgRequest_t * ptStruct2 );
	static int ToBuffer( const IGGDownloadMsgImgRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDownloadMsgImgRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGDownloadMsgImgResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDownloadMsgImgResponse_t * ptStruct );
	static int FreeStructField( IGGDownloadMsgImgResponse_t & tStruct );
	static int DeepCopy( IGGDownloadMsgImgResponse_t * pDestStruct, const IGGDownloadMsgImgResponse_t * pSourceStruct );
	static int Diff( IGGDownloadMsgImgResponse_t * ptStruct1, IGGDownloadMsgImgResponse_t * ptStruct2 );
	static int ToBuffer( const IGGDownloadMsgImgResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDownloadMsgImgResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGEmojiUploadInfoReq_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGEmojiUploadInfoReq_t * ptStruct );
	static int FreeStructField( IGGEmojiUploadInfoReq_t & tStruct );
	static int DeepCopy( IGGEmojiUploadInfoReq_t * pDestStruct, const IGGEmojiUploadInfoReq_t * pSourceStruct );
	static int Diff( IGGEmojiUploadInfoReq_t * ptStruct1, IGGEmojiUploadInfoReq_t * ptStruct2 );
	static int ToBuffer( const IGGEmojiUploadInfoReq_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGEmojiUploadInfoReq_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGUploadEmojiRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadEmojiRequest_t * ptStruct );
	static int FreeStructField( IGGUploadEmojiRequest_t & tStruct );
	static int DeepCopy( IGGUploadEmojiRequest_t * pDestStruct, const IGGUploadEmojiRequest_t * pSourceStruct );
	static int Diff( IGGUploadEmojiRequest_t * ptStruct1, IGGUploadEmojiRequest_t * ptStruct2 );
	static int ToBuffer( const IGGUploadEmojiRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadEmojiRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGEmojiUploadInfoResp_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGEmojiUploadInfoResp_t * ptStruct );
	static int FreeStructField( IGGEmojiUploadInfoResp_t & tStruct );
	static int DeepCopy( IGGEmojiUploadInfoResp_t * pDestStruct, const IGGEmojiUploadInfoResp_t * pSourceStruct );
	static int Diff( IGGEmojiUploadInfoResp_t * ptStruct1, IGGEmojiUploadInfoResp_t * ptStruct2 );
	static int ToBuffer( const IGGEmojiUploadInfoResp_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGEmojiUploadInfoResp_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGUploadEmojiResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadEmojiResponse_t * ptStruct );
	static int FreeStructField( IGGUploadEmojiResponse_t & tStruct );
	static int DeepCopy( IGGUploadEmojiResponse_t * pDestStruct, const IGGUploadEmojiResponse_t * pSourceStruct );
	static int Diff( IGGUploadEmojiResponse_t * ptStruct1, IGGUploadEmojiResponse_t * ptStruct2 );
	static int ToBuffer( const IGGUploadEmojiResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadEmojiResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGEmojiDownloadInfoReq_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGEmojiDownloadInfoReq_t * ptStruct );
	static int FreeStructField( IGGEmojiDownloadInfoReq_t & tStruct );
	static int DeepCopy( IGGEmojiDownloadInfoReq_t * pDestStruct, const IGGEmojiDownloadInfoReq_t * pSourceStruct );
	static int Diff( IGGEmojiDownloadInfoReq_t * ptStruct1, IGGEmojiDownloadInfoReq_t * ptStruct2 );
	static int ToBuffer( const IGGEmojiDownloadInfoReq_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGEmojiDownloadInfoReq_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGDownloadEmojiRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDownloadEmojiRequest_t * ptStruct );
	static int FreeStructField( IGGDownloadEmojiRequest_t & tStruct );
	static int DeepCopy( IGGDownloadEmojiRequest_t * pDestStruct, const IGGDownloadEmojiRequest_t * pSourceStruct );
	static int Diff( IGGDownloadEmojiRequest_t * ptStruct1, IGGDownloadEmojiRequest_t * ptStruct2 );
	static int ToBuffer( const IGGDownloadEmojiRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDownloadEmojiRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGEmojiDownloadInfoResp_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGEmojiDownloadInfoResp_t * ptStruct );
	static int FreeStructField( IGGEmojiDownloadInfoResp_t & tStruct );
	static int DeepCopy( IGGEmojiDownloadInfoResp_t * pDestStruct, const IGGEmojiDownloadInfoResp_t * pSourceStruct );
	static int Diff( IGGEmojiDownloadInfoResp_t * ptStruct1, IGGEmojiDownloadInfoResp_t * ptStruct2 );
	static int ToBuffer( const IGGEmojiDownloadInfoResp_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGEmojiDownloadInfoResp_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGDownloadEmojiResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDownloadEmojiResponse_t * ptStruct );
	static int FreeStructField( IGGDownloadEmojiResponse_t & tStruct );
	static int DeepCopy( IGGDownloadEmojiResponse_t * pDestStruct, const IGGDownloadEmojiResponse_t * pSourceStruct );
	static int Diff( IGGDownloadEmojiResponse_t * ptStruct1, IGGDownloadEmojiResponse_t * ptStruct2 );
	static int ToBuffer( const IGGDownloadEmojiResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDownloadEmojiResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGLbsRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGLbsRequest_t * ptStruct );
	static int FreeStructField( IGGLbsRequest_t & tStruct );
	static int DeepCopy( IGGLbsRequest_t * pDestStruct, const IGGLbsRequest_t * pSourceStruct );
	static int Diff( IGGLbsRequest_t * ptStruct1, IGGLbsRequest_t * ptStruct2 );
	static int ToBuffer( const IGGLbsRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGLbsRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGLbsContactInfo_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGLbsContactInfo_t * ptStruct );
	static int FreeStructField( IGGLbsContactInfo_t & tStruct );
	static int DeepCopy( IGGLbsContactInfo_t * pDestStruct, const IGGLbsContactInfo_t * pSourceStruct );
	static int Diff( IGGLbsContactInfo_t * ptStruct1, IGGLbsContactInfo_t * ptStruct2 );
	static int ToBuffer( const IGGLbsContactInfo_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGLbsContactInfo_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGLbsResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGLbsResponse_t * ptStruct );
	static int FreeStructField( IGGLbsResponse_t & tStruct );
	static int DeepCopy( IGGLbsResponse_t * pDestStruct, const IGGLbsResponse_t * pSourceStruct );
	static int Diff( IGGLbsResponse_t * ptStruct1, IGGLbsResponse_t * ptStruct2 );
	static int ToBuffer( const IGGLbsResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGLbsResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGGetLocationRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGetLocationRequest_t * ptStruct );
	static int FreeStructField( IGGGetLocationRequest_t & tStruct );
	static int DeepCopy( IGGGetLocationRequest_t * pDestStruct, const IGGGetLocationRequest_t * pSourceStruct );
	static int Diff( IGGGetLocationRequest_t * ptStruct1, IGGGetLocationRequest_t * ptStruct2 );
	static int ToBuffer( const IGGGetLocationRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGetLocationRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGGetLocationResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGetLocationResponse_t * ptStruct );
	static int FreeStructField( IGGGetLocationResponse_t & tStruct );
	static int DeepCopy( IGGGetLocationResponse_t * pDestStruct, const IGGGetLocationResponse_t * pSourceStruct );
	static int Diff( IGGGetLocationResponse_t * ptStruct1, IGGGetLocationResponse_t * ptStruct2 );
	static int ToBuffer( const IGGGetLocationResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGetLocationResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGLbsMatchRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGLbsMatchRequest_t * ptStruct );
	static int FreeStructField( IGGLbsMatchRequest_t & tStruct );
	static int DeepCopy( IGGLbsMatchRequest_t * pDestStruct, const IGGLbsMatchRequest_t * pSourceStruct );
	static int Diff( IGGLbsMatchRequest_t * ptStruct1, IGGLbsMatchRequest_t * ptStruct2 );
	static int ToBuffer( const IGGLbsMatchRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGLbsMatchRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGLbsMatchResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGLbsMatchResponse_t * ptStruct );
	static int FreeStructField( IGGLbsMatchResponse_t & tStruct );
	static int DeepCopy( IGGLbsMatchResponse_t * pDestStruct, const IGGLbsMatchResponse_t * pSourceStruct );
	static int Diff( IGGLbsMatchResponse_t * ptStruct1, IGGLbsMatchResponse_t * ptStruct2 );
	static int ToBuffer( const IGGLbsMatchResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGLbsMatchResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGSyncLbsMatchRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSyncLbsMatchRequest_t * ptStruct );
	static int FreeStructField( IGGSyncLbsMatchRequest_t & tStruct );
	static int DeepCopy( IGGSyncLbsMatchRequest_t * pDestStruct, const IGGSyncLbsMatchRequest_t * pSourceStruct );
	static int Diff( IGGSyncLbsMatchRequest_t * ptStruct1, IGGSyncLbsMatchRequest_t * ptStruct2 );
	static int ToBuffer( const IGGSyncLbsMatchRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSyncLbsMatchRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGSyncLbsMatchResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSyncLbsMatchResponse_t * ptStruct );
	static int FreeStructField( IGGSyncLbsMatchResponse_t & tStruct );
	static int DeepCopy( IGGSyncLbsMatchResponse_t * pDestStruct, const IGGSyncLbsMatchResponse_t * pSourceStruct );
	static int Diff( IGGSyncLbsMatchResponse_t * ptStruct1, IGGSyncLbsMatchResponse_t * ptStruct2 );
	static int ToBuffer( const IGGSyncLbsMatchResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSyncLbsMatchResponse_t * ptStruct, int iPickleType, int iPickleStatus );
	
	static int ToBuffer( const IGGLbsMatchContactInfo_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGLbsMatchContactInfo_t * ptStruct );
	static int FreeStructField( IGGLbsMatchContactInfo_t & tStruct );
	static int DeepCopy( IGGLbsMatchContactInfo_t * pDestStruct, const IGGLbsMatchContactInfo_t * pSourceStruct );
	static int Diff( IGGLbsMatchContactInfo_t * ptStruct1, IGGLbsMatchContactInfo_t * ptStruct2 );
	static int ToBuffer( const IGGLbsMatchContactInfo_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGLbsMatchContactInfo_t * ptStruct, int iPickleType, int iPickleStatus );

	//////////////// Ⱥ���Begin //////////////////////////
	
	static int ToBuffer( const IGGModChatRoomNotify_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModChatRoomNotify_t * ptStruct );
	static int FreeStructField( IGGModChatRoomNotify_t & tStruct );
	static int DeepCopy( IGGModChatRoomNotify_t * pDestStruct, const IGGModChatRoomNotify_t * pSourceStruct );
	static int Diff( IGGModChatRoomNotify_t * ptStruct1, IGGModChatRoomNotify_t * ptStruct2 );
	static int ToBuffer( const IGGModChatRoomNotify_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModChatRoomNotify_t * ptStruct, int iPickleType, int iPickleStatus );

	
	static int ToBuffer( const IGGModChatRoomMember_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModChatRoomMember_t * ptStruct );
	static int FreeStructField( IGGModChatRoomMember_t & tStruct );
	static int DeepCopy( IGGModChatRoomMember_t * pDestStruct, const IGGModChatRoomMember_t * pSourceStruct );
	static int Diff( IGGModChatRoomMember_t * ptStruct1, IGGModChatRoomMember_t * ptStruct2 );
	static int ToBuffer( const IGGModChatRoomMember_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModChatRoomMember_t * ptStruct, int iPickleType, int iPickleStatus );

	
	static int ToBuffer( const IGGQuitChatRoom_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGQuitChatRoom_t * ptStruct );
	static int FreeStructField( IGGQuitChatRoom_t & tStruct );
	static int DeepCopy( IGGQuitChatRoom_t * pDestStruct, const IGGQuitChatRoom_t * pSourceStruct );
	static int Diff( IGGQuitChatRoom_t * ptStruct1, IGGQuitChatRoom_t * ptStruct2 );
	static int ToBuffer( const IGGQuitChatRoom_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGQuitChatRoom_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGQuitChatRoomRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGQuitChatRoomRequest_t * ptStruct );
	static int FreeStructField( IGGQuitChatRoomRequest_t & tStruct );
	static int DeepCopy( IGGQuitChatRoomRequest_t * pDestStruct, const IGGQuitChatRoomRequest_t * pSourceStruct );
	static int Diff( IGGQuitChatRoomRequest_t * ptStruct1, IGGQuitChatRoomRequest_t * ptStruct2 );
	static int ToBuffer( const IGGQuitChatRoomRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGQuitChatRoomRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	
	static int ToBuffer( const IGGQuitChatRoomResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGQuitChatRoomResponse_t * ptStruct );
	static int FreeStructField( IGGQuitChatRoomResponse_t & tStruct );
	static int DeepCopy( IGGQuitChatRoomResponse_t * pDestStruct, const IGGQuitChatRoomResponse_t * pSourceStruct );
	static int Diff( IGGQuitChatRoomResponse_t * ptStruct1, IGGQuitChatRoomResponse_t * ptStruct2 );
	static int ToBuffer( const IGGQuitChatRoomResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGQuitChatRoomResponse_t * ptStruct, int iPickleType, int iPickleStatus );


	static int ToBuffer( const IGGQuitGroupRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGQuitGroupRequest_t * ptStruct );
	static int FreeStructField( IGGQuitGroupRequest_t & tStruct );
	static int DeepCopy( IGGQuitGroupRequest_t * pDestStruct, const IGGQuitGroupRequest_t * pSourceStruct );
	static int Diff( IGGQuitGroupRequest_t * ptStruct1, IGGQuitGroupRequest_t * ptStruct2 );
	static int ToBuffer( const IGGQuitGroupRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGQuitGroupRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	
	static int ToBuffer( const IGGQuitGroupResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGQuitGroupResponse_t * ptStruct );
	static int FreeStructField( IGGQuitGroupResponse_t & tStruct );
	static int DeepCopy( IGGQuitGroupResponse_t * pDestStruct, const IGGQuitGroupResponse_t * pSourceStruct );
	static int Diff( IGGQuitGroupResponse_t * ptStruct1, IGGQuitGroupResponse_t * ptStruct2 );
	static int ToBuffer( const IGGQuitGroupResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGQuitGroupResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	
	static int ToBuffer( const IGGModChatRoomTopic_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModChatRoomTopic_t * ptStruct );
	static int FreeStructField( IGGModChatRoomTopic_t & tStruct );
	static int DeepCopy( IGGModChatRoomTopic_t * pDestStruct, const IGGModChatRoomTopic_t * pSourceStruct );
	static int Diff( IGGModChatRoomTopic_t * ptStruct1, IGGModChatRoomTopic_t * ptStruct2 );
	static int ToBuffer( const IGGModChatRoomTopic_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModChatRoomTopic_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGModGroupTopic_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModGroupTopic_t * ptStruct );
	static int FreeStructField( IGGModGroupTopic_t & tStruct );
	static int DeepCopy( IGGModGroupTopic_t * pDestStruct, const IGGModGroupTopic_t * pSourceStruct );
	static int Diff( IGGModGroupTopic_t * ptStruct1, IGGModGroupTopic_t * ptStruct2 );
	static int ToBuffer( const IGGModGroupTopic_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModGroupTopic_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGModChatRoomMemberDisplayName_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModChatRoomMemberDisplayName_t * ptStruct );
	static int FreeStructField( IGGModChatRoomMemberDisplayName_t & tStruct );
	static int DeepCopy( IGGModChatRoomMemberDisplayName_t * pDestStruct, const IGGModChatRoomMemberDisplayName_t * pSourceStruct );
	static int Diff( IGGModChatRoomMemberDisplayName_t * ptStruct1, IGGModChatRoomMemberDisplayName_t * ptStruct2 );
	static int ToBuffer( const IGGModChatRoomMemberDisplayName_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModChatRoomMemberDisplayName_t * ptStruct, int iPickleType, int iPickleStatus );
	
	static int ToBuffer( const IGGModChatRoomMemberFlag_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModChatRoomMemberFlag_t * ptStruct );
	static int FreeStructField( IGGModChatRoomMemberFlag_t & tStruct );
	static int DeepCopy( IGGModChatRoomMemberFlag_t * pDestStruct, const IGGModChatRoomMemberFlag_t * pSourceStruct );
	static int Diff( IGGModChatRoomMemberFlag_t * ptStruct1, IGGModChatRoomMemberFlag_t * ptStruct2 );
	static int ToBuffer( const IGGModChatRoomMemberFlag_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModChatRoomMemberFlag_t * ptStruct, int iPickleType, int iPickleStatus );


	static int ToBuffer( const IGGMemberReq_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGMemberReq_t * ptStruct );
	static int FreeStructField( IGGMemberReq_t & tStruct );
	static int DeepCopy( IGGMemberReq_t * pDestStruct, const IGGMemberReq_t * pSourceStruct );
	static int Diff( IGGMemberReq_t * ptStruct1, IGGMemberReq_t * ptStruct2 );
	static int ToBuffer( const IGGMemberReq_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGMemberReq_t * ptStruct, int iPickleType, int iPickleStatus );


	static int ToBuffer( const IGGMemberResp_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGMemberResp_t * ptStruct );
	static int FreeStructField( IGGMemberResp_t & tStruct );
	static int DeepCopy( IGGMemberResp_t * pDestStruct, const IGGMemberResp_t * pSourceStruct );
	static int Diff( IGGMemberResp_t * ptStruct1, IGGMemberResp_t * ptStruct2 );
	static int ToBuffer( const IGGMemberResp_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGMemberResp_t * ptStruct, int iPickleType, int iPickleStatus );


	static int ToBuffer( const IGGDelMemberReq_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDelMemberReq_t * ptStruct );
	static int FreeStructField( IGGDelMemberReq_t & tStruct );
	static int DeepCopy( IGGDelMemberReq_t * pDestStruct, const IGGDelMemberReq_t * pSourceStruct );
	static int Diff( IGGDelMemberReq_t * ptStruct1, IGGDelMemberReq_t * ptStruct2 );
	static int ToBuffer( const IGGDelMemberReq_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDelMemberReq_t * ptStruct, int iPickleType, int iPickleStatus );


	static int ToBuffer( const IGGDelMemberResp_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDelMemberResp_t * ptStruct );
	static int FreeStructField( IGGDelMemberResp_t & tStruct );
	static int DeepCopy( IGGDelMemberResp_t * pDestStruct, const IGGDelMemberResp_t * pSourceStruct );
	static int Diff( IGGDelMemberResp_t * ptStruct1, IGGDelMemberResp_t * ptStruct2 );
	static int ToBuffer( const IGGDelMemberResp_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDelMemberResp_t * ptStruct, int iPickleType, int iPickleStatus );


	static int ToBuffer( const IGGCreateChatRoomRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGCreateChatRoomRequest_t * ptStruct );
	static int FreeStructField( IGGCreateChatRoomRequest_t & tStruct );
	static int DeepCopy( IGGCreateChatRoomRequest_t * pDestStruct, const IGGCreateChatRoomRequest_t * pSourceStruct );
	static int Diff( IGGCreateChatRoomRequest_t * ptStruct1, IGGCreateChatRoomRequest_t * ptStruct2 );
	static int ToBuffer( const IGGCreateChatRoomRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGCreateChatRoomRequest_t * ptStruct, int iPickleType, int iPickleStatus );


	static int ToBuffer( const IGGCreateChatRoomResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGCreateChatRoomResponse_t * ptStruct );
	static int FreeStructField( IGGCreateChatRoomResponse_t & tStruct );
	static int DeepCopy( IGGCreateChatRoomResponse_t * pDestStruct, const IGGCreateChatRoomResponse_t * pSourceStruct );
	static int Diff( IGGCreateChatRoomResponse_t * ptStruct1, IGGCreateChatRoomResponse_t * ptStruct2 );
	static int ToBuffer( const IGGCreateChatRoomResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGCreateChatRoomResponse_t * ptStruct, int iPickleType, int iPickleStatus );


	static int ToBuffer( const IGGCreateGroupRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGCreateGroupRequest_t * ptStruct );
	static int FreeStructField( IGGCreateGroupRequest_t & tStruct );
	static int DeepCopy( IGGCreateGroupRequest_t * pDestStruct, const IGGCreateGroupRequest_t * pSourceStruct );
	static int Diff( IGGCreateGroupRequest_t * ptStruct1, IGGCreateGroupRequest_t * ptStruct2 );
	static int ToBuffer( const IGGCreateGroupRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGCreateGroupRequest_t * ptStruct, int iPickleType, int iPickleStatus );


	static int ToBuffer( const IGGCreateGroupResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGCreateGroupResponse_t * ptStruct );
	static int FreeStructField( IGGCreateGroupResponse_t & tStruct );
	static int DeepCopy( IGGCreateGroupResponse_t * pDestStruct, const IGGCreateGroupResponse_t * pSourceStruct );
	static int Diff( IGGCreateGroupResponse_t * ptStruct1, IGGCreateGroupResponse_t * ptStruct2 );
	static int ToBuffer( const IGGCreateGroupResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGCreateGroupResponse_t * ptStruct, int iPickleType, int iPickleStatus );


	static int ToBuffer( const IGGSearchChatRoomRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSearchChatRoomRequest_t * ptStruct );
	static int FreeStructField( IGGSearchChatRoomRequest_t & tStruct );
	static int DeepCopy( IGGSearchChatRoomRequest_t * pDestStruct, const IGGSearchChatRoomRequest_t * pSourceStruct );
	static int Diff( IGGSearchChatRoomRequest_t * ptStruct1, IGGSearchChatRoomRequest_t * ptStruct2 );
	static int ToBuffer( const IGGSearchChatRoomRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSearchChatRoomRequest_t * ptStruct, int iPickleType, int iPickleStatus );


	static int ToBuffer( const IGGChatRoomResult_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGChatRoomResult_t * ptStruct );
	static int FreeStructField( IGGChatRoomResult_t & tStruct );
	static int DeepCopy( IGGChatRoomResult_t * pDestStruct, const IGGChatRoomResult_t * pSourceStruct );
	static int Diff( IGGChatRoomResult_t * ptStruct1, IGGChatRoomResult_t * ptStruct2 );
	static int ToBuffer( const IGGChatRoomResult_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGChatRoomResult_t * ptStruct, int iPickleType, int iPickleStatus );


	static int ToBuffer( const IGGSearchChatRoomResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSearchChatRoomResponse_t * ptStruct );
	static int FreeStructField( IGGSearchChatRoomResponse_t & tStruct );
	static int DeepCopy( IGGSearchChatRoomResponse_t * pDestStruct, const IGGSearchChatRoomResponse_t * pSourceStruct );
	static int Diff( IGGSearchChatRoomResponse_t * ptStruct1, IGGSearchChatRoomResponse_t * ptStruct2 );
	static int ToBuffer( const IGGSearchChatRoomResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSearchChatRoomResponse_t * ptStruct, int iPickleType, int iPickleStatus );


	static int ToBuffer( const IGGAddChatRoomMemberRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGAddChatRoomMemberRequest_t * ptStruct );
	static int FreeStructField( IGGAddChatRoomMemberRequest_t & tStruct );
	static int DeepCopy( IGGAddChatRoomMemberRequest_t * pDestStruct, const IGGAddChatRoomMemberRequest_t * pSourceStruct );
	static int Diff( IGGAddChatRoomMemberRequest_t * ptStruct1, IGGAddChatRoomMemberRequest_t * ptStruct2 );
	static int ToBuffer( const IGGAddChatRoomMemberRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGAddChatRoomMemberRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGAddChatRoomMemberResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGAddChatRoomMemberResponse_t * ptStruct );
	static int FreeStructField( IGGAddChatRoomMemberResponse_t & tStruct );
	static int DeepCopy( IGGAddChatRoomMemberResponse_t * pDestStruct, const IGGAddChatRoomMemberResponse_t * pSourceStruct );
	static int Diff( IGGAddChatRoomMemberResponse_t * ptStruct1, IGGAddChatRoomMemberResponse_t * ptStruct2 );
	static int ToBuffer( const IGGAddChatRoomMemberResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGAddChatRoomMemberResponse_t * ptStruct, int iPickleType, int iPickleStatus );


	static int ToBuffer( const IGGAddGroupMemberRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGAddGroupMemberRequest_t * ptStruct );
	static int FreeStructField( IGGAddGroupMemberRequest_t & tStruct );
	static int DeepCopy( IGGAddGroupMemberRequest_t * pDestStruct, const IGGAddGroupMemberRequest_t * pSourceStruct );
	static int Diff( IGGAddGroupMemberRequest_t * ptStruct1, IGGAddGroupMemberRequest_t * ptStruct2 );
	static int ToBuffer( const IGGAddGroupMemberRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGAddGroupMemberRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGAddGroupMemberResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGAddGroupMemberResponse_t * ptStruct );
	static int FreeStructField( IGGAddGroupMemberResponse_t & tStruct );
	static int DeepCopy( IGGAddGroupMemberResponse_t * pDestStruct, const IGGAddGroupMemberResponse_t * pSourceStruct );
	static int Diff( IGGAddGroupMemberResponse_t * ptStruct1, IGGAddGroupMemberResponse_t * ptStruct2 );
	static int ToBuffer( const IGGAddGroupMemberResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGAddGroupMemberResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	
	static int ToBuffer( const IGGDelChatRoomMemberRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDelChatRoomMemberRequest_t * ptStruct );
	static int FreeStructField( IGGDelChatRoomMemberRequest_t & tStruct );
	static int DeepCopy( IGGDelChatRoomMemberRequest_t * pDestStruct, const IGGDelChatRoomMemberRequest_t * pSourceStruct );
	static int Diff( IGGDelChatRoomMemberRequest_t * ptStruct1, IGGDelChatRoomMemberRequest_t * ptStruct2 );
	static int ToBuffer( const IGGDelChatRoomMemberRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDelChatRoomMemberRequest_t * ptStruct, int iPickleType, int iPickleStatus );


	static int ToBuffer( const IGGDelChatRoomMemberResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDelChatRoomMemberResponse_t * ptStruct );
	static int FreeStructField( IGGDelChatRoomMemberResponse_t & tStruct );
	static int DeepCopy( IGGDelChatRoomMemberResponse_t * pDestStruct, const IGGDelChatRoomMemberResponse_t * pSourceStruct );
	static int Diff( IGGDelChatRoomMemberResponse_t * ptStruct1, IGGDelChatRoomMemberResponse_t * ptStruct2 );
	static int ToBuffer( const IGGDelChatRoomMemberResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDelChatRoomMemberResponse_t * ptStruct, int iPickleType, int iPickleStatus );


	static int ToBuffer( const IGGDelGroupMemberRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDelGroupMemberRequest_t * ptStruct );
	static int FreeStructField( IGGDelGroupMemberRequest_t & tStruct );
	static int DeepCopy( IGGDelGroupMemberRequest_t * pDestStruct, const IGGDelGroupMemberRequest_t * pSourceStruct );
	static int Diff( IGGDelGroupMemberRequest_t * ptStruct1, IGGDelGroupMemberRequest_t * ptStruct2 );
	static int ToBuffer( const IGGDelGroupMemberRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDelGroupMemberRequest_t * ptStruct, int iPickleType, int iPickleStatus );


	static int ToBuffer( const IGGDelGroupMemberResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDelGroupMemberResponse_t * ptStruct );
	static int FreeStructField( IGGDelGroupMemberResponse_t & tStruct );
	static int DeepCopy( IGGDelGroupMemberResponse_t * pDestStruct, const IGGDelGroupMemberResponse_t * pSourceStruct );
	static int Diff( IGGDelGroupMemberResponse_t * ptStruct1, IGGDelGroupMemberResponse_t * ptStruct2 );
	static int ToBuffer( const IGGDelGroupMemberResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDelGroupMemberResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	
	static int ToBuffer( const IGGLbsChatRoomRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGLbsChatRoomRequest_t * ptStruct );
	static int FreeStructField( IGGLbsChatRoomRequest_t & tStruct );
	static int DeepCopy( IGGLbsChatRoomRequest_t * pDestStruct, const IGGLbsChatRoomRequest_t * pSourceStruct );
	static int Diff( IGGLbsChatRoomRequest_t * ptStruct1, IGGLbsChatRoomRequest_t * ptStruct2 );
	static int ToBuffer( const IGGLbsChatRoomRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGLbsChatRoomRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGChatRoomMember_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGChatRoomMember_t * ptStruct );
	static int FreeStructField( IGGChatRoomMember_t & tStruct );
	static int DeepCopy( IGGChatRoomMember_t * pDestStruct, const IGGChatRoomMember_t * pSourceStruct );
	static int Diff( IGGChatRoomMember_t * ptStruct1, IGGChatRoomMember_t * ptStruct2 );
	static int ToBuffer( const IGGChatRoomMember_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGChatRoomMember_t * ptStruct, int iPickleType, int iPickleStatus );
	
	static int ToBuffer( const IGGLbsChatRoom_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGLbsChatRoom_t * ptStruct );
	static int FreeStructField( IGGLbsChatRoom_t & tStruct );
	static int DeepCopy( IGGLbsChatRoom_t * pDestStruct, const IGGLbsChatRoom_t * pSourceStruct );
	static int Diff( IGGLbsChatRoom_t * ptStruct1, IGGLbsChatRoom_t * ptStruct2 );
	static int ToBuffer( const IGGLbsChatRoom_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGLbsChatRoom_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGLbsChatRoomResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGLbsChatRoomResponse_t * ptStruct );
	static int FreeStructField( IGGLbsChatRoomResponse_t & tStruct );
	static int DeepCopy( IGGLbsChatRoomResponse_t * pDestStruct, const IGGLbsChatRoomResponse_t * pSourceStruct );
	static int Diff( IGGLbsChatRoomResponse_t * ptStruct1, IGGLbsChatRoomResponse_t * ptStruct2 );
	static int ToBuffer( const IGGLbsChatRoomResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGLbsChatRoomResponse_t * ptStruct, int iPickleType, int iPickleStatus );
	
	static int ToBuffer( const IGGVerifyChatRoomMemberRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGVerifyChatRoomMemberRequest_t * ptStruct );
	static int FreeStructField( IGGVerifyChatRoomMemberRequest_t & tStruct );
	static int DeepCopy( IGGVerifyChatRoomMemberRequest_t * pDestStruct, const IGGVerifyChatRoomMemberRequest_t * pSourceStruct );
	static int Diff( IGGVerifyChatRoomMemberRequest_t * ptStruct1, IGGVerifyChatRoomMemberRequest_t * ptStruct2 );
	static int ToBuffer( const IGGVerifyChatRoomMemberRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGVerifyChatRoomMemberRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGVerifyChatRoomMemberResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGVerifyChatRoomMemberResponse_t * ptStruct );
	static int FreeStructField( IGGVerifyChatRoomMemberResponse_t & tStruct );
	static int DeepCopy( IGGVerifyChatRoomMemberResponse_t * pDestStruct, const IGGVerifyChatRoomMemberResponse_t * pSourceStruct );
	static int Diff( IGGVerifyChatRoomMemberResponse_t * ptStruct1, IGGVerifyChatRoomMemberResponse_t * ptStruct2 );
	static int ToBuffer( const IGGVerifyChatRoomMemberResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGVerifyChatRoomMemberResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGInviteChatRoomMemberRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGInviteChatRoomMemberRequest_t * ptStruct );
	static int FreeStructField( IGGInviteChatRoomMemberRequest_t & tStruct );
	static int DeepCopy( IGGInviteChatRoomMemberRequest_t * pDestStruct, const IGGInviteChatRoomMemberRequest_t * pSourceStruct );
	static int Diff( IGGInviteChatRoomMemberRequest_t * ptStruct1, IGGInviteChatRoomMemberRequest_t * ptStruct2 );
	static int ToBuffer( const IGGInviteChatRoomMemberRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGInviteChatRoomMemberRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGInviteChatRoomMemberResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGInviteChatRoomMemberResponse_t * ptStruct );
	static int FreeStructField( IGGInviteChatRoomMemberResponse_t & tStruct );
	static int DeepCopy( IGGInviteChatRoomMemberResponse_t * pDestStruct, const IGGInviteChatRoomMemberResponse_t * pSourceStruct );
	static int Diff( IGGInviteChatRoomMemberResponse_t * ptStruct1, IGGInviteChatRoomMemberResponse_t * ptStruct2 );
	static int ToBuffer( const IGGInviteChatRoomMemberResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGInviteChatRoomMemberResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGCloseChatRoomRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGCloseChatRoomRequest_t * ptStruct );
	static int FreeStructField( IGGCloseChatRoomRequest_t & tStruct );
	static int DeepCopy( IGGCloseChatRoomRequest_t * pDestStruct, const IGGCloseChatRoomRequest_t * pSourceStruct );
	static int Diff( IGGCloseChatRoomRequest_t * ptStruct1, IGGCloseChatRoomRequest_t * ptStruct2 );
	static int ToBuffer( const IGGCloseChatRoomRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGCloseChatRoomRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGCloseChatRoomResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGCloseChatRoomResponse_t * ptStruct );
	static int FreeStructField( IGGCloseChatRoomResponse_t & tStruct );
	static int DeepCopy( IGGCloseChatRoomResponse_t * pDestStruct, const IGGCloseChatRoomResponse_t * pSourceStruct );
	static int Diff( IGGCloseChatRoomResponse_t * ptStruct1, IGGCloseChatRoomResponse_t * ptStruct2 );
	static int ToBuffer( const IGGCloseChatRoomResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGCloseChatRoomResponse_t * ptStruct, int iPickleType, int iPickleStatus );
	
	/////////////// Ⱥ���End ////////////////////////////

	static int ToBuffer( const IGGDisturbTimeSpan_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDisturbTimeSpan_t * ptStruct );
	static int FreeStructField( IGGDisturbTimeSpan_t & tStruct );
	static int DeepCopy( IGGDisturbTimeSpan_t * pDestStruct, const IGGDisturbTimeSpan_t * pSourceStruct );
	static int Diff( IGGDisturbTimeSpan_t * ptStruct1, IGGDisturbTimeSpan_t * ptStruct2 );
	static int ToBuffer( const IGGDisturbTimeSpan_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDisturbTimeSpan_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGDisturbSetting_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDisturbSetting_t * ptStruct );
	static int FreeStructField( IGGDisturbSetting_t & tStruct );
	static int DeepCopy( IGGDisturbSetting_t * pDestStruct, const IGGDisturbSetting_t * pSourceStruct );
	static int Diff( IGGDisturbSetting_t * ptStruct1, IGGDisturbSetting_t * ptStruct2 );
	static int ToBuffer( const IGGDisturbSetting_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGDisturbSetting_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGGmailInfo_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGmailInfo_t * ptStruct );
	static int FreeStructField( IGGGmailInfo_t & tStruct );
	static int DeepCopy( IGGGmailInfo_t * pDestStruct, const IGGGmailInfo_t * pSourceStruct );
	static int Diff( IGGGmailInfo_t * ptStruct1, IGGGmailInfo_t * ptStruct2 );
	static int ToBuffer( const IGGGmailInfo_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGmailInfo_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGGmailList_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGmailList_t * ptStruct );
	static int FreeStructField( IGGGmailList_t & tStruct );
	static int DeepCopy( IGGGmailList_t * pDestStruct, const IGGGmailList_t * pSourceStruct );
	static int Diff( IGGGmailList_t * ptStruct1, IGGGmailList_t * ptStruct2 );
	static int ToBuffer( const IGGGmailList_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGmailList_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGFacebookInfo_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGFacebookInfo_t * ptStruct );
	static int FreeStructField( IGGFacebookInfo_t & tStruct );
	static int DeepCopy( IGGFacebookInfo_t * pDestStruct, const IGGFacebookInfo_t * pSourceStruct );
	static int Diff( IGGFacebookInfo_t * ptStruct1, IGGFacebookInfo_t * ptStruct2 );
	static int ToBuffer( const IGGFacebookInfo_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGFacebookInfo_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGSafeDevice_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSafeDevice_t * ptStruct );
	static int FreeStructField( IGGSafeDevice_t & tStruct );
	static int DeepCopy( IGGSafeDevice_t * pDestStruct, const IGGSafeDevice_t * pSourceStruct );
	static int Diff( IGGSafeDevice_t * ptStruct1, IGGSafeDevice_t * ptStruct2 );
	static int ToBuffer( const IGGSafeDevice_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSafeDevice_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGSafeDeviceList_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSafeDeviceList_t * ptStruct );
	static int FreeStructField( IGGSafeDeviceList_t & tStruct );
	static int DeepCopy( IGGSafeDeviceList_t * pDestStruct, const IGGSafeDeviceList_t * pSourceStruct );
	static int Diff( IGGSafeDeviceList_t * ptStruct1, IGGSafeDeviceList_t * ptStruct2 );
	static int ToBuffer( const IGGSafeDeviceList_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGSafeDeviceList_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGUserInfoExt_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUserInfoExt_t * ptStruct );
	static int FreeStructField( IGGUserInfoExt_t & tStruct );
	static int DeepCopy( IGGUserInfoExt_t * pDestStruct, const IGGUserInfoExt_t * pSourceStruct );
	static int Diff( IGGUserInfoExt_t * ptStruct1, IGGUserInfoExt_t * ptStruct2 );
	static int ToBuffer( const IGGUserInfoExt_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUserInfoExt_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGModUserInfo_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModUserInfo_t * ptStruct );
	static int FreeStructField( IGGModUserInfo_t & tStruct );
	static int DeepCopy( IGGModUserInfo_t * pDestStruct, const IGGModUserInfo_t * pSourceStruct );
	static int Diff( IGGModUserInfo_t * ptStruct1, IGGModUserInfo_t * ptStruct2 );
	static int ToBuffer( const IGGModUserInfo_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModUserInfo_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGGetProfileRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGetProfileRequest_t * ptStruct );
	static int FreeStructField( IGGGetProfileRequest_t & tStruct );
	static int DeepCopy( IGGGetProfileRequest_t * pDestStruct, const IGGGetProfileRequest_t * pSourceStruct );
	static int Diff( IGGGetProfileRequest_t * ptStruct1, IGGGetProfileRequest_t * ptStruct2 );
	static int ToBuffer( const IGGGetProfileRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGetProfileRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGGetProfileResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGetProfileResponse_t * ptStruct );
	static int FreeStructField( IGGGetProfileResponse_t & tStruct );
	static int DeepCopy( IGGGetProfileResponse_t * pDestStruct, const IGGGetProfileResponse_t * pSourceStruct );
	static int Diff( IGGGetProfileResponse_t * ptStruct1, IGGGetProfileResponse_t * ptStruct2 );
	static int ToBuffer( const IGGGetProfileResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGetProfileResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGUploadCoverImgRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadCoverImgRequest_t * ptStruct );
	static int FreeStructField( IGGUploadCoverImgRequest_t & tStruct );
	static int DeepCopy( IGGUploadCoverImgRequest_t * pDestStruct, const IGGUploadCoverImgRequest_t * pSourceStruct );
	static int Diff( IGGUploadCoverImgRequest_t * ptStruct1, IGGUploadCoverImgRequest_t * ptStruct2 );
	static int ToBuffer( const IGGUploadCoverImgRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadCoverImgRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGUploadCoverImgResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadCoverImgResponse_t * ptStruct );
	static int FreeStructField( IGGUploadCoverImgResponse_t & tStruct );
	static int DeepCopy( IGGUploadCoverImgResponse_t * pDestStruct, const IGGUploadCoverImgResponse_t * pSourceStruct );
	static int Diff( IGGUploadCoverImgResponse_t * ptStruct1, IGGUploadCoverImgResponse_t * ptStruct2 );
	static int ToBuffer( const IGGUploadCoverImgResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadCoverImgResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGGetCoverImgRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGetCoverImgRequest_t * ptStruct );
	static int FreeStructField( IGGGetCoverImgRequest_t & tStruct );
	static int DeepCopy( IGGGetCoverImgRequest_t * pDestStruct, const IGGGetCoverImgRequest_t * pSourceStruct );
	static int Diff( IGGGetCoverImgRequest_t * ptStruct1, IGGGetCoverImgRequest_t * ptStruct2 );
	static int ToBuffer( const IGGGetCoverImgRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGetCoverImgRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGGetCoverImgResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGetCoverImgResponse_t * ptStruct );
	static int FreeStructField( IGGGetCoverImgResponse_t & tStruct );
	static int DeepCopy( IGGGetCoverImgResponse_t * pDestStruct, const IGGGetCoverImgResponse_t * pSourceStruct );
	static int Diff( IGGGetCoverImgResponse_t * ptStruct1, IGGGetCoverImgResponse_t * ptStruct2 );
	static int ToBuffer( const IGGGetCoverImgResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGGetCoverImgResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGHobby_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGHobby_t * ptStruct );
	static int FreeStructField( IGGHobby_t & tStruct );
	static int DeepCopy( IGGHobby_t * pDestStruct, const IGGHobby_t * pSourceStruct );
	static int Diff( IGGHobby_t * ptStruct1, IGGHobby_t * ptStruct2 );
	static int ToBuffer( const IGGHobby_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGHobby_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGBirthday_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGBirthday_t * ptStruct );
	static int FreeStructField( IGGBirthday_t & tStruct );
	static int DeepCopy( IGGBirthday_t * pDestStruct, const IGGBirthday_t * pSourceStruct );
	static int Diff( IGGBirthday_t * ptStruct1, IGGBirthday_t * ptStruct2 );
	static int ToBuffer( const IGGBirthday_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGBirthday_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGFunctionSwitch_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGFunctionSwitch_t * ptStruct );
	static int FreeStructField( IGGFunctionSwitch_t & tStruct );
	static int DeepCopy( IGGFunctionSwitch_t * pDestStruct, const IGGFunctionSwitch_t * pSourceStruct );
	static int Diff( IGGFunctionSwitch_t * ptStruct1, IGGFunctionSwitch_t * ptStruct2 );
	static int ToBuffer( const IGGFunctionSwitch_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGFunctionSwitch_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGMobileOptRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGMobileOptRequest_t * ptStruct );
	static int FreeStructField( IGGMobileOptRequest_t & tStruct );
	static int DeepCopy( IGGMobileOptRequest_t * pDestStruct, const IGGMobileOptRequest_t * pSourceStruct );
	static int Diff( IGGMobileOptRequest_t * ptStruct1, IGGMobileOptRequest_t * ptStruct2 );
	static int ToBuffer( const IGGMobileOptRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGMobileOptRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGMobileOptResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGMobileOptResponse_t * ptStruct );
	static int FreeStructField( IGGMobileOptResponse_t & tStruct );
	static int DeepCopy( IGGMobileOptResponse_t * pDestStruct, const IGGMobileOptResponse_t * pSourceStruct );
	static int Diff( IGGMobileOptResponse_t * ptStruct1, IGGMobileOptResponse_t * ptStruct2 );
	static int ToBuffer( const IGGMobileOptResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGMobileOptResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGEmailOptRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGEmailOptRequest_t * ptStruct );
	static int FreeStructField( IGGEmailOptRequest_t & tStruct );
	static int DeepCopy( IGGEmailOptRequest_t * pDestStruct, const IGGEmailOptRequest_t * pSourceStruct );
	static int Diff( IGGEmailOptRequest_t * ptStruct1, IGGEmailOptRequest_t * ptStruct2 );
	static int ToBuffer( const IGGEmailOptRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGEmailOptRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGEmailOptResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGEmailOptResponse_t * ptStruct );
	static int FreeStructField( IGGEmailOptResponse_t & tStruct );
	static int DeepCopy( IGGEmailOptResponse_t * pDestStruct, const IGGEmailOptResponse_t * pSourceStruct );
	static int Diff( IGGEmailOptResponse_t * ptStruct1, IGGEmailOptResponse_t * ptStruct2 );
	static int ToBuffer( const IGGEmailOptResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGEmailOptResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGUploadPlugFriendsRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadPlugFriendsRequest_t * ptStruct );
	static int FreeStructField( IGGUploadPlugFriendsRequest_t & tStruct );
	static int DeepCopy( IGGUploadPlugFriendsRequest_t * pDestStruct, const IGGUploadPlugFriendsRequest_t * pSourceStruct );
	static int Diff( IGGUploadPlugFriendsRequest_t * ptStruct1, IGGUploadPlugFriendsRequest_t * ptStruct2 );
	static int ToBuffer( const IGGUploadPlugFriendsRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadPlugFriendsRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGUploadPlugFriendsResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadPlugFriendsResponse_t * ptStruct );
	static int FreeStructField( IGGUploadPlugFriendsResponse_t & tStruct );
	static int DeepCopy( IGGUploadPlugFriendsResponse_t * pDestStruct, const IGGUploadPlugFriendsResponse_t * pSourceStruct );
	static int Diff( IGGUploadPlugFriendsResponse_t * ptStruct1, IGGUploadPlugFriendsResponse_t * ptStruct2 );
	static int ToBuffer( const IGGUploadPlugFriendsResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGUploadPlugFriendsResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGPushSettingRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGPushSettingRequest_t * ptStruct );
	static int FreeStructField( IGGPushSettingRequest_t & tStruct );
	static int DeepCopy( IGGPushSettingRequest_t * pDestStruct, const IGGPushSettingRequest_t * pSourceStruct );
	static int Diff( IGGPushSettingRequest_t * ptStruct1, IGGPushSettingRequest_t * ptStruct2 );
	static int ToBuffer( const IGGPushSettingRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGPushSettingRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGPushSettingResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGPushSettingResponse_t * ptStruct );
	static int FreeStructField( IGGPushSettingResponse_t & tStruct );
	static int DeepCopy( IGGPushSettingResponse_t * pDestStruct, const IGGPushSettingResponse_t * pSourceStruct );
	static int Diff( IGGPushSettingResponse_t * ptStruct1, IGGPushSettingResponse_t * ptStruct2 );
	static int ToBuffer( const IGGPushSettingResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGPushSettingResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGModUserNameRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModUserNameRequest_t * ptStruct );
	static int FreeStructField( IGGModUserNameRequest_t & tStruct );
	static int DeepCopy( IGGModUserNameRequest_t * pDestStruct, const IGGModUserNameRequest_t * pSourceStruct );
	static int Diff( IGGModUserNameRequest_t * ptStruct1, IGGModUserNameRequest_t * ptStruct2 );
	static int ToBuffer( const IGGModUserNameRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModUserNameRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGModUserNameResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModUserNameResponse_t * ptStruct );
	static int FreeStructField( IGGModUserNameResponse_t & tStruct );
	static int DeepCopy( IGGModUserNameResponse_t * pDestStruct, const IGGModUserNameResponse_t * pSourceStruct );
	static int Diff( IGGModUserNameResponse_t * ptStruct1, IGGModUserNameResponse_t * ptStruct2 );
	static int ToBuffer( const IGGModUserNameResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModUserNameResponse_t * ptStruct, int iPickleType, int iPickleStatus );

	/////////////////�޸�����///////////////////
	static int ToBuffer( const IGGModPwdRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModPwdRequest_t * ptStruct );
	static int FreeStructField( IGGModPwdRequest_t & tStruct );
	static int DeepCopy( IGGModPwdRequest_t * pDestStruct, const IGGModPwdRequest_t * pSourceStruct );
	static int Diff( IGGModPwdRequest_t * ptStruct1, IGGModPwdRequest_t * ptStruct2 );
	static int ToBuffer( const IGGModPwdRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModPwdRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGModPwdResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModPwdResponse_t * ptStruct );
	static int FreeStructField( IGGModPwdResponse_t & tStruct );
	static int DeepCopy( IGGModPwdResponse_t * pDestStruct, const IGGModPwdResponse_t * pSourceStruct );
	static int Diff( IGGModPwdResponse_t * ptStruct1, IGGModPwdResponse_t * ptStruct2 );
	static int ToBuffer( const IGGModPwdResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModPwdResponse_t * ptStruct, int iPickleType, int iPickleStatus );
	///////////////////////////////////////////
	/////////////////ͨ���ֻ��һ�����///////////////////
	static int ToBuffer( const IGGModPwdByMobileRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModPwdByMobileRequest_t * ptStruct );
	static int FreeStructField( IGGModPwdByMobileRequest_t & tStruct );
	static int DeepCopy( IGGModPwdByMobileRequest_t * pDestStruct, const IGGModPwdByMobileRequest_t * pSourceStruct );
	static int Diff( IGGModPwdByMobileRequest_t * ptStruct1, IGGModPwdByMobileRequest_t * ptStruct2 );
	static int ToBuffer( const IGGModPwdByMobileRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModPwdByMobileRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGModPwdByMobileResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModPwdByMobileResponse_t * ptStruct );
	static int FreeStructField( IGGModPwdByMobileResponse_t & tStruct );
	static int DeepCopy( IGGModPwdByMobileResponse_t * pDestStruct, const IGGModPwdByMobileResponse_t * pSourceStruct );
	static int Diff( IGGModPwdByMobileResponse_t * ptStruct1, IGGModPwdByMobileResponse_t * ptStruct2 );
	static int ToBuffer( const IGGModPwdByMobileResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGModPwdByMobileResponse_t * ptStruct, int iPickleType, int iPickleStatus );
	///////////////////////////////////////////

	/////////////////�ٱ��û�///////////////////
	static int ToBuffer( const IGGReportProfileRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGReportProfileRequest_t * ptStruct );
	static int FreeStructField( IGGReportProfileRequest_t & tStruct );
	static int DeepCopy( IGGReportProfileRequest_t * pDestStruct, const IGGReportProfileRequest_t * pSourceStruct );
	static int Diff( IGGReportProfileRequest_t * ptStruct1, IGGReportProfileRequest_t * ptStruct2 );
	static int ToBuffer( const IGGReportProfileRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGReportProfileRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGReportProfileResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGReportProfileResponse_t * ptStruct );
	static int FreeStructField( IGGReportProfileResponse_t & tStruct );
	static int DeepCopy( IGGReportProfileResponse_t * pDestStruct, const IGGReportProfileResponse_t * pSourceStruct );
	static int Diff( IGGReportProfileResponse_t * ptStruct1, IGGReportProfileResponse_t * ptStruct2 );
	static int ToBuffer( const IGGReportProfileResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGReportProfileResponse_t * ptStruct, int iPickleType, int iPickleStatus );
	///////////////////////////////////////////

	/////////////////�ٱ�Ⱥ///////////////////
	static int ToBuffer( const IGGReportGroupRequest_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGReportGroupRequest_t * ptStruct );
	static int FreeStructField( IGGReportGroupRequest_t & tStruct );
	static int DeepCopy( IGGReportGroupRequest_t * pDestStruct, const IGGReportGroupRequest_t * pSourceStruct );
	static int Diff( IGGReportGroupRequest_t * ptStruct1, IGGReportGroupRequest_t * ptStruct2 );
	static int ToBuffer( const IGGReportGroupRequest_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGReportGroupRequest_t * ptStruct, int iPickleType, int iPickleStatus );

	static int ToBuffer( const IGGReportGroupResponse_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGReportGroupResponse_t * ptStruct );
	static int FreeStructField( IGGReportGroupResponse_t & tStruct );
	static int DeepCopy( IGGReportGroupResponse_t * pDestStruct, const IGGReportGroupResponse_t * pSourceStruct );
	static int Diff( IGGReportGroupResponse_t * ptStruct1, IGGReportGroupResponse_t * ptStruct2 );
	static int ToBuffer( const IGGReportGroupResponse_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGReportGroupResponse_t * ptStruct, int iPickleType, int iPickleStatus );
	///////////////////////////////////////////
	
	static int ToBuffer( const IGGWebProxyInfo_t * ptStruct, Comm::SKBuffer * poBuffer );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGWebProxyInfo_t * ptStruct );
	static int FreeStructField( IGGWebProxyInfo_t & tStruct );
	static int DeepCopy( IGGWebProxyInfo_t * pDestStruct, const IGGWebProxyInfo_t * pSourceStruct );
	static int Diff( IGGWebProxyInfo_t * ptStruct1, IGGWebProxyInfo_t * ptStruct2 );
	static int ToBuffer( const IGGWebProxyInfo_t * ptStruct, Comm::SKBuffer * poBuffer, int iPickleType, int iPickleStatus );
	static int FromBuffer( Comm::SKBuffer * poBuffer, IGGWebProxyInfo_t * ptStruct, int iPickleType, int iPickleStatus );
	//////////////////////////////////////////
	
	//add �ṹ��ת���ӿ�
	
	static void SetNetworkByteOrder( int iNetworkByteOrder );
	static void SetPickleType( int iPickleType );
	static int GetPickleType( );
	static void SetPickleStatus( int iPickleStatus );

private:
#ifdef MACOS
	static int m_iNetworkByteOrder;
	static int m_iPickleType;
	static int m_iPickleStatus;
#else
	static __thread int m_iNetworkByteOrder;
	static __thread int m_iPickleType;
	static __thread int m_iPickleStatus;
#endif
};


void test_UserNameRequest(void);


#endif

#ifdef __cplusplus
}
#endif

