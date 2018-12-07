// DocManager.cpp: implementation of the CDocManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DocManager.h"
#include "ICommonOp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AppFrame
{
	
const tstring CDocManager::chPartitionChar = _T("/");
CDocManager::CDocManager()
{

}

CDocManager::~CDocManager()
{

}

bool CDocManager::GetDoc(const tstring strFile, tstring strTag, 
						 tstring& strValue, const tstring strPath /* = _T */)
{
	DuiLib::CMarkup* pDoc = GetDoc( strFile.c_str() );
	if ( pDoc == NULL )
	{
		return false;
	}

	DuiLib::CMarkupNode pNode = pDoc->GetRoot();
	
	tstring sub_str;
	bool bRet = false;
	int nIndex = 0;

	vector<tstring> vecSubStr;
	ICommonOp::StringSplit( strPath, CDocManager::chPartitionChar, vecSubStr );

	unsigned int dwIdx = 0;
	while( dwIdx < vecSubStr.size())         
	{
		tstring sub_str = vecSubStr[dwIdx];
		dwIdx++;
		if (sub_str != _T(""))
		{
			pNode = pNode.GetChild( sub_str.c_str() );
			if ( pNode.IsValid() == false )
			{
				return false;
			}
		}
	}

	if ( pNode.IsValid() )
	{
		strValue = pNode.GetAttributeValue( strTag.c_str() );
		
		return !strValue.empty() ;
	}

	return false;
}

CMarkup* CDocManager::GetDoc( LPCTSTR lpszFile )
{
	DuiLib::CMarkup* pDoc = Find(lpszFile);
	if ( pDoc == NULL )
	{
		pDoc = new DuiLib::CMarkup();
		bool bRet = pDoc->LoadFromFile(lpszFile);
		if ( bRet == true )
		{
			Add(lpszFile, pDoc);
			return pDoc;
		}
		else
		{
			delete pDoc;
			pDoc = 0;
		}
	}
	return pDoc;
}

DocNode CDocManager::GetNode(LPCTSTR lpszFile, LPCTSTR lpszPath )
{
	DuiLib::CMarkup* pDoc = GetDoc(lpszFile);
	assert( pDoc != 0 );
	DuiLib::CMarkupNode Node = pDoc->GetRoot();
	tstring sub_str;
	bool bRet = false;

	vector<tstring> vecSubStr;
	ICommonOp::StringSplit(lpszPath, CDocManager::chPartitionChar, vecSubStr);
	unsigned int dwIdx = 0;
	while( dwIdx < vecSubStr.size() )         
	{
		tstring sub_str = vecSubStr[dwIdx++];
		if (!sub_str.empty())
		{
			Node = Node.GetChild( sub_str.c_str() );
		}
	}

	return Node;
}

} // namespace AppFrame end 