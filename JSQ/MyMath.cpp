// MyMath.cpp: implementation of the MyMath class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JSQ.h"
#include "MyMath.h"
#include "WkDebug.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//小于100的25个素数
int m_nPrime25[78498] = {2,3,5,7,11,13,17,19,23,29,
31,37,41,43,47,53,59,61,67,71,
73,79,83,89,97};

BigNum m_BNDeltRes[MAX_DIGIT_P*4];//备用的数
BigNum m_BigNumPrime25[25];
BOOL bBigNumPrimeHasInit = FALSE;

MyMath::MyMath()
{
//	strInput1 = NULL;
//	strInput2 = NULL;
	Clear(m_ZERO);
	Clear(m_ONE);
	m_ONE[1] = 1;
	Clear(m_TEN);
	m_TEN[2] = 1;
    m_TEN[0] = 2;
	ClearAll();

	if(!bBigNumPrimeHasInit)
	{
		for(int i=0;i<25;i++)
		{
			m_BNTool.fz2(m_BigNumPrime25[i].m_a, m_nPrime25[i]);
		}
		bBigNumPrimeHasInit = TRUE;
	}
}

MyMath::~MyMath()
{

}

CString MyMath::Add(CString nA, CString nB, CString nResult)
{
	CString nLi = nA;
	CString nLa = nB;
	int nLenA = nA.GetLength();
	int nLenB = nB.GetLength();

	if(nLenA>nLenB)
	{//将位数小的存储到nLi中
		nLi = nB;
		nLa = nA;
		int nTmpAB = nLenA;
		nLenA = nLenB;
		nLenB = nTmpAB;
	}

	CString strTempR;
	int nJW = 0;//进位
	for(int i=nLenB-1;i>=0;i--)
	{
		int j = -nLenB+i+nLenA;
		int nInc = nJW;
		if(j>=0)
			nInc = (int)(nLi[-nLenB+i+nLenA]-'0'+nJW);

		strTempR =  (char)( (int)nLa[i]+nInc );
		if((int)strTempR[0]>(int)'9')
		{
			strTempR = (char)((int)strTempR[0]-('9'-'0'+1));
			nJW = 1;
		}
		else
			nJW = 0;
		strTempR+=nResult;
		nResult = strTempR;
	}
	if(nJW==1)
	{
		strTempR = _T("1");
		strTempR+=nResult;
		nResult=strTempR;
	}

	return nResult;
}

int MyMath::fza(CString stra)
{
	int k = 0;
	CString strTmp = _T("");
	stra.TrimRight();
	LPSTR lstr;
	int nLenA = stra.GetLength();
	int nEtra = nLenA%WK_DIGIT_BASE_WIDTH;

	Clear(a);
	a[0] = nLenA/WK_DIGIT_BASE_WIDTH;
	if( nEtra > 0 )
	{
		a[0]++;
	}


	if(a[0]<1)
	{
		m_strError = _T("请输入你想计算的数.");
		return FALSE;
	}

	if(a[0]>=MAX_DIGIT)
	{
		m_strError = _T("a输入过大, 超过了位数限制.");
		return FALSE;
	}

	for(int i=a[0];i>=1;i--)
	{

		k = a[0]-i+1;
		//a[k] = stra[i-1] - '0';
		
		if(i==1)
		{
			strTmp = stra.Right(nLenA);
			if(nEtra==0)
			{
				strTmp = strTmp.Left(WK_DIGIT_BASE_WIDTH);
			}
			else
			{
				strTmp = strTmp.Left(nEtra);
			}
		}
		else 
		{
			if(k*WK_DIGIT_BASE_WIDTH <= nLenA)
			{
				strTmp = stra.Right(k*WK_DIGIT_BASE_WIDTH);
			}
			else
			{
				strTmp = stra;
			}
			strTmp = strTmp.Left(WK_DIGIT_BASE_WIDTH);
		}
		
		lstr = strTmp.GetBuffer(2);
		a[k] = atoi((char *)lstr);
		if(a[k]<0 || a[k]>=WK_DIGIT_BASE)
		{
			m_strError = _T("请输入数字！");
			return FALSE;
		}
	}

	ZZH(a);
	return TRUE;
}

BOOL MyMath::fzb(CString strb)
{
	int k = 0;
	CString strTmp = _T("");
	LPSTR lstr;
	int nLenB = strb.GetLength();
	int nEtra = nLenB%WK_DIGIT_BASE_WIDTH;

	Clear(b);
	b[0] = nLenB/WK_DIGIT_BASE_WIDTH;
	if( nEtra > 0 )
	{
		b[0]++;
	}

	if(b[0]>=MAX_DIGIT)
	{
		m_strError = _T("b输入过大, 超过了位数限制.");
		return FALSE;
	}

	for(int i=b[0];i>=1;i--)
	{
		
		k = b[0]-i+1;
		//b[k] = strb[i-1] - '0';
		
		if(i==1)
		{
			strTmp = strb.Right(nLenB);
			if(nEtra==0)
			{
				strTmp = strTmp.Left(WK_DIGIT_BASE_WIDTH);
			}
			else
			{
				strTmp = strTmp.Left(nEtra);
			}
		}
		else
		{
			strTmp = strb.Right(k * WK_DIGIT_BASE_WIDTH);
			strTmp = strTmp.Left(WK_DIGIT_BASE_WIDTH);
		}
		
		lstr = strTmp.GetBuffer(2);
		b[k] = atoi((char *)lstr);
		if(b[k]<0 || b[k]>=WK_DIGIT_BASE)
		{
			m_strError = _T("请输入数字！");
			return FALSE;
		}
	}


	ZZH(b);
	return TRUE;

}

BOOL MyMath::JSQADD()
{
	int i=1;
	int maxD = 0;//最大位数
	Clear(aAddb);
	if(a[0]>b[0])
		maxD = a[0];
	else
		maxD = b[0];
	aAddb[0] = maxD;

	for(;i<=maxD;i++)
	{
		aAddb[i] += (a[i] + b[i]);
		if(aAddb[i]>=WK_DIGIT_BASE)
		{
			if(i==maxD)
				aAddb[0]++;
			aAddb[i]-=WK_DIGIT_BASE;
			aAddb[i+1]++;
		}
	}


	for(i=0;i<MAX_DIGIT;i++)
		nRes[i] = aAddb[i];
	return TRUE;
}

void MyMath::Clear0(int aTmp[])
{
	memset(aTmp, 0, MAX_DIGIT*sizeof(int));
}

/**
 * 功能说明: 将a设置为0	
 * 添加日期: 2008-02-01 21:14
 */
BOOL MyMath::Clear(int aTmp[])
{
	memset(aTmp, 0, MAX_DIGIT*sizeof(int));
	aTmp[0] = 1;
	return TRUE;
}

CString MyMath::GetResult()
{
	CString strCh = _T("");
	
	strR = _T("");
	if(nRes[0]==0)
	{
		strR = _T("0");
		return strR;
	}

	strCh.Format(_T("%d"), nRes[nRes[0]]);
	strR+=strCh;
	for(int i=(nRes[0]-1);i>0;i--)
	{
		strCh.Format(WK_DIGIT_OUT_FORMAT, nRes[i]);
		strR+=strCh;
	}
	
	return strR;
}

BOOL MyMath::ClearAll()
{
	Clear(a);
	Clear(b);
	Clear(c);
	Clear(d);
	Clear(nRes);
	return TRUE;
}



/*
 *	aTmp = bTmp * cTmp + dTmp, 0<=dTmp<bTmp
 *
 *  添加日期: 2008-02-04 16:00
 */
BOOL MyMath::Div(const int aTmp[MAX_DIGIT],const int bTmp[MAX_DIGIT],
				 int cTmp[MAX_DIGIT],int dTmp[MAX_DIGIT])
{

	if( Compare(aTmp, bTmp) < 0 ) //aTmp<bTmp时直接返回
	{
		fz(dTmp, aTmp);
		Clear(cTmp); //将cTmp清零
		return TRUE;
	}

	BigNum bnC,bnD;
	int nDiff = 0;
	int i = 0;
	
	fz(bnD.m_a, aTmp);

	while( Compare(bnD.m_a, bTmp)>0 )
	{
		if(bnD.m_a[0]>bTmp[0])
		{
			nDiff = bnD.m_a[0] - bTmp[0] -1;
			if(bnD.m_a[bnD.m_a[0]]>bTmp[bTmp[0]])
			{
				nDiff++;
			}

			for(i=1; i<=bTmp[0]; i++)
			{
				bnD.m_a[i+nDiff]-=bTmp[i];
			}
			ZZH2C(bnD.m_a);
			
			bnC.m_a[nDiff+1]++;
			ZZH2D(bnC.m_a, nDiff+1);
		}
		else if(bnD.m_a[0]<bTmp[0])
		{
			//fz(nRes, bnD.m_a);
			fz(cTmp, bnC.m_a);
			fz(dTmp, bnD.m_a);
			return TRUE;
		}
		else if(bnD.m_a[0]==bTmp[0])
		{
			for(int idb=1;idb<=bnD.m_a[0];idb++)
			{
				bnD.m_a[idb]-=bTmp[idb];
			}
			ZZH2C(bnD.m_a);

			bnC.m_a[1]++;
			ZZH2D(bnC.m_a, 1);
		}
	}
	
	if(Compare(bnD.m_a, bTmp)==0)
	{
		Clear(bnD.m_a);
		bnC.m_a[1]++;
		ZZH2D(bnC.m_a, 1);
	}
		
	fz(cTmp, bnC.m_a);
	fz(dTmp, bnD.m_a);

	return TRUE;

}

BOOL MyMath::fz(int aTmp[], const int bTmp[])
{
	memcpy(aTmp, bTmp, sizeof(int)*MAX_DIGIT);
	return TRUE;
}

