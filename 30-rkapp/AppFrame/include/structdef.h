#pragma once

namespace AppFrame
{
typedef DuiLib::CMarkupNode DocNode;

typedef CAppWindow Window;

typedef DuiLib::CControlUI Control;

#define MAX_PATH_LENTH MAX_PATH
/*
	��Ϣ�����ݽṹ
*/
typedef struct tagMsgParam 
{
	u16		wMsgId;			// ��Ϣ��
	UINT_PTR		pData;				// ����
	LPARAM  lParam;

	tagMsgParam()
	{
		memset( this, 0, sizeof(tagMsgParam) );
	}
}TMsgParam;

} // namespace AppFrame end 