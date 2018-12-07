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


#define DT_MAGIC	"NDT1"							// ��ʶͷ1
#define DT_MAGIC2	"NDT2"							// ��ʶͷ2

#define DT_PROTO_VER "1.3.0.0"						// Э��汾��
#define DT_AUTHENTICATION_ID		0x3210			// ��Ȩ
#define DT_B2_EXT_TAG				0xF7F7			// ���Я�����ֶΣ����ʾ��Я��DEV VERSION
#define DT_V7_EXT_TAG				0xF7F8			// ���Я�����ֶΣ����ʾ��Я��DEV VERSION��DEVICE STATE�Լ�AUTH NONCE

#define DT_LEN_MAGIC			4                 // ��ʶͷ����
#define DT_LEN_MACADDR			6					// MAC��ַ����
#define DT_LEN_USER_PWD_MD5		16					// MD5���ܺ󳤶�
#define DT_LEN_DNS				64					// DNS
#define DT_LEN_NAME				32					// �û���
#define DT_LEN_PROTO_VER		16					// Э��汾�ų���
#define DT_LEN_SOFT_VER			64					// ����汾�ų���
#define DT_LEN_SECURE_CODE		32					// ��ȫ�볤��
#define DT_LEN_SECURE_MAIL		64					// ��ȫ���䳤��
#define DT_LEN_SERIAL			10					// �豸���к�
#define DT_LEN_UPDATE_INFO		14					// �豸������Ϣ

    const u16 DT_PORT = 5513;
    const u16 MAXLEN_BCMSG = 1024;

    // ������
    const u32 DT_ERR_OK = 0;							// �����ɹ�
    const u32 DT_ERR_SET_IP_FAILED = 1;					// ����IPʧ��
    const u32 DT_ERR_CONNECT_CHECK_FAILED = 2;			// FTP����ʧ��
    const u32 DT_ERR_FILE_PATH_WRONG = 3;			// �ļ�·������
    const u32 DT_ERR_UPDATE_FILE_CREATE_FAILED = 4;		// �����ļ�����ʧ��
    const u32 DT_ERR_DATABASE_OP_FAILED = 5;
    const u32 DT_ERR_UPDATE_FILE_CHECK_FAILED = 6;		// �����ļ����ʧ��
    const u32 DT_ERR_SYSUPDATE_FAILED = 7;				// ����ʧ��
    const u32 DT_ERR_APPLOAD_MISS = 8;				// ȱ��apploader
    const u32 DT_ERR_AUTHEN_FAILED = 9;					// ��Ȩʧ��
    const u32 DT_ERR_ACTIVATE_WRONG = 10;				// �豸δ����
    const u32 DT_ERR_AUTHEN_TIMES_FAILED = 11;			// ��Ȩʧ�ܴ�������
    const u32 DT_ERR_OLD_VERSION_WRONG = 12;			// ��֧�ֵľɰ�ָ��
    const u32 DT_ERR_UPDATE_NOACK = 13;					// ���������޻�Ӧ
    const u32 DT_ERR_SET_GATEWAY_FAILED = 14;			// ����IPʧ��(����ʧ��)


    const u32 DT_NETMASK_MODADDR = 0x01;
    const u32 DT_NETMASK_MODREGPLAT = 0x02;

    typedef void(*MsgAckCB)(u32 wMsg, void* pParam, u32 dwContext);


    // ��ϢID����
