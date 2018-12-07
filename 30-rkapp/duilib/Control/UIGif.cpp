#include "stdafx.h"

namespace DuiLib
{
	CGifUI::CGifUI()
		:m_pGifImg(NULL)
		,m_nPreUpdateDelay(0)
		,m_isUpdateTime(false)
		,m_strGifFile(_T(""))
	{
	}

	CGifUI::~CGifUI()
	{
		m_pManager->KillTimer(this, GIF_TIMER_ID);
		if (m_pGifImg)
		{
			delete m_pGifImg;
			m_pGifImg = NULL;
		}
	}

	void CGifUI::SetVisible( bool bVisible /*= true*/ )
	{
		if(m_pManager)
		{
			if(bVisible)
			{
				if(m_pGifImg)
				{
					int nPos = m_pGifImg->GetCurFramePos();
					m_pManager->KillTimer(this, GIF_TIMER_ID);
					m_pManager->SetTimer(this, GIF_TIMER_ID, m_pGifImg->GetFrameDelay(nPos));
				
				}
			}
			else
			{
				m_pManager->KillTimer(this);
			}
		}
		CControlUI::SetVisible(bVisible);
	}

	void CGifUI::PaintStatusImage( HDC hDC )
	{
		if(m_pGifImg)
		{
			if (m_isUpdateTime)
			{
				m_isUpdateTime = false;
				m_pGifImg->ActiveNextFrame();
			}
			int nPos = m_pGifImg->GetCurFramePos();
			RECT rc;
			rc.left = this->GetX();
			rc.top = this->GetY();
			rc.right = this->GetX() + this->GetWidth();
			rc.bottom = this->GetY() + this->GetHeight();
			m_pGifImg->Draw( hDC, rc, nPos );
			if (m_nPreUpdateDelay != m_pGifImg->GetFrameDelay(nPos))
			{
				m_pManager->KillTimer(this, GIF_TIMER_ID);
				m_pManager->SetTimer(this, GIF_TIMER_ID, m_pGifImg->GetFrameDelay(nPos) );
				m_nPreUpdateDelay = m_pGifImg->GetFrameDelay(nPos);
			}
		}
	}

	void CGifUI::DoEvent( TEventUI& event )
	{
		if( event.Type == UIEVENT_TIMER && event.wParam == GIF_TIMER_ID )
		{
			m_isUpdateTime = true;
			Invalidate();
			return;
		}
		CControlUI::DoEvent(event);
	}

	void CGifUI::SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue )
	{
		if( _tcscmp(pstrName, _T("gif")) == 0 )
		{
			SetGifFile(pstrValue);
		}
		CControlUI::SetAttribute(pstrName,pstrValue);
	}

	void CGifUI::SetGifFile( LPCTSTR pstrName )
	{
		if(pstrName == m_strGifFile || pstrName == NULL) return;
		m_strGifFile = pstrName;
		if (m_pGifImg)
		{
			m_pManager->KillTimer(this, GIF_TIMER_ID);
			m_nPreUpdateDelay = 0;
			delete m_pGifImg;
			m_pGifImg = NULL;
		}
		m_pGifImg = CRenderEngine::LoadGif(STRINGorID(pstrName),0, 0);
		Invalidate();
	}

	void CGifUI::DoInit()
	{
	}

	LPCTSTR CGifUI::GetGifFile()
	{
		return m_strGifFile;
	}

}