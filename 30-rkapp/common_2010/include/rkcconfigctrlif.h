/*****************************************************************************
模块名      : rkclib接口
文件名      : rkcsysctrlif.h
相关文件    : 
文件实现功能: rkc配置
作者        : 叶良平
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2018/10/23   1.0         叶良平        创建
******************************************************************************/
#ifndef __RKCCONFIGCTRLIF_H__
#define __RKCCONFIGCTRLIF_H__

#include "kdvdispevent.h"

class CRkcConfigCtrlIF : public CKdvDispEvent
{
public:
    /**
	*   重启设备
	*/ 
    virtual u16 ReBootRk() = 0;

    /**
	*   恢复出厂设置
	*/ 
    virtual u16 RestoreRk(TRK100LoginInfo tRK100LoginInfo) = 0;

    /**
	*   获取工作模式配置
	*/ 
    virtual u16 GetWorkModeConfig() = 0;
	/**
	*   获取工作模式配置内容
	*/
    virtual u16 GetWorkModeConfig(TRK100WorkMode& tRK100WorkMode) = 0;

    /**
	*   修改工作模式配置
	*/ 
    virtual u16 SetWorkModeConfig(TRK100WorkMode tRK100WorkMode) = 0;

    /**
	*   获取网络配置消息
	*/ 
    virtual u16 GetNetWorkConfig() = 0;
    /**
	*   获取网络配置内容
	*/
    virtual u16 GetNetWorkConfig(TRK100NetParam& tRK100NetParam) = 0;

    /**
	*   修改工作模式配置
	*/ 
    virtual u16 SetNetWorkConfig(TRK100NetParam tRK100NetParam) = 0;

    /**
	*   获取升级配置
	*/ 
    virtual u16 SetFtpUpdateFirst(TRK100TftpFwUpdate tRK100TftpFwUpdate) = 0;
    /**
	*   获取升级配置
	*/ 
    virtual u16 SetFtpUpdateSecond() = 0;
    /**
	*   获取升级内容
	*/ 
    virtual u16 GetUpdateConfig(TRK100UpdateHead& tRK100UpdateHead) = 0;

    /**
	*   获取电源配置
	*/ 
    virtual u16 GetPowerConfig() = 0;
    /**
	*   获取电源配置内容
	*/
    virtual u16 GetPowerConfig(TRK100PowerInfo& tRK100PowerInfo) = 0;

    /**
	*   获取调试模式
	*/ 
    virtual u16 GetDebugConfig() = 0;
    /**
	*   获取调试模式内容
	*/
    virtual u16 GetDebugConfig(TRK100DebugMode& tRK100DebugInfo) = 0;
    /**
	*   设置调试模式内容
	*/
    virtual u16 SetDebugConfig(TRK100DebugMode tRK100DebugInfo) = 0;
};

#endif __RKCSYSCTRLIF_H__