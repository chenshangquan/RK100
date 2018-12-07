/*******************************************************************************
 * ģ����  : COMMON_MSG
 * �ļ���  : rk100_msg.h
 * ����ļ�:
 * �ļ�����: RK100 TCPͨ��Э�鹫����Ϣ�����ݽṹ����
 * ����      : Ԭ����
 * �汾      : 1.0
 * -----------------------------------------------------------------------------
 * �޸ļ�¼:
 * ��  ��        �汾       �޸���                          �޸�����
 * 2018/09/26  1.0      yuanzengxing@kedacom.com     ����
*******************************************************************************/
#ifndef __RK100_MSG_H
#define __RK100_MSG_H

#define SN_LENGTH                        36    //SN����
#define ENCRYPT_LENGTH                   36    //��Կ����
#define RK100_LISTEN_PORT                8000

/* ��Ϣ�¼�ID���� */
enum EMRK100EvtId
{
    /* �û���¼, ��Ϣ��:TRK100LoginInfo
     * Ӧ����Ϣ��:NULL */
    RK100_EVT_LOGIN                     =2500,
    RK100_EVT_LOGIN_ACK                 =2501,

    /* ��������, ��Ϣ��:TRK100LoginInfo
     * Ӧ����Ϣ��:NULL */
    RK100_EVT_SET_PASSWORD              =2502,
    RK100_EVT_SET_PASSWORD_ACK          =2503,

    /* ��ȡ�弶��Ϣ, ��Ϣ��:NULL
     * Ӧ����Ϣ��:TRK100BrdInfo */
    RK100_EVT_GET_BRD_INFO              =2504,
    RK100_EVT_GET_BRD_INFO_ACK          =2505,

    /* ���ð弶��Ϣ, ��Ϣ��:TRK100BrdInfo
     * Ӧ����Ϣ��:NULL */
    RK100_EVT_SET_BRD_INFO              =2506,
    RK100_EVT_SET_BRD_INFO_ACK          =2507,

    /* �����豸, ��Ϣ��:NULL
     * Ӧ����Ϣ��:NULL */
    RK100_EVT_REBOOT                    =2508,
    RK100_EVT_REBOOT_ACK                =2509,

    /* ���𵥰�TFTP����, ��Ϣ��:TRK100TftpFwUpdate
     * Ӧ����Ϣ��:TRK100UpdateHead
     * ����������������ʵ��ʧ�ܺ���, ������ע��ȴ�ʱ����ܽϳ� */
    RK100_EVT_TFTP_UPDATE_FIRST         =2510,
    RK100_EVT_TFTP_UPDATE_FIRST_ACK     =2511,

    /* ���𵥰�TFTP����, ��Ϣ��:TRK100TftpFwUpdate
     * Ӧ����Ϣ��:NULL
     * ����������������ʵ��ʧ�ܺ���, ������ע��ȴ�ʱ����ܽϳ� */
    RK100_EVT_TFTP_UPDATE_SECOND        =2512,
    RK100_EVT_TFTP_UPDATE_SECOND_ACK    =2513,

    /* ��ȡ�������, ��Ϣ��:NULL
     * Ӧ����Ϣ��:TRK100NetParam */
    RK100_EVT_GET_NETPARAM              =2514,
    RK100_EVT_GET_NETPARAM_ACK          =2515,

    /* �����������, ��Ϣ��:TRK100NetParam
     * Ӧ����Ϣ��:NULL */
    RK100_EVT_SET_NETPARAM              =2516,
    RK100_EVT_SET_NETPARAM_ACK          =2517,

    /* �ָ���������, ��Ϣ��:TRK100LoginInfo
     * Ӧ����Ϣ��:NULL */
    RK100_EVT_RESTORE                   =2518,
    RK100_EVT_RESTORE_ACK               =2519,

    /* ��ȡ����ģʽ, ��Ϣ��:NULL
     * Ӧ����Ϣ��:TRK100WorkMode */
    RK100_EVT_GET_WORK_MODE             =2520,
    RK100_EVT_GET_WORK_MODE_ACK         =2521,

    /* ���ù���ģʽ, ��Ϣ��:TRK100WorkMode
     * Ӧ����Ϣ��:NULL */
    RK100_EVT_SET_WORK_MODE             =2522,
    RK100_EVT_SET_WORK_MODE_ACK         =2523,

    /* ��������, ��Ϣ��:NULL
     * Ӧ����Ϣ��:NULL */
    RK100_EVT_SET_HEART_BEAT            =2524,
    RK100_EVT_SET_HEART_BEAT_ACK        =2525,

