#include "StdAfx.h"
#include "DragController.h"
namespace DuiLib{
	CDragController::CDragController() : m_bIsLBtnDown(false), m_pSourceCtrl(NULL), m_pTargetCtrl(NULL),
		m_pDragWnd(NULL),m_bIsDragging(false),m_bIsScrolling(false),m_hTargetWnd(NULL)
	{
//		InitHook();
	}

	CDragController::~CDragController()
	{
//		FreeHook();
	}

	LRESULT CDragController::HandleMessage( LPMSG pMsg )
	{
		if ( pMsg->message == WM_LBUTTONDOWN )
		{
			OnLButtonDown(pMsg);
		}
		else if ( pMsg->message == WM_TIMER )
		{
			OnTimer(pMsg);
		}
		else if(pMsg->message == WM_MOUSEMOVE)
		{
			OnMouseMove(pMsg);
		}
		else if ( pMsg->message == WM_LBUTTONUP )
		{
			OnLButtonUp(pMsg);
		}
		return 0;
	}

	void CDragController::InitHook()
	{
		//安装钩子
		s_hHook = ::SetWindowsHookEx(WH_GETMESSAGE, GetMessageProc, 
			NULL,GetCurrentThreadId());
	}

	void CDragController::FreeHook()
	{
		if ( s_hHook != NULL )
		{
			::UnhookWindowsHookEx(s_hHook);
			s_hHook = NULL;
		}
	}

	LRESULT CALLBACK CDragController::GetMessageProc( int nCode, WPARAM wParam, LPARAM lParam )
	{
		LPMSG lpMsg = (LPMSG) lParam;
		if( (nCode >= 0) && (PM_REMOVE == wParam) &&
			IDragController::GetSingletonPtr()->HandleMessage(lpMsg))
		{
			lpMsg->message = WM_NULL;
			lpMsg->lParam = 0L;
			lpMsg->wParam = 0;
		}
		// 将钩子消息传递给当前钩子链中的下一个钩子
		return ::CallNextHookEx(s_hHook, nCode, wParam, lParam);
	}

	void CDragController::StartDrag()
	{
		CControlUI *pDragControl = GetSourceCtrl(m_ptDragPoint);
		if(pDragControl != NULL)
		{
			m_pSourceCtrl = pDragControl;
			//计算offset
			POINT ptClient = m_ptDragPoint;
			::ScreenToClient(m_pSourceCtrl->GetManager()->GetPaintWindow(), &ptClient);
			m_ptOffSet.x = m_pSourceCtrl->GetX() - ptClient.x;
			m_ptOffSet.y = m_pSourceCtrl->GetY() - ptClient.y;
			CDuiSize szShadowSize = m_pSourceCtrl->GetDragShadowSize();
			//缩略图，offset等比缩放
			if ( szShadowSize.cx != 0 &&
				szShadowSize.cy != 0 )
			{
				m_ptOffSet.x = m_ptOffSet.x * szShadowSize.cx / m_pSourceCtrl->GetWidth();
				m_ptOffSet.y = m_ptOffSet.y * szShadowSize.cy / m_pSourceCtrl->GetHeight();
			}
			POINT pt = { m_ptDragPoint.x + m_ptOffSet.x, m_ptDragPoint.y + m_ptOffSet.y };
			if ( m_pDragWnd == NULL )
			{
				m_pDragWnd = new CDragWnd(m_pSourceCtrl,pt);
			}
			else
			{
				m_pDragWnd->SetSourceCtrl(m_pSourceCtrl);
			}
			//拖拽前先发消息给用户(同步)
			m_pSourceCtrl->GetManager()->SendNotify(m_pSourceCtrl, DUI_MSGTYPE_DRAGSTART);
			// 使用SetWindowPos，且不激活窗口，以解决焦点切换导致IE标题框闪烁的问题
			::SetWindowPos(m_pDragWnd->GetHWND(), HWND_TOPMOST, pt.x, pt.y, 0, 0,
						   SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOSIZE );
			m_bIsDragging = true;
			//检测焦点定时器
			::SetTimer(m_pSourceCtrl->GetManager()->GetPaintWindow(),DUI_DRAG_FOCUS_TIMER_ID,200,NULL);
			//自动滚动定时器
			::SetTimer(m_pSourceCtrl->GetManager()->GetPaintWindow(),DUI_DRAG_SCROLL_TIMER_ID,300,NULL);
		}
		else
		{
			Restore();
		}
	}


