/** @defgroup 登录逻辑单元 
 *  @version V1.0.0
 *  @author  ylp
 *  @date    2018.9.27
 */
#if !defined(AFX_TIPBOXLOGIC_H_)
#define AFX_TIPBOXLOGIC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTipBoxLogic : public CNotifyUIImpl
{
public:
	CTipBoxLogic();
	~CTipBoxLogic();

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
    
    APP_DECLARE_MSG_MAP()

private:
};

bool showTipBox(LPCTSTR lpstrText);
#define ShowTipBox showTipBox

#endif // !defined(AFX_TIPBOXLOGIC_H_)