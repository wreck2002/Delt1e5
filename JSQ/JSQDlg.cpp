// JSQDlg.cpp : implementation file
//

#include "stdafx.h"
#include "JSQ.h"
#include "JSQDlg.h"
#include "MyMath.h"
#include "Version.h"
#include "DlgSet.h"
#include "Euler.h"

#include "windows.h"
#include "process.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_strVersion;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT

	//��ʼ���汾��Ϣ
	CVersion wkVersion;
	m_strVersion.Format(_T("JSQ %s ��"), wkVersion.m_strVersion);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_VERSION, m_strVersion);
	DDV_MaxChars(pDX, m_strVersion, 500);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

DWORD g_tickFlash[2];

/////////////////////////////////////////////////////////////////////////////
// CJSQDlg dialog

CJSQDlg::CJSQDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CJSQDlg::IDD, pParent)
{
	
	//{{AFX_DATA_INIT(CJSQDlg)
	m_strHint = _T("��ʾ��Ϣ");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	strInput1 = "";
	strInput2 = "";
	nOperateType = -1;
	
//	nReserved = 0;

	NeedCacu = FALSE;
	nKillTime = 0;
	//nToBeFactor = 10;
	IsInCacu = FALSE;
	

	//ע��: ���ڹ涨m_nMinAddDelt����Ϊ2�����Ծ�Ҫ�������������Ϊ
	//      ������ע��!
	//�������: 2006-03-15 22:07
//	m_nMinAddDelt = 2;//2005-01-20 19:51
	
	m_timeStart = 0;//2005-05-22 09:03

	m_bShowHint = TRUE;//2006-02-22 21:27

	

}

void CJSQDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJSQDlg)
	DDX_Control(pDX, IDC_STEPTIME, m_StepTime);
	DDX_Control(pDX, IDC_HINTMESS, m_hintCtl);
	DDX_Control(pDX, IDC_EDIT_OUTPUT, m_strOutput);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_strInput);
	DDX_Text(pDX, IDC_HINTMESS, m_strHint);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CJSQDlg, CDialog)
	//{{AFX_MSG_MAP(CJSQDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClear)
	ON_BN_CLICKED(IDC_BTN_0, OnBtn0)
	ON_BN_CLICKED(IDC_BTN_1, OnBtn1)
	ON_BN_CLICKED(IDC_BTN_2, OnBtn2)
	ON_BN_CLICKED(IDC_BTN_3, OnBtn3)
	ON_BN_CLICKED(IDC_BTN_4, OnBtn4)
	ON_BN_CLICKED(IDC_BTN_5, OnBtn5)
	ON_BN_CLICKED(IDC_BTN_6, OnBtn6)
	ON_BN_CLICKED(IDC_BTN_7, OnBtn7)
	ON_BN_CLICKED(IDC_BTN_8, OnBtn8)
	ON_BN_CLICKED(IDC_BTN_9, OnBtn9)
	ON_BN_CLICKED(IDC_BTN_MULT, OnBtnMult)
	ON_BN_CLICKED(IDC_BTN_FACTOR, OnBtnFactor)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_DIV, OnBtnDiv)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_REP_LOAD, OnRepLoad)
	ON_BN_CLICKED(IDC_REP_SAVE, OnRepSave)
	ON_BN_CLICKED(IDC_MOD, OnMod)
	ON_BN_CLICKED(IDC_REP10, OnRep10)
	ON_BN_CLICKED(IDC_BTN_MINUS, OnBtnMinus)
	ON_BN_CLICKED(IDC_MSAVE, OnMsave)
	ON_BN_CLICKED(IDC_MR, OnMr)
	ON_BN_CLICKED(ID_CAP_DELT, OnCapDelt)
	ON_BN_CLICKED(ID_PRIME_SEARCH, OnPrimeSearch)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SQRT, OnSqrt)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_SQR, OnButtonSqr)
	ON_BN_CLICKED(IDC_BUTTON_POWER, OnButtonPower)
	ON_BN_CLICKED(IDC_JSQ_EXTEND, OnExtend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJSQDlg message handlers

BOOL CJSQDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	SetTimer(1,2000,NULL); //Warning: nElapse must bigger than 5
//	m_ptime = new CTime();

//	m_bOpenedFile = FALSE;

	//m_strInput.SetWindowText(_T("Test"));

	//��m_nPrime25��ʼ��
	int nCount = 0;
	int i = 0;
	int j = 0;
	BOOL bPrime = TRUE;
	m_nPrime25[0] = 2;
	nCount = 1;
	for(i=3;i<1000000;i+=2)
	{
		bPrime = TRUE;
		for(j = 2; j <= sqrt((double)i); j++)
		{
			if(i%j==0)
			{
				bPrime = FALSE;
				break;
			}
		}

		if(bPrime)
		{
			m_nPrime25[nCount] = i;
			nCount++;
		}
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CJSQDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CJSQDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CJSQDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CJSQDlg::OnOK() 
{
	CString strResult = _T("");
	CString strTemp = _T("");
	BOOL bIsSigOperate = FALSE;//�Ƿ��ǵ�Ŀ�������ֻ��һ������
	int nPos1 = 0;//'('�������ַ����г��ֵ�λ��
	int nPos2 = 0;//')'�������ַ����г��ֵ�λ��
	MyMath myM1;
	g_tickFlash[0] = GetTickCount();

	//������ط�����������ַ����Ƿ�Ϊ������
	m_strInput.GetWindowText(strTemp);
	nPos1 = strTemp.Find('(',0);
	nPos2 = strTemp.Find(')',0);
	if(nPos1>=0 && nPos2>=0)
	{
		strTemp = strTemp.Left(nPos1);
		if(strTemp.Compare("gcd")==0)
		{
			//�����Լ��
			nOperateType = OP_CACU_GCD;
		}
		else if(strTemp.Compare("phi")==0)
		{
			//�����������
			nOperateType = OP_CACU_PHI;
		}
		else if(strTemp.Compare("Delt")==0)
		{
			//����Delt
			nOperateType = OP_CACU_DELT;
		}
	}


	if(nOperateType<0)
		return;
	
	m_strInput.GetWindowText(strInput2);

	//���������Լ��ʱ���������Ҫ�ӱ��ʽ�н���
	if(nOperateType==OP_CACU_GCD)
	{
		int nPos3 = 0;//',��λ��
		m_strInput.GetWindowText(strTemp);
		strInput1 = strTemp.Left(nPos2);
		strTemp = strInput1.Right(strInput1.GetLength()-nPos1-1);
		nPos3 = strTemp.Find(',',0);

		strInput1 = strTemp.Left(nPos3);
		strInput2 = strTemp.Right(strTemp.GetLength()-nPos3-1);
	}
	else if(nOperateType==OP_CACU_PHI || nOperateType==OP_CACU_DELT)
	{
		bIsSigOperate = TRUE;
		strInput1 = strInput2.Left(nPos2);
		strInput1 = strInput1.Right(nPos2-nPos1-1);
	}


	if( !IsNumber(strInput1) )
	{
		m_strOutput.SetWindowText(_T("����ĵ�һ�����ֱ���Ϊ����������!"));
			return;
	}

	if( !bIsSigOperate && !IsNumber(strInput1))
	{
		m_strOutput.SetWindowText(_T("����ڶ������ֱ���Ϊ����������!"));
			return;
	}

	switch(nOperateType)
	{
	case OP_CACU_ADD://��
		{
			CString strAddResult = _T("");//�洢������
			CString strAddResult2 = _T("");
			
			strResult+=strInput1;
			strResult+=_T("+");
			strResult+=strInput2;
			strResult+=_T("=\r\n");
			
			
			//���ж�λ��
			if(!myM1.fza(strInput1)
				|| !myM1.fzb(strInput2))
			{
				strResult.Format(_T("�������ִ��ڴ���!\r\n myM1.m_strError=%s"), 
					myM1.m_strError);
				m_strOutput.SetWindowText(strResult);
				return;
			}
			
			myM1.JSQADD();
			strAddResult = myM1.GetResult();
			strAddResult2.Format(_T("%s (%d digit)"), 
				strAddResult, myM1.GetDigit(myM1.nRes));
			
			
			strResult+=strAddResult2;
			m_strOutput.SetWindowText(strResult);
			m_strInput.SetWindowText(strAddResult);
		}
		break;
	case OP_CACU_MINUS://��
		{
			CString strMinusResult = _T("");//�洢������
			CString strMinusResult2 = _T("");
			BOOL bMinus = FALSE;
			strResult+=strInput1;
			strResult+=_T(" - ");
			strResult+=strInput2;
			strResult+=_T("\r\n = ");
			
			//���ж�λ��
			if(!myM1.fza(strInput1)
				|| !myM1.fzb(strInput2))
			{
				strResult.Format(_T("�������ִ��ڴ���!\r\n myM1.m_strError=%s"), 
					myM1.m_strError);
				m_strOutput.SetWindowText(strResult);
				return;
			}

			if(myM1.Compare(myM1.a, myM1.b)<0)
			{
				myM1.fza(strInput2);
				myM1.fzb(strInput1);
				bMinus = TRUE;
			}

			if(myM1.JSQMINUS())
			{
				if(bMinus)
				{
					strResult = strResult+"-";
				}
				strMinusResult = myM1.GetResult();
				strMinusResult2.Format(_T("%s (%d digit)"), 
					strMinusResult, myM1.GetDigit(myM1.nRes));
				
				
				strResult+=strMinusResult2;
				
				m_strOutput.SetWindowText(strResult);
				m_strInput.SetWindowText(myM1.GetResult());
			}
			else
			{
				m_strOutput.SetWindowText(_T("��������"));
				return;
			}
		}
		break;
	case OP_CACU_MULT://��
		//���ж�λ��
		if(!myM1.fza(strInput1)
			|| !myM1.fzb(strInput2))
		{
			strResult.Format(_T("�������ִ��ڴ���!\r\n myM1.m_strError=%s"), 
				myM1.m_strError);
			m_strOutput.SetWindowText(strResult);
			return;
		}
		if(!myM1.PreMult())
		{
			m_strOutput.SetWindowText(myM1.m_strError);
			return;
		}
		myM1.JSQMULT();
		strResult.Format(_T("%s �� %s\r\n= %s (%d digit)"), 
			strInput1, strInput2, myM1.GetResult(),
			myM1.GetDigit(myM1.nRes));
		m_strOutput.SetWindowText(strResult);
		m_strInput.SetWindowText(myM1.GetResult());
		break;
	case OP_CACU_DIV://��
		//���ж�λ��
		if(!myM1.fza(strInput1)
			|| !myM1.fzb(strInput2))
		{
			strResult.Format(_T("�������ִ��ڴ���!\r\n myM1.m_strError=%s"), 
				myM1.m_strError);
			m_strOutput.SetWindowText(strResult);
			return;
		}

		//��������Ϊ��
		if(myM1.b[0]==1 && myM1.b[1]==0)
		{
			m_strOutput.SetWindowText(_T("����������Ϊ0!"));
			return;
		}
		if(!myM1.JSQDIV())
		{
			m_strOutput.SetWindowText(_T("��������г���!"));
			return;
		}
		strResult.Format( _T("%s / %s = \r\n\
���Ϊ %s  (%d digit)\r\n����Ϊ %s (%d digit)"), 
			strInput1, strInput2, 
			myM1.GetResultMy(myM1.c),
			myM1.GetDigit(myM1.c),
			myM1.GetResultMy(myM1.d),
			myM1.GetDigit(myM1.d));

		m_strOutput.SetWindowText(strResult);
		m_strInput.SetWindowText(myM1.GetResultMy(myM1.c));

		strInput1 = myM1.GetResultMy(myM1.c);
		break;
	case OP_CACU_POWER://��
		//���ж�λ��
		if(!myM1.fza(strInput1)
			|| !myM1.fzb(strInput2))
		{
			strResult.Format(_T("�������ִ��ڴ���!\r\n myM1.m_strError=%s"), 
				myM1.m_strError);
			m_strOutput.SetWindowText(strResult);
			return;
		}

		if( myM1.JSQPOWER() )
		{
			strResult.Format( _T("%s ^ %s\r\n= %s (%d digits)"),
				strInput1, strInput2, myM1.GetResult(),
				myM1.GetDigit(myM1.nRes));
		}
		else
		{
			strResult = myM1.m_strError;
		}
		m_strOutput.SetWindowText(strResult);
		break;
	case OP_CACU_MOD://����
		{
			//���ж�λ��
			CString strModResult = _T("");
			if(!myM1.fza(strInput1)
				|| !myM1.fzb(strInput2))
			{
				strResult.Format(_T("�������ִ��ڴ���!\r\n myM1.m_strError=%s"), 
					myM1.m_strError);
				m_strOutput.SetWindowText(strResult);
				return;
			}
			if(myM1.b[0]==1&&myM1.b[1]==0)
			{
				m_strOutput.SetWindowText("b����Ϊ0!");
				return;
			}
			myM1.JSQMOD();
			strResult+=strInput1;
			strResult+=_T(" mod ");
			strResult+=strInput2;
			strResult+=_T("\r\n = ");
			strModResult = myM1.GetResult();
			strResult+=strModResult;
			m_strOutput.SetWindowText(strResult);
			m_strInput.SetWindowText(strModResult);
		}
		break;
	case OP_CACU_GCD://�����Լ��
		{
			//���ж�λ��
			if(!myM1.fza(strInput1)
				|| !myM1.fzb(strInput2))
			{
				strResult.Format(_T("�������ִ��ڴ���!\r\n myM1.m_strError=%s"), 
					myM1.m_strError);
				m_strOutput.SetWindowText(strResult);
				return;
			}
			myM1.JSQGCD();

			strResult+=_T("gcd(");
			strResult+=strInput1;
			strResult+=_T(" , ");
			strResult+=strInput2;
			strResult+=_T(")\r\n = ");
			strResult+=myM1.GetResult();
			strResult+=_T("\r\n");
			strResult+=myM1.m_strError;
			m_strOutput.SetWindowText(strResult);
		}
		break;
	case OP_CACU_PHI:
		{
			BigNum nPhiA;
			BigNum nPhiN;
			BigNum nPhiResult;

			myM1.fza(strInput1);
			nPhiA.SetValue(10);
			myM1.fz(nPhiN.m_a, myM1.a);

			myM1.Power(&nPhiA, &nPhiN, &nPhiResult);
			strResult = _T("phi(");
			strResult += strInput1;
			strResult += _T(")=");
			strResult += myM1.GetResultMy(nPhiResult.m_a);
			m_strOutput.SetWindowText(strResult);
		}
		break;
	case OP_CACU_DELT:
		{
			BigNum nDeltA;
			BigNum nDeltN;
			BigNum nDeltResult;

			myM1.fza(strInput1);
			nDeltA.SetValue(10);
			myM1.JSQDELT();

			strResult = _T("Delt(");
			strResult += strInput1;
			strResult += _T(")=");
			strResult += myM1.GetResult();
			m_strOutput.SetWindowText(strResult);
		}
		break;
	default:
		break;
	}
	//strInput1 = _T("");
	//strInput2 = _T("");

	//����������ʱ��
	g_tickFlash[1] = GetTickCount();
	int nTempTime2 = (int)(g_tickFlash[1]-g_tickFlash[0]);
	CString strP;
	strP.Format(_T("%d"),nTempTime2);
	m_StepTime.SetWindowText(strP);
	
	
}


void CJSQDlg::OnBtnAdd() 
{
	m_strInput.GetWindowText(strInput1);
	nOperateType = 1;
	strInput2 = _T("0");
	//m_strInput.SetWindowText(_T("0"));
}

void CJSQDlg::OnBtnClear() 
{
	strInput1 = _T("");
	strInput2 = _T("");
	nOperateType = -1;
	m_strInput.SetWindowText(_T("0"));
	m_strOutput.SetWindowText(_T("0"));
	m_hintCtl.SetWindowText(_T("׼����ʼ�µļ���"));
	m_StepTime.SetWindowText( _T("0") );
	nKillTime = 0;
}


void CJSQDlg::OnBtn0() 
{
	OnDigitInput(_T("0"));	
}


void CJSQDlg::OnBtn1() 
{	
	OnDigitInput(_T("1"));
}

void CJSQDlg::OnBtn2() 
{
	OnDigitInput(_T("2"));
	
}

void CJSQDlg::OnBtn3() 
{
	OnDigitInput(_T("3"));
	
}

void CJSQDlg::OnBtn4() 
{
	OnDigitInput(_T("4"));
}

void CJSQDlg::OnBtn5() 
{
	OnDigitInput(_T("5"));
}

void CJSQDlg::OnBtn6() 
{
	OnDigitInput(_T("6"));
//	CString	strTimeCur;
//	
//	strTimeCur.Format(_T("[%04d-%02d-%02d %02d:%02d]"),
//			time.GetYear(),time.GetMonth(),time.GetDay(),
//			time.GetHour(),time.GetMinute());
//	CString strFilePrint;
//	strFilePrint.Format(_T("%s"), strTimeCur);
//	int nStrLen = strFilePrint.GetLength();
//	m_strOutput.SetWindowText(strFilePrint);

}


void CJSQDlg::OnBtn7() 
{
	OnDigitInput(_T("7"));
}

void CJSQDlg::OnBtn8() 
{
	OnDigitInput(_T("8"));
}

void CJSQDlg::OnBtn9() 
{
	OnDigitInput(_T("9"));
	
}


BOOL CJSQDlg::OnDigitInput(CString strDigit)
{
	if(nOperateType<0)
	{
		if( strInput1.GetLength()==1 && strcmp(strInput1, _T("0"))==0 )
			strInput1 = strDigit;
		else
			strInput1+=strDigit;
		m_strInput.SetWindowText(strInput1);
	}
	else
	{
		if( strInput2.GetLength()==1 && strcmp(strInput2, _T("0"))==0 )
			strInput2 = strDigit;
		else
			strInput2+=strDigit;
		m_strInput.SetWindowText(strInput2);
	}
	return TRUE;

}

void CJSQDlg::OnBtnMult() 
{
	m_strInput.GetWindowText(strInput1);
	nOperateType = 3;
	strInput2 = _T("0");
	//m_strInput.SetWindowText(_T("0"));
}

/**
 *	����Factor(p)���߳�
 *  �����void* p����Ǵ���ҳ���ָ�롣
 *  �������: 2009-08-15 09:57
 */
VOID ThreadProcFactor(void* p)
{
	CJSQApp *pApp = (CJSQApp *)p;
	CJSQDlg *pDlg = (CJSQDlg *)pApp->m_pJSQDlg;
	DWORD dwThreadHits = 0;
	int nTempTime = 0;
	//int i;
	do
	{
		g_tickFlash[0] = GetTickCount();
		
		pDlg->FactorSec();
		
		g_tickFlash[1] = GetTickCount();
		nTempTime = (int)(g_tickFlash[1]-g_tickFlash[0]);
		CString strP;
		strP.Format(_T("%d"),nTempTime);
		pDlg->m_StepTime.SetWindowText(strP);
		
		pDlg->nKillTime += nTempTime;

		if(pDlg->NeedCacu!=NC_FACTOR)
		{
			break;
		}
		
	}while(TRUE);//Ѳ��1000��
} // VOID ThreadProc(void* p)


void CJSQDlg::OnBtnFactor() 
{
	CString strResult = _T("");
	m_strInput.GetWindowText(strInput1);
	strResult+=strInput1;
	strResult+="\r\n = ";
	nKillTime = 0;
	

	nToFactor.fza(strInput1);

	//���������С�ڻ������ʱֱ�ӷ���
	if( nToFactor.Compare(nToFactor.a, nToFactor.m_ZERO)<=0 )
	{
		AfxMessageBox( _T("������һ����0������") );
		return;
	}

	if(!nToFactor.FactorPrepare())
	{
		AfxMessageBox( _T("׼������!") );
		return;
	}

	int cacuResult = nToFactor.Factor();
	if(cacuResult!=10)
	{//������ڼ���
		if(cacuResult==1)
		{
			strResult+=nToFactor.strR;
			strResult+=_T("��");
			m_strOutput.SetWindowText(strResult);
			NeedCacu = TRUE;
			//return;
		}
		else
		{
			m_strOutput.SetWindowText(strResult);
			NeedCacu = TRUE;
		}
	}
	else
	{
		strResult+=nToFactor.strR;
		m_strOutput.SetWindowText(strResult);
		NeedCacu = FALSE;
		return;//���������
	}

	m_strOutput.SetWindowText(strResult);


	CJSQApp *pApp = (CJSQApp *)AfxGetApp();
	DWORD tid;
	DWORD dw = IDLE_PRIORITY_CLASS;

	HANDLE _hThread;

	_hThread = CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)ThreadProcFactor,
		pApp,
		dw,//CREATE_SUSPENDED,
		&tid);
	
	//�˴���Ҫ�������̵߳ĵȼ���ñȽϵ͡�
	//THREAD_PRIORITY_LOWEST
	//SetThreadPriority(_hThread, THREAD_PRIORITY_LOWEST);
	SetThreadPriority(_hThread, THREAD_PRIORITY_IDLE);

}

