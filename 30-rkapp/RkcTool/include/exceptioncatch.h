/****************************************************************************
模块名      ：崩溃信息捕获模块
文件名      ：exceptioncatch.h
相关文件    ：exceptioncatch.cpp
文件实现功能：崩溃捕获
作者        ：刘晓静
版本        ：V1.0 Copyright(C) 2009-2009 KDC, All rights reserved.
备注        ：只适用于Windows OS 
用法        ：1. 在你的cpp文件中include "exceptioncatch.h" 
              2. 在主线程入口调用CExceptionCatch::Start()加载崩溃信息捕获模块
              3. 崩溃文件在程序执行目录下的KDCException.txt文件，也可以自定义输出文件CExceptionCatch::LogToFile("文件全路径")
              4. 调用CExceptionCatch::Free()卸载崩溃信息模块
-----------------------------------------------------------------------------
修改记录：
日期      版本    修改人    修改内容 
2009/3/16 1.0     刘晓静    创建
2015/6/1          dyy       修改为Unicode适用
*****************************************************************************/

#if !defined(EXCEPTION_CATCH_H)
#define EXCEPTION_CATCH_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "stdafx.h"
#include "windows.h"


#include <imagehlp.h>
#include <stdio.h>
#include <assert.h>
//#include <fstream.h>

#pragma comment (lib, "imagehlp")

//崩溃输出文件路径
static char m_pszLogFile[MAX_PATH] = "";

//崩溃信息Exception Filter
static LPTOP_LEVEL_EXCEPTION_FILTER m_pPreExcepAddress;

//崩溃信息输出类
class CExceptionOutput  
{
public:
	CExceptionOutput()
	{
			memset (m_strFile, 0x00, sizeof (m_strFile));
			GetCurrentDirectoryA (sizeof (m_strFile), m_strFile);
			strcat (m_strFile, "\\Output.txt");
	}
	virtual ~CExceptionOutput(){}
	CExceptionOutput(char *pch)
	{
		assert (pch != NULL);
		strcpy (m_strFile, pch);
		m_strFile[sizeof (m_strFile) - 1] = NULL;
	}
	
	//设置输出文件名
	void SetFileName(LPCSTR pch)
	{
		assert (pch != NULL);
		strcpy (m_strFile, pch);
		m_strFile[sizeof (m_strFile) - 1] = NULL;
	}
	char *GetFileName()
	{
		return m_strFile;
	}
	
	//输出行
	void WriteString(LPCSTR pstr)
	{
		FILE *p = NULL;
		try
		{
			p = fopen(m_strFile, "a");
			if (p == NULL) return;
			
			fwrite(pstr, strlen (pstr) , 1, p);
			fclose(p);
		}
		catch (...) {
			fclose(p);
		}
	}
	
	//新增一行
	void NewLine()
	{
		FILE *p = NULL;
		char  pchNewLine[4] = {0};
		strcpy(pchNewLine, "\n");
		try
		{
	
			p = fopen(m_strFile, "a");
			if (p == NULL) return;
			
			fwrite(pchNewLine, strlen (pchNewLine) , 1, p);
			fclose(p);
		}
		catch (...) {
			fclose(p);
		}
	}
	
	//获得程序执行路径
	static CString GetModuleFullPath(void)
	{
		TCHAR achDllName[MAX_PATH] = _T("");
		CString csPath = _T("");
		
		GetModuleFileName(AfxGetInstanceHandle(), achDllName, sizeof (achDllName));
		
		csPath = achDllName;
		csPath = csPath.Left( csPath.ReverseFind('\\') + 1 );
		
		return csPath;
	}
private:
	char m_strFile[128];
};

