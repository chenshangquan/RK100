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
		//��װ����
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
		// ��������Ϣ���ݸ���ǰ�������е���һ������
		return ::CallNextHookEx(s_hHook, nCode, wParam, lParam);
	}

	void CDragController::StartDrag()
	{
		CControlUI *pDragControl = GetSourceCtrl(m_ptDragPoint);
		if(pDragControl != NULL)
		{
			m_pSourceCtrl = pDragControl;
			//����offset
			POINT ptClient = m_ptDragPoint;
			::ScreenToClient(m_pSourceCtrl->GetManager()->GetPaintWindow(), &ptClient);
			m_ptOffSet.x = m_pSourceCtrl->GetX() - ptClient.x;
			m_ptOffSet.y = m_pSourceCtrl->GetY() - ptClient.y;
			CDuiSize szShadowSize = m_pSourceCtrl->GetDragShadowSize();
			//����ͼ��offset�ȱ�����
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
			//��קǰ�ȷ���Ϣ���û�(ͬ��)
			m_pSourceCtrl->GetManager()->SendNotify(m_pSourceCtrl, DUI_MSGTYPE_DRAGSTART);
			// ʹ��SetWindowPos���Ҳ�����ڣ��Խ�������л�����IE�������˸������
			::SetWindowPos(m_pDragWnd->GetHWND(), HWND_TOPMOST, pt.x, pt.y, 0, 0,
						   SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOSIZE );
			m_bIsDragging = true;
			//��⽹�㶨ʱ��
			::SetTimer(m_pSourceCtrl->GetManager()->GetPaintWindow(),DUI_DRAG_FOCUS_TIMER_ID,200,NULL);
			//�Զ�������ʱ��
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
				//�жϵ���ؼ��Ƿ���Ա��Ϸ�
				if ( !IsDragableCtrl(pDragControl, pt))
				{
					return NULL;
				}
			}
			//�ҵ�������ק�ĸ��ؼ�
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
			//�ҵ�������ק�ĸ��ؼ�
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
			//��֤������������
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
			//��ǰ����Ĵ�����Դ��Ŀ�꼰��ק����ʱ��Ϊ��ק��Ч��������קȡ��
			//ȡ�����
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
		//�����������
		if ( pContainer == NULL )
		{
			return;
		}
		::ScreenToClient(pContainer->GetManager()->GetPaintWindow(),&ptTarget);
		int nInset0 = 25;
		int nInset1 = 12;
		RECT rcInset = pContainer->GetInset();
		//��Ч�Ĺ��������������ڱ߾���
		RECT rcScroll = {pContainer->GetX() + rcInset.left, 
			pContainer->GetY() + rcInset.top, 
			pContainer->GetX() + pContainer->GetWidth() - rcInset.right, 
			pContainer->GetY() + pContainer->GetHeight() - rcInset.bottom};
		//����ȡ���ڱ߾���nInset0��nInset1��С������
		//����Ȧ��������Ȧ���Զ��������ڵ�һȦ��ʼ���ٹ������ڶ�Ȧ���ٹ���
		RECT rcTarget0 = {pContainer->GetX() + rcInset.left + nInset0, 
								pContainer->GetY() + rcInset.top + nInset0, 
								pContainer->GetX() + pContainer->GetWidth() - rcInset.right - nInset0, 
								pContainer->GetY() + pContainer->GetHeight() - rcInset.bottom - nInset0};
		RECT rcTarget1 = {pContainer->GetX() + rcInset.left + nInset1, 
			pContainer->GetY() + rcInset.top + nInset1, 
			pContainer->GetX() + pContainer->GetWidth() - rcInset.right - nInset1, 
			pContainer->GetY() + pContainer->GetHeight() - rcInset.bottom - nInset1};
		
		//��Ȧ ������
		if ( ::PtInRect(&rcTarget0, ptTarget))
		{
			return;
		}
		//��һȦ
		else if (::PtInRect(&rcTarget1, ptTarget) )
		{
			int nSpeed = 1;
			//�����﷢һ��ͬ����Ϣ���û� ֪ͨ�����
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
		//����Ȧ ���ٹ���
		else if ( ::PtInRect(&rcScroll, ptTarget))
		{
			int nSpeed = 10;
			//�����﷢һ��ͬ����Ϣ���û� ֪ͨ�����
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
			//�����Ϸ�
			POINT ptDrop = pMsg->pt;
			if ( m_pTargetCtrl != NULL )
			{
				m_pTargetCtrl->GetManager()->SendNotify(m_pTargetCtrl, DUI_MSGTYPE_DRAGDROP, \
					(WPARAM)m_pSourceCtrl, (LPARAM)&ptDrop);
				//�û��������Ϸ��¼�֪ͨԴ/Ŀ�Ŀؼ��Ϸ����
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
			//win xp δ�ƶ�Ҳ���ܵ�WM_MOUSEMOVE��Ϣ
			if ( pMsg->pt.x == m_ptDragPoint.x &&pMsg->pt.y == m_ptDragPoint.y )
			{
				return;
			}
			StartDrag();
		}
		//�ƶ�����
		else if( m_bIsDragging )
		{
			if ( m_pDragWnd )
			{
				POINT ptDrag = { pMsg->pt.x + m_ptOffSet.x, pMsg->pt.y + m_ptOffSet.y };
				m_pDragWnd->Move(ptDrag);
			}
			POINT pt = pMsg->pt;
			CControlUI *pTarget = GetTargetCtrl(pt);
			//��ȡĿ��ؼ�
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
			//�ؼ��л�
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
	//��Щ�ؼ����ܴ����Ϸţ�
	//1. ���õĿؼ�
	//2. Button/Option/Edit/RichEdit/Combo/Scrollbar
	//3. ListHeader���϶��ķָ���
	//4. ��/���򲼾ֵķָ���
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
		//�б�ͷ
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