LRESULT CJSQDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch(message)
	{
	case MSG_USER_FACTOR:
		FactorSec();
		break;
	case MSG_USER_STOP:
		OnStop();
		break;
	default:
		break;
	}
	return CDialog::WindowProc(message, wParam, lParam);
}

BOOL CJSQDlg::FactorSec()
{
	CString strResult = _T("");
	m_strOutput.GetWindowText(strResult);
	CString strHint;

	int cacuResult = nToFactor.Factor();
	if(cacuResult!=10)
	{//������ڼ���
		if(cacuResult==1)
		{
			strResult+=nToFactor.strR;
			strResult+=_T("��");
			m_strOutput.SetWindowText(strResult);
		}
		CString strH2;
		strH2 = nToFactor.GetResultMy(nToFactor.b);
		strHint.Format(_T("������ʱ�� %d ms! ��ʱb = "),nKillTime);
		strHint+=strH2;
		m_hintCtl.SetWindowText(strHint);
		return TRUE;
	}
	else
	{
		strResult+=nToFactor.strR;
		m_strOutput.SetWindowText(strResult);

		strHint.Format(_T("��������ʱ�� %d ms!     �����ѽ���!"),nKillTime);
		m_hintCtl.SetWindowText(strHint);

		NeedCacu = FALSE;
	}
	
	return TRUE;

}

