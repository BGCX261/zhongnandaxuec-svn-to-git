; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CShowContDB
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "listtest.h"
LastPage=0

ClassCount=10
Class1=CListTESTApp
Class2=CAboutDlg
Class3=CListTESTDlg
Class4=CLogin
Class5=CMainStuDlg
Class6=CModifPwd

ResourceCount=10
Resource1=IDD_DIA_STDMODIF
Resource2=IDD_MD_PWD
Resource3=IDD_ABOUTBOX
Resource4=IDD_DIALOG1
Resource5=IDD_DADD_STU
Resource6=IDD_DIA_MAIN
Class7=CAddStudenInf
Resource7=IDD_DLG_LOGIN
Class8=CSpeciDlg
Resource8=IDD_LISTTEST_DIALOG
Class9=CModifStudentInfo
Resource9=IDD_DLG_SPECI
Class10=CShowContDB
Resource10=IDR_MENU1

[CLS:CListTESTApp]
Type=0
BaseClass=CWinApp
HeaderFile=ListTEST.h
ImplementationFile=ListTEST.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ListTESTDlg.cpp
ImplementationFile=ListTESTDlg.cpp
LastObject=CAboutDlg

[CLS:CListTESTDlg]
Type=0
BaseClass=CDialog
HeaderFile=ListTESTDlg.h
ImplementationFile=ListTESTDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_LIST1

[CLS:CLogin]
Type=0
BaseClass=CDialog
HeaderFile=Login.h
ImplementationFile=Login.cpp

[CLS:CMainStuDlg]
Type=0
BaseClass=CDialog
HeaderFile=MainStuDlg.h
ImplementationFile=MainStuDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_BTPro

[CLS:CModifPwd]
Type=0
BaseClass=CDialog
HeaderFile=ModifPwd.h
ImplementationFile=ModifPwd.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_LISTTEST_DIALOG]
Type=1
Class=CListTESTDlg
ControlCount=10
Control1=IDC_LIST1,SysListView32,1350631425
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_COMBO1,combobox,1344340227
Control5=IDC_STATIC,static,1342308352
Control6=IDC_BTSERCH,button,1342242816
Control7=IDC_CHALL,button,1342242819
Control8=IDC_STATIC_SW,static,1073873408
Control9=IDC_BUT_ADDDL,button,1342242816
Control10=IDC_BT_CLEARALL,button,1342242816

[DLG:IDD_DLG_LOGIN]
Type=1
Class=CLogin
ControlCount=6
Control1=IDC_EUSER,edit,1350631552
Control2=IDC_EPWD,edit,1350631584
Control3=IDC_BT_LOG,button,1342242817
Control4=IDC_BT_CAN,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_DIA_MAIN]
Type=1
Class=CMainStuDlg
ControlCount=13
Control1=IDC_STATIC,static,1342177294
Control2=IDC_BTStu,button,1342275584
Control3=IDC_BTPro,button,1342275584
Control4=IDC_BTTer,button,1342275584
Control5=IDC_BTPwd,button,1342275584
Control6=IDC_BTCor,button,1342275584
Control7=IDC_STATIC,static,1342308864
Control8=IDC_STATIC,static,1342308864
Control9=IDC_STATIC,static,1342308864
Control10=IDC_STATIC,static,1342308864
Control11=IDC_STATIC,static,1342308864
Control12=IDC_BT_EXIT,button,1342275584
Control13=IDC_STATIC,static,1342308864

[DLG:IDD_MD_PWD]
Type=1
Class=CModifPwd
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631584
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT2,edit,1350631584
Control5=IDC_BUTOK,button,1342242816
Control6=IDC_BUTCAN,button,1342242816

[MNU:IDR_MENU1]
Type=1
Class=CListTESTDlg
Command1=IDCL_MENU_MODIF
Command2=IDCL_MENU_DELET
Command3=IDM_ADD_STUIF
CommandCount=3

