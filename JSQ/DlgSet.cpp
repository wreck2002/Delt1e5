// DlgSet.cpp : implementation file
//

#include "stdafx.h"
#include "JSQ.h"
#include "DlgSet.h"
#include "JSQDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSet dialog


CDlgSet::CDlgSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSet::IDD, pParent)
{
	CJSQApp *pJSQApp = (CJSQApp *)AfxGetApp();
	CJSQDlg *pJSQDlg = (CJSQDlg *)pJSQApp->m_pJSQDlg;

	//{{AFX_DATA_INIT(CDlgSet)
	m_nNeedCacu = pJSQDlg->NeedCacu;
	//}}AFX_DATA_INIT
}


void CDlgSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSet)
	DDX_Text(pDX, IDC_EDIT_NeedCacu, m_nNeedCacu);
	DDV_MinMaxInt(pDX, m_nNeedCacu, -100, 500);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSet, CDialog)
	//{{AFX_MSG_MAP(CDlgSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSet message handlers

void CDlgSet::OnOK() 
{
	// TODO: Add extra validation here
	CJSQApp *pJSQApp = (CJSQApp *)AfxGetApp();
	CJSQDlg *pJSQDlg = (CJSQDlg *)pJSQApp->m_pJSQDlg;
	this->UpdateData();
	pJSQDlg->NeedCacu = m_nNeedCacu;
	
	CDialog::OnOK();
}