void CJSQDlg::OnTimer(UINT nIDEvent) 
{
	g_tickFlash[0]=GetTickCount();
	switch(nIDEvent)
	{
	case(NC_FACTOR)://�任ͼ��
		if(NeedCacu==1 && 1>2)
		{
			if(!IsInCacu)
			{
				IsInCacu = TRUE;
				FactorSec();
				IsInCacu = FALSE;
				g_tickFlash[1] = GetTickCount();
				int nTempTime = (int)(g_tickFlash[1]-g_tickFlash[0]);
				CString strP;
				strP.Format(_T("%d"),nTempTime);
				m_StepTime.SetWindowText(strP);
			}
			nKillTime++;



		}
		else if(NeedCacu==121)
		{
//			if(!IsInCacu)
//			{
//				IsInCacu = TRUE;
//				OnTimerDelt();
//				IsInCacu = FALSE;
//			}
//			nKillTime++;

		}
		break;
	default:
		break;
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CJSQDlg::OnBtnDiv() 
{
	
	m_strInput.GetWindowText(strInput1);
	strInput2 = _T("");
	nOperateType = OP_CACU_DIV;//4
	m_strInput.SetWindowText(_T("0"));
	
}

void CJSQDlg::OnStop() 
{
	//�洢�ɵļ�����
	int nNeedCacuBak = NeedCacu;
	if(NeedCacu==0)
	{
		return;
	}
	NeedCacu = FALSE;
	CString strTmp;
	CString strTmp2;		
	m_hintCtl.GetWindowText(strTmp);
	strTmp+=_T(" �����ƺ��Ѿ�ֹͣ����");
	m_hintCtl.SetWindowText(strTmp);

	DWORD stopTime = GetTickCount();
	DWORD cacuTime = (stopTime-m_timeStart);

	DWORD dwMSecTotal = 0;//���μ����������
	DWORD sec;
	DWORD min;
	DWORD hour;
	DWORD day;

	dwMSecTotal = (int)(cacuTime/1000);
	//msec = cacuTime%1000;
	cacuTime = dwMSecTotal;//�ܹ�������
	sec = cacuTime%60;
	cacuTime = cacuTime/60;//�ܹ��ķ���
	min = cacuTime%60;
	cacuTime = cacuTime/60;//�ܹ���ʱ��
	hour = cacuTime%24;
	day = cacuTime/24;//�ܹ���ʱ��
	
	strTmp.Format(_T("�����ʱ: %dd %dh %dm %ds\r\n"), 
		day, hour, min, sec);

	//�����ǰ���ڼ���Delt��ֵ���򽫼����ٶ���ʾ����
	if(nNeedCacuBak == NC_DELT1E4)
	{
		//�ܹ������˵���
		BigNum bnI;
		//��ʱ��������
		BigNum bnElapseTime;
		//�����ٶ�
		BigNum bnVelocity;
		//�ٶȵ��������������ֻ��һ���洢������
		BigNum bnVelocityModul;
		BigNum bn1e3;//1000
		CString strVelocity = _T("");

		//�ܼ����ʱ
		int nTotalMS = 0;
		CString strTmp2 = _T("");
		nTotalMS = GetTotalMSec(dwMSecTotal);
		//msec = nTotalMS%1000;
		cacuTime = nTotalMS;//�ܹ�������
		sec = cacuTime%60;
		cacuTime = cacuTime/60;//�ܹ��ķ���
		min = cacuTime%60;
		cacuTime = cacuTime/60;//�ܹ���ʱ��
		hour = cacuTime%24;
		day = cacuTime/24;//�ܹ���ʱ��
		strTmp2.Format(_T("�ܹ���ʱ: %dd %dh %dm %ds\r\n"), 
			day, hour, min, sec);

		strTmp += strTmp2;

		bnElapseTime.SetValue(dwMSecTotal);
		nMemory.Minus(nMemory.a, nMemory2.a, bnI.m_a);
		bn1e3.SetValue(1);
		//���ܹ������������1��
		nMemory.Mult(bnI.m_a, bn1e3.m_a, bnI.m_a);
		//�õ�ÿ���Ӽ�������ĸ���
		nMemory.Div(bnI.m_a, bnElapseTime.m_a,
			bnVelocity.m_a, bnVelocityModul.m_a);
		//���ܹ����������ԭ
		nMemory.Div(bnI.m_a, bn1e3.m_a, bnI.m_a, bnVelocityModul.m_a);
		strVelocity.Format(_T("%s nums,%s num/sec\r\n\r\n"), 
			nMemory.GetResultMy(bnI.m_a), 
			nMemory.GetResultMy(bnVelocity.m_a));
		strTmp += strVelocity;
	}

	CString strOutput;
	m_strOutput.GetWindowText(strOutput);
	strOutput= strTmp+strOutput;
	m_strOutput.SetWindowText(strOutput);
}


/**
		����: ��task.txt�ļ���������ֽ������ʼ�ֽ�
		�ֽ�ĸ�ʽΪ
		a
		b,nTime
		����aΪϣ�����ֽ����,bΪ�Ѿ����㵽��ֵ
		��
		1111111
		121,30
		��ʾϣ���ֽ�1111111�����
		�����Ѿ��ֽ⵽��b=121,��ǰ�ֽ���30��
		����������̽121��122��123�������Ƿ�Ϊ1111111������
		�����÷����������ģ�����ٳ�������ʹ���ǳ���д����������
		ʵ��
		/////////=====start
		11111111111111111
		852031,465
		/////////=====end
		���㷨��ΨһҲ��������ȷ������Ч�ʲ��ߣ���Ҫ��������С��sqrt(a)����
		���������棬����ͻ�ֹͣ���ҵ�ǰ����Ľ�����ᱣ�浽�ļ�task.txt��
		�������: 2005-05-22 22:25
*/
void CJSQDlg::OnRepLoad() 
{
	CFile file;
	CString strTemp;
	const int strLen = 2000;
	char buff[strLen];
	CString strTmpB;
	CString strTmpTime;
	int nStrLen = 0;
	memset(buff, 0, sizeof(char)*strLen);
	file.Open("task.txt", CFile::modeRead);
	file.Read(buff,strLen);
	strTemp = buff;
	file.Close();
	int nPos = strTemp.Find(13, 0);
	nStrLen = strTemp.GetLength();
	strInput1 = strTemp.Left(nPos);//��һ�е����ݣ���Ϊ�豻�ֽ����
	strTemp = strTemp.Right(strTemp.GetLength()-nPos-2);//�ڶ��м����������
	nPos = strTemp.Find(',', 0);
	strTmpB = strTemp.Left(nPos);
	strTmpTime = strTemp.Right(strTemp.GetLength()-nPos-1);
	//��ȡ������ϣ���ʼ����

	
	CString strResult = _T("");
	m_strInput.SetWindowText(strInput1);
	strResult+=strInput1;
	strResult+="\r\n = ";
	nKillTime = atoi(strTmpTime);
	
	
	
	
	//��ʼ׼������ֵ
	//=======================Start
	nToFactor.fza(strInput1);
	nToFactor.fzb(strTmpB);
	nToFactor.Clear(nToFactor.nCircle);
	nToFactor.fz(nToFactor.nReserved, nToFactor.a);
	nToFactor.bDiff = 1;
	nToFactor.Sqrt(nToFactor.a, nToFactor.aSqrt);
	//=======================End

	//��������Ƿ�Ϸ�
	if(nToFactor.a[0]==1 && nToFactor.a[1]<2)
	{
		m_strOutput.SetWindowText("���ֽ��������Ϊ2!");
		return;
	}
	
	int cacuResult = nToFactor.Factor();
	if(cacuResult!=10)
	{//������ڼ���
		if(cacuResult==1)
		{
			strResult+=nToFactor.strR;
			strResult+=_T("��");
			m_strOutput.SetWindowText(strResult);
			NeedCacu = TRUE;
			return;
		}
		else
		{
			m_strOutput.SetWindowText(strResult);
			NeedCacu = TRUE;
			return;
		}
	}
	else
	{
		strResult+=nToFactor.strR;
		m_strOutput.SetWindowText(strResult);
		NeedCacu = FALSE;
	}
	
	m_strOutput.SetWindowText(strResult);
	
	return;
	
}

void CJSQDlg::OnRepSave() 
{
	NeedCacu = FALSE;
	CString strTemp;
	CFile file;
	file.Open("task.txt", CFile::modeCreate|CFile::modeWrite);
	strTemp = strInput1;
	strTemp+="\r\n";
	file.Write(strTemp, strTemp.GetLength());
	strTemp = nToFactor.GetResultMy(nToFactor.b);
	strTemp+=",";
	file.Write(strTemp, strTemp.GetLength());
	strTemp.Format(_T("%d"), nKillTime);
	file.Write(strTemp, strTemp.GetLength());
	file.Close();
}

void CJSQDlg::OnMod() 
{
	m_strInput.GetWindowText(strInput1);
	nOperateType = OP_CACU_MOD;
	m_strInput.SetWindowText(_T("0"));
}

void CJSQDlg::OnRep10() 
{
	MyMath MyMathOnRep10;
	CString strTemp;
	m_strInput.GetWindowText(strInput1);

	if(!IsNumber(strInput1) || !IsNumber(strInput2))
	{
		m_strOutput.SetWindowText(_T("�������ֱ���Ϊ����������!"));
		return;
	}

	if(!MyMathOnRep10.fza(strInput1))
	{
		m_strOutput.SetWindowText(MyMathOnRep10.m_strError);
		return;
	}

	if(!MyMathOnRep10.JSQREP10())
	{
		m_strOutput.SetWindowText(MyMathOnRep10.m_strError);
		return;
	}
	
	strTemp.Format(_T("10 ^ %s = \r\n%s (%d digit)"),
		strInput1, MyMathOnRep10.GetResult(),
		MyMathOnRep10.GetDigit(MyMathOnRep10.nRes) ),

	m_strOutput.SetWindowText(strTemp);
}

/*
	������Ҫ��a>b
	�������: 2004-11-28 13:43
*/
void CJSQDlg::OnBtnMinus() 
{	
	m_strInput.GetWindowText(strInput1);
	nOperateType = OP_CACU_MINUS;
	m_strInput.SetWindowText(_T("0"));
}

void CJSQDlg::OnMsave() 
{
	CString strTmp;
	m_strInput.GetWindowText(strTmp);
	nMemory.fza(strTmp);
	nMemory.fz(nMemory.nRes, nMemory.a);
}

void CJSQDlg::OnMr() 
{	
	CString strTmp = nMemory.GetResult();
	m_strInput.SetWindowText(strTmp);
}

BOOL IsPrime(int n)
{
	for(int i=2;i<n;i++)
	{
		if(n%i==0)
			return FALSE;
	}
	return TRUE;
	
} //BOOL IsPrime(int n)


/*
 *	����Delt(p)���߳�
 *  �����void* p����Ǵ���ҳ���ָ�롣
 *  �������: 2007-02-05 11:30
 */
VOID ThreadProc(void* p)
{
	CJSQApp *pApp = (CJSQApp *)p;
	CJSQDlg *pDlg = (CJSQDlg *)pApp->m_pJSQDlg;
	DWORD dwThreadHits = 0;
	//int i;
	do
	{
		dwThreadHits++;//������
		
		if(dwThreadHits%793==0)
		{
			pDlg->m_bShowHint = TRUE;
		}
		
		pDlg->OnTimerDelt();
		
		if(pDlg->NeedCacu!=NC_DELT1E4 || dwThreadHits%50200==0)
		{
			pDlg->m_strEndNum = pDlg->nMemory.GetResultMy(pDlg->nMemory.a);
			CFile file;
			if(file.Open(FILE_DELT_CURA, CFile::modeWrite|CFile::modeCreate))
			{
				file.Write(pDlg->m_strEndNum, pDlg->m_strEndNum.GetLength());
				file.Close();
			}
			if(pDlg->NeedCacu!=NC_DELT1E4)
				break;
		}
		
	}while(TRUE);//Ѳ��1000��
} // VOID ThreadProc(void* p)






unsigned __stdcall ThreadProcEuler(void *p)
{
	CJSQApp *pApp = (CJSQApp *)p;
	CDC *pDC = pApp->GetMainWnd()->GetDC();
	CJSQDlg *pDlg = (CJSQDlg *)pApp->m_pJSQDlg;
	DWORD dwThreadHits = 0;
	CString strWrite = _T("");
	BOOL bGetIt = FALSE;
	int nBounds = 32;
	//int i;
	do
	{
		dwThreadHits++;//������
		
		bGetIt = pDlg->Euler6(nBounds);

		if(bGetIt)
		{
			break;
		}
		
		if(dwThreadHits%10000==0)
		{
			//nMemory.fzb(pDlg->m_strStartNum);
			//nMemory.Minus(nMemory.a, nMemory.b);//cΪ�����˵���
			strWrite.Format(_T("%d"), nBounds);
			CFile file;
			if(file.Open("curAEuler.txt", CFile::modeWrite|CFile::modeCreate))
			{
				file.Write(strWrite, strWrite.GetLength());
				file.Close();
			}
		}
		//Sleep(3);//CPU 15%
		
		//CPU 41%   2005-09-02 08:06  Delt( 311921569 ) = 10000
		//Sleep(2);//CPU 15%
		
		//CPU 42%	2005-09-02 08:02  Delt( 311902277 ) = 10000 
		//Sleep(1);
		
		//CPU 100%	2005-09-02 08:08  Delt( 311979007 ) = 10000
		//nosleep
		
		if(dwThreadHits%1==0)
		{
			//CPU 98%	2005-09-02 08:12  Delt( 311997641 ) = 10000
			Sleep(1000);//0.2ms
		}
		nBounds++;
		
	}while(TRUE);//Ѳ��1000��
	//...
	return NULL;
}

/*
	����˵��: ��ʼ����������һЩ����Delt(10, p) < 1e4
	          �����ݲ��ṩ����������Delt����
	�������: 2005-03-28 18:10
	Author: Wreck
*/
void CJSQDlg::OnCapDelt() 
{
	//	if(!m_bOpenedFile && m_file.Open(FILE_DELTOUT,CFile::modeReadWrite))
	//	{
	//		m_file.SeekToEnd();
	//		m_bOpenedFile = TRUE;
	//	}
	
	//	else if(!m_bOpenedFile)
	//	{
	//		CString strFNTmp;
	//		strFNTmp.Format( _T("�ļ�%s��ʧ��!"), FILE_DELTOUT ), 
	//			
	//		AfxMessageBox(strFNTmp);
	//		return;
	//	}
	
	if(NeedCacu==NC_DELT1E4)
	{ //����Ѿ��ڼ�����˴ε����Ч��
		return;
	}
	
	
	CString strTmp;
	CFile file;
	if(file.Open(FILE_DELT_CURA, CFile::modeRead))
	{
		char charBuff[20];
		memset(charBuff, 0, sizeof(charBuff));
		file.Read(charBuff, 20);
		strTmp = charBuff;
		nMemory.fza(strTmp);
		//nMemory.a[1]+=1;//��aΪ��һ������
		//(ÿ�μ���֮���Ѿ���aΪ��һ��������)
		if(nMemory.a[1]%2==0)
		{
			nMemory.a[1]++;
		}
		nMemory.ZZH2(nMemory.a);
		file.Close();

		//����ʼֵ�洢��nMemory2��
		nMemory2.fz(nMemory2.a, nMemory.a);
	}
	NeedCacu = NC_DELT1E4;
	m_timeStart = GetTickCount();
	CJSQApp *pApp = (CJSQApp *)AfxGetApp();
	m_strStartNum = strTmp;
	
	
	DWORD tid;
	
//	thd = _beginthreadex(NULL,
//		0,
//		ThreadProc,
//		pApp,//arg
//		0,
//		&tid);

	DWORD dw = IDLE_PRIORITY_CLASS;

	HANDLE _hThread;

	_hThread = CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)ThreadProc,
		pApp,
		dw,//CREATE_SUSPENDED,
		&tid);
	
	//�˴���Ҫ�������̵߳ĵȼ���ñȽϵ͡�
	//THREAD_PRIORITY_LOWEST
	//SetThreadPriority(_hThread, THREAD_PRIORITY_LOWEST);
	SetThreadPriority(_hThread, THREAD_PRIORITY_IDLE);
}

