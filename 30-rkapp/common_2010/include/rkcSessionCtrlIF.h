#pragma once
#include "kdvdispevent.h"
#include "rkcsysctrlif.h"
#include "rkcconfigctrlif.h"
#include "rkcsearchctrlif.h"
#include "rkcstruct.h"
#include "mspsearch.h"

class CRkcSessionCtrlIF : public CKdvDispEvent 
{
public:
    //获取接口 
    virtual u16 RkcGetInterface(CRkcSysCtrlIF **ppCtrl) = 0;
    virtual u16 RkcGetInterface(CRkcConfigCtrlIF **ppCtrl) = 0;
    virtual u16 RkcGetInterface(CRkcSearchCtrlIF **ppCtrl) = 0;
};
