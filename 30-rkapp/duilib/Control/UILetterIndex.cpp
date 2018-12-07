#include "stdafx.h"
#include "UILetterIndex.h"

namespace DuiLib
{
	#define LETTER_HEIGHT  30
	#define LETTER_NUM     27

	CLetterIndexUI::CLetterIndexUI(void) : m_uButtonState(0), m_nClickLetter(0)
	{
		m_fLetterHeight = LETTER_HEIGHT;
		if ( CPaintManagerUI::IsSelfAdaption() )
		{
			float fAdpX, fAdpY;
			CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
			m_fLetterHeight = m_fLetterHeight * fAdpY;
		}

		m_uTextStyle &= ~( DT_LEFT | DT_RIGHT | DT_TOP | DT_BOTTOM );			
		m_uTextStyle |= (DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}


	CLetterIndexUI::~CLetterIndexUI(void)
	{
	}

	LPCTSTR CLetterIndexUI::GetClass() const
	{
		return _T("LetterIndexUI");
	}

	LPVOID CLetterIndexUI::GetInterface(LPCTSTR pstrName)
	{
		if( _tcscmp(pstrName, DUI_CTR_LETTERINDEX) == 0 ) 
			return static_cast<CLetterIndexUI*>(this);
		return CLabelUI::GetInterface(pstrName);
	}


	void CLetterIndexUI::DoEvent(TEventUI& event)
	{
		if( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
			if( m_pParent != NULL ) m_pParent->DoEvent(event);
			else CControlUI::DoEvent(event);
			return;
		}

		if( event.Type == UIEVENT_SETFOCUS ) 
		{
			Invalidate();
		}
		if( event.Type == UIEVENT_KILLFOCUS ) 
		{
			Invalidate();
		}
		if( event.Type == UIEVENT_BUTTONDOWN || event.Type == UIEVENT_DBLCLICK )
		{
			if( ::PtInRect(&m_rcItem, event.ptMouse) && IsEnabled() ) 
			{
				int nLetterIndex = GetClickLetter(event.ptMouse);
				m_uButtonState |= UISTATE_PUSHED | UISTATE_CAPTURED;
				
				if( m_pManager != NULL )
				{
					m_pManager->SendNotify(this, DUI_MSGTYPE_LETTERINDEX_CLICK, nLetterIndex, NULL);
				}
				
				Invalidate();
			}
			return;
		}
		if( event.Type == UIEVENT_MOUSEMOVE )
		{
			if( (m_uButtonState & UISTATE_CAPTURED) != 0 ) {
				if( ::PtInRect(&m_rcItem, event.ptMouse) ){
					m_uButtonState |= UISTATE_PUSHED;
					GetClickLetter(event.ptMouse);
				}
				else { 
					m_uButtonState &= ~UISTATE_PUSHED;
				}
				Invalidate();
			}
			return;
		}
		if( event.Type == UIEVENT_BUTTONUP )
		{
			if( (m_uButtonState & UISTATE_CAPTURED) != 0 ) {
				if( ::PtInRect(&m_rcItem, event.ptMouse) ) 
					Activate();
				m_uButtonState &= ~(UISTATE_PUSHED | UISTATE_CAPTURED);
				Invalidate();
			}
			return;
		}

		CLabelUI::DoEvent(event);
	}

	int CLetterIndexUI::GetClickLetter( POINT point )
	{
		POINT ptDown;
		ptDown.x = point.x - m_rcItem.left;
		ptDown.y = point.y - m_rcItem.top;
		m_nClickLetter = int(ptDown.y / m_fLetterHeight);
		if ( m_nClickLetter >= LETTER_NUM )
		{
			m_nClickLetter = LETTER_NUM - 1;
		}

		if ( m_nClickLetter == 0 )
		{
			m_sText = _T("#");
		}
		else
		{
			char chText = 'A' + m_nClickLetter - 1;
			char achText[2] = {0};
			strncpy( achText, &chText, sizeof(chText) );
			m_sText = CA2T(achText);
		}
		
		return m_nClickLetter;
	}

	void CLetterIndexUI::PaintText(HDC hDC)
	{
		if( IsFocused() ) m_uButtonState |= UISTATE_FOCUSED;
		else m_uButtonState &= ~ UISTATE_FOCUSED;

		if( m_dwTextColor == 0 ) 
			m_dwTextColor = m_pManager->GetDefaultFontColor();

		if( (m_uButtonState & UISTATE_PUSHED) == 0 ) 
			return;
		if ( !IsEnabled() ) 
			return;

		RECT rc = m_rcItem;

		rc.top = m_rcItem.top + LONG(m_nClickLetter * m_fLetterHeight);
		rc.bottom = LONG(rc.top + m_fLetterHeight);
	
		CRenderEngine::DrawTextByGdiPlus(hDC, m_pManager, rc, m_sText, m_dwTextColor, \
			m_iFont, m_uTextStyle);

	}

}