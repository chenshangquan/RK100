#include "stdafx.h"
#include "rkcinterface.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

UINT ThreadSearchRkc(LPVOID lpParam)
{
    u16 re = CRkcComInterface->SearchDoing();
    return re;
}

u16 CRkcInterface::BeginSearch(EmSearchType emtype, u32 dwStartip , u32 dwEndip)
{
    if( NULL == m_pSearchCtrlIf )
    {
        return -1;
    }
    m_pSearchCtrlIf->SetSearchType(emtype , dwStartip , dwEndip);
    //开始搜索
    AfxBeginThread( ThreadSearchRkc , NULL );

    return NO_ERROR;
}

u16 CRkcInterface::SearchDoing()
{
    m_pSearchCtrlIf->StartSearch();
//     Sleep(MAX_SEARCH_TIME);
//     m_pSearchCtrlIf->EndSearch();
    return NO_ERROR;
}

u16 CRkcInterface::ReSet(bool bEsitSearch)
{
    if( NULL == m_pSearchCtrlIf )
    {
        return -1;
    }
    if (bEsitSearch)
    {
        //m_pSearchCtrlIf->EndSearch();//停止搜索
    }
    m_pSearchCtrlIf->ReSet();//数据清空
    return NO_ERROR;
}

u16 CRkcInterface::GetDevList(vector<TDevItem>& vecTDevItem)const
{
    if( NULL == m_pSearchCtrlIf )
    {
        return -1;
    }

    vecTDevItem = m_pSearchCtrlIf->GetDevList();

    return NO_ERROR;
}