// DocManager.h: interface for the CDocManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCMANAGER_H__C8280F2F_CBC4_4C18_B4AC_D8900ADB767D__INCLUDED_)
#define AFX_DOCMANAGER_H__C8280F2F_CBC4_4C18_B4AC_D8900ADB767D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace AppFrame
{
	
class CDocManager : public IDocManager, public tmplContainer< tstring, DuiLib::CMarkup* >
{
public:
	static const tstring chPartitionChar;
public:
	CDocManager();
	virtual ~CDocManager();
	virtual bool GetDoc( const tstring strFile, tstring strTag, tstring& strValue, const tstring strPath = _T("") );
	virtual DocNode GetNode( LPCTSTR lpszFile, LPCTSTR lpszPath ) ;
protected:
/** 获得文件句柄 
 *  @param[in] 文件名
 *  @node 
 *  @return 文件句柄
 */
	CMarkup* GetDoc(LPCTSTR lpszFile);
};

} // namespace AppFrame end 

#endif // !defined(AFX_DOCMANAGER_H__C8280F2F_CBC4_4C18_B4AC_D8900ADB767D__INCLUDED_)
