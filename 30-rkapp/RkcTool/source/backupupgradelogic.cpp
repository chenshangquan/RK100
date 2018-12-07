#include "stdafx.h"
#include "searchequipmentlogic.h"
#include "backupupgradelogic.h"
#include "messageboxlogic.h"
#include "tipboxlogic.h"
#include "radiosetuplogic.h"
#include "cmd5.h"

static std::map<char, u8> map16hex;

static UINT     g_nUpLoadProcess;                     //上传进度
static UINT     g_nUpLoadProcessTimerID;              //timer 的id,用于控制显示时间
static UINT     g_nTftpOpenTimerID;                   //timer 的id,用于Tftp开启后的延迟上传
#define         TIME_UPLOAD        1000               //定时器时间间隔
#define         TIME_TFTP          2000               //TFTP定时器时间间隔

VOID  CALLBACK  CUploadTimerFun(  HWND   hwnd,   UINT   uMsg, UINT_PTR  idEvent, DWORD   dwTime  )
{
    if ( idEvent == g_nUpLoadProcessTimerID )
    {
        CString strtmp = _T("");
        if (g_nUpLoadProcess < 90)
        {
            g_nUpLoadProcess += 10;
        }
        strtmp.Format(_T("文件上传中(%d%%)..."),g_nUpLoadProcess);
        IRkcToolCommonOp::SetControlText(strtmp, CBackupUpgradeLogic::GetSingletonPtr()->GetPaintManagerUI(), _T("UpgradeFileLab"));
    }
    else if (idEvent == g_nTftpOpenTimerID)
    {
        KillTimer( NULL, g_nTftpOpenTimerID );
        g_nTftpOpenTimerID = 0;
        CBackupUpgradeLogic::GetSingletonPtr()->SendUpdateFirst();
    }
}

template<> CBackupUpgradeLogic* Singleton<CBackupUpgradeLogic>::ms_pSingleton  = NULL;

APP_BEGIN_MSG_MAP(CBackupUpgradeLogic, CNotifyUIImpl)
    MSG_SELECTCHANGE(_T("ConfigurationBackupOpt"), OnTabConfigurationBackup)
    MSG_SELECTCHANGE(_T("EquipmentUpgradingOpt"), OnTabEquipmentUpgrading)
    MSG_SELECTCHANGE(_T("RestoredOriginalOpt"), OnTabRestoredOriginal)

    MSG_CLICK(_T("backupsBtn"), OnBackupsBtnClick)
    MSG_CLICK(_T("ImportBtn"), OnImportBtnClick)
    MSG_CLICK(_T("UpgradeFilePathBtn"), OnUpgradeFilePathBtnClick)
    MSG_CLICK(_T("UpLoadFileBtn"), OnUpLoadFileBtnClick)
    MSG_CLICK(_T("RestoreRkBtn"), OnRestoreRkBtnClick)

    MSG_EDITCHANGE(_T("PasswardEdt"), OnPWEditTextChange)

    USER_MSG(UI_RKC_RESTONE , OnRkcRestone)
    USER_MSG(UI_RKC_UPDATE_FIRST_ACK , OnRkcUpdateFirstAck)
    USER_MSG(UI_RKC_UPDATE_FIRST_NTY , OnRkcUpdateFirstNty)
    USER_MSG(UI_RKC_UPDATE_SECOND_NTY , OnRkcUpdateSecondNty)
    USER_MSG(UI_RKC_DISCONNECTED , OnRkcDisconnected)
APP_END_MSG_MAP()