BOOL MyMath::fz2(int aTmp[], const int bTmp)
{
	int bTmp2 = bTmp;
	int nBit = 0;//每一位
	int nDigit = 0;

	Clear(aTmp);

	while(bTmp2>0)
	{
		nBit = bTmp2%WK_DIGIT_BASE;
		nDigit++;
		aTmp[nDigit] = nBit;
		bTmp2 = bTmp2/WK_DIGIT_BASE;
	}

	if(nDigit>1)
	{
		aTmp[0] = nDigit;
	}
	return TRUE;
}

BOOL MyMath::Minus(const int aTmp[], const int bTmp[], int cTmp[])
{
	BOOL bReturn = FALSE;
	if(Compare(aTmp, bTmp)>=0)
	{
		for(int i=1;i<=aTmp[0];i++)
		{
			cTmp[i] = aTmp[i] - bTmp[i];
		}
		ZZH(cTmp);
		bReturn = TRUE;
	}
	return bReturn;
}

int MyMath::Compare(const int aTmp[], const int bTmp[])
{
	if(aTmp[0]>bTmp[0])
		return 1;
	
	if(aTmp[0]<bTmp[0])
		return -1;

	for(int iTmp=aTmp[0];iTmp>0;iTmp--)
	{
		if(aTmp[iTmp]>bTmp[iTmp])
			return 1;
		if(aTmp[iTmp]<bTmp[iTmp])
			return -1;
	}
	return 0;
}

/*
 *	暂时只能处理如下类型的数（当WK_DIGIT_BASE为100时）
 1. a 已经为标准型
 2. a中元素除a[0]外，别的数范围在-99~9801之间, 并且a[0]>=1
 3.正在考虑中……
 */
BOOL MyMath::ZZH(int aTmp[])
{
	int i=1;
	int nDivRes = 1;//除商
	for(;i<MAX_DIGIT;i++)
	{
		if(aTmp[i]>=WK_DIGIT_BASE)
		{
			nDivRes = aTmp[i]/WK_DIGIT_BASE;
			aTmp[i]-=WK_DIGIT_BASE*nDivRes;
			aTmp[i+1]+=nDivRes;
		}

		if(aTmp[i]<0)
		{
			aTmp[i]+=WK_DIGIT_BASE;
			aTmp[i+1]--;
		}
	}

	for(i=MAX_DIGIT-1;i>0;i--)
	{
		if(aTmp[i]>0)
		{
			aTmp[0] = i;
			return TRUE;
		}
	}

	BOOL bIsZero = TRUE;
	for(int ij=aTmp[0];ij>0;ij--)
	{
		if(aTmp[ij]!=0)
		{
			bIsZero = FALSE;
			break;
		}
	}

	if(bIsZero)
		aTmp[0] = 1;

	return TRUE;
}

BOOL MyMath::MinusEq(int aTmp[], int bTmp[])
{
	if(aTmp[0]!=bTmp[0])
		return FALSE;
	
	int i = aTmp[0];
	for(;i>0;i--)
	{
		if(aTmp[i]>bTmp[i])
		{//说明a>b
			Minus(aTmp, bTmp, a);
			fz(nRes, a);
			return TRUE;
		}
		if(aTmp[i]<bTmp[i])
		{//说明a<b
			fz(nRes, aTmp);
			return TRUE;
		}
	}
	Clear(a);
	Clear(nRes);//能到这个地方来当且仅当a=b
	c[1]++;
	ZZH(c);
	Clear(d);
	return TRUE;
	
}

/*
 *	   -1	计算出错
        0	正在计算
		1	正在计算，而且已经计算得到一个结果, 需要继续计算
		10	计算结束
 */
int MyMath::Factor()
{
	if( Compare(a, m_ZERO)<=0 )
		return -1;

	nCircle[1]++;
	ZZH2(nCircle);

	//if(bDiff==1 && b[1]%2==1 && a[1]%2==1)
	//	bDiff = 2;

	int nOnce;
	int maxOnce = 2000;//每次循环最多运行的步数

	/*
		测试例子
		 10000  CPU:35%
		20000  CPU:87%   (2004.11.25)
		下面开始以(10^17-1)/9为测试例子
		规定：每一步的运行时间不得超过100ms，现在测试较好的情况是maxOnce=100
		400	250ms
		800	703ms
		100	16ms
		10000	16243ms
		1000
		从今天起以a = (10^233-1)/9作为测试例子，
		现在测试较好的情况是maxOnce=1000,其中MAX_DIGIT=1000
	*/

	int nTempmodRes[MAX_DIGIT];
	for(nOnce=0;nOnce<maxOnce;nOnce++)
	{
		b[1]+=bDiff;
		ZZH2(b);

		if(b[0]==2 && b[1]<=2 && b[2]==21)
		{
			int ndeg = 1;
		}

		if( Compare(aSqrt, b)<0 )//当b*b>a时说明a是素数
		{
			fz(nRes, a);
			GetResult();
			return 10;
		}

		if(nOnce==237)
		{
			int nDeg23 = 1;
		}

		if(!IsPrime2(b))
			continue;

		Mod(a, b, nTempmodRes);

		if(nTempmodRes[0]!=1 || nTempmodRes[1]!=0)
			continue;
		
		
		Clear(c);
		Clear(d);
		
		//if(!Div())
		//	return -1;
		Div(a,b,c,d);

		
		
		if(Compare(a, b)<=0)
		{
			fz(nRes, b);
			GetResult();
			return 10;
		}			
		if(Compare(d, m_ZERO)==0)
		{
			fz(nRes, b);
			GetResult();
			fz(a, c);
			b[1]-=bDiff;
			ZZH(b);
			Sqrt(a, aSqrt);
			return 1;
		}
	}
	return 0;
}


CString MyMath::GetResultMy(int aTmp[])
{
	CString strRet = _T("");
	CString strCh = _T("");
	
	if(aTmp[0]==0)
	{
		strRet = _T("0");
		return strRet;
	}
	
	strCh.Format(_T("%d"), aTmp[aTmp[0]]);
	strRet+=strCh;
	for(int i=(aTmp[0]-1);i>0;i--)
	{
		strCh.Format(WK_DIGIT_OUT_FORMAT, aTmp[i]);
		strRet+=strCh;
	}
	
	return strRet;

}

BOOL MyMath::FactorPrepare()
{
	Clear(b);
	Clear(nCircle);
	fz(nReserved, a);
	b[0] = 1;
	b[1] = 1;
	bDiff = 1;
	Sqrt(a, aSqrt);
	return TRUE;

}

/*
 *	计算aTmp的平方根，结果存放在bTmp中
 */
BOOL MyMath::Sqrt(int aTmp[], int bTmp[])
{
	Clear(bTmp);
	if(aTmp[0]<=1)//当a是1位数时, b=sqrt(a)
	{
		fz(bTmp,aTmp);
		bTmp[1] = (int)sqrt((float)aTmp[1]);
		return TRUE;
	}

	//使用迭代法求出a的平方根
	int nCompRes = 0;
	BigNum bnMin;
	BigNum bnMax;
	BigNum bnSqrtTmp;
	bnMax.m_a[1] = 1;//Let bnMax=1
	
	//当a[0]>10时，起始的bnMax可从10^(a[0]/2-1)开始
	if(aTmp[0]>10)
	{
		int nBitTmp = a[0]/2;
		bnMax.m_a[0] = nBitTmp;
		bnMax.m_a[nBitTmp] = 1;
		bnMax.m_a[1] = 0;
	}
	Mult(bnMax.m_a, bnMax.m_a, bnSqrtTmp.m_a);
	nCompRes = Compare(bnSqrtTmp.m_a, aTmp);
	while(nCompRes<=0)//当bnMin*bnMin<a时
	{
		fz(bnMin.m_a, bnMax.m_a);
		if(nCompRes==0)//当bnMax*bnMax==a时直接返回
		{
			fz(bTmp, bnMin.m_a);
			return TRUE;
		}

		Mult10(bnMax.m_a, bnMax.m_a);//Let bnMax = bnMax*10
		Mult(bnMax.m_a, bnMax.m_a, bnSqrtTmp.m_a);
		nCompRes = Compare(bnSqrtTmp.m_a, aTmp);
		if(nCompRes<0) 
		{
			continue;
		}
		BigNum bgIGetResTmp;
		BigNum bgIDivResS;//除得的商
		BigNum bgIDivResYS;//除得的余数
		BigNum bgI2;//bgI2 = 2;
		bgI2.m_a[1] = 2;
		fz(bgIGetResTmp.m_a, bnMin.m_a);
		bgIGetResTmp.AddSmallDigit(1);			
		while(Compare(bgIGetResTmp.m_a, bnMax.m_a)!=0)//采用二分法计算
		{//当bnMin*bnMin<a并且bnMax*bnMax>a时，其中bnMax=bnMin*10
			Add(bnMin.m_a, bnMax.m_a, bgIGetResTmp.m_a);
			Div(bgIGetResTmp.m_a, bgI2.m_a, bgIDivResS.m_a, bgIDivResYS.m_a);
			Mult(bgIDivResS.m_a, bgIDivResS.m_a, bnSqrtTmp.m_a);
			nCompRes = Compare(bnSqrtTmp.m_a, aTmp);
			if(nCompRes<0)
			{
				fz(bnMin.m_a, bgIDivResS.m_a);
			}
			else if(nCompRes==0)
			{
				fz(bTmp, bgIDivResS.m_a);
				return TRUE;
			}
			else if(nCompRes>0)
			{
				fz(bnMax.m_a, bgIDivResS.m_a);
			}
			fz(bgIGetResTmp.m_a, bnMin.m_a);
			bgIGetResTmp.AddSmallDigit(1);
		}
		break;
	}
	fz(bTmp, bnMin.m_a);

	return TRUE;
}

/*
 *	此函数为内部函数，当a为1位时，返回sqrt(a), 别的情况不一定返回sqrt(a)
 */
