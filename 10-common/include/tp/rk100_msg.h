/*******************************************************************************
 * 模块名  : COMMON_MSG
 * 文件名  : rk100_msg.h
 * 相关文件:
 * 文件功能: RK100 TCP通信协议公用消息、数据结构定义
 * 作者      : 袁增兴
 * 版本      : 1.0
 * -----------------------------------------------------------------------------
 * 修改记录:
 * 日  期        版本       修改人                          修改内容
 * 2018/09/26  1.0      yuanzengxing@kedacom.com     创建
*******************************************************************************/
#ifndef __RK100_MSG_H
#define __RK100_MSG_H

#define SN_LENGTH                        36    //SN长度
#define ENCRYPT_LENGTH                   36    //密钥长度
#define RK100_LISTEN_PORT                8000

/* 消息事件ID定义 */
enum EMRK100EvtId
{
    /* 用户登录, 消息体:TRK100LoginInfo
     * 应答消息体:NULL */
    RK100_EVT_LOGIN                     =2500,
    RK100_EVT_LOGIN_ACK                 =2501,

    /* 设置密码, 消息体:TRK100LoginInfo
     * 应答消息体:NULL */
    RK100_EVT_SET_PASSWORD              =2502,
    RK100_EVT_SET_PASSWORD_ACK          =2503,

    /* 获取板级信息, 消息体:NULL
     * 应答消息体:TRK100BrdInfo */
    RK100_EVT_GET_BRD_INFO              =2504,
    RK100_EVT_GET_BRD_INFO_ACK          =2505,

    /* 设置板级信息, 消息体:TRK100BrdInfo
     * 应答消息体:NULL */
    RK100_EVT_SET_BRD_INFO              =2506,
    RK100_EVT_SET_BRD_INFO_ACK          =2507,

    /* 重启设备, 消息体:NULL
     * 应答消息体:NULL */
    RK100_EVT_REBOOT                    =2508,
    RK100_EVT_REBOOT_ACK                =2509,

    /* 发起单板TFTP升级, 消息体:TRK100TftpFwUpdate
     * 应答消息体:TRK100UpdateHead
     * 单板升级结束或者实际失败后发送, 服务器注意等待时间可能较长 */
    RK100_EVT_TFTP_UPDATE_FIRST         =2510,
    RK100_EVT_TFTP_UPDATE_FIRST_ACK     =2511,

    /* 发起单板TFTP升级, 消息体:TRK100TftpFwUpdate
     * 应答消息体:NULL
     * 单板升级结束或者实际失败后发送, 服务器注意等待时间可能较长 */
    RK100_EVT_TFTP_UPDATE_SECOND        =2512,
    RK100_EVT_TFTP_UPDATE_SECOND_ACK    =2513,

    /* 获取网络参数, 消息体:NULL
     * 应答消息体:TRK100NetParam */
    RK100_EVT_GET_NETPARAM              =2514,
    RK100_EVT_GET_NETPARAM_ACK          =2515,

    /* 设置网络参数, 消息体:TRK100NetParam
     * 应答消息体:NULL */
    RK100_EVT_SET_NETPARAM              =2516,
    RK100_EVT_SET_NETPARAM_ACK          =2517,

    /* 恢复出厂请求, 消息体:TRK100LoginInfo
     * 应答消息体:NULL */
    RK100_EVT_RESTORE                   =2518,
    RK100_EVT_RESTORE_ACK               =2519,

    /* 获取工作模式, 消息体:NULL
     * 应答消息体:TRK100WorkMode */
    RK100_EVT_GET_WORK_MODE             =2520,
    RK100_EVT_GET_WORK_MODE_ACK         =2521,

    /* 设置工作模式, 消息体:TRK100WorkMode
     * 应答消息体:NULL */
    RK100_EVT_SET_WORK_MODE             =2522,
    RK100_EVT_SET_WORK_MODE_ACK         =2523,

    /* 设置心跳, 消息体:NULL
     * 应答消息体:NULL */
    RK100_EVT_SET_HEART_BEAT            =2524,
    RK100_EVT_SET_HEART_BEAT_ACK        =2525,

    /* 获取功耗, 消息体:NULL
     * 应答消息体:TRK100PowerInfo */
    RK100_EVT_GET_POWER                 =2526,
    RK100_EVT_GET_POWER_ACK             =2527,

