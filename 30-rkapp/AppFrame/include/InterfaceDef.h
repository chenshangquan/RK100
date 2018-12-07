#pragma once
#include "singleton.h"
namespace AppFrame
{

/*
	映射表模板类
	KEY需要满足map键值要求
*/
template<class Key, class Object> class tmplContainer
{
protected:
	/*
	对象映射表
*/
	typedef map<Key,Object> ObjectMap;
	ObjectMap m_mapObjects;
public:
/** 找到对应的对象 
 *  @param[in] 
 *  @node 
 *  @return 是否成功
 */
	Object Find( Key key )
	{
		map<Key,Object>::iterator itr = m_mapObjects.find( key );
		if ( itr != m_mapObjects.end() )
		{
			return itr->second;
		}
		return NULL;
	}

/** 添加对象 
 *  @param[in] 
 *  @node 
 *  @return 是否成功
 */
	void Add( Key key, Object pObject )
	{
		Object pOb = Find( key );
		if ( pOb == 0 )
		{
			m_mapObjects[key] = pObject;
		}
	}
/** 重置Key对应的值
 *  @param[in] 
 *  @node 
 *  @return 是否成功
 */
	void Reset( Key key, Object pObject )
	{
		Object pOb = Find( key );
		if ( pOb != 0 )
		{
			m_mapObjects[key] = pObject;
		}
	}

/** 移除对象 
 *  @param[in] 
 *  @node 
 *  @return 是否成功
 */
	void Remove( Key key )
	{
		m_mapObjects.erase( key );
	}
/** 清除对象 
 *  @param[in] 
 *  @node 
 *  @return 是否成功
 */	
	void Clear()
	{
		m_mapObjects.clear();
	}

/** 获取容器大小 
*  @param[in] 
*  @node 
*  @return 容器
*/
	u32 Size()
	{
		return m_mapObjects.size();
	}

}; 

/*
	UI管理器，负责UI的切换和
*/
class IWindowManager : public CSingleton<IWindowManager>
{
public:
	virtual ~IWindowManager(){}
public:
	virtual void SetResourcePath(LPCTSTR lpstrFile) = 0;
	
	/** 显示窗口到屏幕中间
	 *  @param[in] lpstrName 窗口名
	 *  @return 是否成功
	 *  @remarks child窗口不能调用此接口 -xcr
	 */
	virtual bool ShowWindowCenter(LPCTSTR lpstrName) = 0;

	virtual bool ShowWindow(LPCTSTR lpstrName, bool bShow = true) = 0;
	virtual bool HideWindow(LPCTSTR lpstrName) = 0;
	virtual bool ShowModal(LPCTSTR lpstrName, LPCTSTR lpstrParentWindow = _T("")) = 0;
    virtual u8 ShowModalGetRe(LPCTSTR lpstrName, LPCTSTR lpstrParentWindow = _T("")) = 0;
	virtual bool CloseWindow(LPCTSTR lpstrName, UINT nRet = IDOK) = 0;
	virtual Window* GetWindow(LPCTSTR lpstrName) = 0;
	//窗口是否可见 dyy 2015-5-4
	virtual bool IsWindowVisible(LPCTSTR lpstrName) = 0;
    //窗口最小化
    virtual void ShowWindowMinsize(LPCTSTR lpstrName) = 0;
    virtual bool IsWindowMinsize(LPCTSTR lpstrName) = 0;
	virtual Control* GetControl(LPCTSTR lpstrWindow, LPCTSTR lpstrControl) = 0;
	virtual Window* NewWindow(LPCTSTR lpstrWindowName, LPCTSTR lpstrWindowMould, HWND hParentWnd, DWORD dwStyle, DWORD dwExStyle,
								LPVOID lpData = NULL, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT,
								int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT ) = 0;
	virtual Window* NewWindow(LPCTSTR lpstrWindowName, LPCTSTR lpstrWindowMould, LPCTSTR lpstrParentWindow, DWORD dwStyle, DWORD dwExStyle,
								LPVOID lpData = NULL, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT,
								int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT) = 0;
	
	/** 从左至右推出显示窗口
	 *  @param[in] lpstrName 窗口名 bShow 显示/隐藏
	 *  @return 是否成功
	 *  @remarks 隐藏时从右至左 -2014.12.10 xcr
	 */
	virtual bool ShowWindowFromLeftToRight(LPCTSTR lpstrName, bool bShow = true) = 0;
	virtual bool ShowWindowFromBottomToTop(LPCTSTR lpstrName, bool bShow = true) = 0;
    virtual bool ShowWindowFromTopToBottom(LPCTSTR lpstrName, bool bShow = true) = 0;
    virtual bool ShowMainWindowLeftToRight(LPCTSTR lpstrName, bool bShow = true) = 0;
	//归位 dyy 2015-9-16
	virtual bool ShowWindowInitLocation(LPCTSTR lpstrName) = 0;
	//窗口最顶端显示 dyy  2015-10-8
	virtual bool BringWindowTop(LPCTSTR lpstrName) = 0;
	/** 调窗口方案
	 *  @param[in] lpstrName 窗口名 lpstrCaseName 方案名
	 *  @return 是否成功
	 *  @remarks 
	 */
	virtual bool DoCase(LPCTSTR lpstrName, LPCTSTR lpstrCaseName) = 0;
};

static IWindowManager* WNDMNGR()
{
	return IWindowManager::GetSingletonPtr();
}

/*
	获取控件
*/
class IControlFactory : public CSingleton<IControlFactory>
{
public:
	virtual ~IControlFactory(){}
public:
	virtual Control* GetControl( LPCTSTR lpstrName ) = 0;
};

static IControlFactory* CONTROLFACTORY()
{
	return IControlFactory::GetSingletonPtr();
}



/*
	xml文档操作管理类
	可以获取xml文本内容
*/
class IDocManager : public CSingleton<IDocManager>
{
public:
	virtual ~IDocManager(){}
public:
/** xml文本读取 
 *  @param[in] strTag 标签、
 *  @node strPath不填写标明获取根节点 默认加载了system.xml文件过后，当前目录会变成当前资源目录
 *        
 *  @return 是否成功
 */
	virtual bool GetDoc(const tstring strFile, tstring strTag, tstring& strValue, const tstring strPath = _T("")) = 0;

