/*****************************************************************************
ģ����      : rkclib�ӿ�
�ļ���      : rkcsearchctrlif.h
����ļ�    : 
�ļ�ʵ�ֹ���: rkc����
����        : Ҷ��ƽ
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2018/9/5    1.0         Ҷ��ƽ        ����
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
	*   ��ȡ�б�
	*/ 
    virtual const vector<TDevItem>& GetDevList() const = 0;
    /**
	*   set search type
	*/ 
    virtual u16 SetSearchType(EmSearchType emtype , u32 dwStartip , u32 dwEndip) = 0;
};

#endif __RKCSEARCHCTRLIF_H__