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
    ˵��: ������Powerʱ��MAX_DIGIT��Ϊ2000�ȽϺ��ʣ�
	      ��ʱ����10^233��2^739�ȶ���������Ҫ��
  
	//reserved 20 (2005-01-29 15:06) ӦΪѰ�ҵ���С��10^10��p,
	//����20λӦ�ù���

	//reserved 30 (2005-04-09 09:25) ����p�����Ѿ�����500e5
	//����Ϊ�˱��գ�ȡ30λ

	//�����Ϊ�˼���m^n, ����MAX_DIGITȡֵΪ1000, 
	//��MAX_DIGIT����10000ʱ,�����ջ����Ĵ���.
	//ChenBo 2005-10-07 17:22 add the explaination
	
	//reserved 50 (2005-10-31 19:24)
	//˵������ֵ��Ӧ�����䶯
	//�������ڼ�������С��40λ�����Ѿ������ˡ���������


	//��������ԭ������MAX_DIGIT�ݶ�Ϊ50����û������Ŀ��
	//��Ӧ���Ĵ�ֵ��
	//updated: 2008-01-31 19:52

    //��������WK_DIGIT_BASE�����룬��Ӧ4�ش�ֵӦ��Ϊ20

	//�������ķ�ΧΪ0��200λ����������ط���ʱ�̶�Ϊ200.
	//û������ԭ�����ֵ��ʱ���ġ�
	//updated:2009-08-14

	// ***
	// reserved 20 (2010-10-11 10:12)
	// ˵������ֵ��Ӧ�����䶯(�˳������ҪĿ���Ǽ���Delt(p)).
*/
#define MAX_DIGIT 100

//����Deltʱÿ�ε����Ĳ���
//ע���ֵ��Ҫ����5��2008-02-01 20:36��ӣ�
#define WK_DELT_STEP_CUR 7

//reserved 40 (2005-11-01 07:34) should not change without suitable reason
#define MAX_DIGIT_P 8//ϣ��Ѱ�ҵ�p�����λ��

struct BigNum
{
public:
	//������
	int m_a[MAX_DIGIT];

	/**
        ���췽��
	*/
	BigNum()
	{
		memset(m_a, 0, sizeof(m_a));
		m_a[0] = 1;
	}
public:
	/*
	 *	let a = 0;
        �������: 2006-02-22 23:11
	 */
	BOOL ClearMy(int aTmp[MAX_DIGIT]);

	/*
        ��int nת��Ϊint n[MAX_DIGIT]����ʽ,����ʱֻ��nSource<100�����γ���
        here bTmp is source and aTmp for memory
        �������:2006-02-22 23:07
	*/
	BOOL fz2(int aTmp[MAX_DIGIT], int bTmp);

	/*
		Ҫ��aTmp�������һλ���ܳ���9�⣬��Ķ���0��9����Ϊb++׼��
		also for b+=2;
		�������: 2005-01-19 19:37
	 */
	BOOL ZZH2(int aTmp[MAX_DIGIT]);

	BOOL AddSmallDigit(int bSmall);

	/*
	 *	��m_a����Ϊ0��
	 *  �������: 2007-02-05 09:01
	 */
	BOOL Clear(void);

	/*
	 *	��m_a����ֵ���������һ�����ε�����
	 *  �������: 2007-02-05 08:32
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

extern BigNum m_BigNumPrime25[25];//�洢С��100��25������(as type of BigNum)

//������100~200֮���21������(2006-03-15)
extern int m_nPrime25[78498];//�洢С��10^6��78498������(as type of int)
extern BigNum m_BNDeltRes[MAX_DIGIT_P*4];//���õ���
extern BOOL bBigNumPrimeHasInit;//m_BNDeltRes�Ƿ��Ѿ���ʼ��
/*
	���˵��: a[0]���λ��
	��a[0]=0ʱ��˵�������Ϊ0(��δ���丳ֵ������)�������ʱ���a[i]!=0��˵�����ڴ���
	a[1]=1,���λ��Ϊ0ʱ˵�������Ϊ��
	Ҫ�����ʱ���������a[0]<=0������
*/
class MyMath  
{
public:
	int bDiff;//ÿ��b���ӵ���Ŀ
	int a[MAX_DIGIT];
	int b[MAX_DIGIT];
	int c[MAX_DIGIT];
	int d[MAX_DIGIT];
	int e[MAX_DIGIT];
	int nRes[MAX_DIGIT];//��Ž��
	int nReserved[MAX_DIGIT];//��ŵĻ���(Ҫ��ʹ��ʱ����ֵ��ʹ����֮������)
	int aAddb[MAX_DIGIT];
	
