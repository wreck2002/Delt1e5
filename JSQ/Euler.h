// Euler.h: interface for the CEuler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EULER_H__4CEA3D6C_B82B_4935_B082_73EDEFB12E93__INCLUDED_)
#define AFX_EULER_H__4CEA3D6C_B82B_4935_B082_73EDEFB12E93__INCLUDED_

#include "MyMath.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEuler  
{
public:
	BOOL m_bGetIt;
	BigNum m_bgNBounds;
	BOOL SetBound(int nBound);
	CString CacuAt(int nTmp);
	CEuler();
	virtual ~CEuler();

private:
	CString CacuAt6();
	CString CacuAt2();
	CString CacuAt1();
};

#endif // !defined(AFX_EULER_H__4CEA3D6C_B82B_4935_B082_73EDEFB12E93__INCLUDED_)
