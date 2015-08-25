; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCapAudioDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CapAudio.h"

ClassCount=3
Class1=CCapAudioApp
Class2=CCapAudioDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_CAPAUDIO_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDR_MENU1

[CLS:CCapAudioApp]
Type=0
HeaderFile=CapAudio.h
ImplementationFile=CapAudio.cpp
Filter=N

[CLS:CCapAudioDlg]
Type=0
HeaderFile=CapAudioDlg.h
ImplementationFile=CapAudioDlg.cpp
Filter=D
LastObject=CCapAudioDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=CapAudioDlg.h
ImplementationFile=CapAudioDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CAPAUDIO_DIALOG]
Type=1
Class=CCapAudioDlg
ControlCount=0

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_MENUITEM_StartView
Command2=ID_MENUITEM_StopView
Command3=ID_MENUITEM_StartCapture
Command4=ID_MENUITEM_StopCapture
CommandCount=4

