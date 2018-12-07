// UIDataMgr.cpp: implementation of the CUIDataMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UIDataMgr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CUIDataMgr *CUIDataMgr::m_pThis = NULL;
CUIDataMgr::CUIDataMgr()
{
}

CUIDataMgr::~CUIDataMgr()
{
}


CUIDataMgr* CUIDataMgr::GetSingleTon()
{
    if ( m_pThis == NULL )
    {
        m_pThis = new CUIDataMgr();
    }
    return m_pThis;
}

CString CUIDataMgr::SetFileName(CString filter, CString defaultDir, CString fileName, BOOL isOpen)
{
    try
    {
        CFileDialog openFileDlg(isOpen, defaultDir, fileName, OFN_HIDEREADONLY|OFN_READONLY, filter, NULL);
        openFileDlg.GetOFN().lpstrInitialDir = (defaultDir + fileName);
        INT_PTR result = openFileDlg.DoModal();
        CString filePath = defaultDir + fileName;
        if(result == IDOK) 
        {
            filePath = openFileDlg.GetPathName();
        }
        else
        {
            filePath = _T("");
        }
        return filePath;
    }
    catch(...)
    {
        return _T("");
    }
}

void CUIDataMgr::CloseFileDlg()
{
    HWND hwnd1 = ::FindWindow(NULL,_T("打开"));
    if (hwnd1)
    {
        ::PostMessage(hwnd1,WM_COMMAND,MAKELONG(IDCANCEL,0),1);
    }
    HWND hwnd2 = ::FindWindow(NULL,_T("另存为"));
    if (hwnd2)
    {
        ::PostMessage(hwnd2,WM_COMMAND,MAKELONG(IDCANCEL,0),1);
    }
}

void CUIDataMgr::split(const string& s,vector<int>& sv,const char flag) 
{
    sv.clear();
    istringstream iss(s);
    string temp;

    while (getline(iss, temp, flag)) 
    {
        sv.push_back(stoi(temp));
    }
    return;
}

BOOL32 CUIDataMgr::IsValidIp( LPCSTR lptrIPStr )
{
    if ( lptrIPStr == NULL ) 
    {
        return FALSE;
    }

    s32 nDot    = 0;                        //  已处理的字符串里的点号数
    s32 nData   = 0;                        //  已处理的字符串里的数值
    s32 nPos	= 0;						//	两点之间的间隔
    s32 nLen    = strlen( lptrIPStr );     //  字符串长度

    //  字符串最少7位最长15位, 且不能以'0'开头
    if ( nLen < 7 || nLen > 15 ) 
    {
        return FALSE;
    }

    if (strstr(lptrIPStr,".."))
    {
        return FALSE;
    }

    if ( lptrIPStr[0] == '0' /*|| ( lptrIPStr[0] == '2' && lptrIPStr[1] == '5' && lptrIPStr[2] == '5' )*/ )
    {
        return FALSE;
    }

    if ( lptrIPStr[0] == '.' || lptrIPStr[nLen - 1] == '.' )
    {
        return FALSE;
    }

    for ( s32 nCount = 0; nCount < nLen; ++nCount )
    {
        if ( lptrIPStr[nCount] >= '0' && lptrIPStr[nCount] <= '9' )//遇到数字
        {
            nData = 10 * nData + lptrIPStr[nCount] - '0';     //计算数值
            ++nPos;
        }
        else if ( lptrIPStr[nCount] == '.' )     //  遇到点号
        {
            nDot++;
            if ( nDot > 3 )  //  点号数大于3
            {
                return FALSE;
            }
            else if ( nPos > 3 )
            {
                return FALSE;
            }
            else if ( nData > 255 ) //数值大于255
            {
                return FALSE;
            }
            else        //  已处理的字符串合法
            {
                nData = 0;
                nPos = 0;
            }
        }
        else            //  遇到非法字符
        {
            return FALSE;
        }
    }

    if ( nDot != 3 )
    {
        return FALSE;
    }

    // 检查最后一个数字是否合法
    if ( nData > 255 ) //数值大于255
    {
        return FALSE;
    }    

    return TRUE;
}

u32 CUIDataMgr::get_local_ip() 
{
    u32 ip;
    char hostname[128] = {0};
    int ret = gethostname(hostname, sizeof(hostname));
    if (ret == -1)
    {
        return -1;
    }
    struct hostent *hent;
    hent = gethostbyname(hostname);
    if (NULL == hent) 
    {
        return -1;
    }
    ip = ((struct in_addr*)hent->h_addr)->s_addr;
    return ip;
}

