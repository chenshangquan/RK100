#ifndef __UILETTERINDEX_H__
#define __UILETTERINDEX_H__
#pragma once

namespace DuiLib
{

class CLetterIndexUI : public CLabelUI
{
public:
	CLetterIndexUI(void);
	~CLetterIndexUI(void);

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	void DoEvent(TEventUI& event);

	void PaintText(HDC hDC);

protected:
	/**  ���ݵ��λ�û�ȡ�������ĸ
     *  @param[in] point  �����λ��
     *  @return  ���е���ĸ����
     */
	int GetClickLetter( POINT point );

protected:
	UINT   m_uButtonState;
	float  m_fLetterHeight; //ÿ����ĸ�ĸ߶�
	int    m_nClickLetter;
};

} // namespace DuiLib

#endif // __UILETTERINDEX_H__

