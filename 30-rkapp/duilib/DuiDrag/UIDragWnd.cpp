#include "stdafx.h"
#include "DragController.h"
#include "UIDragWnd.h"
namespace DuiLib{
	LRESULT CDragWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if( uMsg == WM_CREATE ) {
			LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
			styleValue &= ~WS_CAPTION;
			::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
			m_pm.Init(m_hWnd);
			CControlUI* pRoot = new CContainerUI;
			m_pm.AttachDialog(pRoot);
			m_pm.AddNotifier(this);
			Init();
			return 0;
		}
		else if( uMsg == WM_ERASEBKGND ) {
			return 1;
		}
		else if( uMsg == WM_NCACTIVATE ) {
			if( !::IsIconic(m_hWnd) ) {
				return (wParam == 0) ? TRUE : FALSE;
			}
		}
		else if( uMsg == WM_NCCALCSIZE ) {
			return 0;
		}
		else if( uMsg == WM_NCPAINT ) {
			return 0;
		}
		else if( uMsg == WM_KILLFOCUS ){
			//Close();
		}
		else if(uMsg == WM_LBUTTONUP)
		{
			//Close();
		}
		else if(uMsg == WM_PAINT)
		{
			HBITMAP hShadowBmp = NULL;
			if ( m_pSourceControl )
			{
				hShadowBmp = m_pSourceControl->GetDragShadowBmp();
				if (hShadowBmp == NULL)
				{
					if (m_hShadowBmp == NULL)
					{
						m_hShadowBmp = GetCtrlShoot();
					}
					hShadowBmp = m_hShadowBmp;
				}
			}			

			PAINTSTRUCT ps = {0};
			::BeginPaint(m_hWnd,&ps);
			BITMAP bmp; 
			if (hShadowBmp && ::GetObject(hShadowBmp, sizeof(BITMAP), (LPSTR)&bmp))
			{
				HDC hPaintDC = ps.hdc;
				HDC hTmpDC = ::CreateCompatibleDC(hPaintDC);
				HBITMAP hOldBmp = (HBITMAP)::SelectObject(hTmpDC, hShadowBmp);
				::StretchBlt(hPaintDC, 0, 0, m_szShadowSize.cx, m_szShadowSize.cy, hTmpDC, 
						0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
				::SelectObject(hTmpDC, hOldBmp);
				::DeleteDC(hTmpDC);
			}
			::EndPaint(m_hWnd, &ps);

 			return 0;
		}
		LRESULT lRes = 0;
		if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
		return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	}

	void CDragWnd::Init()
	{
		m_pm.SetTransparent(m_pSourceControl->GetDragWndAlpha()); 
	}

	void CDragWnd::Create(POINT &pt)
	{
		// 创建时先不要显示，且不激活，以解决焦点切换的问题
		CWindowWnd::Create(NULL, _T("CDragWnd"), WS_POPUP | WS_CLIPSIBLINGS,
			WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE,
			pt.x, pt.y, m_szShadowSize.cx, m_szShadowSize.cy );
	}

	CDragWnd::CDragWnd(CControlUI* pControl, POINT &pt):
	m_hShadowBmp(NULL)
	{
		SetSourceCtrl(pControl);
		Create(pt);
	}

	void CDragWnd::Move( POINT &pt )
	{
		::SetWindowPos(m_hWnd, NULL, pt.x, pt.y, 0, 0, SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOZORDER  );
	}

	void CDragWnd::SetSourceCtrl( CControlUI *pCtrl )
	{
		assert(pCtrl != NULL);
		m_pSourceControl = pCtrl;
		m_szShadowSize = m_pSourceControl->GetDragShadowSize();
		if ( m_szShadowSize.cx == 0 ||
			m_szShadowSize.cy == 0 )
		{
			m_szShadowSize.cx = m_pSourceControl->GetWidth();
			m_szShadowSize.cy = m_pSourceControl->GetHeight();
		}
		if ( m_hShadowBmp != NULL)
		{
			::DeleteObject(m_hShadowBmp);
			m_hShadowBmp = NULL;
		}
	}

	bool CDragWnd::IsVisible()
	{
		if (::IsWindowVisible(m_hWnd))
		{
			return true;
		}
		return false;
	}

	HBITMAP CDragWnd::GetCtrlShoot()
	{
		 RECT rcSource = {m_pSourceControl->GetX(), m_pSourceControl->GetY(), m_pSourceControl->GetX() + m_pSourceControl->GetWidth(), 
			 m_pSourceControl->GetY() + m_pSourceControl->GetHeight()};
		 //如果没有背景颜色 设置为白色
		 bool bBkColorAdded = false;
		 if ( m_pSourceControl->GetBkColor() == 0 )
		 {
			//白色
			//m_pSourceControl->SetBkColor(0xFFFFFFFF);
			 SIZE sz;
			 sz.cx = 15;
			 sz.cy = 15;
			 m_pSourceControl->SetBorderRound(sz);
			 bBkColorAdded = true;
		 }		 
		 RECT rc = m_pSourceControl->GetPos();

// 		 HDC hDC = m_pSourceControl->GetManager()->GetPaintDC();
// 		 ASSERT(::GetObjectType(hDC)==OBJ_DC || ::GetObjectType(hDC)==OBJ_MEMDC);
// 		 HPEN hPen = ::CreatePen(PS_SOLID | PS_INSIDEFRAME, 15, RGB(255,0,0));
// 		 HPEN hOldPen = (HPEN)::SelectObject(hDC, hPen);
// 		 ::SelectObject(hDC, ::GetStockObject(HOLLOW_BRUSH));
// 		 ::RoundRect(hDC, rc.left, rc.top, rc.right, rc.bottom, 15, 15);
// 		 ::SelectObject(hDC, hOldPen);
// 		 ::DeleteObject(hPen);
// 		 ::RoundRect(m_pSourceControl->GetManager()->GetPaintDC(), rc.left, rc.top, rc.right, rc.bottom, 15, 15);
		 HBITMAP hBitmap = CRenderEngine::GenerateBitmap(m_pSourceControl->GetManager(), m_pSourceControl ,rcSource);

		 //恢复
		 if ( bBkColorAdded )
		 {
			 m_pSourceControl->SetBkColor(0);
		 }
		 return hBitmap;
	}

	CDragWnd::~CDragWnd()
	{
		if (m_hShadowBmp != NULL)
		{
			::DeleteObject(m_hShadowBmp);
			m_hShadowBmp = NULL;
		}
	}
}