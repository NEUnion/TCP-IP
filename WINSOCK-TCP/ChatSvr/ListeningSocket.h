#if !defined(AFX_LISTENINGSOCKET_H__758016DD_8715_11D6_8F32_00E04CE76240__INCLUDED_)
#define AFX_LISTENINGSOCKET_H__758016DD_8715_11D6_8F32_00E04CE76240__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListeningSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CListeningSocket command target
class CChatSvrDlg;
class CListeningSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CListeningSocket();
	CListeningSocket(CChatSvrDlg* pDlg);
	virtual ~CListeningSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListeningSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListeningSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CChatSvrDlg* m_pDlg;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENINGSOCKET_H__758016DD_8715_11D6_8F32_00E04CE76240__INCLUDED_)
