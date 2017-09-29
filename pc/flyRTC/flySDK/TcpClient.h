#pragma once

class CTcpClient
{
public:
	CTcpClient();
	virtual ~CTcpClient();

public:
	// ����
	void Init();
	// �ͷ�
	void Free();

	bool Connect(char *server, int port);
	// ��������
	bool Send(char *read, int nSize);
	// ��������
	bool Receive(char *read, int nSize);

private:
	// ���ӱ��
	bool m_bInit;
	// ���Ӿ��
	SOCKET m_socket;
	// ������
	CRITICAL_SECTION m_csLock;
};