BOOL MyMath::sqrtOwn(int aTmp[], int bTmp[])
{
	Clear(bTmp);
	if(aTmp[0]<=1)//当a是1位数时, b=sqrt(a)
	{
		fz(bTmp,aTmp);
		bTmp[1] = (int)sqrt((float)aTmp[1]);
		return TRUE;
	}
	
	int nDigitTmp = 1;
	if(aTmp[0]%2==0)
	{
		nDigitTmp = aTmp[0]/2+1;
		bTmp[0] = nDigitTmp;
		bTmp[nDigitTmp] = 1;
	}
	else
	{//sqrt(12345) = 1000
		int nDigitTmp = (aTmp[0]+1)/2+1;
		bTmp[0] = nDigitTmp;
		bTmp[nDigitTmp] = 1;
	}
	return TRUE;
}


BOOL MyMath::ZZH2(int aTmp[])
{
	int iTmp;

	for(iTmp=1;iTmp<=aTmp[0];iTmp++)
	{
		if(aTmp[iTmp]>=WK_DIGIT_BASE)
		{
			aTmp[iTmp]-=WK_DIGIT_BASE;
			aTmp[iTmp+1]++;
		}
		else
			return TRUE;
	}

	if(aTmp[aTmp[0]+1]>0)
		aTmp[0]++;

	return TRUE;
}


BOOL MyMath::ZZH2A(int aTmp[])
{
	int iTmp;
	
	for(iTmp=1;iTmp<=aTmp[0];iTmp++)
	{
		if(aTmp[iTmp]<0)
		{
			aTmp[iTmp]+=WK_DIGIT_BASE;
			aTmp[iTmp+1]--;
		}
	}

	BOOL b_aTmpEqualZero = TRUE;//a是否等于0
	if(aTmp[aTmp[0]]==0)
	{
		for(iTmp=aTmp[0];iTmp>=1;iTmp--)
		{
			if(aTmp[iTmp]>0)
			{
				aTmp[0] = iTmp;
				b_aTmpEqualZero = FALSE;
				break;
			}

		}
	}
	else
		b_aTmpEqualZero = FALSE;


	if(b_aTmpEqualZero)
	{
		aTmp[0] = 1;
	}

	return TRUE;
}

/*
 *	为乘法准备。
 *  注意在使用此函数时需预先保证aTmp的位数没有越界。
 *
 *  添加日期: 2008-02-04 16:19
 */
BOOL MyMath::ZZH2B(int aTmp[])
{
	int i=1;
	int nDivRes = 1;//除商

	for(;i<=aTmp[0];i++)
	{
		if(aTmp[i]>=WK_DIGIT_BASE)
		{
			nDivRes = aTmp[i]/WK_DIGIT_BASE;
			aTmp[i]-=WK_DIGIT_BASE*nDivRes;
			aTmp[i+1]+=nDivRes;

			if(i==aTmp[0])
			{
				aTmp[0]++;
				return TRUE;
			}
		}
		
		if(aTmp[i]<0)
		{
			aTmp[i]+=WK_DIGIT_BASE;
			aTmp[i+1]--;
		}
	}
	
	//该数可能为0，所以以下代码是为了预防输入的数为
	//类似aTmp[0]=2, aTmp[i]=0, i=1,2,...的情形。
	BOOL bIsZero = TRUE;
	for(int ij=aTmp[0];ij>0;ij--)
	{
		if(aTmp[ij]!=0)
		{
			bIsZero = FALSE;
			break;
		}
	}
	
	if(bIsZero)
		aTmp[0] = 1;
	
	return TRUE;
}

/*
 *	为除法准备。
 *
 *  添加日期: 2008-02-04 19:56
 */
BOOL MyMath::ZZH2C(int aTmp[])
{
	int i=1;
	//int nDivRes = 1;//除商
	
	for(;i<=aTmp[0];i++)
	{
		if( aTmp[i] < 0 )
		{
			//nDivRes = aTmp[i]/WK_DIGIT_BASE;
			//aTmp[i] -= WK_DIGIT_BASE*nDivRes;
			aTmp[i] += WK_DIGIT_BASE;
			aTmp[i+1] -= 1;
		}
	}
	
	//该数可能为0，所以以下代码是为了预防输入的数为
	//类似aTmp[0]=2, aTmp[i]=0, i=1,2,...的情形。
	BOOL bIsZero = TRUE;
	for(int ij=aTmp[0];ij>0;ij--)
	{
		if(aTmp[ij]!=0)
		{
			if(ij<aTmp[0])
			{
				aTmp[0] = ij;
			}
			bIsZero = FALSE;
			break;
		}
	}
	
	if(bIsZero)
		aTmp[0] = 1;
	
	return TRUE;
}



int MyMath::shugen(int aTmp[])
{
	int nSG = 0;
	for(int i=1;i<=aTmp[0];i++)
		nSG+=aTmp[i];
	return nSG;
}

BOOL MyMath::IsPrime(int bTmp[])
{
	if(bTmp[0]==1)
	{//当bTmp只有1位时使用穷举法判断
		if( bTmp[1]==2
			|| bTmp[1]==3 
			|| bTmp[1]==5
			|| bTmp[1]==7)
		{
			return TRUE;
		}
		else
			return FALSE;
	}


	BigNum bgnI1;
	BigNum bgn_bTmpSqrt;
	bgnI1.m_a[1] = 2;
	Sqrt(bTmp, bgn_bTmpSqrt.m_a);//bgn_bTmpSqrt = sqrt(a)

	

	//当bTmp大于或等于10时使用试除法判断
	for( ; Compare(bgnI1.m_a, bgn_bTmpSqrt.m_a)<=0; bgnI1.AddSmallDigit(1) )
	{
		if(!IsPrime2(bgnI1.m_a))//要求试除的数不能为小合数
			continue;

//		if(bgnI1.m_a[0]>4)//最多只试除到9999
//			break;

		BigNum bgnJ;
		Mod(bTmp, bgnI1.m_a, bgnJ.m_a);
		if(bgnJ.m_a[0]==1 && bgnJ.m_a[1]==0)
			return FALSE;
	}
	return TRUE;
}

/*
 *	这里要求b>=2
 如果返回TRUE, 说明bTmp或者是素数，或者为最小质因子大于100的合数
 当返回FALSE，说明bTmp是合数，且有一小于100的质因子
 */
BOOL MyMath::IsPrime2(int bTmp[])
{	
	BOOL bPrime = TRUE;
	BigNum bgnII2;
	int i = 0;

	while( Compare( m_BigNumPrime25[i].m_a, bTmp)<0 )
	{
		Mod_b1000(bTmp, m_BigNumPrime25[i].m_a, bgnII2.m_a);
		if(bgnII2.m_a[0]==1 && bgnII2.m_a[1]==0)
		{
			bPrime = FALSE;
			break;
		}
		i++;
		if(i>24)
			break;
	}
	//如果其质因子大于100，则认为这个数是素数
	return bPrime;
}

/*
	专为OnTimerDelt设计
	这里要求bTmp>1e6
	添加日期: 2005-02-06 10:54
 */
BOOL MyMath::IsPrime3(int bTmp[], int nLimitN)
{	
	BOOL bPrime = TRUE;
	BigNum bgnII2;
	int i = 0;
	
	while( TRUE )
	{
		Mod_b1000(bTmp, m_BigNumPrime25[i].m_a, bgnII2.m_a);
		if(bgnII2.m_a[0]==1 && bgnII2.m_a[1]==0)
		{
			bPrime = FALSE;
			break;
		}
		i++;
		if(i>24 || i>nLimitN)
			break;
	}
	return bPrime;
}

/*
 *	判断bTmp是否为素数, 如果为合数则将最小的质因子存储到bnFactor中
 */
BOOL MyMath::IsPrimeGetFactor(BigNum *bnTmp, BigNum *bnFactor)
{
	int bTmp[MAX_DIGIT];
	fz(bTmp, bnTmp->m_a);

	BigNum bgnI1;
	bgnI1.m_a[1] = 2;
	
	BigNum bgn_bTmpSqrt;
	Sqrt(bTmp, bgn_bTmpSqrt.m_a);//bgn_bTmpSqrt = sqrt(a)
	
	for( ; Compare(bgnI1.m_a, bgn_bTmpSqrt.m_a)<=0; bgnI1.AddSmallDigit(1) )
	{
		if(!IsPrime2(bgnI1.m_a))//要求试除的数不能为小合数
			continue;
		
		//下面这句话是垃圾中的精品
		//这种只做危险事情不说明为什么的语句以后尽量不要出现
		//Chenbo 2005-10-09 20:37 add the explaination
		//if(bgnI1.m_a[0]>4)//最多只试除到9999
		//	break;
		
		BigNum bgnJ;
		Mod(bTmp, bgnI1.m_a, bgnJ.m_a);
		if(bgnJ.m_a[0]==1 && bgnJ.m_a[1]==0)
		{
			fz(bnFactor->m_a, bgnI1.m_a);
			return FALSE;
		}
	}
	return TRUE;
}

int MyMath::SigDIV(int aTmp[], int bTmp[])
{
	int nResult = 0;

	//先去除a<=b的情形
	int aVSb = Compare(aTmp, bTmp);
	if(aVSb<0)
	{
		return 0;
	}

	if(aVSb==0)
	{
		return 1;
	}
	
	
	nResult = SigDIV2(aTmp, bTmp);

	return nResult;
}

