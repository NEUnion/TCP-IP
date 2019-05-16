// ChatSvr.h : main header file for the CHATSVR application
//

#if !defined(AFX_CHATSVR_H__758016D3_8715_11D6_8F32_00E04CE76240__INCLUDED_)
#define AFX_CHATSVR_H__758016D3_8715_11D6_8F32_00E04CE76240__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CChatSvrApp:
// See ChatSvr.cpp for the implementation of this class
//

class CChatSvrApp : public CWinApp
{
public:
	CChatSvrApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatSvrApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CChatSvrApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATSVR_H__758016D3_8715_11D6_8F32_00E04CE76240__INCLUDED_)
