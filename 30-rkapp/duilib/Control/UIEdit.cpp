#include "stdafx.h"
#include "UIEdit.h"

namespace DuiLib
{
	class CEditWnd : public CWindowWnd
	{
	public:
		CEditWnd();

		void Init(CEditUI* pOwner);
		RECT CalPos();

		LPCTSTR GetWindowClassName() const;
		LPCTSTR GetSuperClassName() const;
		void OnFinalMessage(HWND hWnd);

		LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnEditChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	protected:
		CEditUI* m_pOwner;
		HBRUSH m_hBkBrush;
		bool m_bInit;
	};


	CEditWnd::CEditWnd() : m_pOwner(NULL), m_hBkBrush(NULL), m_bInit(false)
	{
	}

	void CEditWnd::Init(CEditUI* pOwner)
	{
		m_pOwner = pOwner;
		RECT rcPos = CalPos();
		//UINT uStyle = WS_CHILD | ES_AUTOHSCROLL;

        UINT uStyle = WS_POPUP | ES_AUTOHSCROLL | WS_VISIBLE;
        RECT rcWnd={0};
        ::GetWindowRect(m_pOwner->GetManager()->GetPaintWindow(), &rcWnd);
        rcPos.left += rcWnd.left;
        rcPos.right += rcWnd.left;
        rcPos.top += rcWnd.top;
        rcPos.bottom += rcWnd.top;

		if( m_pOwner->IsPasswordMode() ) uStyle |= ES_PASSWORD;
		Create(m_pOwner->GetManager()->GetPaintWindow(), NULL, uStyle, 0, rcPos);
		HFONT hFont=NULL;
		int iFontIndex=m_pOwner->GetFont();
		if (iFontIndex!=-1)
			hFont=m_pOwner->GetManager()->GetFont(iFontIndex);
		if (hFont==NULL)
			hFont=m_pOwner->GetManager()->GetDefaultFontInfo()->hFont;

		SetWindowFont(m_hWnd, hFont, TRUE);
		Edit_LimitText(m_hWnd, m_pOwner->GetMaxChar());
		if( m_pOwner->IsPasswordMode() ) Edit_SetPasswordChar(m_hWnd, m_pOwner->GetPasswordChar());
		Edit_SetText(m_hWnd, m_pOwner->GetText());
		Edit_SetModify(m_hWnd, FALSE);
		SendMessage(EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN, MAKELPARAM(0, 0));
		Edit_Enable(m_hWnd, m_pOwner->IsEnabled() == true);
		Edit_SetReadOnly(m_hWnd, m_pOwner->IsReadOnly() == true);
		//Styls
		LONG styleValue = ::GetWindowLong(m_hWnd, GWL_STYLE);
		styleValue |= pOwner->GetWindowStyls();
		::SetWindowLong(GetHWND(), GWL_STYLE, styleValue);
		::ShowWindow(m_hWnd, SW_SHOWNOACTIVATE);
		::SetFocus(m_hWnd);
		m_bInit = true;    
	}

	RECT CEditWnd::CalPos()
	{
		CDuiRect rcPos = m_pOwner->GetPos();
		RECT rcInset = m_pOwner->GetTextPadding();
		rcPos.left += rcInset.left;
		rcPos.top += rcInset.top;
		rcPos.right -= rcInset.right;
		rcPos.bottom -= rcInset.bottom;
		LONG lEditHeight = m_pOwner->GetManager()->GetFontInfo(m_pOwner->GetFont())->tm.tmHeight;
		//由于字体设置后font大小不变 此处不进行自适应 直接用lEditHeight
		if( lEditHeight < rcPos.GetHeight() ) {
			rcPos.top += (rcPos.GetHeight() - lEditHeight) / 2;
			rcPos.bottom = rcPos.top + lEditHeight;
		}
		return rcPos;
	}

	LPCTSTR CEditWnd::GetWindowClassName() const
	{
		return _T("EditWnd");
	}

	LPCTSTR CEditWnd::GetSuperClassName() const
	{
		return WC_EDIT;
	}

	void CEditWnd::OnFinalMessage(HWND /*hWnd*/)
	{
		m_pOwner->Invalidate();
		// Clear reference and die
		if( m_hBkBrush != NULL ) ::DeleteObject(m_hBkBrush);
		m_pOwner->m_pWindow = NULL;
		delete this;
	}

