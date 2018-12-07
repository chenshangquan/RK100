#include "stdafx.h"
#include "UITouchList.h"

namespace DuiLib
{

CTouchListUI::CTouchListUI() : m_bLButtonDown(false),m_bScrollSelect(false), m_iCurSel(-1), m_iExpandedItem(-1)
{
	m_ListInfo.nColumns = 0;
	m_ListInfo.nFont = -1;
	m_ListInfo.uTextStyle = DT_VCENTER; // m_uTextStyle(DT_VCENTER | DT_END_ELLIPSIS)
	m_ListInfo.dwTextColor = 0xFF000000;
	m_ListInfo.dwBkColor = 0;
	m_ListInfo.bAlternateBk = false;
	m_ListInfo.dwSelectedTextColor = 0xFF000000;
	m_ListInfo.dwSelectedBkColor = 0/*0xFFC1E3FF dyy*/; 
	m_ListInfo.dwHotTextColor = 0xFF000000;
	m_ListInfo.dwHotBkColor = 0/*0xFFE9F5FF*/;
	m_ListInfo.dwDisabledTextColor = 0xFFCCCCCC;
	m_ListInfo.dwDisabledBkColor = 0xFFFFFFFF;
	m_ListInfo.dwLineColor = 0;
	m_ListInfo.bShowHtml = false;
	m_ListInfo.bMultiExpandable = false;
	::ZeroMemory(&m_ListInfo.rcTextPadding, sizeof(m_ListInfo.rcTextPadding));
	::ZeroMemory(&m_ListInfo.rcColumn, sizeof(m_ListInfo.rcColumn));
	m_bAutoLayout = true;
}

CTouchListUI::~CTouchListUI()
{

}

LPCTSTR CTouchListUI::GetClass() const
{
	return _T("TouchListUI");
}

UINT CTouchListUI::GetControlFlags() const
{
	return UIFLAG_TABSTOP;
}

LPVOID CTouchListUI::GetInterface(LPCTSTR pstrName)
{
	if( _tcscmp(pstrName, DUI_CTR_TOUCHLIST) == 0 ) 
		return static_cast<CTouchListUI*>(this);
	if( _tcscmp(pstrName, _T("IListOwner")) == 0 ) 
		return static_cast<IListOwnerUI*>(this);
	return CTileLayoutUI::GetInterface(pstrName);
}

bool CTouchListUI::SetItemIndex(CControlUI* pControl, int iIndex)
{
	int iOrginIndex = GetItemIndex(pControl);
	if( iOrginIndex == -1 ) 
		return false;
	if( iOrginIndex == iIndex ) 
		return true;

	IListItemUI* pSelectedListItem = NULL;
	if( m_iCurSel >= 0 ) pSelectedListItem = 
		static_cast<IListItemUI*>(GetItemAt(m_iCurSel)->GetInterface(_T("ListItem")));
	if( !SetItemIndex(pControl, iIndex) ) 
		return false;
	int iMinIndex = min(iOrginIndex, iIndex);
	int iMaxIndex = max(iOrginIndex, iIndex);
	for(int i = iMinIndex; i < iMaxIndex + 1; ++i) {
		CControlUI* p = GetItemAt(i);
		IListItemUI* pListItem = static_cast<IListItemUI*>(p->GetInterface(_T("ListItem")));
		if( pListItem != NULL ) {
			pListItem->SetIndex(i);
		}
	}
	if( m_iCurSel >= 0 && pSelectedListItem != NULL ) 
		m_iCurSel = pSelectedListItem->GetIndex();
	return true;
}

int CTouchListUI::GetCount() const
{
	return CContainerUI::GetCount();
}

bool CTouchListUI::Add(CControlUI* pControl)
{
	// The list items should know about us
	IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
	if( pListItem != NULL ) 
	{
		pListItem->SetOwner(this);
		pListItem->SetIndex(GetCount());
	}
	return CContainerUI::Add(pControl);
}

bool CTouchListUI::AddAt(CControlUI* pControl, int iIndex)
{
	if (!CContainerUI::AddAt(pControl, iIndex)) 
		return false;

	// The list items should know about us
	IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
	if( pListItem != NULL ) {
		pListItem->SetOwner(this);
		pListItem->SetIndex(iIndex);
	}

	for(int i = iIndex + 1; i < GetCount(); ++i) {
		CControlUI* p = GetItemAt(i);
		pListItem = static_cast<IListItemUI*>(p->GetInterface(_T("ListItem")));
		if( pListItem != NULL ) {
			pListItem->SetIndex(i);
		}
	}
	if( m_iCurSel >= iIndex ) m_iCurSel += 1;
	return true;
}

bool CTouchListUI::Remove(CControlUI* pControl)
{
	int iIndex = GetItemIndex(pControl);
	if (iIndex == -1)
		return false;

	if (!CContainerUI::RemoveAt(iIndex)) 
		return false;

	for(int i = iIndex; i < GetCount(); ++i) {
		CControlUI* p = GetItemAt(i);
		IListItemUI* pListItem = static_cast<IListItemUI*>(p->GetInterface(_T("ListItem")));
		if( pListItem != NULL ) {
			pListItem->SetIndex(i);
		}
	}

	if( iIndex == m_iCurSel && m_iCurSel >= 0 ) {
		int iSel = m_iCurSel;
		m_iCurSel = -1;
		SelectItem(FindSelectable(iSel, false));
	}
	else if( iIndex < m_iCurSel )
		m_iCurSel -= 1;
	return true;
}

bool CTouchListUI::RemoveAt(int iIndex)
{
	if (!CContainerUI::RemoveAt(iIndex)) return false;

	for(int i = iIndex; i < GetCount(); ++i) {
		CControlUI* p = GetItemAt(i);
		IListItemUI* pListItem = static_cast<IListItemUI*>(p->GetInterface(_T("ListItem")));
		if( pListItem != NULL ) pListItem->SetIndex(i);
	}

	if( iIndex == m_iCurSel && m_iCurSel >= 0 ) {
		int iSel = m_iCurSel;
		m_iCurSel = -1;
		SelectItem(FindSelectable(iSel, false));
	}
	else if( iIndex < m_iCurSel ) m_iCurSel -= 1;
	return true;
}

void CTouchListUI::RemoveAll()
{
	m_iCurSel = -1;
	m_iExpandedItem = -1;
	CContainerUI::RemoveAll();
}


void CTouchListUI::SetPos(RECT rc)
{
	if ( m_bAutoLayout == true )
	{
		CTileLayoutUI::SetPos(rc);
	}
	else
	{
		CTileLayoutUI::SetPos2(rc);
	}
}


void CTouchListUI::EnsureVisible(int iIndex)
{
	if( m_iCurSel < 0 ) return;
	RECT rcItem = GetItemAt(iIndex)->GetPos();
	RECT rcList = GetPos();
	RECT rcListInset = GetInset();

	rcList.left += rcListInset.left;
	rcList.top += rcListInset.top;
	rcList.right -= rcListInset.right;
	rcList.bottom -= rcListInset.bottom;

	CScrollBarUI* pHorizontalScrollBar = GetHorizontalScrollBar();
	if( pHorizontalScrollBar && pHorizontalScrollBar->IsVisible() ) 
		rcList.bottom -= pHorizontalScrollBar->GetFixedHeight();

	int iPos = GetScrollPos().cy;
	if( rcItem.top >= rcList.top && rcItem.bottom < rcList.bottom ) return;
	int dx = 0;
	if( rcItem.top < rcList.top ) dx = rcItem.top - rcList.top;
	if( rcItem.bottom > rcList.bottom ) dx = rcItem.bottom - rcList.bottom;
	Scroll(0, dx);
}

void CTouchListUI::Scroll(int dx, int dy)
{
	if( dx == 0 && dy == 0 ) return;
	SIZE sz = GetScrollPos();
	SetScrollPos(CDuiSize(sz.cx + dx, sz.cy + dy));
}


void CTouchListUI::DoEvent(TEventUI& event) 
{
	if( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
		if( m_pParent != NULL ) 
			m_pParent->DoEvent(event);
		else 
			CTileLayoutUI::DoEvent(event);
		return;
	}

	if( event.Type == UIEVENT_SETFOCUS ) 
	{
		m_bFocused = true;
		return;
	}
	if( event.Type == UIEVENT_KILLFOCUS ) 
	{
		m_bFocused = false;
		return;
	}

	switch( event.Type ) {
	case UIEVENT_KEYDOWN:
		switch( event.chKey ) {
		case VK_UP:
			SelectItem(FindSelectable(m_iCurSel - 1, false), true);
			return;
		case VK_DOWN:
			SelectItem(FindSelectable(m_iCurSel + 1, true), true);
			return;
		case VK_PRIOR:
			PageUp();
			return;
		case VK_NEXT:
			PageDown();
			return;
		case VK_HOME:
			SelectItem(FindSelectable(0, false), true);
			return;
		case VK_END:
			SelectItem(FindSelectable(GetCount() - 1, true), true);
			return;
		case VK_RETURN:
			if( m_iCurSel != -1 ) GetItemAt(m_iCurSel)->Activate();
			return;
		}
		break;
	case UIEVENT_SCROLLWHEEL:
		{
			switch( LOWORD(event.wParam) ) {
			case SB_LINEUP:
				if( m_bScrollSelect ) SelectItem(FindSelectable(m_iCurSel - 1, false), true);
				else LineUp();
				return;
			case SB_LINEDOWN:
				if( m_bScrollSelect ) SelectItem(FindSelectable(m_iCurSel + 1, true), true);
				else LineDown();
				return;
			}
		}
		break;
	}

	if( event.Type == UIEVENT_BUTTONDOWN || event.Type == UIEVENT_RBUTTONDOWN )
	{
		m_ptLButtonDown = event.ptMouse;
		m_bLButtonDown = TRUE;

		return;
	}
	if( event.Type == UIEVENT_BUTTONUP ) 
	{
		m_bLButtonDown = FALSE;

		return;
	}
	if ( event.Type == UIEVENT_MOUSEMOVE )
	{
		//实现列表拖拽
		if ( m_bLButtonDown  )
		{
			int nYPos = 0;
			int nXPos = 0;
			int cyLine = 0;
			SIZE sz;
			if( m_ptLButtonDown.y > event.ptMouse.y )
			{
				nYPos = m_ptLButtonDown.y - event.ptMouse.y;
				nXPos = m_ptLButtonDown.x - event.ptMouse.x;

				sz = GetScrollPos();
				sz.cx += nXPos;
				sz.cy += nYPos;
				SetScrollPos(sz);

				m_ptLButtonDown.x -= nXPos;
				m_ptLButtonDown.y -= nYPos;
			}
			else if( m_ptLButtonDown.y < event.ptMouse.y )
			{
				nYPos = event.ptMouse.y - m_ptLButtonDown.y;
				nXPos = event.ptMouse.x - m_ptLButtonDown.x;

				sz = GetScrollPos();
				sz.cx -= nXPos;
				sz.cy -= nYPos;
				SetScrollPos(sz);

				m_ptLButtonDown.x += nXPos;
				m_ptLButtonDown.y += nYPos;
			}
		}
		return;
	}
	CTileLayoutUI::DoEvent(event);
}



bool CTouchListUI::GetScrollSelect()
{
	return m_bScrollSelect;
}

void CTouchListUI::SetScrollSelect(bool bScrollSelect)
{
	m_bScrollSelect = bScrollSelect;
}

int CTouchListUI::GetCurSel() const
{
	return m_iCurSel;
}

bool CTouchListUI::SelectItem(int iIndex, bool bTakeFocus)
{
	if( iIndex == m_iCurSel ) 
		return true;

	int iOldSel = m_iCurSel;
	// We should first unselect the currently selected item
	if( m_iCurSel >= 0 ) {
		CControlUI* pControl = GetItemAt(m_iCurSel);
		if( pControl != NULL) {
			IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
			if( pListItem != NULL ) pListItem->Select(false);
		}

		m_iCurSel = -1;
	}
	if( iIndex < 0 ) return false;

	CControlUI* pControl = GetItemAt(iIndex);
	if( pControl == NULL ) return false;
	if( !pControl->IsVisible() ) return false;
	if( !pControl->IsEnabled() ) return false;

	IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
	if( pListItem == NULL ) return false;
	m_iCurSel = iIndex;
	if( !pListItem->Select(true) ) {
		m_iCurSel = -1;
		return false;
	}
	EnsureVisible(m_iCurSel);
	if( bTakeFocus ) pControl->SetFocus();
	if( m_pManager != NULL ) {
		m_pManager->SendNotify(this, DUI_MSGTYPE_ITEMSELECT, m_iCurSel, iOldSel);
	}

	return true;
}

TListInfoUI* CTouchListUI::GetListInfo()
{
	return &m_ListInfo;
}

void CTouchListUI::SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue )
{
	if( _tcscmp(pstrName, _T("itemselectedimage")) == 0 ) SetSelectedItemImage(pstrValue);
	else if( _tcscmp(pstrName, _T("itembkimage")) == 0 ) SetItemBkImage(pstrValue);
	else if( _tcscmp(pstrName, _T("itemtextcolor")) == 0 ) {
		if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
		LPTSTR pstr = NULL;
		DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
		SetItemTextColor(clrColor);
	}
	else if( _tcscmp(pstrName, _T("itemhotimage")) == 0 ) SetHotItemImage(pstrValue);
	else if( _tcscmp(pstrName, _T("itemselectedtextcolor")) == 0 ) {
		if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
		LPTSTR pstr = NULL;
		DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
		SetSelectedItemTextColor(clrColor);
	}
	else if( _tcscmp(pstrName, _T("itemdisabledtextcolor")) == 0 ) {
		if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
		LPTSTR pstr = NULL;
		DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
		SetDisabledItemTextColor(clrColor);
	}
	else if( _tcscmp(pstrName, _T("itemdisabledimage")) == 0 ) SetDisabledItemImage(pstrValue);
	else if( _tcscmp(pstrName, _T("autolayout")) == 0)  SetIsAutoLayout( pstrValue );
	else CTileLayoutUI::SetAttribute(pstrName, pstrValue);
}

