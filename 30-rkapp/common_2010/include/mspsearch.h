 #pragma once

#include "kdvtype.h"

#ifdef __cplusplus
extern "C" {

#ifdef WIN32
#define MSPSEARCH_API  extern "C" __declspec(dllexport)
#ifndef CDECL
#define CDECL  __cdecl
#endif // !CDECL
#define STDCALL  __stdcall
#else
#define MSPSEARCH_API
#define CDECL
#define STDCALL	
#endif  //WIN32

#endif // __cplusplus

#ifdef WIN32
#pragma pack( push, 1 )
#define PACKED
#endif //WIN32
#ifndef PACKED
#ifdef _VXWORKS_
#define PACKED __attribute__((__packed__))
#endif //_VXWORKS_
#ifdef _LINUX_
#ifndef _LINUXEQUATOR_
#define PACKED __attribute__((packed))
#endif //_LINUXEQUATOR_
#endif //_LINUX_
#ifdef _LINUXEQUATOR_
#define PACKED
#endif //_LINUXEQUATOR_
#endif //#ifndef PACKED


#define DT_MAGIC	"NDT1"							// 标识头1
#define DT_MAGIC2	"NDT2"							// 标识头2

#define DT_PROTO_VER "1.3.0.0"						// 协议版本号
#define DT_AUTHENTICATION_ID		0x3210			// 鉴权
#define DT_B2_EXT_TAG				0xF7F7			// 如果携带该字段，则表示会携带DEV VERSION
#define DT_V7_EXT_TAG				0xF7F8			// 如果携带该字段，则表示会携带DEV VERSION、DEVICE STATE以及AUTH NONCE

#define DT_LEN_MAGIC			4                 // 标识头长度
#define DT_LEN_MACADDR			6					// MAC地址长度
#define DT_LEN_USER_PWD_MD5		16					// MD5加密后长度
#define DT_LEN_DNS				64					// DNS
#define DT_LEN_NAME				32					// 用户名
#define DT_LEN_PROTO_VER		16					// 协议版本号长度
#define DT_LEN_SOFT_VER			64					// 软件版本号长度
#define DT_LEN_SECURE_CODE		32					// 安全码长度
#define DT_LEN_SECURE_MAIL		64					// 安全邮箱长度
#define DT_LEN_SERIAL			10					// 设备序列号
#define DT_LEN_UPDATE_INFO		14					// 设备升级信息

    const u16 DT_PORT = 5513;
    const u16 MAXLEN_BCMSG = 1024;

    // 错误码
    const u32 DT_ERR_OK = 0;							// 操作成功
    const u32 DT_ERR_SET_IP_FAILED = 1;					// 设置IP失败
    const u32 DT_ERR_CONNECT_CHECK_FAILED = 2;			// FTP连接失败
    const u32 DT_ERR_FILE_PATH_WRONG = 3;			// 文件路径错误
    const u32 DT_ERR_UPDATE_FILE_CREATE_FAILED = 4;		// 升级文件创建失败
    const u32 DT_ERR_DATABASE_OP_FAILED = 5;
    const u32 DT_ERR_UPDATE_FILE_CHECK_FAILED = 6;		// 升级文件检查失败
    const u32 DT_ERR_SYSUPDATE_FAILED = 7;				// 操作失败
    const u32 DT_ERR_APPLOAD_MISS = 8;				// 缺少apploader
    const u32 DT_ERR_AUTHEN_FAILED = 9;					// 鉴权失败
    const u32 DT_ERR_ACTIVATE_WRONG = 10;				// 设备未激活
    const u32 DT_ERR_AUTHEN_TIMES_FAILED = 11;			// 鉴权失败次数过多
    const u32 DT_ERR_OLD_VERSION_WRONG = 12;			// 不支持的旧版指令
    const u32 DT_ERR_UPDATE_NOACK = 13;					// 升级请求无回应
    const u32 DT_ERR_SET_GATEWAY_FAILED = 14;			// 设置IP失败(网关失败)


    const u32 DT_NETMASK_MODADDR = 0x01;
    const u32 DT_NETMASK_MODREGPLAT = 0x02;

    typedef void(*MsgAckCB)(u32 wMsg, void* pParam, u32 dwContext);


    // 消息ID定义
#define DECLARE_MESSAGE(m, id) const u16 m = id;

    DECLARE_MESSAGE(NC_DEV_TRACK_REQ_CAST, 0x0001)		    // 设备探测广播消息：TDTHeader
    DECLARE_MESSAGE(DEV_NC_TRACK_ACK_CAST, 0x0002)		    // 设备信息通知消息：TDevItem

    DECLARE_MESSAGE(NC_DEV_MODADDR_REQ_CAST, 0x0003)		// 修改设备地址消息: TDTHeader+TDTDevNetParam
    DECLARE_MESSAGE(DEV_NC_MODADDR_ACK_CAST, 0x0004)		// 修改设备地址消息: TDevRetInfo

    DECLARE_MESSAGE(NC_DEV_REBOOT_REQ_CAST, 0x0005)		    // 重启设备消息，不需要回馈: TDTHeader

    // 结构体定义
    struct TDMacAddr
    {
        u8  abyMac[DT_LEN_MACADDR];						// MAC地址

        bool operator < (const TDMacAddr &o) const
        {
            // 重写运算符<用于map查找key值
            for (int i = 0; i < DT_LEN_MACADDR; i++)
            {
                int nRet = abyMac[i] - o.abyMac[i];
                if (nRet == 0)
                {
                    continue;
                }
                else if (nRet < 0)
                {
                    return true;
                }

                return false;
            }

            return false;
        }
    };

    struct TDTHeader
    {
        TDMacAddr  tMacSrc;					// 发送者MAC地址(CHAR[12])  
        TDMacAddr  tMacDst;					// 接收者MAC地址(CHAR[12]) 	
        u16 wMsgID;											// 消息ID
    }PACKED;

    struct TDAuthen											// 鉴权信息
    {
        s8 abyUser[DT_LEN_NAME];							// 鉴权用户名
        u8 abyPwd[DT_LEN_USER_PWD_MD5];						// 鉴权密码
        u8 bAuthType;										// 鉴权类型0x00表示用户名密码方式，0x01表示安全码方式
        u8 bReserved;										// 新密码长度，仅适用于修改密码和激活

        TDAuthen()
        {
            memset(this, 0, sizeof(TDAuthen));
        }
    }PACKED;

    struct TDTHeaderAuthen									// 需要加鉴权的消息头
    {
        TDMacAddr  tMacSrc;									// 发送者MAC地址(CHAR[12])  
        TDMacAddr  tMacDst;									// 接收者MAC地址(CHAR[12]) 	
        u16	wAuthen;										// 鉴权ID
        u16 wMsgID;											// 消息ID
        TDAuthen tAuthen;									// 鉴权信息
    }PACKED;

    struct TDTDevAddr
    {
        u8 bDHCPServ;										// DHCP服务器类型0-没有DHCP服务 1-服务器，2-客户端 
        u8 bDHCPOpen;										// 0-关闭 1-开启DHCP
        u32 dwIpaddr;										// IP地址，网络序
        u32 dwNetmask;										// 子网掩码，网络序
        u32 dwGateWay;										// 默认网关，网络序
    }PACKED;

    struct TDTDvsRegPlat
    {
        u8 byRegIPType;										// 注册地址类型, 0-ip地址、 1-dns
        u8 byIsCMS;											// 是否启用负载均衡， 0-不启用，1-启用
        u32 dwRegIP;										// 网络序，负载均衡的IP以及平台的ip地址公用
        s8  achRegDNS[DT_LEN_DNS];							// 注册平台DNS
        u16 wRegPort;										// 注册平台端口，只有在启用负责均衡时才需修改，其他默认5510
    }PACKED;

    // 平台支持功能
    typedef struct tagPlatForm
    {
        u8 bR : 1;											// 重启 Manual Reboot Mark
        u8 bF : 1;											// 升级 FTP Upgrate Mark
        u8 bReserved1 : 1;
        u8 bReserved2 : 1;
        u8 bReserved3 : 1;
        u8 bReserved4 : 1;
        u8 bReserved5 : 1;
        u8 bReserved6 : 1;
    }TPlatForm;

    struct TDTDevInfo
    {
        TDTDevAddr tAddr;									// IP、MASK、GW
        u32 dwTickCount;									// 运行时间
        u32 dwBrdID;										// 设备类型ID
        TDTDvsRegPlat tRegPlat;						        // 前端注册平台参数
        u8 byDevIdMask;										// 标识后续是否有DevId信息(1:有;0:无 2:DEVID-NAME使用UTF-8编码)
        u8 byDevTypeMask;									// 是否有设备类型字符串(1:有;0:无)，为1时，设备信息在TDTDevID后还有TDTDevType信息
        u8 bySrvTypeMask;									// 服务提供类型（0:IPC(ipdt)，1:VS前端(KDMSearch))
        u8 byMask3;											// 判断升级系列modify by xuqinglai at 20101213
        TPlatForm tPlatForm;								// 平台支持功能
        u8 bReserved1;
        u8 bReserved2;
        u8 bReserved3;
    }PACKED;

    struct TDTDevID
    {
        s8 achDevName[DT_LEN_NAME + 1];						// 设备名称
        s8 achDevSerial[DT_LEN_SERIAL + 1];					// 设备序列号
        s8 achDevType[DT_LEN_NAME + 1];						// 设备类型名称
        s8 achDevUpdate[DT_LEN_UPDATE_INFO + 1];				// 设备升级信息
    }PACKED;

    struct TDTDevEx											// 扩展信息
    {
        s8 achDevSoftVersion[DT_LEN_SOFT_VER];				// 软件版本号
        u16	wActiveState;									// 设备激活状态 0xFFFF-设备异常，0x0000-设备未激活，0x0001-设备已激活
        u8 achSecureCode[DT_LEN_SECURE_CODE];				// 安全码
        s8 achProTocolVer[DT_LEN_PROTO_VER];				// 协议版本号
        s8 achSecureMail[DT_LEN_SECURE_MAIL];				// 安全邮箱
    }PACKED;

    struct TDevItem
    {
        TDMacAddr tDevMacAddr;								// 设备MAC地址
        TDTDevInfo tDevInfo;								// 基本信息
        TDTDevID tDevID;									// ID
        u16 wTag;											// 扩展标识位
        TDTDevEx tDevEx;									// 扩展位
        BOOL bNDT2;											// 协议头是否为NDT2

        TDevItem()
        {
            memset(this, 0, sizeof(TDevItem));
        }
    }PACKED;

    struct TDevRetInfo
    {
        TDMacAddr tDevMacAddr;									// 设备MAC地址
        u32 dwErrorCode;										// 错误码

        TDevRetInfo()
        {
            memset(this, 0, sizeof(TDevRetInfo));
        }
    }PACKED;

    struct TIPInfo
    {
        s8 szIpFields[4 * 4];
        s8 szIPMaskFields[4 * 4];
        TIPInfo()
        {
            memset(this, 0, sizeof(TIPInfo));
        }
    }PACKED;

    struct TLocalAddr
    {
        TDMacAddr atMac;
        u32       dwIPCount;
        TIPInfo   atIPAddr[16];
    };

    struct TDevNetParam
    {
        u32 dwNetMask;					// DT_NETMASK_MODADDR -表示地址有效 DT_NETMASK_MODREGPLAT-表示注册地址有效，需要修改
        TDTDevAddr tAddr;		        // IP、MASK、GW
        TDTDvsRegPlat tRegPlat;	        // 前端注册平台参数
        u32 dwReserved1;
        u32 dwReserved2;

        TDevNetParam()
        {
            memset(this, 0, sizeof(TDevNetParam));
        }
    }PACKED;

    MSPSEARCH_API bool CDECL InitMspSearch();

    MSPSEARCH_API bool CDECL ExitMspSearch();

    MSPSEARCH_API bool SetMsgAckCB(MsgAckCB mCB, u32 dwContext);

    MSPSEARCH_API bool SendDevDetectMsg(bool bRefreshAdapter);

    MSPSEARCH_API bool SendDevDetectMsgByUnicast(bool bRefreshAdapter, u32 dwStart, u32 dwEnd);

    MSPSEARCH_API bool SetDevDetectCtrl(bool bDetect = true);    /*控制是否继续搜索，默认开启搜索*/

    MSPSEARCH_API bool SendNetPrmMsg(u32 dwDstIP, u8* pDstMacAddr, u8* abySecureCode, char* szUser, char* szPwd, TDevNetParam* pDevNetPrm);

    MSPSEARCH_API bool SendNetPrmMsgS(TDevItem* ptDevItem, char* szUser, char* szPwd, TDevNetParam* pDevNetPrm);

    MSPSEARCH_API bool SendRebootMsg(u32 dwDstIP, u8* pDstMacAddr, u8* abySecureCode, char* szUser, char* szPwd);

#ifdef WIN32
#pragma pack( pop )
#endif //WIN32
#ifdef __cplusplus
}
#endif // __cplusplus