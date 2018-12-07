#ifndef TEMPLATECLASS_H
#define TEMPLATECLASS_H
/*---------------------------------------------------------------------
* 类	名：Singleton
* 功    能：单例类统一接口
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/05/09	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
#pragma warning( disable : 4786 )
#pragma warning( disable : 4503 )
#pragma warning( disable : 4800 )
#include <assert.h>
#include <string>
#include <map>
namespace AutoUIFactory
{

/*****************************************************************************
	* 功能:单例基类	 
	* @remarks	该基类的子类无需进行初始化等创建操作，可直接通过GetSingletonPtr()来获取指针 
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2012/11/29     1.0         俞锦锦      创建
 ******************************************************************************/
template<class T> class ISingleTon
{
	protected:
		static T* ms_pSingleton; 
	
	
		ISingleTon( void )
		{  
		}

	public:
		~ISingleTon( void )
		{
		   RemoveInstance();
			
		}
	 
		static T* GetSingletonPtr( void )
		{  
			if ( NULL == ms_pSingleton )
			{
				ms_pSingleton = new T ;
			}
			return ms_pSingleton;
		}


		static void RemoveInstance()
		{
			if(ms_pSingleton)
			{
				delete ms_pSingleton;
			}
			ms_pSingleton = NULL;
		}
};

template <class T> T * ISingleTon<T>::ms_pSingleton = NULL;
 

template<class T> class Singleton
{
protected:
	static T* ms_pSingleton;
public:
	Singleton( void )
	{
		assert( !ms_pSingleton );
		ms_pSingleton = static_cast<T*>(this);
	}
	~Singleton( void )
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

    static void RemoveInstance( void )
    {
        ms_pSingleton = NULL;
	}
};

class IArgs
{
public:
	IArgs( std::string strType ) : m_strType( strType ){}
	virtual ~IArgs(){}
	std::string GetType() const { return m_strType; } 
protected:
	std::string m_strType;
};

class IObserver
{
public:
	virtual ~IObserver(){}
	virtual void Update( IArgs* pArgs ) = 0;
};

