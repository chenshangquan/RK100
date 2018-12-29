#include "stdafx.h"
#include "searchequipmentlogic.h"
#include "toolframelogic.h"
#include "setmenulogic.h"
#include "modifypasswordlogic.h"
#include "messageboxlogic.h"
#include "tipboxlogic.h"
#include <dbt.h>

template<> CSearchEquipmentLogic* Singleton<CSearchEquipmentLogic>::ms_pSingleton  = NULL;

static UINT     g_nTimeOutTimerID;              //timer ��id�����ڼ������Ӳ������Զ��˳�
#define         TIME_TIMEROUT     300000        //��ʱ��ʱ����

static UINT     g_nGrabTimerID;              //timer ��id�����ڼ������Ӳ������Զ��˳�
#define         TIME_GRAB     150        //��ʱ��ʱ����

VOID  CALLBACK  CTimerOutFun(  HWND   hwnd,   UINT   uMsg, UINT_PTR  idEvent, DWORD   dwTime  )
{
    if ( idEvent == g_nTimeOutTimerID )
    {
        KillTimer( NULL, g_nTimeOutTimerID );
        g_nTimeOutTimerID = 0;

        CRkcComInterface->CloseSocket();
        WINDOW_MGR_PTR->ShowWindow(g_stcStrToolFrameDlg.c_str(),false);
        CSearchEquipmentLogic::GetSingletonPtr()->GetPaintManagerUI()->DoCase(_T("caseIsnotLogin"));
    }
    else if ( idEvent == g_nGrabTimerID )
    {
        KillTimer( NULL, g_nGrabTimerID );
        g_nGrabTimerID = 0;

        ShowMessageBox(_T("�˺����������ط���¼"),1);
    }
}

APP_BEGIN_MSG_MAP(CSearchEquipmentLogic, CNotifyUIImpl)
	MSG_CREATEWINDOW(_T("SearchEquipment"), OnCreate)
	MSG_INIWINDOW(_T("SearchEquipment"), OnInit)
    MSG_WINDOWMOVE(_T("SearchEquipment"), OnMove)
	MSG_WINDOWDESTORY(_T("SearchEquipment"), OnDestory)

    MSG_CLICK(_T("setbtn"), OnSetBtnClicked)
    MSG_CLICK(_T("minbtn"), OnMinBtnClicked)
    MSG_CLICK(_T("closebtn"), OnCloseBtnClicked)
    MSG_CLICK(_T("SearchBtn"), OnSearchBtnClicked)
    MSG_CLICK(_T("ResetBtn"), OnResetBtnClicked)
    MSG_CLICK(_T("OperateBtn"), OnItemOperateBtnClicked)
    MSG_CLICK(_T("exitbtn"), OnExitBtnClicked)

    MSG_SELECTCHANGE(_T("OptSearchTypeALL"), OnOptSearchTypeAllSel)
    MSG_SELECTCHANGE(_T("OptSearchTypeIP"), OnOptSearchTypeIPSel)

    USER_MSG(UI_RKC_SEARCH_FINISH , OnRkcSearchFinish)
    USER_MSG(UI_RKC_RKDEV_REFLESH , OnRkcDevReflesh)
    USER_MSG(UI_RKC_CONNECTED , OnRkcConnected)
    USER_MSG(UI_RKC_DISCONNECTED , OnRkcDisconnected)
    USER_MSG(UI_RKC_REBOOT , OnRkcReBoot)
APP_END_MSG_MAP()

const String CSearchEquipmentLogic::strEquipmentList = _T("EquipmentList");
const String CSearchEquipmentLogic::strEquipmentListItem = _T("EquipmentListItem");

CSearchEquipmentLogic::CSearchEquipmentLogic()
{
    g_nTimeOutTimerID = 0;
    g_nGrabTimerID = 0;
}

CSearchEquipmentLogic::~CSearchEquipmentLogic()
{
}

