
#include "StdAfx.h"
#include "kdvdispevent.h"

CKdvDispEvent::CKdvDispEvent()
{
    m_hWnd = NULL;
}

CKdvDispEvent::~CKdvDispEvent()
{
    ClearDisp();
}

/*=======================================================================
函 数 名:   RegDispFunPointer
功    能:   将一个消息和其处理函数注册进来
参    数:   u16 wEvent                 [in]要处理的消息
            DISPEVENT_PFUN pFun        [in]处理消息的类函数指针
            u16 wMsgType               [in]接收消息的类型TYPE_CMESSAGE/TYPE_MTMSG
返 回 值:
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/08/23  3.5   李洪强  创建
=======================================================================*/
void CKdvDispEvent::RegDispFunPointer(u16 wEvent, DISPEVENT_PFUN pFun)
{
    m_mappFun[wEvent] = pFun;
}

/*=======================================================================
函 数 名:   HasRegEvent
功    能:   判断一消息是否在本类中注册过
参    数:   u16 wEvent                 [in]要检查的消息
返 回 值:   注册过返回TRUE, 没注册过返回FALSE
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/08/23  3.5   李洪强  创建
=======================================================================*/
BOOL CKdvDispEvent::HasRegEvent(u16 wEvent) const
{
	if (m_mappFun.find(wEvent) != m_mappFun.end())
	{
		return TRUE;
    }
    return FALSE;  
}

/*=======================================================================
函 数 名:   ClearDisp
功    能:   清空掉所有注册的信息
参    数:
返 回 值:
相关消息:
-------------------------------------------------------------------------
修改纪录:
日      期  版本  修改人  修改内容
2004/08/23  3.5   李洪强  创建
=======================================================================*/
void CKdvDispEvent::ClearDisp()
{
    m_mappFun.clear();
}

/*=============================================================================
  函 数 名： PostEvent 向终控目标窗口发送消息
  功    能： 
  算法实现： 
  全局变量： 
  参    数： u32 dwEvent        终端内部定义的事件ID
             WPARAM wParam     
             LPARAM lParam
  返 回 值： BOOL               是否发送成功
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2004/10/13     3.5		王慧琛                  规范化
=============================================================================*/
BOOL CKdvDispEvent::PostEvent(u32 dwEvent, WPARAM wParam, LPARAM lParam)
{
    if(m_hWnd != NULL)
    {
        return ::SendMessage(m_hWnd, dwEvent, wParam, lParam);
    }
    return FALSE;
}