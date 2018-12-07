/*=======================================================================
模块名      : RCK实例App类
文件名      : rckmsgrecver.h
相关文件    : 
文件实现功能: 声明接收OSP消息所需的CInstance派生类
作者        : 叶良平
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2018/8/29   3.0         叶良平        创建
=======================================================================*/

#include "stdafx.h"
#include <queue>
#include "osp.h"

#define RKC_INSTANCE_COUNT	1	// 接收消息的实例的数目

/************************************************************************/
/*                        消息队列定义                                  */
/************************************************************************/
class CRkcMsgQueue
{
public:
    CRkcMsgQueue();
    ~CRkcMsgQueue();
    // 将一条消息压入队列中
    void PushMsg(CMessage* const pMsg);
    // 从队列中取出一条消息
    void PopMsg(CRkcMsgQueue &cOutQue);
    // 从队列中弹出一条消息
    void Pop() 
    { 
        CMessage *pMsg = &m_queMsg.front(); 
        delete []pMsg->content;
        m_queMsg.pop(); 
    }
    // 队列是否为空
    BOOL IsEmpty();
    // 清空队列
    void Clear();
    // 得到队列最前面元素
    CMessage& Front() { return m_queMsg.front();}
    // 得到队列的大小
    s32 Size() { return m_queMsg.size(); }
private:
    queue<CMessage> m_queMsg;
};

/************************************************************************/
/*                        OSP实例定义                                  */
/************************************************************************/
class CRkcMsgHandler : public CInstance  
{
public:
    CRkcMsgHandler();
    ~CRkcMsgHandler();

    // 实现CInstance中的纯虚方法(线程安全)
    virtual void InstanceEntry(CMessage *const pMsg);
    // 提取缓冲的消息队列(线程安全)
    void PopAllMsg(CRkcMsgQueue &cMsgQue);
    // 清空消息队列
    void ClearQueue();

public:
    static CRkcMsgHandler* GetMsgHandler() { return s_pMsgHandler; }
protected:
    // 消息缓冲队列及其保护关键区
    CRkcMsgQueue       m_cMsgQue;
    CRITICAL_SECTION m_csQueueOspMsg;
private:
    static CRkcMsgHandler *s_pMsgHandler;
};

class CRkcAppBase
{
public:
    CRkcAppBase();
    ~CRkcAppBase();
    // 获取当前连接节点的标识(线程安全)
    u32 GetNodeId(){ return m_dwNodeId;}
    // 设置当前连接节点的标识(线程安全)
    void SetNodeId(u32 dwId) { m_dwNodeId = dwId; }
    //清空消息队列
    void ClearOspMsg();
protected:
    u32                     m_dwNodeId;     // 当前建立连接的节点标识
};

extern zTemplate<CRkcMsgHandler, RKC_INSTANCE_COUNT, CRkcAppBase> g_RckApp;