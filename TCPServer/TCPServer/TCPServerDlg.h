
// TCPServerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include<string.h>

// CTCPServerDlg �Ի���
class CTCPServerDlg : public CDialogEx
{
// ����
public:
	CTCPServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TCPSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	CEdit m_edit;
	int count;
	CButton m_button;
	
	//�������߳�
    static UINT thread1(LPVOID p);
	static UINT thread2(LPVOID p);
	SOCKET  sockSrv;
	SOCKET sockConn;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	CString senddata;
	
	afx_msg void OnEnChangeEdit1();
};
