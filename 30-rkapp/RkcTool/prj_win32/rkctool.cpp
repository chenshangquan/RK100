
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

//抓捕异常信息
LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)  
{     
	// 创建Dump文件
	HANDLE hDumpFile = CreateFileW(L"Exception.dmp", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	// Dump信息
	MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
	dumpInfo.ExceptionPointers = pException;
	dumpInfo.ThreadId = GetCurrentThreadId();
	dumpInfo.ClientPointers = TRUE;
	// 写入Dump文件内容
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
	CloseHandle(hDumpFile);
	return EXCEPTION_EXECUTE_HANDLER;  
}

// CTpadApp initialization

BOOL CRkcToolApp::InitInstance()
{
    //只启动一次
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

    //异常处理
//     CString strFullPath = GetModuleFullPath();
//     strFullPath += EXCEPTION_FILE_PATH;
//     CExceptionCatch::LogToFile( (CT2A)strFullPath );
//     CExceptionCatch::Start(); 

	//抓捕异常文件
	::SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);  //cash代码

    //设置工作目录
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

    //创建rkctool session
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

    //   信号量存在，则程序已有一个实例运行   
    if (GetLastError()   ==   ERROR_ALREADY_EXISTS)   
    {  		
        //   关闭信号量句柄   
        CloseHandle(hSem);   
        //   寻找先前实例的主窗口   
        HWND   hWndPrevious = ::GetWindow(::GetDesktopWindow(),GW_CHILD);   
        while   (::IsWindow(hWndPrevious))   
        {   
            //   检查窗口是否有预设的标记?   
            //   有，则是我们寻找的主窗   
            if   (::GetProp(hWndPrevious, AfxGetApp()->m_pszAppName))   
            {    		 
                //BOOL re = ((CIPSetterDlg)(CWnd::FromHandle(hWndPrevious))).setDestroyFlagEx(FALSE);
                //(CWnd::FromHandle(hWndPrevious))->SendMessage(WM_DESTROY_FLAG,FALSE,TRUE); 

                //   主窗口已最小化，则恢复其大小   
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
            //   继续寻找下一个窗口   
            hWndPrevious   =   ::GetWindow(hWndPrevious,GW_HWNDNEXT); 
        }   
        //   前一实例已存在，但找不到其主窗   
        //   退出本实例   
        return   FALSE;   
    } 
    return TRUE;
}


//还原到主界面
void ResetHomeWindow()
{
    
}



API void help()
{
    PrtRkcMsg( "\nshowver: 显示版本和编译时间");
    PrtRkcMsg( "\nprt: 打印所有级别为3以上的消息");
    PrtRkcMsg( "\nprtlevel nLevel: 打印级别为nLevel的消息；消息级别 1-3，\n \
            1为级别最高的消息，该级别的消息对系统可能产生致命影响\n \
            2为一般级别的消息\n \
            3为最低级别消息 " );
    PrtRkcMsg( "\nprtid msgID: 打印消息号是msgID的消息");
    PrtRkcMsg( "\nprtrange MaxMsgID, MinMsgID: 打印消息号范围在 MinMsgID 和 MaxMsgID 之间的消息");
    PrtRkcMsg( "\nstopprt: 停止打印所有消息");
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