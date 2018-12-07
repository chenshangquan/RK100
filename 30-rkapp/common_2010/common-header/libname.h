/*=============================================================================
ģ   ��   ��: ͷ�ļ�����������
��   ��   ��: libname.h
�� ��  �� ��: 
�ļ�ʵ�ֹ���: �ṩ���ݱ����������뻷���Զ�ѡ��ͷ�ļ��Ϳ����ĺ궨��
��        ��: �޿���
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���      �޸�����
2013/03/14  4.7     �޿���        ����
=============================================================================*/
#pragma once

// ����һЩ���ļ���ͷ�ļ��ĺ꣬����ʹ��
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