	virtual DocNode GetNode(LPCTSTR lpszFile, LPCTSTR lpszPath) = 0;
};

static IDocManager* DOCMNGR()
{
	return IDocManager::GetSingletonPtr();
}

/*
	消息观察者
*/
template<class TParam> class IObserver
{
public:
	virtual ~IObserver(){}
	virtual bool Update( TParam& tMsgParma ) = 0;
	virtual bool UpdateAsyn(TMsgParam& tMsgParam ) = 0;
};
typedef IObserver<TMsgParam> IObserver_MsgPrama;


/**  IUserDataMngr 用户数据管理
  *  该类保存共享界面数据并提供接口
  *  该类还提供下层数据（Session）获取接口，参数与返回值为重定义的结构体
  */  
class IUserDataMngr : public IObserver_MsgPrama, public CSingleton<IUserDataMngr>
{
public:

	/**  根据消息更新
	 *  @param[in] 消息
	 *  @return 是否成功
	 */
	virtual		bool	Update( TMsgParam& tMsgParma )	= 0;


	/**  析构函数
	 */
	virtual	~IUserDataMngr(){};




};
/*
	消息处理接口
*/
class IMsgManager
{
public:
	virtual ~IMsgManager(){}
/** 广播消息 
 *  @param[in] tMsgParam 消息结构体 
 *  @node 
 *  @return 是否成功
 */
	virtual void SendMsg( TMsgParam& tMsgParam ) = 0;
	virtual void PostMsg(TMsgParam& tMsgParam) = 0;

/** 添加/删除观察者 
 *  @param[in] 
 *  @node 
 *  @return 是否成功
 */
	virtual void AddObserver( IObserver_MsgPrama* pOb ) = 0;
	virtual void RemoveObserver( IObserver_MsgPrama* pOb ) = 0;
};

/*
	添加一个Observer
*/
#define REG_MSG_OBSERVER( pObserver ) \
	IMsgManager::GetSingletonPtr()->AddObserver( pObserver );

typedef CNotifyUIImpl ILogic;
/*
	logic工厂，用于创建和管理logic
*/
class ILogicManager : public CSingleton<ILogicManager>, public tmplContainer<tstring, ILogic*>
{
public:
	virtual ~ILogicManager(){}
	virtual ILogic* Create(LPCTSTR lpszLogic) = 0;
};

typedef ILogic* (*PFnCreateLogic)();                            //创建Logic函数指针

#if _MSC_VER < 1200
// 注册宏
#define REG_LOGIC(obj) \
ILogicFactory::GetSingletonPtr()->Register( _T(#obj) , &Create_##obj );
#else
/* =============== For VS2010 ================ */
// 以下代码可以在VS2010中使用，无需DECLARE_LOGIC
// 原理：使用模板函数特化自动生成函数，取代DECLARE_LOGIC的过程
template<class T>
ILogic* CreateLogic()
{
	return new T;
}
#define REG_LOGIC( obj )\
ILogicFactory::GetSingletonPtr()->Register( _T(#obj), &CreateLogic<obj> )
#endif

/**  ILogicFactory 逻辑工厂
  *  @author  周航 
  *  通过界面逻辑类注册的函数来创建逻辑
  */  
class ILogicFactory : public CSingleton<ILogicFactory>
{
public:
	virtual ~ILogicFactory(){}

	/**  Create创建逻辑
	  *  @author     周航 
	  *  @param[in]  strLogic 逻辑名  
	  *  @return     逻辑指针   
	  */
	virtual ILogic* Create(LPCTSTR lpszLogic) = 0;

	/**  注册逻辑创建函数
	  *  @author     周航 
	  *  @param[in]  strLogic 逻辑名    
	  *  @param[in]  PFnCreateLogic 创建逻辑函数指针    
	  *  @return     无   
	  */
	virtual void Register(LPCTSTR lpszLogic, PFnCreateLogic pFunc) = 0;
};

static ILogicFactory* LOGFACTORY()
{
	return ILogicFactory::GetSingletonPtr();
}


enum LogLevel
{
	Errors,
	Warnings,
	Standard,
	Informative,
	Insane			
};


/*
	调试打印信息输出类
*/
class ILogger : public CSingleton<ILogger>
{
public:
	virtual bool LogEvent(LPCTSTR lpszEvent, LogLevel emLoglv = Standard) = 0;
	ILogger(){}
	virtual ~ILogger(){}
};

/*
	打印宏
*/
#define LOGEVENT( message ) \
	tstring strMsg = message; \
	tstring strCodeInfo; \
    TCHAR buff[128] = {0 }; \
	_sntprintf(buff, sizeof (buff), _T("\n filepath=%s line=%d \n"),__FILE__,__LINE__); \
	strMsg += buff; \
ILogger::GetSingletonPtr()->LogEvent(strMsg.c_str(), Insane); 

} // namespace AppFrame end 