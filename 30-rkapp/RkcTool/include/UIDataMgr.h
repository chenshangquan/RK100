// UIDataMgr.h: interface for the CUIDataMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UIDATAMGR_H__27046F30_49B2_4F4B_8662_2133B7CC3BCC__INCLUDED_)
#define AFX_UIDATAMGR_H__27046F30_49B2_4F4B_8662_2133B7CC3BCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class CUIDataMgr  
{
public:
	virtual ~CUIDataMgr();

    static CUIDataMgr* GetSingleTon();
private:
	CUIDataMgr();

public:
    //打开文件 MFC 支持修改文件名
    CString SetFileName(CString filter, CString defaultDir, CString fileName, BOOL isOpen = TRUE/*是否打开(否则为保存)*/);
    void CloseFileDlg();

    //分割字符串
    void split(const string& s,vector<int>& sv,const char flag = ' ');

    //Ip地址是否有效
    BOOL32 IsValidIp( LPCSTR lptrIPStr );

    //获得本地IP
    u32 get_local_ip();

    //获得清理后的IP
    void GetClearIP(CString& strIp);

    //获取编译的软件版本号
    static void GetBuildVersion(s8 achVersion[]);

    //判断IP是否冲突
    BOOL NetIpConflict( u32 dwIP, DWORD chIP );
private:
    static CUIDataMgr *m_pThis;
};

#define UIDATAMGR CUIDataMgr::GetSingleTon()   
#endif // !defined(AFX_UIDATAMGR_H__27046F30_49B2_4F4B_8662_2133B7CC3BCC__INCLUDED_)
