#include "rkcsession.h"

class CRkcSysCtrl : public CRkcSysCtrlIF 
{
	friend class CRkcSession;
public:
	CRkcSysCtrl(CRkcSession &cSession);
	virtual ~CRkcSysCtrl();
    //建立Socket连接
    virtual u16 SocketConnect(s8* pchIP, u32 dwPort);
    //断开Socket连接
    virtual u16 CloseSocket();
    //发送Socket消息
    virtual u16 SendLoginReq(TRK100LoginInfo tRK100LoginInfo);
    //发送修改密码请求消息
    virtual u16 SendModifyPasswordReq(TRK100LoginInfo tRK100LoginInfo);
    //判断是否登录
    virtual bool IsLoginState();

    //获得登录错误反馈
    virtual u16 GetLoginBackInfo(TRK100MsgHead& tRK100MsgHead);

    //TFtp相关
    virtual bool OpenTftp();
    virtual bool CloseTftp();
    virtual bool SetTftpPath(const s8 *pchPath);
    virtual bool SetDhcpBootFile(const s8 *pchPath);
    virtual bool KillTftpProcess();

protected:
    void BuildEventsMap();

    void OnDicconnected(const CMessage& cMsg);
    void OnLoginOther(const CMessage& cMsg);

    void OnLoginRsp(const CMessage& cMsg);
    void OnModifyPasswordRsp(const CMessage& cMsg);

    virtual void DispEvent(const CMessage &cMsg);
    virtual void OnTimeOut(u16 wEvent);

private:
    CRkcSession    *m_pSession;

    TRK100MsgHead  m_tRK100MsgHead;//记录登录时反馈信息
};
