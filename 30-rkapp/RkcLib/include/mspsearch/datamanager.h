#pragma once

#include "broadcast.h"

class CDataManager
{
private:
    CDataManager();

public:
	bool				Init();
	bool				Release();
	bool				SetMsgAckCB(MsgAckCB mCB, u32 dwContext);
	bool				SendDevDetectMsg(bool bRefreshAdapter);
    bool                SendDevDetectMsgByUnicast(bool bRefreshAdapter, u32 dwStart, u32 dwEnd);
    bool                SetDevDetectCtrl(bool bDetect);
    bool                SendNetPrmMsg(u32 dwDstIP, u8* pDstMacAddr, u8* abySecureCode, char* szUser, char* szPwd, TDevNetParam* pDevNetPrm);
    bool                SendRebootMsg(u32 dwDstIP, u8* pDstMacAddr, u8* abySecureCode, char* szUser, char* szPwd);
    static CDataManager*	getInstance();

private:
	CBroadcast			m_cBroadCast;
    static CDataManager*	m_pscMgrdata;
};

