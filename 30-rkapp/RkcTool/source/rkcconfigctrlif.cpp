#include "stdafx.h"
#include "rkcinterface.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "UIDataMgr.h"

u16 CRkcInterface::ReBootRk()
{
    if( NULL == m_pConfigCtrlIf )
    {
        return -1;
    }

    u16 re  = m_pConfigCtrlIf->ReBootRk();

    return re;
}

u16 CRkcInterface::RestoreRk(TRK100LoginInfo tRK100LoginInfo)
{
    if( NULL == m_pConfigCtrlIf )
    {
        return -1;
    }

    u16 re  = m_pConfigCtrlIf->RestoreRk(tRK100LoginInfo);

    return re;
}


u16 CRkcInterface::GetWorkModeConfig()
{
    if( NULL == m_pConfigCtrlIf )
    {
        return -1;
    }

    u16 re  = m_pConfigCtrlIf->GetWorkModeConfig();

    return re;
}

u16 CRkcInterface::GetWorkModeConfig(TRK100WorkMode& tRK100WorkMode)
{
    if( NULL == m_pConfigCtrlIf )
    {
        return -1;
    }

    u16 re  = m_pConfigCtrlIf->GetWorkModeConfig(tRK100WorkMode);

    return re;
}

u16 CRkcInterface::SetWorkModeConfig(TRK100WorkMode tRK100WorkMode)
{
    if( NULL == m_pConfigCtrlIf )
    {
        return -1;
    }

    u16 re  = m_pConfigCtrlIf->SetWorkModeConfig(tRK100WorkMode);

    return re;
}

u16 CRkcInterface::GetNetWorkConfig()
{
    if( NULL == m_pConfigCtrlIf )
    {
        return -1;
    }

    u16 re  = m_pConfigCtrlIf->GetNetWorkConfig();

    return re;
}

u16 CRkcInterface::GetNetWorkConfig(TRK100NetParam& tRK100NetParam)
{
    if( NULL == m_pConfigCtrlIf )
    {
        return -1;
    }

    u16 re  = m_pConfigCtrlIf->GetNetWorkConfig(tRK100NetParam);

    return re;
}

u16 CRkcInterface::SetNetWorkConfig(TRK100NetParam tRK100NetParam)
{
    if( NULL == m_pConfigCtrlIf )
    {
        return -1;
    }

    u16 re  = m_pConfigCtrlIf->SetNetWorkConfig(tRK100NetParam);

    return re;
}

u16 CRkcInterface::SetFtpUpdateFirst(TRK100TftpFwUpdate tRK100TftpFwUpdate)
{
    if( NULL == m_pConfigCtrlIf )
    {
        return -1;
    }

    u16 re  = m_pConfigCtrlIf->SetFtpUpdateFirst(tRK100TftpFwUpdate);

    return re;
}

u16 CRkcInterface::SetFtpUpdateSecond()
{
    if( NULL == m_pConfigCtrlIf )
    {
        return -1;
    }

    u16 re  = m_pConfigCtrlIf->SetFtpUpdateSecond();

    return re;
}

u16 CRkcInterface::GetUpdateConfig(TRK100UpdateHead& tRK100UpdateHead)
{
    if( NULL == m_pConfigCtrlIf )
    {
        return -1;
    }

    u16 re  = m_pConfigCtrlIf->GetUpdateConfig(tRK100UpdateHead);

    return re;
}

u16 CRkcInterface::GetPowerConfig()
{
    if( NULL == m_pConfigCtrlIf )
    {
        return -1;
    }

    u16 re  = m_pConfigCtrlIf->GetPowerConfig();

    return re;
}

u16 CRkcInterface::GetPowerConfig(TRK100PowerInfo& tRK100PowerInfo)
{
    if( NULL == m_pConfigCtrlIf )
    {
        return -1;
    }

    u16 re  = m_pConfigCtrlIf->GetPowerConfig(tRK100PowerInfo);

    return re;
}

u16 CRkcInterface::GetDebugConfig()
{
    if( NULL == m_pConfigCtrlIf )
    {
        return -1;
    }

    u16 re  = m_pConfigCtrlIf->GetDebugConfig();

    return re;
}

u16 CRkcInterface::GetDebugConfig(TRK100DebugMode& tRK100DebugInfo)
{
    if( NULL == m_pConfigCtrlIf )
    {
        return -1;
    }

    u16 re  = m_pConfigCtrlIf->GetDebugConfig(tRK100DebugInfo);

    return re;
}

u16 CRkcInterface::SetDebugConfig(TRK100DebugMode tRK100DebugInfo)
{
    if( NULL == m_pConfigCtrlIf )
    {
        return -1;
    }

    u16 re  = m_pConfigCtrlIf->SetDebugConfig(tRK100DebugInfo);

    return re;
}