; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDLGChat
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Chat.h"

ClassCount=4
Class1=CChatApp
Class2=CChatDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_CHAT_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=CDLGChat
Resource4=IDD_DIALOG_CHAT

[CLS:CChatApp]
Type=0
HeaderFile=Chat.h
ImplementationFile=Chat.cpp
Filter=N

[CLS:CChatDlg]
Type=0
HeaderFile=ChatDlg.h
ImplementationFile=ChatDlg.cpp
Filter=D
LastObject=CChatDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=ChatDlg.h
ImplementationFile=ChatDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CHAT_DIALOG]
Type=1
Class=CChatDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_CHAT]
Type=1
Class=CDLGChat
ControlCount=6
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,button,1342177287
Control3=IDC_BTN_SEND,button,1342242817
Control4=IDC_EDIT_RECV,edit,1350631620
Control5=IDC_IPADDR_SEND,SysIPAddress32,1342242816
Control6=IDC_EDIT_SEND,edit,1350631552

[CLS:CDLGChat]
Type=0
HeaderFile=DLGChat.h
ImplementationFile=DLGChat.cpp
BaseClass=CDialog
Filter=D
LastObject=CDLGChat
VirtualFilter=dWC

