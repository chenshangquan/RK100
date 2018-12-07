#ifndef __UISLIDETABLAYOUT_H__
#define __UISLIDETABLAYOUT_H__

#pragma once

namespace DuiLib
{
	class UILIB_API CSlideTabLayoutUI : public CTabLayoutUI
	{
	public:
		CSlideTabLayoutUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		void DoEvent(TEventUI& event);
		void OnTimer( int nTimerID );
		void OnSliderStep();
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		bool SelectItem(int iIndex );
		void SetPos(RECT rc);

	protected:

        int         m_iCurFrame;
		bool        m_bIsVertical;
		int         m_nPositiveDirection;

		bool        m_bAnimating;

		RECT        m_rcCurPos;
		RECT        m_rcNextPos;

		CControlUI* m_pCurPage;            // 保存当前显示的页面
		CControlUI* m_pNextPage;		   // 保存下一页面

		enum
		{
			TIMER_ANIMATION_ID = 20,
			ANIMATION_ELLAPSE = 10,   //50,
			ANIMATION_FRAME_COUNT = 10//15 加快移动速度
		};
	};
}
#endif // __UISLIDETABLAYOUT_H__