	int nCircle[MAX_DIGIT];
	int aSqrt[MAX_DIGIT];
	CString strR;

	//��������еõ��Ĵ�����Ϣ���˱���һ���ṩ��UI���á�
	CString m_strError;



	//һЩ����
	int m_ZERO[MAX_DIGIT];//0
	int m_ONE[MAX_DIGIT];//1
	int m_TEN[MAX_DIGIT];//10
	
public://������Щ�������ṩ��Dlg�����

	/*
	 *	����˵��: �ӷ�
	 *  �������: 2008-02-03 11:56
	 */
	BOOL JSQADD();

	/*
	 *  ����˵��: ���ڼ�������ʾ�ļ������㣬
	 *            �õ��Ľ����ŵ�c��
	 *
	 *  �������: 2004-11-29 20:25
	 */
	BOOL JSQMINUS();

	/*
	 *	�������˷�
	 *
	 *  �������: 2005-02-06 10:22
	 */
	BOOL JSQMULT();

	/*
		����˵��: ������
		�������: 2005-02-06 10:19
	*/
	BOOL JSQDIV();

	/*
		���ڼ��������ݣ�a��bΪ����
		�������: 2005-01-22 11:52
	*/
	BOOL JSQPOWER();

	/*
		ƽ����
		aΪ���룬�õ��Ľ����ŵ�nRes�С�

		�������: 2005-01-22 10:20
	*/
	BOOL JSQSQR();

	/*
	 *  ����˵��: ����˷�֮ǰ�ж�λ���Ƿ���ȷ 
     *            ����Ҫa[0]+b[0]<MAX_DIGIT
	 *
	 *  �������: 2005-10-13 19:21
	 */
	BOOL PreMult();



	BOOL JSQSQRT();


	/*
		����Delt(10, p)
		�������: 2004-12-11 21:27
	*/
	BOOL JSQDELT();


public://����Ϊ���ߺ�����һ�㲻���ⲿ����(������ܻ������)
	/*
	 *  ����˵��: ZZH2A�ļ�ǿ��Ҫ���aTmp[1] ~aTmp[nPos]���е���
	 *            ������[0,(WK_DIGIT_BASE-1)*2]
	 *            ֮��,
	 *            aTmp[nPos+1]��aTmp[MAX_DIGIT]Ϊ0��
	 *            aTmp[0]>0 (���ܵ���0)
	 *            �˺���רΪaTmp[i]++���.
	 *            (����iΪһ����1��MAX_DIGIT-1֮�����)
	 *
	 *  �������: 2008-02-04 20:14
	 */
	BOOL ZZH2D(int aTmp[MAX_DIGIT], int nPos);
	/*
	 *	����˵��: ��ȡһ����������λ����
	 *            Ҫ����������Ǳ�׼�͡�
	 *            ��nΪ0ʱ����0.
	 *
	 *  �������: 2008-02-03 11:58
	 */
	int GetDigit(int nTmp[MAX_DIGIT]);

	BOOL IsPrime64_2(__int64 n64Tmp);

	/**
	 *  ����˵��: ����������nTmp��ֵ����64λ����p64Tmp
	 *            �����ʱ��p64TmpӦ����ָ�롣
	 *  �������: 2008-02-01 21:52
	 */
	void IntAryToInt64(int nTmp[MAX_DIGIT], __int64 *p64Tmp);
	void Int64ToIntAry(__int64 n64Tmp, int bTmp[MAX_DIGIT]);
	BOOL IsPrime64(__int64 n64Tmp);
	
