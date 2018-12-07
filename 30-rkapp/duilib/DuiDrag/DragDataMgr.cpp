#include "StdAfx.h"
#include "DragDataMgr.h"
namespace DuiLib{
bool CDragDataMgr::SetData( LPCTSTR lpDataName, LPVOID lpData, const int nSize )
{
	if ( m_lpData != NULL)
	{
		ReleaseData();
	}
	m_strDataName = lpDataName;
	m_nDataSize = nSize;
	if ( nSize != 0 )
	{
		m_lpData = (LPVOID)new BYTE[nSize];
		if ( m_lpData != NULL )
		{
			memcpy(m_lpData, lpData, nSize);
			return true;
		}
	}
	return false;
}

bool CDragDataMgr::ReleaseData()
{
	if ( m_lpData != NULL && m_nDataSize != 0 )
	{
		delete m_lpData;
		m_lpData = NULL;
		m_nDataSize = 0;
		m_strDataName = _T("");
		return true;
	}
	return false;
}

bool CDragDataMgr::GetData( LPVOID lpData, int &nSize )
{
	if (lpData != NULL && m_lpData != NULL && m_nDataSize != 0)
	{
		memcpy(lpData, m_lpData, m_nDataSize);
		nSize = m_nDataSize;
		return ReleaseData();
	}
	return false;
}

CDragDataMgr::CDragDataMgr()
{
	m_lpData = NULL;
	m_nDataSize = 0;
	m_strDataName = _T("");
}

CDragDataMgr::~CDragDataMgr()
{
	if(m_lpData)
	{
		delete m_lpData;
	}
	m_lpData = NULL;
	m_nDataSize = 0;
	m_strDataName = _T("");
}




LPCTSTR DuiLib::CDragDataMgr::GetDataName()
{
	return m_strDataName;
}

}