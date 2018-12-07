#include "rkcsession.h"

class CRkcConfigCtrl : public CRkcConfigCtrlIF 
{
	friend class CRkcSession;
public:
	CRkcConfigCtrl(CRkcSession &cSession);
	virtual ~CRkcConfigCtrl();

    //重启设备
    virtual u16 ReBootRk();
    //恢复出厂设置
    virtual u16 RestoreRk(TRK100LoginInfo tRK100LoginInfo);

    //获取工作模式配置
    virtual u16 GetWorkModeConfig();
    //获取工作模式配置内容
    virtual u16 GetWorkModeConfig(TRK100WorkMode& tRK100WorkMode);
    //修改工作模式配置内容
    virtual u16 SetWorkModeConfig(TRK100WorkMode tRK100WorkMode);

    //获取网络配置
    virtual u16 GetNetWorkConfig();
    //获取网络配置内容
    virtual u16 GetNetWorkConfig(TRK100NetParam& tRK100NetParam);
    //修改网络配置内容
    virtual u16 SetNetWorkConfig(TRK100NetParam tRK100NetParam);

    //升级
    virtual u16 SetFtpUpdateFirst(TRK100TftpFwUpdate tRK100TftpFwUpdate);
    virtual u16 SetFtpUpdateSecond();
    //获取升级内容
    virtual u16 GetUpdateConfig(TRK100UpdateHead& tRK100UpdateHead);

    //获取电源配置
    virtual u16 GetPowerConfig();
    //获取电源配置内容
    virtual u16 GetPowerConfig(TRK100PowerInfo& tRK100PowerInfo);

    //获取调试模式
    virtual u16 GetDebugConfig();
    //获取调试模式内容
    virtual u16 GetDebugConfig(TRK100DebugMode& tRK100DebugInfo);
    //修改调试模式内容
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
    TRK100WorkMode          m_tRK100WorkMode;           //保存工作模式
    TRK100NetParam          m_tRK100NetParam;           //网络参数
    TRK100TftpFwUpdate      m_tRK100TftpFwUpdate;       //TFTP
    TRK100PowerInfo         m_tRK100PowerInfo;          //电源
    TRK100DebugMode         m_tRK100DebugInfo;          //调试模式
    TRK100UpdateHead        m_tRK100UpdateHead;         //升级头
};
