// AppWindow.cpp: implementation of the CAppWindow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AppWindow.h"
#include "..\RkcTool\include\constdef.h"


namespace AppFrame {

	void CAppWindow::OnFinalMessage(HWND hWnd)
	{
		// 清理已注册的logic
		for ( int i = 0; i < m_aNotifiers.GetSize(); ++i )
		{
			m_pm.RemoveNotifier(static_cast<INotifyUI*>(m_aNotifiers[i]));
			m_pm.RemoveMessageFilter(static_cast<IMessageFilterUI*>(m_aNotifiers[i]));
			m_pm.RemovePreMessageFilter(static_cast<IPreMessageFilterUI*>(m_aNotifiers[i]));
			m_pm.RemoveTranslateAccelerator(static_cast<ITranslateAccelerator*>(m_aNotifiers[i]));
		}
		m_pm.ReapObjects(m_pm.GetRoot());
		if (m_bIsDelSelOnClose) //默认为true，窗口需要是new出来的，注意
		{
			delete this;
		}
	}

	LPCTSTR CAppWindow::GetWindowClassName() const 
	{ 
		return _T("CAppWindow"); 
	}

	UINT CAppWindow::GetClassStyle() const 
	{ 
		return CS_DBLCLKS; 
	}

	void CAppWindow::Init()
	{

	}

	void CAppWindow::Close(UINT nRet /*=IDOK*/)
	{
		CWindowWnd::Close(nRet);
	}
	
	LRESULT CAppWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
		styleValue &= ~WS_CAPTION;
		::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
		m_pm.Init(m_hWnd);
		for (int i = 0; i < m_aNotifiers.GetSize(); ++i)
		{
			static_cast<CNotifyUIImpl*>(m_aNotifiers[i])->SetData(m_pData);
			m_pm.AddTranslateAccelerator(static_cast<CNotifyUIImpl*>(m_aNotifiers[i]));
			m_pm.AddPreMessageFilter(static_cast<CNotifyUIImpl*>(m_aNotifiers[i]));
		}

		CDialogBuilder builder;
		CControlUI* pRoot = builder.Create((LPCTSTR)m_strSkin, 0, 0, &m_pm);
		ASSERT(pRoot && "Failed to parse XML");
		m_pm.AttachDialog(pRoot);

		for (int i = 0; i < m_aNotifiers.GetSize(); ++i)
		{
			static_cast<CNotifyUIImpl*>(m_aNotifiers[i])->SetData(m_pData);
			m_pm.AddMessageFilter(static_cast<CNotifyUIImpl*>(m_aNotifiers[i]));
			m_pm.AddNotifier(static_cast<CNotifyUIImpl*>(m_aNotifiers[i]));
		}