	void CDragController::Restore()
	{
		if ( m_pSourceCtrl )
		{
			::KillTimer(m_pSourceCtrl->GetManager()->GetPaintWindow(), DUI_DRAG_FOCUS_TIMER_ID);
			::KillTimer(m_pSourceCtrl->GetManager()->GetPaintWindow(), DUI_DRAG_SCROLL_TIMER_ID);
			m_pSourceCtrl->GetManager()->ReleaseCapture();
		}
	    if (m_pDragWnd)
		{
			m_pDragWnd->Close();
			m_pDragWnd = NULL;
		}
		if ( m_hTargetWnd)
		{
			CPaintManagerUI *pManager = CPaintManagerUI::GetManager(m_hTargetWnd);
			if ( pManager)
			{
				pManager->ReleaseCapture();
			}	
		}
		if ( m_pTargetCtrl )
		{
			TEventUI event;
			event.Type = UIEVENT_DRAGLEAVE;
			event.pSender = m_pTargetCtrl;
			m_pTargetCtrl->Event(event);			
		}
		m_bIsDragging = false;
		m_bIsLBtnDown = false;
		m_pSourceCtrl = NULL;
		m_pTargetCtrl = NULL;
		m_hTargetWnd = NULL;
	}


	CControlUI* CDragController::GetSourceCtrl( POINT pt )
	{
		HWND hWnd = WindowFromPoint(pt);
		::ScreenToClient(hWnd, &pt);
		if ( hWnd == NULL )
		{
			return NULL; 
		}
		CPaintManagerUI *pManager = CPaintManagerUI::GetManager(hWnd);
		CControlUI *pDragControl = NULL;
		if (pManager)
		{
			pDragControl = pManager->FindControl(pt);
			if ( pDragControl )
			{
				//判断点击控件是否可以被拖放
				if ( !IsDragableCtrl(pDragControl, pt))
				{
					return NULL;
				}
			}
			//找到可以拖拽的父控件
			while ( pDragControl  )
			{
				if( pDragControl->IsDrag())
				{
					break;
				}
				pDragControl = pDragControl->GetParent();
			}
		}
		return pDragControl;
	}

	CControlUI* CDragController::GetTargetCtrl( POINT pt )
	{
		HWND hWnd = WindowFromPoint(pt);
		if ( hWnd == NULL )
		{
			return NULL; 
		}
		CPaintManagerUI *pManager = CPaintManagerUI::GetManager(hWnd);
		CControlUI *pDropControl = NULL;
		if (pManager)
		{
			if ( m_hTargetWnd != hWnd )
			{
				CPaintManagerUI *pManager = CPaintManagerUI::GetManager(m_hTargetWnd);
				if ( pManager )
				{
					pManager->ReleaseCapture();
				}
				m_hTargetWnd = hWnd;
			}
			::SetFocus(hWnd);
			pManager->SetCapture();
			ScreenToClient(hWnd, &pt);
			pDropControl = pManager->FindControl(pt);
			//找到可以拖拽的父控件
			while ( pDropControl  )
			{
				if( pDropControl->IsDrop())
				{
					break;
				}
				pDropControl = pDropControl->GetParent();
			}
		}
		if ( pDropControl )
		{
			//验证接受数据类型
			if(_tcscmp( pDropControl->GetDropData(), GetDragDataMgr()->GetDataName() ) != 0)
			{
				return NULL;
			}
		}
		return pDropControl;
	}

