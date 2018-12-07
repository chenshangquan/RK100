#ifndef __UICHECKBOX_H__
#define __UICHECKBOX_H__

#pragma once

namespace DuiLib
{
	/// 最普通的单选按钮控件，只有是、否两种结果
	/// 派生于COptionUI，只是每组只有一个按钮而已，组名为空，配置文件默认属性举例：
	/// <CheckBox name="CheckBox" value="height='20' align='left' textpadding='24,0,0,0' normalimage='file='sys_check_btn.png' source='0,0,20,20' dest='0,0,20,20'' selectedimage='file='sys_check_btn.png' source='20,0,40,20' dest='0,0,20,20'' disabledimage='file='sys_check_btn.png' source='40,0,60,20' dest='0,0,20,20''"/>

	class UILIB_API CCheckBoxUI : public COptionUI
	{
	public:
		LPCTSTR GetClass() const;

		void SetCheck(bool bCheck);
		bool GetCheck() const;

		void PaintStatusImage(HDC hDC);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	protected:
		CDuiString m_sSelPushedImage;//选中状态时 点击时的图片 dyy 2015-5-22
		CDuiString m_sSelDisabledImage;//选中状态时 不可用时的图片 dyy 2016-11-23
	};
}

#endif // __UICHECKBOX_H__