int MyMath::SigDIV2(int aTmp[], int bTmp[])
{
	int nResult = 0;
	int aD = aTmp[0];
	int bD = bTmp[0];
	
	int aFTN2 = aTmp[aD]*WK_DIGIT_BASE+aTmp[aD-1];
	int aFTN3 = aFTN2*WK_DIGIT_BASE+aTmp[aD];
	int bFTN2 = bTmp[bD]*WK_DIGIT_BASE+bTmp[bD-1];
	int bFTN3 = bFTN2*WK_DIGIT_BASE+bTmp[bD];
	
	if(bD<=3)
	{
		nResult = aFTN3/bFTN3;
		if(nResult>(WK_DIGIT_BASE*WK_DIGIT_BASE)) 
		{
			nResult = nResult/(WK_DIGIT_BASE*WK_DIGIT_BASE);
		}
		else if(nResult>WK_DIGIT_BASE) 
		{
			nResult = nResult/WK_DIGIT_BASE;
		}
	}
	else
	{
		nResult = aFTN3/(bFTN3+1);
	}
	return nResult;
}


int MyMath::SigDIV2_33(int aTmp[], int bTmp[])
{
	int nResult = 0;
	int aD = aTmp[0];
	int bD = bTmp[0];
	
	
	
	if(bD<2)
	{//1<=b<10
		nResult = aTmp[aD]/(bTmp[1]+1);
	}
	else
	{
		double aFTN2 = (double)aTmp[aD]*WK_DIGIT_BASE+aTmp[aD-1];
		double bFTN2 = (double)bTmp[bD]*WK_DIGIT_BASE+bTmp[bD-1];
		if(bD==2)
		{//1<=b<10
			nResult = (int)(aFTN2/(bFTN2+1.0));
		}
		else//三位以上
		{
			double aFTN3 = (double)aFTN2*WK_DIGIT_BASE+aTmp[aD-2];
			double bFTN3 = (double)bFTN2*WK_DIGIT_BASE+bTmp[bD-2];
			nResult = (int)(aFTN3/(bFTN3+1.0));
		}
	}
	return nResult;
}


int MyMath::SigDIV2_32(int aTmp[], int bTmp[])
{
	int nResult = 0;
	int aD = aTmp[0];
	int bD = bTmp[0];
	
	int aFTN2 = aTmp[aD]*WK_DIGIT_BASE+aTmp[aD-1];
	
	if(bD<2)
	{//1<=b<10
		nResult = aFTN2/bTmp[1];
	}
	else
	{
		//long aFTN3 = aFTN2*WK_DIGIT_BASE+aTmp[aD-2];
		//long bFTN2 = bTmp[bD]*WK_DIGIT_BASE+bTmp[bD-1];

		double aFTN3 = (double)aFTN2*WK_DIGIT_BASE+aTmp[aD-2];
		double bFTN2 = (double)bTmp[bD]*WK_DIGIT_BASE+bTmp[bD-1];

		nResult = (int)(aFTN3/(bFTN2+1));
	}
	return nResult;
}

BOOL MyMath::Mod_b1000(int aTmp[], int bTmp[], int cTmp[])
{
	int nB = bTmp[2]*WK_DIGIT_BASE + bTmp[1];
	int nA = 0;
	int naD = aTmp[0];
	int nX = 0;//将a分为的段数,例如1234567将分为两段123 4567
	           //    123456789054321将分为4段123 4567 8905 4321
	int nC = 0;
	int i = 0;
	int j = 0;
	int naDMod2 = naD%2;
	nX = naD/2;
	if(naDMod2!=0)
	{
		nX++;
	}
	if(naD<4)
	{
		nA = ( aTmp[3] * WK_DIGIT_BASE + aTmp[2]) * WK_DIGIT_BASE
			+ aTmp[1];
		nC = nA%nB;
	}
	else
	{//a>=1e8
		nC = 0;
		if(naDMod2>0)
		{
			for(i=naD;i>(naD-naDMod2);i--)
			{
				nC = ( nC * WK_DIGIT_BASE + aTmp[i] );
			}
			nC = nC%nB;
			nX--;
		}

		for(i=nX;i>0;i--)
		{
			for(j=0;j<2;j++)
			{
				nC=(nC*WK_DIGIT_BASE+aTmp[i*2-j]);
			}
			nC = nC%nB;
		}
	}

	Clear0(cTmp);

	cTmp[2] = nC/WK_DIGIT_BASE;
	cTmp[1] = nC%WK_DIGIT_BASE;
	if(cTmp[2]>0)
	{
		cTmp[0] = 2;
	}
	else
	{
		cTmp[0] = 1;
	}
	return TRUE;
}

BOOL MyMath::Mod(int aTmp[], int bTmp[], int cTmp[])
{
	//由于大部分b均为15位的（计算Deltp时，所以此段代码暂时注掉）
	//当b小于10000
	//if(bTmp[0]<3)
	//{
	//	return Mod_b1000(aTmp, bTmp, cTmp);
	//}

	fz(cTmp, aTmp);
	
	if( Compare(aTmp,bTmp)<0 )
	{//当a<b时得到的余数为a直接返回
		return TRUE;
	}

	int nSigDIV = 0;
	int n8Tmp1 = 0;
	//CString strDebug = _T("");

	while( Compare(cTmp, bTmp)>0 )
	{		
		if(cTmp[0]>bTmp[0])
		{
			int nDiff = cTmp[0] - bTmp[0] -1;
			if( cTmp[cTmp[0]]>bTmp[bTmp[0]] )
			{
				nSigDIV = SigDIV2_33(cTmp, bTmp);

				//strDebug.Format(_T("MyMath.cpp, Ln989. nSigDIV=%d"),nSigDIV);
				//WkDebug::write(strDebug);
				//此时存在比较简单的高校算法
				for(int i=1;i<=bTmp[0];i++)
				{
					if(nSigDIV<=1)
					{
						cTmp[i+nDiff+1]-=bTmp[i];
					}
					if(nSigDIV>1)
					{
						cTmp[i+nDiff+1]-=bTmp[i]*nSigDIV;
						if(cTmp[i+nDiff+1]<0)
						{
							n8Tmp1 = (-cTmp[i+nDiff+1])/WK_DIGIT_BASE;
							if(cTmp[i+nDiff+1]%WK_DIGIT_BASE!=0)
							{
								n8Tmp1++;
							}
							if(i<bTmp[0])
							{
								cTmp[i+nDiff+1]+=(n8Tmp1*WK_DIGIT_BASE);
								cTmp[i+nDiff+2]-=n8Tmp1;
							}
							else
							{
								WkDebug::write(_T("MyMath.cpp, Ln1005. c<0"));
							}
						}
					}
				}//for(int i=1;i<=bTmp[0];i++)
			}//if( cTmp[cTmp[0]]>bTmp[bTmp[0]] )
			else
			{
				nSigDIV = SigDIV2_32(cTmp, bTmp);
				//strDebug.Format(_T("MyMath.cpp, Ln1017. nSigDIV=%d"),nSigDIV);
				//WkDebug::write(strDebug);
				for(int i=1;i<=bTmp[0];i++)
				{
					cTmp[i+nDiff]-=bTmp[i]*nSigDIV;

					if(cTmp[i+nDiff]<0)
					{
						n8Tmp1 = (-cTmp[i+nDiff])/WK_DIGIT_BASE;
						if(cTmp[i+nDiff]%WK_DIGIT_BASE!=0)
						{
							n8Tmp1++;
						}
						
						cTmp[i+nDiff]+=(n8Tmp1*WK_DIGIT_BASE);
						cTmp[i+nDiff+1]-=n8Tmp1;
					}
				}

				
			}
			ZZH2A(cTmp);
		}
		else if(cTmp[0]==bTmp[0])
		{
			int cTmpMod2[MAX_DIGIT];
			MinusEq2(cTmp, bTmp, cTmpMod2);
			fz(cTmp, cTmpMod2);
			return TRUE;
		}				
	}
	
	if( Compare(cTmp, bTmp)==0 )
		fz(cTmp, m_ZERO);
	
	return TRUE;
}

//a[]是否能被b[]整除，如果可以的话返回TRUE,否则返回FALSE
BOOL MyMath::IsMod2(int aTmp[], int bTmp[])
{
	int cTmpIsMod2[MAX_DIGIT];
	Mod(aTmp, bTmp, cTmpIsMod2);
	if(cTmpIsMod2[0]==1 && cTmpIsMod2[1]==0)
		return TRUE;
	return FALSE;
}


/*
 *	此函数特为MyMath::IsPrime2(int bTmp[])准备
 */
BOOL MyMath::IsMod2a(int aTmp[], int bTmp)
{
	int bTmpIsMod2a[MAX_DIGIT];
	Clear(bTmpIsMod2a);
	bTmpIsMod2a[3] = bTmp/100;
	bTmpIsMod2a[2] = (bTmp/10)%10;
	bTmpIsMod2a[1] = bTmp%10;
	
	for(int i=3;i>=1;i--)
	{
		if(bTmpIsMod2a[i]!=0)
		{
			bTmpIsMod2a[0] = i;
			break;
		}
	}

	return IsMod2(aTmp, bTmpIsMod2a);
}

//a[0]=b[0]时，aTmp mod bTmp = cTmp
BOOL MyMath::MinusEq2(int aTmp[], int bTmp[], int cTmp[])
{
	if(aTmp[0]!=bTmp[0])
		return FALSE;
	
	fz(cTmp, aTmp);
	int i = 0;
	int n8Tmp1 = 0;
	int nSigDIV = 0;
	CString strDebug = _T("");
	while(Compare(cTmp, bTmp)>=0)
	{
		nSigDIV = SigDIV2_33(cTmp, bTmp);
		//strDebug.Format(_T("MyMath.cpp, Ln1103. nSigDIV=%d"),nSigDIV);
		//WkDebug::write(strDebug);

		if(nSigDIV<1)
		{
			nSigDIV = 1;
		}
		for(i=1;i<=cTmp[0];i++)
		{
			cTmp[i]-=(bTmp[i]*nSigDIV);

			if(cTmp[i]<0)
			{
				n8Tmp1 = (-cTmp[i])/WK_DIGIT_BASE;
				if(cTmp[i]%WK_DIGIT_BASE!=0)
				{
					n8Tmp1++;
				}
				if(i<cTmp[0])
				{
					cTmp[i]+=(n8Tmp1*WK_DIGIT_BASE);
					cTmp[i+1]-=n8Tmp1;
				}
				else
				{
					WkDebug::write(_T("MyMath.cpp, Ln1124. c<0"));
				}
			}
		}
		//ZZH(cTmp);
		ZZH2A(cTmp);
	}
	return TRUE;
}

