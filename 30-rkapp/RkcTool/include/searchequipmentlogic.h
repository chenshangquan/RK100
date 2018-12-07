/** @defgroup 主窗口逻辑单元 
 *  @version V1.0.0
 *  @author  ylp
 *  @date    2018.9.12
 */
#if !defined(AFX_MAINFRAMELOGIC_H_)
#define AFX_MAINFRAMELOGIC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSearchEquipmentLogic : public CNotifyUIImpl, public Singleton<CSearchEquipmentLogic> 
{
public:
	CSearchEquipmentLogic();
	~CSearchEquipmentLogic();

public:
    void SetDevItem(TDevItem tDevItem);
    TDevItem GetDevItem();

    CString GetIniFilePath();
    void SetTimerOutTimer(bool bStart);//参数表示开启定时器 还是关闭定时器

    // 更新背景窗口位置
    void OnUpdateBGWindowPos();
    // 显示背景窗口
    bool OnShowBGWindow(LPCTSTR lpstrName = g_stcStrBackGroundDlg.c_str(), bool bShow = true);

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

    /** 移动 
	 *  @param[in] 
	 *  @node 
	 *  @return 
     */
    bool OnMove(TNotifyUI& msg);

    /** 收到窗口消息通知 
	*  @param[in] 消息
	*  @return 是否成功
	*/
    bool OnMsgNotify(TNotifyUI& msg);

    //点击设置按钮
    bool OnSetBtnClicked(TNotifyUI& msg);
    //点击最小化按钮
    bool OnMinBtnClicked(TNotifyUI& msg);
    //点击关闭按钮
    bool OnCloseBtnClicked(TNotifyUI& msg);
    //点击搜索按钮
    bool OnSearchBtnClicked(TNotifyUI& msg);
    //点击重置按钮
    bool OnResetBtnClicked(TNotifyUI& msg);
    //点击列表调试按钮
    bool OnItemOperateBtnClicked(TNotifyUI& msg);
    //登录后点击退出按钮
    bool OnExitBtnClicked(TNotifyUI& msg);

    bool OnOptSearchTypeIPSel(TNotifyUI& msg);
    bool OnOptSearchTypeAllSel(TNotifyUI& msg);

    bool OnRkcDevReflesh( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnRkcSearchFinish( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnRkcConnected( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnRkcDisconnected( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnRkcReBoot( WPARAM wparam, LPARAM lparam, bool& bHandle );

    APP_DECLARE_MSG_MAP()

private:
    static const String strEquipmentList;
    static const String strEquipmentListItem;

    TDevItem m_tDevItem;//保存调试的设备信息

    s32 m_nLeft;    //背景窗口左侧位置
    s32 m_nTop;     //背景窗口顶部位置
};

#endif // !defined(AFX_MAINFRAMELOGIC_H_)