CBackupUpgradeLogic::CBackupUpgradeLogic()
{
    map16hex.insert(pair<char, u8>('0', 0));
    map16hex.insert(pair<char, u8>('1', 1));
    map16hex.insert(pair<char, u8>('2', 2));
    map16hex.insert(pair<char, u8>('3', 3));
    map16hex.insert(pair<char, u8>('4', 4));
    map16hex.insert(pair<char, u8>('5', 5));
    map16hex.insert(pair<char, u8>('6', 6));
    map16hex.insert(pair<char, u8>('7', 7));
    map16hex.insert(pair<char, u8>('8', 8));
    map16hex.insert(pair<char, u8>('9', 9));
    map16hex.insert(pair<char, u8>('A', 10));
    map16hex.insert(pair<char, u8>('B', 11));
    map16hex.insert(pair<char, u8>('C', 12));
    map16hex.insert(pair<char, u8>('D', 13));
    map16hex.insert(pair<char, u8>('E', 14));
    map16hex.insert(pair<char, u8>('F', 15));

    g_nUpLoadProcess = 0;
    g_nUpLoadProcessTimerID = 0;

    m_strTftpFilePath = _T("");
}

CBackupUpgradeLogic::~CBackupUpgradeLogic()
{
}

bool CBackupUpgradeLogic::OnTabConfigurationBackup(TNotifyUI& msg)
{
    CTabLayoutUI* pBackupUpgradeTab = (CTabLayoutUI*)IRkcToolCommonOp::FindControl( m_pm, _T("BackupUpgradeTab") );
    if (pBackupUpgradeTab)
    {
        pBackupUpgradeTab->SelectItem(emTabID_ConfigurationBackup);
    }
    return true;
}

bool CBackupUpgradeLogic::OnTabEquipmentUpgrading(TNotifyUI& msg)
{
    CTabLayoutUI* pBackupUpgradeTab = (CTabLayoutUI*)IRkcToolCommonOp::FindControl( m_pm, _T("BackupUpgradeTab") );
    if (pBackupUpgradeTab)
    {
        pBackupUpgradeTab->SelectItem(emTabID_EquipmentUpgrading);
    }
    return true;
}

bool CBackupUpgradeLogic::OnTabRestoredOriginal(TNotifyUI& msg)
{
    CTabLayoutUI* pBackupUpgradeTab = (CTabLayoutUI*)IRkcToolCommonOp::FindControl( m_pm, _T("BackupUpgradeTab") );
    if (pBackupUpgradeTab)
    {
        pBackupUpgradeTab->SelectItem(emTabID_RestoredOriginal);
    }
    return true;
}

