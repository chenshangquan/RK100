#pragma once
#include "kdvtype.h"
#include "rkconst.h"
#include "crkmessage.h"
#include <stdio.h>  
#include <winsock2.h>
#include <queue>

#pragma comment(lib,"ws2_32.lib")  

//消息队列定义
class CRkcScoketMsgQueue
{
public:
    CRkcScoketMsgQueue(){}
    ~CRkcScoketMsgQueue(){}
    // 将一条消息压入队列中
    void PushMsg(CRkMessage const pMsg)
    {
        m_queRkMsg.push(pMsg);
    }
    // 从队列中取出一条消息
    void PopMsg(CRkMessage &cOutQue)
    {
        cOutQue = m_queRkMsg.front();
        m_queRkMsg.pop();
    }
    // 从队列中弹出一条消息
    void Pop() 
    { 
        m_queRkMsg.pop(); 
    }
    // 队列是否为空
    BOOL IsEmpty()
    {
        return m_queRkMsg.empty();
    }
    // 清空队列
    void Clear()
    {
        while (!m_queRkMsg.empty()) 
        {
            m_queRkMsg.pop();
        }
    }
private:
    std::queue<CRkMessage> m_queRkMsg;
};

class CSocketManager
{
public:

    CSocketManager();
    ~CSocketManager();

    //得到全局的Manager变量
    static CSocketManager* m_pSocketManager; 
    static CSocketManager* GetSocketManager(); 

    void setSocketIP(char* pchbuf);

    void SetSocketPort(u32 dwPort);

    u8 OpenSocket();

    void CloseSocket();

    bool IsSocket();

    void SendDataPack(CRkMessage rkmsg);

    void SendDataPack();

    void RecvDataPack();

    //心跳包相关
    void StartHeartBeat();//启动心跳
    void StopHeartBeat();//停止心跳

public:
    CRkcScoketMsgQueue          m_RkcMsgQueue;  //等待发送的消息队列
    u32                         m_evWaitMsg;    //等待回复的消息

    static bool                 m_bIsSocketOpen;
protected:
    CRITICAL_SECTION            m_csMsgLock;    //消息发送临界锁
private:

    SOCKET  m_sclient;
    s8      m_achIP[MAX_IP_LENGTH];
    u32     m_dwPort;
};

#define SOCKETWORK CSocketManager::GetSocketManager()   