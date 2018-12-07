/** @defgroup 设置菜单逻辑单元 
 *  @version V1.0.0
 *  @author  chenshangquan
 *  @date    2018.11.9
 */
#if !defined(AFX_SETMENU_H_)
#define AFX_SETMENU_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSetMenuLogic : public CNotifyUIImpl, public Singleton<CSetMenuLogic> 
{
public:
	CSetMenuLogic();
	~CSetMenuLogic();

public:
    // 更新窗口位置
    void OnUpdateWindowPos();
    // 窗口显示初始化
    void OnMenuShowInit();

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

    // 点击修改密码选项
    bool OnMdPwdItemClicked(TNotifyUI& msg);
    // 重启服务器
    bool OnRebootItemClicked(TNotifyUI& msg);
    // 点击关于选项
    bool OnAboutInfoItemClicked(TNotifyUI& mst);

    APP_DECLARE_MSG_MAP()

private:
    s32 m_nLeft;    //菜单窗口到主窗口左侧位置
    s32 m_nTop;     //菜单窗口到主窗口顶部位置
};

#endif // !defined(AFX_SETMENU_H_)