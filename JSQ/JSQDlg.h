// JSQDlg.h : header file
//

#if !defined(AFX_JSQDLG_H__6240295F_AEAF_45AC_A632_BC2A0885ADB3__INCLUDED_)
#define AFX_JSQDLG_H__6240295F_AEAF_45AC_A632_BC2A0885ADB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CJSQDlg dialog
#include "MyMath.h"

extern DWORD g_tickFlash[2];

class CJSQDlg : public CDialog
{
// Construction
public:
	BOOL Euler6(int nBounds);
	BOOL GetDeltDistance();
	/*****这里面的代码为计算Delt(10, p)用*/////////////
	void OnTimerDelt();
//	int m_nMinAddDelt;
	CString m_strStartNum;//开始计算的数
	CString m_strEndNum;//停止计算的数
	BOOL m_bShowHint;//是否现实提示信息(用于提示Delt(a)>1e4时的a)
	/************************************//////////////

	BOOL FactorSec();
	BOOL OnDigitInput(CString strDigit);
	CFile m_file;
//	BOOL m_bOpenedFile;//文件是否已经打开
	CString strInput1;//第一个输入的字符串
	CString strInput2;//第二个输入的字符串
	int nOperateType;//运算类型
	int nKillTime;//耗时
	int NeedCacu;//是否需要开始计算,121表示计算Delt(定时器计算),122表示用线程计算Delt
	BOOL IsInCacu;//是否正在计算，此时下一次计算不能开始

	CJSQDlg(CWnd* pParent = NULL);	// standard constructor
	MyMath nToFactor;

	//////////////////////////////////////////////////////////////////////////
	//对以下两个备用数稍作说明
	//由于目前本JSQ.exe程序主要用于计算一个素数的Delt值，所以
	//主要解释nMemory和nMemory2的区别
	//nMemory用于存储计算过程中的数，所以在每次计算过程中
	//nMemory都是在变化的，一般来讲nMemory会取遍所有的奇数。
	//而nMemory2则用于单次计算中最先开始计算时的值，所以这个值在未按停止时都会是
	//不变的    (2007-01-31 15:05)
	MyMath nMemory;//备用数
	MyMath nMemory2;//备用数2

// Dialog Data
	//{{AFX_DATA(CJSQDlg)
	enum { IDD = IDD_JSQ_DIALOG };
	CEdit	m_StepTime;
	CEdit	m_hintCtl;
	CEdit	m_strOutput;
	CEdit	m_strInput;
	CString	m_strHint;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJSQDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CJSQDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnClear();
	afx_msg void OnBtn0();
	afx_msg void OnBtn1();
	afx_msg void OnBtn2();
	afx_msg void OnBtn3();
	afx_msg void OnBtn4();
	afx_msg void OnBtn5();
	afx_msg void OnBtn6();
	afx_msg void OnBtn7();
	afx_msg void OnBtn8();
	afx_msg void OnBtn9();
	afx_msg void OnBtnMult();
	afx_msg void OnBtnFactor();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtnDiv();
	afx_msg void OnStop();
	afx_msg void OnRepLoad();
	afx_msg void OnRepSave();
	afx_msg void OnMod();
	afx_msg void OnRep10();
	afx_msg void OnBtnMinus();
	afx_msg void OnMsave();
	afx_msg void OnMr();
	afx_msg void OnCapDelt();
	afx_msg void OnPrimeSearch();
	afx_msg void OnDestroy();
	afx_msg void OnSqrt();
	afx_msg void OnButtonSet();
	afx_msg void OnButtonSqr();
	afx_msg void OnButtonPower();
	afx_msg void OnExtend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Test2();
	void Test();
	int GetTotalMSec(int nCurMSec);
	DWORD m_timeStart;
	BOOL IsNumber(CString str);
	CTime m_time;
	
	//此变量专为计算Delt(p)<1e4准备，即计算单步所花的时间
	DWORD dwTickFlash[2];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JSQDLG_H__6240295F_AEAF_45AC_A632_BC2A0885ADB3__INCLUDED_)