[DLG:IDD_DADD_STU]
Type=1
Class=CAddStudenInf
ControlCount=27
Control1=IDC_EDIT_SID,edit,1350639744
Control2=IDC_EDIT_STNAME,edit,1350631552
Control3=IDC_RADIO_SEX,button,1342308361
Control4=IDC_RADIO2,button,1342177289
Control5=IDC_DT_BIRTH,SysDateTimePick32,1342242848
Control6=IDC_EDIT_ID,edit,1350631552
Control7=IDC_CMB_SPE,combobox,1344340227
Control8=IDC_COM_COLAGE,combobox,1344340227
Control9=IDC_DT_ENTRYTIME,SysDateTimePick32,1342242848
Control10=IDC_EDIT_NATIPLACE,edit,1350631552
Control11=IDC_EDIT_ADDR,edit,1350631552
Control12=IDC_BT_ADD,button,1342242817
Control13=IDC_BT_ACANCE,button,1342242816
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_CMB_SYMB,combobox,1344340227
Control25=IDC_STATIC,static,1342308352
Control26=IDC_EDIT_POSTCD,edit,1350631552
Control27=IDC_STATIC,static,1342308352

[CLS:CAddStudenInf]
Type=0
HeaderFile=AddStudenInf.h
ImplementationFile=AddStudenInf.cpp
BaseClass=CDialog
Filter=D
LastObject=CAddStudenInf
VirtualFilter=dWC

[DLG:IDD_DLG_SPECI]
Type=1
Class=CSpeciDlg
ControlCount=8
Control1=IDC_LTSHOW_SPE,SysListView32,1350631425
Control2=IDC_STATIC,static,1342308352
Control3=IDC_ETSERCH,edit,1350631552
Control4=IDC_COMSER_SPE,combobox,1344340226
Control5=IDC_STATIC,static,1342308352
Control6=IDC_BTSPESERCH,button,1342242816
Control7=IDC_BTSPE_ADD,button,1342242816
Control8=IDC_STATIC_SWSP,static,1073873408

[CLS:CSpeciDlg]
Type=0
HeaderFile=SpeciDlg.h
ImplementationFile=SpeciDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LTSHOW_SPE
VirtualFilter=dWC

[DLG:IDD_DIA_STDMODIF]
Type=1
Class=CModifStudentInfo
ControlCount=27
Control1=IDCANCEL,button,1342242816
Control2=IDC_EDITM_SID,edit,1350641792
Control3=IDC_EDITM_STNAME,edit,1350631552
Control4=IDC_RADIOM_SEX,button,1342308361
Control5=IDC_RADIO2,button,1342177289
Control6=IDC_DTM_BIRTH,SysDateTimePick32,1342242848
Control7=IDC_EDITM_ID,edit,1350631552
Control8=IDC_CMBM_SPE,combobox,1344340227
Control9=IDC_COMM_COLAGE,combobox,1344340227
Control10=IDC_DTM_ENTRYTIME,SysDateTimePick32,1342242848
Control11=IDC_EDITM_NATIPLACE,edit,1350631552
Control12=IDC_EDITM_ADDR,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_CMBM_SYMB,combobox,1344340227
Control24=IDC_STATIC,static,1342308352
Control25=IDC_EDITM_POSTCD,edit,1350631552
Control26=IDC_STATIC,static,1342308352
Control27=IDC_BT_UPDATE,button,1342242817

[CLS:CModifStudentInfo]
Type=0
HeaderFile=ModifStudentInfo.h
ImplementationFile=ModifStudentInfo.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CModifStudentInfo

[DLG:IDD_DIALOG1]
Type=1
Class=CShowContDB
ControlCount=2
Control1=IDC_PROGRESS1,msctls_progress32,1350565888
Control2=IDC_STATIC,static,1342308364

[CLS:CShowContDB]
Type=0
HeaderFile=ShowContDB.h
ImplementationFile=ShowContDB.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_PROGRESS1
VirtualFilter=dWC