    /* ��ȡ����, ��Ϣ��:NULL
     * Ӧ����Ϣ��:TRK100PowerInfo */
    RK100_EVT_GET_POWER                 =2526,
    RK100_EVT_GET_POWER_ACK             =2527,

    /* ������ */
    RK100_EVT_LOGIN_OTHER               =2528,

    /* ������������ʵ��ʧ�ܺ���,������ע��ȴ�ʱ����ܽϳ� */
    RK100_EVT_TFTP_UPDATE_FIRST_NOTIFY  =2529,
    RK100_EVT_TFTP_UPDATE_SECOND_NOTIFY =2530,

    /* ���õ���ģʽ, ��Ϣ��:TRK100DebugMode
     * Ӧ����Ϣ��:NULL */
    RK100_EVT_SET_DEBUG_MODE            =2531,
    RK100_EVT_SET_DEBUG_MODE_ACK        =2532,

    /* ��ȡ����ģʽ, ��Ϣ��:NULL
     * Ӧ����Ϣ��:TRK100DebugMode */
    RK100_EVT_GET_DEBUG_MODE            =2533,
    RK100_EVT_GET_DEBUG_MODE_ACK        =2534,
};

/* �¼�������ֵ���� */
enum EMRK100OptRtn
{
    RK100_OPT_RTN_OK                   = 0x0000, /* �����ɹ�*/

    RK100_OPT_ERR_EVT_ID               = 0x8000, /* ��֧�ֵ��¼�ID */
    RK100_OPT_ERR_USER                 = 0x8001, /* �û������� */
    RK100_OPT_ERR_PASSWORD             = 0x8002, /* ������� */
    RK100_OPT_ERR_NO_LOGIN             = 0x8003, /* �û�δ��¼ */
    RK100_OPT_ERR_PARAM                = 0x8004, /* �������� */
    RK100_OPT_ERR_LEN                  = 0x8005, /* ���ȴ��� */
    RK100_OPT_ERR_NO_MEMORY            = 0x8006, /* û���ڴ� */
    RK100_OPT_ERR_CHKSUM               = 0x8007, /* У��ʹ��� */
    RK100_OPT_ERR_FUNC_FAILE           = 0x8008, /* �ײ㺯������ʧ�� */
    RK100_OPT_ERR_BUSY                 = 0x8009, /* �豸��æ */
    RK100_OPT_ERR_FIRST_LOGIN          = 0x800A, /* �״ε�¼ */
    RK100_OPT_ERR_LOCKED               = 0x800B, /* �豸���� */
    RK100_OPT_ERR_UNKNOWN              = 0xFFFF, /* δ֪���� */
};

/* �豸����״̬���� */
enum EMRK100DevStat
{
    RK100_DEV_STAT_RUN_OK              = 0x0000, /* �豸�������� */
    RK100_DEV_STAT_UPDATE              = 0x0001, /* �豸��������״̬ */
    RK100_DEV_STAT_IN_BOOT             = 0x8001, /* �豸����BOOTģʽ */
    RK100_DEV_STAT_WAINING             = 0x8002, /* �豸�и澯 */
    RK100_DEV_STAT_UNKNOWN             = 0xFFFF, /* δ֪״̬ */
};

/* �ͻ��˺ͷ����֮��ͨ�ŵ���Ϣͷ���ṹ���� */
typedef struct
{
    u32 dwHandle;             /* ��Ϣ����,͸�� */
    u32 dwRsvd;               /* ���� */
    u32 dwSerial;             /* ��ˮ�� һ������/Ӧ����,��ֵ���ֲ��� */
    u16 wExtLen;              /* ��չͷ�ֽ���,������ֽ� */
    u16 wReserved1;           /* ���� */

    u32 dwProtocolVer;        /* Э��汾��, �ɸ��������ж���,���磺1.1.1.1��0x01010101 */
    u32 dwEvent;              /* �¼�,��ʾ��ͬ�Ĳ�����,��EMRK100EvtId���� */
    s32 nArgv;                /* �豸���������ص�˽�д������ͻ��˴��ݵĲ������� */
    u16 wOptRtn;              /* �¼�������ֵ�����: EMRK100OptRtn */
    u16 wMsgLen;              /* ������Ϣ�峤�� */
} TRK100MsgHead;

/* ��¼У�� */
typedef struct
{
    char szUsr[64];
    char szPwd[64];
} TRK100LoginInfo;

/* ������Ϣ */
typedef struct
{
    u32 dwCurrent;            /* ����Ĺ���mW */
    u32 dwPower;              /* ����ĵ���mA */
} TRK100PowerInfo;

