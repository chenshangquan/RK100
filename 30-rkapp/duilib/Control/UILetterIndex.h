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
	/**  根据点击位置获取点击的字母
     *  @param[in] point  鼠标点击位置
     *  @return  点中的字母索引
     */
	int GetClickLetter( POINT point );

protected:
	UINT   m_uButtonState;
	float  m_fLetterHeight; //每个字母的高度
	int    m_nClickLetter;
};

} // namespace DuiLib

#endif // __UILETTERINDEX_H__