bool CBackupUpgradeLogic::OnBackupsBtnClick(TNotifyUI& msg)
{
    //获得本机时间
    SYSTEMTIME systime;
    GetLocalTime( &systime );
    //配置文件路径
    CString strFileDate = _T("");
    strFileDate.Format(_T("\\Config%04d%02d%02d"), systime.wYear, systime.wMonth, systime.wDay);
    CString strdirpath = UIDATAMGR->SetFileName(_T("文件 (*.ini)|*.ini||"), _T("D:\\"), strFileDate, FALSE);
    if (strdirpath.IsEmpty() || CRkcComInterface->IsLoginState() == false)
    {
        return false;
    }
    //备份信息
    CString strConfigTime = _T("");
    strConfigTime.Format(_T("%04d/%02d/%02d %02d:%02d:%02d"),systime.wYear, systime.wMonth, systime.wDay, systime.wHour, systime.wMinute, systime.wSecond);
    WritePrivateProfileString(_T("CONFIGINFO"), _T("TIME"), strConfigTime, strdirpath);
    TDevItem tLoginDevitem;
    CRkcComInterface->GetLoginDevItem(tLoginDevitem);
    WritePrivateProfileString(_T("CONFIGINFO"), _T("MODEL"), CA2T(tLoginDevitem.tDevID.achDevType), strdirpath);
    //工作模式
    TRK100WorkMode tRK100WorkMode;
    memset(&tRK100WorkMode, 0, sizeof(TRK100WorkMode));
    CRkcComInterface->GetWorkModeConfig(tRK100WorkMode);
    //网络配置
    TRK100NetParam tRK100NetParam;
    memset(&tRK100NetParam, 0, sizeof(TRK100NetParam));
    CRkcComInterface->GetNetWorkConfig(tRK100NetParam);
    if (tRK100NetParam.dwIP == 0)
    {
        ShowTipBox(_T("导出失败"));
        remove(CT2A(strdirpath));
        return false;
    }

    in_addr tAddrIP;
    tAddrIP.S_un.S_addr = tRK100NetParam.dwIP;
    WritePrivateProfileString(_T("TRK100NetParam"), _T("dwIP"), (CA2T)inet_ntoa(tAddrIP), strdirpath);
    tAddrIP.S_un.S_addr = tRK100NetParam.dwSubMask;
    WritePrivateProfileString(_T("TRK100NetParam"), _T("dwSubMask"), (CA2T)inet_ntoa(tAddrIP), strdirpath);
    tAddrIP.S_un.S_addr = tRK100NetParam.dwGateway;
    WritePrivateProfileString(_T("TRK100NetParam"), _T("dwGateway"), (CA2T)inet_ntoa(tAddrIP), strdirpath);
    tAddrIP.S_un.S_addr = tRK100NetParam.dwMqttIP;
    WritePrivateProfileString(_T("TRK100NetParam"), _T("dwMqttIP"), (CA2T)inet_ntoa(tAddrIP), strdirpath);
    CString strPort= _T("");
    strPort.Format(_T("%u"), tRK100NetParam.MqttPort);
    WritePrivateProfileString(_T("TRK100NetParam"), _T("MqttPort"), strPort, strdirpath);

    CString strbuff = _T("");
    strbuff.Format(_T("%d"), tRK100WorkMode.FuncMod[0].AcFlag);
    WritePrivateProfileString(_T("TRK100WorkMode"), _T("FuncMod[0].AcFlag"), strbuff, strdirpath);
    strbuff = _T("");
    strbuff.Format(_T("%d"), tRK100WorkMode.FuncMod[0].AcDelay);
    WritePrivateProfileString(_T("TRK100WorkMode"), _T("FuncMod[0].AcDelay"), strbuff, strdirpath);
    strbuff = _T("");
    strbuff.Format(_T("%d"), tRK100WorkMode.FuncMod[1].AcFlag);
    WritePrivateProfileString(_T("TRK100WorkMode"), _T("FuncMod[1].AcFlag"), strbuff, strdirpath);
    strbuff = _T("");
    strbuff.Format(_T("%d"), tRK100WorkMode.FuncMod[1].AcDelay);
    WritePrivateProfileString(_T("TRK100WorkMode"), _T("FuncMod[1].AcDelay"), strbuff, strdirpath);

    if (tRK100WorkMode.FuncMod[0].RfFlag != 0)
    {
        WritePrivateProfileString(_T("TRK100WorkMode"), _T("FuncMod[0].RfFlag"), _T("1"), strdirpath);
    }
    else
    {
        WritePrivateProfileString(_T("TRK100WorkMode"), _T("FuncMod[0].RfFlag"), _T("0"), strdirpath);
    }
    for (u8 i = 0 ; i < MAX_RADIO_COUNT ; i++)
    {
        CString strSign = _T("");
        strSign.Format(_T("FuncMod[0].RfID[%d][0]"), i );
        if (tRK100WorkMode.FuncMod[0].RfID[i][0] != 0)
        {
            WritePrivateProfileString(_T("TRK100WorkMode"), strSign, _T("1"), strdirpath);
        }
        else
        {
            WritePrivateProfileString(_T("TRK100WorkMode"), strSign, _T("0"), strdirpath);
        }
        strSign.Format(_T("FuncMod[0].RfID[%d][1-4]"), i );
        CString strID = _T("");
        strID.Format(_T("%02X%02X%02X%02X"),    tRK100WorkMode.FuncMod[0].RfID[i][1], 
                                                tRK100WorkMode.FuncMod[0].RfID[i][2], 
                                                tRK100WorkMode.FuncMod[0].RfID[i][3], 
                                                tRK100WorkMode.FuncMod[0].RfID[i][4]    );
        WritePrivateProfileString(_T("TRK100WorkMode"), strSign, strID, strdirpath);
    }

    ShowTipBox(_T("导出成功"));
    return true;
}