	void CDragController::CheckFocus()
	{
		if ( m_bIsDragging)
		{
			HWND hFocus = GetForegroundWindow();
			//当前激活的窗口是源、目标及拖拽窗口时认为拖拽有效，否则拖拽取消
			//取最外层
			HWND hSourceWnd = m_pSourceCtrl->GetManager()->GetPaintWindow();
			while ( ::GetWindowLong(hSourceWnd, GWL_STYLE) & WS_CHILD )
			{
				hSourceWnd = ::GetParent(hSourceWnd);
			}
			HWND hTargetWnd = m_hTargetWnd;
			while ( ::GetWindowLong(hTargetWnd, GWL_STYLE) & WS_CHILD )
			{
				hTargetWnd = ::GetParent(hTargetWnd);
			}
			if (      m_pDragWnd->GetHWND() != hFocus &&
				      hSourceWnd != hFocus &&
				      hTargetWnd != hFocus
			   )
			{
				m_pSourceCtrl->GetManager()->SendNotify(m_pSourceCtrl, DUI_MSGTYPE_DRAGCANCEL);
				if ( m_pTargetCtrl )
				{
					m_pTargetCtrl->GetManager()->SendNotify(m_pTargetCtrl,DUI_MSGTYPE_DRAGCANCEL);
				}
				Restore();
			}
		}
	}

	void CDragController::DoAutoScroll( CControlUI *pTraget, POINT ptMouse )
	{
		if ( pTraget == NULL)
		{
			return;
		}
		POINT ptTarget = ptMouse;
		CContainerUI *pContainer = (CContainerUI*)pTraget->GetInterface(_T("Container"));
		//如果不是容器
		if ( pContainer == NULL )
		{
			return;
		}
		::ScreenToClient(pContainer->GetManager()->GetPaintWindow(),&ptTarget);
		int nInset0 = 25;
		int nInset1 = 12;
		RECT rcInset = pContainer->GetInset();
		//有效的滚动区域在容器内边距内
		RECT rcScroll = {pContainer->GetX() + rcInset.left, 
			pContainer->GetY() + rcInset.top, 
			pContainer->GetX() + pContainer->GetWidth() - rcInset.right, 
			pContainer->GetY() + pContainer->GetHeight() - rcInset.bottom};
		//这里取得内边距内nInset0和nInset1大小的区域，
		//两个圈，在最内圈不自动滚动，在第一圈开始慢速滚动，第二圈快速滚动
		RECT rcTarget0 = {pContainer->GetX() + rcInset.left + nInset0, 
								pContainer->GetY() + rcInset.top + nInset0, 
								pContainer->GetX() + pContainer->GetWidth() - rcInset.right - nInset0, 
								pContainer->GetY() + pContainer->GetHeight() - rcInset.bottom - nInset0};
		RECT rcTarget1 = {pContainer->GetX() + rcInset.left + nInset1, 
			pContainer->GetY() + rcInset.top + nInset1, 
			pContainer->GetX() + pContainer->GetWidth() - rcInset.right - nInset1, 
			pContainer->GetY() + pContainer->GetHeight() - rcInset.bottom - nInset1};
		
		//内圈 不滚动
		if ( ::PtInRect(&rcTarget0, ptTarget))
		{
			return;
		}
		//第一圈
		else if (::PtInRect(&rcTarget1, ptTarget) )
		{
			int nSpeed = 1;
			//在这里发一个同步消息给用户 通知会滚动
			pContainer->GetManager()->SendNotify(pContainer, DUI_MSGTYPE_DRAGSCROLL,\
				(WPARAM)DUI_AUTOSCROLL_SLOW, (LPARAM)&nSpeed);
			int nTime = 0;
			for (; nTime < nSpeed; nTime++ )
			{
				if ( ptTarget.x > rcTarget0.right)
				{
					pContainer->LineRight();
				}
				if (ptTarget.x < rcTarget0.left)
				{
					pContainer->LineLeft();
				}
				if (ptTarget.y < rcTarget0.top)
				{
					pContainer->LineUp();
				}
				if(ptTarget.y > rcTarget0.bottom)
				{
					pContainer->LineDown();
				}
			}
			pContainer->GetManager()->SendNotify(pContainer, DUI_MSGTYPE_DRAGOVER, \
				(WPARAM)m_pSourceCtrl,(LPARAM)&ptMouse);
		TEventUI event;
		event.Type = UIEVENT_DRAGMOVE;
		event.pSender = pContainer;
		event.wParam = (WPARAM)m_pSourceCtrl;
		event.lParam = (LPARAM)&ptMouse;
		pContainer->Event(event);
		}
		//最外圈 快速滚动
		else if ( ::PtInRect(&rcScroll, ptTarget))
		{
			int nSpeed = 10;
			//在这里发一个同步消息给用户 通知会滚动
			pContainer->GetManager()->SendNotify(pContainer, DUI_MSGTYPE_DRAGSCROLL, \
				(WPARAM)DUI_AUTOSCROLL_FAST, (LPARAM)&nSpeed);
			int nTime = 0;
			for (; nTime < nSpeed; nTime++ )
			{
				if ( ptTarget.x > rcTarget1.right)
				{
					pContainer->LineRight();
				}
				if (ptTarget.x < rcTarget1.left)
				{
					pContainer->LineLeft();
				}
				if (ptTarget.y < rcTarget1.top)
				{
					pContainer->LineUp();
				}
				if(ptTarget.y > rcTarget1.bottom)
				{
					pContainer->LineDown();
				}
			}
			pContainer->GetManager()->SendNotify(pContainer, DUI_MSGTYPE_DRAGOVER, \
				(WPARAM)m_pSourceCtrl,(LPARAM)&ptMouse);
		}
	}

