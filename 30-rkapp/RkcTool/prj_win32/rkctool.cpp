
// tpad.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "rkctool.h"
#include "rkctoolDlg.h"
#include "exceptioncatch.h"
#include <imagehlp.h>
#pragma comment(lib, "DbgHelp.lib")
#include "rkcprintctrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define EXCEPTION_FILE_PATH _T("exception.log")

void ResetHomeWindow();

// CTpadApp

BEGIN_MESSAGE_MAP(CRkcToolApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTpadApp construction

CRkcToolApp::CRkcToolApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTpadApp object

CRkcToolApp theApp;

//ץ���쳣��Ϣ
LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)  
{     
	// ����Dump�ļ�
	HANDLE hDumpFile = CreateFileW(L"Exception.dmp", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	// Dump��Ϣ
	MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
	dumpInfo.ExceptionPointers = pException;
	dumpInfo.ThreadId = GetCurrentThreadId();
	dumpInfo.ClientPointers = TRUE;
	// д��Dump�ļ�����
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
	CloseHandle(hDumpFile);
	return EXCEPTION_EXECUTE_HANDLER;  
}

// CTpadApp initialization

BOOL CRkcToolApp::InitInstance()
{
    //ֻ����һ��
    if ( !OnlyStartOne() )
    {   
        UINT uExitCode = 0;
        ExitProcess( uExitCode );
        return FALSE;
    }

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

    //�쳣����
//     CString strFullPath = GetModuleFullPath();
//     strFullPath += EXCEPTION_FILE_PATH;
//     CExceptionCatch::LogToFile( (CT2A)strFullPath );
//     CExceptionCatch::Start(); 

	//ץ���쳣�ļ�
	::SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);  //cash����

    //���ù���Ŀ¼
#ifndef _DEBUG 
    char chpath[MAX_PATH];  
    GetModuleFileNameA(NULL,(LPSTR)chpath,sizeof(chpath));  
    std::string strPath = (std::string)chpath;
    int pos = strPath.find_last_of('\\', strPath.length());
    strPath = strPath.substr(0, pos); 
    SetCurrentDirectoryA(strPath.c_str());
#endif

    InitAppFrame(m_hInstance);

    new CSystem(_T("system.xml"));

    //����rkctool session
    CRkcComInterface->CreateSession();

    CSystem::GetSingletonPtr()->Launch();

    return TRUE;


	CRkcToolDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CRkcToolApp::ExitInstance()
{
    CExceptionCatch::Free();

    QuitAppFrame();

    ::RemoveProp( m_pMainWnd->GetSafeHwnd(), AfxGetApp()->m_pszAppName );

    return CWinApp::ExitInstance();
}


BOOL CRkcToolApp::OnlyStartOne()
{
    HANDLE  hSem  =  CreateSemaphore(NULL,  1,  1, AfxGetApp()->m_pszAppName);   

    //   �ź������ڣ����������һ��ʵ������   
    if (GetLastError()   ==   ERROR_ALREADY_EXISTS)   
    {  		
        //   �ر��ź������   
        CloseHandle(hSem);   
        //   Ѱ����ǰʵ����������   
        HWND   hWndPrevious = ::GetWindow(::GetDesktopWindow(),GW_CHILD);   
        while   (::IsWindow(hWndPrevious))   
        {   
            //   ��鴰���Ƿ���Ԥ��ı��?   
            //   �У���������Ѱ�ҵ�����   
            if   (::GetProp(hWndPrevious, AfxGetApp()->m_pszAppName))   
            {    		 
                //BOOL re = ((CIPSetterDlg)(CWnd::FromHandle(hWndPrevious))).setDestroyFlagEx(FALSE);
                //(CWnd::FromHandle(hWndPrevious))->SendMessage(WM_DESTROY_FLAG,FALSE,TRUE); 

                //   ����������С������ָ����С   
                if   (::IsIconic(hWndPrevious)) 				
                    ::ShowWindow(hWndPrevious,SW_RESTORE);   

                HWND hdl = GetForegroundWindow();
                if (hWndPrevious !=  hdl )
                {   					
                    ::ShowWindow(hWndPrevious,SW_RESTORE); 
                    ::SetForegroundWindow(hWndPrevious);
                }

                return   FALSE;   
            }   
            //   ����Ѱ����һ������   
            hWndPrevious   =   ::GetWindow(hWndPrevious,GW_HWNDNEXT); 
        }   
        //   ǰһʵ���Ѵ��ڣ����Ҳ���������   
        //   �˳���ʵ��   
        return   FALSE;   
    } 
    return TRUE;
}


//��ԭ��������
void ResetHomeWindow()
{
    
}



API void help()
{
    PrtRkcMsg( "\nshowver: ��ʾ�汾�ͱ���ʱ��");
    PrtRkcMsg( "\nprt: ��ӡ���м���Ϊ3���ϵ���Ϣ");
    PrtRkcMsg( "\nprtlevel nLevel: ��ӡ����ΪnLevel����Ϣ����Ϣ���� 1-3��\n \
            1Ϊ������ߵ���Ϣ���ü������Ϣ��ϵͳ���ܲ�������Ӱ��\n \
            2Ϊһ�㼶�����Ϣ\n \
            3Ϊ��ͼ�����Ϣ " );
    PrtRkcMsg( "\nprtid msgID: ��ӡ��Ϣ����msgID����Ϣ");
    PrtRkcMsg( "\nprtrange MaxMsgID, MinMsgID: ��ӡ��Ϣ�ŷ�Χ�� MinMsgID �� MaxMsgID ֮�����Ϣ");
    PrtRkcMsg( "\nstopprt: ֹͣ��ӡ������Ϣ");
}

API void showver()
{   
    s8 achVersion[MAX_DEVICEVER_LEN] = {0};
    CUIDataMgr::GetBuildVersion(achVersion);
    PrtRkcMsg( "RK100  version: V%s  \n", achVersion ); 
    PrtRkcMsg( "compile time: %s %s", __DATE__, __TIME__ );
}

API void prt()
{
    CRkcPrintCtrl::GetPrintCtrl()->PrintAllMsg();
}

API void prtlevel( u8 byLevel )
{
    CRkcPrintCtrl::GetPrintCtrl()->PrintMsgLevel(byLevel);
}

API void prtid( u32 msgID )
{
    CRkcPrintCtrl::GetPrintCtrl()->SetPrintMsgID( msgID );
}

API void prtrange( u32 beginID, u32 endID )
{ 
    CRkcPrintCtrl::GetPrintCtrl()->SetPrintMsgRange( beginID, endID ); 
}

API void stopprt()
{
    CRkcPrintCtrl::GetPrintCtrl()->StopPrint();
}