bool CBackupUpgradeLogic::OnImportBtnClick(TNotifyUI& msg)
{
    std::wstring strfilepath = _T("");
    TCHAR tchConfigTime[32] = {0};
    TCHAR tchConfigModel[32] = {0};
    do 
    {
        strfilepath = UIDATAMGR->SetFileName(_T("文件 (*.ini)|*.ini||"), _T("D:\\"), _T(""));
        if (strfilepath.empty() || CRkcComInterface->IsLoginState() == false)
        {
            return false;
        }
        memset(tchConfigTime,0,sizeof(tchConfigTime));
        memset(tchConfigModel,0,sizeof(tchConfigModel));
        GetPrivateProfileString(_T("CONFIGINFO"), _T("TIME"), _T(""), tchConfigTime, 31, strfilepath.c_str());
        GetPrivateProfileString(_T("CONFIGINFO"), _T("MODEL"), _T(""), tchConfigModel, 31, strfilepath.c_str());

        TDevItem tLoginDevitem;
        CRkcComInterface->GetLoginDevItem(tLoginDevitem);
        if (wcscmp(tchConfigModel, CA2T(tLoginDevitem.tDevID.achDevType)) != 0)
        {
            int nBoxRe = ShowMessageBox(_T("请选择正确的RK100配置文件"), 2, _T("重新选择"));
            if (nBoxRe != IDOK)
            {
                return false;
            }
        }
        else
        {
            break;
        }
    }while (true);

    TCHAR tchConfig[64] = {0};
    //工作模式
    TRK100WorkMode tRK100WorkMode;
    memset(&tRK100WorkMode, 0, sizeof(TRK100WorkMode));
    //网络配置
    TRK100NetParam tRK100NetParam;
    memset(&tRK100NetParam, 0, sizeof(TRK100NetParam));

    tRK100WorkMode.FuncMod[0].AcFlag = GetPrivateProfileInt(_T("TRK100WorkMode"), _T("FuncMod[0].AcFlag"), 0, strfilepath.c_str());
    tRK100WorkMode.FuncMod[0].AcDelay = GetPrivateProfileInt(_T("TRK100WorkMode"), _T("FuncMod[0].AcDelay"), 0, strfilepath.c_str());
    tRK100WorkMode.FuncMod[1].AcFlag = GetPrivateProfileInt(_T("TRK100WorkMode"), _T("FuncMod[1].AcFlag"), 0, strfilepath.c_str());
    tRK100WorkMode.FuncMod[1].AcDelay = GetPrivateProfileInt(_T("TRK100WorkMode"), _T("FuncMod[1].AcDelay"), 0, strfilepath.c_str());

    tRK100WorkMode.FuncMod[0].RfFlag = GetPrivateProfileInt(_T("TRK100WorkMode"), _T("FuncMod[0].RfFlag"), 0, strfilepath.c_str());

    for (int i = 0 ; i < MAX_RADIO_COUNT ; i++)
    {
        CString strSign = _T("");
        strSign.Format(_T("FuncMod[0].RfID[%d][0]"), i );
        tRK100WorkMode.FuncMod[0].RfID[i][0] = GetPrivateProfileInt(_T("TRK100WorkMode"), strSign, 0, strfilepath.c_str());

        strSign.Format(_T("FuncMod[0].RfID[%d][1-4]"), i );
        char tchRdID[32] = {0};
        GetPrivateProfileStringA("TRK100WorkMode", CT2A(strSign), "", tchRdID, 31, CT2A(strfilepath.c_str()));
        
        tRK100WorkMode.FuncMod[0].RfID[i][1] = map16hex[tchRdID[0]] * 16 + map16hex[tchRdID[1]];
        tRK100WorkMode.FuncMod[0].RfID[i][2] = map16hex[tchRdID[2]] * 16 + map16hex[tchRdID[3]];
        tRK100WorkMode.FuncMod[0].RfID[i][3] = map16hex[tchRdID[4]] * 16 + map16hex[tchRdID[5]];
        tRK100WorkMode.FuncMod[0].RfID[i][4] = map16hex[tchRdID[6]] * 16 + map16hex[tchRdID[7]];
    }

    memset(tchConfig,0,sizeof(tchConfig));
    GetPrivateProfileString(_T("TRK100NetParam"), _T("dwIP"),_T(""), tchConfig, 32, strfilepath.c_str());
    tRK100NetParam.dwIP = inet_addr(CT2A(tchConfig));
    memset(tchConfig,0,sizeof(tchConfig));
    GetPrivateProfileString(_T("TRK100NetParam"), _T("dwSubMask"),_T(""), tchConfig, 32, strfilepath.c_str());
    tRK100NetParam.dwSubMask = inet_addr(CT2A(tchConfig));
    memset(tchConfig,0,sizeof(tchConfig));
    GetPrivateProfileString(_T("TRK100NetParam"), _T("dwGateway"),_T(""), tchConfig, 32, strfilepath.c_str());
    tRK100NetParam.dwGateway = inet_addr(CT2A(tchConfig));
    memset(tchConfig,0,sizeof(tchConfig));
    GetPrivateProfileString(_T("TRK100NetParam"), _T("dwMqttIP"),_T(""), tchConfig, 32, strfilepath.c_str());
    tRK100NetParam.dwMqttIP = inet_addr(CT2A(tchConfig));
    tRK100NetParam.MqttPort = GetPrivateProfileInt(_T("TRK100NetParam"),_T("MqttPort"), 0, strfilepath.c_str());

    int nBoxRe = ShowBackUpBox(tchConfigTime,tchConfigModel,strfilepath.c_str());
    if (nBoxRe == IDOK)
    {
        CRkcComInterface->SetNetWorkConfig(tRK100NetParam);
        CRkcComInterface->SetWorkModeConfig(tRK100WorkMode);
    }
    return true;
}