	/*
	 *	����˵��������Delt(n)
	 *            �������1e4�򷵻�10000�����򷵻�Delt��ֵ��
	 *            �������������n�Ǻ����򷵻�0
	 *            ����Ҫ�������n64Tmp����С��(2^64/10^WK_DELT_STEP_CUR)
	 *
	 *            ��Delt15Genuine()������֮ͬ�����ڴ˷��������ж�
	 *            Delt(n64Tmp)�Ƿ�С��10000�����ȼ���10^5000 mod n, Ȼ��������д�
	 *            5000��9999��iֵ���ж�10^i mod n�Ƿ�Ϊ1������õ���������i, ˵��
	 *            Delt(n)С��10000�������´�1��9999��iֵ����һ�εõ�Delt(n)��׼ȷֵ��
	 *            ���û�еõ���5000��9999��iֵ��˵��Delt(n)>10000, ��ʱ��n��ֱ�ӷ��ء�
	 *            �˷�����ԭ�����ڵ�Delt(n)<5000ʱ�����ٴ���һ��5000��9998֮��
	 *            ��ֵiʹ�� 10^i mod n = 1.(�˷�������Mult��ModЧ�ʽϵ���δʵʩ��
	 *            ����ɼ�F:\my\cpp\cacu\JSQ\backup\Delt15.txt�ļ�.)
	 *
	 *
	 *            �˷�������������: 2008-02-01 21:02
	 *  �������: 2007-02-12 08:46
	 */
	int Delt15(__int64 n64Tmp);

	int Delt15Genuine(__int64 n64Tmp);
	

	/*
		����˵��:�ж�aTmp�Ƿ�Ϊ��
		         ��a����0ʱ����TRUE, ���򷵻�FALSE.
		�������: 2005-02-06 09:57
	*/
	BOOL IsZero(int aTmp[MAX_DIGIT]);

	BOOL MinusEq(int dTmp[MAX_DIGIT], int bTmp[MAX_DIGIT], int cTmp[MAX_DIGIT]);

	/*
		���ڼ�����ݣ�a��bΪ���룬resΪ���
		�������: 2005-01-22 11:51
	 */
	BOOL Power(BigNum *aTmp, BigNum *bTmp, BigNum *resTmp);


	/*
		����aTmp^(bTmp-1) mod bTmp 
		�����ŵ�resTmp��
		�������: 2005-01-29 16:01
	*/
	BOOL PowerMod(BigNum *aTmp, BigNum *bTmp2, BigNum *resTmp);


	/*
	 *	�ӷ�, aTmp+bTmp=cTmp
	 �������: 2005-02-06 10:21
	 �޸����ڣ�2009-08-14 08��23    ��a��b��Ϊconst���͵ġ�
	 */
	BOOL Add(const int aTmp[MAX_DIGIT], const int bTmp[MAX_DIGIT], int cTmp[MAX_DIGIT]);

	BOOL Mult(const int aTmp[MAX_DIGIT], const int bTmp[MAX_DIGIT], int cTmp[MAX_DIGIT]);

	


	/*
 		��int aTmp[MAX_DIGIT]ת��Ϊint�͵�
		���ؽ��Ϊint
		�������: 2004-11-28 13:26
	*/
	int IntMDToInt(int aTmp[MAX_DIGIT]);
	

	/*
		10^a = b
		Ҫ��:0<a<10000
		�������: 2004-11-28 13:22
	*/
	BOOL JSQREP10();


	/*
		���ڼ�������ʾ��mod����
		�������: 2004-11-29 20:26
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
		a[]�Ƿ��ܱ�b������������ԵĻ�����TRUE,���򷵻�FALSE
		����Ҫ��0<b<100
		�������: 2004-11-27 15:43
	*/
	BOOL IsMod2a(int aTmp[], int bTmp);
	

	BOOL IsMod2(int aTmp[MAX_DIGIT], int bTmp[MAX_DIGIT]);


