#pragma once

#ifndef _EVRKCLIB_20180920_H_
#define _EVRKCLIB_20180920_H_



//rkcLib����Ϣ����
enum EmUiRkcMsg
{

#define UI_RKC_MSG_BEGIN  	2000 + 0x1 

	/************************************************************************/
	/** ���� 
	wparam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkConnect	= UI_RKC_MSG_BEGIN,
#define	UI_RKC_CONNECTED  ev_UIRkConnect
	
	/************************************************************************/
	/** �ѶϿ�
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkDisconnected,
#define UI_RKC_DISCONNECTED	 ev_UIRkDisconnected

    /************************************************************************/
	/** ����
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkReBoot,
#define UI_RKC_REBOOT	 ev_UIRkReBoot

    /************************************************************************/
	/** �ָ���������
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkRestore,
#define UI_RKC_RESTONE	 ev_UIRkRestore

    /************************************************************************/
	/** ˢ�������б�
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkDevReflesh,
#define UI_RKC_RKDEV_REFLESH    ev_UIRkDevReflesh

    /************************************************************************/
	/** �������������
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UISearchFinish,
#define UI_RKC_SEARCH_FINISH    ev_UISearchFinish

     /************************************************************************/
	/** ˢ�¹���ģʽ����
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIWorkModeReflesh,
#define UI_RKC_WORKMODE_REFLESH    ev_UIWorkModeReflesh

    /************************************************************************/
	/** ����ģʽ�޸ķ���
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIWorkModeChange,
#define UI_RKC_WORKMODE_CHANGE    ev_UIWorkModeChange

    /************************************************************************/
	/** IPУ�鷴��
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIIPChecking,
#define UI_RKC_IP_CHECK    ev_UIIPChecking

    /************************************************************************/
	/** ˢ���������ý���
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UINetWorkReflesh,
#define UI_RKC_NETWORK_REFLESH    ev_UINetWorkReflesh

    /************************************************************************/
	/** ���������޸ķ���
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UINetWorkChange,
#define UI_RKC_NETWORK_CHANGE    ev_UINetWorkChange

	/************************************************************************/
	/** �޸����뷴��
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkModifyPassword,
#define UI_RKC_MODIFY_PASSWORD    ev_UIRkModifyPassword

    /************************************************************************/
	/** ���ĵ�Դˢ��
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIPowerFlesh,
#define UI_RKC_POWER_FLESH    ev_UIPowerFlesh

    /************************************************************************/
	/** �������»ظ�
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkUpdateFirstAck,
#define UI_RKC_UPDATE_FIRST_ACK    ev_UIRkUpdateFirstAck

    /************************************************************************/
	/** �������»ظ�notify
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkUpdateFirstNty,
#define UI_RKC_UPDATE_FIRST_NTY    ev_UIRkUpdateFirstNty

    /************************************************************************/
	/** �������»ظ�notify
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIRkUpdateSecondNty,
#define UI_RKC_UPDATE_SECOND_NTY    ev_UIRkUpdateSecondNty

    /************************************************************************/
	/** ����ģʽˢ��
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIDebugModeFlesh,
#define UI_RKC_DEBUGMODE_FLESH    ev_UIDebugModeFlesh

    /************************************************************************/
	/** ����ģʽ�޸ķ���
	wParam = 0
	lparam = 0*/
	/************************************************************************/
	ev_UIDebugModeChange,
#define UI_RKC_DEBUGMODE_CHANGE    ev_UIDebugModeChange

    ev_UIRkcEnd,
#define	UI_RKC_MSG_END   ev_UIRkcEnd

};

#endif 
