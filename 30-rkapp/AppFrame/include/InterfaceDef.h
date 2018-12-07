#pragma once
#include "singleton.h"
namespace AppFrame
{

/*
	ӳ���ģ����
	KEY��Ҫ����map��ֵҪ��
*/
template<class Key, class Object> class tmplContainer
{
protected:
	/*
	����ӳ���
*/
	typedef map<Key,Object> ObjectMap;
	ObjectMap m_mapObjects;
public:
/** �ҵ���Ӧ�Ķ��� 
 *  @param[in] 
 *  @node 
 *  @return �Ƿ�ɹ�
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

/** ��Ӷ��� 
 *  @param[in] 
 *  @node 
 *  @return �Ƿ�ɹ�
 */
	void Add( Key key, Object pObject )
	{
		Object pOb = Find( key );
		if ( pOb == 0 )
		{
			m_mapObjects[key] = pObject;
		}
	}
/** ����Key��Ӧ��ֵ
 *  @param[in] 
 *  @node 
 *  @return �Ƿ�ɹ�
 */
	void Reset( Key key, Object pObject )
	{
		Object pOb = Find( key );
		if ( pOb != 0 )
		{
			m_mapObjects[key] = pObject;
		}
	}

/** �Ƴ����� 
 *  @param[in] 
 *  @node 
 *  @return �Ƿ�ɹ�
 */
	void Remove( Key key )
	{
		m_mapObjects.erase( key );
	}
/** ������� 
 *  @param[in] 
 *  @node 
 *  @return �Ƿ�ɹ�
 */	
	void Clear()
	{
		m_mapObjects.clear();
	}

/** ��ȡ������С 
*  @param[in] 
*  @node 
*  @return ����
*/
	u32 Size()
	{
		return m_mapObjects.size();
	}

}; 

/*
	UI������������UI���л���
*/
class IWindowManager : public CSingleton<IWindowManager>
{
public:
	virtual ~IWindowManager(){}
public:
	virtual void SetResourcePath(LPCTSTR lpstrFile) = 0;
	
	/** ��ʾ���ڵ���Ļ�м�
	 *  @param[in] lpstrName ������
	 *  @return �Ƿ�ɹ�
	 *  @remarks child���ڲ��ܵ��ô˽ӿ� -xcr
	 */
	virtual bool ShowWindowCenter(LPCTSTR lpstrName) = 0;

	virtual bool ShowWindow(LPCTSTR lpstrName, bool bShow = true) = 0;
	virtual bool HideWindow(LPCTSTR lpstrName) = 0;
	virtual bool ShowModal(LPCTSTR lpstrName, LPCTSTR lpstrParentWindow = _T("")) = 0;
    virtual u8 ShowModalGetRe(LPCTSTR lpstrName, LPCTSTR lpstrParentWindow = _T("")) = 0;
	virtual bool CloseWindow(LPCTSTR lpstrName, UINT nRet = IDOK) = 0;
	virtual Window* GetWindow(LPCTSTR lpstrName) = 0;
	//�����Ƿ�ɼ� dyy 2015-5-4
	virtual bool IsWindowVisible(LPCTSTR lpstrName) = 0;
    //������С��
    virtual void ShowWindowMinsize(LPCTSTR lpstrName) = 0;
    virtual bool IsWindowMinsize(LPCTSTR lpstrName) = 0;
	virtual Control* GetControl(LPCTSTR lpstrWindow, LPCTSTR lpstrControl) = 0;
	virtual Window* NewWindow(LPCTSTR lpstrWindowName, LPCTSTR lpstrWindowMould, HWND hParentWnd, DWORD dwStyle, DWORD dwExStyle,
								LPVOID lpData = NULL, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT,
								int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT ) = 0;
	virtual Window* NewWindow(LPCTSTR lpstrWindowName, LPCTSTR lpstrWindowMould, LPCTSTR lpstrParentWindow, DWORD dwStyle, DWORD dwExStyle,
								LPVOID lpData = NULL, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT,
								int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT) = 0;
	
	/** ���������Ƴ���ʾ����
	 *  @param[in] lpstrName ������ bShow ��ʾ/����
	 *  @return �Ƿ�ɹ�
	 *  @remarks ����ʱ�������� -2014.12.10 xcr
	 */
	virtual bool ShowWindowFromLeftToRight(LPCTSTR lpstrName, bool bShow = true) = 0;
	virtual bool ShowWindowFromBottomToTop(LPCTSTR lpstrName, bool bShow = true) = 0;
    virtual bool ShowWindowFromTopToBottom(LPCTSTR lpstrName, bool bShow = true) = 0;
    virtual bool ShowMainWindowLeftToRight(LPCTSTR lpstrName, bool bShow = true) = 0;
	//��λ dyy 2015-9-16
	virtual bool ShowWindowInitLocation(LPCTSTR lpstrName) = 0;
	//���������ʾ dyy  2015-10-8
	virtual bool BringWindowTop(LPCTSTR lpstrName) = 0;
	/** �����ڷ���
	 *  @param[in] lpstrName ������ lpstrCaseName ������
	 *  @return �Ƿ�ɹ�
	 *  @remarks 
	 */
	virtual bool DoCase(LPCTSTR lpstrName, LPCTSTR lpstrCaseName) = 0;
};

static IWindowManager* WNDMNGR()
{
	return IWindowManager::GetSingletonPtr();
}

/*
	��ȡ�ؼ�
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
	xml�ĵ�����������
	���Ի�ȡxml�ı�����
*/
class IDocManager : public CSingleton<IDocManager>
{
public:
	virtual ~IDocManager(){}
public:
/** xml�ı���ȡ 
 *  @param[in] strTag ��ǩ��
 *  @node strPath����д������ȡ���ڵ� Ĭ�ϼ�����system.xml�ļ����󣬵�ǰĿ¼���ɵ�ǰ��ԴĿ¼
 *        
 *  @return �Ƿ�ɹ�
 */
	virtual bool GetDoc(const tstring strFile, tstring strTag, tstring& strValue, const tstring strPath = _T("")) = 0;

