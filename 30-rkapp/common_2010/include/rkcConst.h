/*****************************************************************************
ģ����      : CNC����̨
�ļ���      : cncConst.h
����ļ�    : 
�ļ�ʵ�ֹ���: ���������ʹ������,��cnc��UI���ֺ�cnclib���ֹ�ͬʹ��
����        : 
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��       �汾        �޸���      �޸�����
2014/12/20   1.4         Ф��Ȼ        ����
******************************************************************************/
#pragma once

#ifndef _CMSCONST_20110423_H_
#define _CMSCONST_20110423_H_

#include "kdvtype.h"
#include <map> 
using namespace std;

#define PrtRkcMsg (CRkcPrintCtrl::GetPrintCtrl()->PrintMsg)                        //��ӡCurl��Ϣ�ӿ�
#define RKCMAPPING_HELPER (CRkcPrintCtrl::GetPrintCtrl()->MappingHelper)                  //ע���ӡ����Ϣ��

//------------------------------�����벿��------begin-------------------------------
/*�ն˿���̨����(27501 - 29500)*/
#define ERR_BGN		100
#define ERR_END		ERR_BGN + 1999

#define MAX_IP_LENGTH               16
#define MAX_ALIAS_LENGTH            32
#define MAX_SEARCH_TIME             10000

//rkcLib�еĴ�����
enum EmErrRkcLib
{

#define ERR_RKC_LIB_BEGIN  ERR_BGN

    // ����̨����
    errrkc = ERR_RKC_LIB_BEGIN,
#define ERR_RKC                                 errrkc

	// ����̨����
	err_rk_creatinstance,
#define ERR_RK_CREATINSTANCE                    err_rk_creatinstance

    // �ӿ���Ч
    errInterface,
#define ERR_RK_INTERFACE                        errInterface

    //osp ��ʼ��ʧ��
    errOspInit,
#define  ERR_OSP_Init                           errOspInit   

    //Socket��ʼ������
    errSocketInit,
#define  ERR_SOCKET_INIT                        errSocketInit   

    //Socket����ʧ��
    errSocketConnect,
#define  ERR_SOCKET_CONNECT                     errSocketConnect

	errCncLibEnd,
#define ERR_CNC_LIB_END                         errCncLibEnd
		
};
 
#define RKC_UPDATEFILE_TYPE                     "lpc1837_app"
#define RKC_UPDATEFILE_NAME                     "rk100.bin"
 
#endif
