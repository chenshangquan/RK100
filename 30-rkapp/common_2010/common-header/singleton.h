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
* ��	����Singleton
* ��    �ܣ��ṩͳһ������ӿ�
* ����˵����1. ������           class CData : public CSingleton<CData>
			2. ��������(��CData��cpp�ļ���) 
			template<> CData* CSingleton<CData>::m_psSingleton  = NULL;
			
			3. �ڳ����ʼ�ĳ�ʼ������г�ʼ��
			new CData();

			4. ����ʼ�����󣬾Ϳ����ڳ��������ط�ʹ��
			
			CData* pData = CSingleton<CData>::GetSingleTonPtr();

			����û�ж�CData�Ĺ��캯���������ƣ������м���3��ʱ��ȷ��CDataֻ��ʼ��һ��

* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2010/07/16	v1.0		Ĳ��ï		����
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
	
	// ��ȡָ��Ͷ���
	static T& GetSingleton(){ return *m_psSingleton; }
	
	static T* GetSingletonPtr(){ return m_psSingleton; }
};

/*---------------------------------------------------------------------
* ��	����LazySingleton
* ��    �ܣ�����ģʽSingleton
* ����˵����
* 1.������ʹ��ʱ�Զ����ɣ������ֶ�����
* 2.���������̰߳�ȫ
* 3.ʹ��ʱ��Ҫ��CPP�ļ������INIT_LAZY_SINGLTON���ʼ��singleton״̬
* ���磺
* typedef LazySingleton<CDecoderFactory> DecoderSingleton;
* INIT_LAZY_SINGLTON( DecoderSingleton )
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2013/09/14	v1.0		�޿���		����
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
	// ��ʼ�����
	volatile static u32 s_initState;
	// ����������˽�У���ֹ��������
	static T& SingletonCreator()
	{
		// ͨ����̬�ֲ���������֤�ڳ����˳���ʱ���Զ�����
		static T s_Singleton;
		return s_Singleton;
	};
	// ���캯����operator=˽��
	LazySingleton(){};
	virtual ~LazySingleton(){}
	LazySingleton ( const LazySingleton& );
	LazySingleton& operator=( const LazySingleton& );
public:
	// ��ȡָ��Ͷ���
	static T& GetSingleton()
	{
		// ͨ��CAS������֤�̰߳�ȫ
		// �����û��������ת״̬Ϊ���ڴ���
		s32 OldVal = InterlockedCompareExchange( &s_initState, SINGLETON_STATE_INITING, SINGLETON_STATE_NULL );
		if ( OldVal == SINGLETON_STATE_NULL )
		{
			// ��ʱ��̬�ֲ������һ�α�����
			T& cSingleton = SingletonCreator();
			// �����ɹ����޸�״̬
			InterlockedExchange( &s_initState, SINGLETON_STATE_DONE );
			return cSingleton;
		}
		else
		{
			// ������ڴ�������ȴ�ֱ�������ɹ�
			while ( s_initState == SINGLETON_STATE_INITING )
			{
				Sleep(0);
			};
			// ��ȡ�����õ�����
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
