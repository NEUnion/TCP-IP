
// TCPServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TCPServer.h"
#include "TCPServerDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTCPServerDlg 对话框




CTCPServerDlg::CTCPServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTCPServerDlg::IDD, pParent)
	, senddata(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTCPServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_BUTTON1, m_button);
	DDX_Text(pDX, IDC_EDIT1, senddata);

}

BEGIN_MESSAGE_MAP(CTCPServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_BUTTON2, &CTCPServerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CTCPServerDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CTCPServerDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CTCPServerDlg 消息处理程序

BOOL CTCPServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	m_list.InsertColumn(0,"消息");
	m_list.SetColumnWidth(0,550);
	m_edit.SetLimitText(99);
	m_button.EnableWindow(false);
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested=MAKEWORD(2,2);
	err=WSAStartup(wVersionRequested,&wsaData);
	if(err!=0)
	{
			AfxMessageBox("加载WinSock失败");
	}
	//创建一个流套接字
	sockSrv=socket(AF_INET,SOCK_STREAM,0);
	if(sockSrv==INVALID_SOCKET)
	{
		AfxMessageBox("创建侦听套接字错误");
	}

		
	//设定地址，INADDR_ANY代表由系统随机指定一块网卡的地址
	const int DEFAULT_PORT=5000;
	
	SOCKADDR_IN serv;
	serv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	serv.sin_family=AF_INET;
	serv.sin_port=htons(DEFAULT_PORT); //htons函数进行字节顺序转换
	//addlen=sizeof(serv);
	//m_button.EnableWindow(FALSE);
	if (bind(sockSrv,(sockaddr*)&serv,sizeof(serv)))
	{
		AfxMessageBox("绑定错误");
		
	} 
	//开始侦听		
	listen(sockSrv,5);	
	//调用线程
	AfxBeginThread(&thread1,0);
	

	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTCPServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTCPServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTCPServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






//服务器线程
UINT CTCPServerDlg::thread1(LPVOID p)
{
	
		
	//通过accept函数接受客户端的连接请求

	SOCKADDR_IN addrClient;
	int len=sizeof(SOCKADDR);
	//dlg指向主对话框
	CTCPServerDlg *dlg=(CTCPServerDlg*)AfxGetApp()->GetMainWnd();

	while(1)
	{
		dlg->sockConn=accept(dlg->sockSrv,(SOCKADDR*)&addrClient,&len);
		if(dlg->sockConn==INVALID_SOCKET)
		{
			AfxMessageBox("accept()fail");
			break;
		}
		//char sendBuf[1024],hostname[100];
		/*if(gethostname(hostname,100)!=0)
			strcpy(hostname,"None");*/
		CString s;
		s.Format("%s connected me sucessfully!",inet_ntoa(addrClient.sin_addr));
		dlg->m_list.InsertItem(0,s);
		AfxBeginThread(&thread2,0);
	}
		
	//终止线程
	AfxEndThread(0);
	return 0;
} 

//服务器接收数据线程
UINT CTCPServerDlg::thread2(LPVOID p)
{
	
		
	
	//dlg指向主对话框
	while(1)
	{
		CTCPServerDlg *dlg=(CTCPServerDlg*)AfxGetApp()->GetMainWnd();

	
		int err;
		char receivedata[1024]="\0";
		err=recv(dlg->sockConn,receivedata,1024,0);
		if(err==SOCKET_ERROR)
		{
			AfxMessageBox("接收数据失败！");
			return -1;
		}
		dlg->m_list.InsertItem(0,receivedata);
	}
	
	
	//终止线程
	AfxEndThread(0);
	return 0;
} 

void CTCPServerDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CTCPServerDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if(senddata=="")
	{
		AfxMessageBox("请输入信息！");
		return;
	}
	
	//dlg指向主对话框
	CTCPServerDlg *dlg=(CTCPServerDlg*)AfxGetApp()->GetMainWnd();
	int err,iLen;
	err=send(dlg->sockConn,senddata,strlen(senddata)+1,0);
	if(err==SOCKET_ERROR)
	{
		AfxMessageBox("发送数据失败！");
		return;
	}
	dlg->m_list.InsertItem(0,senddata);
	senddata="";
	UpdateData(false);

}



void CTCPServerDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	
	UpdateData(true);
	if(senddata!="")
	{
		m_button.EnableWindow(true);
	}
	else m_button.EnableWindow(false);
	
}
