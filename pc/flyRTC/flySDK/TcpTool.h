#pragma once
#include "TcpClient.h"

class CFlyBase;
class TcpTool
{
public:
	TcpTool();
	virtual ~TcpTool();

public:
	// ����TCPģ��
	void StartTcp(char *pServer, int nPort);
	// ֹͣTCPģ��
	void StopTcp();
	
private:
	// ���Ͱ汾������
	void SendVersion();
	// ���͵�¼��
	void SendLogin();
	// ����������
	bool SendHeat();
	// ������¼��
	void SendLoginOut();

	// TCP�����߳�
	DWORD static WINAPI TcpWorkThread(LPVOID lpParam);
	// TCP�����߳�
	DWORD static WINAPI TcpRecvThread(LPVOID lpParam);
	
public:
	// �ϲ����
	CFlyBase *m_pBase;
	// TCP���Ӷ���
	CTcpClient m_cTcpClient;

	// ����״̬
	int m_nStatus;
	// �̱߳��
	HANDLE m_hWorkEvent;
	HANDLE m_hRecvEvent;
	HANDLE m_hWorkThread;
	HANDLE m_hRecvThread;

	// ��¼���������
	int m_nRand;
	// ������Ӧ
	HANDLE m_hEvent;
};