	/*
	���Ƽ���a/b��ֵ�����λ,�õ��Ľ��ֻӦ��Ϊ
	������ x=[a/b]
	�򷵻ص�ֵΪx��x-1
	����a=72, b=24, �򷵻�3
	a=7200000000000001, b=2400000, �򷵻�2
	˼����a<bʱ����1
	��a>=bʱ, ��aD=a[0], bD=b[0];
	    1. b[0]<=3
		    11. a[0]<=3, ����[a/b]
			12. a[0]>3, ����[(a[aD]*100+a[aD-1]*10+a[aD-2])/b]
		2. b[0]>3
		    ����[(a[aD]*100+a[aD-1]*10+a[aD-2])/(b[bD]*100+b[bD-1]*10+b[bD-2]+1)]
	 �������: 2005-10-13 20:05
	 */
	int SigDIV(int aTmp[MAX_DIGIT], int bTmp[MAX_DIGIT]);


	/*
	 *	���Ƽ���a/b��ֵ�����λ
	 ʹ�ñ�����Ӧ�ñ�֤a>b
	 �˺�ʳ��ʱ����
	 �Ժ���Ҫ��ʱ������д
	 �����ж�
	     124......./124....
	 ��ʽ�ļ���ʱ��������
	 ��124000/1240 = 1
	 124000/1241 = 9
	 �������Ǽ򵥵����1�Ĺ�ϵ
	 �������: 2005-10-13 20:06
	 */
	int SigDIV2(int aTmp[MAX_DIGIT], int bTmp[MAX_DIGIT]);


	/*
	Ҫ��a[0]>=2
	a>b
	 return	aFTN3/bFTN2
	 �������: 2005-10-13 20:18
	 */
	int SigDIV2_32(int aTmp[MAX_DIGIT], int bTmp[MAX_DIGIT]);

	/*
	Ҫ��a[0]>=1
	a>b
	 return	aFTN3/bFTN3
	 �������: 2005-10-13 20:19
	 */
	int SigDIV2_33(int aTmp[MAX_DIGIT], int bTmp[MAX_DIGIT]);


	/*
	 b<1000ʱ����a mod b
	 ʹ�ô˺���ǰ���뱣֤b<1000, ��������õ��Ľ�����ܲ���
	 ����浽c��, 
	 this method is for test prime to a to lower than 100's factor
	 
	 �������: 2005-10-14 19:22
	 */
	BOOL Mod_b1000(int aTmp[MAX_DIGIT],int bTmp[MAX_DIGIT],int cTmp[MAX_DIGIT]);

	/*
	    ����˵����	  //a mod b = c,
	                  //(a,bΪ����,cΪ���,�õ����̲��账��)
	                  �����aTmp��cTmp������ͬһ������ı�����
		�������: 2008-02-01 21:11
	*/
	BOOL Mod(int aTmp[MAX_DIGIT],int bTmp[MAX_DIGIT],int cTmp[MAX_DIGIT]);

	
	/*
		����˵��: ���ҽ���bTmp������ʱ����TRUE.


		      ע��1���˺���Ϊ����������ֻ������һ���б���;����Ҫ�������кϷ��������
			         ����bTmp=2�򷵻�TRUE��bTmp=214281757�򷵻�FALSE��
					 �����������Ϸ�����ָbTmp[0]��Ҫ����������λ����bTmp������ڻ����2
					 ����0<i<MAX_DIGIT����������0<=bTmp[i]<=9
					 ��ע��֮������ɼ���Delt(p)<1e4ʱ�õ����
					     [2005-08-06 11:42] Delt( 214281757 ) = 978
					 ���£���Ȼ�����ʽ����ȷ�ģ�����214281757ȴ����������
					 ��ע�Ͳ���ɾ�����Ժ��ע�͵òο���ע�ͽ��С�
										2005-08-06 12:48 (Chenbo)

		�������: 2004-11-27 15:45
	*/
	BOOL IsPrime(int bTmp[MAX_DIGIT]);


	/*
		bTmp�Ƿ�Ϊ�������Ǻ���ʱ����FALSE��
		ֻ����λ������2�ģ�����ֻ�ж����Ƿ����޸�������
		�������: 2004-11-27 15:45
	*/
	BOOL IsPrime2(int bTmp[MAX_DIGIT]);


