// MyMath.h: interface for the MyMath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYMATH_H__BE90C74F_9902_419F_AA7E_0EDCAE848729__INCLUDED_)
#define AFX_MYMATH_H__BE90C74F_9902_419F_AA7E_0EDCAE848729__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "math.h"

/*
    说明: 当计算Power时，MAX_DIGIT设为2000比较合适，
	      此时计算10^233、2^739等都可以满足要求
  
	//reserved 20 (2005-01-29 15:06) 应为寻找的是小于10^10的p,
	//所以20位应该够了

	//reserved 30 (2005-04-09 09:25) 由于p现在已经增至500e5
	//所以为了保险，取30位

	//如果是为了计算m^n, 建议MAX_DIGIT取值为1000, 
	//当MAX_DIGIT大于10000时,会出现栈溢出的错误.
	//ChenBo 2005-10-07 17:22 add the explaination
	
	//reserved 50 (2005-10-31 19:24)
	//说明：此值不应经常变动
	//而且现在几乎所有小于40位的数已经发现了。。。。。


	//出于种种原因，现在MAX_DIGIT暂定为50，如没有特殊目的
	//不应更改此值。
	//updated: 2008-01-31 19:52

    //现在由于WK_DIGIT_BASE的引入，相应4地此值应改为20

	//打算计算的范围为0到200位，所以这个地方暂时固定为200.
	//没有特殊原因这个值暂时不改。
	//updated:2009-08-14

	// ***
	// reserved 20 (2010-10-11 10:12)
	// 说明：此值不应经常变动(此程序的主要目的是计算Delt(p)).
*/
#define MAX_DIGIT 100

//计算Delt时每次迭代的步数
//注意此值不要大于5（2008-02-01 20:36添加）
#define WK_DELT_STEP_CUR 7

//reserved 40 (2005-11-01 07:34) should not change without suitable reason
#define MAX_DIGIT_P 8//希望寻找的p的最大位数

struct BigNum
{
public:
	//主变量
	int m_a[MAX_DIGIT];

	/**
        构造方法
	*/
	BigNum()
	{
		memset(m_a, 0, sizeof(m_a));
		m_a[0] = 1;
	}
public:
	/*
	 *	let a = 0;
        添加日期: 2006-02-22 23:11
	 */
	BOOL ClearMy(int aTmp[MAX_DIGIT]);

	/*
        将int n转化为int n[MAX_DIGIT]的形式,先暂时只对nSource<100的情形成立
        here bTmp is source and aTmp for memory
        添加日期:2006-02-22 23:07
	*/
	BOOL fz2(int aTmp[MAX_DIGIT], int bTmp);

	/*
		要求aTmp除了最后一位可能超过9外，别的都在0～9。特为b++准备
		also for b+=2;
		添加日期: 2005-01-19 19:37
	 */
	BOOL ZZH2(int aTmp[MAX_DIGIT]);

	BOOL AddSmallDigit(int bSmall);

	/*
	 *	将m_a设置为0。
	 *  添加日期: 2007-02-05 09:01
	 */
	BOOL Clear(void);

	/*
	 *	给m_a赋初值，输入的是一个整形的数。
	 *  添加日期: 2007-02-05 08:32
	 */
	BOOL SetValue(int bTmp);

private:
	/*
	 *	let all of a's content is zero!
	 this method is for private, use carefully!
	 add time:2006-02-22 23:13
	 */
	BOOL ClearMy0(int aTmp[MAX_DIGIT]);
};

extern BigNum m_BigNumPrime25[25];//存储小于100的25个素数(as type of BigNum)

