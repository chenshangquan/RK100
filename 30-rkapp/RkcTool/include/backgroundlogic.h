/** @defgroup 背景逻辑单元 
 *  @version V1.0.0
 *  @author  chenshangquan
 *  @date    2018.11.23
 */
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBackGroundLogic : public CNotifyUIImpl, public Singleton<CBackGroundLogic> 
{
public:
	CBackGroundLogic();
	~CBackGroundLogic();

public:

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

    APP_DECLARE_MSG_MAP()

private:

};