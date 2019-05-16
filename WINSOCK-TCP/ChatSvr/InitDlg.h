#if !defined(AFX_INITDLG_H__758016DF_8715_11D6_8F32_00E04CE76240__INCLUDED_)
#define AFX_INITDLG_H__758016DF_8715_11D6_8F32_00E04CE76240__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InitDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInitDlg dialog

class CInitDlg : public CDialog
{
// Construction
public:
	CInitDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInitDlg)
	enum { IDD = IDD_INIT };
	int		m_nPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInitDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInitDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INITDLG_H__758016DF_8715_11D6_8F32_00E04CE76240__INCLUDED_)
