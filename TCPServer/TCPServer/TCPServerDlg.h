
// TCPServerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include<string.h>

// CTCPServerDlg 对话框
class CTCPServerDlg : public CDialogEx
{
// 构造
public:
	CTCPServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TCPSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	
	//服务器线程
    static UINT thread1(LPVOID p);
	static UINT thread2(LPVOID p);
	SOCKET  sockSrv;
	SOCKET sockConn;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	CString senddata;
	
	afx_msg void OnEnChangeEdit1();
};
