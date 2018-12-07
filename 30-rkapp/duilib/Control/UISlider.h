#ifndef __UISLIDER_H__
#define __UISLIDER_H__

#pragma once

namespace DuiLib
{
	class UILIB_API CSliderUI : public CProgressUI
	{
	public:
		CSliderUI();

		LPCTSTR GetClass() const;
		UINT GetControlFlags() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		void SetEnabled(bool bEnable = true);

		int GetChangeStep();
		void SetChangeStep(int step);
		void SetThumbSize(SIZE szXY);
		RECT GetThumbRect() const;
		LPCTSTR GetThumbImage() const;
		void SetThumbImage(LPCTSTR pStrImage);
		LPCTSTR GetThumbHotImage() const;
		void SetThumbHotImage(LPCTSTR pStrImage);
		LPCTSTR GetThumbPushedImage() const;
		void SetThumbPushedImage(LPCTSTR pStrImage);

		void DoEvent(TEventUI& event);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void PaintBkImage(HDC hDC);
		void PaintStatusImage(HDC hDC);
		//计算当前的鼠标位置时进度的值
		int  CalculateMouseValue(POINT ptMouse);

		void SetValue(int nValue);

		void SetMouseWheel(bool bMouseWheel);

		bool GetIsMouseWheel();
		
		//是否保持滑动条高度不变 dyy 2015-1-22
		void SetIsKeepImageHeight(bool bIsKeepImageHeight);
		bool GetIsKeepImageHeight();

	protected:
		SIZE m_szThumb;
		UINT m_uButtonState;
		int	 m_nStep;
		bool m_bIsMouseWheel;  //是否支持鼠标滚动

		bool m_bIsKeepImageHeight;  //是否保持滑动条高度不变

		CDuiString m_sThumbImage;
		CDuiString m_sThumbHotImage;
		CDuiString m_sThumbPushedImage;

		CDuiString m_sImageModify;
	};
}

#endif // __UISLIDER_H__