/*
	a mod b = c (必须如此)
	此函数调用前必须给a和b赋值，计算得到的结果存放到c中
	创建日期: 2004-11-28 12:19
*/
BOOL MyMath::JSQMOD()
{
	Mod(a, b, c);
	fz(nRes, c);
	return TRUE;
}

/*
    Description: d*a-e*b=c
		输入是a和b,输出是c,d,e
		采用Euclid算法，输出的结果满足0<=d<=b,0<=e<=a.

	Time: 2009-07-05 07:17
*/
void MyMath::gcd(const int aTmp[MAX_DIGIT], const int bTmp[MAX_DIGIT], int cTmp[MAX_DIGIT],
		int dTmp[MAX_DIGIT],int eTmp[MAX_DIGIT])
{
	// "n" is a
	// "u" is b
	// "a" is d
	// "b" is e
	// "gcd(n,u)" is c
	int nDebug = 1;
	int nTmp1[MAX_DIGIT];
	int nTmp2[MAX_DIGIT];
	int aTmp1[MAX_DIGIT];
	int bTmp1[MAX_DIGIT];
	int aTmp2[MAX_DIGIT];
	int bTmp2[MAX_DIGIT];
	int qTmp[MAX_DIGIT];
	int rTmp[MAX_DIGIT];
	int tTmp[MAX_DIGIT];

	int tTmp2[MAX_DIGIT];
	int tTmp3[MAX_DIGIT];
	int aTmp3[MAX_DIGIT];
	int dTmp3[MAX_DIGIT];

	Clear(c);
	Clear(d);
	Clear(e);

	fz(nTmp1,aTmp);
	fz(nTmp2,bTmp);
	fz(aTmp1,m_ONE);
	fz(bTmp1,m_ZERO);
	fz(aTmp2,m_ZERO);
	fz(bTmp2,m_ONE);
	
	while(nDebug<1000)
	{
		nDebug++;
		Div(nTmp1,nTmp2,qTmp,rTmp);
		if(Compare(rTmp,m_ZERO)==0)
		{
			//gcd(n,u)=n2
			if(Compare(aTmp2,m_ZERO)<=0)
			{
				Add(aTmp2,bTmp,aTmp2);
				Minus(aTmp,bTmp2,bTmp2);
			}

			fz(cTmp,nTmp2);
			fz(dTmp,aTmp2);
			fz(eTmp,bTmp2);
			break;
		}
		else
		{
			fz(nTmp1,nTmp2);
			fz(nTmp2,rTmp);
			fz(tTmp,aTmp2);//t=a2

			//a2=a1-q*a2
			Mult(qTmp,aTmp2,tTmp2);
			if(Compare(aTmp1,tTmp2)<=0)
			{
				Minus(tTmp2,aTmp1,aTmp2);

				fz(aTmp1,tTmp);

				fz(tTmp,bTmp2);

				//b2=b1-q*b2
				Mult(qTmp,bTmp2,tTmp2);
				if(Compare(tTmp2,bTmp1)>=0)
				{
					Minus(tTmp2,bTmp1,bTmp2);
				}
				else
				{
					Minus(bTmp1,tTmp2,bTmp2);
				}

				//当a2为负数时
				//a2 = a2 + (|a2|/b + 1) * b
				//b2 = b2 - (|a2|/b + 1) * a
				Div(aTmp2,bTmp,aTmp3,dTmp3);
				Add(aTmp3,m_ONE,aTmp3);

				Mult(aTmp3,bTmp,tTmp3);
				Minus(tTmp3,aTmp2,aTmp2);

				Mult(aTmp3,aTmp,tTmp3);
				Minus(tTmp3,bTmp2,bTmp2);

			}
			else
			{
				Minus(aTmp1,tTmp2,aTmp2);

				fz(aTmp1,tTmp);

				fz(tTmp,bTmp2);

				//b2=b1-q*b2
				Mult(qTmp,bTmp2,tTmp2);
				if(Compare(tTmp2,bTmp1)>=0)
				{
					Minus(tTmp2,bTmp1,bTmp2);
				}
				else
				{
					Minus(bTmp1,tTmp2,bTmp2);
				}
			}
			

			fz(bTmp1,tTmp);
		}

	}



	



	/**
	A[1]=133  B[1]=77    C[1]=0
	gcd(133,77)

	A[2]=77   B[2]=56    C[2]=1
	133-1*77=56		gcd(133,77)=gcd(77,56)
	A[2]=B[1] B[2]=A[1]-C[2]*B[1]

	A[3]=56   B[3]=21    C[3]=1
	77-1*56=21      gcd(77,56)=gcd(56,21)
	A[3]=B[2] B[3]=A[2]-C[3]*B[2]

	A[4]=21   B[4]=14    C[4]=2
	56-2*21=14      gcd(56,21)=gcd(21,14)
	A[4]=B[3] B[4]=A[3]-C[4]*B[3]

    A[5]=14   B[5]=7     C[5]=1
	21-1*14=7       gcd(21,14)=gcd(14,7)
	A[5]=B[4] B[5]=A[4]-C[5]*B[4]

	A[6]=7    B[6]=0     C[6]=2
	14-2*7=0        gcd(14,7)=7
	7=14-7=A[5]-(C[6]-1)*B[5]



	*/


}


/*
	gcd(a,b) = c
	此函数调用前必须给a和b赋值，计算得到的结果存放到c中
	额外结果放在strRessage.
	创建日期: 2009-07-05 06:59
*/
BOOL MyMath::JSQGCD()
{
	gcd(a, b, c, d, e);
	fz(nRes, c);
	m_strError.Format(_T("%s*%s-%s*%s=%s"), GetResultMy(d),GetResultMy(a),
		GetResultMy(e),GetResultMy(b),GetResultMy(c));
	return TRUE;
}

BOOL MyMath::JSQREP10()
{
	int i = 0;
	int nRep = 1;
	int nDGT = IntMDToInt(a);
	int nDGT2 = 0;
	if ( nDGT < 0 || nDGT > ((MAX_DIGIT-2) * WK_DIGIT_BASE_WIDTH) )
	{
		m_strError = _T("输入的数过大.");
		return FALSE;
	}
	Clear(b);
	nDGT2 = nDGT % WK_DIGIT_BASE_WIDTH;
	nDGT = nDGT / WK_DIGIT_BASE_WIDTH;

	for(i=0;i<nDGT2;i++)
	{
		nRep *= 10;
	}
	
	b[0] = nDGT+1;
	b[nDGT+1] = nRep;

	fz(nRes, b);
	return TRUE;
}


int MyMath::IntMDToInt(int aTmp[])
{
	CString strTemp;
	strTemp = GetResultMy(aTmp);
	if(aTmp[0]>8)
		return 0;
	return atoi(strTemp);
}

BOOL MyMath::JSQMINUS()
{
	if(Compare(a, b)<0)
		return FALSE;
	int nTmp;
	for(nTmp = 1;nTmp<=b[0];nTmp++)
		a[nTmp]-=b[nTmp];
	ZZH(a);
	fz(nRes,a);
	return TRUE;

}


