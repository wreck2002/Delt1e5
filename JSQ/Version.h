// Version.h: interface for the CVersion class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VERSION_H__AC78CDF6_0748_405D_9A8C_3256799BF741__INCLUDED_)
#define AFX_VERSION_H__AC78CDF6_0748_405D_9A8C_3256799BF741__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//°æ±¾¿ØÖÆ
//Add time: 2005-05-22 09:34
class CVersion  
{
public:
	CVersion();
	virtual ~CVersion();

public:
	CString m_strVersion;
private:
	CString m_strTime;
	CString m_strDescription;
};

#endif // !defined(AFX_VERSION_H__AC78CDF6_0748_405D_9A8C_3256799BF741__INCLUDED_)