	virtual DocNode GetNode(LPCTSTR lpszFile, LPCTSTR lpszPath) = 0;
};

static IDocManager* DOCMNGR()
{
	return IDocManager::GetSingletonPtr();
}

/*
	��Ϣ�۲���
*/
template<class TParam> class IObserver
{
public:
	virtual ~IObserver(){}
	virtual bool Update( TParam& tMsgParma ) = 0;
	virtual bool UpdateAsyn(TMsgParam& tMsgParam ) = 0;
};
typedef IObserver<TMsgParam> IObserver_MsgPrama;


/**  IUserDataMngr �û����ݹ���
  *  ���ౣ�湲��������ݲ��ṩ�ӿ�
  *  ���໹�ṩ�²����ݣ�Session����ȡ�ӿڣ������뷵��ֵΪ�ض���Ľṹ��
  */  
class IUserDataMngr : public IObserver_MsgPrama, public CSingleton<IUserDataMngr>
{
public:

	/**  ������Ϣ����
	 *  @param[in] ��Ϣ
	 *  @return �Ƿ�ɹ�
	 */
	virtual		bool	Update( TMsgParam& tMsgParma )	= 0;


	/**  ��������
	 */
	virtual	~IUserDataMngr(){};




};
/*
	��Ϣ����ӿ�
*/
class IMsgManager
{
public:
	virtual ~IMsgManager(){}
/** �㲥��Ϣ 
 *  @param[in] tMsgParam ��Ϣ�ṹ�� 
 *  @node 
 *  @return �Ƿ�ɹ�
 */
	virtual void SendMsg( TMsgParam& tMsgParam ) = 0;
	virtual void PostMsg(TMsgParam& tMsgParam) = 0;

/** ���/ɾ���۲��� 
 *  @param[in] 
 *  @node 
 *  @return �Ƿ�ɹ�
 */
	virtual void AddObserver( IObserver_MsgPrama* pOb ) = 0;
	virtual void RemoveObserver( IObserver_MsgPrama* pOb ) = 0;
};

/*
	���һ��Observer
*/
#define REG_MSG_OBSERVER( pObserver ) \
	IMsgManager::GetSingletonPtr()->AddObserver( pObserver );

typedef CNotifyUIImpl ILogic;
/*
	logic���������ڴ����͹���logic
*/
class ILogicManager : public CSingleton<ILogicManager>, public tmplContainer<tstring, ILogic*>
{
public:
	virtual ~ILogicManager(){}
	virtual ILogic* Create(LPCTSTR lpszLogic) = 0;
};

typedef ILogic* (*PFnCreateLogic)();                            //����Logic����ָ��

#if _MSC_VER < 1200
// ע���
#define REG_LOGIC(obj) \
ILogicFactory::GetSingletonPtr()->Register( _T(#obj) , &Create_##obj );
#else
/* =============== For VS2010 ================ */
// ���´��������VS2010��ʹ�ã�����DECLARE_LOGIC
// ԭ��ʹ��ģ�庯���ػ��Զ����ɺ�����ȡ��DECLARE_LOGIC�Ĺ���
template<class T>
ILogic* CreateLogic()
{
	return new T;
}
#define REG_LOGIC( obj )\
ILogicFactory::GetSingletonPtr()->Register( _T(#obj), &CreateLogic<obj> )
#endif

/**  ILogicFactory �߼�����
  *  @author  �ܺ� 
  *  ͨ�������߼���ע��ĺ����������߼�
  */  
class ILogicFactory : public CSingleton<ILogicFactory>
{
public:
	virtual ~ILogicFactory(){}

	/**  Create�����߼�
	  *  @author     �ܺ� 
	  *  @param[in]  strLogic �߼���  
	  *  @return     �߼�ָ��   
	  */
	virtual ILogic* Create(LPCTSTR lpszLogic) = 0;

	/**  ע���߼���������
	  *  @author     �ܺ� 
	  *  @param[in]  strLogic �߼���    
	  *  @param[in]  PFnCreateLogic �����߼�����ָ��    
	  *  @return     ��   
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
	���Դ�ӡ��Ϣ�����
*/
class ILogger : public CSingleton<ILogger>
{
public:
	virtual bool LogEvent(LPCTSTR lpszEvent, LogLevel emLoglv = Standard) = 0;
	ILogger(){}
	virtual ~ILogger(){}
};

/*
	��ӡ��
*/
#define LOGEVENT( message ) \
	tstring strMsg = message; \
	tstring strCodeInfo; \
    TCHAR buff[128] = {0 }; \
	_sntprintf(buff, sizeof (buff), _T("\n filepath=%s line=%d \n"),__FILE__,__LINE__); \
	strMsg += buff; \
ILogger::GetSingletonPtr()->LogEvent(strMsg.c_str(), Insane); 

} // namespace AppFrame end 