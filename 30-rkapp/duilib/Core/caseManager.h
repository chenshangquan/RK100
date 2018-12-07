#pragma once

#include <map>
#include <vector>
#pragma warning(disable:4251)//
/*****************************************************************************
* ����: ��������ģ��  
* @remarks	 
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/4/24       1.0         �����      ����
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
typedef  std::vector< TAttrib >  VcAttrib;//�����б�
typedef  std::map<  CDuiString /*strCtlName*/,VcAttrib /*vcAttrib*/  > CtlsAttribMap; //�ؼ�����map

typedef   std::map< CDuiString /*strCtrlName*/  , CtlsAttribMap /*vcAttrib*/ >   CaseMAP;//����map
	  

class CPaintManagerUI;
class CMarkupNode;

class UILIB_API CCaseManager 
{
public: 
	 CCaseManager();
	 virtual ~CCaseManager();
	 //����rootNode ���һ������
	 bool AddCase( CMarkupNode* pNodeRoot,  CPaintManagerUI* pManager );

	/*****************************************************************************
	* ����: ���÷���
	* @param [in]  szCaseName Ҫ���÷�����
	* @param [in]  pManager ��Ӧ��panitManagerUI
	* @param [in]  pParent  ���ؼ������������ӿؼ��ķ���
	* @return      �ɹ�����true��ʧ�ܷ���false 
	* @remarks	 
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾         �޸���      �޸�����
	2013/4/24       1.0         �����      ����
	2015/1/26       1.1         Ф��Ȼ      ����parent����
    ******************************************************************************/
	 bool DoCase( const LPCTSTR szCaseName, CPaintManagerUI* pManager, CControlUI *pParent = NULL );


	 /*****************************************************************************
	* ����: ����Ĭ�Ϸ���
	* @param [in]  dlgOrXmlName Ҫ���÷�����dlg�����߶�Ӧ��xml ������
	* @return      �ɹ�����true��ʧ�ܷ��� 
	* @remarks ����Ĭ�Ϸ���һ���漰����xml�ļ�������Ĭ�Ϸ���ʱ��ֱ�Ӷ�ȡxml�ļ�	 
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/4/9       1.0         �����      ����
    ******************************************************************************/
	 bool DoDefCase( const LPCTSTR dlgOrXmlName );
	 

private:
	

	//���ݡ�������������ȡ��Ӧ�ķ����б�
	bool GetCaseInfo( const LPCTSTR szCaseName , CtlsAttribMap & attribLst ) ;

	//���һ������
	bool AddCase(const LPCTSTR szCaseName, const CtlsAttribMap &attribLst  );
	
private: 
	 CaseMAP m_caseMap; 
};
}