//扩充了100~200之间的21个素数(2006-03-15)
extern int m_nPrime25[78498];//存储小于10^6的78498个素数(as type of int)
extern BigNum m_BNDeltRes[MAX_DIGIT_P*4];//备用的数
extern BOOL bBigNumPrimeHasInit;//m_BNDeltRes是否已经初始化
/*
	相关说明: a[0]存放位数
	当a[0]=0时，说明这个数为0(还未对其赋值的情形)，如果此时别的a[i]!=0则说明存在错误
	a[1]=1,别的位均为0时说明这个数为零
	要求计算时不允许出现a[0]<=0的情形
*/
class MyMath  
{
public:
	int bDiff;//每次b增加的数目
	int a[MAX_DIGIT];
	int b[MAX_DIGIT];
	int c[MAX_DIGIT];
	int d[MAX_DIGIT];
	int e[MAX_DIGIT];
	int nRes[MAX_DIGIT];//存放结果
	int nReserved[MAX_DIGIT];//存放的缓存(要求使用时赋初值，使用完之后清零)
	int aAddb[MAX_DIGIT];
	
	int nCircle[MAX_DIGIT];
	int aSqrt[MAX_DIGIT];
	CString strR;

	//计算过程中得到的错误信息，此变量一般提供给UI调用。
	CString m_strError;



	//一些常数
	int m_ZERO[MAX_DIGIT];//0
	int m_ONE[MAX_DIGIT];//1
	int m_TEN[MAX_DIGIT];//10
	
public://以下这些函数是提供给Dlg界面的

	/*
	 *	功能说明: 加法
	 *  添加日期: 2008-02-03 11:56
	 */
	BOOL JSQADD();

	/*
	 *  功能说明: 用于计算器显示的减法运算，
	 *            得到的结果存放到c中
	 *
	 *  添加日期: 2004-11-29 20:25
	 */
	BOOL JSQMINUS();

	/*
	 *	计算器乘法
	 *
	 *  添加日期: 2005-02-06 10:22
	 */
	BOOL JSQMULT();

	/*
		功能说明: 除法，
		添加日期: 2005-02-06 10:19
	*/
	BOOL JSQDIV();

	/*
		用于计算器乘幂，a、b为输入
		添加日期: 2005-01-22 11:52
	*/
	BOOL JSQPOWER();

	/*
		平方。
		a为输入，得到的结果存放到nRes中。

		添加日期: 2005-01-22 10:20
	*/
	BOOL JSQSQR();

	/*
	 *  功能说明: 计算乘法之前判断位数是否正确 
     *            即需要a[0]+b[0]<MAX_DIGIT
	 *
	 *  添加日期: 2005-10-13 19:21
	 */
	BOOL PreMult();



	BOOL JSQSQRT();


	/*
		计算Delt(10, p)
		添加日期: 2004-12-11 21:27
	*/
	BOOL JSQDELT();


public://以下为工具函数，一般不被外部调用(否则可能会出问题)
	/*
	 *  功能说明: ZZH2A的加强，要求从aTmp[1] ~aTmp[nPos]所有的数
	 *            在区间[0,(WK_DIGIT_BASE-1)*2]
	 *            之间,
	 *            aTmp[nPos+1]到aTmp[MAX_DIGIT]为0。
	 *            aTmp[0]>0 (不能等于0)
	 *            此函数专为aTmp[i]++设计.
	 *            (其中i为一介于1到MAX_DIGIT-1之间的数)
	 *
	 *  添加日期: 2008-02-04 20:14
	 */
	BOOL ZZH2D(int aTmp[MAX_DIGIT], int nPos);
	/*
	 *	功能说明: 获取一个整型数的位数，
	 *            要求输入的数是标准型。
	 *            当n为0时返回0.
	 *
	 *  添加日期: 2008-02-03 11:58
	 */
	int GetDigit(int nTmp[MAX_DIGIT]);

	BOOL IsPrime64_2(__int64 n64Tmp);

	/**
	 *  功能说明: 将数组型数nTmp的值赋给64位的数p64Tmp
	 *            输入的时候p64Tmp应传入指针。
	 *  添加日期: 2008-02-01 21:52
	 */
	void IntAryToInt64(int nTmp[MAX_DIGIT], __int64 *p64Tmp);
	void Int64ToIntAry(__int64 n64Tmp, int bTmp[MAX_DIGIT]);
	BOOL IsPrime64(__int64 n64Tmp);
	
