#include "stdall.h"
#include "broadcast.h"
#include "md5.h"

#ifdef WIN32
#include <Iphlpapi.h>
#pragma comment(lib,"Iphlpapi.lib") //需要添加Iphlpapi.lib库
#else
#include <stdlib.h>
#include <stdio.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cerrno>
#include <unistd.h>
#endif // WIN32

#ifdef _MSC_VER
#if defined(_WIN64) || defined(WIN64) ||defined (__LP64__) || defined (__64BIT__) || defined (_LP64) || (__WORDSIZE == 64)
#define SOCKHANDLE            unsigned long long
#else
#define SOCKHANDLE            unsigned long
#endif
#else
#define SOCKHANDLE            int
#endif    // _MSC_VER

#ifdef _LINUX_
#define SOCKET_ERROR          (-1)
#define INVALID_SOCKET        (-1)
#endif // _LINUX_

SOCKHANDLE m_bcSocketUnicastDetect;

CBroadcast::CBroadcast()
{
	m_bInited = false;
	m_bExitRecv = false;
}


CBroadcast::~CBroadcast()
{
}

bool CBroadcast::Init()
{
	m_bInited = true;
	m_bExitRecv = false;
    m_bDetect = true;
    m_mAckCB = NULL;

    m_threadRecv.Start(this, RecvMessageProc);
	m_threadSend.Start(this, SendMessageProc);

	return true;
}

bool CBroadcast::Exit()
{
	m_bExitRecv = true;
	m_bInited = false;
	m_mAckCB = NULL;

 	m_threadRecv.Exit();
 	m_threadSend.Exit();

	return true;
}

bool CBroadcast::IsInit()
{
	return m_bInited;
}

bool CBroadcast::SetMsgAckCB(MsgAckCB mCB, u32 dwContext)
{
	m_mAckCB = mCB;
	m_dwContext = dwContext;

	return true;
}

bool CBroadcast::PopMessage(u32 &dwSize, u8* pBuffer)
{
    schlck::CLock lock(m_semhandle);

#ifdef WIN32
    assert(pBuffer != NULL);
#endif // WIN32

	if (m_cMsgList.empty())
	{
		return false;
	}
	else
	{
		u8* pMsgItem = m_cMsgList.front();
		if (!pMsgItem)
		{
			return false;
		}

		m_cMsgList.pop_front();

		u32 dwMsgSize;
		memcpy(&dwMsgSize, pMsgItem, sizeof(u32));

		dwSize = min(dwMsgSize, dwSize);
		memcpy(pBuffer, pMsgItem + sizeof(u32), dwSize);
		delete[] pMsgItem;
	}

	return true;
}

bool CBroadcast::PushMessage(u32 dwSize, u8* pBuffer)
{
    schlck::CLock lock(m_semhandle);

	u8* pMsgItem = new u8[sizeof(u32) + dwSize];
	memcpy(pMsgItem, &dwSize, sizeof(u32));
	memcpy(pMsgItem + sizeof(u32), pBuffer, dwSize);
	m_cMsgList.push_back(pMsgItem);

	return true;
}

#ifdef WIN32
#define RESULT_FAILED       1
#define RESULT_SUCCESS      0
#else
#define RESULT_FAILED       
#define RESULT_SUCCESS      
#endif // WIN32

CALLBACKRET STDCALL CBroadcast::RecvMessageProc(void* pParam)
{
	CBroadcast *pcBroadcast = (CBroadcast*)pParam;

    SOCKHANDLE bcRecvSocket;
	sockaddr_in addrBind;

    bcRecvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == bcRecvSocket)
	{
		printf("MsgProc: Socket error = %s!\n", strerror(errno));
        return RESULT_FAILED;
	}

	// 赋值给两个地址: addrBind用来绑定套接字，addrFrom用来从网络上的广播地址接收消息
	//
    sockaddr_in addrFrom;
	addrBind.sin_family = AF_INET;
	addrBind.sin_addr.s_addr = htonl(INADDR_ANY);
	addrBind.sin_port = htons(DT_PORT);
	addrFrom.sin_family = AF_INET;
	addrFrom.sin_addr.s_addr = INADDR_BROADCAST;
	addrFrom.sin_port = htons(DT_PORT);
#ifdef _LINUX_
    socklen_t nFromlen = sizeof(sockaddr_in);
#else
    s32 nFromlen = sizeof(sockaddr_in);
#endif
	// 使用select设置超时时，需要将socket设置为非阻塞方式
	//
    s32 nRet = 0;
#ifdef WIN32
    u32 nMode = 1;      // 0:阻塞方式
    nRet = ioctlsocket(bcRecvSocket, FIONBIO, (u_long *)&nMode);
#else
    s32 nMode = 1;      // 0:阻塞方式
    nRet = ioctl(bcRecvSocket, FIONBIO, &nMode);
