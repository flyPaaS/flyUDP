#include "stdafx.h"
#include "TcpTool.h"
#include "FlyBase.h"
#include <regex>

// TYPE
#define SOCKET_INTERNAL_TYPE	0x00
#define SOCKET_USERSTATUS_TYPE	0x05	// ״̬��ѯ
#define SOCKET_CALL				0xA		// �绰
#define SOCKET_REALTIME_TYPE	0xB		// ʵʱ��Ϣ
#define SOCKET_STORAGE_TYPE		0xC		// �洢ת����Ϣ
#define SOCKET_BOROADCAST		0xD		// �㲥��Ϣ
#define SOCKET_SEVERPUSH_TYPE	0xE		// ����������ҵ��

// OP
#define SOCKET_LOGIN_STATUS_OP			0x01	// ��¼
#define SOCKET_PING_OP					0x02	// ����,״̬��ѯ
#define SOCKET_INPUT_OP					0x03	// ��������
#define SOCKET_LOGINCOT_OFF_LINE_OP		0x04	// �ǳ���Ϣ���洢��Ϣ
#define SOCKET_CONNET_OP				0x05	// ���ӽ���
#define SOCKET_COMPULSORY_OP			0x06	// ǿ��������Ϣ
#define SOCKET_SERVICE_STOP_OP			0x07	// ������ͣ��
#define SOCKET_REEIVER_OP				0x79	// ����Ӧ��
#define SOCKET_VERSION					0x78	// �汾�ŷ���

// ��BSON���������JSON��KEY����˫����
std::string fixProblemJsonString(const std::string& jsonString)
{
	std::regex_constants::syntax_option_type fl = std::regex_constants::icase;
	std::regex regReplaceExp("([a-zA-Z]\\w+):", fl);
	return std::regex_replace(jsonString, regReplaceExp, "\"$1\":");
}

TcpTool::TcpTool()
{
	m_pBase = NULL;
	m_nStatus = 0;

	m_hWorkEvent = NULL;
	m_hRecvEvent = NULL;
	m_hWorkThread = NULL;
	m_hRecvThread = NULL;

	m_nRand = 0;
	m_hEvent = NULL;
}

TcpTool::~TcpTool()
{
	
}

void TcpTool::StartTcp(char *pServer, int nPort)
{
	// �ر���Դ
	StopTcp();
	// ����TCP
	m_cTcpClient.Init();
	// ���������߳�
	if (m_cTcpClient.Connect(pServer, nPort))
	{
		// �����¼�֪ͨ
		m_hEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
		// �����߳�
		m_hWorkEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
		m_hRecvEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
		m_hWorkThread = ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TcpWorkThread, this, 0, NULL);
		m_hRecvThread = ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TcpRecvThread, this, 0, NULL);
	}
	else
	{
		// �ص��ϲ�TCP���ӳɹ�
		if (m_pBase->m_CallBackFunc != NULL)
		{
			m_pBase->m_CallBackFunc(TCP_DISCONNECT, 0, 1, NULL, NULL);
		}
	}
}

void TcpTool::StopTcp()
{
	// �ȹر�TCP����
	m_cTcpClient.Free();
	m_nStatus = 0;
	// �ص��ϲ�TCP���ӳɹ�
	if (m_pBase->m_CallBackFunc != NULL)
	{
		m_pBase->m_CallBackFunc(TCP_DISCONNECT, 0, 0, NULL, NULL);
	}
	// �ر��¼�֪ͨ
	if (m_hEvent != NULL)
	{
		::CloseHandle(m_hEvent);
		m_hEvent = NULL;
	}

	// �رս����߳�
	SetEvent(m_hRecvEvent);
	// �رչ����߳�
	SetEvent(m_hWorkEvent);
	// �ȴ������߳��˳�
	if (m_hRecvThread != NULL)
	{
		DWORD dwStart = GetTickCount();
		while (1)
		{
			int nRet = ::WaitForSingleObject(m_hRecvThread, 1000);
			if (nRet == WAIT_OBJECT_0)
			{
				break;
			}

			if (GetTickCount() - dwStart > 3000)
			{
				::TerminateThread(m_hRecvThread, 0);
				break;
			}
		}
		::CloseHandle(m_hRecvThread);
		m_hRecvThread = NULL;
	}
	if (m_hRecvEvent != NULL)
	{
		::CloseHandle(m_hRecvEvent);
		m_hRecvEvent = NULL;
	}

	// �رչ����߳�
	if (m_hWorkThread != NULL)
	{
		DWORD dwStart = GetTickCount();
		while (1)
		{
			int nRet = ::WaitForSingleObject(m_hWorkThread, 1000);
			if (nRet == WAIT_OBJECT_0)
			{
				break;
			}

			if (GetTickCount() - dwStart > 3000)
			{
				::TerminateThread(m_hWorkThread, 0);
				break;
			}
		}
		::CloseHandle(m_hWorkThread);
		m_hWorkThread = NULL;
	}
	if (m_hWorkEvent != NULL)
	{
		::CloseHandle(m_hWorkEvent);
		m_hWorkEvent = NULL;
	}
}

