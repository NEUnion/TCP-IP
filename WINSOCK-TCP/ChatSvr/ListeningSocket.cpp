// ListeningSocket.cpp : implementation file
// Download by http://www.codefans.net

#include "stdafx.h"
#include "ChatSvr.h"
#include "ListeningSocket.h"
#include "ChatSvrDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListeningSocket

CListeningSocket::CListeningSocket()
{
}
CListeningSocket::CListeningSocket(CChatSvrDlg* pDlg)
{
	m_pDlg = pDlg;
}
CListeningSocket::~CListeningSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CListeningSocket, CSocket)
	//{{AFX_MSG_MAP(CListeningSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CListeningSocket member functions

//通知服务器，有客户端连接服务器了
void CListeningSocket::OnAccept(int nErrorCode) 
{

	CSocket::OnAccept(nErrorCode);

	//主对话框处理连接信息
	if(m_pDlg)
		m_pDlg->ProcessPendingAccept();
}
