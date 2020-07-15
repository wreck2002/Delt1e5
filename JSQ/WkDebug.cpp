// WkDebug.cpp: implementation of the WkDebug class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JSQ.h"
#include "WkDebug.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WkDebug::WkDebug()
{

}

WkDebug::~WkDebug()
{

}

BOOL WkDebug::write(CString strP)
{
	CString strPrint = _T("");
	BOOL bReturn = FALSE;
	CFile file;
	BOOL bFlag1 = FALSE;
	BOOL bFlag2 = FALSE;

	CString strFileName = _T("");
	CTime time = CTime::GetCurrentTime();
	strFileName.Format(_T("debug%04d%02d%02d.txt"),
		time.GetYear(),time.GetMonth(),time.GetDay());
	bFlag1 = file.Open(strFileName,CFile::modeReadWrite);
	if(!bFlag1) 
	{
		bFlag2 = file.Open(strFileName,CFile::modeReadWrite|CFile::modeCreate);
	}

	strPrint.Format(_T("[%04d-%02d-%02d %02d:%02d:%02d] %s \r\n"),
		time.GetYear(),time.GetMonth(),time.GetDay(),
		time.GetHour(), time.GetMinute(), time.GetSecond(),
		strP);

	int nStrLen = strPrint.GetLength();
	if(bFlag1 || bFlag2)//储存到文件中
	{
		file.SeekToEnd();
		file.Write(strPrint.GetBuffer(nStrLen), nStrLen);
		file.Close();
	}
	return bReturn;
}