#define DECLARE_MESSAGE(m, id) const u16 m = id;

    DECLARE_MESSAGE(NC_DEV_TRACK_REQ_CAST, 0x0001)		    // �豸̽��㲥��Ϣ��TDTHeader
    DECLARE_MESSAGE(DEV_NC_TRACK_ACK_CAST, 0x0002)		    // �豸��Ϣ֪ͨ��Ϣ��TDevItem

    DECLARE_MESSAGE(NC_DEV_MODADDR_REQ_CAST, 0x0003)		// �޸��豸��ַ��Ϣ: TDTHeader+TDTDevNetParam
    DECLARE_MESSAGE(DEV_NC_MODADDR_ACK_CAST, 0x0004)		// �޸��豸��ַ��Ϣ: TDevRetInfo

    DECLARE_MESSAGE(NC_DEV_REBOOT_REQ_CAST, 0x0005)		    // �����豸��Ϣ������Ҫ����: TDTHeader

    // �ṹ�嶨��
    struct TDMacAddr
    {
        u8  abyMac[DT_LEN_MACADDR];						// MAC��ַ

        bool operator < (const TDMacAddr &o) const
        {
            // ��д�����<����map����keyֵ
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
        TDMacAddr  tMacSrc;					// ������MAC��ַ(CHAR[12])  
        TDMacAddr  tMacDst;					// ������MAC��ַ(CHAR[12]) 	
        u16 wMsgID;											// ��ϢID
    }PACKED;

    struct TDAuthen											// ��Ȩ��Ϣ
    {
        s8 abyUser[DT_LEN_NAME];							// ��Ȩ�û���
        u8 abyPwd[DT_LEN_USER_PWD_MD5];						// ��Ȩ����
        u8 bAuthType;										// ��Ȩ����0x00��ʾ�û������뷽ʽ��0x01��ʾ��ȫ�뷽ʽ
        u8 bReserved;										// �����볤�ȣ����������޸�����ͼ���

        TDAuthen()
        {
            memset(this, 0, sizeof(TDAuthen));
        }
    }PACKED;

    struct TDTHeaderAuthen									// ��Ҫ�Ӽ�Ȩ����Ϣͷ
    {
        TDMacAddr  tMacSrc;									// ������MAC��ַ(CHAR[12])  
        TDMacAddr  tMacDst;									// ������MAC��ַ(CHAR[12]) 	
        u16	wAuthen;										// ��ȨID
        u16 wMsgID;											// ��ϢID
        TDAuthen tAuthen;									// ��Ȩ��Ϣ
    }PACKED;

    struct TDTDevAddr
    {
        u8 bDHCPServ;										// DHCP����������0-û��DHCP���� 1-��������2-�ͻ��� 
        u8 bDHCPOpen;										// 0-�ر� 1-����DHCP
        u32 dwIpaddr;										// IP��ַ��������
        u32 dwNetmask;										// �������룬������
        u32 dwGateWay;										// Ĭ�����أ�������
    }PACKED;

    struct TDTDvsRegPlat
    {
        u8 byRegIPType;										// ע���ַ����, 0-ip��ַ�� 1-dns
        u8 byIsCMS;											// �Ƿ����ø��ؾ��⣬ 0-�����ã�1-����
        u32 dwRegIP;										// �����򣬸��ؾ����IP�Լ�ƽ̨��ip��ַ����
        s8  achRegDNS[DT_LEN_DNS];							// ע��ƽ̨DNS
        u16 wRegPort;										// ע��ƽ̨�˿ڣ�ֻ�������ø������ʱ�����޸ģ�����Ĭ��5510
    }PACKED;

    // ƽ̨֧�ֹ���
    typedef struct tagPlatForm
    {
        u8 bR : 1;											// ���� Manual Reboot Mark
        u8 bF : 1;											// ���� FTP Upgrate Mark
        u8 bReserved1 : 1;
        u8 bReserved2 : 1;
        u8 bReserved3 : 1;
        u8 bReserved4 : 1;
        u8 bReserved5 : 1;
        u8 bReserved6 : 1;
    }TPlatForm;

    struct TDTDevInfo
    {
        TDTDevAddr tAddr;									// IP��MASK��GW
        u32 dwTickCount;									// ����ʱ��
        u32 dwBrdID;										// �豸����ID
        TDTDvsRegPlat tRegPlat;						        // ǰ��ע��ƽ̨����
        u8 byDevIdMask;										// ��ʶ�����Ƿ���DevId��Ϣ(1:��;0:�� 2:DEVID-NAMEʹ��UTF-8����)
        u8 byDevTypeMask;									// �Ƿ����豸�����ַ���(1:��;0:��)��Ϊ1ʱ���豸��Ϣ��TDTDevID����TDTDevType��Ϣ
        u8 bySrvTypeMask;									// �����ṩ���ͣ�0:IPC(ipdt)��1:VSǰ��(KDMSearch))
        u8 byMask3;											// �ж�����ϵ��modify by xuqinglai at 20101213
        TPlatForm tPlatForm;								// ƽ̨֧�ֹ���
        u8 bReserved1;
        u8 bReserved2;
        u8 bReserved3;
    }PACKED;

    struct TDTDevID
    {
        s8 achDevName[DT_LEN_NAME + 1];						// �豸����
        s8 achDevSerial[DT_LEN_SERIAL + 1];					// �豸���к�
        s8 achDevType[DT_LEN_NAME + 1];						// �豸��������
        s8 achDevUpdate[DT_LEN_UPDATE_INFO + 1];				// �豸������Ϣ
    }PACKED;

    struct TDTDevEx											// ��չ��Ϣ
    {
        s8 achDevSoftVersion[DT_LEN_SOFT_VER];				// ����汾��
        u16	wActiveState;									// �豸����״̬ 0xFFFF-�豸�쳣��0x0000-�豸δ���0x0001-�豸�Ѽ���
        u8 achSecureCode[DT_LEN_SECURE_CODE];				// ��ȫ��
        s8 achProTocolVer[DT_LEN_PROTO_VER];				// Э��汾��
        s8 achSecureMail[DT_LEN_SECURE_MAIL];				// ��ȫ����
    }PACKED;

    struct TDevItem
    {
        TDMacAddr tDevMacAddr;								// �豸MAC��ַ
        TDTDevInfo tDevInfo;								// ������Ϣ
        TDTDevID tDevID;									// ID
        u16 wTag;											// ��չ��ʶλ
        TDTDevEx tDevEx;									// ��չλ
        BOOL bNDT2;											// Э��ͷ�Ƿ�ΪNDT2

        TDevItem()
        {
            memset(this, 0, sizeof(TDevItem));
        }
    }PACKED;

    struct TDevRetInfo
    {
        TDMacAddr tDevMacAddr;									// �豸MAC��ַ
        u32 dwErrorCode;										// ������

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
        u32 dwNetMask;					// DT_NETMASK_MODADDR -��ʾ��ַ��Ч DT_NETMASK_MODREGPLAT-��ʾע���ַ��Ч����Ҫ�޸�
        TDTDevAddr tAddr;		        // IP��MASK��GW
        TDTDvsRegPlat tRegPlat;	        // ǰ��ע��ƽ̨����
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

    MSPSEARCH_API bool SetDevDetectCtrl(bool bDetect = true);    /*�����Ƿ����������Ĭ�Ͽ�������*/

    MSPSEARCH_API bool SendNetPrmMsg(u32 dwDstIP, u8* pDstMacAddr, u8* abySecureCode, char* szUser, char* szPwd, TDevNetParam* pDevNetPrm);

    MSPSEARCH_API bool SendNetPrmMsgS(TDevItem* ptDevItem, char* szUser, char* szPwd, TDevNetParam* pDevNetPrm);

    MSPSEARCH_API bool SendRebootMsg(u32 dwDstIP, u8* pDstMacAddr, u8* abySecureCode, char* szUser, char* szPwd);

#ifdef WIN32
#pragma pack( pop )
#endif //WIN32
#ifdef __cplusplus
}
#endif // __cplusplus