void CJSQDlg::OnPrimeSearch() 
{
	m_strInput.GetWindowText(strInput1);
	CString strOutputPrime;
	int nIPutPrime = atoi(strInput1);

	
	if(nIPutPrime<2 || nIPutPrime>200000)
	{
		m_strOutput.SetWindowText(_T("������һ������2С��200000������"));
		return;
	}

	CString strTmp;
	int nNum = 0;
    int j = 0;
	strTmp.Format(_T("%d"), nIPutPrime);
	strOutputPrime = _T("С��");
	strOutputPrime+=strTmp;
	strOutputPrime+=_T("�������У�\r\n");
	for(int i=2;i<nIPutPrime;i++)
	{
		int sqrti = (int)sqrt((double)i);
		for (j = 2; j <= sqrti; j++)
		{
			if(i%j==0)
				break;
		}

		if(j==(sqrti+1))
		{
			CString strI;
			//strI.Format(_T("%6d "),i);
			strI.Format(_T("%d,"),i);
			strOutputPrime+=strI;
			nNum++;
			if(nNum==1)
			{
				//strOutputPrime.Format(_T("%5d: "), nNum-1);
			}
			if(nNum%10==0)
			{
				CString strCRLF;
				//strCRLF.Format(_T("%5d: "), nNum);
				strOutputPrime+=_T("\r\n");
				strOutputPrime+=strCRLF;
			}
		}
	}

	CString strCRLFLast;
	strCRLFLast.Format(_T("\r\n��%d������"), nNum);
	strOutputPrime+=strCRLFLast;

	m_strOutput.SetWindowText(strOutputPrime);
}