bool CBackupUpgradeLogic::OnUpgradeFilePathBtnClick(TNotifyUI& msg)
{
    CButtonUI* pMsgSpend = (CButtonUI*)msg.pSender;
    if (!pMsgSpend)
    {
        return false;
    }
    pMsgSpend->SetEnabled(false);
    int nBoxRe = IDOK;
    do 
    {
        IRkcToolCommonOp::SetControlText( _T("") , m_pm ,_T("UpgradeFilePathEdt"));
        m_pm->DoCase(_T("caseNoFilePath"));
        pMsgSpend->SetEnabled(false);
        std::wstring strfilepath = UIDATAMGR->SetFileName(_T("bin文件 (*.bin)|*.bin||"), _T("D:\\"), _T(""));
        if (strfilepath.empty() || CRkcComInterface->IsLoginState() == false)
        {
            pMsgSpend->SetEnabled(true);
            return false;
        }
        string sFileName = CT2A(strfilepath.c_str());
        int nIndex = sFileName.find_last_of('\\');
        if (nIndex > 0 && nIndex < strlen(sFileName.c_str()))
        {
            sFileName = sFileName.substr(nIndex+1, strlen(sFileName.c_str()));
        }
        if (strcmp(sFileName.c_str(), RKC_UPDATEFILE_NAME) != 0)
        {
            nBoxRe = ShowMessageBox(_T("请使用设备配套软件版本"),2,_T("重新选择"));
        }
        else
        {
            IRkcToolCommonOp::SetControlText( strfilepath.c_str() , m_pm ,_T("UpgradeFilePathEdt"));
            OnUpLoadFileFirst();
            return true;
        }
    } while (nBoxRe == IDOK);
    pMsgSpend->SetEnabled(true);
    return true;
}

