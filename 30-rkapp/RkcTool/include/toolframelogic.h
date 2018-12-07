/** @defgroup 工具主框架逻辑单元 
 *  @version V1.0.0
 *  @author  ylp
 *  @date    2018.10.9
 */
#if !defined(AFX_TOOLFRAME_H_)
#define AFX_TOOLFRAME_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum EmConfCtrlTabID
{
    emTabID_NetworkSetup = 0,
    emTabID_RadioSetup,
    emTabID_WorkingMode,
    emTabID_BackupUpgrade,
    emTabID_DebugMode,
    emTabID_ModifyPassword,
    emTabID_AboutInfo
};

class CToolFrameLogic : public CNotifyUIImpl, public Singleton<CToolFrameLogic> 
{
public:
	CToolFrameLogic();
	~CToolFrameLogic();

public:
    //刷新界面下方控件
    void InitBottomLeb();
    //修改密码页面
    bool OnTabModifyPassword();
    //关于信息页面
    bool OnTabAboutInfo();

    void SetFirstLogin(bool bFirstLogin);
    bool IsFirstLogin();

    //判断配置项是否修改 修改后是否保存 返回值 0->没有修改配置 1->点击保存配置 3->点击取消保存配置
    u8 ExitCheckChange();

protected:
	/** 窗口创建 
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnCreate(TNotifyUI& msg);

	/** 关闭窗口消息 
	 *  @param[in] 
	 *  @node 
	 *  @return 
     */
    bool OnDestory(TNotifyUI& msg);

	/** 初始化消息 
	 *  @param[in] 
	 *  @node 
	 *  @return 
     */
    bool OnInit(TNotifyUI& msg);

    /** 收到窗口消息通知 
	*  @param[in] 消息
	*  @return 是否成功
	*/
    bool OnMsgNotify(TNotifyUI& msg);

    //网络设置
    bool OnTabNetworkSetup(TNotifyUI& msg);
    //射频设置
    bool OnTabRadioSetup(TNotifyUI& msg);
    //工作模式
    bool OnTabWorkingMode(TNotifyUI& msg);
    //备份升级
    bool OnTabBackupUpgrade(TNotifyUI& msg);
    //调试模式
    bool OnTabDebugModel(TNotifyUI& msg);

    //判断配置项是否修改 修改后是否保存
    bool IsConfigChange();

    bool OnRkcPowerReflesh( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnRkcDisconnected( WPARAM wparam, LPARAM lparam, bool& bHandle );

    APP_DECLARE_MSG_MAP()

private:
    bool m_bIsFirstLogin;//是否是第一次登录
};

#endif // !defined(AFX_TOOLFRAME_H_)