/*
	功能说明:  最终结果存放到变量nRes中,b用于存储余数,只计算Delt<10000的数，超过的部分将不予处理
			   a表示待计算的数，只计算素数
			   现在此函数暂用于搜索Delt(10, p)<1e4的数p, p>100e4
			   要求Delt必须小于10000
 
               现在对返回值作一说明,以免以后老是产生误会
               当且仅当a为素数并且Delt(a)<1e4时才返回TRUE,
			   别的情形一律返回FALSE, 规定Delt(2)=0, Delt(5)=0
			   又为了显示的区别
			   设以下区分
			   1. a为合数且其一质因子小于100,则nRes=0
			   2. a的素性未定,且若a为合数其最小质因子大于100,再就是Delt(a)>=1e4
			      此时nRes=10000
			   3. a为合数,并且a的最小质因子大于100,Delt(a)<1e4
			      此时nRes=Delt(a)
			   ChenBo 2005-10-09 20:55 add the explaination
	添加日期: 2005-02-06 10:59
*/
BOOL MyMath::JSQDELT()
{
	BOOL bReturn = FALSE;
	
	//初值判断结束
	//////////////////////////////////////////////////////////////////////////
	
	if((a[0]*WK_DIGIT_BASE_WIDTH)<18)
	{
		__int64 n64Tmp = 0;
		IntAryToInt64(a, &n64Tmp);
		
		//先判断是否为素数
		if(!IsPrime64_2(n64Tmp))
		{
			fz(nRes, m_ZERO);
			//m_strError = _T("输入的数必须为素数!");
			return FALSE;
		}
		
		//int n32Res = Delt15(n64Tmp);
		int n32Res = Delt15(n64Tmp);
		if(n32Res>0 && n32Res<WK_DIGIT_DELT1E5) 
		{
			fz2(nRes, n32Res);
			return TRUE;
		}
		
		//nRes[0] = 2;
		//nRes[2] = 10;
		fz2(nRes, 100000);
		return FALSE;
	}//if(a[0]<8)
	
	if(!IsPrime2(a))
	{
		fz(nRes, m_ZERO);
		m_strError = _T("输入的数必须为素数!");
		return bReturn;
	}
	
	

	int i = 0;
	int nCC = 1;//存放得到的Delt值
	BOOL bGetResult = TRUE;//是否已经得到了结果
	Clear(b);
	b[1] = 1;//let b = 1;
	for(;nCC+=WK_DELT_STEP_CUR;)
	{	
		//if(Compare(b, m_ZERO)==0 || c[0]>4)
		if(nCC>WK_DIGIT_DELT1E5)
		{//当b＝0或c>1e4时退出
			//======================================
			// 这里需要加一些注释, 就是一般情况下b是不会等于0的,
			// 假设b=0, 则
			// 10^c mod a = b = 0
			// 即10^c = a*s
			// a = 2^k*5^l
			// 但是步骤IsPrime2保证了a不含2或5的因子
			// 所以b不会等于0
			// 这里只是起个预防作用,为了提升速度,这种情况先注掉
			// 但是注释的话不应该去掉
			// chenbo add the explaination at 2005-10-09 20:13
			//=====================================
			//if( Compare(b, m_ZERO)==0 )
			//{
			//	fz(c, b);
			//}
			break;
		}

		for(i=b[0]+WK_DELT_STEP_CUR;i>WK_DELT_STEP_CUR;i--)
		{
			b[i] = b[i-WK_DELT_STEP_CUR];
		}
		for(i=1;i<=WK_DELT_STEP_CUR;i++)
		{
			b[i] = 0;
		}
		
		b[0]+=WK_DELT_STEP_CUR;
		Mod(b,a,b);

		//当b满足下列条件时说明已经计算得到了结果
		//b[b[0]]=1,b[1]=0,b[2]=0;b[3]=0;...b[b[0]-1]=0
		//并且b[0]>c
		bGetResult = TRUE;
		
		if(b[b[0]]==1)
		{
			for(i=1;i<b[0];i++)
			{
				if(b[i]!=0)
				{
					bGetResult = FALSE;
					break;
				}
			}
			if(nCC<=b[0])
			{
				bGetResult = FALSE;
			}
		}
		else
		{
			bGetResult = FALSE;
		}
		
		if(bGetResult)
		{//当b==1时说明已经得到结果，退出计算	
			BOOL bPrimeA = TRUE;
			nCC-=b[0];
			fz2(c, nCC);
			Mod(a, c, nRes);
			
			if(nRes[0]!=1||nRes[1]!=1)
			{//当a mod  c != 1时，说明a不是素数
				m_strError = _T("输入的数必须为素数!");
				return FALSE;
			}
			
			BigNum bnATmp, bnFactorTmp;
			fz(bnATmp.m_a, a);
			
			//确保得到的数是素数
			if( !IsPrimeGetFactor(&bnATmp, &bnFactorTmp) )
			{
				
				CString strP = _T("");
				strP.Format( _T("Delt( %s ) = %s     Fst factor = %s"),
					GetResultMy(a), 
					GetResultMy(c),
					GetResultMy(bnFactorTmp.m_a) );
				WkDebug::write(strP);
				
				
				m_strError = _T("输入的数必须为素数!");
				return FALSE;
			}
			
			
			
			fz2(nRes, nCC);
			return TRUE;
		}

		//由于前面有c>1e4就退出的判断,所以这个地方的判断可以去掉(一切为了速度)
		//我现在是成天地开机计算,一点速度的提升实际上就是在节省money
		//Chenbo add the explaination at 2005-10-09 21:01
		//if(Compare(c,a)>0)
		//{
		//	break;
		//}
	}

	fz2(nRes, nCC);
	return bReturn;
}





/*
    暂时要求所赋的值小于1000。
*/
BOOL BigNum::SetValue(int bTmp)
{
	Clear();
//	m_a[3] = bTmp/100;
//	m_a[2] = bTmp/10 - 10*m_a[3];
//	m_a[1] = bTmp%10;
//
//	for(int i=3;i>0;i--)
//	{
//		if(m_a[i]!=0)
//		{
//			m_a[0] = i;
//			break;
//		}
//	}


	int i = 0;

	while(bTmp>0)
	{
		i++;
		m_a[i] = bTmp%WK_DIGIT_BASE;
		bTmp/=WK_DIGIT_BASE;
	}

	if(i>0)
	{
		m_a[0] = i;
	}

	return TRUE;
}

BOOL BigNum::Clear()
{
	for(int i=0;i<MAX_DIGIT;i++)
	{
		m_a[i] = 0;
	}
	m_a[0] = 1;

	return TRUE;
}

/*
 *	need bSmall<10
 */
BOOL BigNum::AddSmallDigit(int bSmall)
{
	if(bSmall < 0 || bSmall > 10)
		return FALSE;

	m_a[1] += bSmall;

	ZZH2(m_a);
	return TRUE;

}

BOOL BigNum::ZZH2(int aTmp[])
{
	int iTmp;
	for(iTmp=1;iTmp<=aTmp[0];iTmp++)
	{
		if(aTmp[iTmp]>=WK_DIGIT_BASE)
		{
			aTmp[iTmp]-=WK_DIGIT_BASE;
			aTmp[iTmp+1]++;
		}
		else
			return TRUE;
	}

	if(aTmp[aTmp[0]+1]>0)
		aTmp[0]++;
	return TRUE;

}

BOOL MyMath::JSQSQRT()
{
	BigNum bgNumSqrt;
	BOOL bRet = FALSE;
	bRet = Sqrt(a, bgNumSqrt.m_a);
	fz(nRes, bgNumSqrt.m_a);
	return bRet;
}

BOOL BigNum::fz2(int aTmp[], int bTmp)
{//将int n转化为int n[MAX_DIGIT]的形式,先暂时只对nSource<100的情形成立
	int bTmp2 = bTmp;
	int nBit = 0;//每一位
	int nDigit = 0;
	ClearMy(aTmp);
	while(bTmp2>0)
	{
		nBit = bTmp2%WK_DIGIT_BASE;
		nDigit++;
		aTmp[nDigit] = nBit;
		bTmp2 = bTmp2/WK_DIGIT_BASE;
	}
	if(nDigit>1)
	{
		aTmp[0] = nDigit;
	}
	return TRUE;
}

BOOL BigNum::ClearMy(int aTmp[])
{
	memset(aTmp, 0, sizeof(int)*MAX_DIGIT);
	//for(int i=0;i<MAX_DIGIT;i++)
	//{
	//	aTmp[i] = 0;
	//}
	aTmp[0] = 1;
	return TRUE;
}

BOOL BigNum::ClearMy0(int aTmp[])
{
	memset(aTmp, 0, sizeof(int)*MAX_DIGIT);
	return TRUE;
}


///code for BigNum is end
/////////////////////



////////////////////////////////////////////////
//here is for class MyMath

BOOL MyMath::PreMult()
{
	BOOL bReturn = FALSE;
	int nDigitMax = a[0] + b[0];
	if(nDigitMax<MAX_DIGIT) 
	{
		bReturn = TRUE;
	} 
	else if(nDigitMax==MAX_DIGIT) 
	{	
		m_strError = _T("计算结果可能会超过数的表示范围, 请重新输入!");	
	}
	else
	{
		m_strError = _T("计算结果超过了数的表示范围, 请重新输入!");	
	}
	return bReturn;
}

BOOL MyMath::JSQMULT()
{
	BigNum bgNumSqrt;
	BOOL bRet = FALSE;
	bRet = Mult(a, b, bgNumSqrt.m_a);
	fz(nRes, bgNumSqrt.m_a);
	return TRUE;
}

BOOL MyMath::Mult(const int aTmp[], const int bTmp[], int cTmp[])
{
	BigNum bgRes;
	BigNum bgTmp;
	BigNum bgTTmp;

	//bgTmp.m_a[0] = aTmp[0];

	for(int ib=1;ib<=bTmp[0];ib++)
	{
		bgTmp.Clear();
		for(int ia=1;ia<=aTmp[0];ia++)
		{
			bgTmp.m_a[ia] = aTmp[ia]*bTmp[ib];
		}

		bgTmp.m_a[0] = aTmp[0];
		ZZH2B(bgTmp.m_a);

		fz(bgTTmp.m_a, bgTmp.m_a);
		for(int ibB=1;ibB<ib;ibB++)
		{
			Mult10(bgTTmp.m_a, bgTTmp.m_a);
		}
		Add(bgRes.m_a, bgTTmp.m_a, bgRes.m_a);
	}

	fz(cTmp, bgRes.m_a);

	return TRUE;
}

/*
 *	dst = src * WK_DIGIT_BASE
 *  添加日期: 2005-01-21 21:58
 */
BOOL MyMath::Mult10(int srcTmp[], int dstTmp[])
{
	// // bgI的存在是为了防止srcTmp和dstTmp为同一个变量。
	// 当srcTmp和dstTmp为同一变量时此代码仍然成立。
	//(2008-02-04 15:46)
	if(Compare(srcTmp, m_ZERO)==0)
	{
		fz(dstTmp, m_ZERO);
		return TRUE;
	}
	
	//BigNum bgI;
	int i = 0;
	//fz(bgI.m_a, srcTmp);

	for(i=srcTmp[0]+1;i>1;i--)
	{
		dstTmp[i] = srcTmp[i-1];
	}
	
	dstTmp[1] = 0;
	
	
	dstTmp[0] = srcTmp[0] + 1;

	return TRUE;
}

/*
 *	这里要求aTmp和bTmp是标准的自然数。
 最后更新时间： 2006-02-27 19:28
 */
BOOL MyMath::Add(const int aTmp[], const int bTmp[], int cTmp[])
{
	int i = 1;
	int nEtd = 0;//extend 是否有进位

	cTmp[0] = (aTmp[0]>bTmp[0]?aTmp[0]:bTmp[0]);

	for(;i<=cTmp[0];i++)
	{
		cTmp[i] = aTmp[i] + bTmp[i] + nEtd;
		if(cTmp[i]>=WK_DIGIT_BASE)
		{
			cTmp[i]-=WK_DIGIT_BASE;
			nEtd = 1;
		}
		else
		{
			nEtd = 0;
		}
	}

	if(nEtd==1)
	{
		cTmp[i] = 1;
		cTmp[0]++;
	}
	

	return TRUE;
}