	/*
		����˵��: nLimitNΪ������ĸ���, 
				  ���δ�2��3��5�𲽼��飬������24��
		�������: 2005-02-06 10:14
	 */
	BOOL IsPrime3(int bTmp[MAX_DIGIT], int nLimitN);

	BOOL IsPrimeGetFactor(BigNum *bnTmp, BigNum *bnFactor);

	/*
		����˵��: ��aTmp��һ����������shugen(759)=21
		�������: 2005-02-06 10:16
	 */
	int shugen(int aTmp[MAX_DIGIT]);

	/*
		Ҫ��aTmp�������һλ���ܳ���99�⣬��Ķ���0��99����Ϊb++׼��
		�������: 2004-11-28 12:44
	 */
	BOOL ZZH2(int aTmp[MAX_DIGIT]);

	
	/*
	 *  ����˵��: ZZH2�ļ�ǿ��Ҫ���aTmp[1] ~aTmp[aTmp[0]]���е���
	 *            ������[-(WK_DIGIT_BASE-1),WK_DIGIT_BASE-1]֮��,
	 *            aTmp[aTmp[0]+1]��aTmp[MAX_DIGIT]Ϊ0��
	 *            aTmp[0]>0 (���ܵ���0)
	 *            �˺���רΪa-b���
	 *
	 *  �������: 2004-11-29 19:57
	 */
	BOOL ZZH2A(int aTmp[MAX_DIGIT]);

	/*
	 *  ����˵��: ZZH2�ļ�ǿ��Ҫ���aTmp[1] ~aTmp[aTmp[0]]���е���
	 *            ������[0,(WK_DIGIT_BASE-1)^2]
	 *            ֮��,
	 *            aTmp[aTmp[0]+1]��aTmp[MAX_DIGIT]Ϊ0��
	 *            aTmp[0]>0 (���ܵ���0)
	 *            �˺���רΪa*b���. 
	 *            Ϊ�˷�׼����
	 *
	 *  �������: 2008-02-04 16:15
	 */
	BOOL ZZH2B(int aTmp[MAX_DIGIT]);

	/*
	 *  ����˵��: ZZH2�ļ�ǿ��Ҫ���aTmp[1] ~aTmp[aTmp[0]]���е���
	 *            ������[0,(WK_DIGIT_BASE-1)^2]
	 *            ֮��,
	 *            aTmp[aTmp[0]+1]��aTmp[MAX_DIGIT]Ϊ0��
	 *            aTmp[0]>0 (���ܵ���0)
	 *            �˺���רΪa/b���.
	 *
	 *  �������: 2008-02-04 16:15
	 */
	BOOL ZZH2C(int aTmp[MAX_DIGIT]);




	/*
		��ƽ��
		�������: 2004-11-29 20:30
	*/
	BOOL Sqrt(int aTmp[MAX_DIGIT], int bTmp[MAX_DIGIT]);


	/*
		Ϊ�ֽ�����������һЩ׼��
		�������: 2004-11-29 20:34
	*/
	BOOL FactorPrepare();
	

	/*
		��aTmp[]ת��ΪCString
		�������: 2004-11-28 13:30
	*/
	CString GetResultMy(int a[MAX_DIGIT]);

	
	/*
		�ֽ����ӣ��⺯��������һ������Ч�����ǲ���ã�����ȴ���Ӽ���ʵ����
		�������: 2004-11-29 20:31
	*/
	int Factor();

	/*
		��a=bʱa-b
		�������: 2004-11-29 20:33
	*/
	BOOL MinusEq(int aTmp[MAX_DIGIT], int bTmp[MAX_DIGIT]);

	/*
		���򻯣�����ȥ�������ʹ���10����
		(�˺������뿼���������������ÿһλ�ķ�Χ��-9~18,a[0]>=0)
	*/
	BOOL ZZH(int aTmp[MAX_DIGIT]);

