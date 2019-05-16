// ChatSvrDlg.h : header file
//

#if !defined(AFX_CHATSVRDLG_H__758016D5_8715_11D6_8F32_00E04CE76240__INCLUDED_)
#define AFX_CHATSVRDLG_H__758016D5_8715_11D6_8F32_00E04CE76240__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChatSvrDlg dialog
#define BUFFER_SIZE		200


class CListeningSocket;
class CClientSocket;
class CChatSvrDlg : public CDialog
{
// Construction
public:
	CChatSvrDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CChatSvrDlg)
	enum { IDD = IDD_CHATSVR_DIALOG };
	CListBox	m_ctrlMsgs;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatSvrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void ProcessPendingAccept();
	void ProcessPendingRead(CClientSocket* pSocket);
	void UpdateClients(char* buffer,int nBufferSize);
protected:
	HICON m_hIcon;


	CListeningSocket* m_pSocket;		//监听套节字
	CPtrList m_connectionList;			//客户端套节字链表
	// Generated message map functions
	//{{AFX_MSG(CChatSvrDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATSVRDLG_H__758016D5_8715_11D6_8F32_00E04CE76240__INCLUDED_)
