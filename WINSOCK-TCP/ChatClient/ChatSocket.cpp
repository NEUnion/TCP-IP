// ChatSocket.cpp : implementation file
// Download by http://www.codefans.net

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatSocket.h"
#include "ChatClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatSocket

CChatSocket::CChatSocket()
{
}
CChatSocket::CChatSocket(CChatClientDlg* pDlg)
{
	m_pDlg = pDlg;
}
CChatSocket::~CChatSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CChatSocket, CSocket)
	//{{AFX_MSG_MAP(CChatSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CChatSocket member functions

//通知客户端可以结束数据了
void CChatSocket::OnReceive(int nErrorCode) 
{
	CSocket::OnReceive(nErrorCode);

	//让主对话框处理数据
	if(m_pDlg)
		m_pDlg->ProcessPendingRead();
}
