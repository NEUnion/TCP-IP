// ChatSvrDlg.cpp : implementation file
// Download by http://www.codefans.net

#include "stdafx.h"
#include "ChatSvr.h"
#include "ChatSvrDlg.h"
#include "ClientSocket.h"
#include "ListeningSocket.h"
#include "InitDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatSvrDlg dialog

CChatSvrDlg::CChatSvrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatSvrDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChatSvrDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pSocket = NULL;
}

void CChatSvrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatSvrDlg)
	DDX_Control(pDX, IDC_LIST_MSGS, m_ctrlMsgs);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChatSvrDlg, CDialog)
	//{{AFX_MSG_MAP(CChatSvrDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatSvrDlg message handlers

BOOL CChatSvrDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	//弹出初始话对话框
	CInitDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		//创建监听套节字
		m_pSocket = new CListeningSocket(this);
		if (m_pSocket->Create(dlg.m_nPort+700))
		{
			if (m_pSocket->Listen())
				return TRUE;
		}
		else
			return FALSE;
	}
	else
		return FALSE;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChatSvrDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChatSvrDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChatSvrDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//更新所有客户端
void CChatSvrDlg::UpdateClients(char* buffer,int nBufferSize)
{
	for(POSITION pos = m_connectionList.GetHeadPosition(); pos != NULL;)
	{
		//将新信息发送给每个客户端
		CClientSocket* pSocket = (CClientSocket*)m_connectionList.GetNext(pos);
		if (buffer != NULL)
			pSocket->Send(buffer,nBufferSize,0);
	}
}

//处理客户端的连接信息
void CChatSvrDlg::ProcessPendingAccept() 
{
	//生成一个新的套节字与客户端通讯
	CClientSocket* pSocket = new CClientSocket(this);

	if (m_pSocket->Accept(*pSocket))
	{
		//将该套节字保存起来
		m_connectionList.AddTail(pSocket);
	}
	else
		delete pSocket;
}

//接收数据
void CChatSvrDlg::ProcessPendingRead(CClientSocket* pSocket)
{
	//定义缓冲区
	char buffer[BUFFER_SIZE];

	//接收数据
	int nReceived = pSocket->Receive(buffer,BUFFER_SIZE,0);
	buffer[nReceived] = 0;

	//将数据在列表框中显示出来
	m_ctrlMsgs.AddString(buffer);

	//将数据发送给每个客户
	UpdateClients(buffer,nReceived);
}

void CChatSvrDlg::OnDestroy() 
{
	delete m_pSocket;
	CDialog::OnDestroy();	
}
