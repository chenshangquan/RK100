/*=======================================================================
模块名      : RKC控制台
文件名      : rckmsgdriver.h
相关文件    : 
文件实现功能: RCK消息驱动器
作者        : 叶良平
-------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容

=======================================================================*/
#ifndef RKCMSGDRIVER_H
#define RKCMSGDRIVER_H

#include <vector>
#include "kdvdispevent.h"
#include "ospmsg.h"
#include "eventoutrkcentre.h"
#include "crkmessage.h"

#define     AID_RKC_APP     100

class CRkcMsgDriver
{
public:
    CRkcMsgDriver();
    ~CRkcMsgDriver();

    // 得到发送消息的指针
    COspMsg* GetOspMsgPtr(BOOL32 bClear = TRUE);
    // 注册一个处理消息的类的指针
    void RegHandler(CKdvDispEvent* const pDispEvnet);
    // 发送osp消息
    virtual u16 PostMsg(u32 dwType = TYPE_CMESSAGE);

public:
    static CRkcMsgDriver *s_pMsgDriver;

    // 响应WM_OSPMESSAGECOMING消息
    void OnOspMessageComing(WPARAM wParam, LPARAM lParam);

protected:
    COspMsg m_tOspMsg;                      //osp传送消息
private:
    void MappingEventName();

    vector<CKdvDispEvent*> m_vpDispEvent;   // 消息分发表

};


#endif //RKCMSGDRIVER_H
