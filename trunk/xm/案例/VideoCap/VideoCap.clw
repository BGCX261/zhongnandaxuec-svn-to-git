; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CVideoCapDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "VideoCap.h"

ClassCount=3
Class1=CVideoCapApp
Class2=CVideoCapDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_VIDEOCAP_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDR_MENU1

[CLS:CVideoCapApp]
Type=0
HeaderFile=VideoCap.h
ImplementationFile=VideoCap.cpp
Filter=N

[CLS:CVideoCapDlg]
Type=0
HeaderFile=VideoCapDlg.h
ImplementationFile=VideoCapDlg.cpp
Filter=D
LastObject=ID_MENUITEM_PREVIEW_START
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=VideoCapDlg.h
ImplementationFile=VideoCapDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_VIDEOCAP_DIALOG]
Type=1
Class=CVideoCapDlg
ControlCount=0

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_MENUITEM_PREVIEW_START
Command2=ID_MENUITEM_PREVIEW_STOP
Command3=ID_MENUITEM_CAP_START
Command4=ID_MENUITEM_CAP_STOP
CommandCount=4

