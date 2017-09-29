#pragma once
#include "TcpTool.h"

class CFlyBase
{
public:
	CFlyBase();
	virtual ~CFlyBase();

public:
	// ����SDK
	BOOL Init();
	// �ͷ�SDK
	void Free();

	// ��¼
	void Login(InitParam stParam);
	// ע��
	void LoginOut();

	// TCP����
	void TcpConnect();
	// TCP��һ��CS����
	void NextTcpConnect();

	// ����绰
	int Dialing(CStringA strUid);
	// �����绰
	int Answer();
	// �Ҷϵ绰
	int Hangup();

	// ���ñ�������
	int SetCode(int nVideoCodec, int nAudioCodec);

	// ������Ƶ�ļ�
	void StartPlayfile(char* pchFilePaht, int iFormat, int iDirect, int iLoop);
	// ֹͣ����
	void StopPlayfile();

private:
	// �ͷ��������ֳɹ��󣬸���������ò���
	void UpdateParam();
	// �����RTT�󣬸���RTPP���ò���
	void UpdateRtppParam();

	// IM�˺ŵ�¼
	void IMLogin();
	void IMLoginOut();

	// AMS��֤
	BOOL LoginAMS();
	// ��ȡCS,RTPP�Ļ�ȡ��ַ
	BOOL GetUrl();
	// ��¼CS
	BOOL GetCS();
	// ��¼RTPP
	BOOL GetRTPP();

	// �򿪹ر��߳�
	void StartWorkThread();
	void StopWorkThread();
	// �̺߳���
	DWORD static WINAPI WorkThread(LPVOID lpParam);

public:
	// ���سɹ����
	bool m_bLoad;
	// ��¼���
	bool m_bWork;
	bool m_bGetUrl;

	// ѡ���CS������Index
	int m_nSelectCS;

	// ͨ��״̬
	int m_nCallStatus;
	// ����id
	CStringA m_strCallId;
	
	// ��Ƶ����
	HWND m_hLocalWnd;
	HWND m_hRemoteWnd;

	// �߳̾��
	HANDLE m_hEvent;
	HANDLE m_hThread;

	// �ص�����
	CallBackFunc m_CallBackFunc;

	// �����¼�˺���Ϣ
	char m_accountSid[MAX_PATH];
	char m_accountToken[MAX_PATH];
	char m_clientId[MAX_PATH];
	char m_clientPwd[MAX_PATH];

	// ����AMS��֤���ص�����
	char m_phone[MAX_PATH];
	char m_ssid[MAX_PATH];
	char m_uid[MAX_PATH];
	char m_im_ssid[MAX_PATH];
	char m_name[MAX_PATH];
	char m_forwardnumber[MAX_PATH];

	// ��������ַ
	std::vector<CStringA> m_csAddress;
	std::vector<CStringA> m_rtppAddress;
	CStringA m_stumAddress;

	// TCP���Ӷ���
	TcpTool m_cTcp;
};

