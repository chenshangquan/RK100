//拖拽相关定义
#pragma once
#define DUI_MSGTYPE_DRAGSTART			(_T("dragstart"))			//开始拖拽前发送				wparam(NULL)						lparam(NULL)
#define DUI_MSGTYPE_DRAGDONE 		(_T("dragdone"))		//拖放完成后发送				wparam(NULL)						lparam(NULL)
#define DUI_MSGTYPE_DRAGCANCEL		(_T("dragcancel"))		//拖放取消后发送				wparam(NULL)						lparam(NULL)
#define DUI_MSGTYPE_DRAGENTER		(_T("dragenter"))		//拖拽进入控件时发送			wparam(NULL)						lparam(NULL)
#define DUI_MSGTYPE_DRAGOVER			(_T("dragover"))			//拖拽在控件上方时发送		wparam(CControlUI* 源控件)	lparam(LPPOINT)
#define DUI_MSGTYPE_DRAGLEAVE			(_T("dragleave"))		//拖拽出控件时发送			wparam(NULL)						lparam(NULL)
#define DUI_MSGTYPE_DRAGDROP			(_T("dragdrop"))		    //拖放在控件后发送			wparam(CControlUI* 源控件)	lparam(LPPOINT)
#define DUI_MSGTYPE_DRAGSCROLL		(_T("dragscroll"))		//拖拽自动滚动之前			wparam(int 模式)                   lparam(滚动速度倍率)


#define DUI_DRAG_FOCUS_TIMER_ID	0xff+1
#define DUI_DRAG_SCROLL_TIMER_ID   0xff+2

//两种滚动模式
#define  DUI_AUTOSCROLL_SLOW   (int)0
#define DUI_AUTOSCROLL_FAST (int)1
enum EVENTTYPE_DRAG
{
	UIEVENT_DRAG_FIRST = 1000/**/,
	UIEVENT_DRAGENTER,
	UIEVENT_DRAGMOVE,
	UIEVENT_DRAGLEAVE,
};