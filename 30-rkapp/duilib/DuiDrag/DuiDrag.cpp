#pragma once
#include "StdAfx.h"
#include "DuiDrag.h"
#include "DragDataMgr.h"
#include "DragController.h"
namespace DuiLib{

	bool CDuiDragControlUI::IsDrag() const
	{
		return m_bDrag;
	}

	bool CDuiDragControlUI::IsDrop() const
	{
		return m_bDrop;
	}

	void CDuiDragControlUI::SetDrop(bool bDrop)
	{
		m_bDrop = bDrop;
	}

	void CDuiDragControlUI::SetDrag(bool bDrag)
	{
		m_bDrag = bDrag;
	}

	LPCTSTR CDuiDragControlUI::GetDropData() const
	{
		return m_sDropData;
	}

	void CDuiDragControlUI::SetDropData( LPCTSTR lpData )
	{
		m_sDropData = lpData;
	}

	CDuiDragControlUI::CDuiDragControlUI() :m_bDrop(false),
		m_bDrag(false),
		m_pVirtualCtrl(NULL),
		m_sDropData(_T("")),
		m_bAutoRespond(true),
		m_dwVirtualColor(0),
		m_hDragShawdowBmp(NULL),
		m_byAlpha(150)
	{
		ZeroMemory(&m_szVirtualCtrl,sizeof(CDuiSize));
		ZeroMemory(&m_szDragShadow, sizeof(CDuiSize));
		ZeroMemory(&m_rcVirtualPadding,sizeof(CDuiRect));
	}

	CDuiDragControlUI::~CDuiDragControlUI()
	{
		if ( m_hDragShawdowBmp )
		{
			::DeleteObject(m_hDragShawdowBmp);
			m_hDragShawdowBmp = NULL;
		}

	}

