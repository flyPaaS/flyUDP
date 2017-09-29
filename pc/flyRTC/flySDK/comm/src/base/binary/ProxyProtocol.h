/***********************************************************************
 *
 * File:        ProxyProtocol.h
 * Author:      IGG
 * Revision:    $Id: ProxyProtocol.h $
 * Description: ���ݰ�
 *
 ***********************************************************************/

#ifndef MM_PROXY_PROXY_PROTOCOL_H
#define MM_PROXY_PROXY_PROTOCOL_H

/**
 * ͨѶЭ��
 */
struct ProxyProtocol {
	enum {
		PROTO_VER			= 1,	/**< Э��汾�� */
		MIN_HEADER_LEN		= 16, 	/**< ���ͷ������ */
		MAX_HEADER_LEN		= 16  	/**< �ͷ������ */
	};

	enum {
		RESP_NONE					= 10000,		/**< ����Ӧ */

		//IGG logic cmd
		REQ_REG         			= 600001,      /**< Reg ���� */
       RESP_REG        			= 10600001,		/**< Reg ��Ӧ */

		REQ_AUTH					= 600002,		/**< Auth ���� */
		RESP_AUTH       			= 10600002,  	/**< Auth ��Ӧ */
		REQ_REAUTH       			= 600003,		/**< ReAuth���� ʹ��SK */
		RESP_REAUTH       			= 10600003,		/**< ReAuth��Ӧ ʹ��SK */

		REQ_INIT					= 600010,		/**< Init ���� */
    	RESP_INIT					= 10600010,
		REQ_NEW_SYNC        		= 600011,		/**< New Sync ���� */
		RESP_NEW_SYNC       		= 10600011,		/**< New Sync ��Ӧ */
		REQ_SEND_MSG    			= 600012,		/**< SendMsg ���� */
		RESP_SEND_MSG   			= 10600012,		/**< SendMsg ��Ӧ */
		REQ_SYNC_FRIEND				= 600013,		/**< SyncFriend ����*/
    	RESP_SYNC_FRIEND			= 10600013,		/**< SyncFriend ��Ӧ*/
		REQ_USERINFOSET 			= 600014,      /**< UserInfoSet ���� */
    	RESP_USERINFOSET			= 10600014,		/**< UserInfoSet ��Ӧ */
		REQ_GETPROFILE				= 600015,		/**< GetProfile ���� */
		RESP_GETPROFILE				= 10600015,		/**< GetProfile ��Ӧ */	
		REQ_NEW_NOTIFY  			= 600016,      /**< NewNotify ���� */
		REQ_NEW_SYNCCHK 			= 600017,      /**< NewSyncCheck ���� */
		RESP_NEW_SYNCCHK			= 10600017,		/**< NewSyncCheck ���� */

    	REQ_SEARCH_CONTACT 			= 600020, 		/**< SearchContact ����*/
    	RESP_SEARCH_CONTACT			= 10600020,		/**< SearchContact ��Ӧ*/
    	REQ_VERIFY_USER				= 600021,		/**< VerifyUser ����*/
    	RESP_VERIFY_USER			= 10600021,		/**< VerifyUser ��Ӧ*/
    	REQ_GET_CONTACT				= 600022,		/**< GetContact ����*/
    	RESP_GET_CONTACT			= 10600022,		/**< GetContact ��Ӧ*/