#endif // WIN32

	if ( nRet == SOCKET_ERROR)
	{
        pcBroadcast->closesock(bcRecvSocket);
        printf("set mode error = %s!\n", strerror(errno));
        return RESULT_FAILED;
	}

	// 设置地址复用
	s32 opt = 1;
	// 单播
	if (0 != setsockopt(bcRecvSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)))
	{
        pcBroadcast->closesock(bcRecvSocket);
        printf("set reuse addr error = %s!\n", strerror(errno));
        return RESULT_FAILED;
	}

	// 一个端口只bind一次
	//
    int nRetValue = bind(bcRecvSocket, (sockaddr *)&addrBind, sizeof(sockaddr_in));
	if (nRetValue != 0)
	{
        pcBroadcast->closesock(bcRecvSocket);
        printf("bind error = %s!\n", strerror(errno));
        return RESULT_FAILED;
	}

	char buf[MAXLEN_BCMSG] = { 0 };

    while (!pcBroadcast->m_bExitRecv)
	{
        SCHSLEEP(10);

		// 设置recvfrom阻塞的超时时间: 若1.500秒内未读到数据则阻塞的recvfrom函数返回.
		//
		fd_set fdread;
		FD_ZERO(&fdread);
		FD_SET(bcRecvSocket, &fdread);
		timeval tWaitTime = { 1, 100 };
		int nRetValue = select(bcRecvSocket + 1, &fdread, NULL, NULL, &tWaitTime);

		if (nRetValue > 0)
		{
            int nRecvBytes = recvfrom(bcRecvSocket, buf, MAXLEN_BCMSG, 0, (sockaddr *)&addrFrom, &nFromlen);

			if (nRecvBytes == 0 || nRecvBytes > MAXLEN_BCMSG)
			{
				continue;
			}

			if (nRecvBytes < DT_LEN_MAGIC + sizeof(TDTHeader))
			{
				continue;
			}

			// buf的格式:DT_MAGIC+TDTHeader+TDTDevInfo [8/6/2009 caogaijian]
			if (strncmp(buf, "NDT1", DT_LEN_MAGIC) == 0
				|| strncmp(buf, "NDT2", DT_LEN_MAGIC) == 0)
			{   // 先根据Msg ID和DT_MAGIC过滤掉部分消息
				TDTHeader tHeader;
				memcpy(&tHeader, buf + DT_LEN_MAGIC, sizeof(tHeader));
				tHeader.wMsgID = ntohs(tHeader.wMsgID);

				switch (tHeader.wMsgID)
				{
				case NC_DEV_TRACK_REQ_CAST:
				case DEV_NC_TRACK_ACK_CAST:
                case DEV_NC_MODADDR_ACK_CAST:
				{
					pcBroadcast->PushMessage((u32)nRecvBytes, (u8*)buf);
				}
				break;
				}
			}

            memset(buf, 0, MAXLEN_BCMSG);
		}
	}

    pcBroadcast->closesock(bcRecvSocket);
	//pcBroadcast->m_pcRecvThread = NULL;

	//TRACE("接收线程正常退出  \n");
    return RESULT_SUCCESS;
}