//崩溃信息捕获类
class CExceptionCatch
{
public:
	static	void   Start()
	{
		if (NULL == m_pPreExcepAddress) 
		{
			SetErrorMode (SEM_NOGPFAULTERRORBOX);
			m_pPreExcepAddress = SetUnhandledExceptionFilter (CallBackDebugInfo);
		}
	}
	
	
	static	void   Free()
	{
		SetErrorMode (0);
		SetUnhandledExceptionFilter (m_pPreExcepAddress);
	}
	
	static	void   LogToFile(char *pszFile)
	{
		lstrcpynA (m_pszLogFile, pszFile, sizeof (m_pszLogFile));
	}
protected:
	static LONG WINAPI CallBackDebugInfo(EXCEPTION_POINTERS *pException)
	{
		// 得到异常的信息
		PEXCEPTION_RECORD pExcp = pException->ExceptionRecord;
		while (NULL != pExcp) 
		{
			DealExcep (pExcp);
			pExcp = pExcp->ExceptionRecord;
		}
		
		//打印堆栈信息
		ImgStackWalk (pException->ContextRecord);
		if (m_pPreExcepAddress) 
		{
			return m_pPreExcepAddress (pException);
		}
		return EXCEPTION_CONTINUE_SEARCH;
	}
	static void		   DealExcep(PEXCEPTION_RECORD pExcp)
	{
		char szFileInfo[3 * MAX_PATH], szExceptionInfo[MAX_PATH];
		memset (szExceptionInfo, 0x00, sizeof (szExceptionInfo));
		memset (szFileInfo, 0x00, sizeof (szFileInfo));
		
		// 打印提示头
		sprintf(szExceptionInfo, "======================== 崩溃信息 ==========================\n");
		lstrcpyA (szFileInfo, szExceptionInfo);
		
		// 获得当前时间
		SYSTEMTIME st;
		GetLocalTime(&st);  
		sprintf(szExceptionInfo, "崩溃时间： %4d/%.2d/%.2d %.2d:%.2d:%.2d\n",
			st.wYear, st.wMonth,  st.wDay,
			st.wHour, st.wMinute, st.wSecond);
		lstrcatA(szFileInfo, szExceptionInfo);
		
		lstrcatA(szFileInfo, "崩溃原因： ");
		
		// 判断异常原因
		switch (pExcp->ExceptionCode)
		{
		case STATUS_ACCESS_VIOLATION:
			sprintf(szExceptionInfo, "非法内存操作\n异常代码 = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
			sprintf(szExceptionInfo, "数组访问越界\n异常代码 = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_BREAKPOINT:
			sprintf(szExceptionInfo, "遇到breakpoint\n异常代码 = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_DATATYPE_MISALIGNMENT:
			sprintf(szExceptionInfo, "The thread tried to read or write data that is misaligned on hardware that does not provide alignment. For example, 16-bit values must be aligned on 2-byte boundaries; 32-bit values on 4-byte boundaries, and so on. \n异常代码 = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_FLT_DENORMAL_OPERAND:
			sprintf(szExceptionInfo, "One of the operands in a floating-point operation is denormal. A denormal value is one that is too small to represent as a standard floating-point value. \n异常代码 = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_FLT_DIVIDE_BY_ZERO: 
			sprintf(szExceptionInfo, "浮点除0. \n异常代码 = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_FLT_INEXACT_RESULT: 
			sprintf(szExceptionInfo, "The result of a floating-point operation cannot be represented exactly as a decimal fraction. \n异常代码 = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_FLT_INVALID_OPERATION:
			sprintf(szExceptionInfo, "This exception represents any floating-point exception not included in this list. \n异常代码 = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_FLT_OVERFLOW :
			sprintf(szExceptionInfo, "The exponent of a floating-point operation is greater than the magnitude allowed by the corresponding type. \n异常代码 = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_FLT_STACK_CHECK :
			sprintf(szExceptionInfo, "The stack overflowed or underflowed as the result of a floating-point operation. \n异常代码 = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_FLT_UNDERFLOW :
			sprintf(szExceptionInfo, "The exponent of a floating-point operation is less than the magnitude allowed by the corresponding type. \n异常代码 = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_ILLEGAL_INSTRUCTION :
			sprintf(szExceptionInfo, "The thread tried to execute an invalid instruction. \n异常代码 = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_IN_PAGE_ERROR :
			sprintf(szExceptionInfo, "The thread tried to access a page that was not present, and the system was unable to load the page. For example, this exception might occur if a network connection is lost while running a program over the network. \n异常代码 = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_INT_OVERFLOW: 
			sprintf(szExceptionInfo, "The result of an integer operation caused a carry out of the most significant bit of the result. \n异常代码 = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_INVALID_DISPOSITION :
			sprintf(szExceptionInfo, "(在异常处理过程中系统使用的代码)An exception handler returned an invalid disposition to the exception dispatcher. Programmers using a high-level language such as C should never encounter this exception. \n异常代码 = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_NONCONTINUABLE_EXCEPTION :
			sprintf(szExceptionInfo, "(不可持续异常,程序无法恢复执行,异常处理例程不应处理这个异常)The thread tried to continue execution after a noncontinuable exception occurred. \n异常代码 = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_PRIV_INSTRUCTION :
			sprintf(szExceptionInfo, "The thread tried to execute an instruction whose operation is not allowed in the current machine mode. \n异常代码 = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_SINGLE_STEP :
			sprintf(szExceptionInfo, "A trace trap or other single-instruction mechanism signaled that one instruction has been executed.	\n异常代码 = %8x\n", pExcp->ExceptionCode);
			break;
//		case STATUS_STACK_OVERFLOW:
/////		case EXCEPTION_STACK_OVERFLOW:
//			sprintf (szExceptionInfo, "堆栈溢出\n异常代码 = %8x\n", pExcp->ExceptionCode);
// 			break;
		case STATUS_INTEGER_DIVIDE_BY_ZERO:
			sprintf (szExceptionInfo, "整型除数为0\n异常代码 = %8x\n", pExcp->ExceptionCode);
			break;
		default:
			sprintf (szExceptionInfo, "其它异常\n异常代码 = %8x\n", pExcp->ExceptionCode);
			break;
		}
		
		// 异常地址
		lstrcatA (szFileInfo, szExceptionInfo);
		sprintf (szExceptionInfo, "\n异常地址 = 0x%.8x \n异常模块: ", pExcp->ExceptionAddress);
		lstrcatA (szFileInfo, szExceptionInfo);
		
		// 得到异常所在的module
		MEMORY_BASIC_INFORMATION mem;
		VirtualQuery (pExcp->ExceptionAddress, &mem, sizeof (MEMORY_BASIC_INFORMATION));
		GetModuleFileNameA ((HMODULE)mem.AllocationBase, szExceptionInfo, sizeof (szExceptionInfo));
		lstrcatA (szFileInfo, szExceptionInfo);
		
		// 定位异常的偏移位置(相对地址)
		PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)(mem.AllocationBase);
		PIMAGE_NT_HEADERS pNts = (PIMAGE_NT_HEADERS)((PBYTE)pDos + pDos->e_lfanew);
		PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION (pNts);
		
		// 获得偏移位置(相对地址)
		DWORD dRva = (DWORD)pExcp->ExceptionAddress - (DWORD)mem.AllocationBase;
		
		//  跟踪每个section.
		for (WORD wCnt = 0; wCnt < pNts->FileHeader.NumberOfSections; ++wCnt) 
		{
			DWORD dStart = pSection->VirtualAddress;
			DWORD dEnd = dStart + max (pSection->SizeOfRawData, pSection->Misc.VirtualSize);
			if (dRva >= dStart && dRva <= dEnd) 
			{
				sprintf (szExceptionInfo, "\nSection name: %s - offset(rva) : 0x%.8x\n", pSection->Name, dRva - dStart);
				lstrcatA (szFileInfo, szExceptionInfo);
				break;
			}
			++pSection;
		}
		
		// 如果没有设置文件名，赋默认值
		if (lstrlenA (m_pszLogFile) <= 0) 
		{
			strcpy(m_pszLogFile,  CExceptionOutput::GetModuleFullPath() + "KDCException.txt");
		} 
		
		// 输出打印到文件
		CExceptionOutput out(m_pszLogFile);
		out.WriteString (szFileInfo);
		out.NewLine();
		out.NewLine();
    }

	static void	ImgStackWalk(PCONTEXT pCon)
	{
		char szFileInfo[MAX_PATH * 2], szExceptionInfo[MAX_PATH];
		memset (szFileInfo, 0x00, sizeof (szFileInfo));
		
		// 先获取模块名字
		MEMORY_BASIC_INFORMATION mem;
		VirtualQuery((PVOID)pCon->Eip, &mem, sizeof (MEMORY_BASIC_INFORMATION));
		GetModuleFileNameA((HMODULE)mem.AllocationBase, szExceptionInfo, sizeof (szExceptionInfo));
		lstrcpyA(szFileInfo, szExceptionInfo);
		
		
		if (SymInitialize(GetCurrentProcess (), NULL, TRUE)) 
		{
			STACKFRAME sf;
			memset(&sf, 0x00, sizeof (STACKFRAME));
			
			// 初始化STACKFRAME（表示当前线程的调用堆栈中的一个函数调用）结构，只适用于Intel CPU
			sf.AddrPC.Offset       = pCon->Eip;
			sf.AddrPC.Mode         = AddrModeFlat;
			sf.AddrStack.Offset    = pCon->Esp;
			sf.AddrStack.Mode      = AddrModeFlat;
			sf.AddrFrame.Offset    = pCon->Ebp;
			sf.AddrFrame.Mode      = AddrModeFlat;
			
			
			while (true) 
			{
				if (!StackWalk (IMAGE_FILE_MACHINE_I386,
					GetCurrentProcess (),
					GetCurrentThread (),
					&sf,
					pCon,
					NULL,
					SymFunctionTableAccess,
					SymGetModuleBase,
					NULL))
				{
					break;
				}
				
				
				// 检查堆栈帧，不合理退出
				if ( 0 == sf.AddrFrame.Offset ) 
				{
					break;
				}
				
				// 申请image缓冲
				BYTE imgBuf[sizeof (IMAGEHLP_SYMBOL) + 512];
				PIMAGEHLP_SYMBOL pSymbol = reinterpret_cast <PIMAGEHLP_SYMBOL> (imgBuf);
				pSymbol->SizeOfStruct = sizeof (IMAGEHLP_SYMBOL);
				pSymbol->MaxNameLength = 512;
				DWORD dLen = 0;
				if (SymGetSymFromAddr (GetCurrentProcess(), sf.AddrPC.Offset,
					&dLen, pSymbol))
				{
					sprintf (szExceptionInfo, "\nname : %s - location: %x", pSymbol->Name, dLen);
					lstrcatA (szFileInfo, szExceptionInfo);
				}
			}
			SymCleanup (GetCurrentProcess ());
		}
		
		//如果没有设置文件名，赋默认值
		if (lstrlenA(m_pszLogFile) <= 0) 
		{
			strcpy(m_pszLogFile, CExceptionOutput::GetModuleFullPath() + "KDCException.txt");
		} 
		
		//输出到文件
		CExceptionOutput out(m_pszLogFile);
		out.WriteString("---------------------- Trips of Stack ----------------------\n");
		out.WriteString(szFileInfo);
		out.NewLine();
		out.NewLine();
	}
protected:
	///static	LPTOP_LEVEL_EXCEPTION_FILTER m_pPreExcepAddress;
	///static	char	m_pszLogFile[MAX_PATH];
	
};

#endif // !defined(EXCEPTION_CATCH_H)
