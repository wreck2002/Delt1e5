; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CJSQDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "JSQ.h"

ClassCount=4
Class1=CJSQApp
Class2=CJSQDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_JSQ_DIALOG
Class4=CDlgSet
Resource4=IDD_DIALOG_SET

[CLS:CJSQApp]
Type=0
HeaderFile=JSQ.h
ImplementationFile=JSQ.cpp
Filter=N
LastObject=CJSQApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CJSQDlg]
Type=0
HeaderFile=JSQDlg.h
ImplementationFile=JSQDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_HINTMESS

[CLS:CAboutDlg]
Type=0
HeaderFile=JSQDlg.h
ImplementationFile=JSQDlg.cpp
Filter=D
LastObject=IDC_VERSION
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_VERSION,static,1342308480
Control3=IDC_COPYRIGHT,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_JSQ_DIALOG]
Type=1
Class=CJSQDlg
ControlCount=35
Control1=IDOK,button,1342242817
Control2=IDC_EDIT_OUTPUT,edit,1352732676
Control3=IDC_EDIT_INPUT,edit,1350631552
Control4=IDC_BTN_ADD,button,1342242816
Control5=IDC_BTN_MINUS,button,1342242816
Control6=IDC_BTN_MULT,button,1342242816
Control7=IDC_BTN_DIV,button,1342242816
Control8=IDC_BTN_7,button,1342243584
Control9=IDC_BTN_8,button,1342243584
Control10=IDC_BTN_9,button,1342243584
Control11=IDC_BTN_4,button,1342242816
Control12=IDC_BTN_5,button,1342242816
Control13=IDC_BTN_6,button,1342242816
Control14=IDC_BTN_1,button,1342242816
Control15=IDC_BTN_2,button,1342242816
Control16=IDC_BTN_3,button,1342242816
Control17=IDC_BTN_CLEAR,button,1342242816
Control18=IDC_BTN_0,button,1342242816
Control19=IDC_BTN_FACTOR,button,1342242816
Control20=IDC_HINTMESS,edit,1350631552
Control21=IDC_STEPTIME,edit,1350631552
Control22=IDC_STOP,button,1342242816
Control23=IDC_REP_LOAD,button,1342242816
Control24=IDC_REP_SAVE,button,1342242816
Control25=IDC_MOD,button,1342242816
Control26=IDC_REP10,button,1342242816
Control27=IDC_MSAVE,button,1342242816
Control28=IDC_MR,button,1342242816
Control29=ID_CAP_DELT,button,1342242816
Control30=ID_PRIME_SEARCH,button,1342242816
Control31=IDC_SQRT,button,1342242816
Control32=IDC_BUTTON_SET,button,1342242816
Control33=IDC_BUTTON_SQR,button,1342242816
Control34=IDC_BUTTON_POWER,button,1342242816
Control35=IDC_JSQ_EXTEND,button,1342242816

[DLG:IDD_DIALOG_SET]
Type=1
Class=CDlgSet
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_NeedCacu,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[CLS:CDlgSet]
Type=0
HeaderFile=DlgSet.h
ImplementationFile=DlgSet.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_NeedCacu
VirtualFilter=dWC