bool CBackupUpgradeLogic::OnUpLoadFileFirst()
{
    CString strFilePath = (IRkcToolCommonOp::GetControlText( m_pm ,_T("UpgradeFilePathEdt"))).c_str();
    m_strTftpFilePath = strFilePath;
    if (strFilePath.IsEmpty())
    {
        ShowMessageBox(_T("还没选择文件路径"));
        return false;
    }
    string sFilePath = CT2A(strFilePath);
    //开启ftp
    CRkcComInterface->KillTftpProcess();//先关闭TFTP进程
    if (!CRkcComInterface->OpenTftp())
    {
        ShowMessageBox(_T("TFTP服务器开启失败"));
        return false;
    }
    //设置ftp路径
    string strFileDir = CT2A(strFilePath);
    int nIndex = strFileDir.find_last_of('\\');
    if (nIndex > 0 && nIndex < strlen(strFileDir.c_str()))
    {
        strFileDir = strFileDir.substr(0, nIndex);
    }
    if (!CRkcComInterface->SetTftpPath(strFileDir.c_str()))
    {
        ShowMessageBox(_T("设置Tftp文件路径失败"));
        return false;
    }
    g_nTftpOpenTimerID = SetTimer( NULL, 0, TIME_TFTP, CUploadTimerFun );
    return true;
}

void CBackupUpgradeLogic::SendUpdateFirst()
{
    //bin包大小
    CFile cfile; 
    unsigned int nFileSize = 0;
    if (cfile.Open(m_strTftpFilePath, CFile::modeRead))  
    {
        nFileSize = cfile.GetLength();  
    }
    //数据发送
    TRK100TftpFwUpdate tRK100TftpFwUpdate;
    memset(&tRK100TftpFwUpdate, 0, sizeof(TRK100TftpFwUpdate));
    tRK100TftpFwUpdate.dwTftpSvrIp = UIDATAMGR->get_local_ip();
    tRK100TftpFwUpdate.dwFileSize = nFileSize;
    strncpy(tRK100TftpFwUpdate.szFwTypeName , RKC_UPDATEFILE_TYPE, sizeof(RKC_UPDATEFILE_TYPE) );
    strncpy(tRK100TftpFwUpdate.szFileFullName , RKC_UPDATEFILE_NAME, sizeof(RKC_UPDATEFILE_NAME) );
    tRK100TftpFwUpdate.byChkSumValid = 0;
    CRkcComInterface->SetFtpUpdateFirst(tRK100TftpFwUpdate);
    //m_pm->DoCase(_T("caseUpLoadFile"));
}

