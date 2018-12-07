/*=============================================================================
模   块   名: UNICODE宏定义
文   件   名: unicode.h
相 关  文 件: 
文件实现功能: 提供UNICODE用的宏定义
作        者: 邹俊龙
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2013/01/23  4.7     邹俊龙        创建
=============================================================================*/
#if !defined(UNICODE_INCLUDED_)
#define UNICODE_INCLUDED_

#pragma once

// 在工程的预编译宏中加入_CSTRING_NO_TRANS
// 以禁止UNICODE版本的CString自动编码转换功能
// 因自动编码转换以CP_ACP进行转换，而非指定编码，可能与实际编码不符
// 通过该方法可在编译期发现未转换的代码
// 
// 需要修改AFX.H中的CString定义
// 将以下函数用#ifndef _CSTRING_NO_TRANS  #endif括起来来
// CString(LPCSTR lpsz);
// CString(LPCSTR lpch, int nLength);
// CString(const unsigned char* psz);
// const CString& operator=(char ch);
// const CString& operator=(LPCSTR lpsz);
// const CString& operator=(const unsigned char* psz);
// const CString& operator+=(char ch);
// friend CString AFXAPI operator+(const CString& string, char ch);
// friend CString AFXAPI operator+(char ch, const CString& string);

// 防止遗漏_UNICODE
#ifdef UNICODE
	#ifndef _UNICODE
		#define _UNICODE
	#endif
#endif

// 防止遗漏UNICODE
#ifdef _UNICODE
	#ifndef UNICODE
		#define UNICODE
	#endif
#endif

// 定义tstring
#ifndef tstring
	#ifdef _UNICODE
#define tstring wstring
	#else
#define tstring string
	#endif
#endif

// 定义_countof，用于获取数组的元素个数
#ifndef _countof
	#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif

// CP936即GBK编码 by zjl
#define CP936			936

#include <tchar.h>

#if ( _MSC_VER <= 1200 )
	// 把ATL7的宏移植到VC6
	#include "atlconv7_vc6.h"
#else
	#include <atlexcept.h>
	#include <atlconv.h>
	using namespace ATL;
#endif

#endif
