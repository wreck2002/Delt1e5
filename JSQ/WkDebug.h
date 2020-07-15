// WkDebug.h: interface for the WkDebug class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WKDEBUG_H__3C512A42_A943_4F91_9AB0_DD7C5CF51913__INCLUDED_)
#define AFX_WKDEBUG_H__3C512A42_A943_4F91_9AB0_DD7C5CF51913__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class WkDebug  
{
public:
	static BOOL write(CString strP);
	WkDebug();
	virtual ~WkDebug();

};

#endif // !defined(AFX_WKDEBUG_H__3C512A42_A943_4F91_9AB0_DD7C5CF51913__INCLUDED_)
