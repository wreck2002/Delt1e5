// Euler.cpp: implementation of the CEuler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JSQ.h"
#include "Euler.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEuler::CEuler()
{
	m_bGetIt = FALSE;
}

CEuler::~CEuler()
{

}

CString CEuler::CacuAt(int nTmp)
{
	CString strReturn = _T("");
	if(nTmp==1)
	{
		strReturn = CacuAt1();
	}
	else if(nTmp==6)
	{
		strReturn = CacuAt6();
	}
	return strReturn;
}


//计算n1+n2=n3的整数解
CString CEuler::CacuAt1()
{
	CString strReturn = _T("");
	return strReturn;
}

CString CEuler::CacuAt2()
{
	CString strReturn = _T("");
	return strReturn;
}

CString CEuler::CacuAt6()
{
	CString strReturn = _T("");
	BigNum bgNCurAt;
	BigNum bgN1, bgN2, bgN3, bgN4, bgN5, bgN6, bgN7;
	MyMath mmTest;
	mmTest.fz(bgNCurAt.m_a, m_bgNBounds.m_a);

	BigNum bgNSum, bgN7Times6;
	BigNum bgNTemp;
	BigNum bgMinResult;//计算得到的最小值（绝对值）
	CString strMinusResult = _T("");

	BigNum bgNPower;
	bgNPower.SetValue(6);
	mmTest.Power(&m_bgNBounds, &bgNPower, &bgMinResult);
	mmTest.Mult(bgMinResult.m_a, bgNPower.m_a, bgMinResult.m_a);

	mmTest.fz(bgN7.m_a, bgNCurAt.m_a);
	mmTest.Clear(bgN7Times6.m_a);
	
	//n7^6
	mmTest.Power(&bgN7, &bgNPower, &bgN7Times6);

	CString strN1, strN2, strN3, strN4, strN5, strN6, strN7;
	strN7 = mmTest.GetResultMy(bgN7.m_a);

	BigNum bgN7_next6Min;
	BigNum bgN7Tmp1, bgN7Tmp2;
	bgN7Tmp1.SetValue(100);//7Tmp1 = 100;

	bgN7Tmp2.SetValue(135);//7Tmp2 = 135;

	mmTest.Mult(bgN7.m_a, bgN7Tmp1.m_a, bgN7Tmp1.m_a);
	mmTest.Div(bgN7Tmp1.m_a, bgN7Tmp2.m_a, 
		bgN7_next6Min.m_a, bgN7Tmp1.m_a);
	

	for(mmTest.fz(bgN1.m_a,mmTest.m_ONE);mmTest.Compare(bgN1.m_a,
		bgNCurAt.m_a)<0;bgN1.AddSmallDigit(1))
	{
		for(mmTest.fz(bgN2.m_a,mmTest.m_ONE);mmTest.Compare(bgN2.m_a,
			bgNCurAt.m_a)<0;bgN2.AddSmallDigit(1))
		{
			Sleep(10);
			for(mmTest.fz(bgN3.m_a,mmTest.m_ONE);mmTest.Compare(bgN3.m_a,
				bgNCurAt.m_a)<0;bgN3.AddSmallDigit(1))
			{
				for(mmTest.fz(bgN4.m_a,mmTest.m_ONE);mmTest.Compare(bgN4.m_a,
					bgNCurAt.m_a)<0;bgN4.AddSmallDigit(1))
				{
					for(mmTest.fz(bgN5.m_a,mmTest.m_ONE);mmTest.Compare(bgN5.m_a,
						bgNCurAt.m_a)<0;bgN5.AddSmallDigit(1))
					{
						for(mmTest.fz(bgN6.m_a,mmTest.m_ONE);mmTest.Compare(bgN6.m_a,
							bgNCurAt.m_a)<0;bgN6.AddSmallDigit(1))
						{
							//要求n6>=n7*100/135
							if(mmTest.Compare(bgN6.m_a,bgN7_next6Min.m_a)<0)
							{
								continue;
							}

								//要求n1<=n2<=n3<=n4<=n5<=n6
								if(mmTest.Compare(bgN1.m_a,bgN2.m_a)>0
									||mmTest.Compare(bgN2.m_a,bgN3.m_a)>0
									||mmTest.Compare(bgN3.m_a,bgN4.m_a)>0
									||mmTest.Compare(bgN4.m_a,bgN5.m_a)>0
									||mmTest.Compare(bgN5.m_a,bgN6.m_a)>0) 
								{
									continue;
								}

								mmTest.Clear(bgNSum.m_a);

								//n1^6
								mmTest.Power(&bgN1, &bgNPower, &bgNTemp);
								mmTest.Add(bgNSum.m_a, bgNTemp.m_a, bgNSum.m_a);
								//n2^6
								mmTest.Power(&bgN2, &bgNPower, &bgNTemp);
								mmTest.Add(bgNSum.m_a, bgNTemp.m_a, bgNSum.m_a);
								//n3^6
								mmTest.Power(&bgN3, &bgNPower, &bgNTemp);
								mmTest.Add(bgNSum.m_a, bgNTemp.m_a, bgNSum.m_a);
								//n4^6
								mmTest.Power(&bgN4, &bgNPower, &bgNTemp);
								mmTest.Add(bgNSum.m_a, bgNTemp.m_a, bgNSum.m_a);
								//n5^6
								mmTest.Power(&bgN5, &bgNPower, &bgNTemp);
								mmTest.Add(bgNSum.m_a, bgNTemp.m_a, bgNSum.m_a);
								//n6^6
								mmTest.Power(&bgN6, &bgNPower, &bgNTemp);
								mmTest.Add(bgNSum.m_a, bgNTemp.m_a, bgNSum.m_a);

								//如果n1^6+...+n6^6=n7^6则成功并且返回
								int nMinusR = mmTest.Compare(bgNSum.m_a, bgN7Times6.m_a);
								CString strOut = _T("");
								strN1 = mmTest.GetResultMy(bgN1.m_a);
								strN2 = mmTest.GetResultMy(bgN2.m_a);
								strN3 = mmTest.GetResultMy(bgN3.m_a);
								strN4 = mmTest.GetResultMy(bgN4.m_a);
								strN5 = mmTest.GetResultMy(bgN5.m_a);
								strN6 = mmTest.GetResultMy(bgN6.m_a);
								if(nMinusR==0)
								{
									strOut.Format(_T("%s^6+%s^6+%s^6+%s^6+%s^6+%s^6=%s^6"), 
										strN1, strN2, strN3, strN4,strN5,strN6,strN7);
									strReturn = strOut;
									m_bGetIt = TRUE;
									return strReturn;
								}
								else if(nMinusR>0)
								{
									mmTest.Minus(bgNSum.m_a, bgN7Times6.m_a, bgNTemp.m_a);
									if(mmTest.Compare(bgNTemp.m_a, bgMinResult.m_a)<0)
									{
										strReturn = mmTest.GetResultMy(bgNTemp.m_a);
										strMinusResult.Format(_T("%s^6+%s^6+%s^6+%s^6+%s^6+%s^6-%s^6=%s"), 
											strN1, strN2, strN3, strN4,strN5,strN6,strN7, strReturn);
										mmTest.fz(bgMinResult.m_a, bgNTemp.m_a);
									}
									
								}
								else if(nMinusR<0)
								{
									mmTest.Minus(bgN7Times6.m_a, bgNSum.m_a, bgNTemp.m_a);
									if(mmTest.Compare(bgNTemp.m_a, bgMinResult.m_a)<0)
									{
										strReturn = mmTest.GetResultMy(bgNTemp.m_a);
										strMinusResult.Format(_T("%s^6+%s^6+%s^6+%s^6+%s^6+%s^6-%s^6=-%s"), 
											strN1, strN2, strN3, strN4,strN5,strN6,strN7, strReturn);
										mmTest.fz(bgMinResult.m_a, bgNTemp.m_a);
									}
								}
							//}
						}
					}
				}
			}
		}
	}
	strReturn.Format(_T("%s"), strMinusResult);
	return strReturn;
}

BOOL CEuler::SetBound(int nBound)
{
	MyMath mmTemp;
	char szBounds[10];
	memset(szBounds, 0, sizeof(szBounds));
	itoa(nBound, szBounds, 10);
	CString strBounds = szBounds;
	mmTemp.fza(strBounds);
	mmTemp.fz(m_bgNBounds.m_a, mmTemp.a);
	return TRUE;
}
