// ChatClientDlg.cpp : implementation file
// Download by http://www.codefans.net

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"
#include "ChatSocket.h"
#include "SetupDlg.h"

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
// CChatClientDlg dialog

CChatClientDlg::CChatClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChatClientDlg)
	m_strMsg = _T("");
	m_strClientName = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatClientDlg)
	DDX_Control(pDX, IDC_LIST_MSGS, m_ctrlMsgs);
	DDX_Text(pDX, IDC_MSG, m_strMsg);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChatClientDlg, CDialog)
	//{{AFX_MSG_MAP(CChatClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, OnSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatClientDlg message handlers

BOOL CChatClientDlg::OnInitDialog()
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
	

	//显示登录对话框
	CSetupDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		//创建一个新的Socket
		m_pSocket = new CChatSocket(this);
		
		if (!m_pSocket->Create())
		{
			delete m_pSocket;
			m_pSocket = NULL;
			AfxMessageBox("create socket failed");
			return FALSE;
		}
		
		//连接服务器
		while (!m_pSocket->Connect(dlg.m_strServer,dlg.m_nPort + 700))
		{
			if (AfxMessageBox("Failed to connect to server\nTry again?",MB_YESNO) == IDNO)
			{
				delete m_pSocket;
				m_pSocket = NULL;
				return FALSE;
			}
		}
		m_strClientName = dlg.m_strName;
	}
	else
		return FALSE;

	//发送登录消息给服务器
	SendMsg("进入聊天室");
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChatClientDlg::OnPaint() 
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
HCURSOR CChatClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//接收数据
void CChatClientDlg::ProcessPendingRead()
{
	//定义缓冲区
	char buffer[BUFFER_SIZE];

	//接收数据
	int nReceived = m_pSocket->Receive(buffer,BUFFER_SIZE,0);
	buffer[nReceived] = 0;
	
	//将数据在列表框中显示出来
	CString str;
	str.Format("%s",buffer);
	m_ctrlMsgs.AddString(str);
}

void CChatClientDlg::OnSend() 
{
	UpdateData(TRUE);
	SendMsg(m_strMsg);
}

//发送数据到服务器
void CChatClientDlg::SendMsg(CString strMsg)
{
	CString str;
	str.Format("%s:%s",m_strClientName,strMsg);
	m_pSocket->Send(str.GetBuffer(0),str.GetLength(),0);
}
