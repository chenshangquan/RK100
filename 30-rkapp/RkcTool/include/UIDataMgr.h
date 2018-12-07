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
    //���ļ� MFC ֧���޸��ļ���
    CString SetFileName(CString filter, CString defaultDir, CString fileName, BOOL isOpen = TRUE/*�Ƿ��(����Ϊ����)*/);
    void CloseFileDlg();

    //�ָ��ַ���
    void split(const string& s,vector<int>& sv,const char flag = ' ');

    //Ip��ַ�Ƿ���Ч
    BOOL32 IsValidIp( LPCSTR lptrIPStr );

    //��ñ���IP
    u32 get_local_ip();

    //���������IP
    void GetClearIP(CString& strIp);

    //��ȡ���������汾��
    static void GetBuildVersion(s8 achVersion[]);

    //�ж�IP�Ƿ��ͻ
    BOOL NetIpConflict( u32 dwIP, DWORD chIP );
private:
    static CUIDataMgr *m_pThis;
};

#define UIDATAMGR CUIDataMgr::GetSingleTon()   
#endif // !defined(AFX_UIDATAMGR_H__27046F30_49B2_4F4B_8662_2133B7CC3BCC__INCLUDED_)