void CUIDataMgr::GetClearIP(CString& strIp)
{
    if (strIp == _T(""))
    {
        return;
    }
    int nIp[4] = {0};
    CString strClearIp = _T("");
    swscanf( strIp, _T("%d.%d.%d.%d"), &nIp[0],&nIp[1],&nIp[2],&nIp[3] );
    strClearIp.Format( _T("%d.%d.%d.%d"), nIp[0], nIp[1], nIp[2], nIp[3] );
    strIp = strClearIp;
}

void CUIDataMgr::GetBuildVersion(s8 achVersion[MAX_VER_LEN])
{
    s8 achMon[16] = {0};
    u32 byDay = 0;
    u32 byMonth = 0;
    u32 wYear = 0;
    s8 achFullDate[24] = {0};

    s8 achDate[32] = {0};
    sprintf(achDate, "%s", __DATE__);

    sscanf(achDate, "%s %d %d", achMon, &byDay, &wYear );

    if ( 0 == stricmp( achMon, "JAN") )
        byMonth = 1;
    else if ( 0 == stricmp( achMon, "FEB") )
        byMonth = 2;
    else if ( 0 == stricmp( achMon, "MAR") )
        byMonth = 3;
    else if ( 0 == stricmp( achMon, "APR") )
        byMonth = 4;
    else if ( 0 == stricmp( achMon, "MAY") )
        byMonth = 5;
    else if ( 0 == stricmp( achMon, "JUN") )
        byMonth = 6;
    else if ( 0 == stricmp( achMon, "JUL") )
        byMonth = 7;
    else if ( 0 == stricmp( achMon, "AUG") )
        byMonth = 8;
    else if ( 0 == stricmp( achMon, "SEP") )
        byMonth = 9;
    else if ( 0 == stricmp( achMon, "OCT") )
        byMonth = 10;
    else if ( 0 == stricmp( achMon, "NOV") )
        byMonth = 11;
    else if ( 0 == stricmp( achMon, "DEC") )
        byMonth = 12;
    else
        byMonth = 0;

    sprintf( achFullDate, "%04d%02d%02d", wYear, byMonth, byDay );

    _snprintf( achVersion, MAX_VER_LEN, "%s%s", RK100_VERSION_ID, achFullDate );

    achVersion[strlen(achVersion) + 1] = '\0';
}

BOOL CUIDataMgr::NetIpConflict( u32 dwIP, DWORD chIP )
{
    try
    {
        HRESULT hr; 
        ULONG  pulMac[6];
        ULONG ulLen; 
        //获取本机MAC地址,当前ip为0出现在断链时候或者获取不了ip时候
        if ( dwIP == 0 )
        {
            return FALSE;
        }
        ulLen = 6;
        hr = SendARP(dwIP, 0, pulMac, &ulLen);

        s8 achIP[16];
        u8 *pIP;
        pIP = (u8*)&dwIP;
        sprintf(achIP, "%u.%u.%u.%u", *(pIP+3), *(pIP+2), *(pIP+1), *pIP);
        // 
        //MAC 地址转换
        // 
        size_t i, j; 
        char* szMac = NULL;
        szMac = new char[30]; 
        if ( NULL == szMac )
        {
            return FALSE;
        }
        memset(szMac, 0, 30 );
        PBYTE pbHexMac = (PBYTE) pulMac;
        tstring strMACRem;
        ulLen = 6;
        for( i = 0, j = 0; i < ulLen - 1; ++ i )   
        { 
            j += sprintf( szMac + j, "%02X: ", pbHexMac[i] );
        } 

        sprintf(szMac + j, "%02X ", pbHexMac[i]); 
        //	printf("MAC address %s\n ", szMac);
        tstring strMAC = (CA2T)szMac;
        //获取网络上设下去ip的MAC地址
        if ( chIP == 0 )
        {
            return TRUE;
        }

        ulLen = 6;
        memset(pulMac, 0xff, sizeof(pulMac));
        hr = SendARP(chIP, 0, pulMac, &ulLen);
        // 
        //转换MAC地址 
        //
        ulLen = 6;
        pbHexMac = (PBYTE) pulMac;
        for( i = 0, j = 0; i < ulLen - 1; ++ i )   
        { 
            j += sprintf( szMac + j, "%02X: ", pbHexMac[i] );
        } 

        sprintf(szMac + j, "%02X ", pbHexMac[i]); 
        strMACRem = (CA2T)szMac;

        if( strMACRem != strMAC  && strMACRem != _T("FF: FF: FF: FF: FF: FF ") )
        {
            //MessageBox( "IP冲突" );

            delete []szMac;
            szMac = NULL;

            return TRUE;
        }
        else if ( strMAC == _T("CC: CC: CC: CC: CC: CC ") )
        {
            delete []szMac;
            szMac = NULL;

            return FALSE;
        }	

        delete []szMac;
        szMac = NULL;
    }
    catch ( ... )
    {
        return FALSE;
    }
    return FALSE;
}