CALLBACKRET STDCALL CBroadcast::SendMessageProc(void* pParam)
{
	CBroadcast* pcBroadcast = (CBroadcast*)pParam;
	while (!pcBroadcast->m_bExitRecv)
	{
        SCHSLEEP(10);
		if (pcBroadcast->m_cMsgList.empty())
		{
			continue;
		}

		u8 pMsgBuf[MAXLEN_BCMSG] = { 0 };
		u32 dwMsgSize = MAXLEN_BCMSG;
        while (!pcBroadcast->m_bExitRecv && pcBroadcast->PopMessage(dwMsgSize, pMsgBuf))
		{
            SCHSLEEP(10);
			TDTHeader tHeader;
			memcpy(&tHeader, pMsgBuf + DT_LEN_MAGIC, sizeof(tHeader));
			u8* pBufTemp = pMsgBuf + DT_LEN_MAGIC + sizeof(TDTHeader);
			tHeader.wMsgID = ntohs(tHeader.wMsgID);
			switch (tHeader.wMsgID)
			{
			case DEV_NC_TRACK_ACK_CAST:
			{
				u16 uMsgSize = sizeof(TDTHeader) + DT_LEN_MAGIC;

				TDevItem tDevItem;

				memcpy(&tDevItem.tDevMacAddr, &tHeader.tMacSrc, DT_LEN_MACADDR);

				memcpy(&tDevItem.tDevInfo, pBufTemp, sizeof(TDTDevInfo));
				pBufTemp += sizeof(TDTDevInfo);
				uMsgSize += sizeof(TDTDevInfo);
				// 接收到数据后马上转为本地序,因此本地处理的均是本地序数据
				NetOrder2LocalOrder(tDevItem.tDevInfo);

				if (tDevItem.tDevInfo.byDevIdMask)			// 0-不携带 1-携带 2-utf编码
				{
					memcpy(&tDevItem.tDevID.achDevName, pBufTemp, DT_LEN_NAME);
					pBufTemp += DT_LEN_NAME + 1;
					uMsgSize += DT_LEN_NAME + 1;
					memcpy(&tDevItem.tDevID.achDevSerial, pBufTemp, DT_LEN_SERIAL);
					pBufTemp += DT_LEN_SERIAL + 1;
					uMsgSize += DT_LEN_SERIAL + 1;
				}
				else
				{   // 获取不到别名则显示---
					sprintf(tDevItem.tDevID.achDevName, "%s", "---");
				}

				if (tDevItem.tDevInfo.byDevTypeMask == 1)
				{
					memcpy(&tDevItem.tDevID.achDevType, pBufTemp, DT_LEN_NAME);
					pBufTemp += DT_LEN_NAME + 1;
					uMsgSize += DT_LEN_NAME + 1;
				}
				else
				{
					std::string szArray = BrdID2DeviceType(tDevItem.tDevInfo.dwBrdID);
                    strcpy((char*)tDevItem.tDevID.achDevType, szArray.c_str());
				}

				if (tDevItem.tDevInfo.byMask3 == 1)
				{
					memcpy(&tDevItem.tDevID.achDevUpdate, pBufTemp, DT_LEN_UPDATE_INFO);
					pBufTemp += DT_LEN_UPDATE_INFO + 1;
					uMsgSize += DT_LEN_UPDATE_INFO + 1;
				}
				if (dwMsgSize >= uMsgSize + sizeof(u16) + DT_LEN_SOFT_VER)
				{
					u16 wTag = 0;
					memcpy(&wTag, pBufTemp, sizeof(u16));

					wTag = htons(wTag);
					tDevItem.wTag = wTag;

					// 						if (tHeader.tMacSrc.abyMac[0] == 0x22
					// 							&&tHeader.tMacSrc.abyMac[1] == 0x1F
					// 							&&tHeader.tMacSrc.abyMac[2] == 0xE7
					// 							&&tHeader.tMacSrc.abyMac[3] == 0x39
					// 							&&tHeader.tMacSrc.abyMac[4] == 0xB2
					// 							&&tHeader.tMacSrc.abyMac[5] == 0x9F)
					// 						{
					// 							int a = 0;
					// 							a++;
					// 						}

					if (wTag == DT_B2_EXT_TAG)
					{
						pBufTemp += sizeof(wTag);
						memcpy(&tDevItem.tDevEx.achDevSoftVersion, pBufTemp, DT_LEN_SOFT_VER);
					}
					else if (wTag == DT_V7_EXT_TAG)					// 如果携带该字段，则表示会携带DEV VERSION、DEVICE STATE以及AUTH NONCE
					{
						pBufTemp += sizeof(wTag);

						memcpy(&tDevItem.tDevEx.achDevSoftVersion, pBufTemp, DT_LEN_SOFT_VER);
						pBufTemp += DT_LEN_SOFT_VER;

						// 激活状态
						memcpy(&tDevItem.tDevEx.wActiveState, pBufTemp, sizeof(u16));
						tDevItem.tDevEx.wActiveState = htons(tDevItem.tDevEx.wActiveState);
						pBufTemp += sizeof(u16);

						// 安全码
						memcpy(&tDevItem.tDevEx.achSecureCode, pBufTemp, DT_LEN_SECURE_CODE);
						pBufTemp += DT_LEN_SECURE_CODE;

						// 协议版本号
						memcpy(&tDevItem.tDevEx.achProTocolVer, pBufTemp, DT_LEN_PROTO_VER);
						pBufTemp += DT_LEN_PROTO_VER;

// 						// 版本号为1.2.XX 或以下的 直接过滤掉消息,不处理
// 						int verCur[4] = { 0 };
// 						sprintf(tDevItem.tDevEx.achProTocolVer, "%d.%d.%d.%d", verCur[0], verCur[1], verCur[2], verCur[3]);
// 						if (verCur[0] == 1 && verCur[1] < 3)
// 						{
// 							break;
// 						}

						// 安全邮箱
						memcpy(&tDevItem.tDevEx.achSecureMail, pBufTemp, DT_LEN_SECURE_MAIL);
						pBufTemp += DT_LEN_SECURE_MAIL;
					}
				}

				if (tDevItem.wTag != DT_V7_EXT_TAG)
				{
					// v5设备认为激活状态是已激活
					tDevItem.tDevEx.wActiveState = 0x0001;
				}

				tDevItem.bNDT2 = strncmp((char*)pMsgBuf, "NDT2", DT_LEN_MAGIC) == 0 ? true : false;

				if (pcBroadcast->m_mAckCB && pcBroadcast->m_bDetect)
				{
					pcBroadcast->m_mAckCB(DEV_NC_TRACK_ACK_CAST, (void*)&tDevItem, (u32)pcBroadcast->m_dwContext);
				}
			}
			break;
            case DEV_NC_MODADDR_ACK_CAST:   //修改设备地址应答
            {
                u32 dwErrorCode = 0;
                memcpy(&dwErrorCode, pBufTemp, sizeof(u32));

                dwErrorCode = ntohl(dwErrorCode);
                TDevRetInfo tDevRetInfo;
                memcpy(&tDevRetInfo.tDevMacAddr, &tHeader.tMacSrc, DT_LEN_MACADDR);
                tDevRetInfo.dwErrorCode = dwErrorCode;
                printf("receive message id = 0x%04x, mac = %02x:%02x:%02x:%02x:%02x:%02x\n",
                    tHeader.wMsgID, tDevRetInfo.tDevMacAddr.abyMac[0], tDevRetInfo.tDevMacAddr.abyMac[1], tDevRetInfo.tDevMacAddr.abyMac[2],
                    tDevRetInfo.tDevMacAddr.abyMac[3], tDevRetInfo.tDevMacAddr.abyMac[4], tDevRetInfo.tDevMacAddr.abyMac[5]);

                if (pcBroadcast->m_mAckCB)
                {
                    pcBroadcast->m_mAckCB(tHeader.wMsgID, (void*)&tDevRetInfo, (u32)pcBroadcast->m_dwContext);
                }
            }
            break;
			default: 
                break;
			}

			dwMsgSize = MAXLEN_BCMSG;
			memset(pMsgBuf, 0, MAXLEN_BCMSG);
		}
		//Sleep(30);
	}

	return RESULT_SUCCESS;
}

void CBroadcast::closesock(u32 hSock)
{
    if (hSock == INVALID_SOCKET)
    {
        return;
    }
#ifdef WIN32
    closesocket(hSock);
#else
    close(hSock);
#endif // WIN32
    hSock = INVALID_SOCKET;
}

