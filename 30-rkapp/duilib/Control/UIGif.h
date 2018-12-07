#ifndef __UIBUTTONGIF_H__
#define __UIBUTTONGIF_H__

#pragma once

#include "UILabel.h"
#include "../utils/GifImage.h"

namespace DuiLib
{
	class UILIB_API CGifUI: public CControlUI
	{
	public:	
		CGifUI();
		~CGifUI();

		LPCTSTR GetClass() const
		{
			return _T("GifUI");
		}

		LPVOID GetInterface( LPCTSTR pstrName )
		{
			if( _tcscmp(pstrName, _T("Gif")) == 0 ) 
				return static_cast<CGifUI*>(this);

			return CControlUI::GetInterface(pstrName);
		}
		void DoInit();
		void SetGifFile(LPCTSTR pstrName);
		LPCTSTR GetGifFile();
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		virtual void DoEvent(TEventUI& event);
		virtual void SetVisible(bool bVisible = true);//设置控件可视性
		virtual void PaintStatusImage(HDC hDC);
	protected:
		enum
		{
			GIF_TIMER_ID = 15
		};

		bool m_isUpdateTime;
		CGifImage* m_pGifImg;
		int m_nPreUpdateDelay;
		CDuiString m_strGifFile;

	};
}// namespace DuiLib

#endif // __UIBUTTONGIF_H__