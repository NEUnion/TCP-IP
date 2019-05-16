// ChatClientDlg.h : header file
//

#if !defined(AFX_CHATCLIENTDLG_H__7DFB6A29_8715_11D6_8F32_00E04CE76240__INCLUDED_)
#define AFX_CHATCLIENTDLG_H__7DFB6A29_8715_11D6_8F32_00E04CE76240__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChatClientDlg dialog

#define	BUFFER_SIZE	200			//»º³åÇø´óÐ¡

class CChatSocket;
class CChatClientDlg : public CDialog
{
// Construction
public:
	CChatClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CChatClientDlg)
	enum { IDD = IDD_CHATCLIENT_DIALOG };
	CListBox	m_ctrlMsgs;
	CString	m_strMsg;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
public:
	void ProcessPendingRead();
// Implementation
protected:
	HICON m_hIcon;

	CChatSocket* m_pSocket;
	CString m_strClientName;
	
	void SendMsg(CString strMsg);
	// Generated message map functions
	//{{AFX_MSG(CChatClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATCLIENTDLG_H__7DFB6A29_8715_11D6_8F32_00E04CE76240__INCLUDED_)
