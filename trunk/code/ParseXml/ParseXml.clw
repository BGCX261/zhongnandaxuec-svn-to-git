; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CParseXmlDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ParseXml.h"

ClassCount=3
Class1=CParseXmlApp
Class2=CParseXmlDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_PARSEXML_DIALOG

[CLS:CParseXmlApp]
Type=0
HeaderFile=ParseXml.h
ImplementationFile=ParseXml.cpp
Filter=N

[CLS:CParseXmlDlg]
Type=0
HeaderFile=ParseXmlDlg.h
ImplementationFile=ParseXmlDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_LIST_XML

[CLS:CAboutDlg]
Type=0
HeaderFile=ParseXmlDlg.h
ImplementationFile=ParseXmlDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PARSEXML_DIALOG]
Type=1
Class=CParseXmlDlg
ControlCount=2
Control1=IDC_STATIC,button,1342177287
Control2=IDC_LIST_XML,SysListView32,1350631437

