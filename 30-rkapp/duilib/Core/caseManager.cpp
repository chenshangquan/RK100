#include "stdafx.h"
#include "caseManager.h"

void PrintErr( TCHAR *chFormat, ...)
{
	if( NULL == chFormat )
	{
		return;
	} 
	va_list arg_ptr; 
	va_start( arg_ptr,chFormat );
	TCHAR buff[256]= _T("0");
	_vsntprintf( buff, sizeof(buff)/sizeof(TCHAR),chFormat, arg_ptr );
	va_end( arg_ptr );

	OutputDebugString( buff ); 

}


namespace DuiLib {


CCaseManager::CCaseManager(void)
{
}


CCaseManager::~CCaseManager(void)
{
}




bool CCaseManager::GetCaseInfo( const LPCTSTR szCaseName , CtlsAttribMap & attribLst )
{
	bool Re = false;
	CaseMAP::iterator it = m_caseMap.find( szCaseName );
	if( it!= m_caseMap.end() )
	{
		attribLst = it->second;
		Re = true;
	}
	return Re;
}

bool CCaseManager::AddCase( const LPCTSTR szCaseName, const CtlsAttribMap &attribLst )
{
	bool Re = false;
	CaseMAP::iterator it = m_caseMap.find( szCaseName );
	if( it== m_caseMap.end() )
	{
		m_caseMap.insert( CaseMAP::value_type( szCaseName, attribLst ));
		Re = true;
	}
	return Re;
}

bool CCaseManager::AddCase(   CMarkupNode* pNodeRoot, CPaintManagerUI* pManager )
{
	 
	if( NULL == pNodeRoot || NULL == pManager )
	{
		return false;
	}
	 
	CDuiString strCaseName = pNodeRoot->GetAttributeValue( _T("name") );
	 
	CtlsAttribMap ctrlMap;
	for(  CMarkupNode node = pNodeRoot->GetChild(); node.IsValid(); node = node.GetSibling() ) 
	{//�ؼ���
		CDuiString pstrCtrlName = node.GetName();//
		VcAttrib vcAttrib;
		int nAttributes = node.GetAttributeCount();
		for( int i = 0; i < nAttributes; i++ ) 
		{//�ؼ���Ӧ�����Լ� 
			TAttrib tProp;
			tProp.strPropName  =  node.GetAttributeName(i);
			tProp.strPropValue = node.GetAttributeValue(i); 
			vcAttrib.push_back( tProp);
		}
		ctrlMap.insert( CtlsAttribMap::value_type(pstrCtrlName,vcAttrib) );

	}

	m_caseMap.insert(CaseMAP::value_type(strCaseName,ctrlMap) );
	return true;

}

bool CCaseManager::DoCase( const LPCTSTR szCaseName, CPaintManagerUI* pManager, CControlUI *pParent )
{
	bool Re = false;
	CaseMAP::iterator itCaseMap = m_caseMap.find( szCaseName );
	if( itCaseMap!= m_caseMap.end() )
	{//���ݷ������Ҽ�����
		Re = true;

		//�����ж�Ӧ�Ŀؼ���
		CtlsAttribMap ctrldAttribMap = itCaseMap->second;
		CtlsAttribMap::iterator itCtlsAttrib  =  ctrldAttribMap.begin();
		while( itCtlsAttrib != ctrldAttribMap.end() ) //�ؼ���
		{   
			CControlUI* pCtrl = NULL;
			if (pParent == NULL)
			{
				pCtrl = pManager->FindControl((LPCTSTR)itCtlsAttrib->first);
			}
			else
			{
				pCtrl = pManager->FindSubControlByName(pParent, (LPCTSTR)itCtlsAttrib->first);
			}
			if( NULL == pCtrl )
			{
				itCtlsAttrib ++;
				//PrintErr(_T("\n[CCaseMap::DoCase] δ�ҵ��ؼ�[%s]\n"), (LPCTSTR)itCtlsAttrib->first );
				continue;
			}

			//�ؼ��ж�Ӧ�����Լ�
			VcAttrib::iterator itVcAttrib = itCtlsAttrib->second.begin();
			while( pCtrl && itVcAttrib != itCtlsAttrib->second.end() )//ĳ���ؼ������Լ�
			{  
				pCtrl->SetAttribute( itVcAttrib->strPropName, itVcAttrib->strPropValue); 
				itVcAttrib++;
			} 	

			itCtlsAttrib ++;
		}

	}

	return Re;
}

bool CCaseManager::DoDefCase( const LPCTSTR dlgOrXmlName )
{
	bool Re = false; 

	return Re;
}


}