void TcpTool::SendVersion()
{
	// �汾��
	char sendByte[4] = { 0 };
	int ver = 0x20;
	sendByte[0] = (byte)((ver >> 24) & 0xff);
	sendByte[1] = (byte)((ver >> 16) & 0xff);
	sendByte[2] = (byte)((ver >> 8) & 0xff);
	sendByte[3] = (byte)(ver & 0xff);
	m_cTcpClient.Send(sendByte, 4);
}

void TcpTool::SendLogin()
{
	bsonobjbuilder bjson;
	bjson.append("type", SOCKET_INTERNAL_TYPE);
	bjson.append("op", SOCKET_LOGIN_STATUS_OP);
	bjson.append("enc", 0);
	bsonobj obj = bjson.obj();

	Json *pNode = new Json();
	JsonDict *pRoot = new JsonDict();
	string str1(m_pBase->m_im_ssid);
	JsonString *pValue1 = new JsonString(str1);
	pRoot->setValue("im_ssid", pValue1);

	string str2(VERSION);
	JsonString *pValue2 = new JsonString(str2);
	pRoot->setValue("version", pValue2);

	JsonValue *pValue3 = new JsonValue((double)1);
	pRoot->setValue("netmode", pValue3);

	JsonValue *pValue4 = new JsonValue((double)m_nRand);
	pRoot->setValue("randcode", pValue4);
	pNode->setRoot(pRoot);

	string strBody;
	pNode->writeToStr(strBody);

	int nHeadLength = obj.objsize();
	int nBodyLength = strBody.length();
	int nTotal = nHeadLength + nBodyLength + 4;
	char *pData = new char[nTotal];
	pData[0] = (char)((nHeadLength >> 8) & 0xff);
	pData[1] = (char)(nHeadLength & 0xff);
	pData[2] = (char)((nBodyLength >> 8) & 0xff);
	pData[3] = (char)(nBodyLength & 0xff);
	memcpy(pData + 4, obj.objdata(), nHeadLength);
	memcpy(pData + 4 + nHeadLength, strBody.c_str(), nBodyLength);
	m_cTcpClient.Send(pData, nTotal);
	delete pNode;
	delete[] pData;
}

bool TcpTool::SendHeat()
{
	char sendByte[4] = { 0 };
	sendByte[0] = 0;
	sendByte[1] = 0;
	sendByte[2] = 0;
	sendByte[3] = 0;

	ResetEvent(m_hEvent);
	if (m_cTcpClient.Send(sendByte, 4))
	{
		if (::WaitForSingleObject(m_hEvent, 5000) == WAIT_OBJECT_0)
		{
			return true;
		}
	}
	return false;
}

void TcpTool::SendLoginOut()
{
	bsonobjbuilder bjson;
	bjson.append("type", SOCKET_INTERNAL_TYPE);
	bjson.append("op", SOCKET_LOGINCOT_OFF_LINE_OP);
	bjson.append("enc", 0);
	bsonobj obj = bjson.obj();

	int nHeadLength = obj.objsize();
	int nTotal = nHeadLength + 4;
	char *pData = new char[nTotal];
	pData[0] = (char)((nHeadLength >> 8) & 0xff);
	pData[1] = (char)(nHeadLength & 0xff);
	pData[2] = 0;
	pData[3] = 0;
	memcpy(pData + 4, obj.objdata(), nHeadLength);
	m_cTcpClient.Send(pData, nTotal);
}

DWORD WINAPI TcpTool::TcpWorkThread(LPVOID lpParam)
{
	TcpTool *pTcp = (TcpTool*)lpParam;
	if (pTcp == NULL)
	{
		return 0;
	}

	static int nCount = 1;
	static int nHeatCount = 0;
	while (1)
	{
		if (pTcp->m_nStatus == 0)
		{
			// ���Ͱ汾��Ϣ
			nCount = 1;
			pTcp->SendVersion();
		}
		else if (pTcp->m_nStatus == 1)
		{
			nCount = 1;
			pTcp->SendLogin();
		}
		else if (pTcp->m_nStatus == 2)
		{
			nCount = 30;
			if (pTcp->SendHeat())
			{
				nHeatCount = 0;
			}
			else
			{
				nHeatCount++;
			}
			// 3��ʧ�ܾ��˳�
			if (nHeatCount == 3)
			{
				nCount = 1;
				nHeatCount = 0;
				pTcp->SendLoginOut();
				pTcp->m_nStatus = 0;
				// �ص��ϲ�TCP���ӳɹ�
				if (pTcp->m_pBase->m_CallBackFunc != NULL)
				{
					pTcp->m_pBase->m_CallBackFunc(TCP_DISCONNECT, 0, 2, NULL, NULL);
				}
			}
		}

		if (::WaitForSingleObject(pTcp->m_hWorkEvent, 1000 * nCount) == WAIT_OBJECT_0)
		{
			break;
		}
	}
	return 0;
}