void CTouchListUI::SetSelectedItemImage( LPCTSTR pStrImage )
{
	m_ListInfo.sSelectedImage = pStrImage;
}

LPCTSTR CTouchListUI::GetSelectedItemImage() const
{
	return m_ListInfo.sSelectedImage;
}

void CTouchListUI::SetItemBkImage(LPCTSTR pStrImage)
{
	m_ListInfo.sBkImage = pStrImage;
	Invalidate();
}

LPCTSTR CTouchListUI::GetItemBkImage() const
{
	return m_ListInfo.sBkImage;
}

LPCTSTR CTouchListUI::GetHotItemImage() const
{
	return m_ListInfo.sHotImage;
}

void CTouchListUI::SetHotItemImage( LPCTSTR pStrImage )
{
	m_ListInfo.sHotImage = pStrImage;
	Invalidate();
}

LPCTSTR CTouchListUI::GetDisabledItemImage() const
{
	return m_ListInfo.sDisabledImage;
}

void CTouchListUI::SetDisabledItemImage( LPCTSTR pStrImage )
{
	m_ListInfo.sDisabledImage = pStrImage;
	Invalidate();
}

DWORD CTouchListUI::GetDisabledItemTextColor() const
{
	return m_ListInfo.dwDisabledTextColor;
}