/*
 *	此函数是专门提供给JSGDlg调用
 */
BOOL MyMath::JSQSQR()
{
	Clear(nReserved);
	Mult(a, a, nReserved);
	fz(nRes, nReserved);
	
	//将nReserved清零
	Clear(nReserved);
	return TRUE;
}

BOOL MyMath::JSQPOWER()
{
	BigNum bgATmp;
	BigNum bgBTmp;
	BigNum bgPower;

	fz(bgATmp.m_a, a);
	fz(bgBTmp.m_a, b);

	
	if(b[0]>3)
	{
		m_strError = _T("指数过多，不得超过999999！");
		return FALSE;
	}

	double dbnRes = b[1] 
		+ b[2]*WK_DIGIT_BASE
		+ b[3]*WK_DIGIT_BASE*WK_DIGIT_BASE;
	double dDigit;
	if(a[0]>3)
	{
		dDigit = (a[0])*dbnRes;
	}
	else
	{
		double dbNTmp = a[1]
			+a[2]*WK_DIGIT_BASE
			+a[3]*WK_DIGIT_BASE*WK_DIGIT_BASE;
		dDigit = dbnRes * log10(dbNTmp);
	}

	if( dDigit > ( MAX_DIGIT * WK_DIGIT_BASE_WIDTH ) )
	{
		m_strError.Format(_T("The number is too large! dDigit = %f, 结果不得超过 %d 位！"), dDigit,
			MAX_DIGIT * WK_DIGIT_BASE_WIDTH);
		return FALSE;
	}

  
	Power(&bgATmp, &bgBTmp, &bgPower);

	fz(nRes, bgPower.m_a);

	return TRUE;

}

BOOL MyMath::GetBigNum(int nDigitAt, int nNumD, int bnRes[MAX_DIGIT])
{
	BigNum bnTemp;
	bnTemp.m_a[1] = 1;
	switch(nNumD) 
	{
	case 0:
		fz(bnRes, bnTemp.m_a);
		return TRUE;
	case 1:
		fz(bnRes, m_BNDeltRes[4*(nDigitAt-1)].m_a);
		return TRUE;
	case 2:
		fz(bnRes, m_BNDeltRes[4*(nDigitAt-1)+1].m_a);
		return TRUE;
	case 3:
		fz(bnRes, m_BNDeltRes[4*(nDigitAt-1)+2].m_a);
		return TRUE;
	case 4:
		Mult(m_BNDeltRes[4*(nDigitAt-1)+1].m_a,m_BNDeltRes[4*(nDigitAt-1)+1].m_a,
			bnTemp.m_a);
		fz(bnRes, bnTemp.m_a);
		return TRUE;
	case 5:
		fz(bnRes, m_BNDeltRes[4*(nDigitAt-1)+3].m_a);
		return TRUE;
	case 6:
		Mult(m_BNDeltRes[4*(nDigitAt-1)].m_a,m_BNDeltRes[4*(nDigitAt-1)+3].m_a,
			bnTemp.m_a);
		fz(bnRes, bnTemp.m_a);
		return TRUE;
	case 7:
		Mult(m_BNDeltRes[4*(nDigitAt-1)+1].m_a,m_BNDeltRes[4*(nDigitAt-1)+3].m_a,
			bnTemp.m_a);
		fz(bnRes, bnTemp.m_a);
		return TRUE;
	case 8:
		Mult(m_BNDeltRes[4*(nDigitAt-1)+2].m_a,m_BNDeltRes[4*(nDigitAt-1)+3].m_a,
			bnTemp.m_a);
		
		fz(bnRes, bnTemp.m_a);
		return TRUE;
	case 9:
		Mult(m_BNDeltRes[4*(nDigitAt-1)+1].m_a,m_BNDeltRes[4*(nDigitAt-1)+1].m_a,
			bnTemp.m_a);
		Mult(bnTemp.m_a,m_BNDeltRes[4*(nDigitAt-1)+3].m_a,
			bnTemp.m_a);
		fz(bnRes, bnTemp.m_a);
		return TRUE;
	default:
		break;
	}
	return FALSE;
}

/*
 *	功能说明: a^b=res, a和b为输入，res为输出
 *            首先将bTmp转化为二进制，然后再分别对之进行平方，
 *            加一的操作。
 *            2^18
 *            18=2^4+2=10010
 *            0010= D D DA D
 *            1 -> (2) -> (4) -> (8 -> 9) -> (18)
 *
 *  添加时间: 2008-02-06 12:57
 */
BOOL MyMath::Power(BigNum *aTmp, BigNum *bTmp, BigNum *resTmp)
{
	//先将bTmp化为二进制形式的字符串
	BigNum cTmp;
	BigNum dTmp;
	BigNum eTmp;//存储结果(暂时性的)
	BigNum bnTWO;
	CString strBinary = _T("");
	int nLenBinary = 0;
	int i = 0;
	char ch = 0;

	bnTWO.SetValue(2);
	fz(cTmp.m_a, bTmp->m_a);
	while(Compare(cTmp.m_a, m_ZERO)>0)
	{
		Div(cTmp.m_a, bnTWO.m_a, cTmp.m_a, dTmp.m_a);
		if(Compare(dTmp.m_a, m_ONE)==0)
		{
			strBinary = _T("1") + strBinary;
		}
		else 
		{
			strBinary = _T("0") + strBinary;
		}
	}

	nLenBinary = strBinary.GetLength() - 1;
	strBinary = strBinary.Right(nLenBinary);
	fz(eTmp.m_a, aTmp->m_a);
	for(i=0;i<nLenBinary;i++)
	{
		ch = strBinary.GetAt(i);
		if(ch=='0')
		{//e=e^2
			Mult(eTmp.m_a, eTmp.m_a, eTmp.m_a); 
		}
		else //if(ch=='1')
		{//e=e^2*a
			Mult(eTmp.m_a, eTmp.m_a, eTmp.m_a); 
			Mult(eTmp.m_a, aTmp->m_a, eTmp.m_a);
		}
	}
	fz(resTmp->m_a, eTmp.m_a);

	return TRUE;
}

BOOL MyMath::PowerMod(BigNum *aTmp, BigNum *bTmp2, BigNum *resTmp)
{
	BigNum bgI;
	BigNum bgNumResPowerTmp;

	BigNum *bTmp = new BigNum();
	fz(bTmp->m_a, bTmp2->m_a);
	bTmp->m_a[1]--;
	ZZH(bTmp->m_a);

	bgI.m_a[1] = 1;
	bgNumResPowerTmp.m_a[1] = 1;

	for(int iI=0;iI<(MAX_DIGIT_P*4);iI++)
	{
		Clear(m_BNDeltRes[iI].m_a);
	}

	fz(m_BNDeltRes[0].m_a, aTmp->m_a);
	Mod(m_BNDeltRes[0].m_a, bTmp2->m_a,
		m_BNDeltRes[0].m_a);//1 mod p

	/*	0		1		2		3

0		1,		2,		3,		5,
1		10,		20,		30,		50,
2		100,	200,	300,	500,
3		1000,	2000,	3000,	5000

	*/
	for(int i=0;i<bTmp->m_a[0];i++)
	{	
		if( i==(bTmp->m_a[0]-1) && bTmp->m_a[bTmp->m_a[0]]<2)
			break;
		Mult(m_BNDeltRes[i*4].m_a, m_BNDeltRes[i*4].m_a,
			m_BNDeltRes[i*4+1].m_a);//1+1=2
		Mod(m_BNDeltRes[i*4+1].m_a, bTmp2->m_a,
			m_BNDeltRes[i*4+1].m_a);//2 mod p

		if( i==(bTmp->m_a[0]-1) && bTmp->m_a[bTmp->m_a[0]]<3)
			break;
		Mult(m_BNDeltRes[i*4].m_a, m_BNDeltRes[i*4+1].m_a,
			m_BNDeltRes[i*4+2].m_a);//1+2=3
		Mod(m_BNDeltRes[i*4+2].m_a, bTmp2->m_a,
			m_BNDeltRes[i*4+2].m_a);//3 mod p

		if( i==(bTmp->m_a[0]-1) && bTmp->m_a[bTmp->m_a[0]]<5)
			break;
		Mult(m_BNDeltRes[i*4+1].m_a, m_BNDeltRes[i*4+2].m_a,
			m_BNDeltRes[i*4+3].m_a);//2+3=5
		Mod(m_BNDeltRes[i*4+3].m_a, bTmp2->m_a,
			m_BNDeltRes[i*4+3].m_a);//5 mod p
		

		if(i<(bTmp->m_a[0]-1))
		{
			Mult(m_BNDeltRes[i*4+3].m_a, m_BNDeltRes[i*4+3].m_a,
				m_BNDeltRes[i*4+4].m_a);
			Mod(m_BNDeltRes[i*4+4].m_a, bTmp2->m_a,
				m_BNDeltRes[i*4+4].m_a);//10 mod p
		}
		
	}

	BigNum bnTmpDig;
	GetBigNum(1, bTmp->m_a[1], bnTmpDig.m_a);
	fz(bgNumResPowerTmp.m_a, bnTmpDig.m_a);
	
	for(int iB=2;iB<=bTmp->m_a[0];iB++)
	{
		GetBigNum(iB, bTmp->m_a[iB], bnTmpDig.m_a);
		Mult( bnTmpDig.m_a, bgNumResPowerTmp.m_a, 
			bgNumResPowerTmp.m_a);
		Mod( bgNumResPowerTmp.m_a, bTmp2->m_a, 
			bgNumResPowerTmp.m_a);
	}

//	Mod( bgNumResPowerTmp.m_a, bTmp2->m_a, 
//		bgNumResPowerTmp.m_a);
	fz(resTmp->m_a, bgNumResPowerTmp.m_a);

	delete bTmp;
	return TRUE;
}

