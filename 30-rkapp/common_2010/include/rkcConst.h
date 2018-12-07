/*****************************************************************************
模块名      : CNC控制台
文件名      : cncConst.h
相关文件    : 
文件实现功能: 声明常量和错误代码,供cnc的UI部分和cnclib部分共同使用
作者        : 
版本        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期       版本        修改人      修改内容
2014/12/20   1.4         肖楚然        创建
******************************************************************************/
#pragma once

#ifndef _CMSCONST_20110423_H_
#define _CMSCONST_20110423_H_

#include "kdvtype.h"
#include <map> 
using namespace std;

#define PrtRkcMsg (CRkcPrintCtrl::GetPrintCtrl()->PrintMsg)                        //打印Curl消息接口
#define RKCMAPPING_HELPER (CRkcPrintCtrl::GetPrintCtrl()->MappingHelper)                  //注册打印的消息名

//------------------------------错误码部分------begin-------------------------------
/*终端控制台错误(27501 - 29500)*/
#define ERR_BGN		100
#define ERR_END		ERR_BGN + 1999

#define MAX_IP_LENGTH               16
#define MAX_ALIAS_LENGTH            32
#define MAX_SEARCH_TIME             10000

//rkcLib中的错误码
enum EmErrRkcLib
{

#define ERR_RKC_LIB_BEGIN  ERR_BGN

    // 控制台错误
    errrkc = ERR_RKC_LIB_BEGIN,
#define ERR_RKC                                 errrkc

	// 控制台错误
	err_rk_creatinstance,
#define ERR_RK_CREATINSTANCE                    err_rk_creatinstance

    // 接口无效
    errInterface,
#define ERR_RK_INTERFACE                        errInterface

    //osp 初始化失败
    errOspInit,
#define  ERR_OSP_Init                           errOspInit   

    //Socket初始化错误
    errSocketInit,
#define  ERR_SOCKET_INIT                        errSocketInit   

    //Socket连接失败
    errSocketConnect,
#define  ERR_SOCKET_CONNECT                     errSocketConnect

	errCncLibEnd,
#define ERR_CNC_LIB_END                         errCncLibEnd
		
};
 
#define RKC_UPDATEFILE_TYPE                     "lpc1837_app"
#define RKC_UPDATEFILE_NAME                     "rk100.bin"
 
#endif
