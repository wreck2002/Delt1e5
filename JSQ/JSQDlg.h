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
	/*****������Ĵ���Ϊ����Delt(10, p)��*/////////////
	void OnTimerDelt();
//	int m_nMinAddDelt;
	CString m_strStartNum;//��ʼ�������
	CString m_strEndNum;//ֹͣ�������
	BOOL m_bShowHint;//�Ƿ���ʵ��ʾ��Ϣ(������ʾDelt(a)>1e4ʱ��a)
	/************************************//////////////

	BOOL FactorSec();
	BOOL OnDigitInput(CString strDigit);
	CFile m_file;
//	BOOL m_bOpenedFile;//�ļ��Ƿ��Ѿ���
	CString strInput1;//��һ��������ַ���
	CString strInput2;//�ڶ���������ַ���
	int nOperateType;//��������
	int nKillTime;//��ʱ
	int NeedCacu;//�Ƿ���Ҫ��ʼ����,121��ʾ����Delt(��ʱ������),122��ʾ���̼߳���Delt
	BOOL IsInCacu;//�Ƿ����ڼ��㣬��ʱ��һ�μ��㲻�ܿ�ʼ

	CJSQDlg(CWnd* pParent = NULL);	// standard constructor
	MyMath nToFactor;

	//////////////////////////////////////////////////////////////////////////
	//��������������������˵��
	//����Ŀǰ��JSQ.exe������Ҫ���ڼ���һ��������Deltֵ������
	//��Ҫ����nMemory��nMemory2������
	//nMemory���ڴ洢��������е�����������ÿ�μ��������
	//nMemory�����ڱ仯�ģ�һ������nMemory��ȡ�����е�������
	//��nMemory2�����ڵ��μ��������ȿ�ʼ����ʱ��ֵ���������ֵ��δ��ֹͣʱ������
	//�����    (2007-01-31 15:05)
	MyMath nMemory;//������
	MyMath nMemory2;//������2

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
	
	//�˱���רΪ����Delt(p)<1e4׼���������㵥��������ʱ��
	DWORD dwTickFlash[2];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JSQDLG_H__6240295F_AEAF_45AC_A632_BC2A0885ADB3__INCLUDED_)
