#include "stdafx.h"
#include "UICheckBox.h"

namespace DuiLib
{
	LPCTSTR CCheckBoxUI::GetClass() const
	{
		return _T("CheckBoxUI");
	}

    void CCheckBoxUI::SetCheck(bool bCheck)
    {
        Selected(bCheck);
    }

	bool  CCheckBoxUI::GetCheck() const
	{
		return IsSelected();
	}

	void CCheckBoxUI::PaintStatusImage( HDC hDC )
	{
		if( (m_uButtonState & UISTATE_PUSHED) != 0 ) {
		
			if (GetCheck())//Ñ¡ÖÐÊ± 
			{
				if( !m_sSelPushedImage.IsEmpty() ) {
					if( !DrawImage(hDC, (LPCTSTR)m_sSelPushedImage) ){
						m_sSelPushedImage.Empty();
					}
					if( !m_sPushedForeImage.IsEmpty() )
					{
						if( !DrawImage(hDC, (LPCTSTR)m_sPushedForeImage) )
							m_sPushedForeImage.Empty();
						return;
					}
					else goto Label_ForeImage;
				}
			}
			else
			{
				if( !m_sPushedImage.IsEmpty() ) {
					if( !DrawImage(hDC, (LPCTSTR)m_sPushedImage) ){
						m_sPushedImage.Empty();
					}
					if( !m_sPushedForeImage.IsEmpty() )
					{
						if( !DrawImage(hDC, (LPCTSTR)m_sPushedForeImage) )
							m_sPushedForeImage.Empty();
						return;
					}
					else goto Label_ForeImage;
				}
			}
		}

		if( (m_uButtonState & UISTATE_DISABLED) != 0 ) {
			if( GetCheck() && !m_sSelDisabledImage.IsEmpty() )
			{
				if( !DrawImage(hDC, (LPCTSTR)m_sSelDisabledImage) ) 
					m_sSelDisabledImage.Empty();
				    return;
			}
		}

		COptionUI::PaintStatusImage(hDC);

Label_ForeImage:
		if( !m_sForeImage.IsEmpty() ) {
			if( !DrawImage(hDC, (LPCTSTR)m_sForeImage) ) m_sForeImage.Empty();
		}
	}

	void CCheckBoxUI::SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue )
	{
		if( _tcscmp(pstrName, _T("selpushedimage")) == 0 )
		{
			m_sSelPushedImage = pstrValue;
			Invalidate();
		}
		if( _tcscmp(pstrName, _T("seldisabledimage")) == 0 )
		{
			m_sSelDisabledImage = pstrValue;
			Invalidate();
		}
		else COptionUI::SetAttribute(pstrName, pstrValue);
	}

}
