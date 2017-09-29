
// flyRTCDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// �ص�����
static void CallBack(int nEvent, int wParam, int lParam, char *pWParam, char *plParam);

// CflyRTCDlg dialog
class CflyRTCDlg : public CDialog
{
// Construction
public:
	CflyRTCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FLYRTC_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnLogin();
	afx_msg void OnBnClickedBtnLoginout();
	afx_msg void OnBnClickedBtnDail();
	afx_msg void OnBnClickedBtnAnswer();
	afx_msg void OnBnClickedBtnHandup();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();

public:
	// ��ʼ���ؼ�
	void InitCtrl();
	// �ص���������
	void CallBackAdapter(int nEvent, int wParam, int lParam, char *pWParam, char *plParam);

public:
	// ƽ̨ѡ��
	int m_nSelect;
	// �б�ѡ��
	int m_nItemSelect;
	// ��¼���
	bool m_bWork;

	// �����绰
	CButton m_btnAnswer;
	// ����绰
	CButton m_btnDail;
	// �Ҷϵ绰
	CButton m_btnHandup;
	// ��¼
	CButton m_btnLogin;
	// ע��
	CButton m_btnLoginOut;
	// ���Բ���ĵ绰�����б�
	CListCtrl m_ltCall;
	// �ͻ���ID�б�
	CListCtrl m_ltClient;
	// ������Ƶ����
	CStatic m_sLocalWnd;
	// Զ����Ƶ����
	CStatic m_sRemoteWnd;
	// �ı���ʾ����
	CStatic m_sText;
	// Codec
	CComboBox m_cVideoCode;
	CComboBox m_cAudioCode;
};
