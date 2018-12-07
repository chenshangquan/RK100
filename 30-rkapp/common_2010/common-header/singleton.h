// singleton.h: interface for the CSingleTon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SINGLETON_H__AEF4D8BA_C3E8_44C1_874D_854F10BE573A__INCLUDED_)
#define AFX_SINGLETON_H__AEF4D8BA_C3E8_44C1_874D_854F10BE573A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "kdvtype.h"

/*---------------------------------------------------------------------
* 类	名：Singleton
* 功    能：提供统一单件类接口
* 特殊说明：1. 类声明           class CData : public CSingleton<CData>
			2. 变量声明(在CData的cpp文件中) 
			template<> CData* CSingleton<CData>::m_psSingleton  = NULL;
			
			3. 在程序最开始的初始化点进行初始化
			new CData();

			4. 当初始化过后，就可以在程序其他地方使用
			
			CData* pData = CSingleton<CData>::GetSingleTonPtr();

			由于没有对CData的构造函数进行限制，所以切记在3的时候，确保CData只初始化一次

* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/07/16	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
template<typename T> class CSingleton
{
protected:
	static T* m_psSingleton;
	
public:
	CSingleton()
	{
		m_psSingleton = static_cast<T*>(this);
	}
	
	virtual ~CSingleton()
	{
		m_psSingleton = NULL;
	}
	
	// 获取指针和对象
	static T& GetSingleton(){ return *m_psSingleton; }
	
	static T* GetSingletonPtr(){ return m_psSingleton; }
};

/*---------------------------------------------------------------------
* 类	名：LazySingleton
* 功    能：懒汉模式Singleton
* 特殊说明：
* 1.可以在使用时自动生成，无需手动创建
* 2.创建过程线程安全
* 3.使用时需要在CPP文件里调用INIT_LAZY_SINGLTON宏初始化singleton状态
* 例如：
* typedef LazySingleton<CDecoderFactory> DecoderSingleton;
* INIT_LAZY_SINGLTON( DecoderSingleton )
* 修改记录：
* 日期			版本		修改人		修改记录
* 2013/09/14	v1.0		邹俊龙		创建
----------------------------------------------------------------------*/

#define SINGLETON_STATE_NULL	0
#define SINGLETON_STATE_INITING	1
#define SINGLETON_STATE_DONE	2

#define INIT_LAZY_SINGLTON( name ) \
	u32 volatile name::s_initState = SINGLETON_STATE_NULL;

template<typename T>
class LazySingleton
{
private:
	// 初始化标记
	volatile static u32 s_initState;
	// 创建函数，私有，防止被外界调用
	static T& SingletonCreator()
	{
		// 通过静态局部函数，保证在程序退出的时候自动析构
		static T s_Singleton;
		return s_Singleton;
	};
	// 构造函数及operator=私有
	LazySingleton(){};
	virtual ~LazySingleton(){}
	LazySingleton ( const LazySingleton& );
	LazySingleton& operator=( const LazySingleton& );
public:
	// 获取指针和对象
	static T& GetSingleton()
	{
		// 通过CAS操作保证线程安全
		// 如果还没创建，旋转状态为正在创建
		s32 OldVal = InterlockedCompareExchange( &s_initState, SINGLETON_STATE_INITING, SINGLETON_STATE_NULL );
		if ( OldVal == SINGLETON_STATE_NULL )
		{
			// 此时静态局部对象第一次被创建
			T& cSingleton = SingletonCreator();
			// 创建成功，修改状态
			InterlockedExchange( &s_initState, SINGLETON_STATE_DONE );
			return cSingleton;
		}
		else
		{
			// 如果正在创建，则等待直到创建成功
			while ( s_initState == SINGLETON_STATE_INITING )
			{
				Sleep(0);
			};
			// 获取创建好的内容
			T& cSingleton = SingletonCreator();
			return cSingleton;
		}
	}

	static T* GetSingletonPtr()
	{
		T& cSingleton = GetSingleton();
		return &cSingleton;
	}
};

#endif // !defined(AFX_SINGLETON_H__AEF4D8BA_C3E8_44C1_874D_854F10BE573A__INCLUDED_)
