/** @defgroup cnc����urllib�Ĺ����ӿ� 
 *  @version V1.0.0
 *  @author  Ҷ��ƽ
 *  @date    2018.3.23
 */
#pragma once

#include "rkclib.h"

class CRkcInterface
{
public:
    /** ��ȡ�ӿ�ָ�� */
    static CRkcInterface* GetCommIF();
    /** ���ٽӿ�ָ�� */
    void DestroyCommIF();

public:
    /** ��ȡ��Ƕ�Ĵ��ھ��
	*   @return HWND ���ش��ھ�� 
	*/
	HWND GetRecvWindow(){ return m_hRecvWnd;};
	/** �����Ự
	*   @return u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
	*/
	void CreateSession();

	/** ���ٻỰ
	*   @return u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
	*/
	void DesdroySession();

    /**
	*   ��ʼ����
	*/ 
    u16 BeginSearch(EmSearchType emtype , u32 dwStartip = 0 , u32 dwEndip = 0);
    /**
	*   ��������
	*/ 
    u16 SearchDoing();
    /**
	*   ��������
	*/ 
    u16 ReSet(bool bEsitSearch = true);//bEsitSearch == false ֻ������� ���ر���������

    /**
	*   ���IPC�б�
	*/ 
    u16 GetDevList(vector<TDevItem>& vecTDevItem)const;

    /**
	*   �ж��Ƿ��½�ɹ�
	*/ 
    bool IsLoginState();
    /**
	*   ��õ�¼���豸��Ϣ
	*/ 
    u16 GetLoginDevItem(TDevItem& tDevItem);
    /**
	*   ��õ�½���˺�����
	*/ 
    u16 GetLoginInfo(TRK100LoginInfo& tRK100LoginInfo);

    /**
	*   �޸ĵ�½����
	*/ 
    u16 SetLoginInfo(s8* szNewPwd);

    /**
	*   Socket����
	*/ 
    u16 SocketConnect(TDevItem tDevItem , s8* szUser , s8* szPwd);
    /**
	*   Socket����
	*/ 
    u16 SocketIP();
    /**
	*   Socket�Ͽ�
	*/ 
    u16 CloseSocket();

    /**
	*   ���͵�¼��Ϣ
	*/ 
    u16 SendLoginReq();

    /**
	*   �����޸�������Ϣ
	*/ 
    u16 SendModifyPasswordReq();
    /**
	*   ��õ�¼������
	*/ 
    u16 GetLoginBackInfo(TRK100MsgHead& tRK100MsgHead);

    /**
	*   �����豸
	*/ 
    u16 ReBootRk();
    /**
	*   �ָ���������
	*/ 
    u16 RestoreRk(TRK100LoginInfo tRK100LoginInfo);

    /**
	*   ��ȡ����ģʽ������Ϣ
	*/ 
    u16 GetWorkModeConfig();

    /**
	*   ��ȡ����ģʽ��������
	*/ 
    u16 GetWorkModeConfig(TRK100WorkMode& tRK100WorkMode);

    /**
	*   �޸Ĺ���ģʽ����
	*/ 
    u16 SetWorkModeConfig(TRK100WorkMode tRK100WorkMode);

    /**
	*   ��ȡ����������Ϣ
	*/ 
    u16 GetNetWorkConfig();
    /**
	*   ��ȡ������������
	*/ 
    u16 GetNetWorkConfig(TRK100NetParam& tRK100NetParam);
    /**
	*   �޸���������
	*/ 
    u16 SetNetWorkConfig(TRK100NetParam tRK100NetParam);

    /**
	*   ��������������Ϣ
	*/ 
    u16 SetFtpUpdateFirst(TRK100TftpFwUpdate tRK100TftpFwUpdate);
    /**
	*   ��������������Ϣ
	*/ 
    u16 SetFtpUpdateSecond();

    /**
	*   ��ȡ��������
	*/ 
    u16 GetUpdateConfig(TRK100UpdateHead& tRK100UpdateHead);

    /**
	*   ��ȡ��Դ������Ϣ
	*/ 
    u16 GetPowerConfig();
    /**
	*   ��ȡ��Դ��������
	*/ 
    u16 GetPowerConfig(TRK100PowerInfo& tRK100PowerInfo);

    /**
	*   ��ȡ����ģʽ
	*/ 
    u16 GetDebugConfig();
    /**
	*   ��ȡ����ģʽ����
	*/ 
    u16 GetDebugConfig(TRK100DebugMode& tRK100DebugInfo);
    /**
	*   �޸ĵ���ģʽ����
	*/ 
    u16 SetDebugConfig(TRK100DebugMode tRK100DebugInfo);

    //TFtp���
    bool OpenTftp();
    bool CloseTftp();
    bool SetTftpPath(const s8 *pchPath);
    bool SetDhcpBootFile(const s8 *pchPath);
    bool KillTftpProcess();

private:
    static  CRkcInterface*  m_pMySelf;
    CRkcInterface(void);
    HWND                 m_hRecvWnd;         // ��Ƕ������Ϣ�Ĵ���
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    WNDPROC              m_wndprocOld;       // ϵͳ���ڹ���

    CRkcSessionCtrlIF   *m_pRkcSession;       //url�Ự

    CRkcSysCtrlIF  *m_pSysCtrlIf;
    CRkcConfigCtrlIF  *m_pConfigCtrlIf;
    CRkcSearchCtrlIF  *m_pSearchCtrlIf;

    TDevItem             m_tDevItem;//�����½���豸��Ϣ
    TLoginInfo           m_tLoginInfo;//�����¼��IP �˿�
    TRK100LoginInfo      m_tRK100LoginInfo;//�����¼�� �˺�����
};

#define CRkcComInterface  CRkcInterface::GetCommIF()
