#if !defined(AFX_DLGSET_H__487DE7B9_D361_41A3_B816_EDB363C30177__INCLUDED_)
#define AFX_DLGSET_H__487DE7B9_D361_41A3_B816_EDB363C30177__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSet dialog

class CDlgSet : public CDialog
{
// Construction
public:
	CDlgSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSet)
	enum { IDD = IDD_DIALOG_SET };
	int		m_nNeedCacu;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSet)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSET_H__487DE7B9_D361_41A3_B816_EDB363C30177__INCLUDED_)