	LRESULT CEditWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lRes = 0;
		BOOL bHandled = TRUE;
		if( uMsg == WM_KILLFOCUS ) lRes = OnKillFocus(uMsg, wParam, lParam, bHandled);
		else if( uMsg == OCM_COMMAND ) {
			if( GET_WM_COMMAND_CMD(wParam, lParam) == EN_CHANGE ) lRes = OnEditChanged(uMsg, wParam, lParam, bHandled);
			else if( GET_WM_COMMAND_CMD(wParam, lParam) == EN_UPDATE ) {
				RECT rcClient;
				::GetClientRect(m_hWnd, &rcClient);
				::InvalidateRect(m_hWnd, &rcClient, FALSE);
			}
		}
		else if( uMsg == WM_KEYDOWN /*&& TCHAR(wParam) == VK_RETURN*/ ) {         
            if(TCHAR(wParam) == VK_RETURN)  
            {
                m_pOwner->GetManager()->SendNotify(m_pOwner, DUI_MSGTYPE_RETURN);
            }  
            else if(TCHAR(wParam) == VK_TAB)
            {
                m_pOwner->GetManager()->SetNextTabControl(::GetKeyState(VK_SHIFT) >= 0);  
            }
		}
		else if( uMsg == OCM__BASE + WM_CTLCOLOREDIT  || uMsg == OCM__BASE + WM_CTLCOLORSTATIC ) {
			if( m_pOwner->GetNativeEditBkColor() == 0xFFFFFFFF ) return NULL;
			::SetBkMode((HDC)wParam, TRANSPARENT);
			DWORD dwTextColor = m_pOwner->GetTextColor();
			::SetTextColor((HDC)wParam, RGB(GetBValue(dwTextColor),GetGValue(dwTextColor),GetRValue(dwTextColor)));
			if( m_hBkBrush == NULL ) {
				DWORD clrColor = m_pOwner->GetNativeEditBkColor();
				m_hBkBrush = ::CreateSolidBrush(RGB(GetBValue(clrColor), GetGValue(clrColor), GetRValue(clrColor)));
                //m_hBkBrush = ::CreateSolidBrush(clrColor);
                //m_hBkBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);         
			}
			return (LRESULT)m_hBkBrush;
		}
        else if ( uMsg == WM_LBUTTONDOWN )
        {
            if ( !m_pOwner->IsPasswordMode() )//非密码框再次点击在这里响应
            {
                ::PostMessage( m_pOwner->GetManager()->GetPaintWindow(), WM_DUI_EDITSETFOCUS, 0, 0 );
            }        
            bHandled = FALSE;
        }/*
        else if ( uMsg == WM_PAINT )
        {
            HDC hDC = ::GetDC(m_hWnd);
            DWORD clrColor = m_pOwner->GetNativeEditBkColor();
            RECT rcClient;
            ::GetClientRect(m_hWnd, &rcClient);
            CRenderEngine::DrawColor( hDC, rcClient, clrColor);

            ::ReleaseDC(m_hWnd, hDC);

            bHandled = FALSE;
        }*/
        else if ( uMsg == WM_COPY && m_pOwner->IsPasswordMode() == false)
        {
            if ( m_pOwner->IsAllowedCopy() == true )
            {
                bHandled = FALSE;
            }
        }
		else bHandled = FALSE;
		if( !bHandled ) return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
		return lRes;
	}

	LRESULT CEditWnd::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRes = ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
		PostMessage(WM_CLOSE);
		return lRes;
	}

	LRESULT CEditWnd::OnEditChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if( !m_bInit ) return 0;
		if( m_pOwner == NULL ) return 0;
		// Copy text back
		int cchLen = ::GetWindowTextLength(m_hWnd) + 1;
		LPTSTR pstr = static_cast<LPTSTR>(_alloca(cchLen * sizeof(TCHAR)));
		ASSERT(pstr);
		if( pstr == NULL ) return 0;
		::GetWindowText(m_hWnd, pstr, cchLen);

		//限制字节数而不是字符数 dyy 2015-5-19
		USES_CONVERSION;
		std::string str;
		str = W2A(pstr);
		int nbyte= str.size();

