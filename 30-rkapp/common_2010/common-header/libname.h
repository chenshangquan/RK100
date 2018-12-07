/*=============================================================================
模   块   名: 头文件及库名定义
文   件   名: libname.h
相 关  文 件: 
文件实现功能: 提供根据编译器及编译环境自动选择头文件和库名的宏定义
作        者: 邹俊龙
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2013/03/14  4.7     邹俊龙        创建
=============================================================================*/
#pragma once

// 定义一些库文件和头文件的宏，便于使用
#ifdef _UNICODE
	#define LIB_UILIB		"uilib_u.lib"
	#define LIB_NMSCOMMON	"nmscommon_u.lib"
	#define LIB_MCSLIB		"mcslib_u.lib"
	#define LIB_SLIMXML		"slimxml_u.lib"
	#define LIB_MULTILAN	"multilan_u.lib"
    #define LIB_PRINTLIB    "printlib_u.lib"
	#define LIB_KDVDECODER	"kdvdecoder_u.lib"
	#define LIB_KDVDECODER_NGP "KdvDecoder_NGP.lib"
    #ifdef _DEBUG
	    #define LIB_DUILIB		"duilib_ud.lib"
    #else
        #define LIB_DUILIB		"duilib_u.lib"
    #endif
	#define LIB_APPFRAME	"appframe_u.lib"
#else
	#define LIB_UILIB		"uilib.lib"
	#define LIB_NMSCOMMON	"nmscommon.lib"
	#define LIB_MCSLIB		"mcslib.lib"
	#define LIB_SLIMXML		"slimxml.lib"
	#define LIB_MULTILAN	"multilan.lib"
    #define LIB_PRINTLIB    "printlib.lib"
	#define LIB_KDVDECODER	"kdvdecoder.lib"
	#define LIB_DUILIB		"duilib.lib"
	#define LIB_APPFRAME	"appframe.lib"
#endif

#if( _MSC_VER > 1200 )
	#define H_CODECLIB "codeclib_vs2010.h"
#else
	#define H_CODECLIB "codeclib.h"
#endif
