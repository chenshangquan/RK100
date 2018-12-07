#include "StdAfx.h"
#include "UISlider.h"

namespace DuiLib
{
	CSliderUI::CSliderUI() : m_uButtonState(0), m_nStep(1),m_bIsMouseWheel(true),m_bIsKeepImageHeight(false)
	{
		m_uTextStyle = DT_SINGLELINE | DT_CENTER;
		m_szThumb.cx = m_szThumb.cy = 10;
	}

	LPCTSTR CSliderUI::GetClass() const
	{
		return _T("SliderUI");
	}

	UINT CSliderUI::GetControlFlags() const
	{
		if( IsEnabled() ) return UIFLAG_SETCURSOR;
		else return 0;
	}

	LPVOID CSliderUI::GetInterface(LPCTSTR pstrName)
	{
		if( _tcscmp(pstrName, DUI_CTR_SLIDER) == 0 ) return static_cast<CSliderUI*>(this);
		return CProgressUI::GetInterface(pstrName);
	}

	void CSliderUI::SetEnabled(bool bEnable)
	{
		CControlUI::SetEnabled(bEnable);
		if( !IsEnabled() ) {
			m_uButtonState = 0;
		}
	}

	int CSliderUI::GetChangeStep()
	{
		return m_nStep;
	}

	void CSliderUI::SetChangeStep(int step)
	{
		m_nStep = step;
	}

	void CSliderUI::SetThumbSize(SIZE szXY)
	{
		if ( CPaintManagerUI::IsSelfAdaption() )
		{
			float fAdpX, fAdpY;
			CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
			m_szThumb.cy = szXY.cy * fAdpY;
			m_szThumb.cx = szXY.cx * fAdpX;
		}
		else
		{
			m_szThumb = szXY;
		}
	}

	RECT CSliderUI::GetThumbRect() const
	{
		if( m_bHorizontal ) {
			int left = m_rcItem.left +  ( (long long)(m_rcItem.right - m_rcItem.left - m_szThumb.cx) ) *  (m_nValue - m_nMin)  / (m_nMax - m_nMin);
			int top = (m_rcItem.bottom + m_rcItem.top - m_szThumb.cy) / 2;
			return CDuiRect(left, top, left + m_szThumb.cx, top + m_szThumb.cy); 
		}
		else {
			int left = (m_rcItem.right + m_rcItem.left - m_szThumb.cx) / 2;
			int top = m_rcItem.bottom - m_szThumb.cy -  ( (long long )(m_rcItem.bottom - m_rcItem.top - m_szThumb.cy) )* (m_nValue - m_nMin)  / (m_nMax - m_nMin);
			return CDuiRect(left, top, left + m_szThumb.cx, top + m_szThumb.cy); 
		}
	}

	LPCTSTR CSliderUI::GetThumbImage() const
	{
		return m_sThumbImage;
	}

	void CSliderUI::SetThumbImage(LPCTSTR pStrImage)
	{
		m_sThumbImage = pStrImage;
		Invalidate();
	}

	LPCTSTR CSliderUI::GetThumbHotImage() const
	{
		return m_sThumbHotImage;
	}

	void CSliderUI::SetThumbHotImage(LPCTSTR pStrImage)
	{
		m_sThumbHotImage = pStrImage;
		Invalidate();
	}

	LPCTSTR CSliderUI::GetThumbPushedImage() const
	{
		return m_sThumbPushedImage;
	}

	void CSliderUI::SetThumbPushedImage(LPCTSTR pStrImage)
	{
		m_sThumbPushedImage = pStrImage;
		Invalidate();
	}

