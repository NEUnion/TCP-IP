// ClientSocket.cpp : implementation file
// Download by http://www.codefans.net

#include "stdafx.h"
#include "ChatSvr.h"
#include "ClientSocket.h"
#include "ChatSvrDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSocket

CClientSocket::CClientSocket()
{
}
CClientSocket::CClientSocket(CChatSvrDlg* pDlg)
{
	m_pDlg = pDlg;
}
CClientSocket::~CClientSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSocket, CSocket)
	//{{AFX_MSG_MAP(CClientSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSocket member functions


//通知服务器可以接收数据了
void CClientSocket::OnReceive(int nErrorCode) 
{	
	CSocket::OnReceive(nErrorCode);

	if(m_pDlg)
	{
		//让主对话框处理数据
		m_pDlg->ProcessPendingRead(this);
	}
}

void CClientSocket::OnSend(int nErrorCode) 
{	
	CSocket::OnSend(nErrorCode);
}