bool CBroadcast::SendBroadcastPackage(u8* pSrcMacAddr,
	u32 dwLocalIP,
	u16 wMsgID,
	u8* pDstMacAddr/* = NULL*/,
	u8* pAuthenBuf/* = NULL*/,
	u32 dwMsgBodySize/* = 0*/,
	u8* pMsgBodyBuf/* = NULL*/)
{
	if (wMsgID != NC_DEV_TRACK_REQ_CAST)
	{
		char szTemp[DT_LEN_MACADDR + 1];
		memset(&szTemp, 0, sizeof(szTemp));

		if (pDstMacAddr == NULL || memcmp(pDstMacAddr, szTemp, DT_LEN_MACADDR) == 0)
		{
			return false;
		}
	}

	bool bAuthen = pAuthenBuf ? true : false;							// 是否有鉴权, TRUE-是，FALSE-否
	int nMsgLen = bAuthen ? sizeof(TDTHeaderAuthen) : sizeof(TDTHeader);	// 
	nMsgLen = nMsgLen + DT_LEN_MAGIC + dwMsgBodySize + DT_LEN_PROTO_VER; 						// buf长度

	u8* pMsgBuf = new u8[nMsgLen];										// 申请buf 
	memset(pMsgBuf, 0, nMsgLen);
	memcpy(pMsgBuf, "NDT1", DT_LEN_MAGIC);									// 固定标识
	u8* pPoint = pMsgBuf + DT_LEN_MAGIC;			    					// 指针,记录位置

	if (!bAuthen)														// 是否有鉴权
	{
		// 无鉴权
		TDTHeader tDTHeader;											// 不加鉴权的消息头
		memset(&tDTHeader, 0, sizeof(tDTHeader));
		memcpy(&tDTHeader.tMacSrc, pSrcMacAddr, DT_LEN_MACADDR);			// 主机网卡
		if (pDstMacAddr != NULL)
		{
			memcpy(&tDTHeader.tMacDst, pDstMacAddr, DT_LEN_MACADDR);		// 设备网卡
		}

		tDTHeader.wMsgID = htons(wMsgID);								// 消息ID
		memcpy(pPoint, &tDTHeader, sizeof(tDTHeader));					// 将TDTHeader拷到buf里,tDTHeader栈空间释放
		pPoint += sizeof(tDTHeader);									// 指针偏移sizeof(tDTHeader)字节
	}
	else
	{
		// 有鉴权
		TDTHeaderAuthen tDTHeader;										// 加鉴权的消息头
		memset(&tDTHeader, 0, sizeof(tDTHeader));
		memcpy(&tDTHeader.tMacSrc, pSrcMacAddr, DT_LEN_MACADDR);			// 主机网卡
		if (pDstMacAddr != NULL)
		{
			memcpy(&tDTHeader.tMacDst, pDstMacAddr, DT_LEN_MACADDR);		// 设备网卡
		}

		tDTHeader.wMsgID = htons(wMsgID);								// 消息ID
		tDTHeader.wAuthen = htons(DT_AUTHENTICATION_ID);				// 鉴权ID0x3210
		memcpy(&tDTHeader.tAuthen, pAuthenBuf, sizeof(TDAuthen));		// 鉴权消息
		memcpy(pPoint, &tDTHeader, sizeof(tDTHeader));					// 将TDTHeader拷到buf里,tDTHeader栈空间释放
		pPoint += sizeof(tDTHeader);									// 指针偏移sizeof(tDTHeader)字节
	}

	// 消息内容
	if (dwMsgBodySize > 0 && pMsgBodyBuf != NULL)
	{
		memcpy(pPoint, pMsgBodyBuf, dwMsgBodySize);
		pPoint += dwMsgBodySize;
	}

	memcpy(pPoint, DT_PROTO_VER, DT_LEN_PROTO_VER);
	pPoint += DT_LEN_PROTO_VER;

	// 
	// 创建SOCKET,并设置该套接字为广播类型
	// 
    SOCKHANDLE bcSocket;
	bcSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (INVALID_SOCKET == bcSocket)
	{
		delete[] pMsgBuf;
		pMsgBuf = NULL;
        printf("socket init error = %s(errno = %d)\n", strerror(errno), errno);
		return false;
	}

	s32 opt = true;
	// 单播 opt = FALSE
	int nRetValue = setsockopt(bcSocket, SOL_SOCKET, SO_BROADCAST, (char*)&opt, sizeof(opt));
	if (nRetValue != 0)
	{
		delete[] pMsgBuf;
		pMsgBuf = NULL;
        printf("socket set broadcast error = %s(errno = %d)\n", strerror(errno), errno);
		return false;
	}

	sockaddr_in	addrClient = { 0 };
	addrClient.sin_family = AF_INET;
    addrClient.sin_addr.s_addr = dwLocalIP;
    //广播是绑定IP，其他不绑定，否则单播时无法收到应答包（多网卡情况）
    if (wMsgID != NC_DEV_TRACK_REQ_CAST)
    {
        addrClient.sin_addr.s_addr = 0;
    }
	addrClient.sin_port = 0;	/// 0 表示由系统自动分配端口号
	if (0 != bind(bcSocket, (sockaddr*)&addrClient, sizeof(addrClient)))
	{
        printf("bind error = %s(errno = %d)\n", strerror(errno), errno);
	}

    sockaddr_in addrto;
	addrto.sin_family = AF_INET;
	addrto.sin_addr.s_addr = INADDR_BROADCAST;	// 广播给所有机器
	addrto.sin_port = htons(DT_PORT);

	nRetValue = sendto(bcSocket, (const s8*)pMsgBuf, nMsgLen, 0, (sockaddr*)&addrto, sizeof(addrto));

    if (nRetValue < 0)
    {
        printf("socket sendto error = %s(errno = %d)\n", strerror(errno), errno);
    }
	delete[] pMsgBuf;
	pMsgBuf = NULL;

    closesock(bcSocket);

	return true;
}

