; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CInitDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ChatSvr.h"

ClassCount=6
Class1=CChatSvrApp
Class2=CChatSvrDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CClientSocket
Class4=CListeningSocket
Resource3=IDD_INIT
Class6=CInitDlg
Resource4=IDD_CHATSVR_DIALOG

[CLS:CChatSvrApp]
Type=0
HeaderFile=ChatSvr.h
ImplementationFile=ChatSvr.cpp
Filter=N

[CLS:CChatSvrDlg]
Type=0
HeaderFile=ChatSvrDlg.h
ImplementationFile=ChatSvrDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CChatSvrDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=ChatSvrDlg.h
ImplementationFile=ChatSvrDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CHATSVR_DIALOG]
Type=1
Class=CChatSvrDlg
ControlCount=1
Control1=IDC_LIST_MSGS,listbox,1353777409

[CLS:CListeningSocket]
Type=0
HeaderFile=ListeningSocket.h
ImplementationFile=ListeningSocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq
LastObject=CListeningSocket

[CLS:CClientSocket]
Type=0
HeaderFile=ClientSocket.h
ImplementationFile=ClientSocket.cpp
BaseClass=CSocket
Filter=N
LastObject=CClientSocket
VirtualFilter=uq

[DLG:IDD_INIT]
Type=1
Class=CInitDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[CLS:CInitDlg]
Type=0
HeaderFile=InitDlg.h
ImplementationFile=InitDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CInitDlg

