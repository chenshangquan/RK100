/** @defgroup cnc调用urllib的公共接口 
 *  @version V1.0.0
 *  @author  叶良平
 *  @date    2018.3.23
 */
#pragma once

#include "rkclib.h"

class CRkcInterface
{
public:
    /** 获取接口指针 */
    static CRkcInterface* GetCommIF();
    /** 销毁接口指针 */
    void DestroyCommIF();

public:
    /** 获取内嵌的窗口句柄
	*   @return HWND 返回窗口句柄 
	*/
	HWND GetRecvWindow(){ return m_hRecvWnd;};
	/** 创建会话
	*   @return u16 成功返回0;失败返回非0错误码 
	*/
	void CreateSession();

	/** 销毁会话
	*   @return u16 成功返回0;失败返回非0错误码 
	*/
	void DesdroySession();

    /**
	*   开始搜索
	*/ 
    u16 BeginSearch(EmSearchType emtype , u32 dwStartip = 0 , u32 dwEndip = 0);
    /**
	*   搜索操作
	*/ 
    u16 SearchDoing();
    /**
	*   搜索重置
	*/ 
    u16 ReSet(bool bEsitSearch = true);//bEsitSearch == false 只清空数据 不关闭搜索步骤

    /**
	*   获得IPC列表
	*/ 
    u16 GetDevList(vector<TDevItem>& vecTDevItem)const;

    /**
	*   判断是否登陆成功
	*/ 
    bool IsLoginState();
    /**
	*   获得登录的设备信息
	*/ 
    u16 GetLoginDevItem(TDevItem& tDevItem);
    /**
	*   获得登陆的账号密码
	*/ 
    u16 GetLoginInfo(TRK100LoginInfo& tRK100LoginInfo);

    /**
	*   修改登陆密码
	*/ 
    u16 SetLoginInfo(s8* szNewPwd);

    /**
	*   Socket连接
	*/ 
    u16 SocketConnect(TDevItem tDevItem , s8* szUser , s8* szPwd);
    /**
	*   Socket连接
	*/ 
    u16 SocketIP();
    /**
	*   Socket断开
	*/ 
    u16 CloseSocket();

    /**
	*   发送登录消息
	*/ 
    u16 SendLoginReq();

    /**
	*   发送修改密码消息
	*/ 
    u16 SendModifyPasswordReq();
    /**
	*   获得登录错误反馈
	*/ 
    u16 GetLoginBackInfo(TRK100MsgHead& tRK100MsgHead);

    /**
	*   重启设备
	*/ 
    u16 ReBootRk();
    /**
	*   恢复出厂设置
	*/ 
    u16 RestoreRk(TRK100LoginInfo tRK100LoginInfo);

    /**
	*   获取工作模式配置消息
	*/ 
    u16 GetWorkModeConfig();

    /**
	*   获取工作模式配置内容
	*/ 
    u16 GetWorkModeConfig(TRK100WorkMode& tRK100WorkMode);

    /**
	*   修改工作模式配置
	*/ 
    u16 SetWorkModeConfig(TRK100WorkMode tRK100WorkMode);

    /**
	*   获取网络配置消息
	*/ 
    u16 GetNetWorkConfig();
    /**
	*   获取网络配置内容
	*/ 
    u16 GetNetWorkConfig(TRK100NetParam& tRK100NetParam);
    /**
	*   修改网络配置
	*/ 
    u16 SetNetWorkConfig(TRK100NetParam tRK100NetParam);

    /**
	*   设置升级配置消息
	*/ 
    u16 SetFtpUpdateFirst(TRK100TftpFwUpdate tRK100TftpFwUpdate);
    /**
	*   设置升级配置消息
	*/ 
    u16 SetFtpUpdateSecond();

    /**
	*   获取升级内容
	*/ 
    u16 GetUpdateConfig(TRK100UpdateHead& tRK100UpdateHead);

    /**
	*   获取电源配置消息
	*/ 
    u16 GetPowerConfig();
    /**
	*   获取电源配置内容
	*/ 
    u16 GetPowerConfig(TRK100PowerInfo& tRK100PowerInfo);

    /**
	*   获取调试模式
	*/ 
    u16 GetDebugConfig();
    /**
	*   获取调试模式内容
	*/ 
    u16 GetDebugConfig(TRK100DebugMode& tRK100DebugInfo);
    /**
	*   修改调试模式内容
	*/ 
    u16 SetDebugConfig(TRK100DebugMode tRK100DebugInfo);

    //TFtp相关
    bool OpenTftp();
    bool CloseTftp();
    bool SetTftpPath(const s8 *pchPath);
    bool SetDhcpBootFile(const s8 *pchPath);
    bool KillTftpProcess();

private:
    static  CRkcInterface*  m_pMySelf;
    CRkcInterface(void);
    HWND                 m_hRecvWnd;         // 内嵌接收消息的窗口
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    WNDPROC              m_wndprocOld;       // 系统窗口过程

    CRkcSessionCtrlIF   *m_pRkcSession;       //url会话

    CRkcSysCtrlIF  *m_pSysCtrlIf;
    CRkcConfigCtrlIF  *m_pConfigCtrlIf;
    CRkcSearchCtrlIF  *m_pSearchCtrlIf;

    TDevItem             m_tDevItem;//保存登陆的设备信息
    TLoginInfo           m_tLoginInfo;//保存登录的IP 端口
    TRK100LoginInfo      m_tRK100LoginInfo;//保存登录的 账号密码
};

#define CRkcComInterface  CRkcInterface::GetCommIF()