    /* 被抢登 */
    RK100_EVT_LOGIN_OTHER               =2528,

    /* 升级结束或者实际失败后发送,服务器注意等待时间可能较长 */
    RK100_EVT_TFTP_UPDATE_FIRST_NOTIFY  =2529,
    RK100_EVT_TFTP_UPDATE_SECOND_NOTIFY =2530,

    /* 设置调试模式, 消息体:TRK100DebugMode
     * 应答消息体:NULL */
    RK100_EVT_SET_DEBUG_MODE            =2531,
    RK100_EVT_SET_DEBUG_MODE_ACK        =2532,

    /* 获取调试模式, 消息体:NULL
     * 应答消息体:TRK100DebugMode */
    RK100_EVT_GET_DEBUG_MODE            =2533,
    RK100_EVT_GET_DEBUG_MODE_ACK        =2534,
};

/* 事件处理返回值定义 */
enum EMRK100OptRtn
{
    RK100_OPT_RTN_OK                   = 0x0000, /* 操作成功*/

    RK100_OPT_ERR_EVT_ID               = 0x8000, /* 不支持的事件ID */
    RK100_OPT_ERR_USER                 = 0x8001, /* 用户名错误 */
    RK100_OPT_ERR_PASSWORD             = 0x8002, /* 密码错误 */
    RK100_OPT_ERR_NO_LOGIN             = 0x8003, /* 用户未登录 */
    RK100_OPT_ERR_PARAM                = 0x8004, /* 参数错误 */
    RK100_OPT_ERR_LEN                  = 0x8005, /* 长度错误 */
    RK100_OPT_ERR_NO_MEMORY            = 0x8006, /* 没有内存 */
    RK100_OPT_ERR_CHKSUM               = 0x8007, /* 校验和错误 */
    RK100_OPT_ERR_FUNC_FAILE           = 0x8008, /* 底层函数操作失败 */
    RK100_OPT_ERR_BUSY                 = 0x8009, /* 设备正忙 */
    RK100_OPT_ERR_FIRST_LOGIN          = 0x800A, /* 首次登录 */
    RK100_OPT_ERR_LOCKED               = 0x800B, /* 设备锁定 */
    RK100_OPT_ERR_UNKNOWN              = 0xFFFF, /* 未知错误 */
};

/* 设备运行状态定义 */
enum EMRK100DevStat
{
    RK100_DEV_STAT_RUN_OK              = 0x0000, /* 设备运行正常 */
    RK100_DEV_STAT_UPDATE              = 0x0001, /* 设备处于升级状态 */
    RK100_DEV_STAT_IN_BOOT             = 0x8001, /* 设备处于BOOT模式 */
    RK100_DEV_STAT_WAINING             = 0x8002, /* 设备有告警 */
    RK100_DEV_STAT_UNKNOWN             = 0xFFFF, /* 未知状态 */
};

/* 客户端和服务端之间通信的消息头部结构定义 */
typedef struct
{
    u32 dwHandle;             /* 消息令牌,透传 */
    u32 dwRsvd;               /* 备用 */
    u32 dwSerial;             /* 流水号 一个请求/应答中,该值保持不变 */
    u16 wExtLen;              /* 扩展头字节数,含填充字节 */
    u16 wReserved1;           /* 保留 */

    u32 dwProtocolVer;        /* 协议版本号, 由各单板自行定义,型如：1.1.1.1或0x01010101 */
    u32 dwEvent;              /* 事件,表示不同的操作码,见EMRK100EvtId定义 */
    s32 nArgv;                /* 设备处理函数返回的私有错误码或客户端传递的参数数据 */
    u16 wOptRtn;              /* 事件处理返回值。详见: EMRK100OptRtn */
    u16 wMsgLen;              /* 后续消息体长度 */
} TRK100MsgHead;

/* 登录校验 */
typedef struct
{
    char szUsr[64];
    char szPwd[64];
} TRK100LoginInfo;

/* 功耗信息 */
typedef struct
{
    u32 dwCurrent;            /* 外设的功率mW */
    u32 dwPower;              /* 外设的电流mA */
} TRK100PowerInfo;

