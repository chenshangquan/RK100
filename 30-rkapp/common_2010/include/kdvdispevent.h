#ifndef __DISPEVENT_H__
#define __DISPEVENT_H__

#include "kdvtype.h"
//#include "kdvsys.h"
#include <map>
#include "nmscommon.h"
#include "crkmessage.h"
 
using namespace std;

#define TYPE_CMESSAGE  0         // 一般的CMessage消息
#define TYPE_TPMSG     1         // 收发的消息为CTPMSG ,需要进行消息类型的转换

//////////////////////////////////////////////////////////////////////////
// 各接口基类，主要用于分发消息
class CKdvDispEvent
{
public:
    typedef void(CKdvDispEvent::*DISPEVENT_PFUN)(const CMessage & cMsg);
public:
    CKdvDispEvent();
    virtual ~CKdvDispEvent();
    // 判断一消息是否在本类中注册过
    BOOL HasRegEvent(u16 wEvent) const;
    // 分发消息，引起相对应的类的函数的调用，各子类完成自已的调用
    virtual void DispEvent(const CMessage &cMsg) = 0;
    // 消息超时的响应
    virtual void OnTimeOut(u16 wEvent) = 0;
    // 得到通知窗口句柄
    HWND GetNotifyWnd() { return m_hWnd; }
    // 设定通知窗口句柄
    void SetNotifyWnd(HWND hWnd) { m_hWnd = hWnd; }
protected:
    // 将一个消息和其处理函数注册进来
    void RegDispFunPointer(u16 wEvent, DISPEVENT_PFUN pFun);
    // 清空掉所有注册的信息
    void ClearDisp();
    // 向注册的界面窗口发送指定的消息
    BOOL PostEvent(u32 dwEvent, WPARAM wParam = 0, LPARAM lParam = 0);
protected:
	// 4.0 修改为只是用事件的Id
    map<u16, DISPEVENT_PFUN> m_mappFun;
    HWND        m_hWnd;         // 消息发送界面的窗口句柄
};
//注册消息映射
#if _MSC_VER <= 1200
#define REG_PFUN(event, fun)        \
    RegDispFunPointer(event, (void (CKdvDispEvent::*)(const CMessage &cMsg))fun);
#else
//支持VS2010
#define REG_PFUN(event, fun)        \
	RegDispFunPointer(event, (void (CKdvDispEvent::*)(const CMessage &cMsg))&fun);
#endif

//分发消息映射
#define DISP_FUN(clsName, cMsg)                                 \
	if(m_mappFun.find(cMsg.event) != m_mappFun.end())			\
	{															\
	   (this->*(void(clsName::*)(const CMessage &cMsg))(m_mappFun[cMsg.event]))(cMsg);	\
	}
#endif