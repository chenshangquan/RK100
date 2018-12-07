#pragma once
#include "DragDef.h"
namespace DuiLib{
/**  Singleton
  *  µ¥Àý»ùÀà
  */  
template<class T> class DuiSingleton
{
protected:
	static T* ms_pSingleton;
public:
	DuiSingleton( void )
	{
		assert( !ms_pSingleton );
		ms_pSingleton = static_cast<T*>(this);
	}
	~DuiSingleton( void )
	{
		assert( ms_pSingleton );
		ms_pSingleton = 0;
	}
	static T& GetSingleton( void )
	{
		assert( ms_pSingleton );
		return ( *ms_pSingleton );
	}
	static T* GetSingletonPtr( void )
	{
		return ms_pSingleton;
	}
	static void ReleaseSingleton()
	{
		if ( ms_pSingleton != 0 )
		{
			delete ms_pSingleton;
			ms_pSingleton = 0;
		}
	}
};

class IDragController : public DuiSingleton<IDragController>
{
public:
	~IDragController(){};
	virtual LRESULT HandleMessage(LPMSG pMsg) = 0;
};

class IDragDataMgr : public DuiSingleton<IDragDataMgr>
{
public:
	virtual ~IDragDataMgr(){}
	virtual bool SetData(LPCTSTR lpDataName, LPVOID lpData, const int nSize) = 0;
	virtual LPCTSTR GetDataName() = 0;
	virtual bool GetData(LPVOID lpData, int &nSize) = 0;
	virtual bool ReleaseData() = 0;
};


}