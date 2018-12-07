#include "stdall.h"
#include "datamanager.h"
#include "broadcast.h"

CDataManager* CDataManager::m_pscMgrdata = NULL;

CDataManager::CDataManager()
{

}


CDataManager* CDataManager::getInstance()
{
	if (NULL == m_pscMgrdata)
	{
        m_pscMgrdata = new CDataManager();
	}

	return m_pscMgrdata;
}

bool CDataManager::Init()
{
	return m_cBroadCast.Init();
}

bool CDataManager::Release()
{
	return m_cBroadCast.Exit();
}

bool CDataManager::SetMsgAckCB(MsgAckCB mCB, u32 dwContext)
{
	return m_cBroadCast.SetMsgAckCB(mCB, dwContext);
}

bool CDataManager::SendDevDetectMsg(bool bRefreshAdapter)
{
	return m_cBroadCast.SendDevDetectMsg(bRefreshAdapter);
}

bool CDataManager::SendDevDetectMsgByUnicast(bool bRefreshAdapter, u32 dwStart, u32 dwEnd)
{
    return m_cBroadCast.SendDevDetectMsgByUnicast(bRefreshAdapter, dwStart, dwEnd);
}

bool CDataManager::SetDevDetectCtrl(bool bDetect)
{
    return m_cBroadCast.SetDevDetectCtrl(bDetect);
}

bool CDataManager::SendNetPrmMsg(u32 dwDstIP, u8* pDstMacAddr, u8* abySecureCode, char* szUser, char* szPwd, TDevNetParam* pDevNetPrm)
{
    return m_cBroadCast.SendNetPrmMsg(dwDstIP, pDstMacAddr, abySecureCode, szUser, szPwd, pDevNetPrm);
}

bool CDataManager::SendRebootMsg(u32 dwDstIP, u8* pDstMacAddr, u8* abySecureCode, char* szUser, char* szPwd)
{
    return m_cBroadCast.SendRebootMsg(dwDstIP, pDstMacAddr, abySecureCode, szUser, szPwd);
}
