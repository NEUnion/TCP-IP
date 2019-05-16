#if !defined(AFX_CHATSOCKET_H__7DFB6A31_8715_11D6_8F32_00E04CE76240__INCLUDED_)
#define AFX_CHATSOCKET_H__7DFB6A31_8715_11D6_8F32_00E04CE76240__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChatSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CChatSocket command target
class CChatClientDlg;
class CChatSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CChatSocket();
	CChatSocket(CChatClientDlg* pDlg);
	virtual ~CChatSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CChatSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CChatClientDlg* m_pDlg;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATSOCKET_H__7DFB6A31_8715_11D6_8F32_00E04CE76240__INCLUDED_)
