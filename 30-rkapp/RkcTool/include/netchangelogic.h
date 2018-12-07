/** @defgroup 网络变化提示*/
#pragma once

class CNetChangeLogic : public CNotifyUIImpl
{
public:
	CNetChangeLogic(void);
	~CNetChangeLogic(void);

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
	
public:
	/** 设置位置
	*  @param[in] 左上角坐标
	*  @return 
	*/
	bool SetPos();

	APP_DECLARE_MSG_MAP()
		
private:
	 
};

bool showNetChange(POINT pt, LPCTSTR lpstrIniPath);
#define ShowNetChange showNetChange