BOOL MyMath::JSQDIV()
{
	BOOL bJsqDivTmp = FALSE;
	bJsqDivTmp = Div(a, b, c, d);
	return bJsqDivTmp;
}

/*
 *	函数功能说明：dTmp 不停地减 bTmp，最后减得的结果仍存放到dTmp中, 
 减的次数加到cTmp中，此函数暂时专为Div(a, b, c, d)设计
 编写日期：2005-01-23 00:37
 */
BOOL MyMath::MinusEq(int dTmp[], int bTmp[], int cTmp[])
{	

	return TRUE;

	//此函数暂未实现
	int i = dTmp[0];
	for(;i>0;i--)
	{
		if(dTmp[i]>bTmp[i])
		{//说明d>b
			Minus(dTmp, bTmp, dTmp);
			//fz(nRes, dTmp);
			return TRUE;
		}
		if(dTmp[i]<bTmp[i])
		{//说明a<b
			fz(nRes, dTmp);
			return TRUE;
		}
	}
	Clear(dTmp);
	cTmp[1]++;
	ZZH(cTmp);
	Clear(dTmp);
	return TRUE;

}

BOOL MyMath::IsZero(int aTmp[])
{
	if(aTmp[0]==1 && aTmp[1]==0)
		return TRUE;
	
	return FALSE;
}

//saved at 2008-02-01 22:07
int MyMath::Delt15(__int64 n64Tmp)
{
	int nReturn = WK_DELT_STEP_CUR;
	__int64 n64Mult = 1;
	__int64 nStepNum = (__int64)pow(10.0, WK_DELT_STEP_CUR);
	int nCurStep = 0;

	int b2_TMP[MAX_DIGIT];
	
	//先计算10^5000 mod n的值
	//将计算得到的余数存放到b中
	Clear(b);
	b[1] = 1;//let b = 1;
	Mult(b, m_TEN, b);//nCurStep=1
	Mult(b, b, b);//nCurStep=2
	Mult(b, b, b);//nCurStep=4
	Mod(b,a,b);
	Mult(b, b, b);//nCurStep=8
	Mod(b,a,b);
	Mult(b, m_TEN, b);//nCurStep=9
	Mod(b,a,b);
	Mult(b, b, b);//nCurStep=18
	Mod(b,a,b);
	Mult(b, m_TEN, b);//nCurStep=19
	Mod(b,a,b);
	Mult(b, b, b);//nCurStep=38
	Mod(b,a,b);
	Mult(b, m_TEN, b);//nCurStep=39
	Mod(b,a,b);
	Mult(b, b, b);//nCurStep=78
	Mod(b,a,b);
	Mult(b, b, b);//nCurStep=156
	Mod(b,a,b);
	Mult(b, b, b);//nCurStep=312
	Mod(b,a,b);
	Mult(b, b, b);//nCurStep=624
	Mod(b,a,b);
	Mult(b, m_TEN, b);//nCurStep=625
	Mod(b,a,b);
	Mult(b, b, b);//nCurStep=1250
	Mod(b,a,b);
	Mult(b, b, b);//nCurStep=2500
	Mod(b,a,b);
	Mult(b, b, b);//nCurStep=5000
	Mod(b,a,b);
	Mult(b, b, b);//nCurStep=10000
	Mod(b,a,b);
	fz(b2_TMP, b);
	Mult(b, b, b);//nCurStep=20000
	Mod(b,a,b);
	Mult(b, b, b);//nCurStep=40000
	Mod(b,a,b);
	Mult(b, b2_TMP, b);//nCurStep=50000
	Mod(b,a,b);

	nCurStep = 50000;
	
	IntAryToInt64(b, &n64Mult);
	
	if(n64Mult==1)
	{
		return Delt15Genuine(n64Tmp);
	}
	
	while(TRUE)
	{
		n64Mult*=nStepNum;
		n64Mult%=n64Tmp;
		
		//如果得到的结果表明10^i mod n = 1, 则重新计算一次。
		if(n64Mult==1 || 
			(GetRepLogNum(n64Mult, &nCurStep)>=0 && nReturn>nCurStep)
			)
		{
			return Delt15Genuine(n64Tmp);
		}//if(n64Mult==1 || 
		nReturn+=WK_DELT_STEP_CUR;
		
		if(nReturn>WK_DIGIT_DELT1E5)
		{
			break;
		}
		
	}//while(TRUE)
	return nReturn;
}




/*
 *	功能说明：对于小于10^15的数计算其DELT值。
 *            当输入的数n64Tmp>10^15时，此函数返回的值可能不对。
 *            所以应该注意此函数的适用范围。
 *            这里每一步计算WK_DELT_STEP_CUR步，可以略微提升计算的速度。
 *            
 *  添加日期：2008-01-31 19:54
 */
int MyMath::Delt15Genuine(__int64 n64Tmp)
{
	int nReturn = WK_DELT_STEP_CUR;
	__int64 n64Mult = 1;
	__int64 nStepNum = (__int64)pow(10.0, WK_DELT_STEP_CUR);
	int nCurStep = 0;


	while(TRUE)
	{
		n64Mult*=nStepNum;
		n64Mult%=n64Tmp;
		if(n64Mult==1 || 
			(GetRepLogNum(n64Mult, &nCurStep)>=0 && nReturn>nCurStep)
			)
		{
			BigNum bgN, bnFactorTmp;
			//Int64ToIntAry(n64Tmp, bgN.m_a);
			fz(bgN.m_a, a);

			if(nCurStep>=0)
			{
				nReturn-=nCurStep;
			}
			
			//确保得到的数是素数
			if( !IsPrimeGetFactor(&bgN, &bnFactorTmp) )
			{
				
				CString strP = _T("");
				strP.Format( _T("Delt( %s ) = %d     Fst factor = %s"),
					GetResultMy(bgN.m_a), nReturn,
					GetResultMy(bnFactorTmp.m_a) );
				WkDebug::write(strP);
				
				//为了提高运行速度，不必要的调试信息去掉
				//只以注释的方式进行提示
				//m_strError = _T("输入的数必须为素数!");
				return 0;
			}//if( !IsPrimeGetFactor(&bgN, &bnFactorTmp) )


			//显示得到的值
			break;
		}//if(n64Mult==1 || 
		nReturn+=WK_DELT_STEP_CUR;

		if(nReturn>WK_DIGIT_DELT1E5)
		{
			break;
		}

	}//while(TRUE)
  	return nReturn;
}




/*
    功能说明: 鉴于速度的考虑，这里要求nIn不大于10000。
              也就是WK_DELT_STEP_CUR不大于5.
			  当输入的数不是10的整数幂时，返回-1.
			  nIn是10时，返回1;100->2;1000->3;10000->4
	添加日期: 2008-02-01 20:33
*/
int MyMath::GetRepLogNum(__int64 nIn, int *pOut)
{
	
	int i = -1;

	if(nIn==10)
	{
		i = 1;
	}
	else if(nIn==100)
	{
		i = 2;
	}
	else if(nIn==1000)
	{
		i = 3;
	}
	else if(nIn==10000)
	{
		i = 4;
	}
	else if(nIn==10000)
	{
		i = 4;
	}
	else if(nIn==100000)
	{
		i = 5;
	}
	else if(nIn==1000000)
	{
		i = 6;
	}

	*pOut = i;
	return i;
}


BOOL MyMath::IsPrime64(__int64 n64Tmp)
{
	//先将n装还为nTmp[MAX_DIGIT]
	BigNum bgN;
	Int64ToIntAry(n64Tmp, bgN.m_a);

	return IsPrime(bgN.m_a);
}

void MyMath::Int64ToIntAry(__int64 n64Tmp, int bTmp[])
{
	__int64 n64Tmp1 = n64Tmp;
	int i = 0;
	while(n64Tmp1>0)
	{
		i++;
		bTmp[i] = (int)(n64Tmp1%10);
		n64Tmp1/=10;
	}
	bTmp[0] = i;
}


void MyMath::IntAryToInt64(int nTmp[], __int64 *p64Tmp)
{
	__int64 n64Num = 0;
    int i = nTmp[0];
	while(i>=1)
	{
		n64Num *= WK_DIGIT_BASE;
		n64Num += nTmp[i];
		i--;
	}
	*p64Tmp = n64Num;
}

BOOL MyMath::IsPrime64_2(__int64 n64Tmp)
{
	int i = 1;
	for(;i<4900;i++)
	{
		if(n64Tmp%m_nPrime25[i]==0)
		{
			if(n64Tmp==m_nPrime25[i])
			{
				return TRUE;
			}

			return FALSE;
		}
	}
	return TRUE;
}





/*
 *	功能说明: 返回位数，当n为0时返回0
 *
 *  添加日期: 2008-02-03 12:01
 */
int MyMath::GetDigit(int nTmp[])
{
    int nReturn = 0;
    
	if(!IsZero(nTmp))
	{
		CString strDigitHigh = _T("");
		
		nReturn = (nTmp[0]-1) * WK_DIGIT_BASE_WIDTH;

		strDigitHigh.Format(_T("%d"), nTmp[nTmp[0]]);
		nReturn += strDigitHigh.GetLength();
	}

	return nReturn;
	
}

/*
 *	此处需预先保证 0 < nPos < MAX_DIGIT
 *  专为 aTmp[i] += 1 设计.
 *  此处需保证 aTmp>0
 */
BOOL MyMath::ZZH2D(int aTmp[], int nPos)
{
	int i = 0;

	if(aTmp[0]<nPos)
	{
		aTmp[0] = nPos;
	}
	
	for(i=nPos;i<=aTmp[0];i++)
	{
		if(aTmp[i]>=WK_DIGIT_BASE)
		{
			aTmp[i]-=WK_DIGIT_BASE;
			aTmp[i+1]++;

			if(i==aTmp[0])
			{ //表示aTmp的位数增加了. 
				aTmp[0]++;
				return TRUE;
			}
		}
	}
		
	return TRUE;
}





