	/*
		�ж�a��b�Ĵ�С
		a>b ����1
		a<b ����-1
		a=b ����0
		�������: 2004-11-29 20:14
	*/
	int Compare(const int aTmp[MAX_DIGIT], const int bTmp[MAX_DIGIT]);

	/*
		aTmp-bTmp���õ��Ľ���ŵ�cTmp�С�
		�ڼ��������aTmp��bTmp��ֵ����ı䡣
		�������: 2004-11-29 20:23
		��������: 2005-11-10 22:38
		          2009-08-14 08:14    ��a��b�����͸�Ϊconst���͵ġ�
		����˵��: ��Ϊa-b=c����ʽ����a��b��ֵ���ı�
	*/
	BOOL Minus(const int aTmp[MAX_DIGIT], const int bTmp[MAX_DIGIT], int cTmp[MAX_DIGIT]);

	/*
	 *  ����˵��: ��ֵ����b����a,
	 *            ���������Ԥ����,�������Ķ�,
	 *            �����ÿһλ��ֵ.
	 *
	 *  �������: 2004-11-29 20:24
	 */
	BOOL fz(int aTmp[MAX_DIGIT], const int bTmp[MAX_DIGIT]);

	/*
	 *	����˵��: ��ֵ����b����a,���������Ԥ���ģ��������Ķ�;
	 *	          Ϊ�˲���ɻ��ң����ｫ���ָ�Ϊfz2(),
	 *            ����b��һ��int�͵�����ע�⣡��
	 *
	 *  �������: 2006-02-22 20:34
	 */
	BOOL fz2(int aTmp[MAX_DIGIT], const int bTmp);



	/*
	 *  ����˵��: aTmp/bTmp = cTmp ����Ϊ dTmp��
	 *            Ҳ���� aTmp = bTmp*cTmp+dTmp��
	 *            ���������aTmp��bTmp��ֵ����ı䡣
	 *	          ע�������ʱ����Ҫȷ��bTmp��Ϊ0������һЩ����
	 *            ����ĺϷ���Ҫ��
     *
     *  �������: 2007-01-31 15:28
	 */
	BOOL Div(const int aTmp[MAX_DIGIT],const int bTmp[MAX_DIGIT],
		int cTmp[MAX_DIGIT],int dTmp[MAX_DIGIT]);

	BOOL ClearAll();
	
	CString GetResult();

	/**
	 * ����˵��: ��a����Ϊ0	
	 * �������: 2008-02-01 21:13
	 */
	BOOL Clear(int aTmp[MAX_DIGIT]);



	//��b��ֵ
	BOOL fzb(CString strb);

	//��a��ֵ
	int fza(CString stra);

	CString Add(CString nA, CString nB, CString nResult);


	/*
	 *	�������: 2005-01-29 15:40
	 ���磺����Ҫ֪��2^435��2^30��ʱ��ʹ��
	 GetBigNum(1, 3, bnGet);//����1����30��2λ��3�������ΪΪ3
	 */
	BOOL GetBigNum(int nDigitAt, int nNumD, int bnRes[MAX_DIGIT]);

	MyMath();
	virtual ~MyMath();

private:
	BOOL sqrtOwn(int aTmp[MAX_DIGIT], int bTmp[MAX_DIGIT]);

	/*
		��aTmp������ֵ��Ϊ0(�ڲ�����)
		ע��˲��������aTmp[0]����
		�������: 2005-02-06 10:52
	*/
	void Clear0(int aTmp[]);

	/*
	 *	����˵��: ����һ���������10Ϊ������������
	 *  �������: 2007-02-12 08:50
	 */
	int GetRepLogNum(__int64 nIn, int *pOut);

private://function
	/*
     *	dst = src * WK_DIGIT_BASE
	 *
     *  �������: 2008-02-03 12:31
     */
	BOOL Mult10(int srcTmp[MAX_DIGIT], int dstTmp[MAX_DIGIT]);
private://attribute

	BigNum m_BNTool;//������
};

#endif // !defined(AFX_MYMATH_H__BE90C74F_9902_419F_AA7E_0EDCAE848729__INCLUDED_)


























