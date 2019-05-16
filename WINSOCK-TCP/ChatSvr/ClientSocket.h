#if !defined(AFX_CLIENTSOCKET_H__758016DE_8715_11D6_8F32_00E04CE76240__INCLUDED_)
#define AFX_CLIENTSOCKET_H__758016DE_8715_11D6_8F32_00E04CE76240__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CClientSocket command target
class CChatSvrDlg;
class CClientSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CClientSocket(CChatSvrDlg* pDlg);
	CClientSocket();
	virtual ~CClientSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CChatSvrDlg* m_pDlg;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCKET_H__758016DE_8715_11D6_8F32_00E04CE76240__INCLUDED_)