/*
	����Delt�Ķ�ʱ������ʱЧ�ʻ��ܵ�
	�˺��������ڼ���Delt(10, p)<1e4
	��ӡ�ĸ�ʽ����:
	[2005-03-28 18:50] Delt( 10769401 ) = 5983
*/
void CJSQDlg::OnTimerDelt()
{	
	dwTickFlash[0] = GetTickCount();

	BOOL bCacuRes = nMemory.JSQDELT();
	//��a����С�����Ӵ���100ʱ��ʾ��ʾ��Ϣ
	if(bCacuRes || (nMemory.nRes[0]!=1 || nMemory.nRes[1]!=0) )
	{
		CString strDeltResult = nMemory.GetResult();
		
		CString strDeltOut = _T("");
		strDeltOut.Format( _T("Delt( %s ) = %s  (%d digits)"),
			nMemory.GetResultMy(nMemory.a), 
			strDeltResult, 
			nMemory.GetDigit(nMemory.a));

		//����a��������JSQDELT()���Ѿ��ж���,�������ﲻ��Ҫ���ж�
		if(bCacuRes)
		{
			CString strFilePrint = _T("");
			CString strTimeCur = _T("");//_T("[0000-00-00 00:00]");;
			
			CTime time = CTime::GetCurrentTime();
			strTimeCur.Format(_T("[%04d-%02d-%02d %02d:%02d]"),
				time.GetYear(),time.GetMonth(),time.GetDay(),
				time.GetHour(),time.GetMinute());
			strFilePrint.Format(_T("\r\n%s %s"), strTimeCur, strDeltOut);
			int nStrLen = strFilePrint.GetLength();
			if(m_file.Open(FILE_DELTOUT,CFile::modeReadWrite))//���浽�ļ���
			{
				m_file.SeekToEnd();
				m_file.Write(strFilePrint.GetBuffer(nStrLen), nStrLen);
				m_file.Close();
			}

			//��ʾ����Ļ��
			CString strTempOutput;
			m_strOutput.GetWindowText(strTempOutput);
			if(strTempOutput.GetLength()>4500)
			{
				strTempOutput = strTempOutput.Left(1500);
			}
			CString strOP;
			strOP = strFilePrint;
			strOP+=strTempOutput;
			m_strOutput.SetWindowText(strOP);

			//ÿһ������������ʱ��
			dwTickFlash[1] = GetTickCount();
			
			long nTempTime2 = dwTickFlash[1]-dwTickFlash[0];
			CString strP;
			strP.Format(_T("%d ms"), nTempTime2);
			m_StepTime.SetWindowText(strP);
		}
		else if(m_bShowHint)
		{
			//strDeltOut = getBStat();
			m_hintCtl.SetWindowText(strDeltOut);
			m_bShowHint = FALSE;
		}
	}
	nMemory.a[1]+=2;//m_nMinAddDelt;
	nMemory.ZZH2(nMemory.a);
}

void CJSQDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

/************************************************************************/
/* �������������ƽ����                                                 */
/************************************************************************/
void CJSQDlg::OnSqrt() 
{
	// TODO: Add your control notification handler code here
	g_tickFlash[0]=GetTickCount();
	m_strInput.GetWindowText(strInput1);
	nMemory.fza(strInput1);
	nMemory.JSQSQRT();
	CString strA = strInput1;//���������
	CString strResult = nMemory.GetResult();//����õ���ƽ����
	int nBitResult = nMemory.nRes[0];//ƽ������λ��
	CString strOutputTmp;
	CString strTemp2 = _T("");

	//��ʼ��������(�����c��,ƽ���������b��)
	//b^2�����d��
	nMemory.Clear(nMemory.c);
	nMemory.fz(nMemory.b, nMemory.nRes);
	nMemory.Mult(nMemory.b, nMemory.b, nMemory.d);
	nMemory.Minus(nMemory.a, nMemory.d, nMemory.c);

	strOutputTmp.Format(_T("sqrt( %s ) = %s (%d digits)\r\n"), 
		strA,strResult,
		nMemory.GetDigit(nMemory.nRes) );

	CString strDiff = nMemory.GetResultMy(nMemory.c);
	strTemp2.Format(_T("���Ϊ: %s (%d digits)"),
		strDiff, nMemory.GetDigit(nMemory.c) );
	
	strOutputTmp = strOutputTmp + strTemp2;
	m_strOutput.SetWindowText(strOutputTmp);
	m_strInput.SetWindowText(strResult);

	g_tickFlash[1]=GetTickCount();
	int nElapsedTime = g_tickFlash[1] - g_tickFlash[0];
	strOutputTmp.Format(_T("%d"), nElapsedTime);
	m_StepTime.SetWindowText(strOutputTmp);
}

void CJSQDlg::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	CDlgSet dlgSet;
	dlgSet.DoModal();

	
}

void CJSQDlg::OnButtonSqr() 
{
	// TODO: Add your control notification handler code here
	m_strInput.GetWindowText(strInput1);
	
	if(!nMemory.fza(strInput1))
	{
		//ĳЩ�ط������ˣ��粻��������ĸ��
		AfxMessageBox(nMemory.m_strError);
		return;
	}

	//����������ܹ���
	if((nMemory.a[0]*2)>=MAX_DIGIT)
	{
		AfxMessageBox(_T("�������, ������λ������."));
		return;
	}

	nMemory.JSQSQR();
	CString strResult = nMemory.GetResult();
	CString strOutputTmp;
	strOutputTmp.Format(_T("%s^2 (%d digits)\r\n= %s (%d digits)"), 
		strInput1, nMemory.GetDigit(nMemory.a),
		strResult, nMemory.GetDigit(nMemory.nRes) );
	m_strOutput.SetWindowText(strOutputTmp);

	m_strInput.SetWindowText(strResult);
}

void CJSQDlg::OnButtonPower() 
{
	// TODO: Add your control notification handler code here
	m_strInput.GetWindowText(strInput1);
	nOperateType = OP_CACU_POWER;
	m_strInput.SetWindowText(_T("0"));
}

//��������Ƿ�Ϊ����
BOOL CJSQDlg::IsNumber(CString str)
{
	int nLen = str.GetLength();
	

	for(int i=0;i<nLen;i++)
	{
		if((str[i] - '0')<0 || (str[i] - '9')>0)
			return FALSE;
	}

	
	return TRUE;
}

void CJSQDlg::OnExtend() 
{
	CString type = _T("");
	m_strInput.GetWindowText(type);
	// TODO: Add your control notification handler code here
	//���ж�����
	if(type.Compare("GetDeltDistance")==0) 
	{
		GetDeltDistance();
	}
	else if(type.Compare("Euler6")==0)
	{
		CJSQApp *pApp = (CJSQApp *)AfxGetApp();
		
		
		unsigned long thd;
		unsigned tid;
		
		thd = _beginthreadex(NULL,
			0,
			ThreadProcEuler,
			pApp,//arg
			0,
			&tid);
	}
	else if(type.Compare(_T("Test"))==0) 
	{
		Test();
	}
	else if(type.Compare(_T("Test2"))==0) 
	{
		Test2();
	}
	
	
}