DWORD WINAPI TcpTool::TcpRecvThread(LPVOID lpParam)
{
	TcpTool *pTcp = (TcpTool*)lpParam;
	if (pTcp == NULL)
	{
		return 0;
	}

	while (1)
	{
		char szRead[8] = { 0 };
		bool bSuc = pTcp->m_cTcpClient.Receive(szRead, 4);
		if (bSuc)
		{
			int nHeadLength = (int)((short)(szRead[0] << 8) + (short)(szRead[1] & 0xff));
			int nBodyLength = (int)((short)(szRead[2] << 8) + (short)(szRead[3] & 0xff));
			if (nHeadLength == 0 && nBodyLength == 0)
			{
				// �յ�������
				OutputDebugStringA("recv Heat Pack\r\n");
				if (pTcp->m_hEvent != NULL)
				{
					SetEvent(pTcp->m_hEvent);
				}
			}
			else
			{
				int gnType = -1;
				int gnOp = -1;
				int gnResult = 0;
				char *pszHead = NULL;
				char *pszBody = NULL;
				// ������ͷ
				if (nHeadLength > 0)
				{
					pszHead = new char[nHeadLength + 1];
					bSuc = pTcp->m_cTcpClient.Receive(pszHead, nHeadLength);
					if (bSuc)
					{
						bsonobj obj(pszHead);
						string str = obj.toString();
						// ��û��˫���ŵ�KEY��˫����
						str = fixProblemJsonString(str);

						OutputDebugStringA("recv head = ");
						OutputDebugStringA(str.c_str());
						OutputDebugStringA("\r\n");

						try
						{
							Json json(str);
							JsonDict *pRoot = json.getRoot()->toDict();
							if (pRoot != NULL)
							{
								// ����ͷ����
								if (pRoot->contain("type"))
								{
									gnType = (int)pRoot->getValue("type")->toNumber();
								}
								if (pRoot->contain("op"))
								{
									gnOp = (int)pRoot->getValue("op")->toNumber();
								}
							}
						}
						catch (Exception e)
						{
							// ��ӡ����
							CStringA strTmp;
							strTmp.Format("Json Head fail = %s\r\n", e.getDesc().c_str());
							OutputDebugStringA(strTmp);
						}
					}
				}

				// �����ݰ�
				if (nBodyLength > 0)
				{
					pszBody = new char[nBodyLength + 1];
					bSuc = pTcp->m_cTcpClient.Receive(pszBody, nBodyLength);
					if (bSuc)
					{
						OutputDebugStringA("recv data = ");
						OutputDebugStringA(pszBody);
						OutputDebugStringA("\r\n");

						try
						{
							string str(pszBody);
							Json json(str);
							JsonDict *pRoot = json.getRoot()->toDict();
							if (pRoot != NULL)
							{
								if (pRoot->contain("randcode"))
								{
									pTcp->m_nRand = (int)pRoot->getValue("randcode")->toNumber();
								}
								if (pRoot->contain("result"))
								{
									gnResult = (int)pRoot->getValue("result")->toNumber();
								}
							}
						}
						catch (Exception e)
						{
							// ��ӡ����
							CStringA strTmp;
							strTmp.Format("Json Body fail = %s\r\n", e.getDesc().c_str());
							OutputDebugStringA(strTmp);
						}
					}
				}

				// ���ֳɹ�������״̬
				if (gnType == SOCKET_INTERNAL_TYPE)
				{
					if (gnOp == SOCKET_CONNET_OP)
					{
						pTcp->m_nStatus = 1;
					}
					else if (gnOp == SOCKET_LOGIN_STATUS_OP)
					{
						if (gnResult == 0)
						{
							pTcp->m_nStatus = 2;
							// �ص��ϲ�TCP���ӳɹ�
							if (pTcp->m_pBase->m_CallBackFunc != NULL)
							{
								pTcp->m_pBase->m_CallBackFunc(TCP_CONNECT, 0, 0, NULL, NULL);
							}
						}
					}
				}
				else if (gnType == SOCKET_CALL)
				{
					int nTotal = nHeadLength + nBodyLength + 4;
					char *pData = new char[nTotal];
					pData[0] = (char)((nHeadLength >> 8) & 0xff);
					pData[1] = (char)(nHeadLength & 0xff);
					pData[2] = (char)((nBodyLength >> 8) & 0xff);
					pData[3] = (char)(nBodyLength & 0xff);
					if (nHeadLength > 0)
					{
						memcpy(pData + 4, pszHead, nHeadLength);
					}
					if (nBodyLength > 0)
					{
						memcpy(pData + 4 + nHeadLength, pszBody, nBodyLength);
					}
					UGo_tcp_recv_msg(nTotal,pData);
					delete[] pData;
				}
			}
		}

		if (::WaitForSingleObject(pTcp->m_hRecvEvent, 1000) == WAIT_OBJECT_0)
		{
			break;
		}
	}
	return 0;
}
