// JSQ.h : main header file for the JSQ application
//

#if !defined(AFX_JSQ_H__748AAE92_5C22_489C_907E_760737F63EE5__INCLUDED_)
#define AFX_JSQ_H__748AAE92_5C22_489C_907E_760737F63EE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CJSQApp:
// See JSQ.cpp for the implementation of this class
//

class CJSQApp : public CWinApp
{
public:
	CJSQApp();
	CDialog *m_pJSQDlg;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJSQApp)
	public:
	virtual BOOL InitInstance();
	virtual CWnd* GetMainWnd();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CJSQApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JSQ_H__748AAE92_5C22_489C_907E_760737F63EE5__INCLUDED_)
