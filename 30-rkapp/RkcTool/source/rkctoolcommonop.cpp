#include "StdAfx.h"
#include "rkctoolcommonop.h"

#include "searchequipmentlogic.h"
#include "loginlogic.h"
#include "messageboxlogic.h"
#include "tipboxlogic.h"
#include "toolframelogic.h"
#include "networksetuplogic.h"
#include "radiosetuplogic.h"
#include "workingmodelogic.h"
#include "backupupgradelogic.h"
#include "setmenulogic.h"
#include "modifypasswordlogic.h"
#include "Debugmodelogic.h"
#include "netchangelogic.h"

IRkcToolCommonOp::IRkcToolCommonOp(void)
{
}


IRkcToolCommonOp::~IRkcToolCommonOp(void)
{
}


void IRkcToolCommonOp::RegLogics()
{
	REG_LOGIC(CSearchEquipmentLogic);
    REG_LOGIC(CLoginLogic);
    REG_LOGIC(CMessageBoxLogic);
    REG_LOGIC(CTipBoxLogic);
    REG_LOGIC(CToolFrameLogic);
    REG_LOGIC(CNetworkSetupLogic);
    REG_LOGIC(CRadioSetupLogic);
    REG_LOGIC(CWorkingModeLogic);
    REG_LOGIC(CBackupUpgradeLogic);
    REG_LOGIC(CSetMenuLogic);
    REG_LOGIC(CModifyPasswordLogic);
    REG_LOGIC(CDebugModeLogic);
    REG_LOGIC(CNetChangeLogic);

	return ;
}

bool IRkcToolCommonOp::NotifyMsg(u16 wMsgId, void *pData)
{
	TMsgParam Msg;
	Msg.wMsgId = wMsgId;
	Msg.pData = (UINT_PTR)pData;
	IRkcToolMsgManager::GetSingletonPtr()->PostMsg(Msg);
	return true;
}

bool IRkcToolCommonOp::NotifyMsg(u16 wMsgId, WPARAM wParam, LPARAM lParam)
{
	TMsgParam Msg;
	Msg.wMsgId = wMsgId;
	Msg.pData = (UINT_PTR)wParam;
	Msg.lParam = lParam;
	IRkcToolMsgManager::GetSingletonPtr()->PostMsg(Msg);
	return true;
}


MbString IRkcToolCommonOp::StringFormat(const char *format, ... )
{
	char str[1024] = { 0 };
	va_list pvlist;
	va_start(pvlist, format);
	vsnprintf((char *)str, 1024, format, pvlist);
	va_end(pvlist);
	return str;
}
