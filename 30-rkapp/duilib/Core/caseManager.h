#pragma once

#include <map>
#include <vector>
#pragma warning(disable:4251)//
/*****************************************************************************
* 功能: 方案管理模块  
* @remarks	 
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/4/24       1.0         俞锦锦      创建
******************************************************************************/
namespace DuiLib { 

typedef struct  tagAttrib
{
	CDuiString strPropName;
	CDuiString strPropValue;
	tagAttrib()
	{
		strPropName.Empty();
		strPropValue.Empty();

	}
} TAttrib, *PTAttrib ;
typedef  std::vector< TAttrib >  VcAttrib;//属性列表
typedef  std::map<  CDuiString /*strCtlName*/,VcAttrib /*vcAttrib*/  > CtlsAttribMap; //控件属性map

typedef   std::map< CDuiString /*strCtrlName*/  , CtlsAttribMap /*vcAttrib*/ >   CaseMAP;//方案map
	  

class CPaintManagerUI;
class CMarkupNode;

class UILIB_API CCaseManager 
{
public: 
	 CCaseManager();
	 virtual ~CCaseManager();
	 //根据rootNode 添加一个方案
	 bool AddCase( CMarkupNode* pNodeRoot,  CPaintManagerUI* pManager );

	/*****************************************************************************
	* 功能: 调用方案
	* @param [in]  szCaseName 要调用方案名
	* @param [in]  pManager 对应的panitManagerUI
	* @param [in]  pParent  父控件，调用其中子控件的方案
	* @return      成功返回true，失败返回false 
	* @remarks	 
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本         修改人      修改内容
	2013/4/24       1.0         俞锦锦      创建
	2015/1/26       1.1         肖楚然      增加parent参数
    ******************************************************************************/
	 bool DoCase( const LPCTSTR szCaseName, CPaintManagerUI* pManager, CControlUI *pParent = NULL );


	 /*****************************************************************************
	* 功能: 调用默认方案
	* @param [in]  dlgOrXmlName 要调用方案的dlg名或者对应的xml 的名字
	* @return      成功返回true，失败返回 
	* @remarks 由于默认方案一般涉及整个xml文件，启用默认方案时，直接读取xml文件	 
	-----------------------------------------------------------------------------
	修改记录:
	日  期         版本        修改人      修改内容
	2013/4/9       1.0         俞锦锦      创建
    ******************************************************************************/
	 bool DoDefCase( const LPCTSTR dlgOrXmlName );
	 

private:
	

	//根据“方案名”来获取对应的方案列表
	bool GetCaseInfo( const LPCTSTR szCaseName , CtlsAttribMap & attribLst ) ;

	//添加一个方案
	bool AddCase(const LPCTSTR szCaseName, const CtlsAttribMap &attribLst  );
	
private: 
	 CaseMAP m_caseMap; 
};
}
