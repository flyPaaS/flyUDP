
// flyUDPDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CflyUDPDlg dialog
class CflyUDPDlg : public CDialog
{
// Construction
public:
	CflyUDPDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FLYUDP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnPush();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedBtnRes();
	afx_msg LRESULT OnUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnVigoStart(WPARAM wParam, LPARAM lParam);

public:
	// �򿪹ر��߳�
	void StartWorkThread();
	void StartExitThread();
	// �̺߳���
	DWORD static WINAPI WorkThread(LPVOID lpParam);
	DWORD static WINAPI ExitThread(LPVOID lpParam);

	// ��ȡ�����������б�
	void UpdateUdpList();
	DWORD static WINAPI GetUdpThread(LPVOID lpParam);

	// ���������������б�
	void UpdatePullServer(CStringA strSer, CStringA strSerShow, CStringA strSerName);
	DWORD static WINAPI GetUdpPullThread(LPVOID lpParam);
	DWORD static WINAPI GetUdpPullOneThread(LPVOID lpParam);

	// �����б���ʾ
	void UpdateListCtrl();

	// ˢ����ID
	void UpdateStreamId();

public:
	// ������ѡ��
	int m_nMode;
	// �ؼ�
	CButton *m_pCheckPush;
	CButton *m_pCheckPull;

	// flyCanѡ��
	int m_nStreamCan;
	// �ؼ�
	CButton *m_pCheck1;
	CButton *m_pCheck2;

	// �������ؼ�
	CButton m_btnStart;
	// �������б�ؼ�
	CListCtrl m_ltServer;
	// ˢ�»Ự�б�ؼ�
	CButton m_btnRes;
	// ������Ƶ��ʾ�ؼ�
	CStatic m_sLocal;
	// Զ����Ƶ��ʾ�ؼ�
	CStatic m_sRemote;
	// Tips��ʾ�ؼ�
	CStatic m_sTip;

	// �������
	BOOL m_bWork;

	// ˢ�±��
	BOOL m_bRefresh;

	// ���ɵ���ID
	CStringA m_strStreamId;
	CHAR m_szID[128];
	
	// ����������IP
	std::vector<CStringA> m_vtList;
	// ��������������
	std::vector<CStringA> m_vtNameList;
	// ������������ʾ
	std::vector<CStringA> m_vtShowList;

	// ����������IP
	std::vector<CStringA> m_vtPullList;
	// ����������Name
	std::vector<CStringA> m_vtPullNameList;
	// ������������ID
	std::vector<CStringA> m_vtPullStreamList;
	// ������������ʾ
	std::vector<CStringA> m_vtPullShowList;
};