	/*
	 *	功能说明：计算Delt(n)
	 *            如果大于1e4则返回10000，否则返回Delt的值，
	 *            这里面如果发现n是合数则返回0
	 *            这里要求输入的n64Tmp必须小于(2^64/10^WK_DELT_STEP_CUR)
	 *
	 *            和Delt15Genuine()方法不同之处在于此方法是先判断
	 *            Delt(n64Tmp)是否小于10000，即先计算10^5000 mod n, 然后计算所有从
	 *            5000到9999的i值，判断10^i mod n是否为1，如果得到了这样的i, 说明
	 *            Delt(n)小于10000，再重新从1到9999的i值计算一次得到Delt(n)的准确值，
	 *            如果没有得到从5000到9999的i值，说明Delt(n)>10000, 此时的n可直接返回。
	 *            此方法的原理在于当Delt(n)<5000时，至少存在一个5000到9998之间
	 *            的值i使得 10^i mod n = 1.(此方法由于Mult和Mod效率较低暂未实施，
	 *            代码可见F:\my\cpp\cacu\JSQ\backup\Delt15.txt文件.)
	 *
	 *
	 *            此方法引进的日期: 2008-02-01 21:02
	 *  添加日期: 2007-02-12 08:46
	 */
	int Delt15(__int64 n64Tmp);

	int Delt15Genuine(__int64 n64Tmp);
	

	/*
		功能说明:判断aTmp是否为零
		         当a等于0时返回TRUE, 否则返回FALSE.
		添加日期: 2005-02-06 09:57
	*/
	BOOL IsZero(int aTmp[MAX_DIGIT]);

	BOOL MinusEq(int dTmp[MAX_DIGIT], int bTmp[MAX_DIGIT], int cTmp[MAX_DIGIT]);

	/*
		用于计算乘幂，a、b为输入，res为输出
		添加日期: 2005-01-22 11:51
	 */
	BOOL Power(BigNum *aTmp, BigNum *bTmp, BigNum *resTmp);


	/*
		计算aTmp^(bTmp-1) mod bTmp 
		结果存放到resTmp中
		添加日期: 2005-01-29 16:01
	*/
	BOOL PowerMod(BigNum *aTmp, BigNum *bTmp2, BigNum *resTmp);


	/*
	 *	加法, aTmp+bTmp=cTmp
	 添加日期: 2005-02-06 10:21
	 修改日期：2009-08-14 08：23    将a和b改为const类型的。
	 */
	BOOL Add(const int aTmp[MAX_DIGIT], const int bTmp[MAX_DIGIT], int cTmp[MAX_DIGIT]);

	BOOL Mult(const int aTmp[MAX_DIGIT], const int bTmp[MAX_DIGIT], int cTmp[MAX_DIGIT]);

	


	/*
 		将int aTmp[MAX_DIGIT]转化为int型的
		返回结果为int
		添加日期: 2004-11-28 13:26
	*/
	int IntMDToInt(int aTmp[MAX_DIGIT]);
	

	/*
		10^a = b
		要求:0<a<10000
		添加日期: 2004-11-28 13:22
	*/
	BOOL JSQREP10();


	/*
		用于计算器显示的mod运算
		添加日期: 2004-11-29 20:26
	*/
	BOOL JSQMOD();

	BOOL JSQGCD();

	void gcd(const int aTmp[MAX_DIGIT], const int bTmp[MAX_DIGIT], int cTmp[MAX_DIGIT]);

	/**
		2009-07-05 07:02
		d*a-e*b=c
	*/
	void gcd(const int aTmp[MAX_DIGIT], const int bTmp[MAX_DIGIT], int cTmp[MAX_DIGIT],
		int dTmp[MAX_DIGIT],int eTmp[MAX_DIGIT]);


