/*=============================================================================
ģ   ��   ��: UNICODE�궨��
��   ��   ��: unicode.h
�� ��  �� ��: 
�ļ�ʵ�ֹ���: �ṩUNICODE�õĺ궨��
��        ��: �޿���
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���      �޸�����
2013/01/23  4.7     �޿���        ����
=============================================================================*/
#if !defined(UNICODE_INCLUDED_)
#define UNICODE_INCLUDED_

#pragma once

// �ڹ��̵�Ԥ������м���_CSTRING_NO_TRANS
// �Խ�ֹUNICODE�汾��CString�Զ�����ת������
// ���Զ�����ת����CP_ACP����ת��������ָ�����룬������ʵ�ʱ��벻��
// ͨ���÷������ڱ����ڷ���δת���Ĵ���
// 
// ��Ҫ�޸�AFX.H�е�CString����
// �����º�����#ifndef _CSTRING_NO_TRANS  #endif��������
// CString(LPCSTR lpsz);
// CString(LPCSTR lpch, int nLength);
// CString(const unsigned char* psz);
// const CString& operator=(char ch);
// const CString& operator=(LPCSTR lpsz);
// const CString& operator=(const unsigned char* psz);
// const CString& operator+=(char ch);
// friend CString AFXAPI operator+(const CString& string, char ch);
// friend CString AFXAPI operator+(char ch, const CString& string);

// ��ֹ��©_UNICODE
#ifdef UNICODE
	#ifndef _UNICODE
		#define _UNICODE
	#endif
#endif

// ��ֹ��©UNICODE
#ifdef _UNICODE
	#ifndef UNICODE
		#define UNICODE
	#endif
#endif

// ����tstring
#ifndef tstring
	#ifdef _UNICODE
#define tstring wstring
	#else
#define tstring string
	#endif
#endif

// ����_countof�����ڻ�ȡ�����Ԫ�ظ���
#ifndef _countof
	#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif

// CP936��GBK���� by zjl
#define CP936			936

#include <tchar.h>

#if ( _MSC_VER <= 1200 )
	// ��ATL7�ĺ���ֲ��VC6
	#include "atlconv7_vc6.h"
#else
	#include <atlexcept.h>
	#include <atlconv.h>
	using namespace ATL;
#endif

#endif
