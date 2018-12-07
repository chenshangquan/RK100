#ifndef __UITOUCHLIST_H__
#define __UITOUCHLIST_H__

#pragma once
#include "Core\UIBase.h"
#include "Layout/UITileLayout.h"
#include "Control/UIList.h"

namespace DuiLib
{

class UILIB_API CTouchListUI : public CTileLayoutUI, public IListOwnerUI
{
public:
	CTouchListUI();
	~CTouchListUI();

	LPCTSTR GetClass() const;
	UINT GetControlFlags() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	bool GetScrollSelect();
	void SetScrollSelect(bool bScrollSelect);
	int GetCurSel() const;
	bool SelectItem(int iIndex, bool bTakeFocus = false);

	TListInfoUI* GetListInfo();

	//CControlUI* GetItemAt(int iIndex) const;
	//int GetItemIndex(CControlUI* pControl) const;
	bool SetItemIndex(CControlUI* pControl, int iIndex);
	int GetCount() const;
	bool Add(CControlUI* pControl);
	bool AddAt(CControlUI* pControl, int iIndex);
	bool Remove(CControlUI* pControl);
	bool RemoveAt(int iIndex);
	void RemoveAll();

	void EnsureVisible(int iIndex);
	void Scroll(int dx, int dy);

	void SetPos(RECT rc);
	void DoEvent(TEventUI& event);

	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	LPCTSTR GetSelectedItemImage() const;
	void SetSelectedItemImage(LPCTSTR pStrImage); 
	LPCTSTR GetItemBkImage() const;
	void SetItemBkImage(LPCTSTR pStrImage);
	LPCTSTR GetHotItemImage() const;
	void SetHotItemImage(LPCTSTR pStrImage);
	LPCTSTR GetDisabledItemImage() const;
	void SetDisabledItemImage(LPCTSTR pStrImage);
	DWORD GetDisabledItemTextColor() const;
	void SetDisabledItemTextColor(DWORD dwTextColor);
	DWORD GetItemTextColor() const;
	void SetItemTextColor(DWORD dwTextColor);
	DWORD GetSelectedItemTextColor() const;
	void SetSelectedItemTextColor(DWORD dwTextColor);


	//letter索引时列表跳到索引位置 dyy 2015-5-26
	void ScrollToIndexLetter(int nItemIndex);

	void SetIsAutoLayout( LPCTSTR pIsAutoLayout );
	bool IsAutoLayout() const;
protected:
	bool m_bScrollSelect;
	int m_iCurSel;
	int m_iExpandedItem;
	
	bool            m_bLButtonDown;
	POINT           m_ptLButtonDown;      //鼠标按下位置

	bool m_bAutoLayout;
	TListInfoUI m_ListInfo;
};

} // namespace DuiLib

#endif // __UITOUCHLIST_H__