/*---------------------------------------------------------------------
* 类	名：ICallBackFuncBase
* 功    能：回调函数接口
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/08/20	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
class ICallBackFuncBase
{
public:
	virtual ~ICallBackFuncBase(){}
	virtual bool operator()( const IArgs& args ) = 0;
};

/*---------------------------------------------------------------------
* 类	名：CMemberCallBackFunc
* 功    能：为成员函数定义的回调函数
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/08/20	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
template<class T> class CMemberCallBackFunc : public ICallBackFuncBase
{
public:
    //定义回调函数的格式
    typedef bool (T::*MemberFunctionType)( const IArgs& args );
	
	// 构造的时候需要为函数赋值
    CMemberCallBackFunc( MemberFunctionType pFunc, T* pObject ) : m_pObject(pObject), m_pFuc( pFunc ) {}
	
    virtual bool operator()( const IArgs& args )
    {
        return (m_pObject->*m_pFuc)( args );
    }
	
private:
	T* m_pObject;
    MemberFunctionType m_pFuc;	
};

/*---------------------------------------------------------------------
* 类	名：CMemberCallBackFunc
* 功    能：为成员函数定义的回调函数
* 特殊说明：
* 修改记录：
* 日期			版本		修改人		修改记录
* 2010/08/20	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
class CCallBackFunc : public ICallBackFuncBase
{
public:
	virtual bool operator()( const IArgs& args)
	{
		return m_pFuc(args);
	}
	
    //定义回调函数的格式
    typedef bool (CallBackFunc)( const IArgs& args);
	
	// 构造的时候需要为函数赋值
    CCallBackFunc(CallBackFunc* pFunc) : m_pFuc( pFunc ) {}
	
private:
    CallBackFunc* m_pFuc;	
};

//----------------------------------------------------------
//类    名: IItem
//功    能: 条目基类 采用Composite模式
//主要接口: 提供删除、添加、设置、等操作,
//特殊说明: DATA需要重载操作符== = 以及Clone函数 由于使用了map，KEY需要重载<操作符
//修改记录:
//日期		版本		修改人		修改记录
//2010/4/26	V1.0		muxingmao	创建
//----------------------------------------------------------
enum EmItemType
{
	emItem,
	emGroup
};
template<class DATA,typename KEY>
class IItem 
{
public:
	IItem()
	{
		m_emItemType	= emItem;
		m_pParentItem	= 0;
	}
	virtual ~IItem()
	{
		if ( 0 != m_ptItemData )
		{
			delete m_ptItemData;
			m_ptItemData = 0;
		}
	}
	
	// 添加子项 内部会拷贝一次，所以如果在外面new的参数，请自行delete
	virtual IItem<DATA,KEY>*	AddItem( KEY key, IItem<DATA,KEY>* pItem ) {return 0;}
	virtual IItem<DATA,KEY>*	AddItem( KEY key, DATA* pData, EmItemType emType ) {return 0;}

	// 获得子项
	virtual IItem<DATA,KEY>*	GetItemByKey( KEY key ){ return 0; }
	// 获得子项
	virtual IItem<DATA,KEY>*	GetItemByIndex( int nIndex ){ return 0; }
	// 获得子项
	virtual IItem<DATA,KEY>*	GetItemByData( DATA* pData ){ return 0; }
	// 删除子项
	virtual bool				DeleteItem( KEY key, bool bDeleteData = true ) { return false; }
	// 删除所有子项
	virtual bool				DeleteAllItem( bool bDeleteData = true ) { return false; }
	// 获得子项数据
	virtual DATA*				GetItemData(){ return m_ptItemData; }
	// 设置条目数据
	virtual bool		SetItemData( DATA* ptItemData )
	{ 
		if ( m_ptItemData == ptItemData || ptItemData == 0 )
		{
			return false;
		}
		if ( m_ptItemData != 0 )
		{
			delete m_ptItemData;
			m_ptItemData = 0;
		}
		m_ptItemData = ptItemData->Clone();
		return true; 
	}

	// 获得条目数量
	virtual int					GetItemCount() = 0;
	// 存储读取条目 有序列化需求的时候添加
	//	virtual void				Serialize( CArchive& ar ) = 0;
	// 修改条目
	virtual bool				ModifyItemKey( KEY keyNew ) = 0;
	
	// 修改条目数据
	virtual IItem<DATA,KEY>*	ModifyItem( KEY key, DATA* pData ) { return 0; }
	// 获得条目名称
	virtual KEY					GetItemName(){ return m_keyName; }
	// 获得条目类型
	virtual EmItemType			GetItemType(){ return m_emItemType; }
	// 获得父节点
	virtual IItem<DATA,KEY>*	GetParentItem(){ return m_pParentItem; }
	// 复制条目
	virtual IItem<DATA,KEY>*		Clone() = 0;
	// 条目名
	KEY		m_keyName;
	// 条目数据
	DATA					*m_ptItemData;	
	// 条目类型
	EmItemType	m_emItemType;
	// 父条目 用户修改条目
	IItem<DATA,KEY>*		m_pParentItem;
};


//----------------------------------------------------------
//类    名: CItem
//功    能：条目类
//主要接口: 同基类
//修改记录:
//日期		版本		修改人		修改记录
//2010/4/26	V1.0		muxingmao	创建
//----------------------------------------------------------
template<class DATA,typename KEY>
class CItem : public IItem<DATA,KEY> 
{
public:
	CItem()
	{
		m_emItemType = emItem;
		m_ptItemData = 0;
	}
	virtual bool	DeleteItem( KEY key, bool bDeleteData = true ) { return false; }
	virtual bool	DeleteAllItem( bool bDeleteData = true ) { return false; }
	virtual int		GetItemCount() { return 0; };	
		
	virtual bool	ModifyItemKey( KEY keyNew )
	{
		if ( m_pParentItem == 0)
		{
			return false;
		}
		
		IItem<DATA,KEY>* pItem = Clone();
		
		if ( m_pParentItem->AddItem( keyNew, pItem ) != 0 )
		{
			m_pParentItem->DeleteItem( m_keyName );
			
			return true;
		}
		
		return false;
	}
	
	virtual IItem<DATA,KEY>*	Clone()
	{
		IItem<DATA,KEY>* pItem = new CItem<DATA,KEY>();
		pItem->m_keyName = m_keyName;
		pItem->SetItemData( m_ptItemData );
		pItem->m_pParentItem = m_pParentItem;
		
		return pItem;
	}
};

//----------------------------------------------------------
//类    名: CItemGroup
//功    能：条目组类
//主要接口: 同基类
//修改记录: 
//日期		版本		修改人		修改记录
//2010/4/26	V1.0		muxingmao	创建
//----------------------------------------------------------
template<class DATA,typename KEY>
class CItemGroup : public IItem<DATA,KEY>
{
public:
	CItemGroup()
	{
		m_emItemType = emGroup;
		m_ptItemData = 0;
	}
	
	~CItemGroup()
	{
		DeleteAllItem();
	}
	
	virtual int			GetItemCount()
	{	
		return m_pList.size(); 
	}
	
	virtual IItem<DATA,KEY>* AddItem( KEY key, IItem<DATA,KEY>* pItem )
	{
		if ( GetItemByKey( key ) == 0)
		{		
			IItem<DATA,KEY>* pTemp = pItem->Clone();
			
			pTemp->m_pParentItem = this;
			
			pTemp->m_keyName = key;
			
			m_pList.insert( map<KEY,IItem<DATA,KEY>*>::value_type( key, pTemp ));
			
			return pTemp;
		}
		return 0;
	}

	virtual IItem<DATA,KEY>* AddItem( KEY key, DATA* pData, EmItemType emType )
	{
		if ( GetItemByKey( key ) == 0)
		{		
			IItem<DATA,KEY>* pTemp = 0;
			if ( emType == emItem )
			{
				pTemp = new CItem<DATA,KEY>;
			}
			else if ( emType == emGroup )
			{
				pTemp = new CItemGroup<DATA,KEY>;
			}
			if ( pTemp == 0 )
			{
				return pTemp;
			}
			
			pTemp->m_pParentItem = this;
			
			pTemp->m_keyName = key;

            pTemp->m_ptItemData = pData->Clone();
			
			m_pList.insert( map<KEY,IItem<DATA,KEY>*>::value_type( key, pTemp ));
			
			return pTemp;
		}
		return 0;
	}
	
	virtual IItem<DATA,KEY>*		GetItemByKey( KEY key )
	{
		map<KEY,IItem<DATA,KEY>*>::iterator itr = m_pList.find( key );
		
		IItem<DATA,KEY>* pItem = 0;
		if ( itr != m_pList.end() )
		{
			pItem = itr->second;
		}
		return pItem;
	}
	
	virtual IItem<DATA,KEY>*		GetItemByIndex( int nIndex )
	{
		IItem<DATA,KEY>* pItem = 0;
		if ( nIndex >= m_pList.size() )
		{
			return pItem;
		}
		
		map<KEY,IItem<DATA,KEY>*>::iterator itr = m_pList.begin();
		
		while ( nIndex > 0 )
		{
			itr++;
			nIndex--;
		}
		pItem = itr->second;
		
		return pItem;
	}

	virtual IItem<DATA,KEY>*		GetItemByData( DATA* pData )
	{
		IItem<DATA,KEY>* pItem = 0;
		if ( pData == 0 )
		{
			return pItem;
		}
		
		map<KEY,IItem<DATA,KEY>*>::iterator itr = m_pList.begin();
		
		while ( itr != m_pList.end() )
		{
			pItem = itr->second;
			if ( pItem != 0 && pItem->GetItemData() == pData )
			{
				return pItem;
			}
			itr++;
		}	
		return 0;
	}

	virtual bool		DeleteItem( KEY key, bool bDeleteData = true )
	{
		map<KEY,IItem<DATA,KEY>*>::iterator itr = m_pList.find( key );
		
		if ( m_pList.end() == itr )
		{
			return false;
		}
		
		if ( bDeleteData == true )
		{
			delete itr->second;
			
			itr->second = 0;
		}
		
		m_pList.erase( itr );
		
		return true;
	}
	
	virtual bool		DeleteAllItem( bool bDeleteData = true )
	{
		map<KEY,IItem<DATA,KEY>*>::iterator itr = m_pList.begin();
		
		while( itr != m_pList.end() )
		{
			itr->second->DeleteAllItem( bDeleteData );
			if ( bDeleteData == true )
			{
				delete itr->second;
				itr->second = 0;
			}			
			itr++;
		}
		
		m_pList.clear();
		
		return true;
	}
	/*	有序列化需求的时候添加
	virtual void		Serialize( CArchive& ar ) 
	{
	if (ar.IsStoring())
	{
	int nItem = m_pList.size();
	
	  ar << nItem;
	  m_keyName.Serialize( ar );
	  
		map<KEY,IItem<DATA,KEY>*>::iterator itr = m_pList.begin();		
		for ( ; itr != m_pList.end(); itr++ )
		{
		
		  KEY key = (*itr).first;
		  key.Serialize( ar );
		  IItem<DATA,KEY> *pItem = itr->second;	
		  
			ar << (WORD)pItem->m_emItemType;
			
			  pItem->Serialize(ar);
			  }
			  }
			  else
			  {
			  int nItem = 0;
			  ar >> nItem;
			  m_keyName.Serialize( ar );
			  
				for (int i = 0; i < nItem; i++ )
				{
				IItem<DATA,KEY> *pItem;
				
				  KEY key;
				  key.Serialize( ar );
				  
					WORD wType;
					ar >> wType;
					
					  EmItemType emType = (EmItemType)wType;
					  switch (emType)
					  {
					  case emItem:
					  {
					  pItem = new CItem<DATA,KEY>;
					  }
					  break;
					  case emGroup:
					  {
					  pItem = new CItemGroup<DATA,KEY>;
					  }
					  break;
					  default:
					  {
					  pItem = new CItem<DATA,KEY>;
					  }	
					  break;
					  }
					  pItem->Serialize(ar);
					  AddItem(key,pItem);
					  }
					  }
					  }
	*/
	virtual bool		ModifyItemKey( KEY keyNew )
	{		
		if ( m_pParentItem == 0)
		{
			m_keyName = keyNew;
			return false;
		}
		
		m_pParentItem->DeleteItem( m_keyName, false );
		m_keyName = keyNew;
		if ( m_pParentItem != 0 )
		{			
			CItemGroup* pParentItem = (CItemGroup*)m_pParentItem;
			pParentItem->m_pList.insert( map<KEY,IItem<DATA,KEY>*>::value_type( keyNew, this ));
		}
		
		return true;
	}

	virtual IItem<DATA,KEY>*	ModifyItem( KEY key, DATA* pData )
	{
		if ( pData == 0 )
		{
			return 0;
		}
		IItem<DATA,KEY>* pItem = GetItemByKey( key );
		if ( pItem == 0 )
		{
			return AddItem( key, pData, emGroup );
		}
		pItem->SetItemData( pData );
		return pItem;
	}
	
	virtual IItem<DATA,KEY>*		Clone()
	{
		IItem<DATA,KEY>* pGroup = new CItemGroup<DATA,KEY>();
		pGroup->m_keyName = m_keyName;
		pGroup->m_pParentItem = m_pParentItem;
		if ( m_ptItemData != 0 )
		{
			pGroup->SetItemData( m_ptItemData );
		}
		
		map<KEY,IItem<DATA,KEY>*>::iterator itr = m_pList.begin();
		
		while ( itr != m_pList.end() )
		{
			pGroup->AddItem( itr->first, itr->second );
			itr++;	
		}
		return pGroup;
	}
public:
	// 条目列表
	std::map<KEY,IItem<DATA,KEY>*> m_pList;
};

/*---------------------------------------------------------------------
* 类	名：INoncopyable
* 功    能：用于不可拷贝类的基类，比方说一些全局的资源
* 特殊说明：如果要使用，请用private继承
* 修改记录：
* 日期			版本		修改人		修改记录
* 2011/07/19	v1.0		牟兴茂		创建
----------------------------------------------------------------------*/
class INoncopyable
{
protected:
	INoncopyable() {}
	~INoncopyable() {}
private:  // emphasize the following members are private
	   INoncopyable( const INoncopyable& );
	   const INoncopyable& operator=( const INoncopyable& );
};

} // namespace AutoUIFactory end
#endif