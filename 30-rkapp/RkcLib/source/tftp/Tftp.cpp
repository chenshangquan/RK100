#include "StdAfx.h"
#include "Tftp.h"
#include "rkcprintctrl.h"

HANDLE CTftpOp::s_hRead = NULL;

HANDLE CTftpOp::s_hWrite = NULL;
#if _DEBUG
	CString CTftpOp::s_StrTftpDir = _T(".\\tftp\\debug\\tftp.exe");
#else
	CString CTftpOp::s_StrTftpDir = _T(".\\tftp.exe");
#endif

CString CTftpOp::s_StrCmdLine = _T(" -producetest");

bool CTftpOp::Open()
{
	SECURITY_ATTRIBUTES sa;
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	if( !CreatePipe( &s_hRead, &s_hWrite, &sa, 0 ) )
	{
		PrtRkcMsg("TFTP：创建匿名管道失败!\n");
		return false;
	}
	PrtRkcMsg("TFTP：创建匿名管道成功!\n");
	STARTUPINFO sui;
	PROCESS_INFORMATION pi;
	ZeroMemory( &sui, sizeof(STARTUPINFO) );
	sui.cb = sizeof(STARTUPINFO);
	sui.dwFlags = STARTF_USESTDHANDLES;
	sui.hStdInput = s_hRead;
	sui.hStdOutput = s_hWrite;
	sui.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	s8 achCmdLine[CMD_LINE_LEN] = {0};
	strcpy( achCmdLine, s_StrCmdLine );
	if( !CreateProcess( s_StrTftpDir, achCmdLine, NULL, NULL, 
						TRUE, 0, NULL, NULL, &sui, &pi ) )
	{
		CloseHandle(s_hRead);
		CloseHandle(s_hWrite);
		s_hRead = NULL;
		s_hWrite = NULL;
		PrtRkcMsg("TFTP：子进程创建失败\n");
		return false;
	}
	else
	{
		PrtRkcMsg("TFTP：子进程创建成功!\n");
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	return true; 
	
}

bool CTftpOp::Close()
{
	if ( s_hWrite == NULL)
	{
		return false;
	}
	bool bRet = SendMsgToChildProc( EV_P_C_CLOSE );
	KillTftpProcess();
	if ( bRet)
	{
		if ( s_hRead )
		{
			CloseHandle(s_hRead);
			s_hRead = NULL;
		}
		if ( s_hWrite )
		{
			CloseHandle(s_hWrite);
			s_hWrite = NULL;
		}
		return true;
	}
	return false;
}

bool CTftpOp::SetTftpPath( const s8 *pchPath )
{
	if ( s_hWrite == NULL)
	{
		return false;
	}
	return SendMsgToChildProc( EV_P_C_CHNG_TFTP_PATH, pchPath );
}



bool CTftpOp::SetDhcpBootFile( const s8 *pchFileName )
{
	if ( s_hWrite == NULL)
	{
		return false;
	}
	return SendMsgToChildProc( EV_P_C_CHNG_DHCP_FILE, pchFileName );	
}

bool CTftpOp::SendMsgToChildProc( u32 dwMsgId, LPCTSTR pContent /*= NULL */ )
{
	TTftpCtrlMsg Msg;
	ZeroMemory(&Msg,sizeof(Msg));
	Msg.dwMsgId = dwMsgId;
	DWORD dwWrite = 0;
	if ( pContent != NULL )
	{
		memcpy( Msg.achContent, pContent, sizeof(Msg.achContent) );
	}
	return WriteFile( s_hWrite, &Msg, sizeof(Msg), &dwWrite, NULL );
}

bool CTftpOp::KillTftpProcess()
{
	CString strCmdLine = _T(" /f /im \"tftp.exe\"");
	CString strApp  = _T("\\taskkill.exe");
	s8 achAppPath[255] = {0};
	GetSystemDirectory(achAppPath, 255);
	strApp = achAppPath + strApp;
	PROCESS_INFORMATION pi;
	STARTUPINFO si = { sizeof(si) };
	if(CreateProcess(strApp, CT2A(strCmdLine), NULL, NULL, 
		FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi ))
	{
		//同步
		WaitForSingleObject( pi.hProcess, INFINITE );
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}	
	return true;
}


