#pragma once
#include "DragInterface.h"
namespace DuiLib{
class CDragDataMgr : public IDragDataMgr
{
public:
	CDragDataMgr();
	~CDragDataMgr();
	virtual bool SetData(LPCTSTR lpDataName, LPVOID lpData, const int nSize);
	virtual LPCTSTR GetDataName();
	virtual bool GetData(LPVOID lpData, int &nSize);
	virtual bool ReleaseData();
protected:
	int m_nDataSize;
	CDuiString m_strDataName;
	LPVOID m_lpData;

};

}