bool CBroadcast::SendUnicastPackage(u8* pSrcMacAddr, u32 dwDstIP, u16 wMsgID, u8* pDstMacAddr /*= NULL*/, u8* pAuthenBuf /*= NULL*/, u32 dwMsgBodySize /*= 0*/, u8* pMsgBodyBuf /*= NULL*/)
{
    if (wMsgID != NC_DEV_TRACK_REQ_CAST)
    {
        char szTemp[DT_LEN_MACADDR + 1];
        memset(&szTemp, 0, sizeof(szTemp));

        if (pDstMacAddr == NULL || memcmp(pDstMacAddr, szTemp, DT_LEN_MACADDR) == 0)
        {
            printf("--------------[Line:%d]send unicast package dest mac addr is invalid!\n", __LINE__);
            return false;
        }
    }

    bool bAuthen = pAuthenBuf ? true : false;                               // 是否有鉴权， true-是
    s32 nMsgLen = bAuthen ? sizeof(TDTHeaderAuthen) : sizeof(TDTHeader);    
    nMsgLen = nMsgLen + DT_LEN_MACADDR + dwMsgBodySize + DT_LEN_PROTO_VER;

    u8* pMsgBuf = new u8[nMsgLen];
    memset(pMsgBuf, 0, nMsgLen);
    memcpy(pMsgBuf, "NDT1", DT_LEN_MAGIC);
    u8* pPoint = pMsgBuf + DT_LEN_MAGIC;
    if (!bAuthen)
    {
        //无鉴权
        TDTHeader tDTHeader;
        memset(&tDTHeader, 0, sizeof(tDTHeader));
        memcpy(&tDTHeader.tMacSrc, pSrcMacAddr, DT_LEN_MACADDR);
        if (pDstMacAddr)
        {
            memcpy(&tDTHeader.tMacDst, pDstMacAddr, DT_LEN_MACADDR);
        }

        s8 szDstMac[256] = { 0 };
        s8 szSrcMac[256] = { 0 };

        sprintf(szDstMac, "%02x-%02x-%02x-%02x-%02x-%02x", *pDstMacAddr, *(pDstMacAddr + 1), *(pDstMacAddr + 2), *(pDstMacAddr + 3),
            *(pDstMacAddr + 4), *(pDstMacAddr + 5));
        sprintf(szSrcMac, "%02x-%02x-%02x-%02x-%02x-%02x", *pSrcMacAddr, *(pSrcMacAddr + 1), *(pSrcMacAddr + 2), *(pSrcMacAddr + 3),
            *(pSrcMacAddr + 4), *(pSrcMacAddr + 5));
  
        printf("--------------[Line:%d]dest mac = %s, src mac = %s!\n", __LINE__, szDstMac, szSrcMac);

        tDTHeader.wMsgID = htons(wMsgID);
        memcpy(pPoint, &tDTHeader, sizeof(tDTHeader));
        pPoint += sizeof(tDTHeader);
    }
    else
    {
        //有鉴权
        TDTHeaderAuthen tDTHeader;
        memset(&tDTHeader, 0, sizeof(tDTHeader));
        memcpy(&tDTHeader.tMacSrc, pSrcMacAddr, DT_LEN_MACADDR);			// 主机网卡
        if (pDstMacAddr != NULL)
        {
            memcpy(&tDTHeader.tMacDst, pDstMacAddr, DT_LEN_MACADDR);		// 设备网卡
        }

        tDTHeader.wMsgID = htons(wMsgID);								// 消息ID
        tDTHeader.wAuthen = htons(DT_AUTHENTICATION_ID);				// 鉴权ID0x3210
        memcpy(&tDTHeader.tAuthen, pAuthenBuf, sizeof(TDAuthen));				// 鉴权消息
        memcpy(pPoint, &tDTHeader, sizeof(tDTHeader));					// 将TDTHeader拷到buf里,tDTHeader栈空间释放
        pPoint += sizeof(tDTHeader);									// 指针偏移sizeof(tDTHeader)字节
    }

    // 消息内容
    if (dwMsgBodySize > 0 && pMsgBodyBuf != NULL)
    {
        memcpy(pPoint, pMsgBodyBuf, dwMsgBodySize);
        pPoint += dwMsgBodySize;
    }

    memcpy(pPoint, DT_PROTO_VER, DT_LEN_PROTO_VER);
    pPoint += DT_LEN_PROTO_VER;

    // 
    // 创建SOCKET,并设置该套接字为组播类型
    // 
    SOCKHANDLE bcSocket;
    bcSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);;
    if (INVALID_SOCKET == bcSocket)
    {
        delete[] pMsgBuf;
        pMsgBuf = NULL;
        return FALSE;
    }

    sockaddr_in addrto;
    addrto.sin_family = AF_INET;
    addrto.sin_addr.s_addr = dwDstIP;									// 单播地址
    addrto.sin_port = htons(DT_PORT);
    printf("----------[Line=%d] send to ip = %s\n", __LINE__, inet_ntoa(addrto.sin_addr));
    int nRetValue = sendto(bcSocket, (const s8*)pMsgBuf, nMsgLen, 0, (sockaddr*)&addrto, sizeof(addrto));
    delete[] pMsgBuf;
    pMsgBuf = NULL;

    closesock(bcSocket);
    return true;
}

