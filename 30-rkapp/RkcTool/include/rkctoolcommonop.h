#pragma once


class IRkcToolCommonOp : public ICommonOp
{
public:
	IRkcToolCommonOp(void);
	~IRkcToolCommonOp(void);

    /** 注册逻辑类 
	 *  @param[in] 
	 *  @return 是否成功
	 */
	static void RegLogics();

	/**  发送界面消息
	 *  @param[in] 消息Id，消息内容指针
	 *  @node 
	 *  @return 是否成功
	 */
	static bool NotifyMsg(u16 wMsgId, void *pData = NULL);

	static bool NotifyMsg(u16 wMsgId, WPARAM wParam, LPARAM lParam);

	/**  字符串格式化
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	static MbString StringFormat(const char *format, ...);
};

