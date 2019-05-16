
// TCPServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TCPServer.h"
#include "TCPServerDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTCPServerDlg �Ի���




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


// CTCPServerDlg ��Ϣ�������

BOOL CTCPServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	m_list.InsertColumn(0,"��Ϣ");
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
			AfxMessageBox("����WinSockʧ��");
	}
	//����һ�����׽���
	sockSrv=socket(AF_INET,SOCK_STREAM,0);
	if(sockSrv==INVALID_SOCKET)
	{
		AfxMessageBox("���������׽��ִ���");
	}

		
	//�趨��ַ��INADDR_ANY������ϵͳ���ָ��һ�������ĵ�ַ
	const int DEFAULT_PORT=5000;
	
	SOCKADDR_IN serv;
	serv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	serv.sin_family=AF_INET;
	serv.sin_port=htons(DEFAULT_PORT); //htons���������ֽ�˳��ת��
	//addlen=sizeof(serv);
	//m_button.EnableWindow(FALSE);
	if (bind(sockSrv,(sockaddr*)&serv,sizeof(serv)))
	{
		AfxMessageBox("�󶨴���");
		
	} 
	//��ʼ����		
	listen(sockSrv,5);	
	//�����߳�
	AfxBeginThread(&thread1,0);
	

	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTCPServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTCPServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






//�������߳�
UINT CTCPServerDlg::thread1(LPVOID p)
{
	
		
	//ͨ��accept�������ܿͻ��˵���������

	SOCKADDR_IN addrClient;
	int len=sizeof(SOCKADDR);
	//dlgָ�����Ի���
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
		
	//��ֹ�߳�
	AfxEndThread(0);
	return 0;
} 

//���������������߳�
UINT CTCPServerDlg::thread2(LPVOID p)
{
	
		
	
	//dlgָ�����Ի���
	while(1)
	{
		CTCPServerDlg *dlg=(CTCPServerDlg*)AfxGetApp()->GetMainWnd();

	
		int err;
		char receivedata[1024]="\0";
		err=recv(dlg->sockConn,receivedata,1024,0);
		if(err==SOCKET_ERROR)
		{
			AfxMessageBox("��������ʧ�ܣ�");
			return -1;
		}
		dlg->m_list.InsertItem(0,receivedata);
	}
	
	
	//��ֹ�߳�
	AfxEndThread(0);
	return 0;
} 

void CTCPServerDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}


void CTCPServerDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if(senddata=="")
	{
		AfxMessageBox("��������Ϣ��");
		return;
	}
	
	//dlgָ�����Ի���
	CTCPServerDlg *dlg=(CTCPServerDlg*)AfxGetApp()->GetMainWnd();
	int err,iLen;
	err=send(dlg->sockConn,senddata,strlen(senddata)+1,0);
	if(err==SOCKET_ERROR)
	{
		AfxMessageBox("��������ʧ�ܣ�");
		return;
	}
	dlg->m_list.InsertItem(0,senddata);
	senddata="";
	UpdateData(false);

}



void CTCPServerDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	UpdateData(true);
	if(senddata!="")
	{
		m_button.EnableWindow(true);
	}
	else m_button.EnableWindow(false);
	
}