bool CBroadcast::SendUnicastDetectPackage( u8* pSrcMacAddr, u32 dwDstIP)
{
    s32 nMsgLen = sizeof(TDTHeader);    
    nMsgLen = nMsgLen + DT_LEN_MACADDR + DT_LEN_PROTO_VER;

    u8* pMsgBuf = new u8[nMsgLen];
    memset(pMsgBuf, 0, nMsgLen);
    memcpy(pMsgBuf, "NDT1", DT_LEN_MAGIC);
    u8* pPoint = pMsgBuf + DT_LEN_MAGIC;

    //无鉴权
    TDTHeader tDTHeader;
    memset(&tDTHeader, 0, sizeof(tDTHeader));
    memcpy(&tDTHeader.tMacSrc, pSrcMacAddr, DT_LEN_MACADDR);

    tDTHeader.wMsgID = htons(NC_DEV_TRACK_REQ_CAST);
    memcpy(pPoint, &tDTHeader, sizeof(tDTHeader));
    pPoint += sizeof(tDTHeader);

    // 
    // 创建SOCKET,并设置该套接字为组播类型
    // 
//     SOCKHANDLE bcSocket;
//     bcSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);;
//     if (INVALID_SOCKET == bcSocket)
//     {
//         delete[] pMsgBuf;
//         pMsgBuf = NULL;
//         return FALSE;
//     }

    sockaddr_in addrto;
    addrto.sin_family = AF_INET;
    addrto.sin_addr.s_addr = dwDstIP;									// 单播地址
    addrto.sin_port = htons(DT_PORT);
    printf("----------[Line=%d] send to ip = %s\n", __LINE__, inet_ntoa(addrto.sin_addr));
    int nRetValue = sendto(m_bcSocketUnicastDetect, (const s8*)pMsgBuf, nMsgLen, 0, (sockaddr*)&addrto, sizeof(addrto));
    delete[] pMsgBuf;
    pMsgBuf = NULL;

//    closesock(bcSocket);
    return true;
}

bool CBroadcast::SendNetPrmMsg(u32 dwDstIP, u8* pDstMacAddr, u8* abySecureCode, char* szUser, char* szPwd, TDevNetParam* pDevNetPrm)
{
    TDAuthen tAuthen;
    u8* pAuthenBuf = NULL;
    if (szUser != NULL && szPwd != NULL)
    {
        CMD5::MD5Authen(szUser, szPwd, abySecureCode, &tAuthen);
        pAuthenBuf = (u8*)&tAuthen;
    }

    printf("---------[Line=%d]dest mac: %02x-%02x-%02x-%02x-%02x-%02x \n", __LINE__,
        *pDstMacAddr, *(pDstMacAddr + 1), *(pDstMacAddr + 2),
        *(pDstMacAddr + 3), *(pDstMacAddr + 4), *(pDstMacAddr + 5));

    //转网络序
    pDevNetPrm->dwNetMask = htonl(pDevNetPrm->dwNetMask);

    pDevNetPrm->tAddr.dwIpaddr = htonl(pDevNetPrm->tAddr.dwIpaddr);
    pDevNetPrm->tAddr.dwGateWay = htonl(pDevNetPrm->tAddr.dwGateWay);
    pDevNetPrm->tAddr.dwNetmask = htonl(pDevNetPrm->tAddr.dwNetmask);

    pDevNetPrm->tRegPlat.dwRegIP = htonl(pDevNetPrm->tRegPlat.dwRegIP);
    pDevNetPrm->tRegPlat.wRegPort = htons(pDevNetPrm->tRegPlat.wRegPort);
    
    return SendUdpMsgPackage(NC_DEV_MODADDR_REQ_CAST, htonl(dwDstIP), pDstMacAddr, pAuthenBuf, sizeof(TDevNetParam), (u8*)pDevNetPrm);
}


bool CBroadcast::SendRebootMsg(u32 dwDstIP, u8* pDstMacAddr, u8* abySecureCode, char* szUser, char* szPwd)
{
    TDAuthen tAuthen;

    u8* pAuthenBuf = NULL;
    if (szUser != NULL && szPwd != NULL)
    {
        CMD5::MD5Authen(szUser, szPwd, abySecureCode, &tAuthen);
        pAuthenBuf = (u8*)&tAuthen;
    }

    return SendUdpMsgPackage(NC_DEV_REBOOT_REQ_CAST, htonl(dwDstIP), pDstMacAddr, pAuthenBuf);
}

bool CBroadcast::SendUdpMsgPackage(u16 nMsgID, u32 dwDstIP /*= 0*/, u8* pDstMacAddr /*= NULL*/, u8* pAuthenBuf /*= NULL*/, u32 dwMsgBodySize /*= 0*/, u8* pMsgBodyBuf /*= NULL*/, bool bRefreshAdapter /*= TRUE*/)
{
    if (bRefreshAdapter)
    {
        memset(&m_atLoalAddr, 0, sizeof(m_atLoalAddr));
        //发送前更新一下网卡信息，防止网卡被破坏
        GetLocalAddr(m_atLoalAddr, m_dwLocalAdapterCount);
    }

    bool bRst = false;
    for (u32 dwIndex = 0; dwIndex < m_dwLocalAdapterCount; dwIndex++)
    {
        for (s32 nIndex = 0; nIndex < m_atLoalAddr[dwIndex].dwIPCount; nIndex++)
        {
            char pLocalIP[33];
            memcpy(pLocalIP, m_atLoalAddr[dwIndex].atIPAddr[nIndex].szIpFields, sizeof(char) * 16);

            u32 dwLocalIP = 0;
            if (strlen(pLocalIP))
            {
                dwLocalIP = inet_addr(pLocalIP);
            }
            
            printf("----------[Line:%d]local ipaddr = %s\n", __LINE__, pLocalIP);
            bRst |= SendBroadcastPackage(m_atLoalAddr[dwIndex].atMac.abyMac, dwLocalIP, nMsgID, pDstMacAddr, pAuthenBuf, dwMsgBodySize, pMsgBodyBuf);

            if (dwDstIP)
                bRst |= SendUnicastPackage(m_atLoalAddr[dwIndex].atMac.abyMac, dwDstIP, nMsgID, pDstMacAddr, pAuthenBuf, dwMsgBodySize, pMsgBodyBuf);
        }
    }
    return bRst;
}