	void CSliderUI::DoEvent(TEventUI& event)
	{
		if( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
			if( m_pParent != NULL ) m_pParent->DoEvent(event);
			else CProgressUI::DoEvent(event);
			return;
		}

		if( event.Type == UIEVENT_BUTTONDOWN || event.Type == UIEVENT_DBLCLICK )
		{
			if( IsEnabled() ) {
				RECT rcThumb = GetThumbRect();
				if( ::PtInRect(&rcThumb, event.ptMouse) ) {
					m_uButtonState |= UISTATE_CAPTURED;
				}
			}
			return;
		}
		if( event.Type == UIEVENT_BUTTONUP )
		{
			if ( IsEnabled() )
			{
				int nValue;
				if( (m_uButtonState & UISTATE_CAPTURED) != 0 ) {
					m_uButtonState &= ~UISTATE_CAPTURED;
				}
				if( m_bHorizontal ) {
					if( event.ptMouse.x >= m_rcItem.right - m_szThumb.cx / 2 ) nValue = m_nMax;
					else if( event.ptMouse.x <= m_rcItem.left + m_szThumb.cx / 2 ) nValue = m_nMin;
					else nValue = m_nMin + ( (long long)(m_nMax - m_nMin) ) * (event.ptMouse.x - m_rcItem.left - m_szThumb.cx / 2 ) / (m_rcItem.right - m_rcItem.left - m_szThumb.cx);
				}
				else {
					if( event.ptMouse.y >= m_rcItem.bottom - m_szThumb.cy / 2 ) nValue = m_nMin;
					else if( event.ptMouse.y <= m_rcItem.top + m_szThumb.cy / 2  ) nValue = m_nMax;
					else nValue = m_nMin + ( (long long)(m_nMax - m_nMin) )* (m_rcItem.bottom - event.ptMouse.y - m_szThumb.cy / 2 ) / (m_rcItem.bottom - m_rcItem.top - m_szThumb.cy);
				}
				SetValue(nValue);
				m_pManager->SendNotify(this, DUI_MSGTYPE_VALUECHANGED);
			}
			
			return;
		}
		if( event.Type == UIEVENT_CONTEXTMENU )
		{
			return;
		}
		if( event.Type == UIEVENT_SCROLLWHEEL ) 
		{
			if (m_bIsMouseWheel)
			{/*判断是否支持鼠标滚动，默认情况是支持*/
				switch( LOWORD(event.wParam) ) {
				case SB_LINEUP:
					SetValue(GetValue() + GetChangeStep());
					m_pManager->SendNotify(this, DUI_MSGTYPE_VALUECHANGED);
					return;
				case SB_LINEDOWN:
					SetValue(GetValue() - GetChangeStep());
					m_pManager->SendNotify(this, DUI_MSGTYPE_VALUECHANGED);
			}		
  			return;
			}
		}
		if( event.Type == UIEVENT_MOUSEMOVE )
		{
			if ( IsEnabled() )
			{
				if( (m_uButtonState & UISTATE_CAPTURED) != 0 ) {
					if( m_bHorizontal ) {
						if( event.ptMouse.x >= m_rcItem.right - m_szThumb.cx / 2 ) m_nValue = m_nMax;
						else if( event.ptMouse.x <= m_rcItem.left + m_szThumb.cx / 2 ) m_nValue = m_nMin;
						else m_nValue = m_nMin + ( (long long)(m_nMax - m_nMin) ) * (event.ptMouse.x - m_rcItem.left - m_szThumb.cx / 2 ) / (m_rcItem.right - m_rcItem.left - m_szThumb.cx);
					}
					else {
						if( event.ptMouse.y >= m_rcItem.bottom - m_szThumb.cy / 2 ) m_nValue = m_nMin;
						else if( event.ptMouse.y <= m_rcItem.top + m_szThumb.cy / 2  ) m_nValue = m_nMax;
						else m_nValue = m_nMin + ( (long long)(m_nMax - m_nMin) ) * (m_rcItem.bottom - event.ptMouse.y - m_szThumb.cy / 2 ) / (m_rcItem.bottom - m_rcItem.top - m_szThumb.cy);
					}
					m_pManager->SendNotify(this, DUI_MSGTYPE_VALUECHANGING);
					Invalidate();

				}

				m_pManager->SendNotify(this, DUI_MSGTYPE_MOUSEMOVE);
			}

			return;
		}
		if( event.Type == UIEVENT_SETCURSOR )
		{
			RECT rcThumb = GetThumbRect();
			if( IsEnabled() && ::PtInRect(&rcThumb, event.ptMouse) ) {
				::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND)));
				return;
			}
		}
		if( event.Type == UIEVENT_MOUSEENTER )
		{
			if( IsEnabled() ) {
				m_uButtonState |= UISTATE_HOT;
				Invalidate();
				m_pManager->SendNotify(this, DUI_MSGTYPE_MOUSEENTER);
			}			
			return;
		}
		if( event.Type == UIEVENT_MOUSELEAVE )
		{
			if( IsEnabled() ) {
				m_uButtonState &= ~UISTATE_HOT;
				Invalidate();
				m_pManager->SendNotify(this, DUI_MSGTYPE_MOUSELEAVE);
			}
			return;
		}
		CControlUI::DoEvent(event);
	}

	int CSliderUI::CalculateMouseValue(POINT ptMouse)
	{
		int nValue = 0;
		if( m_bHorizontal ) {
			if( ptMouse.x >= m_rcItem.right - m_szThumb.cx / 2 ) nValue = m_nMax;
			else if( ptMouse.x <= m_rcItem.left + m_szThumb.cx / 2 ) nValue = m_nMin;
			else nValue = m_nMin + ( (long long)(m_nMax - m_nMin) ) * ( ptMouse.x - m_rcItem.left - m_szThumb.cx / 2 ) / (m_rcItem.right - m_rcItem.left - m_szThumb.cx);
		}
		else {
			if( ptMouse.y >= m_rcItem.bottom - m_szThumb.cy / 2 ) nValue = m_nMin;
			else if( ptMouse.y <= m_rcItem.top + m_szThumb.cy / 2  ) nValue = m_nMax;
			else nValue = m_nMin + ( (long long)(m_nMax - m_nMin) ) * (m_rcItem.bottom - ptMouse.y - m_szThumb.cy / 2 ) / (m_rcItem.bottom - m_rcItem.top - m_szThumb.cy);
		}
		return nValue;
	}

	void CSliderUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		if( _tcscmp(pstrName, _T("thumbimage")) == 0 ) SetThumbImage(pstrValue);
		else if( _tcscmp(pstrName, _T("thumbhotimage")) == 0 ) SetThumbHotImage(pstrValue);
		else if( _tcscmp(pstrName, _T("thumbpushedimage")) == 0 ) SetThumbPushedImage(pstrValue);
		else if( _tcscmp(pstrName, _T("thumbsize")) == 0 ) {
			SIZE szXY = {0};
			LPTSTR pstr = NULL;
			szXY.cx = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
			szXY.cy = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr); 
			SetThumbSize(szXY);
		}
		else if( _tcscmp(pstrName, _T("step")) == 0 ) {
			SetChangeStep(_ttoi(pstrValue));
		}
		else if ( _tcscmp(pstrName, _T("mousewheel")) == 0)
		{
			SetMouseWheel( _tcscmp( pstrValue, _T("true") )  == 0  );
		}
		else if ( _tcscmp(pstrName, _T("iskeepimageheight")) == 0)
		{
			SetIsKeepImageHeight( _tcscmp( pstrValue, _T("true") )  == 0  );
		}
		else if( _tcscmp(pstrName, _T("width")) == 0 ) SetFixedWidth(_ttoi(pstrValue));
		else CProgressUI::SetAttribute(pstrName, pstrValue);
	}

	void CSliderUI::PaintBkImage(HDC hDC)//重新计算位置大小 dyy
	{
		if (!m_bIsKeepImageHeight)
		{
			CControlUI::PaintBkImage(hDC);
			return;
		}
		//背景滑条从滑块中心开始
		if( m_sBkImage.IsEmpty() ) return;

		CDuiString sBkImageModify;
		sBkImageModify.Empty();

		RECT rc = {0};
		if( m_bHorizontal ) 
		{
			rc.right = (long long) (m_rcItem.right - (m_szThumb.cx/2) - m_rcItem.left);
			rc.left = (long long) m_szThumb.cx/2;

			//滑动条高度由图片决定 
			const TImageInfo* data = NULL;
			data = m_pManager->GetImageEx((LPCTSTR)m_sBkImage, NULL, 0); 
			rc.top = (m_rcItem.bottom - data->nY - m_rcItem.top)/2;
			rc.bottom = data->nY + rc.top;
		}

		sBkImageModify.SmallFormat(_T("Dest='%d,%d,%d,%d'"), rc.left, rc.top, rc.right, rc.bottom);

		if( !DrawImage(hDC, (LPCTSTR)m_sBkImage, (LPCTSTR)sBkImageModify) ) m_sBkImage.Empty();
		//if( !DrawImage(hDC, (LPCTSTR)m_sBkImage) ) m_sBkImage.Empty();
	}

	void CSliderUI::PaintStatusImage(HDC hDC)
	{
		//CProgressUI::PaintStatusImage(hDC);
		if( m_nMax <= m_nMin ) m_nMax = m_nMin + 1;
		if( m_nValue > m_nMax ) m_nValue = m_nMax;
		if( m_nValue < m_nMin ) m_nValue = m_nMin;

		RECT rc = {0};
		if( m_bHorizontal ) 
		{
			if (m_bIsKeepImageHeight)
			{
				rc.right =  (( (long long)(m_nValue - m_nMin) )  * (m_rcItem.right - m_rcItem.left - m_szThumb.cx) / (m_nMax - m_nMin)) + m_szThumb.cx / 2;
				rc.left = (long long) m_szThumb.cx/4;
				//滑动条高度由图片决定 
				const TImageInfo* data = NULL;
				data = m_pManager->GetImageEx((LPCTSTR)m_sForeImage, NULL, 0); 
				rc.top = (m_rcItem.bottom - data->nY - m_rcItem.top)/2;
				rc.bottom = data->nY + rc.top;
			}
			else
			{
				rc.right =  ( (long long)(m_nValue - m_nMin) ) * (m_rcItem.right - m_rcItem.left) / (m_nMax - m_nMin);
				rc.bottom = m_rcItem.bottom - m_rcItem.top;
			}
		}
		else {
			rc.top =  ( (long long)(m_rcItem.bottom - m_rcItem.top) ) * ( m_nMax - m_nValue ) / (m_nMax - m_nMin);
			rc.right = m_rcItem.right - m_rcItem.left;
			rc.bottom = m_rcItem.bottom - m_rcItem.top;
		}

		if( !m_sForeImage.IsEmpty() ) {
			m_sForeImageModify.Empty();
			if (m_bStretchForeImage)
				m_sForeImageModify.SmallFormat(_T("Dest='%d,%d,%d,%d'"), rc.left, rc.top, rc.right, rc.bottom);
			else
				m_sForeImageModify.SmallFormat(_T("Dest='%d,%d,%d,%d' source='%d,%d,%d,%d'")
				, rc.left, rc.top, rc.right, rc.bottom
				, rc.left, rc.top, rc.right, rc.bottom);

			if( !DrawImage(hDC, (LPCTSTR)m_sForeImage, (LPCTSTR)m_sForeImageModify) ) m_sForeImage.Empty();
			//else return;
		}

		RECT rcThumb = GetThumbRect();
		rcThumb.left = rcThumb.left - m_rcItem.left;
		if (rcThumb.top > m_rcItem.top)
		{
			rcThumb.top -= m_rcItem.top;
		}
		else
		{
			rcThumb.top = m_rcItem.top - rcThumb.top;
		}
		rcThumb.bottom -= m_rcItem.top;
		rcThumb.right -= m_rcItem.left;
		
		if( (m_uButtonState & UISTATE_CAPTURED) != 0 ) {
			if( !m_sThumbPushedImage.IsEmpty() ) {
				m_sImageModify.Empty();
				m_sImageModify.SmallFormat(_T("Dest='%d,%d,%d,%d'"), rcThumb.left, rcThumb.top, rcThumb.right, rcThumb.bottom);
				if( !DrawImage(hDC, (LPCTSTR)m_sThumbPushedImage, (LPCTSTR)m_sImageModify) ) m_sThumbPushedImage.Empty();
				else return;
			}
		}
		else if( (m_uButtonState & UISTATE_HOT) != 0 ) {
			if( !m_sThumbHotImage.IsEmpty() ) {
				m_sImageModify.Empty();
				m_sImageModify.SmallFormat(_T("Dest='%d,%d,%d,%d'"), rcThumb.left, rcThumb.top, rcThumb.right, rcThumb.bottom);
				if( !DrawImage(hDC, (LPCTSTR)m_sThumbHotImage, (LPCTSTR)m_sImageModify) ) m_sThumbHotImage.Empty();
				else return;
			}
		}

		if( !m_sThumbImage.IsEmpty() ) {
			m_sImageModify.Empty();
			m_sImageModify.SmallFormat(_T("Dest='%d,%d,%d,%d'"), rcThumb.left, rcThumb.top, rcThumb.right, rcThumb.bottom);
			if( !DrawImage(hDC, (LPCTSTR)m_sThumbImage, (LPCTSTR)m_sImageModify) ) m_sThumbImage.Empty();
			else return;
		}
	}

	void CSliderUI::SetValue(int nValue)
	{
		// 当鼠标拖拽的时候，不设置值
		if ( (m_uButtonState & UISTATE_CAPTURED) == 0 )
		{
			CProgressUI::SetValue(nValue);
		}
	}

	void CSliderUI::SetMouseWheel(bool bMouseWheel)
	{
		m_bIsMouseWheel = bMouseWheel;
	}

	bool CSliderUI::GetIsMouseWheel()
	{
		return m_bIsMouseWheel;
	}

	void CSliderUI::SetIsKeepImageHeight( bool bIsKeepImageHeight )
	{
		m_bIsKeepImageHeight = bIsKeepImageHeight;
	}

	bool CSliderUI::GetIsKeepImageHeight()
	{
		return m_bIsKeepImageHeight;
	}

}
