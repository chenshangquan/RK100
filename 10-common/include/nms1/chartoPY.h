/*---------------------------------------------------------------------
* 类	名：CCharToPY
* 功    能：汉字转拼音
* 特殊说明：用于获取汉字的拼音首字母
* 修改记录：
* 日期			版本		修改人		修改记录
* 2012/12/05	v1.0		肖楚然		创建
----------------------------------------------------------------------*/

#if !defined(AFX_CHARTOPY_H__B2F2F86E_CDB6_4CD0_A359_06334B8FC32A__INCLUDED_)
#define AFX_CHARTOPY_H__B2F2F86E_CDB6_4CD0_A359_06334B8FC32A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCharToPY  
{
public:
	CCharToPY();
	virtual ~CCharToPY();

    /**
    * 功能:	将字符串转化为拼音首字母
	* @param [in]  strName 字符串
    * @param [out]  strFirstLetter 拼音
	* @return  无
	* @remarks
	*/
    static void GetFirstLetter(CString strName, CString& strFirstLetter);

    static BOOL In(int Lp, int Hp,int Value);
    char GetPYChar(CString HZ) ;

    /**
    * 功能:	将一个汉字转化为拼音首字母
	* @param [in]  c1、c2 汉字的两个字符
	* @return  该汉字的拼音
	* @remarks
	*/
    static char GetPYChar(TCHAR c1,TCHAR c2); 

    //二级汉字拼音表
    static CString m_ArrQWSecond[32];   //区位码字母头: 56区~87区对应0~30
};

#endif // !defined(AFX_CHARTOPY_H__B2F2F86E_CDB6_4CD0_A359_06334B8FC32A__INCLUDED_)
