#include "stdall.h"
#include <stdio.h>
#include "mspsearch.h"


MSPSEARCH_API bool CDECL InitMspSearch()
{
    return CDataManager::getInstance()->Init();
}

MSPSEARCH_API bool CDECL ExitMspSearch()
{
    return CDataManager::getInstance()->Release();
}

MSPSEARCH_API bool SetMsgAckCB(MsgAckCB mCB, u32 dwContext)
{
    return CDataManager::getInstance()->SetMsgAckCB(mCB, dwContext);
}

MSPSEARCH_API bool SendDevDetectMsg(bool bRefreshAdapter)
{
    return CDataManager::getInstance()->SendDevDetectMsg(bRefreshAdapter);
}

MSPSEARCH_API bool SendDevDetectMsgByUnicast(bool bRefreshAdapter, u32 dwStart, u32 dwEnd)
{
    return CDataManager::getInstance()->SendDevDetectMsgByUnicast(bRefreshAdapter, dwStart, dwEnd);
}

MSPSEARCH_API bool SetDevDetectCtrl(bool bDetect /*= true*/)
{
    return CDataManager::getInstance()->SetDevDetectCtrl(bDetect);
}

MSPSEARCH_API bool SendNetPrmMsg(u32 dwDstIP, u8* pDstMacAddr, u8* abySecureCode, char* szUser, char* szPwd, TDevNetParam* pDevNetPrm)
{
    return CDataManager::getInstance()->SendNetPrmMsg(dwDstIP, pDstMacAddr, abySecureCode, szUser, szPwd, pDevNetPrm);
}

MSPSEARCH_API bool SendNetPrmMsgS(TDevItem* ptDevItem, char* szUser, char* szPwd, TDevNetParam* pDevNetPrm)
{
    if (ptDevItem->wTag != DT_V7_EXT_TAG)
    {
        szUser = NULL;
        szPwd = NULL;
    }
    printf("---------[Line=%d]dest mac: %02x-%02x-%02x-%02x-%02x-%02x \n", __LINE__,
        ptDevItem->tDevMacAddr.abyMac[0], ptDevItem->tDevMacAddr.abyMac[1], ptDevItem->tDevMacAddr.abyMac[2],
        ptDevItem->tDevMacAddr.abyMac[3], ptDevItem->tDevMacAddr.abyMac[4], ptDevItem->tDevMacAddr.abyMac[5]);

    return SendNetPrmMsg(ptDevItem->tDevInfo.tAddr.dwIpaddr, ptDevItem->tDevMacAddr.abyMac,
        ptDevItem->tDevEx.achSecureCode, szUser, szPwd, pDevNetPrm);
}

MSPSEARCH_API bool SendRebootMsg(u32 dwDstIP, u8* pDstMacAddr, u8* abySecureCode, char* szUser, char* szPwd)
{
    return CDataManager::getInstance()->SendRebootMsg(dwDstIP, pDstMacAddr, abySecureCode, szUser, szPwd);
}
