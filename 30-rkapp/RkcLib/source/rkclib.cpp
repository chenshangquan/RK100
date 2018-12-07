#include "stdafx.h"
#include "rkclib.h"
#include "rkcsession.h"
#include "rkcConst.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CRckLib::CRckLib()
{

}

CRckLib::~CRckLib()
{

}

/*=============================================================================
  函 数 名： CreateSession
  功    能： 创建实现了接口CRckSessionCtrlIF的对象
  算法实现： 接口使用完成后,调用DestroyInstance方法销毁对象
  全局变量： 
  参    数： CRckSessionCtrlIF **ppICnt 成功返回CRckSessionCtrlIF接口,失败返回NULL
  返 回 值： u16 
  -----------------------------------------------------------------------------
  修改记录：
  日  期        版本        修改人        走读人    修改内容
 2018.02.26     1.0             ylp                     创建
=============================================================================*/
u16 CRckLib::CreateSession(CRkcSessionCtrlIF **ppICnt)
{
    CRkcSession *pConnect = new CRkcSession();
    if(pConnect == NULL)
    {
        *ppICnt = NULL;
        return ERR_RK_CREATINSTANCE;
    }
    else
    {
        *ppICnt = pConnect;
        return NO_ERROR;
    }
}

/*=============================================================================
  函 数 名： DestroySession
  功    能： 销毁实现了接口CRckSessionCtrlIF的对象
  算法实现： 
  全局变量： 
  参    数： CRckSessionCtrlIF **ppICnt 输入接口CRckSessionCtrlIF,成功后返回NULL
  返 回 值： u16 
  说    明： 只能销毁由CreateInstance方法创建的对象
  -----------------------------------------------------------------------------
  修改记录：
  日  期        版本        修改人        走读人    修改内容
 2018.02.26     1.0              ylp                    创建
=============================================================================*/
u16 CRckLib::DestroySession(CRkcSessionCtrlIF **ppICnt)
{
    CRkcSession *pConnect = dynamic_cast<CRkcSession*>(*ppICnt);
    if(pConnect == NULL)
    {
        return ERR_RK_INTERFACE;
    }
    delete pConnect;
    *ppICnt = NULL;
    return NO_ERROR;
}