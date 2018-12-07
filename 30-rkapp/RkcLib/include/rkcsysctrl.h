#include "rkcsession.h"

class CRkcSysCtrl : public CRkcSysCtrlIF 
{
	friend class CRkcSession;
public:
	CRkcSysCtrl(CRkcSession &cSession);
	virtual ~CRkcSysCtrl();
    //����Socket����
    virtual u16 SocketConnect(s8* pchIP, u32 dwPort);
    //�Ͽ�Socket����
    virtual u16 CloseSocket();
    //����Socket��Ϣ
    virtual u16 SendLoginReq(TRK100LoginInfo tRK100LoginInfo);
    //�����޸�����������Ϣ
    virtual u16 SendModifyPasswordReq(TRK100LoginInfo tRK100LoginInfo);
    //�ж��Ƿ��¼
    virtual bool IsLoginState();

    //��õ�¼������
    virtual u16 GetLoginBackInfo(TRK100MsgHead& tRK100MsgHead);

    //TFtp���
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

    TRK100MsgHead  m_tRK100MsgHead;//��¼��¼ʱ������Ϣ
};