/* 单板信息定义 */
typedef struct
{
    u8   abyMac[6];           /* MAC地址 */
    u16  wHid;                /* hid */
    u16  wPid;                /* pid */
    char szSoftVer[32];       /* 单板业务软件编译时间, 如: "Jan 9 2017 15:56:12" */
    char szSn[SN_LENGTH];     /* 序列号,只读 */
    u32  dwExt;               /* 扩展保留 */
} TRK100BrdInfo;

/* 通过TFTP进行升级 */
typedef struct
{
    u32  dwTftpSvrIp;         /* TFTP 服务器地址,网络序 */
    u32  dwFileSize;          /* 文件大小 */
    char szFwTypeName[64];    /* 固件类型名称 */
    char szFileFullName[260]; /* 下载文件名 */
    u8   byChkSumValid;       /* 版本数据校验和有效标志，非0时下面参数才有效 */
    u8   byChkSum;            /* 版本数据校验和，文件字节累加的值 */
    u8   byRsved;             /* 保留 */
} TRK100TftpFwUpdate;

 /* 网络参数 */
typedef struct {
    u8  byDhcpEn;             /* 1表示使用动态IP地址,以下参数在获取到地址信息后赋值 */
    u8  byRsved[1];           /* 预留字段 */
    u16 MqttPort;             /* mqtt端口 */
    u32 dwIP;                 /* IP地址 */
    u32 dwSubMask;            /* 子网掩码 */
    u32 dwGateway;            /* 网关 */
    u32 dwMqttIP;             /* mqtt地址 */
} TRK100NetParam;

/* 工作模式 */
typedef struct
{
    u8 AcFlag;                /* AC启动的标志 1:启动 0: 不启用 */
    u8 AcDelay;               /* AC上电以后的延时0~180s */
    u8 Uart0Flag;             /* uart0 开启标志 1: 启用 0: 不启用 */
    u8 Uart0SndDat[32];       /* uart0 发送的内容 */
    u8 Uart0RevDat[32];       /* uart0 接收的内容 */
    u8 Uart0SndLen;           /* uart0 发送的内容长度 */
    u8 Uart0RevLen;           /* uart0 接收的内容长度 */
    u8 Uart0Delay;            /* uart0 操作延时 */
    u8 Uart1Flag;             /* uart1 开启标志 1: 启用 0: 不启用 */
    u8 Uart1SndDat[32];       /* uart1 发送的内容 */
    u8 Uart1RevDat[32];       /* uart1 接收的内容 */
    u8 Uart1SndLen;           /* uart1 发送的内容长度 */
    u8 Uart1RevLen;           /* uart1 接收的内容长度 */
    u8 Uart1Delay;            /* uart1 操作延时 */
    u8 Uart2Flag;             /* uart2 开启标志 1: 启用 0: 不启用 */
    u8 Uart2SndDat[32];       /* uart2 发送的内容 */
    u8 Uart2RevDat[32];       /* uart2 接收的内容 */
    u8 Uart2SndLen;           /* uart2 发送的内容长度 */
    u8 Uart2RevLen;           /* uart2 接收的内容长度 */
    u8 Uart2Delay;            /* uart2 操作延时 */
    u8 Ir0Flag;               /* 红外发送0 开启标志 1: 启用 0: 不启用 */
    u8 Ir0Index;              /* 红外发送0的码形下标 CalcDate[Ir0Index] */
    u8 Ir0Delay;              /* 红外发送0延时 */
    u8 Ir1Flag;               /* 红外发送1 开启标志 1: 启用 0: 不启用 */
    u8 Ir1Index;              /* 红外发送1的码形下标 CalcDate[Ir1Index] */
    u8 Ir1Delay;              /* 红外发送1延时 */
    u8 RfFlag;                /* RF模块开启标志 1: 启用 0: 不启用 */
    u8 RfID[5][5];            /* RF模块ID号 RfID[0][0]:0x0 禁用 0x1:启用 RfID[0][1]..RfID[0][4]:RF开关的ID */
} TFuncMod;

/* 操作模式结构体 */
typedef struct
{
    TFuncMod FuncMod[4];      /* 4个操作模式 0:开机 1:关机 2:唤醒 3:待机 */
} TRK100WorkMode;

typedef struct
{
    u32 Magic;
    u8  FileCrc;
    u8  Version[64];
    u8  TftpCount;
} TRK100UpdateHead;

typedef struct
{
    u8  DebugSW;              /* 1:开启串口 0:关闭串口 */
} TRK100DebugMode;
#endif