	BOOL MinusEq2(int aTmp[MAX_DIGIT], int bTmp[MAX_DIGIT], int cTmp[MAX_DIGIT]);

	
	/*
		a[]是否能被b整除，如果可以的话返回TRUE,否则返回FALSE
		这里要求0<b<100
		添加日期: 2004-11-27 15:43
	*/
	BOOL IsMod2a(int aTmp[], int bTmp);
	

	BOOL IsMod2(int aTmp[MAX_DIGIT], int bTmp[MAX_DIGIT]);


	/*
	近似计算a/b的值的最高位,得到的结果只应该为
	不妨设 x=[a/b]
	则返回的值为x或x-1
	例如a=72, b=24, 则返回3
	a=7200000000000001, b=2400000, 则返回2
	思想是a<b时返回1
	当a>=b时, 设aD=a[0], bD=b[0];
	    1. b[0]<=3
		    11. a[0]<=3, 返回[a/b]
			12. a[0]>3, 返回[(a[aD]*100+a[aD-1]*10+a[aD-2])/b]
		2. b[0]>3
		    返回[(a[aD]*100+a[aD-1]*10+a[aD-2])/(b[bD]*100+b[bD-1]*10+b[bD-2]+1)]
	 添加日期: 2005-10-13 20:05
	 */
	int SigDIV(int aTmp[MAX_DIGIT], int bTmp[MAX_DIGIT]);


	/*
	 *	近似计算a/b的值的最高位
	 使用本函数应该保证a>b
	 此寒食暂时作废
	 以后如要用时载满满写
	 发现判断
	     124......./124....
	 形式的计算时存在困难
	 如124000/1240 = 1
	 124000/1241 = 9
	 两个并非简单的相隔1的关系
	 添加日期: 2005-10-13 20:06
	 */
	int SigDIV2(int aTmp[MAX_DIGIT], int bTmp[MAX_DIGIT]);


	/*
	要求a[0]>=2
	a>b
	 return	aFTN3/bFTN2
	 添加日期: 2005-10-13 20:18
	 */
	int SigDIV2_32(int aTmp[MAX_DIGIT], int bTmp[MAX_DIGIT]);

	/*
	要求a[0]>=1
	a>b
	 return	aFTN3/bFTN3
	 添加日期: 2005-10-13 20:19
	 */
	int SigDIV2_33(int aTmp[MAX_DIGIT], int bTmp[MAX_DIGIT]);


	/*
	 b<1000时计算a mod b
	 使用此函数前必须保证b<1000, 否则运算得到的结果可能不对
	 结果存到c中, 
	 this method is for test prime to a to lower than 100's factor
	 
	 添加日期: 2005-10-14 19:22
	 */
	BOOL Mod_b1000(int aTmp[MAX_DIGIT],int bTmp[MAX_DIGIT],int cTmp[MAX_DIGIT]);

	/*
	    功能说明：	  //a mod b = c,
	                  //(a,b为输入,c为输出,得到的商不予处理)
	                  这里的aTmp和cTmp可能是同一个输入的变量。
		添加日期: 2008-02-01 21:11
	*/
	BOOL Mod(int aTmp[MAX_DIGIT],int bTmp[MAX_DIGIT],int cTmp[MAX_DIGIT]);

	
	/*
		功能说明: 当且仅当bTmp是素数时返回TRUE.


		      注释1：此函数为保留函数，只能用于一般判别用途，需要考虑所有合法的情况。
			         例如bTmp=2则返回TRUE，bTmp=214281757则返回FALSE。
					 而且输入必须合法，意指bTmp[0]需要是输入数的位数，bTmp必须大于或等于2
					 对于0<i<MAX_DIGIT，均需满足0<=bTmp[i]<=9
					 此注释之添加乃由计算Delt(p)<1e4时得到结果
					     [2005-08-06 11:42] Delt( 214281757 ) = 978
					 所致，虽然这个等式是正确的，但是214281757却并非素数。
					 此注释不得删除，以后的注释得参考本注释进行。
										2005-08-06 12:48 (Chenbo)

		添加日期: 2004-11-27 15:45
	*/
	BOOL IsPrime(int bTmp[MAX_DIGIT]);


