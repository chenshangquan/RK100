//��ק��ض���
#pragma once
#define DUI_MSGTYPE_DRAGSTART			(_T("dragstart"))			//��ʼ��קǰ����				wparam(NULL)						lparam(NULL)
#define DUI_MSGTYPE_DRAGDONE 		(_T("dragdone"))		//�Ϸ���ɺ���				wparam(NULL)						lparam(NULL)
#define DUI_MSGTYPE_DRAGCANCEL		(_T("dragcancel"))		//�Ϸ�ȡ������				wparam(NULL)						lparam(NULL)
#define DUI_MSGTYPE_DRAGENTER		(_T("dragenter"))		//��ק����ؼ�ʱ����			wparam(NULL)						lparam(NULL)
#define DUI_MSGTYPE_DRAGOVER			(_T("dragover"))			//��ק�ڿؼ��Ϸ�ʱ����		wparam(CControlUI* Դ�ؼ�)	lparam(LPPOINT)
#define DUI_MSGTYPE_DRAGLEAVE			(_T("dragleave"))		//��ק���ؼ�ʱ����			wparam(NULL)						lparam(NULL)
#define DUI_MSGTYPE_DRAGDROP			(_T("dragdrop"))		    //�Ϸ��ڿؼ�����			wparam(CControlUI* Դ�ؼ�)	lparam(LPPOINT)
#define DUI_MSGTYPE_DRAGSCROLL		(_T("dragscroll"))		//��ק�Զ�����֮ǰ			wparam(int ģʽ)                   lparam(�����ٶȱ���)


#define DUI_DRAG_FOCUS_TIMER_ID	0xff+1
#define DUI_DRAG_SCROLL_TIMER_ID   0xff+2

//���ֹ���ģʽ
#define  DUI_AUTOSCROLL_SLOW   (int)0
#define DUI_AUTOSCROLL_FAST (int)1
enum EVENTTYPE_DRAG
{
	UIEVENT_DRAG_FIRST = 1000/**/,
	UIEVENT_DRAGENTER,
	UIEVENT_DRAGMOVE,
	UIEVENT_DRAGLEAVE,
};