bool CBroadcast::GetLocalAddr(TLocalAddr* atAddr, u32& dwEthCount)
{
    // 分配空间循环获取mac地址信息
    int nIndex;
    dwEthCount = 0;         /*物理网卡mac地址个数*/
    memset(atAddr, 0, 32 * sizeof(TLocalAddr));

#ifdef WIN32
    IP_ADAPTER_INFO  *IpAdaptersInfo;
    IP_ADAPTER_INFO  *IpAdaptersInfoHead;

    IpAdaptersInfo = (IP_ADAPTER_INFO *)GlobalAlloc(GPTR, sizeof(IP_ADAPTER_INFO));
    if (NULL == IpAdaptersInfo)
    {
        return false;
    }

    ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
    if (ERROR_BUFFER_OVERFLOW == GetAdaptersInfo(IpAdaptersInfo, &ulOutBufLen))
    {
        GlobalFree(IpAdaptersInfo);
        IpAdaptersInfo = (IP_ADAPTER_INFO *)GlobalAlloc(GPTR, ulOutBufLen);
    }

    u32 dwRetVal = GetAdaptersInfo(IpAdaptersInfo, &ulOutBufLen);
    if (dwRetVal != ERROR_SUCCESS)
    {
        GlobalFree(IpAdaptersInfo);
        return false;
    }
    else
    {
        IpAdaptersInfoHead = IpAdaptersInfo;

        do
        {
            // 只获取物理网卡
            if (IsLocalAdapter(IpAdaptersInfo->AdapterName))
            {
                for (nIndex = 0; nIndex < DT_LEN_MACADDR; ++nIndex)
                {
                    atAddr[dwEthCount].atMac.abyMac[nIndex] = IpAdaptersInfo->Address[nIndex];
                }
                _IP_ADDR_STRING* IpAddressList;
                IpAddressList = &(IpAdaptersInfo->IpAddressList);
                do
                {
                    for (nIndex = 0; nIndex < 16; ++nIndex)
                    {
                        atAddr[dwEthCount].atIPAddr[atAddr[dwEthCount].dwIPCount].szIpFields[nIndex] = IpAddressList->IpAddress.String[nIndex];
                        atAddr[dwEthCount].atIPAddr[atAddr[dwEthCount].dwIPCount].szIPMaskFields[nIndex] = IpAddressList->IpMask.String[nIndex];
                    }
                    atAddr[dwEthCount].dwIPCount++;
                    IpAddressList = IpAddressList->Next;
                } while (IpAddressList);
                dwEthCount++;
            }

            IpAdaptersInfo = IpAdaptersInfo->Next;

        } while (IpAdaptersInfo);
    }

    GlobalFree(IpAdaptersInfoHead);
#else

    SOCKHANDLE hSock = socket(AF_INET, SOCK_DGRAM, 0);
    if (INVALID_SOCKET == hSock)
    {
        closesock(hSock);
        return false;
    }
    struct ifreq atIfReq[16];
    struct ifconf tIfConf;
    struct ifreq tIfReqCp;
    s8 szMac[16]= {0};
    s8 szAddr[32]={0};
    s8 szMask[32] = {0};

    tIfConf.ifc_len = sizeof(atIfReq);
    tIfConf.ifc_buf = (caddr_t)atIfReq;
    u32 dwInterfaceCount = 0;

    if (!ioctl(hSock, SIOCGIFCONF, (s8*)&tIfConf))//获取所有网卡信息
    {
        dwInterfaceCount = tIfConf.ifc_len / sizeof(struct ifreq);
        dwEthCount = dwInterfaceCount;
        printf("----------[Line:%d]interface count = %d\n", __LINE__, dwEthCount);
        while (dwInterfaceCount--)
        {
            printf("----------[Line:%d]dev name = %s\n", __LINE__, atIfReq[dwInterfaceCount].ifr_name);
            tIfReqCp = atIfReq[dwInterfaceCount];

            if (ioctl(hSock, SIOCGIFFLAGS, &tIfReqCp))
            {
                closesock(hSock);
                return false;
            }

            //get one mac
            if (!ioctl(hSock, SIOCGIFHWADDR, (s8*)&atIfReq[dwInterfaceCount]))
            {
                for (nIndex = 0; nIndex < DT_LEN_MACADDR; ++nIndex)
                { 
                    atAddr[dwInterfaceCount].atMac.abyMac[nIndex] = (u8)atIfReq[dwInterfaceCount].ifr_hwaddr.sa_data[nIndex];
                }
            }
            else
            {
                closesock(hSock);
                return false;
            }

            //get one ip
            if (!ioctl(hSock, SIOCGIFADDR, (s8*)&atIfReq[dwInterfaceCount]))
            {
                sprintf(atAddr[dwInterfaceCount].atIPAddr[atAddr[dwEthCount].dwIPCount].szIpFields, "%s", (s8*)inet_ntoa(((struct sockaddr_in *)&(atIfReq[dwInterfaceCount].ifr_addr))->sin_addr));
            }
            else
            {
                closesock(hSock);
                return false;
            }

            //get one mask
            if (!ioctl(hSock, SIOCGIFNETMASK, &atIfReq[dwInterfaceCount]))
            {
                sprintf(atAddr[dwInterfaceCount].atIPAddr[atAddr[dwEthCount].dwIPCount].szIPMaskFields, "%s", (s8*)inet_ntoa(((struct sockaddr_in *)&(atIfReq[dwInterfaceCount].ifr_netmask))->sin_addr));
            }
            else
            {
                closesock(hSock);
                return false;
            }
            atAddr[dwInterfaceCount].dwIPCount++;
        }
    }
    else
    {
        closesock(hSock);
        return false;
    }

    closesock(hSock);

#endif // WIN32

    for (s32 nIndex = 0; nIndex < dwEthCount; nIndex++)
    {
        printf("eth[nIndex = %d] macaddr = %02x-%02x-%02x-%02x-%02x-%02x \n", nIndex + 1,
            atAddr[nIndex].atMac.abyMac[0], atAddr[nIndex].atMac.abyMac[1], atAddr[nIndex].atMac.abyMac[2],
            atAddr[nIndex].atMac.abyMac[3], atAddr[nIndex].atMac.abyMac[4], atAddr[nIndex].atMac.abyMac[5]);
        for (s32 n = 0; n < atAddr[nIndex].dwIPCount; n++)
        {
            printf("IP[n = %d] IPAddr = %s \n", n + 1, atAddr[nIndex].atIPAddr[n].szIpFields);
        }
    }
    return true;
}

