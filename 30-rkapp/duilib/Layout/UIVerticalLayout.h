#ifndef __UIVERTICALLAYOUT_H__
#define __UIVERTICALLAYOUT_H__

#pragma once

namespace DuiLib
{
	class UILIB_API CVerticalLayoutUI : public CContainerUI
	{
	public:
		CVerticalLayoutUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		UINT GetControlFlags() const;

		void SetSepHeight(int iHeight);
		int GetSepHeight() const;
		void SetSepImmMode(bool bImmediately);
		//设置是否响应鼠标拖动消息 dyy 2015-5-15 
		void SetSlideable(bool bSliderable);
		bool IsSepImmMode() const;
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void DoEvent(TEventUI& event);

		void SetPos(RECT rc);
		void DoPostPaint(HDC hDC, const RECT& rcPaint);

		RECT GetThumbRect(bool bUseNew = false) const;

	protected:
		int m_iSepHeight;                     //分隔符高度
		UINT m_uButtonState;
		POINT ptLastMouse;
		RECT m_rcNewPos;                      //控件区域位置
		bool m_bImmMode;                      //是否为立即模式(立即改变大小)
		bool m_bSliderable;

		bool            m_bLButtonDown;
		POINT           m_ptLButtonDown;      //鼠标按下位置
	};
}
#endif // __UIVERTICALLAYOUT_H__