//失去焦点会重新设置 只针对一直输入的可控 dyy 2015-5-20
		if (nbyte > m_pOwner->GetMaxChar() - 2)
		{
			if (nbyte < m_pOwner->GetMaxChar())
			{
				Edit_LimitText(m_hWnd, cchLen);
			}

			if (nbyte == m_pOwner->GetMaxChar())
			{
				Edit_LimitText(m_hWnd, cchLen - 1);
			}
		}
		else
		{
			if (nbyte < m_pOwner->GetMaxChar())
			{
				Edit_LimitText(m_hWnd, m_pOwner->GetMaxChar());
			}
		}

		if (nbyte > m_pOwner->GetMaxChar())
		{
			//Edit_SetText(m_hWnd, m_pOwner->GetText());
			Edit_Undo(m_hWnd);
			m_pOwner->Invalidate();
			return 0;
		}

        if (m_pOwner->GetNumberStyle() == MENU_HEX_STYLE)//十六进制
        {
            if (str.size() > 0)
            {
                char c = str[str.size() - 1];
                if (c < '0' || (c > '9' && c < 'A') || (c > 'F' && c < 'a') || c > 'f' )
                {
                    Edit_Undo(m_hWnd);
                    m_pOwner->Invalidate();
                    return 0;
                }
            }
        }
        else if (m_pOwner->GetNumberStyle() == MENU_IP_STYLE)//IP
        {
            if (str.size() > 0)
            {
                char c = str[str.size() - 1];
                if ((c < '0' || c > '9') && c != '.' )
                {
                    Edit_Undo(m_hWnd);
                    m_pOwner->Invalidate();
                    return 0;
                }
            }
        }

		Edit_EmptyUndoBuffer(m_hWnd);

		m_pOwner->m_sText = pstr;

		if ( CPaintManagerUI::IsSelfAdaption() )
		{
			m_pOwner->Invalidate();
		}
		m_pOwner->GetManager()->SendNotify(m_pOwner, DUI_MSGTYPE_TEXTCHANGED);

		return 0;
	}


	/////////////////////////////////////////////////////////////////////////////////////
	//
	//

	CEditUI::CEditUI() : m_pWindow(NULL), m_uMaxChar(255), m_bReadOnly(false),
		m_bAllowedCopy(true),m_bPasswordMode(false), m_cPasswordChar(_T('*')),
		m_uButtonState(0), m_dwEditbkColor(0xFFFFFFFF), m_iWindowStyls(0),
        m_dwTipTextColor(0), m_uNumberStyle(MENU_NO_STYLE)
	{
		SetTextPadding(CDuiRect(4, 3, 4, 3));
		//SetBkColor(0xFFFFFFFF);
	}

	LPCTSTR CEditUI::GetClass() const
	{
		return _T("EditUI");
	}

	LPVOID CEditUI::GetInterface(LPCTSTR pstrName)
	{
		if( _tcscmp(pstrName, DUI_CTR_EDIT) == 0 ) return static_cast<CEditUI*>(this);
		return CLabelUI::GetInterface(pstrName);
	}

	UINT CEditUI::GetControlFlags() const
	{
		if( !IsEnabled() ) return CControlUI::GetControlFlags();

		return UIFLAG_SETCURSOR | UIFLAG_TABSTOP;
	}

	void CEditUI::DoEvent(TEventUI& event)
	{
		if( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
			if( m_pParent != NULL ) m_pParent->DoEvent(event);
			else CLabelUI::DoEvent(event);
			return;
		}

		if( event.Type == UIEVENT_SETCURSOR && IsEnabled() )
		{
			::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_IBEAM)));
			return;
		}
		if( event.Type == UIEVENT_WINDOWSIZE )
		{
			if( m_pWindow != NULL ) m_pManager->SetFocusNeeded(this);
		}
		if( event.Type == UIEVENT_SCROLLWHEEL )
		{
			if( m_pWindow != NULL ) return;
		}
		if( event.Type == UIEVENT_SETFOCUS && IsEnabled() ) 
		{
            //if( m_pManager != NULL )
            //    ::PostMessage( m_pManager->GetPaintWindow(), WM_DUI_EDITSETFOCUS, 0, 0 );

			if( m_pWindow ) return;
			m_pWindow = new CEditWnd();
			ASSERT(m_pWindow);
			m_pWindow->Init(this);
			Invalidate();
		}
		if( event.Type == UIEVENT_KILLFOCUS && IsEnabled() ) 
		{
			Invalidate();
		}
		if( event.Type == UIEVENT_BUTTONDOWN || event.Type == UIEVENT_DBLCLICK || event.Type == UIEVENT_RBUTTONDOWN) 
		{
			if( IsEnabled() ) {
				GetManager()->ReleaseCapture();

                if( m_pManager != NULL && !m_bPasswordMode )
                    ::PostMessage( m_pManager->GetPaintWindow(), WM_DUI_EDITSETFOCUS, 0, 0 );

				if( IsFocused() && m_pWindow == NULL )
				{
					m_pWindow = new CEditWnd();
					ASSERT(m_pWindow);
					m_pWindow->Init(this);

					if( PtInRect(&m_rcItem, event.ptMouse) )
					{
						int nSize = GetWindowTextLength(*m_pWindow);
						if( nSize == 0 )
							nSize = 1;

						Edit_SetSel(*m_pWindow, 0, nSize);
					}
				}
				else if( m_pWindow != NULL )
				{
#if 1
					int nSize = GetWindowTextLength(*m_pWindow);
					if( nSize == 0 )
						nSize = 1;

					Edit_SetSel(*m_pWindow, 0, nSize);
#else
					POINT pt = event.ptMouse;
					pt.x -= m_rcItem.left + m_rcTextPadding.left;
					pt.y -= m_rcItem.top + m_rcTextPadding.top;
					::SendMessage(*m_pWindow, WM_LBUTTONDOWN, event.wParam, MAKELPARAM(pt.x, pt.y));
#endif
				}
			}
			return;
		}
		if( event.Type == UIEVENT_MOUSEMOVE ) 
		{
			return;
		}
		if( event.Type == UIEVENT_BUTTONUP ) 
		{
			return;
		}
		if( event.Type == UIEVENT_CONTEXTMENU )
		{
			return;
		}
		if( event.Type == UIEVENT_MOUSEENTER )
		{
			if( IsEnabled() ) {
				m_uButtonState |= UISTATE_HOT;
				Invalidate();
			}
			return;
		}
		if( event.Type == UIEVENT_MOUSELEAVE )
		{
			if( IsEnabled() ) {
				m_uButtonState &= ~UISTATE_HOT;
				Invalidate();
			}
			return;
		}
		CLabelUI::DoEvent(event);
	}

	void CEditUI::SetEnabled(bool bEnable)
	{
		CControlUI::SetEnabled(bEnable);
		if( !IsEnabled() ) {
			m_uButtonState = 0;
		}
	}

	void CEditUI::SetText(LPCTSTR pstrText)
	{
		m_sText = pstrText;
		if( m_pWindow != NULL ) Edit_SetText(*m_pWindow, m_sText);
		Invalidate();
	}

	void CEditUI::SetMaxChar(UINT uMax)
	{
		m_uMaxChar = uMax;
		if( m_pWindow != NULL ) Edit_LimitText(*m_pWindow, m_uMaxChar);
	}

	UINT CEditUI::GetMaxChar()
	{
		return m_uMaxChar;
	}

	void CEditUI::SetReadOnly(bool bReadOnly)
	{
		if( m_bReadOnly == bReadOnly ) return;

		m_bReadOnly = bReadOnly;
		if( m_pWindow != NULL ) Edit_SetReadOnly(*m_pWindow, m_bReadOnly);
		Invalidate();
	}

	bool CEditUI::IsReadOnly() const
	{
		return m_bReadOnly;
	}

	void CEditUI::SetNumberOnly(bool bNumberOnly)
	{
		if( bNumberOnly )
		{
			m_iWindowStyls |= ES_NUMBER;
		}
		else
		{
			m_iWindowStyls |= ~ES_NUMBER;
		}
	}

	bool CEditUI::IsNumberOnly() const
	{
		return m_iWindowStyls&ES_NUMBER ? true:false;
	}

    void CEditUI::SetNumberStyle(UINT uType)
    {
        m_uNumberStyle = uType;
    }

    UINT CEditUI::GetNumberStyle() const
    {
        return m_uNumberStyle;
    }

	int CEditUI::GetWindowStyls() const 
	{
		return m_iWindowStyls;
	}

    void CEditUI::SetTipTextColor(DWORD dwTextColor)
    {
        m_dwTipTextColor = dwTextColor;
        Invalidate();
    }

    DWORD CEditUI::GetTipTextColor() const
    {
        return m_dwTipTextColor;
    }

    void CEditUI::SetAllowedCopy(bool bAllowedCopy)
    {
        if( m_bAllowedCopy == bAllowedCopy ) return;
        m_bAllowedCopy = bAllowedCopy;
        Invalidate();
    }

    bool CEditUI::IsAllowedCopy() const
    {
        return m_bAllowedCopy;
    }

	void CEditUI::SetPasswordMode(bool bPasswordMode)
	{
		if( m_bPasswordMode == bPasswordMode ) return;
		m_bPasswordMode = bPasswordMode;
		Invalidate();
	}

	bool CEditUI::IsPasswordMode() const
	{
		return m_bPasswordMode;
	}

	void CEditUI::SetPasswordChar(TCHAR cPasswordChar)
	{
		if( m_cPasswordChar == cPasswordChar ) return;
		m_cPasswordChar = cPasswordChar;
		if( m_pWindow != NULL ) Edit_SetPasswordChar(*m_pWindow, m_cPasswordChar);
		Invalidate();
	}

	TCHAR CEditUI::GetPasswordChar() const
	{
		return m_cPasswordChar;
	}

	LPCTSTR CEditUI::GetNormalImage()
	{
		return m_sNormalImage;
	}

	void CEditUI::SetNormalImage(LPCTSTR pStrImage)
	{
		m_sNormalImage = pStrImage;
		Invalidate();
	}

	LPCTSTR CEditUI::GetHotImage()
	{
		return m_sHotImage;
	}

	void CEditUI::SetHotImage(LPCTSTR pStrImage)
	{
		m_sHotImage = pStrImage;
		Invalidate();
	}

	LPCTSTR CEditUI::GetFocusedImage()
	{
		return m_sFocusedImage;
	}

	void CEditUI::SetFocusedImage(LPCTSTR pStrImage)
	{
		m_sFocusedImage = pStrImage;
		Invalidate();
	}

	LPCTSTR CEditUI::GetDisabledImage()
	{
		return m_sDisabledImage;
	}

	void CEditUI::SetDisabledImage(LPCTSTR pStrImage)
	{
		m_sDisabledImage = pStrImage;
		Invalidate();
	}

	void CEditUI::SetNativeEditBkColor(DWORD dwBkColor)
	{
		m_dwEditbkColor = dwBkColor;
	}

	DWORD CEditUI::GetNativeEditBkColor() const
	{
		return m_dwEditbkColor;
	}

	void CEditUI::SetSel(long nStartChar, long nEndChar)
	{
		if( m_pWindow != NULL ) Edit_SetSel(*m_pWindow, nStartChar,nEndChar);
	}

	void CEditUI::SetSelAll()
	{
		SetSel(0,-1);
	}

	void CEditUI::SetReplaceSel(LPCTSTR lpszReplace)
	{
		if( m_pWindow != NULL ) Edit_ReplaceSel(*m_pWindow, lpszReplace);
	}

	void CEditUI::SetPos(RECT rc)
	{
		CControlUI::SetPos(rc);
		if( m_pWindow != NULL ) {
			RECT rcPos = m_pWindow->CalPos();
            RECT rcWnd={0};
            ::GetWindowRect(GetManager()->GetPaintWindow(), &rcWnd);
            rcPos.left += rcWnd.left;
            rcPos.right += rcWnd.left;
            rcPos.top += rcWnd.top;
            rcPos.bottom += rcWnd.top;
			::SetWindowPos(m_pWindow->GetHWND(), NULL, rcPos.left, rcPos.top, rcPos.right - rcPos.left, 
				rcPos.bottom - rcPos.top, SWP_NOZORDER | SWP_NOACTIVATE);        
		}
	}

	void CEditUI::SetVisible(bool bVisible)
	{
		CControlUI::SetVisible(bVisible);
		if( !IsVisible() && m_pWindow != NULL ) m_pManager->SetFocus(NULL);
	}

	void CEditUI::SetInternVisible(bool bVisible)
	{
		if( !IsVisible() && m_pWindow != NULL ) m_pManager->SetFocus(NULL);
	}

	SIZE CEditUI::EstimateSize(SIZE szAvailable)
	{
		if( m_cxyFixed.cy == 0 ) return CDuiSize(m_cxyFixed.cx, m_pManager->GetFontInfo(GetFont())->tm.tmHeight + 6);
		return CControlUI::EstimateSize(szAvailable);
	}

	CDuiString CEditUI::GetTipText() const
	{
		return m_sTipText;
	}

	void CEditUI::SetTipText(LPCTSTR pstrText)
	{
		CDuiString strTemp(pstrText);
		strTemp.Replace(_T("<n>"),_T("\r\n"));
		m_sTipText=strTemp;
	}

	void CEditUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		if( _tcscmp(pstrName, _T("readonly")) == 0 ) SetReadOnly(_tcscmp(pstrValue, _T("true")) == 0);
		else if( _tcscmp(pstrName, _T("numberonly")) == 0 ) SetNumberOnly(_tcscmp(pstrValue, _T("true")) == 0);
        else if( _tcscmp(pstrName, _T("numberstyle")) == 0 ) SetNumberStyle(_ttoi(pstrValue));
        else if( _tcscmp(pstrName, _T("allowedcopy")) == 0 ) SetAllowedCopy(_tcscmp(pstrValue, _T("true")) == 0);
		else if( _tcscmp(pstrName, _T("password")) == 0 ) SetPasswordMode(_tcscmp(pstrValue, _T("true")) == 0);
		else if( _tcscmp(pstrName, _T("maxchar")) == 0 ) SetMaxChar(_ttoi(pstrValue));
		else if( _tcscmp(pstrName, _T("normalimage")) == 0 ) SetNormalImage(pstrValue);
		else if( _tcscmp(pstrName, _T("hotimage")) == 0 ) SetHotImage(pstrValue);
		else if( _tcscmp(pstrName, _T("focusedimage")) == 0 ) SetFocusedImage(pstrValue);
		else if( _tcscmp(pstrName, _T("disabledimage")) == 0 ) SetDisabledImage(pstrValue);
		else if( _tcscmp(pstrName, _T("tiptext")) == 0 ) SetTipText(pstrValue);
		else if( _tcscmp(pstrName, _T("nativebkcolor")) == 0 ) {
			if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
			LPTSTR pstr = NULL;
			DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
			SetNativeEditBkColor(clrColor);
		}
        else if( _tcscmp(pstrName, _T("tiptextcolor")) == 0 ) {
            if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
            LPTSTR pstr = NULL;
            DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
            SetTipTextColor(clrColor);
        }
		else CLabelUI::SetAttribute(pstrName, pstrValue);
	}

	void CEditUI::PaintStatusImage(HDC hDC)
	{
		if( IsFocused() ) m_uButtonState |= UISTATE_FOCUSED;
		else m_uButtonState &= ~ UISTATE_FOCUSED;
		if( !IsEnabled() ) m_uButtonState |= UISTATE_DISABLED;
		else m_uButtonState &= ~ UISTATE_DISABLED;

		if ( !m_sMosImgFolder.IsEmpty() )
		{
			if((m_uButtonState & UISTATE_DISABLED) != 0 ) 
			{
				DrawMosaicImage(hDC, UISTATE_DISABLED);
				return;
			}
			else if (((m_uButtonState & UISTATE_FOCUSED) != 0 ) )
			{
				DrawMosaicImage(hDC, UISTATE_FOCUSED);
				return;
			}
			else if (((m_uButtonState & UISTATE_HOT) != 0 ) ) 
			{
				DrawMosaicImage(hDC, UISTATE_HOT);
				return;
			}

			DrawMosaicImage(hDC);
			return;
		}
		else if( (m_uButtonState & UISTATE_DISABLED) != 0 ) {
			if( !m_sDisabledImage.IsEmpty() ) {
				if( !DrawImage(hDC, (LPCTSTR)m_sDisabledImage)) m_sDisabledImage.Empty();
				else return;
			}
		}
		else if( (m_uButtonState & UISTATE_FOCUSED) != 0 ) {
			if( !m_sFocusedImage.IsEmpty() ) {
				if( !DrawImage(hDC, (LPCTSTR)m_sFocusedImage)) m_sFocusedImage.Empty();
				else return;
			}
		}
		else if( (m_uButtonState & UISTATE_HOT) != 0 ) {
			if( !m_sHotImage.IsEmpty() ) {
				if( !DrawImage(hDC, (LPCTSTR)m_sHotImage) ) m_sHotImage.Empty();
				else return;
			}
		}

		if( !m_sNormalImage.IsEmpty() ) {
			if( !DrawImage(hDC, (LPCTSTR)m_sNormalImage)) m_sNormalImage.Empty();
			else return;
		}
	}

	void CEditUI::PaintText(HDC hDC)
	{
		if( m_dwTextColor == 0 ) m_dwTextColor = m_pManager->GetDefaultFontColor();
		if( m_dwDisabledTextColor == 0 ) m_dwDisabledTextColor = m_pManager->GetDefaultDisabledColor();

// 		if( m_sText.IsEmpty() ) return;
// 
// 		CDuiString sText = m_sText;
// 		if( m_bPasswordMode ) {
// 			sText.Empty();
// 			LPCTSTR p = m_sText.GetData();
// 			while( *p != _T('\0') ) {
// 				sText += m_cPasswordChar;
// 				p = ::CharNext(p);
// 			}
// 		}

        DWORD	dwTextColor = m_dwTextColor;
		CDuiString sText;
		if( m_sText.IsEmpty() ) 
		{
			sText = m_sTipText;
            if (m_dwTipTextColor != 0)
            {
                dwTextColor = m_dwTipTextColor;
            }
		}
		else
		{
			sText = m_sText;
			if( m_bPasswordMode ) {
				sText.Empty();
				LPCTSTR p = m_sText.GetData();
				while( *p != _T('\0') ) {
					sText += m_cPasswordChar;
					p = ::CharNext(p);
				}
			}
		}

		RECT rc = m_rcItem;
		rc.left += m_rcTextPadding.left;
		rc.right -= m_rcTextPadding.right;
		rc.top += m_rcTextPadding.top;
		rc.bottom -= m_rcTextPadding.bottom;
		if( IsEnabled() ) {
            if( m_bGdiPlus )
                CRenderEngine::DrawTextByGdiPlus(hDC, m_pManager, rc, sText, dwTextColor, \
                m_iFont, m_uTextStyle);//DT_SINGLELINE属性表示只有一行 GDI的不强加必须一行
            else
                CRenderEngine::DrawText(hDC, m_pManager, rc, sText, dwTextColor, \
                m_iFont, DT_SINGLELINE | m_uTextStyle);

//			CRenderEngine::DrawText(hDC, m_pManager, rc, sText, dwTextColor, \
//				m_iFont, DT_SINGLELINE | m_uTextStyle);
		}
		else {
            if( m_bGdiPlus )
                CRenderEngine::DrawTextByGdiPlus(hDC, m_pManager, rc, sText, m_dwDisabledTextColor, \
                m_iFont, DT_SINGLELINE | m_uTextStyle);
            else
                CRenderEngine::DrawText(hDC, m_pManager, rc, sText, m_dwDisabledTextColor, \
                m_iFont, DT_SINGLELINE | m_uTextStyle);

//			CRenderEngine::DrawText(hDC, m_pManager, rc, sText, m_dwDisabledTextColor, \
//				m_iFont, DT_SINGLELINE | m_uTextStyle);

		}
	}

	void CEditUI::SetFocusX()
	{
		GetManager()->SetFocus(this);
		GetManager()->ReleaseCapture();
		if(m_pWindow == NULL )
		{
			m_pWindow = new CEditWnd();
			ASSERT(m_pWindow);
			m_pWindow->Init(this);

			int nSize = GetWindowTextLength(*m_pWindow);
			if( nSize == 0 )
				nSize = 1;

			Edit_SetSel(*m_pWindow, 0, nSize);
			Activate();
		}
		else if( m_pWindow != NULL )
		{
			int nSize = GetWindowTextLength(*m_pWindow);
			if( nSize == 0 )
				nSize = 1;

			Edit_SetSel(*m_pWindow, 0, nSize);
		}
	}
}