#ifdef WIN32
bool CBroadcast::IsLocalAdapter(char *pAdapterName)
{
	// 网卡在注册表中的位置
#define NET_CARD_KEY ("System\\CurrentControlSet\\Control\\Network\\{4D36E972-E325-11CE-BFC1-08002BE10318}")

	HKEY hNetKey = NULL;
	if (ERROR_SUCCESS != RegOpenKeyExA(HKEY_LOCAL_MACHINE, NET_CARD_KEY, 0, KEY_READ, &hNetKey))
	{
		return false;
	}

	HKEY hLocalNet = NULL;
	char szDataBuf[MAX_PATH + 1];

	wsprintfA(szDataBuf, ("%s\\Connection"), pAdapterName);
	if (ERROR_SUCCESS != RegOpenKeyExA(hNetKey, szDataBuf, 0, KEY_READ, &hLocalNet))
	{
		RegCloseKey(hNetKey);
		return false;
	}

	BOOL ret_value = false;
	DWORD dwDataLen = MAX_PATH;
	DWORD dwType = REG_SZ;

	dwDataLen = MAX_PATH;
	if (ERROR_SUCCESS != RegQueryValueExA(hLocalNet, ("PnpInstanceID"), 0, &dwType, (BYTE *)szDataBuf, &dwDataLen))
	{
		goto ret;
	}

	if (strstr(szDataBuf, ("PCI")/*, strlen("PCI")*/) == NULL)
	{
		goto ret;
	}

	ret_value = true;

ret:
	RegCloseKey(hLocalNet);
	RegCloseKey(hNetKey);

	return ret_value;
}
#endif // WIN32

bool CBroadcast::SendDevDetectMsg(bool bRefreshAdapter)
{
	if (bRefreshAdapter)
	{
        memset(&m_atLoalAddr, 0, sizeof(m_atLoalAddr));
		// 为防止网卡被破坏，发送前再更新一下网卡信息
        GetLocalAddr(m_atLoalAddr, m_dwLocalAdapterCount);
	}

	bool bRst = false;
    for (u32 i = 0; i < m_dwLocalAdapterCount; i++)
	{
        for (s32 nIndex = 0; nIndex < m_atLoalAddr[i].dwIPCount; nIndex++)
        {
            char pLocalIP[33];
            memcpy(pLocalIP, m_atLoalAddr[i].atIPAddr[nIndex].szIpFields, sizeof(char) * 16);

            u32 dwLocalIP = 0;
            if (strlen(pLocalIP) != 0)
            {
                dwLocalIP = inet_addr(pLocalIP);
            }
            bRst = SendBroadcastPackage(m_atLoalAddr[i].atMac.abyMac, dwLocalIP, NC_DEV_TRACK_REQ_CAST);
        }
	}

	return bRst;
}

bool CBroadcast::SendDevDetectMsgByUnicast(bool bRefreshAdapter, u32 dwStart, u32 dwEnd)
{
    if (bRefreshAdapter)
    {
        memset(&m_atLoalAddr, 0, sizeof(m_atLoalAddr));
        // 为防止网卡被破坏，发送前再更新一下网卡信息
        GetLocalAddr(m_atLoalAddr, m_dwLocalAdapterCount);
    }

    bool bRst = false;
    for (u32 i = 0; i < m_dwLocalAdapterCount; i++)
    {
        // 创建SOCKET,并设置该套接字为组播类型
        m_bcSocketUnicastDetect = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);;
        if (INVALID_SOCKET == m_bcSocketUnicastDetect)
        {
            return FALSE;
        }

        for (u32 iIp = dwStart; iIp <= dwEnd && iIp <= (dwStart + 510) ; iIp++)
        {
            bRst = SendUnicastDetectPackage( m_atLoalAddr[i].atMac.abyMac, htonl(iIp));
            Sleep(20);
        }
        // 关闭SOCKET
        closesock(m_bcSocketUnicastDetect);
    }

    return bRst;
}

bool CBroadcast::SetDevDetectCtrl(bool bDetect)
{
    m_bDetect = bDetect;
    return m_bDetect;
}
