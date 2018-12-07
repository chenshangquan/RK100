#include "rkcsession.h"

class CRkcConfigCtrl : public CRkcConfigCtrlIF 
{
	friend class CRkcSession;
public:
	CRkcConfigCtrl(CRkcSession &cSession);
	virtual ~CRkcConfigCtrl();

    //�����豸
    virtual u16 ReBootRk();
    //�ָ���������
    virtual u16 RestoreRk(TRK100LoginInfo tRK100LoginInfo);

    //��ȡ����ģʽ����
    virtual u16 GetWorkModeConfig();
    //��ȡ����ģʽ��������
    virtual u16 GetWorkModeConfig(TRK100WorkMode& tRK100WorkMode);
    //�޸Ĺ���ģʽ��������
    virtual u16 SetWorkModeConfig(TRK100WorkMode tRK100WorkMode);

    //��ȡ��������
    virtual u16 GetNetWorkConfig();
    //��ȡ������������
    virtual u16 GetNetWorkConfig(TRK100NetParam& tRK100NetParam);
    //�޸�������������
    virtual u16 SetNetWorkConfig(TRK100NetParam tRK100NetParam);

    //����
    virtual u16 SetFtpUpdateFirst(TRK100TftpFwUpdate tRK100TftpFwUpdate);
    virtual u16 SetFtpUpdateSecond();
    //��ȡ��������
    virtual u16 GetUpdateConfig(TRK100UpdateHead& tRK100UpdateHead);

    //��ȡ��Դ����
    virtual u16 GetPowerConfig();
    //��ȡ��Դ��������
    virtual u16 GetPowerConfig(TRK100PowerInfo& tRK100PowerInfo);

    //��ȡ����ģʽ
    virtual u16 GetDebugConfig();
    //��ȡ����ģʽ����
    virtual u16 GetDebugConfig(TRK100DebugMode& tRK100DebugInfo);
    //�޸ĵ���ģʽ����
    virtual u16 SetDebugConfig(TRK100DebugMode tRK100DebugInfo);

protected:
    void BuildEventsMap();

    void OnDicconnected(const CMessage& cMsg);

    void OnGetWorkModeConfigRsp(const CMessage& cMsg);
    void OnSetWorkModeConfigRsp(const CMessage& cMsg);

    void OnGetNetWorkConfigRsp(const CMessage& cMsg);
    void OnSetNetWorkConfigRsp(const CMessage& cMsg);

    void OnSetFtpUpdateFirstRsp(const CMessage& cMsg);
    void OnSetFtpUpdateFirstNotify(const CMessage& cMsg);
    void OnSetFtpUpdateSecondRsp(const CMessage& cMsg);
    void OnSetFtpUpdateSecondNotify(const CMessage& cMsg);

    void OnReBootRkRsp(const CMessage& cMsg);
    void OnRestoreRkRsp(const CMessage& cMsg);
    void OnPowerRsp(const CMessage& cMsg);

    void OnGetDebugModeRsp(const CMessage& cMsg);
    void OnSetDebugModeRsp(const CMessage& cMsg);

    virtual void DispEvent(const CMessage &cMsg);
    virtual void OnTimeOut(u16 wEvent);

private:
    CRkcSession             *m_pSession;
    TRK100WorkMode          m_tRK100WorkMode;           //���湤��ģʽ
    TRK100NetParam          m_tRK100NetParam;           //�������
    TRK100TftpFwUpdate      m_tRK100TftpFwUpdate;       //TFTP
    TRK100PowerInfo         m_tRK100PowerInfo;          //��Դ
    TRK100DebugMode         m_tRK100DebugInfo;          //����ģʽ
    TRK100UpdateHead        m_tRK100UpdateHead;         //����ͷ
};