	/*
		bTmp是否为素数，是合数时返回FALSE，
		只检验位数大于2的，而且只判断其是否被有限个数整除
		添加日期: 2004-11-27 15:45
	*/
	BOOL IsPrime2(int bTmp[MAX_DIGIT]);


	/*
		功能说明: nLimitN为最多检验的个数, 
				  依次从2、3、5逐步检验，最多检验24个
		添加日期: 2005-02-06 10:14
	 */
	BOOL IsPrime3(int bTmp[MAX_DIGIT], int nLimitN);

	BOOL IsPrimeGetFactor(BigNum *bnTmp, BigNum *bnFactor);

	/*
		功能说明: 求aTmp的一重数根，如shugen(759)=21
		添加日期: 2005-02-06 10:16
	 */
	int shugen(int aTmp[MAX_DIGIT]);

	/*
		要求aTmp除了最后一位可能超过99外，别的都在0～99。特为b++准备
		添加日期: 2004-11-28 12:44
	 */
	BOOL ZZH2(int aTmp[MAX_DIGIT]);

	
	/*
	 *  功能说明: ZZH2的加强，要求从aTmp[1] ~aTmp[aTmp[0]]所有的数
	 *            在区间[-(WK_DIGIT_BASE-1),WK_DIGIT_BASE-1]之间,
	 *            aTmp[aTmp[0]+1]到aTmp[MAX_DIGIT]为0。
	 *            aTmp[0]>0 (不能等于0)
	 *            此函数专为a-b设计
	 *
	 *  添加日期: 2004-11-29 19:57
	 */
	BOOL ZZH2A(int aTmp[MAX_DIGIT]);

	/*
	 *  功能说明: ZZH2的加强，要求从aTmp[1] ~aTmp[aTmp[0]]所有的数
	 *            在区间[0,(WK_DIGIT_BASE-1)^2]
	 *            之间,
	 *            aTmp[aTmp[0]+1]到aTmp[MAX_DIGIT]为0。
	 *            aTmp[0]>0 (不能等于0)
	 *            此函数专为a*b设计. 
	 *            为乘法准备。
	 *
	 *  添加日期: 2008-02-04 16:15
	 */
	BOOL ZZH2B(int aTmp[MAX_DIGIT]);

	/*
	 *  功能说明: ZZH2的加强，要求从aTmp[1] ~aTmp[aTmp[0]]所有的数
	 *            在区间[0,(WK_DIGIT_BASE-1)^2]
	 *            之间,
	 *            aTmp[aTmp[0]+1]到aTmp[MAX_DIGIT]为0。
	 *            aTmp[0]>0 (不能等于0)
	 *            此函数专为a/b设计.
	 *
	 *  添加日期: 2008-02-04 16:15
	 */
	BOOL ZZH2C(int aTmp[MAX_DIGIT]);




	/*
		开平方
		添加日期: 2004-11-29 20:30
	*/
	BOOL Sqrt(int aTmp[MAX_DIGIT], int bTmp[MAX_DIGIT]);


	/*
		为分解因子所作的一些准备
		添加日期: 2004-11-29 20:34
	*/
	BOOL FactorPrepare();
	

	/*
		将aTmp[]转化为CString
		添加日期: 2004-11-28 13:30
	*/
	CString GetResultMy(int a[MAX_DIGIT]);

	
	/*
		分解因子，这函数废了我一番心神，效果还是不大好，但是却将加减除实现了
		添加日期: 2004-11-29 20:31
	*/
	int Factor();

	/*
		当a=b时a-b
		添加日期: 2004-11-29 20:33
	*/
	BOOL MinusEq(int aTmp[MAX_DIGIT], int bTmp[MAX_DIGIT]);

	/*
		正则化，就是去掉负数和大于10的数
		(此函数必须考虑所有情况，这里每一位的范围是-9~18,a[0]>=0)
	*/
	BOOL ZZH(int aTmp[MAX_DIGIT]);