/* ������Ϣ���� */
typedef struct
{
    u8   abyMac[6];           /* MAC��ַ */
    u16  wHid;                /* hid */
    u16  wPid;                /* pid */
    char szSoftVer[32];       /* ����ҵ���������ʱ��, ��: "Jan 9 2017 15:56:12" */
    char szSn[SN_LENGTH];     /* ���к�,ֻ�� */
    u32  dwExt;               /* ��չ���� */
} TRK100BrdInfo;

/* ͨ��TFTP�������� */
typedef struct
{
    u32  dwTftpSvrIp;         /* TFTP ��������ַ,������ */
    u32  dwFileSize;          /* �ļ���С */
    char szFwTypeName[64];    /* �̼��������� */
    char szFileFullName[260]; /* �����ļ��� */
    u8   byChkSumValid;       /* �汾����У�����Ч��־����0ʱ�����������Ч */
    u8   byChkSum;            /* �汾����У��ͣ��ļ��ֽ��ۼӵ�ֵ */
    u8   byRsved;             /* ���� */
} TRK100TftpFwUpdate;

 /* ������� */
typedef struct {
    u8  byDhcpEn;             /* 1��ʾʹ�ö�̬IP��ַ,���²����ڻ�ȡ����ַ��Ϣ��ֵ */
    u8  byRsved[1];           /* Ԥ���ֶ� */
    u16 MqttPort;             /* mqtt�˿� */
    u32 dwIP;                 /* IP��ַ */
    u32 dwSubMask;            /* �������� */
    u32 dwGateway;            /* ���� */
    u32 dwMqttIP;             /* mqtt��ַ */
} TRK100NetParam;

/* ����ģʽ */
typedef struct
{
    u8 AcFlag;                /* AC�����ı�־ 1:���� 0: ������ */
    u8 AcDelay;               /* AC�ϵ��Ժ����ʱ0~180s */
    u8 Uart0Flag;             /* uart0 ������־ 1: ���� 0: ������ */
    u8 Uart0SndDat[32];       /* uart0 ���͵����� */
    u8 Uart0RevDat[32];       /* uart0 ���յ����� */
    u8 Uart0SndLen;           /* uart0 ���͵����ݳ��� */
    u8 Uart0RevLen;           /* uart0 ���յ����ݳ��� */
    u8 Uart0Delay;            /* uart0 ������ʱ */
    u8 Uart1Flag;             /* uart1 ������־ 1: ���� 0: ������ */
    u8 Uart1SndDat[32];       /* uart1 ���͵����� */
    u8 Uart1RevDat[32];       /* uart1 ���յ����� */
    u8 Uart1SndLen;           /* uart1 ���͵����ݳ��� */
    u8 Uart1RevLen;           /* uart1 ���յ����ݳ��� */
    u8 Uart1Delay;            /* uart1 ������ʱ */
    u8 Uart2Flag;             /* uart2 ������־ 1: ���� 0: ������ */
    u8 Uart2SndDat[32];       /* uart2 ���͵����� */
    u8 Uart2RevDat[32];       /* uart2 ���յ����� */
    u8 Uart2SndLen;           /* uart2 ���͵����ݳ��� */
    u8 Uart2RevLen;           /* uart2 ���յ����ݳ��� */
    u8 Uart2Delay;            /* uart2 ������ʱ */
    u8 Ir0Flag;               /* ���ⷢ��0 ������־ 1: ���� 0: ������ */
    u8 Ir0Index;              /* ���ⷢ��0�������±� CalcDate[Ir0Index] */
    u8 Ir0Delay;              /* ���ⷢ��0��ʱ */
    u8 Ir1Flag;               /* ���ⷢ��1 ������־ 1: ���� 0: ������ */
    u8 Ir1Index;              /* ���ⷢ��1�������±� CalcDate[Ir1Index] */
    u8 Ir1Delay;              /* ���ⷢ��1��ʱ */
    u8 RfFlag;                /* RFģ�鿪����־ 1: ���� 0: ������ */
    u8 RfID[5][5];            /* RFģ��ID�� RfID[0][0]:0x0 ���� 0x1:���� RfID[0][1]..RfID[0][4]:RF���ص�ID */
} TFuncMod;

/* ����ģʽ�ṹ�� */
typedef struct
{
    TFuncMod FuncMod[4];      /* 4������ģʽ 0:���� 1:�ػ� 2:���� 3:���� */
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
    u8  DebugSW;              /* 1:�������� 0:�رմ��� */
} TRK100DebugMode;
#endif