BOOL CJSQDlg::GetDeltDistance()
{
	// TODO: Add your command handler code here
	int nSize = 18;
	int nAry[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	double dAry[] = {64000,32000,16000.0,8000.0,
		4000.0,2000.0,1100.0,1000.0,
		900.0,800.0,700.0,600.0,500.0,
		400.0,300.0,200.0,100.0,50.0,0.0};
	CFile file;
	char buf[400000];
	MyMath mmTest;
	BigNum bgA, bgB, bgC, bgD; 
	
	CString strBuffer = _T("");
	int nPos1 = 0;
	int nPos2 = 0;
	CString strLine = _T("");
	CString strLeft = _T("");

	CString strMax = _T("0");
	CString strMax2 = _T("0");
	int nMax = 10;

	CString strMin = _T("0");
	CString strMin2 = _T("0");
	int nMin = 10000;
	
	file.Open(_T("DistanceDelt1e4.txt"), CFile::modeRead);
	
	memset(buf, 0, sizeof(buf));
	file.Read(buf, sizeof(buf));
	file.Close();
	
	strBuffer = buf;
	
	
	nPos1 = strBuffer.Find(_T("\r\n"), nPos2);
	CString num1 = _T("0");
	CString num2 = _T("0");
	//CString strExt1;
	//CString strExt2;
	int nPos31 = 0;
	int nPos32 = 0;
	int nCount = 0;

	CString num1Minus2MultN;
	
	while(nPos1>=0)
	{
		strLeft = strBuffer.Left(nPos1);
		strLine = strLeft.Right(nPos1-nPos2);

		nPos31 = strLine.Find(_T("( "));
		nPos32 = strLine.Find(_T(" )"));

		if(nCount>0)
		{
			num2 = num1;
		}

		strLeft = strLine.Left(nPos32);
		num1 = strLeft.Right(nPos32-nPos31-2);

		if(nCount>0)
		{

			mmTest.fza(num1);
			mmTest.fzb(num2);
			mmTest.Minus(mmTest.a, mmTest.b, bgC.m_a);//c=a-b


			mmTest.Div(mmTest.b, bgC.m_a, bgA.m_a, bgB.m_a);//bgA=b/(a-b);
			num1Minus2MultN = mmTest.GetResultMy(bgA.m_a);
			int nNumReal = atoi(num1Minus2MultN.GetBuffer(num1Minus2MultN.GetLength()));
			int i = 0;
			for(i=0;i<nSize;i++)
			{
				if((double)nNumReal>dAry[i])
				{
					nAry[i]++;
					break;
				}
			}

			if(i==nSize)
			{
				nAry[i]++;
			}

			if(nNumReal>nMax)
			{
				nMax = nNumReal;
				strMax = num2;
				strMax2 = num1;
			}

			if(nNumReal<nMin)
			{
				nMin = nNumReal;
				strMin = num2;
				strMin2 = num1;
			}
		}

		nPos2 = nPos1;
		nPos1 = strBuffer.Find(_T("\r\n"), nPos2+1);
		nCount++;
	}

	CString strOut = _T("");
	CString strTemp;

	for(int j=0;j<=nSize;j++)
	{
		strTemp.Format(_T("%d. %d nTimes>%d\r\n"), j, nAry[j], (int)dAry[j]);
		strOut+=strTemp;
	}

	CString strOut2 = _T("");
	strOut2.Format(_T("min=%d  %s,%s\r\nmax=%d  %s,%s\r\nnCount=%d\r\n"),
		nMin, strMin, strMin2, nMax, strMax, strMax2, nCount);

	strOut+=strOut2;

	m_strOutput.SetWindowText(strOut);
	
	return TRUE;
}

BOOL CJSQDlg::Euler6(int nBounds)
{
	
	CString strOut2 = _T("");
	CString strTemp = _T("");
	int nStrLen = 0;
	BOOL bReturn = FALSE;
	dwTickFlash[0] = GetTickCount();
	CString strOutTmp = _T("");
	CString strOutTmp2 = _T("");
	CEuler euler6;
	euler6.SetBound(nBounds);
	strOutTmp = euler6.CacuAt(6);
	bReturn = euler6.m_bGetIt;
	m_strOutput.GetWindowText(strTemp);
	if(strTemp.GetLength()>1000)
	{
		strTemp = strTemp.Left(500);
	}
	dwTickFlash[1] = GetTickCount();
	int nSpend = dwTickFlash[1] - dwTickFlash[0];

	CTime curTime = CTime::GetCurrentTime();
	CString strTime;
	strTime.Format(_T("[%04d-%02d-%02d %02d:%02d]"), 
		curTime.GetYear(),curTime.GetMonth(),curTime.GetDay(),
		curTime.GetHour(),curTime.GetMinute());

	strOutTmp2.Format(_T("%s %s, %d ms\r\n"), strTime, strOutTmp, nSpend);

	strOut2.Format(_T("%s%s"),
		strOutTmp2, strTemp);

	if(m_file.Open(_T("Euler6.txt"),CFile::modeReadWrite))//���浽�ļ���
	{
		nStrLen = strOutTmp2.GetLength();
		m_file.SeekToEnd();
		m_file.Write(strOutTmp2.GetBuffer(nStrLen), nStrLen);
		m_file.Close();
	}
	
	m_strOutput.SetWindowText(strOut2);

	
	strOutTmp.Format(_T("%d ms"), nSpend);
	m_StepTime.SetWindowText(strOutTmp);
	return bReturn;
}


int CJSQDlg::GetTotalMSec(int nCurMSec)
{
	int nReturn = 0;
	CFile file;
	CString strTmp = _T("");
	if(file.Open(FILE_DELT1e4CFG, CFile::modeReadWrite))
	{
		char charBuff[20];
		int nFileLen = 0;
		int nTotalMS = 0;
		memset(charBuff, 0, sizeof(charBuff));
		file.Read(charBuff, 20);
		nTotalMS = atoi(charBuff);
		nTotalMS += nCurMSec;

		//����ʱ��浽�ļ���
		strTmp.Format(_T("%d"), nTotalMS);
		file.SeekToBegin();
		nFileLen = strTmp.GetLength();
		file.Write(strTmp.GetBuffer(nFileLen), nFileLen);
		file.Close();
		nReturn = nTotalMS;
	}
	return nReturn;
}

void CJSQDlg::Test()
{
    int i = 0;
	int nTimes = 10000;
	DWORD tickFlash[2];
	tickFlash[0] = GetTickCount();
	MyMath mm1;
	mm1.fza(_T("25873625873698719871"));
	mm1.fzb(_T("25873625873698719871"));
	__int64 test1=347842573624817;
	__int64 test2=548751458524213;
	for(i=0;i<nTimes;i++)
	{
		//���Գ˷���Ч��(2��15λ�������)
		//mm1.Mod(mm1.a, mm1.b, mm1.c);
		mm1.Mult(mm1.a,mm1.b,mm1.c);
		//test1 *= 10;
		//resTT = test1%test2;
	}
	tickFlash[1] = GetTickCount();

	int nTempTime2 = (int)(tickFlash[1]-tickFlash[0]);
	CString strP;
	strP.Format(_T("%.10f  ms"),(double)nTempTime2/nTimes);
	m_strOutput.SetWindowText(strP);
}


void CJSQDlg::Test2()
{
	DWORD tickFlash[2];
	tickFlash[0] = GetTickCount();
	//����1+1/2+1/3
	BigNum bnFZ1;//����
	BigNum bnFM1;//��ĸ

	BigNum bnFZ2;//����
	BigNum bnFM2;//��ĸ

	BigNum bnFZR;//����
	BigNum bnFMR;//��ĸ

	BigNum bnTemp1;
	BigNum bnTemp2;

	BigNum bnTemp3;
	BigNum bnTemp4;
	BigNum bnTemp5;


	bnFZ1.SetValue(1);
	bnFM1.SetValue(1);

	bnFZ2.SetValue(1);


	for(int i=2;i<=111;i++)
	{
		
		bnFM2.SetValue(i);

		nMemory.Mult(bnFM1.m_a,bnFM2.m_a,bnFMR.m_a);

		nMemory.Mult(bnFZ1.m_a,bnFM2.m_a,bnTemp1.m_a);
		nMemory.Mult(bnFM1.m_a,bnFZ2.m_a,bnTemp2.m_a);
		nMemory.Add(bnTemp1.m_a,bnTemp2.m_a,bnFZR.m_a);


		nMemory.gcd(bnFZR.m_a,bnFMR.m_a,bnTemp3.m_a,bnTemp4.m_a,bnTemp5.m_a);

		if(nMemory.Compare(bnTemp3.m_a,nMemory.m_ONE)>0)
		{
			nMemory.Div(bnFZR.m_a,bnTemp3.m_a,bnFZR.m_a,bnTemp4.m_a);
			nMemory.Div(bnFMR.m_a,bnTemp3.m_a,bnFMR.m_a,bnTemp4.m_a);
		}

		nMemory.fz(bnFM1.m_a,bnFMR.m_a);
		nMemory.fz(bnFZ1.m_a,bnFZR.m_a);	
	}

	nMemory.Div(bnFZR.m_a,bnFMR.m_a,bnTemp1.m_a,bnTemp2.m_a);

	tickFlash[1] = GetTickCount();

	int nTempTime2 = (int)(tickFlash[1]-tickFlash[0]);
	CString strP2;
	strP2.Format(_T("%d  ms"),nTempTime2);


	double sum = 0.0;
	double temp = 1.0;

	for(int j=1;j<=1111;j++)
	{
		temp = 1.0/j;
		sum += temp;
	}


	CString strP;
	strP.Format(_T("%s (%d digit)/ %s = %s �� %s  %f"),nMemory.GetResultMy(bnFZR.m_a),
		nMemory.GetResultMy(bnFZR.m_a).GetLength(),
		nMemory.GetResultMy(bnFMR.m_a),
		nMemory.GetResultMy(bnTemp1.m_a),nMemory.GetResultMy(bnTemp2.m_a),sum);
	m_strOutput.SetWindowText(strP + "\r\n    " + strP2);




	
}


