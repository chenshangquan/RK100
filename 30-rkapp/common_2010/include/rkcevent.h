#pragma once

#ifndef _EVRKCLIB_20180920_H_
#define _EVRKCLIB_20180920_H_



//rkcLib中消息定义
enum EmUiRkcMsg
{

#define UI_RKC_MSG_BEGIN  	2000 + 0x1 

	/************************************************************************/
	/** 连接 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkConnect	= UI_RKC_MSG_BEGIN,
#define	UI_RKC_CONNECTED  ev_UIRkConnect
	
	/************************************************************************/
	/** 已断开
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkDisconnected,
#define UI_RKC_DISCONNECTED	 ev_UIRkDisconnected

    /************************************************************************/
	/** 重启
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkReBoot,
#define UI_RKC_REBOOT	 ev_UIRkReBoot

    /************************************************************************/
	/** 恢复出厂设置
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkRestore,
#define UI_RKC_RESTONE	 ev_UIRkRestore

    /************************************************************************/
	/** 刷新搜索列表
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkDevReflesh,
#define UI_RKC_RKDEV_REFLESH    ev_UIRkDevReflesh

    /************************************************************************/
	/** 搜索包发送完毕
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UISearchFinish,
#define UI_RKC_SEARCH_FINISH    ev_UISearchFinish

     /************************************************************************/
	/** 刷新工作模式界面
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIWorkModeReflesh,
#define UI_RKC_WORKMODE_REFLESH    ev_UIWorkModeReflesh

    /************************************************************************/
	/** 工作模式修改反馈
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIWorkModeChange,
#define UI_RKC_WORKMODE_CHANGE    ev_UIWorkModeChange

    /************************************************************************/
	/** IP校验反馈
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIIPChecking,
#define UI_RKC_IP_CHECK    ev_UIIPChecking

    /************************************************************************/
	/** 刷新网络配置界面
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UINetWorkReflesh,
#define UI_RKC_NETWORK_REFLESH    ev_UINetWorkReflesh

    /************************************************************************/
	/** 网络配置修改反馈
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UINetWorkChange,
#define UI_RKC_NETWORK_CHANGE    ev_UINetWorkChange

	/************************************************************************/
	/** 修改密码反馈
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkModifyPassword,
#define UI_RKC_MODIFY_PASSWORD    ev_UIRkModifyPassword

    /************************************************************************/
	/** 功耗电源刷新
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIPowerFlesh,
#define UI_RKC_POWER_FLESH    ev_UIPowerFlesh

    /************************************************************************/
	/** 升级更新回复
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkUpdateFirstAck,
#define UI_RKC_UPDATE_FIRST_ACK    ev_UIRkUpdateFirstAck

    /************************************************************************/
	/** 升级更新回复notify
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkUpdateFirstNty,
#define UI_RKC_UPDATE_FIRST_NTY    ev_UIRkUpdateFirstNty

    /************************************************************************/
	/** 升级更新回复notify
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkUpdateSecondNty,
#define UI_RKC_UPDATE_SECOND_NTY    ev_UIRkUpdateSecondNty

    /************************************************************************/
	/** 调试模式刷新
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIDebugModeFlesh,
#define UI_RKC_DEBUGMODE_FLESH    ev_UIDebugModeFlesh

    /************************************************************************/
	/** 调试模式修改反馈
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIDebugModeChange,
#define UI_RKC_DEBUGMODE_CHANGE    ev_UIDebugModeChange

    ev_UIRkcEnd,
#define	UI_RKC_MSG_END   ev_UIRkcEnd

};

#endif 