		REQ_UPLOAD_MSGIMG  			= 600030,      /**< UploadMsgImg ���� */
		RESP_UPLOAD_MSGIMG 			= 10600030,		/**< UploadMsgImg ��Ӧ */
		REQ_DOWNLOAD_MSGIMG     	= 600031,      /**< DownloadMsgImg ���� */
		RESP_DOWNLOAD_MSGIMG    	= 10600031,    /**< DownloadMsgImg ��Ӧ */
		REQ_UPLOAD_HEAD_HDIMG  		= 600032,      /**< UploadHeadHDImg ���� */
		RESP_UPLOAD_HEAD_HDIMG 		= 10600032,		/**< UploadHeadHDImg ��Ӧ */
		REQ_GET_HEAD_HDIMG     		= 600033,      /**< GetHeadHDImg ���� */
		RESP_GET_HEAD_HDIMG    		= 10600033,		/**< GetHeadHDImg ��Ӧ */
		REQ_GET_HEAD_IMG     		= 600034,      /**< GetHeadImg ���� */
		RESP_GET_HEAD_IMG    		= 10600034,		/**< GetHeadImg ��Ӧ */
		REQ_UPLOAD_VOICE  			= 600035,      /**< UploadVoice ���� */
		RESP_UPLOAD_VOICE 			= 10600035,		/**< UploadVoice ��Ӧ */
		REQ_DOWNLOAD_VOICE     		= 600036,      /**< DownloadVoice ���� */
		RESP_DOWNLOAD_VOICE   		= 10600036,		/**< DownloadVoice ��Ӧ */
		REQ_UPLOAD_VIDEO     		= 600037,      /**< UploadVideo ���� */
		RESP_UPLOAD_VIDEO    		= 10600037,		/**< UploadVideo ��Ӧ */
		REQ_DOWNLOAD_VIDEO     		= 600038,      /**< DownloadVideo ���� */
		RESP_DOWNLOAD_VIDEO    		= 10600038,		/**< DownloadVideo ��Ӧ */
		REQ_UPLOAD_EMOJI     		= 600039,      /**< UploadEmoji ���� */
		RESP_UPLOAD_EMOJI    		= 10600039,		/**< UploadEmoji ��Ӧ */
		REQ_DOWNLOAD_EMOJI    		= 600040,      /**< DownloadEmoji ���� */
		RESP_DOWNLOAD_EMOJI    		= 10600040,		/**< DownloadEmoji ��Ӧ */
		REQ_UPLOADCOVERIMG			= 600041,		/**< UploadCoverImg ���� */
		RESP_UPLOADCOVERIMG			= 10600041,		/**< UploadCoverImg ��Ӧ */	
		REQ_GETCOVERIMG				= 600042,		/**< GetCoverImg ���� */
		RESP_GETCOVERIMG			= 10600042,		/**< GetCoverImg ��Ӧ */	
			
		REQ_LBSFIND					= 600060,		/**< LbsFind ���� */
		RESP_LBSFIND				= 10600060,		/**< LbsFind ��Ӧ */
		REQ_GETLOCATION				= 600061,		/**< GetLocation ���� */
		RESP_GETLOCATION			= 10600061,		/**< GetLocation ��Ӧ */
		REQ_LBSMATCH				= 600062,		/**< LbsMatch ���� */
		RESP_LBSMATCH				= 10600062,		/**< LbsMatch ��Ӧ */
		REQ_SYNCLBSMATCH			= 600063,		/**< SyncLbsMatch ���� */
		RESP_SYNCLBSMATCH			= 10600063,		/**< SyncLbsMatch ��Ӧ */

		//=========================================================

		REQ_MOBILE_OPT				= 600070,
		RESP_MOBILE_OPT				= 10600070,
		REQ_EMAIL_OPT				= 600071,
		RESP_EMAIL_OPT				= 10600071,
		REQ_UPLOAD_PLUGFRIENDS		= 600072,
		RESP_UPLOAD_PLUGFRIENDS		= 10600072,
		REQ_PUSHSETTING				= 600073,
		RESP_PUSHSETTING			= 10600073,

		REQ_MODUSERNAME				= 600074,
		RESP_MODUSERNAME			= 10600074,

		REQ_MODPWD					= 600075,
		RESP_MODPWD					= 10600075,

		REQ_MODPWD_BYMOBILE			= 600076,
		RESP_MODPWD_BYMOBILE		= 10600076,

		REQ_GET_DNS 				= 600077,      /**< ��ȡ ip ���� */
		RESP_GET_DNS 				= 10600077,		/**< ��ȡ ip ��Ӧ */
		
		//==========================Ⱥ����ؿ�ʼ==================

		REQ_CREATE_CHATROOM			= 600080,		/**< CreateChatRoom ����*/
		RESP_CREATE_CHATROOM		= 10600080,		/**< CreateChatRoom ��Ӧ*/

		REQ_ADD_CHATROOM_MEMBER		= 600081,		/**< AddChatRoomMember ����*/
		RESP_ADD_CHATROOM_MEMBER	= 10600081,		/**< AddChatRoomMember ��Ӧ*/

		REQ_DEL_CHATROOM_MEMBER		= 600082,		/**< DelChatRoomMember ����*/
		RESP_DEL_CHATROOM_MEMBER	= 10600082,		/**< DelChatRoomMember ��Ӧ*/

		REQ_QUIT_CHATROOM			= 600083,		/**< QuitChatRomm ���� */
		RESP_QUIT_CHATROOM			= 10600083,		/**< QuitChatRomm ��Ӧ*/

		REQ_SEARCH_CHATROOM			= 600084,		/**< SearchChatRoom ����*/
		RESP_SEARCH_CHATROOM		= 10600084,		/**< SearchChatRoom ��Ӧ*/

		REQ_LBSCHATROOMFIND			= 600085,		/**< LbsChatRoomFind ���� */
		RESP_LBSCHATROOMFIND		= 10600085,		/**< LbsChatRoomFind ��Ӧ */

