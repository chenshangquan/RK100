#pragma once
#include "kdvtype.h"
#include "rkconst.h"
#include "crkmessage.h"
#include <stdio.h>  
#include <winsock2.h>
#include <queue>

#pragma comment(lib,"ws2_32.lib")  

//��Ϣ���ж���
class CRkcScoketMsgQueue
{
public:
    CRkcScoketMsgQueue(){}
    ~CRkcScoketMsgQueue(){}
    // ��һ����Ϣѹ�������
    void PushMsg(CRkMessage const pMsg)
    {
        m_queRkMsg.push(pMsg);
    }
    // �Ӷ�����ȡ��һ����Ϣ
    void PopMsg(CRkMessage &cOutQue)
    {
        cOutQue = m_queRkMsg.front();
        m_queRkMsg.pop();
    }
    // �Ӷ����е���һ����Ϣ
    void Pop() 
    { 
        m_queRkMsg.pop(); 
    }
    // �����Ƿ�Ϊ��
    BOOL IsEmpty()
    {
        return m_queRkMsg.empty();
    }
    // ��ն���
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

    //�õ�ȫ�ֵ�Manager����
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

    //���������
    void StartHeartBeat();//��������
    void StopHeartBeat();//ֹͣ����

public:
    CRkcScoketMsgQueue          m_RkcMsgQueue;  //�ȴ����͵���Ϣ����
    u32                         m_evWaitMsg;    //�ȴ��ظ�����Ϣ

    static bool                 m_bIsSocketOpen;
protected:
    CRITICAL_SECTION            m_csMsgLock;    //��Ϣ�����ٽ���
private:

    SOCKET  m_sclient;
    s8      m_achIP[MAX_IP_LENGTH];
    u32     m_dwPort;
};

#define SOCKETWORK CSocketManager::GetSocketManager()   