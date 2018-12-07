#pragma once

namespace AppFrame
{
typedef DuiLib::CMarkupNode DocNode;

typedef CAppWindow Window;

typedef DuiLib::CControlUI Control;

#define MAX_PATH_LENTH MAX_PATH
/*
	消息体数据结构
*/
typedef struct tagMsgParam 
{
	u16		wMsgId;			// 消息号
	UINT_PTR		pData;				// 数据
	LPARAM  lParam;

	tagMsgParam()
	{
		memset( this, 0, sizeof(tagMsgParam) );
	}
}TMsgParam;

} // namespace AppFrame end 