	/*
		判断a与b的大小
		a>b 返回1
		a<b 返回-1
		a=b 返回0
		添加日期: 2004-11-29 20:14
	*/
	int Compare(const int aTmp[MAX_DIGIT], const int bTmp[MAX_DIGIT]);

	/*
		aTmp-bTmp，得到的结果放到cTmp中。
		在计算过程中aTmp和bTmp的值不会改变。
		添加日期: 2004-11-29 20:23
		更新日期: 2005-11-10 22:38
		          2009-08-14 08:14    将a和b的类型改为const类型的。
		更新说明: 改为a-b=c的形式并且a和b的值不改变
	*/
	BOOL Minus(const int aTmp[MAX_DIGIT], const int bTmp[MAX_DIGIT], int cTmp[MAX_DIGIT]);

	/*
	 *  功能说明: 赋值，将b付给a,
	 *            这个函数是预留的,不得随便改动,
	 *            必须给每一位赋值.
	 *
	 *  添加日期: 2004-11-29 20:24
	 */
	BOOL fz(int aTmp[MAX_DIGIT], const int bTmp[MAX_DIGIT]);

	/*
	 *	功能说明: 赋值，将b付给a,这个函数是预留的，不得随便改动;
	 *	          为了不造成混乱，这里将名字改为fz2(),
	 *            这里b是一个int型的数，注意！！
	 *
	 *  添加日期: 2006-02-22 20:34
	 */
	BOOL fz2(int aTmp[MAX_DIGIT], const int bTmp);



	/*
	 *  功能说明: aTmp/bTmp = cTmp 余数为 dTmp。
	 *            也就是 aTmp = bTmp*cTmp+dTmp，
	 *            计算过程中aTmp和bTmp的值不会改变。
	 *	          注意输入的时候需要确保bTmp不为0及其他一些输入
	 *            方面的合法性要求。
     *
     *  添加日期: 2007-01-31 15:28
	 */
	BOOL Div(const int aTmp[MAX_DIGIT],const int bTmp[MAX_DIGIT],
		int cTmp[MAX_DIGIT],int dTmp[MAX_DIGIT]);

	BOOL ClearAll();
	
	CString GetResult();

	/**
	 * 功能说明: 将a设置为0	
	 * 添加日期: 2008-02-01 21:13
	 */
	BOOL Clear(int aTmp[MAX_DIGIT]);



	//给b赋值
	BOOL fzb(CString strb);

	//给a赋值
	int fza(CString stra);

	CString Add(CString nA, CString nB, CString nResult);


	/*
	 *	添加日期: 2005-01-29 15:40
	 比如：当需要知道2^435的2^30次时需使用
	 GetBigNum(1, 3, bnGet);//其中1代表30有2位，3代表最高为为3
	 */
	BOOL GetBigNum(int nDigitAt, int nNumD, int bnRes[MAX_DIGIT]);

	MyMath();
	virtual ~MyMath();

private:
	BOOL sqrtOwn(int aTmp[MAX_DIGIT], int bTmp[MAX_DIGIT]);

	/*
		将aTmp的所有值设为0(内部函数)
		注意此操作将会把aTmp[0]置零
		添加日期: 2005-02-06 10:52
	*/
	void Clear0(int aTmp[]);

	/*
	 *	功能说明: 返回一个数相对于10为底数对数函数
	 *  添加日期: 2007-02-12 08:50
	 */
	int GetRepLogNum(__int64 nIn, int *pOut);

private://function
	/*
     *	dst = src * WK_DIGIT_BASE
	 *
     *  添加日期: 2008-02-03 12:31
     */
	BOOL Mult10(int srcTmp[MAX_DIGIT], int dstTmp[MAX_DIGIT]);
private://attribute

	BigNum m_BNTool;//工具类
};

#endif // !defined(AFX_MYMATH_H__BE90C74F_9902_419F_AA7E_0EDCAE848729__INCLUDED_)


