bool CSearchEquipmentLogic::OnCreate( TNotifyUI& msg )
{
	HWND hWnd = m_pm->GetPaintWindow();
	LONG styleValue = ::GetWindowLong(hWnd, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	styleValue &= ~WS_SIZEBOX;//���ڴ�С������ק
	::SetWindowLong(hWnd, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	return false;
}

bool CSearchEquipmentLogic::OnDestory( TNotifyUI& msg )
{
	TerminateProcess(GetCurrentProcess(), 0);
    // ������������
    WINDOW_MGR_PTR->CloseWindow(g_stcStrBackGroundDlg.c_str());
	return true;
}

bool CSearchEquipmentLogic::OnInit( TNotifyUI& msg )
{
	REG_RCKTOOL_MSG_WND_OB(m_pm->GetPaintWindow());
    m_pm->DoCase(_T("caseIsSearchAll"));

    // �������ڴ���
    WINDOW_MGR_PTR->ShowWindow(g_stcStrBackGroundDlg.c_str(), false);
    RECT rcParent;
    HWND hparent = m_pm->GetPaintWindow();
    GetWindowRect(hparent,&rcParent);
    HWND hAppWind = FindWindow(NULL, g_stcStrBackGroundDlg.c_str());
    SetWindowPos( hAppWind, NULL, rcParent.left, rcParent.top, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE);

    m_nLeft = rcParent.left;
    m_nTop  = rcParent.top;

    return true;
}

bool CSearchEquipmentLogic::OnMove( TNotifyUI& msg )
{
    // �������ڴ���
    if (WINDOW_MGR_PTR->IsWindowVisible(g_stcStrBackGroundDlg.c_str()))
    {
        RECT rcParent;
        HWND hparent = m_pm->GetPaintWindow();
        GetWindowRect(hparent,&rcParent);
        HWND hAppWind = FindWindow(NULL, g_stcStrBackGroundDlg.c_str());
        SetWindowPos( hAppWind, NULL, rcParent.left, rcParent.top, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE);

        m_nLeft = rcParent.left;
        m_nTop  = rcParent.top;
    }
    return true;
}

bool CSearchEquipmentLogic::OnMsgNotify(TNotifyUI& msg)
{
    SetTimerOutTimer(true);
    return true;
}

bool CSearchEquipmentLogic::OnMinBtnClicked(TNotifyUI& msg)
{
    WINDOW_MGR_PTR->ShowWindowMinsize(g_stcStrMainFrameDlg.c_str());
    return false;
}

bool CSearchEquipmentLogic::OnCloseBtnClicked(TNotifyUI& msg)
{
    CRkcComInterface->KillTftpProcess();
    TerminateProcess(GetCurrentProcess(), 0);  
    return false;
}

bool CSearchEquipmentLogic::OnSearchBtnClicked(TNotifyUI& msg)
{
    //��ť�û�
    IRkcToolCommonOp::EnableControl(false, m_pm, _T("SearchBtn"));
    //��������
    CRkcComInterface->ReSet(false);
    CListUI* pEquipmentList = (CListUI*)IRkcToolCommonOp::FindControl( m_pm, strEquipmentList.c_str() );
    if (pEquipmentList)
    {
        pEquipmentList->RemoveAll();
    }

    COptionUI* pTypeAll = (COptionUI*)IRkcToolCommonOp::FindControl( m_pm, _T("OptSearchTypeALL") );
    COptionUI* pTypeIP = (COptionUI*)IRkcToolCommonOp::FindControl( m_pm, _T("OptSearchTypeIP") );

    if (pTypeAll && pTypeIP)
    {
        EmSearchType emtype = emTypeAll;
        u32 dwStartIP = 0;
        u32 dwEndIP = 0;
        if (pTypeAll->IsSelected())
        {
            CRkcComInterface->BeginSearch(emTypeAll);
        }
        else if (pTypeIP->IsSelected())
        {
            CEditUI* pStartIP = (CEditUI*)IRkcToolCommonOp::FindControl( m_pm, _T("EdtStartIP") );
            CEditUI* pEndIP = (CEditUI*)IRkcToolCommonOp::FindControl( m_pm, _T("EdtEndIP") );
            if (pStartIP && pEndIP)
            {
                CString strstartIp = pStartIP->GetText();
                if(!UIDATAMGR->IsValidIp(CT2A(strstartIp)))
                {
                    ShowMessageBox(_T("������ʼIP��ַ�Ƿ�"));
                    IRkcToolCommonOp::EnableControl(true, m_pm, _T("SearchBtn"));
                    return false;
                }
                CString strendIp = pEndIP->GetText();
                if(!UIDATAMGR->IsValidIp(CT2A(strendIp)))
                {
                    ShowMessageBox(_T("������ֹIP��ַ�Ƿ�"));
                    IRkcToolCommonOp::EnableControl(true, m_pm, _T("SearchBtn"));
                    return false;
                }
                std::string strStartIP = CT2A(strstartIp);
                std::string strEndIP = CT2A(strendIp);
                vector<int> vstrStartIP;
                UIDATAMGR->split(strStartIP, vstrStartIP, '.');
                vector<int> vstrEndIP;
                UIDATAMGR->split(strEndIP, vstrEndIP, '.');
                if ( !((vstrStartIP.size() > 3 && vstrEndIP.size() > 3) &&
                       (vstrStartIP.at(0) == vstrEndIP.at(0)) &&
                       (vstrStartIP.at(1) == vstrEndIP.at(1)) &&
                       (vstrStartIP.at(2) == vstrEndIP.at(2)) ) )
                {
                    ShowMessageBox(_T("ֻ����ͬ����������"));
                    IRkcToolCommonOp::EnableControl(true, m_pm, _T("SearchBtn"));
                    return false;
                }

                if (!strstartIp.IsEmpty())
                {
                    dwStartIP = htonl(inet_addr(CT2A(strstartIp)));
                }
                if (!strendIp.IsEmpty())
                {
                    dwEndIP = htonl(inet_addr(CT2A(strendIp)));
                }
                if (dwEndIP < dwStartIP)//��ֹIP С�� ��ʵIP
                {
                    ShowMessageBox(_T("��ǰ��дIP������Ч"));
                    IRkcToolCommonOp::EnableControl(true, m_pm, _T("SearchBtn"));
                    return false;
                }
                u16 wRe = CRkcComInterface->BeginSearch(emTypeIP , dwStartIP , dwEndIP);
                if (wRe != NO_ERROR)
                {
                    IRkcToolCommonOp::EnableControl(true, m_pm, _T("SearchBtn"));
                    return false;
                }
            }
        }
    }
    return true;
}

bool CSearchEquipmentLogic::OnResetBtnClicked(TNotifyUI& msg)
{
    CRkcComInterface->ReSet();

    COptionUI* pTypeAll = (COptionUI*)IRkcToolCommonOp::FindControl( m_pm, _T("OptSearchTypeALL") );
    COptionUI* pTypeIP = (COptionUI*)IRkcToolCommonOp::FindControl( m_pm, _T("OptSearchTypeIP") );
    if (pTypeAll)
    {
        pTypeAll->Selected(true);
    }
    IRkcToolCommonOp::SetControlText( _T("") , m_pm, _T("EdtStartIP") );
    IRkcToolCommonOp::SetControlText( _T("") , m_pm, _T("EdtEndIP") );

    CListUI* pEquipmentList = (CListUI*)IRkcToolCommonOp::FindControl( m_pm, strEquipmentList.c_str() );
    if (pEquipmentList)
    {
        pEquipmentList->RemoveAll();
    }

    return true;
}

bool CSearchEquipmentLogic::OnItemOperateBtnClicked(TNotifyUI& msg)
{
    if (CRkcComInterface->IsLoginState())
    {
        return false;
    }
    CListUI* pEquipmentList = (CListUI*)IRkcToolCommonOp::FindControl( m_pm, strEquipmentList.c_str() );
    if (pEquipmentList)
    {
        int nIndex = pEquipmentList->GetItemIndex(msg.pSender->GetParent());
        std::vector<TDevItem> vecDevItem;
        CRkcComInterface->GetDevList(vecDevItem);
        if (nIndex >= vecDevItem.size())
        {
            return false;
        }
        SetDevItem(vecDevItem.at(nIndex));
        OnShowBGWindow();
        WINDOW_MGR_PTR->ShowWindowCenter(g_stcStrLoginDlg.c_str());
    }
    return true;
}

bool CSearchEquipmentLogic::OnExitBtnClicked(TNotifyUI& msg)
{
    u8 byCgeckChange = CToolFrameLogic::GetSingletonPtr()->ExitCheckChange();
    if (byCgeckChange == 1)
    {
        return false;
    }
    else if (byCgeckChange == 2)
    {
        CRkcComInterface->CloseSocket();
        WINDOW_MGR_PTR->ShowWindow(g_stcStrToolFrameDlg.c_str(),false);
        m_pm->DoCase(_T("caseIsnotLogin"));
        return true;
    }
    else
    {
        int nBoxRe = ShowMessageBox(_T("�����˳���¼"),2);
        if (nBoxRe == IDOK)
        {
            CRkcComInterface->CloseSocket();
            WINDOW_MGR_PTR->ShowWindow(g_stcStrToolFrameDlg.c_str(),false);
            m_pm->DoCase(_T("caseIsnotLogin"));
        }
        return true;
    }
}

bool CSearchEquipmentLogic::OnOptSearchTypeIPSel(TNotifyUI& msg)
{
    COptionUI* pMsgSpend = (COptionUI*)msg.pSender;
    if (pMsgSpend->IsSelected())
    {
        m_pm->DoCase(_T("caseIsSearchIP"));
    }
    return true;
}

bool CSearchEquipmentLogic::OnOptSearchTypeAllSel(TNotifyUI& msg)
{
    COptionUI* pMsgSpend = (COptionUI*)msg.pSender;
    if (pMsgSpend->IsSelected())
    {
        m_pm->DoCase(_T("caseIsSearchAll"));
    }
    return true;
}

bool CSearchEquipmentLogic::OnRkcDevReflesh(WPARAM wparam, LPARAM lparam, bool& bHandle)
{
    CListUI* pEquipmentList = (CListUI*)IRkcToolCommonOp::FindControl( m_pm, strEquipmentList.c_str() );
    if (pEquipmentList)
    {
        pEquipmentList->RemoveAll();
        std::vector<TDevItem> vecDevItem;
        CRkcComInterface->GetDevList(vecDevItem);
        for (unsigned int i = 0 ; i < vecDevItem.size() ; i++)
        {
            CListContainerElementUI *pListContainer = (CListContainerElementUI*)CONTROLFACTORY()->GetControl( strEquipmentListItem.c_str() );
            if (pListContainer)
            {
                CString str = _T("");
                str.Format(_T("%d"), pEquipmentList->GetCount() + 1);
                IRkcToolCommonOp::SetControlText( str , m_pm ,_T("IndexLab"), pListContainer);
                //����
                IRkcToolCommonOp::SetControlText( CA2T(vecDevItem.at(i).tDevID.achDevType) , m_pm ,_T("ModelLab"), pListContainer);
                //IP
                u32 dwIP = htonl(vecDevItem.at(i).tDevInfo.tAddr.dwIpaddr);
                IRkcToolCommonOp::SetControlText( CA2T(inet_ntoa(*(in_addr*)&dwIP)) , m_pm ,_T("IPLab"), pListContainer);
                //SN
                IRkcToolCommonOp::SetControlText( CA2T(vecDevItem.at(i).tDevID.achDevSerial) , m_pm ,_T("SNLab"), pListContainer);
                //Version
                IRkcToolCommonOp::SetControlText( CA2T(vecDevItem.at(i).tDevEx.achDevSoftVersion) , m_pm ,_T("VersionLab"), pListContainer);
                pEquipmentList->Add(pListContainer);
            }
        }
    }
    return true;
}

bool CSearchEquipmentLogic::OnRkcSearchFinish( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    //��ť�ͷ�
    IRkcToolCommonOp::EnableControl(true, m_pm, _T("SearchBtn"));
    return true;
}

bool CSearchEquipmentLogic::OnRkcConnected( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    bool bIsLogin = (bool)wparam;
    EMRK100OptRtn emErr = (EMRK100OptRtn)lparam;
    if (bIsLogin || emErr == RK100_OPT_ERR_FIRST_LOGIN)
    {
        SetTimerOutTimer(true);
        //������
        m_pm->DoCase(_T("caseIsLogin"));
        TRK100LoginInfo tLoginInfo;
        CRkcComInterface->GetLoginInfo(tLoginInfo);
        IRkcToolCommonOp::SetControlText( CA2T(tLoginInfo.szUsr) , m_pm ,_T("nameLab"));
        //���ڱ��
        WINDOW_MGR_PTR->ShowWindow(g_stcStrBackGroundDlg.c_str(), false);
        WINDOW_MGR_PTR->CloseWindow(g_stcStrLoginDlg.c_str());
        WINDOW_MGR_PTR->ShowWindow(g_stcStrToolFrameDlg.c_str(), true);
        //��һ�ε�¼ǿ�Ƹ�����
        if (emErr == RK100_OPT_ERR_FIRST_LOGIN)
        {
            ShowMessageBox(_T("��ǰ����ΪĬ�����룬����������޸�"),1);
            CToolFrameLogic::GetSingletonPtr()->SetFirstLogin(true);
        }
        //������ʾ
        CToolFrameLogic::GetSingletonPtr()->InitBottomLeb();
    }
    else
    {
        m_pm->DoCase(_T("caseIsnotLogin"));
    }
    return true;
}

bool CSearchEquipmentLogic::OnRkcDisconnected( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    u8 byReason = (u8)wparam;
    m_pm->DoCase(_T("caseIsnotLogin"));
    SetTimerOutTimer(false);

    //�رյ������
    UIDATAMGR->CloseFileDlg();

    if (wparam == 1)
    {
        g_nGrabTimerID = SetTimer( NULL, 0, TIME_GRAB, CTimerOutFun );
    }
    return true;
}

bool CSearchEquipmentLogic::OnRkcReBoot( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    if (wparam)//������Ϣ���ͳɹ�
    {
        CRkcComInterface->CloseSocket();
        WINDOW_MGR_PTR->ShowWindow(g_stcStrToolFrameDlg.c_str(),false);
        m_pm->DoCase(_T("caseIsnotLogin"));
    }
    return true;
}

void CSearchEquipmentLogic::SetDevItem(TDevItem tDevItem)
{
    m_tDevItem = tDevItem;
}

TDevItem CSearchEquipmentLogic::GetDevItem()
{
    return m_tDevItem;
}

bool CSearchEquipmentLogic::OnSetBtnClicked(TNotifyUI& msg)
{
    if (CToolFrameLogic::GetSingletonPtr()->IsFirstLogin())//�����޸�ǿ�Ʋ����л�tab
    {
        return false;
    }
    // �˵�����λ��ˢ�£������������ڵ����λ��
    Window* pAppWindow = WINDOW_MGR_PTR->GetWindow(g_stcStrSetMenuDlg.c_str());
    if ( pAppWindow != NULL )
	{
        CSetMenuLogic::GetSingletonPtr()->OnUpdateWindowPos();
	}

    // �˵�������ʾ
    WINDOW_MGR_PTR->ShowWindow(g_stcStrSetMenuDlg.c_str(), true);
    CSetMenuLogic::GetSingletonPtr()->OnMenuShowInit();

    return true;
}

CString CSearchEquipmentLogic::GetIniFilePath()
{
    TCHAR tchPath[MAX_PATH] = {0};
    CString strIniFilePath;
    if (S_OK == SHGetFolderPathW(NULL,CSIDL_APPDATA,NULL,0,tchPath))
    {
        CString strIniFileDir(tchPath);
        strIniFileDir = strIniFileDir + _T("\\rkc100");		
        if(!PathFileExists(strIniFileDir))
        {
            CreateDirectory(strIniFileDir, NULL);
        }
        strIniFilePath = strIniFileDir + _T("\\conf.ini");
    }

    return strIniFilePath;
}


void CSearchEquipmentLogic::SetTimerOutTimer(bool bStart)
{
    KillTimer( NULL, g_nTimeOutTimerID );
    g_nTimeOutTimerID = 0;
    if (bStart && CRkcComInterface->IsLoginState())
    {
        g_nTimeOutTimerID = SetTimer( NULL, 0, TIME_TIMEROUT, CTimerOutFun );
    }
    return;
}

void CSearchEquipmentLogic::OnUpdateBGWindowPos()
{
    RECT rcParent;
    HWND hparent = m_pm->GetPaintWindow();
    GetWindowRect(hparent,&rcParent);

    s32 nLeft = rcParent.left;
    s32 nTop  = rcParent.top;

    // ������λ���Ƿ�ı䣬���±�������λ��
    if (nLeft != m_nLeft || nTop != m_nTop)
    {
        HWND hAppWind = FindWindow(NULL, g_stcStrBackGroundDlg.c_str());
        SetWindowPos(hAppWind, NULL, nLeft, nTop, 0, 0, SWP_NOSIZE |SWP_NOACTIVATE );
        m_nLeft = nLeft;
        m_nTop  = nTop;
    }
}

bool CSearchEquipmentLogic::OnShowBGWindow(LPCTSTR lpstrName, bool bShow)
{
    // ��������λ�ø��£������������ڵ����λ��
    Window* pAppWindow = WINDOW_MGR_PTR->GetWindow(lpstrName);
    if ( pAppWindow != NULL )
    {
        OnUpdateBGWindowPos();
    }

    WINDOW_MGR_PTR->ShowWindow(lpstrName, bShow);
    return false;
}