	void CDragController::OnLButtonDown( LPMSG pMsg )
	{
		POINT pt = pMsg->pt;
		CControlUI *pSourCtrl = GetSourceCtrl(pt);
		if ( pSourCtrl != NULL )
		{
			m_bIsLBtnDown = true;
			m_ptDragPoint = pt;
		}
	}

	void CDragController::OnLButtonUp( LPMSG pMsg )
	{
		if(m_bIsDragging)
		{
			//正常拖放
			POINT ptDrop = pMsg->pt;
			if ( m_pTargetCtrl != NULL )
			{
				m_pTargetCtrl->GetManager()->SendNotify(m_pTargetCtrl, DUI_MSGTYPE_DRAGDROP, \
					(WPARAM)m_pSourceCtrl, (LPARAM)&ptDrop);
				//用户处理完拖放事件通知源/目的控件拖放完成
				m_pSourceCtrl->GetManager()->SendNotify(m_pSourceCtrl, DUI_MSGTYPE_DRAGDONE);
				m_pTargetCtrl->GetManager()->SendNotify(m_pTargetCtrl,  DUI_MSGTYPE_DRAGDONE);
			}
			else
			{
				m_pSourceCtrl->GetManager()->SendNotify(m_pSourceCtrl, DUI_MSGTYPE_DRAGCANCEL);
			}
			Restore();
		}
		if ( m_bIsLBtnDown )
		{
			m_bIsLBtnDown = false;
		}
	}

	void CDragController::OnTimer( LPMSG pMsg )
	{
		if(pMsg->wParam == DUI_DRAG_FOCUS_TIMER_ID )
		{
			CheckFocus();
		}
		else if (pMsg->wParam == DUI_DRAG_SCROLL_TIMER_ID )
		{
			if ( m_pTargetCtrl == NULL )
			{
				return;
			}
			CControlUI *pScroll = NULL;
			CTreeNodeUI *pNode = (CTreeNodeUI*)m_pTargetCtrl->GetInterface(_T("TreeNode"));
			if(pNode)
			{
				pScroll = pNode->GetTreeView();
			}
			else
			{
				pScroll = m_pTargetCtrl;
			}
			DoAutoScroll(m_pTargetCtrl, pMsg->pt);
		}
	}