		REQ_VERIFYCHATROOMMEMBER	= 600086,		/**< VerifyChatRoomMember���� */
		RESP_VERIFYCHATROOMMEMBER	= 10600086,		/**< VerifyChatRoomMember ��Ӧ */
		
		REQ_INVITECHATROOMMEMBER	= 600087,		/**< InviteChatRoomMember���� */
		RESP_INVITECHATROOMMEMBER	= 10600087,		/**< InviteChatRoomMember ��Ӧ */
		
		REQ_CLOSECHATROOM			= 600088,		/**< CloseChatRoom���� */
		RESP_CLOSECHATROOM			= 10600088,		/**< CloseChatRoom ��Ӧ */


		REQ_CREATE_GROUP			= 600090,		/**< CreateGroup ����*/
		RESP_CREATE_GROUP			= 10600090,		/**< CreateGroup ��Ӧ*/

		REQ_ADD_GROUP_MEMBER		= 600091,		/**< AddGroupMember ����*/
		RESP_ADD_GROUP_MEMBER		= 10600091,		/**< AddGroupMember ��Ӧ*/

		REQ_DEL_GROUP_MEMBER		= 600092,		/**< DelGroupMember ����*/
		RESP_DEL_GROUP_MEMBER		= 10600092,		/**< DelGroupMember ��Ӧ*/
		
		REQ_QUIT_GROUP				= 600093,		/**< QuitGroup ����*/
		RESP_QUIT_GROUP				= 10600093,		/**< QuitGroup ��Ӧ*/
		//==========================Ⱥ��ؽ���==================
		
		REQ_REPORT_PROFILE			= 600094,		/**< ReportProfile ����*/
		RESP_REPORT_PROFILE			= 10600094,		/**< ReportProfile ��Ӧ*/
		
		REQ_REPORT_GROUP			= 600095,		/**< ReportGroup ����*/
		RESP_REPORT_GROUP			= 10600095,		/**< ReportGroup ��Ӧ*/
		
		REQ_NOOP        			= 600100,      /**< Noop ���� */
		RESP_NOOP       			= 10600100,		/**< Noop ��Ӧ */
		REQ_QUIT        			= 600101,      /**< Quit ���� */
		REQ_DIRECT_SEND 			= 600102,      /**< DirectSend ���� */
		
		REQ_SYNC_CHECK		= 600103,
		RESP_SYNC_CHECK		= 10600103,
		REQ_FIX_SYNCCHK		= 600104,
		RESP_FIX_SYNCCHK	= 10600104,

		REQ_BULLETIN    			= 700000,      /**< ���Ϲ��� */
		REQ_SPEED_TEST_NOTIFY 		= 700001,     	/**< ����֪ͨ */
		REQ_SPEED_TEST  			= 700002,      /**< �������� */
		RESP_SPEED_TEST 			= 10700002,		/**< ������Ӧ */
		REQ_RPT_SPEED_TEST 			= 700003,      /**< �ϱ����ٽ������ */
		RESP_RPT_SPEED_TEST 		= 10700003,		/**< �ϱ����ٽ����Ӧ */
		
		REQ_VOIP_INVITE_NOTIFY 		= 700010,   	/**< VoipInviteNotify ���� */
		REQ_NEWSYNC_SYNCWAIT 		= 700011,		/**< ֧��syncwait��newsync����*/
		RESP_NEWSYNC_SYNCWAIT 		= 10700011,		/**< ֧��syncwait��newsync��Ӧ*/
		REQ_NEWSYNC_NOTIFYDATA 		= 700012,		/**< newsync notifydata����*/
		REQ_NEWSYNC_ACK 			= 10700012,		/**< newsync ack ��Ӧ*/

		RESP_VOIP_SYNC			= 10700013,
		RESP_SNS_SYNC			= 10700014,
		REQ_NOTIFY			= 700015,
		REQ_VOIP_NOTIFY			= 700016,

		REQ_CONN        			= 700300,   	/**< �ڲ�ָ��: ���� */
		REQ_DISCONN     			= 700301,   	/**< �ڲ�ָ��: ���� */
		REQ_ONLINE      			= 700302,   	/**< �ڲ�ָ��: ���� */
		REQ_OFFLINE     			= 700303,   	/**< �ڲ�ָ��: ���� */
		REQ_SWITCH      			= 700304,   	/**< �ڲ�ָ��: �л� */
		REQ_CLI_NOT_FOUND 			= 700305,      	/**< �ڲ�ָ��: �ͻ��˲����� */
	};
};

#endif
