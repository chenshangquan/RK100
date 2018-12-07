#ifndef __UIVERTICALLAYOUT_H__
#define __UIVERTICALLAYOUT_H__

#pragma once

namespace DuiLib
{
	class UILIB_API CVerticalLayoutUI : public CContainerUI
	{
	public:
		CVerticalLayoutUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		UINT GetControlFlags() const;

		void SetSepHeight(int iHeight);
		int GetSepHeight() const;
		void SetSepImmMode(bool bImmediately);
		//�����Ƿ���Ӧ����϶���Ϣ dyy 2015-5-15 
		void SetSlideable(bool bSliderable);
		bool IsSepImmMode() const;
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void DoEvent(TEventUI& event);

		void SetPos(RECT rc);
		void DoPostPaint(HDC hDC, const RECT& rcPaint);

		RECT GetThumbRect(bool bUseNew = false) const;

	protected:
		int m_iSepHeight;                     //�ָ����߶�
		UINT m_uButtonState;
		POINT ptLastMouse;
		RECT m_rcNewPos;                      //�ؼ�����λ��
		bool m_bImmMode;                      //�Ƿ�Ϊ����ģʽ(�����ı��С)
		bool m_bSliderable;

		bool            m_bLButtonDown;
		POINT           m_ptLButtonDown;      //��갴��λ��
	};
}
#endif // __UIVERTICALLAYOUT_H__
