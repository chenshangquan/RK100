#pragma once
#include "threadbase.h"

typedef std::deque<u8*> MsgList;

class CBroadcast : public schlck::CLockObject
{
public:
	CBroadcast();
	~CBroadcast();

	bool Init();
	bool Exit();
	bool IsInit();

	bool SetMsgAckCB(MsgAckCB mCB, u32 dwContext);

	bool PopMessage(u32 &dwSize, u8* pBuffer);
	bool PushMessage(u32 dwSize, u8* pBuffer);

    bool GetLocalAddr(TLocalAddr* atAddr, u32& dwEthCount);                         //��ȡ���ص�ַ

#ifdef WIN32
    bool IsLocalAdapter(char *pAdapterName);										// �ж��Ƿ���������������
#endif // WIN32


	bool SendDevDetectMsg(bool bRefreshAdapter);
    bool SendDevDetectMsgByUnicast(bool bRefreshAdapter, u32 dwStart, u32 dwEnd);//����������

    bool SetDevDetectCtrl(bool bDetect);

    //�㲥��
	bool SendBroadcastPackage(u8* pSrcMacAddr,
		u32 dwLocalIP,
		u16 wMsgID,
		u8* pDstMacAddr = NULL,
		u8* pAuthenBuf = NULL,
		u32 dwMsgBodySize = 0,
		u8* pMsgBodyBuf = NULL);
    //������
    bool SendUnicastPackage(u8* pSrcMacAddr,
        u32 dwDstIP,
        u16 wMsgID,
        u8* pDstMacAddr = NULL,
        u8* pAuthenBuf = NULL,
        u32 dwMsgBodySize = 0,
        u8* pMsgBodyBuf = NULL);
    //����������
    bool SendUnicastDetectPackage( u8* pSrcMacAddr, u32 dwDstIP );

    bool SendNetPrmMsg(u32 dwDstIP, u8* pDstMacAddr, u8* abySecureCode, char* szUser, char* szPwd, TDevNetParam* pDevNetPrm);
    bool SendRebootMsg(u32 dwDstIP, u8* pDstMacAddr, u8* abySecureCode, char* szUser, char* szPwd);

    bool SendUdpMsgPackage(u16 nMsgID,
        u32 dwDstIP = 0,
        u8* pDstMacAddr = NULL,
        u8* pAuthenBuf = NULL,
        u32 dwMsgBodySize = 0,
        u8* pMsgBodyBuf = NULL,
        bool bRefreshAdapter = TRUE);

    static CALLBACKRET STDCALL RecvMessageProc(void* pParam);
    static CALLBACKRET STDCALL SendMessageProc(void* pParam);


    void        closesock(u32 hSock);
protected:
	bool		m_bInited;
	bool		m_bExitRecv;
    bool        m_bDetect;                                              // �Ƿ���ܹ㲥��

	u32			m_dwLocalAdapterCount;                                  // ����������������

    TLocalAddr m_atLoalAddr[32];                                        //  ���ص�ַ����mac��ip��ַ
// 
	MsgList m_cMsgList;
// 	CCriticalSection m_cMsgLock;										// ����m_cMsgList
// 	std::deque<INT> m_aMsgList;

	MsgAckCB m_mAckCB;
	u32 m_dwContext;

	CThreadBase			m_threadRecv;
	CThreadBase			m_threadSend;
};

