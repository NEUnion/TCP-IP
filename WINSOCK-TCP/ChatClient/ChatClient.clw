; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSetupDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ChatClient.h"

ClassCount=5
Class1=CChatClientApp
Class2=CChatClientDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_CHATCLIENT_DIALOG
Resource2=IDR_MAINFRAME
Class4=CChatSocket
Resource3=IDD_ABOUTBOX
Class5=CSetupDlg
Resource4=IDD_SETUP

[CLS:CChatClientApp]
Type=0
HeaderFile=ChatClient.h
ImplementationFile=ChatClient.cpp
Filter=N

[CLS:CChatClientDlg]
Type=0
HeaderFile=ChatClientDlg.h
ImplementationFile=ChatClientDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CChatClientDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=ChatClientDlg.h
ImplementationFile=ChatClientDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CHATCLIENT_DIALOG]
Type=1
Class=CChatClientDlg
ControlCount=4
Control1=IDC_LIST_MSGS,listbox,1353777409
Control2=IDC_MSG,edit,1350631552
Control3=IDC_SEND,button,1342242817
Control4=IDC_STATIC,static,1342308352

[CLS:CChatSocket]
Type=0
HeaderFile=ChatSocket.h
ImplementationFile=ChatSocket.cpp
BaseClass=CSocket
Filter=N
LastObject=CChatSocket
VirtualFilter=uq

[DLG:IDD_SETUP]
Type=1
Class=CSetupDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_NAME,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_SERVER,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_PORT,edit,1350631552
Control8=IDC_STATIC,static,1342308352

[CLS:CSetupDlg]
Type=0
HeaderFile=SetupDlg.h
ImplementationFile=SetupDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

