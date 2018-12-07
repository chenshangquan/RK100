#ifndef __UIPROGRESS_H__
#define __UIPROGRESS_H__

#pragma once

namespace DuiLib
{
	class UILIB_API CProgressUI : public CLabelUI
	{
	public:
		CProgressUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		bool IsHorizontal();
		void SetHorizontal(bool bHorizontal = true);
		bool IsStretchForeImage();
		void SetStretchForeImage(bool bStretchForeImage = true);
		int GetMinValue() const;
		void SetMinValue(int nMin);
		int GetMaxValue() const;
		void SetMaxValue(int nMax);
		int GetValue() const;
		virtual void SetValue(int nValue);
		LPCTSTR GetForeImage() const;
		void SetForeImage(LPCTSTR pStrImage);
		void SetForeColor(DWORD dwForeBkColor);//add wangkui 2016-10-13

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void PaintStatusImage(HDC hDC);

	protected:
		bool m_bHorizontal;
		bool m_bStretchForeImage;
		int m_nMax;
		int m_nMin;
		int m_nValue;

		CDuiString m_sForeImage;
		CDuiString m_sForeImageModify;
		DWORD m_dwForeBkColor;//add wangkui 2016-10-13
	};

} // namespace DuiLib

#endif // __UIPROGRESS_H__