bool CBackupUpgradeLogic::OnUpLoadFileBtnClick(TNotifyUI& msg)
{
    m_pm->DoCase(_T("caseUpLoadFile"));
    //开始定时器 到达时间后关闭窗口
    CString strtmp = _T("");
    strtmp.Format(_T("文件上传中(%d%%)..."),g_nUpLoadProcess);
    IRkcToolCommonOp::SetControlText(strtmp,m_pm,_T("UpgradeFileLab"));
    g_nUpLoadProcessTimerID = SetTimer( NULL, 0, TIME_UPLOAD, CUploadTimerFun );
    //开始上传
    CRkcComInterface->SetFtpUpdateSecond();
    return true;

//     CString strFilePath = (IRkcToolCommonOp::GetControlText( m_pm ,_T("UpgradeFilePathEdt"))).c_str();
//     if (strFilePath.IsEmpty())
//     {
//         ShowMessageBox(_T("还没选择文件路径"));
//         return false;
//     }
//     string sFilePath = CT2A(strFilePath);
//     //开启ftp
//     CRkcComInterface->KillTftpProcess();//先关闭TFTP进程
//     if (!CRkcComInterface->OpenTftp())
//     {
//         ShowMessageBox(_T("TFTP服务器开启失败"));
//         return false;
//     }
//     //设置ftp路径
//     string strFileDir = CT2A(strFilePath);
//     int nIndex = strFileDir.find_last_of('\\');
//     if (nIndex > 0 && nIndex < strlen(strFileDir.c_str()))
//     {
//         strFileDir = strFileDir.substr(0, nIndex);
//     }
//     if (!CRkcComInterface->SetTftpPath(strFileDir.c_str()))
//     {
//         ShowMessageBox(_T("设置Tftp文件路径失败"));
//         return false;
//     }
//     //bin包大小
//     CFile cfile; 
//     unsigned int nFileSize = 0;
//     if (cfile.Open(strFilePath, CFile::modeRead))  
//     {
//         nFileSize = cfile.GetLength();  
//     }
//     //数据发送
//     TRK100TftpFwUpdate tRK100TftpFwUpdate;
//     memset(&tRK100TftpFwUpdate, 0, sizeof(TRK100TftpFwUpdate));
//     tRK100TftpFwUpdate.dwTftpSvrIp = UIDATAMGR->get_local_ip();
//     tRK100TftpFwUpdate.dwFileSize = nFileSize;
//     strncpy(tRK100TftpFwUpdate.szFwTypeName , RKC_UPDATEFILE_TYPE, sizeof(RKC_UPDATEFILE_TYPE) );
//     strncpy(tRK100TftpFwUpdate.szFileFullName , RKC_UPDATEFILE_NAME, sizeof(RKC_UPDATEFILE_NAME) );
//     tRK100TftpFwUpdate.byChkSumValid = 0;
//     CRkcComInterface->SetFtpUpdateFirst(tRK100TftpFwUpdate);
//     m_pm->DoCase(_T("caseUpLoadFile"));
//     return true;
}

bool CBackupUpgradeLogic::OnRestoreRkBtnClick(TNotifyUI& msg)
{
    CString strPassWord = (IRkcToolCommonOp::GetControlText( m_pm ,_T("PasswardEdt"))).c_str();
    if (strPassWord.IsEmpty())
    {
        ShowMessageBox(_T("设备密码不能为空。"));
        return false;
    }

    TRK100LoginInfo tLoginInfo;
    CRkcComInterface->GetLoginInfo(tLoginInfo);
    if (strcmp(tLoginInfo.szPwd, (CT2A)strPassWord) != 0)
    {
        IRkcToolCommonOp::ShowControl(true, m_pm, _T("PWTipLeb"));
    }
    else
    {
        int nBoxRe = ShowMessageBox(_T("设备即将恢复出厂设置，请确认操作"),2);
        if (nBoxRe == IDOK)
        {
            //密码输入框清空
            IRkcToolCommonOp::SetControlText(_T(""), m_pm, _T("PasswardEdt"));

            TRK100LoginInfo tRK100LoginInfo;
            memset(&tRK100LoginInfo,0,sizeof(TRK100LoginInfo));
            strncpy(tRK100LoginInfo.szPwd,  CT2A(strPassWord), sizeof(tRK100LoginInfo.szPwd));
            CMD5Encrypt cMd5;
            cMd5.GetEncrypted(tRK100LoginInfo.szPwd, tRK100LoginInfo.szPwd);//Md5加密
            CRkcComInterface->RestoreRk(tRK100LoginInfo);

            ShowMessageBox(_T("设备正在恢复出厂中，请勿关机"),0);
        }
    }

    return true;
}

bool CBackupUpgradeLogic::OnPWEditTextChange(TNotifyUI& msg)
{
    IRkcToolCommonOp::ShowControl(false, m_pm, _T("PWTipLeb"));
    return true;
}

bool CBackupUpgradeLogic::OnRkcRestone( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    bool bIsSuccess = (bool)wparam;
    EMRK100OptRtn emErr = (EMRK100OptRtn)lparam;
    if (bIsSuccess == false)
    {
        if (emErr == RK100_OPT_ERR_PASSWORD)
        {
            IRkcToolCommonOp::ShowControl(true, m_pm, _T("PWTipLeb"));
        }
    }
    return true;
}