	void CDuiDragControlUI::SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue )
	{
		if(_tcscmp(pstrName, _T("drag")) == 0 ) SetDrag(_tcscmp(pstrValue, _T("true")) == 0);
		else if(_tcscmp(pstrName, _T("drop")) == 0 ) SetDrop(_tcscmp(pstrValue, _T("true")) == 0);
		else if(_tcscmp(pstrName, _T("dropdata")) == 0 ) SetDropData(pstrValue);
		else if (_tcscmp(pstrName,_T("autorespond")) == 0 ) SetAutoRespond(_tcscmp(pstrValue, _T("true")) == 0);
		else if(_tcscmp(pstrName,_T("virtualctrlbkcolor")) == 0 )
		{
			while( *pstrValue > _T('\0') && *pstrValue <= _T(' ') ) pstrValue = ::CharNext(pstrValue);
			if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
			LPTSTR pstr = NULL;
			DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
			SetVirtualCtrlBkColor(clrColor);
		}
		else if(_tcscmp(pstrName,_T("virtualctrlpadding")) == 0)
		{
			RECT rcPadding = { 0 };
			LPTSTR pstr = NULL;
			rcPadding.left = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
			rcPadding.top = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);    
			rcPadding.right = _tcstol(pstr + 1, &pstr, 10);  ASSERT(pstr);    
			rcPadding.bottom = _tcstol(pstr + 1, &pstr, 10); ASSERT(pstr);    
			SetVirtualCtrlPadding(rcPadding);
		}
		else if(_tcscmp(pstrName,_T("virtualctrlsize")) == 0)
		{
			SIZE szVirtual = { 0 };
			LPTSTR pstr = NULL;
			szVirtual.cx = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
			szVirtual.cy = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);    
			SetVirtualCtrlSize(szVirtual);
		}
		else if (_tcscmp(pstrName,_T("dragshadowsize")) == 0)
		{
			SIZE szShadow = { 0 };
			LPTSTR pstr = NULL;
			szShadow.cx = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
			szShadow.cy = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);    
			SetDragShadowSize(szShadow);
		}
		else if (_tcscmp(pstrName, _T("dragshadowalpha")) == 0)
		{
			SetDragWndAlpha( _ttoi(pstrValue) );
		}
	}

	void CDuiDragControlUI::DoEvent( TEventUI& event )
	{
		if ( event.pSender != this || !m_bAutoRespond )
		{
			return;
		}
		if (event.Type == UIEVENT_DRAGMOVE)
		{
			CControlUI *pSource = (CControlUI *)event.wParam;
			LPPOINT ppt = (LPPOINT)event.lParam;
			OnDragMove(pSource,*ppt);
		}
		else if(event.Type == UIEVENT_DRAGLEAVE)
		{
			OnDragLeave();
		}
		else if(event.Type == UIEVENT_DRAGENTER)
		{
			OnDragEnter();
		}
	}

	int CDuiDragControlUI::GetVVirtualIdx( CVerticalLayoutUI *pLayout ,POINT pt )
	{
		::ScreenToClient(pLayout->GetManager()->GetPaintWindow(), &pt);
		if ( pt.x > (pLayout->GetX() + pLayout->GetWidth()) || pt.x < pLayout->GetX() )
		{
			return pLayout->GetCount();
		}
		int nIdx = 0;
		for ( nIdx = 0; nIdx < pLayout->GetCount(); nIdx++)
		{
			CControlUI *pItem = pLayout->GetItemAt(nIdx);
			if (!pItem->IsVisible())
			{
				continue;
			}
			int nUp = pItem->GetY() - pItem->GetPadding().top;
			int nDown = pItem->GetY() + pItem->GetHeight() + pItem->GetPadding().bottom;
			if ( pt.y >= nUp && pt.y <= nDown )
			{
				return ((nDown - pt.y) <= (pt.y - nUp) ) ? (nIdx+1) : nIdx;
			}
		}
		return pLayout->GetCount();
	}

	int CDuiDragControlUI::GetHVirtualIdx( CHorizontalLayoutUI *pLayout ,POINT pt )
	{
		::ScreenToClient(pLayout->GetManager()->GetPaintWindow(), &pt);
		if ( pt.y > (pLayout->GetY() + pLayout->GetHeight()) || pt.y < pLayout->GetY() )
		{
			return pLayout->GetCount();
		}
		int nIdx = 0;
		for ( nIdx = 0; nIdx < pLayout->GetCount(); nIdx++)
		{
			CControlUI *pItem = pLayout->GetItemAt(nIdx);
			if (!pItem->IsVisible())
			{
				continue;
			}
			int nLeft = pItem->GetX() - pItem->GetPadding().left;
			int nRight = pItem->GetX() + pItem->GetWidth() + pItem->GetPadding().right;
			if ( pt.x >= nLeft && pt.x <= nRight)
			{
				return ((nRight - pt.x) <= (pt.x - nLeft) ) ? (nIdx+1) : nIdx;
			}
		}
		return pLayout->GetCount();
	}

	void CDuiDragControlUI::SetVirtualControl( int nIdx, CContainerUI *pContainer, CControlUI *pSourceCtrl )
	{
		if ( pContainer->GetInterface(_T("TreeNode")))
		{
			pContainer = ((CTreeNodeUI*)pContainer)->GetTreeView();
		}
		//清除
		if ( nIdx == -1 )
		{
			if ( m_pVirtualCtrl )
			{
				pContainer->Remove(m_pVirtualCtrl);
				m_pVirtualCtrl = NULL;
			}
			return;
		}
		//新建
		if ( m_pVirtualCtrl == NULL )
		{
			if(pContainer->GetInterface(DUI_CTR_LIST))
			{
				m_pVirtualCtrl = new CListContainerElementUI();
			}
			else
			{
				m_pVirtualCtrl = new CControlUI();
			}
			if ( nIdx < pContainer->GetCount() )
			{
				pContainer->AddAt(m_pVirtualCtrl,nIdx);
			}
			else
			{
				pContainer->Add(m_pVirtualCtrl);
			}
			//用户没有指定控件大小
			m_pVirtualCtrl->SetFixedWidth(m_szVirtualCtrl.cx);
			m_pVirtualCtrl->SetFixedHeight(m_szVirtualCtrl.cy);
			m_pVirtualCtrl->SetBkColor(m_dwVirtualColor);
			m_pVirtualCtrl->SetPadding(m_rcVirtualPadding);
			if(pContainer->GetInterface(DUI_CTR_LIST))
			{
				static_cast<CListUI*>(pContainer)->SelectItem(-1);
			}
			return;
		}
		else
		{
			int nVirtualIdx =pContainer->GetItemIndex(m_pVirtualCtrl);
			//在虚拟控件上下就不响应了
			if (nIdx == nVirtualIdx || nIdx == nVirtualIdx + 1)
			{
				return;
			}
			pContainer->RemoveAt(nVirtualIdx);
			m_pVirtualCtrl = NULL;
			SetVirtualControl(nIdx,pContainer,pSourceCtrl);
		}
	}

	void CDuiDragControlUI::OnDragMove( CControlUI *pSourceCtrl, POINT pt )
	{
		int nVirtualIdx = 0;
		CControlUI *pTarget = (CControlUI*)this;
		if ( pTarget->GetInterface(_T("TreeView")))
		{
			CTreeViewUI *pTree = (CTreeViewUI *)pTarget;
			POINT ptMouse = pt;
			::ScreenToClient(pTree->GetManager()->GetPaintWindow(), &ptMouse);
			nVirtualIdx = GetVVirtualIdx(pTree, pt);
			CTreeNodeUI *pNode = GetTreeNode(pTree,ptMouse);
			if ( pNode)
			{
				pNode->GetTreeView()->SetItemExpand(true, pNode);
			}
		}
		else if (pTarget->GetInterface(DUI_CTR_VERTICALLAYOUT))
		{
			CVerticalLayoutUI *pVl = (CVerticalLayoutUI*)pTarget;
			nVirtualIdx = GetVVirtualIdx(pVl, pt);
		}
		else if (pTarget->GetInterface(DUI_CTR_HORIZONTALLAYOUT))
		{
			CHorizontalLayoutUI *pHl = (CHorizontalLayoutUI*)pTarget;
			nVirtualIdx = GetHVirtualIdx(pHl, pt);
		}
		else
		{
			//其他的不支持
			return;
		}
		SetVirtualControl(nVirtualIdx,(CContainerUI*)this, pSourceCtrl);

	}

	void CDuiDragControlUI::OnDragLeave()
	{
		CControlUI *pTarget = (CControlUI*)this;
		if (pTarget->GetInterface(DUI_CTR_VERTICALLAYOUT) || pTarget->GetInterface(DUI_CTR_HORIZONTALLAYOUT))
		{
			SetVirtualControl(-1, (CContainerUI*)this, 0);
		}
	}

	void CDuiDragControlUI::SetAutoRespond( bool bAuto )
	{
		m_bAutoRespond = bAuto;
	}

	bool CDuiDragControlUI::GetAutoRespond()
	{
		return m_bAutoRespond;
	}

	void CDuiDragControlUI::SetVirtualCtrlSize( SIZE szCtrl )
	{
		m_szVirtualCtrl = szCtrl;
	}

	SIZE CDuiDragControlUI::GetVirtualCtrlSize()
	{
		return m_szVirtualCtrl;
	}

	void CDuiDragControlUI::SetVirtualCtrlBkColor( DWORD dwColor )
	{
		m_dwVirtualColor = dwColor;
	}

	DWORD CDuiDragControlUI::GetVirtualCtrlBkColor()
	{
		return m_dwVirtualColor;
	}

	void CDuiDragControlUI::SetVirtualCtrlPadding( RECT rcPadding )
	{
		m_rcVirtualPadding = rcPadding;
	}

	RECT CDuiDragControlUI::GetVirtualCtrlPadding()
	{
		return m_rcVirtualPadding;
	}

	CTreeNodeUI* CDuiDragControlUI::GetTreeNode( CTreeViewUI *pTree, POINT pt )
	{
		CControlUI *pItem = NULL;
		int nIdx = 0;
		for ( ; nIdx < pTree->GetCount(); nIdx++ )
		{
			pItem = pTree->GetItemAt(nIdx);
			if ( !pItem->IsVisible())
			{
				continue;
			}
			RECT rcItem = {pItem->GetX(), pItem->GetY(), pItem->GetX() + pItem->GetWidth(), pItem->GetY() + pItem->GetHeight()};
			if (::PtInRect(&rcItem, pt))
			{
				return (CTreeNodeUI*)pItem;
			}
		}
		return NULL;
	}

	void CDuiDragControlUI::OnDragEnter()
	{
	}

	void CDuiDragControlUI::SetDragShadowSize( SIZE szShadow )
	{
		m_szDragShadow = szShadow;
	}

	SIZE CDuiDragControlUI::GetDragShadowSize()
	{
		return m_szDragShadow;
	}

	void CDuiDragControlUI::SetDragShadowBmp( HBITMAP hBmp )
	{
		if ( m_hDragShawdowBmp )
		{
			::DeleteObject(m_hDragShawdowBmp);
			m_hDragShawdowBmp = NULL;
		}
		m_hDragShawdowBmp = hBmp;
	}

	HBITMAP CDuiDragControlUI::GetDragShadowBmp()
	{
		return m_hDragShawdowBmp;
	}

	void CDuiDragControlUI::SetDragWndAlpha(byte byWndAlpha)
	{
		m_byAlpha = byWndAlpha;
	}

	byte CDuiDragControlUI::GetDragWndAlpha()
	{
		return m_byAlpha;
	}

	void CDuiDrag::InitDuiDrag()
	{
		if ( IDragController::GetSingletonPtr() == NULL ) new CDragController();
		if ( IDragDataMgr::GetSingletonPtr() == NULL) new CDragDataMgr();
	}

	void CDuiDrag::FreeDuiDrag()
	{
		if ( IDragController::GetSingletonPtr() != NULL ) IDragController::ReleaseSingleton();
		if ( IDragDataMgr::GetSingletonPtr() != NULL) IDragDataMgr::ReleaseSingleton();
	}

	DuiLib::CDuiDrag CDuiDrag::s_cDuiDrag;

	IDragDataMgr* GetDragDataMgr()
	{
		return IDragDataMgr::GetSingletonPtr();
	}

}