void CTouchListUI::SetDisabledItemTextColor( DWORD dwTextColor )
{
	m_ListInfo.dwDisabledTextColor = dwTextColor;
	Invalidate();
}

void CTouchListUI::SetItemTextColor( DWORD dwTextColor )
{
	m_ListInfo.dwTextColor = dwTextColor;
	Invalidate();
}

DWORD CTouchListUI::GetItemTextColor() const
{
	return m_ListInfo.dwTextColor;
}

void CTouchListUI::SetSelectedItemTextColor( DWORD dwTextColor )
{
	m_ListInfo.dwSelectedTextColor = dwTextColor;
	Invalidate();
}

DWORD CTouchListUI::GetSelectedItemTextColor() const
{
	return m_ListInfo.dwSelectedTextColor;
}

void CTouchListUI::SetIsAutoLayout( LPCTSTR pIsAutoLayout )
{

	if (( _tcscmp(_T("false"),pIsAutoLayout) ==0 )||( _tcscmp(_T("FALSE"),pIsAutoLayout) ==0))
	{
		m_bAutoLayout = false;
	}
	else
	{
		m_bAutoLayout = true;
	}
}

bool CTouchListUI::IsAutoLayout() const
{
	return m_bAutoLayout;
}

void CTouchListUI::ScrollToIndexLetter( int nItemIndex )
{
	CControlUI* pCtrl = GetItemAt(0);
	if (!pCtrl)
	{
		return;
	}

	RECT rc = pCtrl->GetPos();
	RECT rcPadding = pCtrl->GetPadding();

	int nCount = nItemIndex/GetColumns();
	SIZE sz = GetScrollPos();
	sz.cy = (rc.bottom - rc.top + rcPadding.bottom + rcPadding.top) * nCount;
	SetScrollPos(sz);
}
}