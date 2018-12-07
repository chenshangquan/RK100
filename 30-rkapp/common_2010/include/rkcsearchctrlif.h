/*****************************************************************************
模块名      : rkclib接口
文件名      : rkcsearchctrlif.h
相关文件    : 
文件实现功能: rkc搜索
作者        : 叶良平
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2018/9/5    1.0         叶良平        创建
******************************************************************************/
#ifndef __RKCSEARCHCTRLIF_H__
#define __RKCSEARCHCTRLIF_H__

#include "kdvdispevent.h"
#include <vector>
#include "mspsearch.h"

enum EmSearchType
{
    emTypeAll = 0,
    emTypeIP,
};

class CRkcSearchCtrlIF : public CKdvDispEvent
{
public:
    /**
	*   start Search
	*/ 
    virtual u16 StartSearch() = 0;
    /**
	*   end Search
	*/ 
    virtual u16 EndSearch() = 0;
    /**
	*   ReSet
	*/ 
    virtual void ReSet() = 0;
    /**
	*   获取列表
	*/ 
    virtual const vector<TDevItem>& GetDevList() const = 0;
    /**
	*   set search type
	*/ 
    virtual u16 SetSearchType(EmSearchType emtype , u32 dwStartip , u32 dwEndip) = 0;
};

#endif __RKCSEARCHCTRLIF_H__