#ifndef _h_rktruct_h__
#define _h_rktruct_h__

//登录请求
typedef struct tagTLoginRequest
{
public:
    char		m_achname[MAX_CHARLENGTH + 1]; //用户名
    char		m_achpassword[MAX_CHARLENGTH + 1];//密码
public:
    TLoginRequest()
    {
        memset(m_achname,0,MAX_CHARLENGTH + 1 );
        memset(m_achpassword,0,MAX_CHARLENGTH + 1 );
    }
    //设置和得到用户名
    char* GetName()
    {
        m_achname[MAX_CHARLENGTH] = '\0';
        return m_achname;
    }
    void  SetName(char* pchbuf)
    {
        if(pchbuf == NULL)
        {
            return;
        }
        memset(m_achname,0,MAX_CHARLENGTH + 1);
        int nlength = (strlen(pchbuf) >= MAX_CHARLENGTH ? MAX_CHARLENGTH: strlen(pchbuf));
        memcpy(m_achname,pchbuf,nlength);
        m_achname[nlength] = '\0';
    };
    //设置和得到密码
    char* GetPassword()
    {
        return m_achpassword;
    }
    //输入密码为明文
    void  SetPassword(char* pchbuf)
    {
        if(pchbuf == NULL)
        {
            return;
        }
        memset(m_achpassword,0,MAX_CHARLENGTH + 1);
        int nlength = (strlen(pchbuf) >= MAX_CHARLENGTH ? MAX_CHARLENGTH: strlen(pchbuf));
        memcpy(m_achpassword,pchbuf,nlength);
        m_achpassword[nlength] = '\0';
    }

    void Empty()
    {
        memset(m_achname,0,MAX_CHARLENGTH+1);
        memset(m_achpassword,0,MAX_CHARLENGTH+1);
    }
}TLoginRequest;

//登录反馈
typedef struct tagTLoginRet 
{
public:
    void SetRet( EmTpLoginUmsRet emRet )
    {
        m_emRet = (EmTpLoginUmsRet)htonl( emRet );
    }

    EmTpLoginUmsRet GetRet( )
    {
        return (EmTpLoginUmsRet)ntohl( m_emRet );
    }
public:
    EmTpLoginUmsRet m_emRet;

    tagTLoginRet()
    {
        m_emRet = tp_LoginUms_sucess;
    }
}TLoginRet;

//射频设置
typedef struct tagTRadioFrequency 
{
public:
    void CheckOpen(BOOL32 bOpen)
    {
        m_bOpen = bOpen;
    }

    BOOL32 IsOpen()
    {
        return m_bOpen;
    }

    void SetEquipmentType( EmEquipmentType emEqe )
    {
        m_emEqe = (EmEquipmentType)htonl( emEqe );
    }

    EmEquipmentType GetEquipmentType( )
    {
        return (EmEquipmentType)ntohl( m_emEqe );
    }

    void SetPeripheralIp(u8 wIndex, u32 dwIp)
    {
        if (wIndex > MAX_PERIPHERAL_NUM)
        {
            return;
        }
        m_dwIp[wIndex] = dwIp;
    }
public:
    BOOL32          m_bOpen;
    EmEquipmentType m_emEqe;
    u32             m_dwIp[MAX_PERIPHERAL_NUM];             //外设IP（最大五个）

    tagTRadioFrequency()
    {
        memset(this, 0, sizeof(tagTRadioFrequency));
    }
}TRadioFrequency;

//工作模式
typedef struct tagTWorkingMode 
{
public:
    void SetWorkingMode( EmWorkingMode emWorkingMode )
    {
        m_emWorkingMode = (EmWorkingMode)htonl( emWorkingMode );
    }

    EmEquipmentType GetWorkingMode( )
    {
        return (EmWorkingMode)ntohl( m_emWorkingMode );
    }
public:
    EmWorkingMode m_emWorkingMode;
    BOOL32        m_bRelayAC;
    u16           m_wRelayDelay;
    BOOL32        m_bSwitchSW;
    u16           m_wSwitchDelay;
    EmSerialPort  m_emserialport;
    u16           m_wSPDelay;

    EmInfraRed    m_eminfrared;

    tagTWorkingMode()
    {
        memset(this, 0, sizeof(tagTWorkingMode));
    }
}TWorkingMode;

#endif //_h_rktruct_h__