		m_pm.SendNotify(pRoot, DUI_MSGTYPE_WINDOWCREATE, 0, 0, false);
		Init();
		return 0;
	}

	LRESULT CAppWindow::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{		
		bHandled = FALSE;
		return 0;
	}

	LRESULT CAppWindow::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_pm.SendNotify( m_pm.GetRoot(), DUI_MSGTYPE_WINDOWDESTROY, 0, 0 );
		bHandled = FALSE;
		return 0;
	}

	LRESULT CAppWindow::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
        if( ::IsIconic(*this) ) bHandled = FALSE;
        return (wParam == 0) ? TRUE : FALSE;
	}

	LRESULT CAppWindow::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LPRECT pRect = NULL;

		if (wParam == TRUE)
		{
			LPNCCALCSIZE_PARAMS pParam = (LPNCCALCSIZE_PARAMS)lParam;
			pRect = &pParam->rgrc[0];
		}
		else
		{
			pRect = (LPRECT)lParam;
		}

		if (::IsZoomed(m_hWnd))
		{	// 最大化时，计算当前显示器最适合宽高度
			MONITORINFO oMonitor = {};
			oMonitor.cbSize = sizeof(oMonitor);
			::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTONEAREST), &oMonitor);
			CDuiRect rcMonitor = oMonitor.rcMonitor;

			pRect->right = pRect->left + rcMonitor.GetWidth();
			pRect->bottom = pRect->top + rcMonitor.GetHeight();
			return WVR_REDRAW;
		}

		return 0;
	}
	
	LRESULT CAppWindow::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0;
	}

	LRESULT CAppWindow::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
		::ScreenToClient(*this, &pt);

		RECT rcClient;
		::GetClientRect(*this, &rcClient);
        
		// 改变大小
		if( !::IsZoomed(*this) ) {
			RECT rcSizeBox = m_pm.GetSizeBox();
			if( pt.y < rcClient.top + rcSizeBox.top ) {
				if( pt.x < rcClient.left + rcSizeBox.left ) return HTTOPLEFT;
				if( pt.x > rcClient.right - rcSizeBox.right ) return HTTOPRIGHT;
				return HTTOP;
			}
			else if( pt.y > rcClient.bottom - rcSizeBox.bottom ) {
				if( pt.x < rcClient.left + rcSizeBox.left ) return HTBOTTOMLEFT;
				if( pt.x > rcClient.right - rcSizeBox.right ) return HTBOTTOMRIGHT;
				return HTBOTTOM;
			}
			if( pt.x < rcClient.left + rcSizeBox.left ) return HTLEFT;
			if( pt.x > rcClient.right - rcSizeBox.right ) return HTRIGHT;
		}

		// 标题栏响应
		RECT rcCaption = m_pm.GetCaptionRect();
		if( pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
			&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom ) {
				CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
				if( pControl && _tcscmp(pControl->GetClass(), _T("ButtonUI")) != 0 && 
					_tcscmp(pControl->GetClass(), _T("OptionUI")) != 0 &&
					_tcscmp(pControl->GetClass(), _T("TextUI")) != 0 )
					return HTCAPTION;
		}

		return HTCLIENT;
	}

	LRESULT CAppWindow::OnMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if ( IsWindowVisible() )
		{
			m_pm.SendNotify( m_pm.GetRoot(), DUI_MSGTYPE_WINDOWMOVE, wParam, lParam );
		}
		return 0;
	}
	LRESULT CAppWindow::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
        SIZE szRoundCorner = m_pm.GetRoundCorner();
        if( !::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0) ) {
            CDuiRect rcWnd;
            ::GetWindowRect(*this, &rcWnd);
            rcWnd.Offset(-rcWnd.left, -rcWnd.top);
            rcWnd.right++; rcWnd.bottom++;
            HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom, szRoundCorner.cx, szRoundCorner.cy);
            ::SetWindowRgn(*this, hRgn, TRUE);
            ::DeleteObject(hRgn);
        }
		if ( IsWindowVisible() )
		{
			m_pm.SendNotify( m_pm.GetRoot(), DUI_MSGTYPE_WINDOWSIZE, wParam, lParam );
		}
        bHandled = FALSE;
        return 0;
	}

	LRESULT CAppWindow::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;

		MONITORINFO oMonitor = {};
		oMonitor.cbSize = sizeof(oMonitor);
		::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTONEAREST), &oMonitor);
		CDuiRect rcMonitor = oMonitor.rcMonitor;

		// 计算最大化时，正确的原点坐标
		lpMMI->ptMaxPosition.x = rcMonitor.left;
		lpMMI->ptMaxPosition.y = rcMonitor.top;

		lpMMI->ptMaxTrackSize.x = rcMonitor.GetWidth();
		lpMMI->ptMaxTrackSize.y = rcMonitor.GetHeight();

		lpMMI->ptMinTrackSize.x = m_pm.GetMinInfo().cx;
		lpMMI->ptMinTrackSize.y = m_pm.GetMinInfo().cy;

		bHandled = FALSE;
		return 0;
	}

	LRESULT CAppWindow::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
		return lRes;
	}

	LRESULT CAppWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lRes = 0;
		BOOL bHandled = TRUE;
		switch( uMsg ) {
		case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
		case WM_CLOSE:         lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
		case WM_DESTROY:       lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
		case WM_NCACTIVATE:    lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
		case WM_NCCALCSIZE:    lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
		case WM_NCPAINT:       lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
		case WM_NCHITTEST:     lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
		case WM_MOVE:          lRes = OnMove(uMsg, wParam, lParam, bHandled); break;
		case WM_SIZE:          lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
		case WM_GETMINMAXINFO: lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); break;
		case WM_SYSCOMMAND:    lRes = OnSysCommand(uMsg, wParam, lParam, bHandled); break;
		case WM_ACTIVATE:
			{
				lRes = OnActive(uMsg, wParam, lParam, bHandled); 
				bHandled = FALSE;//控件处理
				break;
			}		
		case WM_NCLBUTTONDBLCLK:
			{
				return lRes;
			}
		case WM_TIMER:
			{
				if( wParam < 0x10 ) //大于16的Timer进m_pm.MessageHandler
				{
					lRes = OnTimer(uMsg, wParam, lParam, bHandled);				
				}
				else
				{
					bHandled = FALSE;
				}
				break;
			}
		default:
		bHandled = FALSE;
		}
		if( bHandled ) return lRes;
		if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;

		return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	}

	LRESULT CAppWindow::OnActive(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		u16 uActive = LOWORD( wParam );
		if ( uActive == WA_INACTIVE )
		{
			if ( m_bAutoHide )
			{
				u32 l = lParam;
				ShowWindow( false );
			}			 
		}
		return 0;
	}

	bool CAppWindow::AddNotifier( CNotifyUIImpl* pNotifier )
	{
		pNotifier->SetPaintManagerUI(&m_pm);
		m_aNotifiers.Add(pNotifier);

		if ( m_hWnd && ::IsWindow(m_hWnd) )
		{
			pNotifier->SetData(m_pData);
			m_pm.AddTranslateAccelerator(pNotifier);
			m_pm.AddPreMessageFilter(pNotifier);
			m_pm.AddMessageFilter(pNotifier);
			m_pm.AddNotifier(pNotifier);
		}
		return true;
	}

	void CAppWindow::MoveWindow( int x, int y, int nWidth, int nHeight, bool bRepaint )
	{
		::MoveWindow( m_hWnd, x, y, nWidth, nHeight, bRepaint );
	}

	CAppWindow::CAppWindow(LPCTSTR lpstrUI, LPVOID pData) :m_strSkin(lpstrUI), m_pData(pData)
	{
		m_bAutoHide = false;
		m_bIsDelSelOnClose = true;
	}

	CAppWindow::~CAppWindow()
	{
		// 清理已注册的logic
		for (int i = 0; i < m_aNotifiers.GetSize(); ++i)
		{
			delete(static_cast<CNotifyUIImpl*>(m_aNotifiers[i]));
			m_aNotifiers.Remove(i);
		}
	}

	void CAppWindow::SetPaintOnWindow( bool bPaint )
	{
		m_pm.SetPaintOnWindow( bPaint );
		::InvalidateRect( m_hWnd, NULL, 0);
	}

	void CAppWindow::SetAutoHide( bool bAutoHide )
	{
		m_bAutoHide = bAutoHide;
	}

	void CAppWindow::ShowWindowFromLeftToRight(bool bShow)
	{
		if ( GetParent(m_hWnd) == NULL )
		{
			return;
		}

		if ( bShow )
		{
			CDuiRect rcWnd;
			//::GetClientRect(*this, &rcWnd);
			::GetWindowRect(m_hWnd, &rcWnd);
			POINT point;
			point.x = rcWnd.left;
			point.y = rcWnd.top;
			ScreenToClient( GetParent(m_hWnd), &point );

			int nLeft = - rcWnd.GetWidth();
			//::MoveWindow( m_hWnd, nLeft, rcWnd.top, rcWnd.GetWidth(), rcWnd.GetHeight(), TRUE );  
			SetWindowPos( m_hWnd, NULL, nLeft, point.y, rcWnd.GetWidth(), rcWnd.GetHeight(), SWP_SHOWWINDOW |SWP_NOACTIVATE );

            KillTimer( m_hWnd, TIMERID_HIDEWND_LEFT );
			::SetTimer( m_hWnd, TIMERID_SHOWWND_LEFT, WINDOW_TIMER_ELAPSE, NULL );
		}
		else
		{
            KillTimer( m_hWnd, TIMERID_SHOWWND_LEFT );
			::SetTimer( m_hWnd, TIMERID_HIDEWND_LEFT, WINDOW_TIMER_ELAPSE, NULL );
		}	
	}

	void CAppWindow::ShowWindowFromBottomToTop(bool bShow)
	{
		if ( GetParent(m_hWnd) == NULL )
		{
			return;
		}

		if ( bShow )
		{
			CDuiRect rcWnd;
			//::GetWindowRect(*this, &rcWnd);
			::GetClientRect(*this, &rcWnd);

			int nTop = rcWnd.GetHeight();
			//::MoveWindow( m_hWnd, nLeft, rcWnd.top, rcWnd.GetWidth(), rcWnd.GetHeight(), TRUE );  
			SetWindowPos( m_hWnd, NULL, rcWnd.left, nTop, rcWnd.GetWidth(), rcWnd.GetHeight(), SWP_SHOWWINDOW |SWP_NOACTIVATE );

			//ShowWindow( true );
			::SetTimer( m_hWnd, TIMERID_SHOWWND_BOTTOM, WINDOW_TIMER_ELAPSE, NULL );
		}
		else
		{
			::SetTimer( m_hWnd, TIMERID_HIDEWND_BOTTOM, WINDOW_TIMER_ELAPSE, NULL );
		}	
	}

    void CAppWindow::ShowWindowFromTopToBottom(bool bShow)
    {
        if ( bShow )
        {
            CDuiRect rcWnd;
            ::GetClientRect(*this, &rcWnd);

            int nTop = - rcWnd.GetHeight();
            SetWindowPos( m_hWnd, NULL, rcWnd.left, nTop, rcWnd.GetWidth(), rcWnd.GetHeight(), SWP_SHOWWINDOW |SWP_NOACTIVATE );

            ::SetTimer( m_hWnd, TIMERID_SHOWWND_TOP, WINDOW_TIMER_ELAPSE, NULL );
        }
        else
        {
            ::SetTimer( m_hWnd, TIMERID_HIDEWND_TOP, WINDOW_TIMER_ELAPSE, NULL );
        }	
    }

    void CAppWindow::ShowMainWindowFromLeftToRight(bool bShow)
    {
        if ( bShow )
        {
            CDuiRect rcWnd;
            //::GetWindowRect(*this, &rcWnd);
            ::GetClientRect(*this, &rcWnd);

            int nLeft = - rcWnd.GetWidth();
            SetWindowPos( m_hWnd, NULL, nLeft, rcWnd.top, rcWnd.GetWidth(), rcWnd.GetHeight(), SWP_SHOWWINDOW |SWP_NOACTIVATE );

            //ShowWindow( true );
            ::SetTimer( m_hWnd, TIMERID_SHOWMAINWND_LEFT, WINDOW_TIMER_ELAPSE, NULL );
        }
        else
        {
            ::SetTimer( m_hWnd, TIMERID_HIDEMAINWND_LEFT, WINDOW_TIMER_ELAPSE, NULL );
        }	
    }

	LRESULT CAppWindow::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if ( wParam == TIMERID_SHOWWND_LEFT )
		{
			CDuiRect rcWnd;
			::GetWindowRect(*this, &rcWnd);
			POINT point;
			point.x = rcWnd.left;
			point.y = rcWnd.top;
			ScreenToClient( GetParent(m_hWnd), &point );

			int nStepLen = rcWnd.GetWidth() / WINDOW_MOVESTEP_COUNT;

			point.x += nStepLen;
			if ( point.x >= 0)
			{
				point.x = 0;
				KillTimer( m_hWnd, TIMERID_SHOWWND_LEFT );
			}
			SetWindowPos( m_hWnd, NULL, point.x, point.y, rcWnd.GetWidth(), rcWnd.GetHeight(), SWP_NOSIZE|SWP_NOACTIVATE );
		}
		else if ( wParam == TIMERID_HIDEWND_LEFT )
		{
			CDuiRect rcWnd;
			::GetWindowRect(*this, &rcWnd);
			POINT point;
			point.x = rcWnd.left;
			point.y = rcWnd.top;
			ScreenToClient( GetParent(m_hWnd), &point );

			int nStepLen = rcWnd.GetWidth() / WINDOW_MOVESTEP_COUNT;

			point.x -= nStepLen;
			int nRight = point.x + rcWnd.GetWidth();
			if ( nRight <= 0 )
			{
				//point.x -= nRight;			
				KillTimer( m_hWnd, TIMERID_HIDEWND_LEFT );
				ShowWindow( false );
			}
		
			SetWindowPos( m_hWnd, NULL, point.x, point.y, rcWnd.GetWidth(), rcWnd.GetHeight(), SWP_NOSIZE|SWP_NOACTIVATE );
		}
		else if ( wParam == TIMERID_SHOWWND_BOTTOM )
		{
			CDuiRect rcWnd;
			::GetWindowRect(*this, &rcWnd);
			POINT point;
			point.x = rcWnd.left;
			point.y = rcWnd.top;
			ScreenToClient( GetParent(m_hWnd), &point );

			s32 nTop = DEFAULT_TITLE_HEIGHT;
			if ( CPaintManagerUI::IsSelfAdaption() )
			{
				float fAdpX, fAdpY;
				CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
				nTop = s32(nTop * fAdpY);
			}

			int nStepLen = rcWnd.GetHeight() / WINDOW_MOVESTEP_COUNT;

			point.y -= nStepLen;
			if ( point.y <= nTop)
			{
				point.y = nTop;
				KillTimer( m_hWnd, TIMERID_SHOWWND_BOTTOM );
			}
			//::MoveWindow( m_hWnd, rcWnd.left, rcWnd.top, rcWnd.GetWidth(), rcWnd.GetHeight(), TRUE );
			SetWindowPos( m_hWnd, NULL, point.x, point.y, rcWnd.GetWidth(), rcWnd.GetHeight(), SWP_NOSIZE|SWP_NOACTIVATE );
		}
		else if ( wParam == TIMERID_HIDEWND_BOTTOM )
		{
			CDuiRect rcWnd;
			::GetWindowRect(*this, &rcWnd);
			POINT point;
			point.x = rcWnd.left;
			point.y = rcWnd.top;
			ScreenToClient( GetParent(m_hWnd), &point );

			int nStepLen = rcWnd.GetHeight() / WINDOW_MOVESTEP_COUNT;

			point.y += nStepLen;
			int nTop = point.y - rcWnd.GetHeight();
			if ( nTop >= rcWnd.GetHeight() )
			{
				//point.x -= nRight;			
				KillTimer( m_hWnd, TIMERID_HIDEWND_BOTTOM );
				ShowWindow( false );
			}

			//::MoveWindow( m_hWnd, rcWnd.left, rcWnd.top, rcWnd.GetWidth(), rcWnd.GetHeight(), TRUE );
			SetWindowPos( m_hWnd, NULL, point.x, point.y, rcWnd.GetWidth(), rcWnd.GetHeight(), SWP_NOSIZE|SWP_NOACTIVATE );
		}
        else if ( wParam == TIMERID_SHOWMAINWND_LEFT )
        {
            CDuiRect rcWnd;
            ::GetWindowRect(*this, &rcWnd);
            POINT point;
            point.x = rcWnd.left;
            point.y = rcWnd.top;
            //ScreenToClient( GetParent(m_hWnd), &point );

            int nStepLen = rcWnd.GetWidth() / WINDOW_MOVESTEP_COUNT;

            point.x += nStepLen;
            if ( point.x >= 0)
            {
                point.x = 0;
                KillTimer( m_hWnd, TIMERID_SHOWMAINWND_LEFT );
            }
            SetWindowPos( m_hWnd, NULL, point.x, point.y, rcWnd.GetWidth(), rcWnd.GetHeight(), SWP_NOSIZE|SWP_NOACTIVATE );
        }
        else if ( wParam == TIMERID_HIDEMAINWND_LEFT )
        {
            CDuiRect rcWnd;
            ::GetWindowRect(*this, &rcWnd);
            POINT point;
            point.x = rcWnd.left;
            point.y = rcWnd.top;
            //ScreenToClient( GetParent(m_hWnd), &point );

            int nStepLen = rcWnd.GetWidth() / WINDOW_MOVESTEP_COUNT;

            point.x -= nStepLen;
            int nRight = point.x + rcWnd.GetWidth();
            if ( nRight <= 0 )
            {
                //point.x -= nRight;			
                KillTimer( m_hWnd, TIMERID_HIDEMAINWND_LEFT );
                ShowWindow( false );
            }

            SetWindowPos( m_hWnd, NULL, point.x, point.y, rcWnd.GetWidth(), rcWnd.GetHeight(), SWP_NOSIZE|SWP_NOACTIVATE );
        }
        else if ( wParam == TIMERID_SHOWWND_TOP )
        {
            CDuiRect rcWnd;
            ::GetWindowRect(*this, &rcWnd);
            POINT point;
            point.x = rcWnd.left;
            point.y = rcWnd.top;

            int nStepLen = rcWnd.GetHeight() / WINDOW_MOVESTEP_COUNT;

            point.y += nStepLen;
            if ( point.y >= 0)
            {
                point.x = 0;
                KillTimer( m_hWnd, TIMERID_SHOWWND_TOP );
            }
            SetWindowPos( m_hWnd, NULL, point.x, point.y, rcWnd.GetWidth(), rcWnd.GetHeight(), SWP_NOSIZE|SWP_NOACTIVATE );
        }
        else if ( wParam == TIMERID_HIDEWND_TOP )
        {
            CDuiRect rcWnd;
            ::GetWindowRect(*this, &rcWnd);
            POINT point;
            point.x = rcWnd.left;
            point.y = rcWnd.top;

            int nStepLen = rcWnd.GetWidth() / WINDOW_MOVESTEP_COUNT;

            point.y -= nStepLen;
            int nBottom = point.y + rcWnd.GetHeight();
            if ( nBottom <= 0 )
            {
                KillTimer( m_hWnd, TIMERID_HIDEWND_TOP );
                ShowWindow( false );
            }

            SetWindowPos( m_hWnd, NULL, point.x, point.y, rcWnd.GetWidth(), rcWnd.GetHeight(), SWP_NOSIZE|SWP_NOACTIVATE );
        }
		return 0;
	}

	void CAppWindow::SetIsDelSelOnClose( bool bIsDelSelOnClose )
	{
		m_bIsDelSelOnClose = bIsDelSelOnClose;
	}

	void CAppWindow::ShowWindowInitLocation()
	{
		CDuiRect rcWnd;
		::GetWindowRect(*this, &rcWnd);

		s32 nTop = DEFAULT_TITLE_HEIGHT;
		if ( CPaintManagerUI::IsSelfAdaption() )
		{
			float fAdpX, fAdpY;
			CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
			nTop = s32(nTop * fAdpY);
		}

		SetWindowPos( m_hWnd, NULL, 0, nTop, rcWnd.GetWidth(), rcWnd.GetHeight(), SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOACTIVATE );
	}


	const MSGMAP CNotifyUIImpl::messageMap =
	{
		0,
		&CNotifyUIImpl::_messageEntries[0]
	};
		
	const MSGMAP_ENTRY CNotifyUIImpl::_messageEntries[] =
	{
		{ 0,_T(""), _T(""), 0, 0 }     // nothing here
	};

	const MSGMAP* CNotifyUIImpl::GetMessageMap() const
	{
		return 0;
	};

	void CNotifyUIImpl::Notify(TNotifyUI& msg)
	{
		const MSGMAP* pMap = GetMessageMap();
		if ( pMap != 0 )
		{
			Invoke( pMap, msg );
		}
	}

	LRESULT CNotifyUIImpl::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
	{
		const MSGMAP* pMap = GetMessageMap();
		if ( pMap != 0 )
		{
			Invoke( pMap, uMsg, wParam, lParam, bHandled );
		}
		return 0;
	}

	LRESULT CNotifyUIImpl::PreMessageHandler(MSG* pMsg)
	{
		return S_OK;
	}

	LRESULT CNotifyUIImpl::TranslateAccelerator(MSG *pMsg)
	{
		return S_FALSE;
	}
	
	void CNotifyUIImpl::Invoke( const MSGMAP* pMsg, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled )
	{
		MSGMAP_ENTRY* pBegin = const_cast<MSGMAP_ENTRY*>(pMsg->lpEntries);
		while ( pBegin->m_pfn != 0 )
		{
			// 消息查找、目前不支持继承消息，若要支持，需要建立一个hash表
			if ( uMsg == pBegin->m_dwEvent )
			{
				union MessageMapFuncs mmf;
				mmf.pfn = pBegin->m_pfn;
				
				switch ( pBegin->m_wSig )
				{
				case emFunc_uwlb:				
					(this->*mmf.pfn_uwlb)( wParam, lParam, bHandled );	
					break;
				default:
					break;
				}
				break;
			}
			pBegin++;
		}
	}

	void CNotifyUIImpl::Invoke( const MSGMAP* pMsg, TNotifyUI& msg )
	{
		if ( msg.pSender == 0 )
		{
			return;
		}
		MSGMAP_ENTRY* pBegin = const_cast<MSGMAP_ENTRY*>(pMsg->lpEntries);
		while ( pBegin->m_pfn != 0 )
		{
			// 消息查找、目前不支持继承消息，若要支持，需要建立一个hash表
			if ( msg.pSender->GetName() == pBegin->m_chControl && msg.sType == pBegin->m_chEvent )
			{
				union MessageMapFuncs mmf;
				mmf.pfn = pBegin->m_pfn;

				switch ( pBegin->m_wSig )
				{
				case emFunc_bn:		
					(this->*mmf.pfn_bn)(msg);	
					break;
				case emFunc_vv:
					(this->*mmf.pfn)();
					break;
				}
				break;
			}
			pBegin++;
		}

        if ( !msg.pSender->GetName().IsEmpty() && (msg.sType == DUI_MSGTYPE_CLICK || msg.sType == DUI_MSGTYPE_SELECTCHANGED || msg.sType == DUI_MSGTYPE_TEXTCHANGED) )
        {
            OnMsgNotify(msg);
        }
	}

    bool CNotifyUIImpl::OnMsgNotify(TNotifyUI& msg)
    {
        return true;
    }
}