	void CDragController::OnMouseMove( LPMSG pMsg )
	{
		if ( m_bIsLBtnDown && !m_bIsDragging )
		{
			//win xp 未移动也会受到WM_MOUSEMOVE消息
			if ( pMsg->pt.x == m_ptDragPoint.x &&pMsg->pt.y == m_ptDragPoint.y )
			{
				return;
			}
			StartDrag();
		}
		//移动窗口
		else if( m_bIsDragging )
		{
			if ( m_pDragWnd )
			{
				POINT ptDrag = { pMsg->pt.x + m_ptOffSet.x, pMsg->pt.y + m_ptOffSet.y };
				m_pDragWnd->Move(ptDrag);
			}
			POINT pt = pMsg->pt;
			CControlUI *pTarget = GetTargetCtrl(pt);
			//获取目标控件
			if( pTarget == NULL ) 
			{
				if ( m_pTargetCtrl != NULL)
				{	
					m_pTargetCtrl->GetManager()->SendNotify(m_pTargetCtrl, DUI_MSGTYPE_DRAGLEAVE);
					TEventUI event;
					event.Type = UIEVENT_DRAGLEAVE;
					event.pSender = m_pTargetCtrl;
					m_pTargetCtrl->Event(event);
					m_pTargetCtrl = NULL;
				}
				return;
			}
			if ( pTarget == m_pTargetCtrl )
			{
				m_pTargetCtrl->GetManager()->SendNotify(m_pTargetCtrl, DUI_MSGTYPE_DRAGOVER, \
					(WPARAM)m_pSourceCtrl, (LPARAM)&pt);
				if (m_pTargetCtrl->GetInterface(_T("TreeNode")))
				{
					int a = 0;
				}
				TEventUI event;
				event.Type = UIEVENT_DRAGMOVE;
				event.pSender = m_pTargetCtrl;
				event.wParam = (WPARAM)m_pSourceCtrl;
				event.lParam = (LPARAM)&pt;
				m_pTargetCtrl->Event(event);
			}
			//控件切换
			else
			{
				if ( m_pTargetCtrl != NULL)
				{
					m_pTargetCtrl->GetManager()->SendNotify(m_pTargetCtrl, DUI_MSGTYPE_DRAGLEAVE);
					TEventUI event;
					event.pSender = m_pTargetCtrl;
					event.Type = UIEVENT_DRAGLEAVE;
					m_pTargetCtrl->Event(event);
				}
				TEventUI event;
				event.Type = UIEVENT_DRAGENTER;
				event.pSender = pTarget;
				pTarget->Event(event);
				pTarget->GetManager()->SendNotify(pTarget, DUI_MSGTYPE_DRAGENTER);
				m_pTargetCtrl = pTarget;
			}
		}

	}
	//这些控件不能触发拖放：
	//1. 禁用的控件
	//2. Button/Option/Edit/RichEdit/Combo/Scrollbar
	//3. ListHeader可拖动的分隔符
	//4. 横/纵向布局的分隔符
	bool CDragController::IsDragableCtrl( CControlUI *pCtrl, POINT pt )
	{
		if ( !pCtrl->IsEnabled())
		{
			return false;
		}
		if (NULL != pCtrl->GetInterface(DUI_CTR_BUTTON))
		{
			return false;
		}
		if (NULL != pCtrl->GetInterface(DUI_CTR_OPTION))
		{
			return false;
		}
		if (NULL != pCtrl->GetInterface(DUI_CTR_EDIT))
		{
			return false;
		}
		if (NULL != pCtrl->GetInterface(DUI_CTR_RICHEDIT))
		{
			return false;
		}
		if (NULL != pCtrl->GetInterface(DUI_CTR_COMBO))
		{
			return false;
		}
		if (NULL != pCtrl->GetInterface(DUI_CTR_SCROLLBAR))
		{
			return false;
		}
		//列表头
		CListHeaderItemUI *pListHeaderItem = (CListHeaderItemUI*)pCtrl->GetInterface(DUI_CTR_LISTHEADERITEM);
		if( NULL != pListHeaderItem )
		{
			RECT rcSeparator = pListHeaderItem->GetThumbRect();
			int iSepWidth = pListHeaderItem->GetSepWidth();
			if (iSepWidth>=0)
				rcSeparator.left-= 4;
			else
				rcSeparator.right+= 4;
			if( ::PtInRect(&rcSeparator, pt) )
			{
				if( pListHeaderItem->IsDragable() ) 
				{
					return false;
				}
			}
		}
		//VerticalLayout
		CVerticalLayoutUI *pVl = (CVerticalLayoutUI *)pCtrl->GetInterface(DUI_CTR_VERTICALLAYOUT);
		if ( NULL != pVl )
		{
			RECT rcSeparator = pVl->GetThumbRect(false);
			if( ::PtInRect(&rcSeparator, pt) ) 
			{
				return false;
			}
		}
		//HorizontalLayout
		CHorizontalLayoutUI *pHl = (CHorizontalLayoutUI *)pCtrl->GetInterface(DUI_CTR_HORIZONTALLAYOUT);
		if ( NULL != pHl )
		{
			RECT rcSeparator = pHl->GetThumbRect(false);
			if( ::PtInRect(&rcSeparator, pt) ) 
			{
				return false;
			}
		}
		return true;
	}

	HHOOK CDragController::s_hHook = NULL;
}