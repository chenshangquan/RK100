/** @defgroup 登录逻辑单元 
 *  @version V1.0.0
 *  @author  ylp
 *  @date    2018.9.27
 */
#if !defined(AFX_MESSAGEBOXLOGIC_H_)
#define AFX_MESSAGEBOXLOGIC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum EmueMsgOperat
{
    Emue_None              = 0,     //无操作
    Emue_Restore,                   //恢复默认
};


class CMessageBoxLogic : public CNotifyUIImpl
{
public:
	CMessageBoxLogic();
	~CMessageBoxLogic();

protected:
	/** 窗口创建 
	*  @param[in] 消息
	*  @return 是否成功
	*/
	bool OnCreate(TNotifyUI& msg);

	/** 初始化消息 
	 *  @param[in] 
	 *  @node 
	 *  @return 
     */
    bool OnInit(TNotifyUI& msg);

    /** 关闭消息 
	 *  @param[in] 
	 *  @node 
	 *  @return 
     */
    bool OnDestroy(TNotifyUI& msg);

    //点击关闭按钮
    bool OnCloseBtnClicked(TNotifyUI& msg);
    //点击确定按钮
    bool OnOKBtnClicked(TNotifyUI& msg);
    //点击取消按钮
    bool OnCancelBtnClicked(TNotifyUI& msg);
    //网络修改详情
    bool OnNetChangeBtnClicked(TNotifyUI& msg);
    //点击其他地方
    bool OnSpaceLayoutClicked(TNotifyUI& msg);

    //设备重启反馈
    bool OnRkcRestone( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnRkcDisconnected( WPARAM wparam, LPARAM lparam, bool& bHandle );
    
    APP_DECLARE_MSG_MAP()

private:

    u8 m_emOperation;
};

u8 showMessageBox(LPCTSTR lpstrText, u8 byType = 1, LPCTSTR lpstrLeftText = _T("确定"));//0 没有按钮，1 确定按钮，2 确定 取消按钮
#define ShowMessageBox showMessageBox

bool showBackUpBox(LPCTSTR lpstrTime, LPCTSTR lpstrModel, LPCTSTR lpstrIniPath);
#define ShowBackUpBox showBackUpBox

bool showUpDateBox(LPCTSTR lpstrModel, LPCTSTR lpstrVer, LPCTSTR lpstrVerN);
#define ShowUpDateBox showUpDateBox

#endif // !defined(AFX_MESSAGEBOXLOGIC_H_)