bool CBackupUpgradeLogic::OnRkcUpdateFirstAck( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    bool bIsSuccess = (bool)wparam;
    EMRK100OptRtn emErr = (EMRK100OptRtn)lparam;
    if (bIsSuccess)
    {

    }
    else
    {
        IRkcToolCommonOp::EnableControl(true,m_pm,_T("UpgradeFilePathBtn"));
    }
    return true;
}

bool CBackupUpgradeLogic::OnRkcUpdateFirstNty( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    IRkcToolCommonOp::EnableControl(true,m_pm,_T("UpgradeFilePathBtn"));

    bool bIsSuccess = (bool)wparam;
    EMRK100OptRtn emErr = (EMRK100OptRtn)lparam;
    if (bIsSuccess)
    {
        TDevItem tLoginDevitem;
        CRkcComInterface->GetLoginDevItem(tLoginDevitem);
        TRK100UpdateHead tRK100UpdateHead;
        memset(&tRK100UpdateHead,0,sizeof(TRK100UpdateHead));
        CRkcComInterface->GetUpdateConfig(tRK100UpdateHead);
        char achver[64] = {0};
        sprintf(achver,"%s",tRK100UpdateHead.Version);
        //int nBoxRe = ShowUpDateBox(CA2T(tLoginDevitem.tDevID.achDevType), CA2T(tLoginDevitem.tDevEx.achDevSoftVersion), CA2T(achver));
        //if (nBoxRe == IDOK)
        {
            m_pm->DoCase(_T("caseCheckFilePath"));
            IRkcToolCommonOp::SetControlText( CA2T(tLoginDevitem.tDevEx.achDevSoftVersion) , m_pm, _T("CurrentVerShowLab") );
            IRkcToolCommonOp::SetControlText( CA2T(achver) , m_pm, _T("UpgradeVerShowLab") );
            //CRkcComInterface->SetFtpUpdateSecond();
        }
        //else
        //{
        //    m_pm->DoCase(_T("caseCheckFilePath"));
        //    CRkcComInterface->KillTftpProcess();
        //}
    }
    else
    {
        m_pm->DoCase(_T("caseUpLoadFileFail"));
        CRkcComInterface->KillTftpProcess();
    }
    return true;
}

bool CBackupUpgradeLogic::OnRkcUpdateSecondNty( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    CRkcComInterface->KillTftpProcess();
    KillTimer( NULL, g_nUpLoadProcessTimerID );
    g_nUpLoadProcessTimerID = 0;
    g_nUpLoadProcess = 0;

    bool bIsSuccess = (bool)wparam;
    EMRK100OptRtn emErr = (EMRK100OptRtn)lparam;
    if (bIsSuccess)
    {
        m_pm->DoCase(_T("caseUpLoadFileSuccess"));
        ShowMessageBox(_T("设备升级成功，即将进入重启，请勿断电！"),1);
        CRkcComInterface->ReBootRk();
        return true;
    }
    else
    {
        m_pm->DoCase(_T("caseUpLoadFileFail"));
    }
    return true;
}

bool CBackupUpgradeLogic::OnRkcDisconnected( WPARAM wparam, LPARAM lparam, bool& bHandle )
{
    KillTimer( NULL, g_nUpLoadProcessTimerID );
    g_nUpLoadProcessTimerID = 0;

    //密码输入框清空
    IRkcToolCommonOp::SetControlText(_T(""), m_pm, _T("PasswardEdt"));
    IRkcToolCommonOp::ShowControl(false, m_pm, _T("PWTipLeb"));

    IRkcToolCommonOp::SetControlText( _T("") , m_pm ,_T("UpgradeFilePathEdt"));
    m_pm->DoCase(_T("caseNoFilePath"));
    return true;
}