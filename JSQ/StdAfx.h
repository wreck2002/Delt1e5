// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__62DCD8EB_0D9B_465D_94CD_90FA7A2DE512__INCLUDED_)
#define AFX_STDAFX_H__62DCD8EB_0D9B_465D_94CD_90FA7A2DE512__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#define MSG_USER_FACTOR		0x1000
#define MSG_USER_STOP		0x1001//ֹͣ����
#define MSG_USER_STEPOVER    0x1001//һ���׶εļ������

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#define FILE_DELTOUT		_T("DELT1e4.txt")
#define FILE_DELT1e4CFG		_T("Delt1e4.cfg")
#define FILE_DELT_CURA		_T("CurA.txt")
#define FILE_DEBUG			_T("debug.txt")

//�������Ͷ���
#define OP_CACU_ADD			1//��
#define OP_CACU_MINUS		2//��
#define OP_CACU_MULT		3//��
#define OP_CACU_DIV			4//��
//#define OP_CACU_SQR		5//ƽ��
//#define OP_CACU_SQRT		6//��ƽ��
#define OP_CACU_POWER		7//��
//#define OP_CACU_FACTOR	8 //�ֽ�
#define OP_CACU_MOD			9//����
#define OP_CACU_GCD         10//�����Լ��
#define OP_CACU_lmd         11//����С������
#define OP_CACU_PHI         12
#define OP_CACU_DELT        13//����Delt(p)


//defeine the type of NEEDCACU
#define NC_FACTOR			1//�ֽ�����(less than 1e20) 2005-10-28
#define NC_DELT_BY_TIMER	121//121��ʾ����Delt(��ʱ������)
#define NC_DELT1E4			122//122��ʾ���̼߳���Delt


// ������ƣ��������ƵĿ�Ⱥͽ���4���ף�
// ��ʱ������ƵĿ��Ϊ2�����ƻ���Ϊ100
#define WK_DIGIT_BASE_WIDTH 4 //���ƵĿ��
#define WK_DIGIT_BASE 10000 //���ƻ���
#define WK_DIGIT_OUT_FORMAT _T("%04d") //���ʱ�ĸ�ʽ

#define WK_DIGIT_DELT1E5 100000  //����С��10^n-1, (1<n<100000)������

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__62DCD8EB_0D9B_465D_94CD_90FA7A2DE512__INCLUDED_)
