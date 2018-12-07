/****************************************************************************
ģ����      ��������Ϣ����ģ��
�ļ���      ��exceptioncatch.h
����ļ�    ��exceptioncatch.cpp
�ļ�ʵ�ֹ��ܣ���������
����        ��������
�汾        ��V1.0 Copyright(C) 2009-2009 KDC, All rights reserved.
��ע        ��ֻ������Windows OS 
�÷�        ��1. �����cpp�ļ���include "exceptioncatch.h" 
              2. �����߳���ڵ���CExceptionCatch::Start()���ر�����Ϣ����ģ��
              3. �����ļ��ڳ���ִ��Ŀ¼�µ�KDCException.txt�ļ���Ҳ�����Զ�������ļ�CExceptionCatch::LogToFile("�ļ�ȫ·��")
              4. ����CExceptionCatch::Free()ж�ر�����Ϣģ��
-----------------------------------------------------------------------------
�޸ļ�¼��
����      �汾    �޸���    �޸����� 
2009/3/16 1.0     ������    ����
2015/6/1          dyy       �޸�ΪUnicode����
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

//��������ļ�·��
static char m_pszLogFile[MAX_PATH] = "";

//������ϢException Filter
static LPTOP_LEVEL_EXCEPTION_FILTER m_pPreExcepAddress;

//������Ϣ�����
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
	
	//��������ļ���
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
	
	//�����
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
	
	//����һ��
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
	
	//��ó���ִ��·��
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

//������Ϣ������
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
		// �õ��쳣����Ϣ
		PEXCEPTION_RECORD pExcp = pException->ExceptionRecord;
		while (NULL != pExcp) 
		{
			DealExcep (pExcp);
			pExcp = pExcp->ExceptionRecord;
		}
		
		//��ӡ��ջ��Ϣ
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
		
		// ��ӡ��ʾͷ
		sprintf(szExceptionInfo, "======================== ������Ϣ ==========================\n");
		lstrcpyA (szFileInfo, szExceptionInfo);
		
		// ��õ�ǰʱ��
		SYSTEMTIME st;
		GetLocalTime(&st);  
		sprintf(szExceptionInfo, "����ʱ�䣺 %4d/%.2d/%.2d %.2d:%.2d:%.2d\n",
			st.wYear, st.wMonth,  st.wDay,
			st.wHour, st.wMinute, st.wSecond);
		lstrcatA(szFileInfo, szExceptionInfo);
		
		lstrcatA(szFileInfo, "����ԭ�� ");
		
		// �ж��쳣ԭ��
		switch (pExcp->ExceptionCode)
		{
		case STATUS_ACCESS_VIOLATION:
			sprintf(szExceptionInfo, "�Ƿ��ڴ����\n�쳣���� = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
			sprintf(szExceptionInfo, "�������Խ��\n�쳣���� = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_BREAKPOINT:
			sprintf(szExceptionInfo, "����breakpoint\n�쳣���� = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_DATATYPE_MISALIGNMENT:
			sprintf(szExceptionInfo, "The thread tried to read or write data that is misaligned on hardware that does not provide alignment. For example, 16-bit values must be aligned on 2-byte boundaries; 32-bit values on 4-byte boundaries, and so on. \n�쳣���� = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_FLT_DENORMAL_OPERAND:
			sprintf(szExceptionInfo, "One of the operands in a floating-point operation is denormal. A denormal value is one that is too small to represent as a standard floating-point value. \n�쳣���� = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_FLT_DIVIDE_BY_ZERO: 
			sprintf(szExceptionInfo, "�����0. \n�쳣���� = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_FLT_INEXACT_RESULT: 
			sprintf(szExceptionInfo, "The result of a floating-point operation cannot be represented exactly as a decimal fraction. \n�쳣���� = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_FLT_INVALID_OPERATION:
			sprintf(szExceptionInfo, "This exception represents any floating-point exception not included in this list. \n�쳣���� = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_FLT_OVERFLOW :
			sprintf(szExceptionInfo, "The exponent of a floating-point operation is greater than the magnitude allowed by the corresponding type. \n�쳣���� = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_FLT_STACK_CHECK :
			sprintf(szExceptionInfo, "The stack overflowed or underflowed as the result of a floating-point operation. \n�쳣���� = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_FLT_UNDERFLOW :
			sprintf(szExceptionInfo, "The exponent of a floating-point operation is less than the magnitude allowed by the corresponding type. \n�쳣���� = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_ILLEGAL_INSTRUCTION :
			sprintf(szExceptionInfo, "The thread tried to execute an invalid instruction. \n�쳣���� = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_IN_PAGE_ERROR :
			sprintf(szExceptionInfo, "The thread tried to access a page that was not present, and the system was unable to load the page. For example, this exception might occur if a network connection is lost while running a program over the network. \n�쳣���� = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_INT_OVERFLOW: 
			sprintf(szExceptionInfo, "The result of an integer operation caused a carry out of the most significant bit of the result. \n�쳣���� = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_INVALID_DISPOSITION :
			sprintf(szExceptionInfo, "(���쳣���������ϵͳʹ�õĴ���)An exception handler returned an invalid disposition to the exception dispatcher. Programmers using a high-level language such as C should never encounter this exception. \n�쳣���� = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_NONCONTINUABLE_EXCEPTION :
			sprintf(szExceptionInfo, "(���ɳ����쳣,�����޷��ָ�ִ��,�쳣�������̲�Ӧ��������쳣)The thread tried to continue execution after a noncontinuable exception occurred. \n�쳣���� = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_PRIV_INSTRUCTION :
			sprintf(szExceptionInfo, "The thread tried to execute an instruction whose operation is not allowed in the current machine mode. \n�쳣���� = %8x\n", pExcp->ExceptionCode);
			break;
		case EXCEPTION_SINGLE_STEP :
			sprintf(szExceptionInfo, "A trace trap or other single-instruction mechanism signaled that one instruction has been executed.	\n�쳣���� = %8x\n", pExcp->ExceptionCode);
			break;
//		case STATUS_STACK_OVERFLOW:
/////		case EXCEPTION_STACK_OVERFLOW:
//			sprintf (szExceptionInfo, "��ջ���\n�쳣���� = %8x\n", pExcp->ExceptionCode);
// 			break;
		case STATUS_INTEGER_DIVIDE_BY_ZERO:
			sprintf (szExceptionInfo, "���ͳ���Ϊ0\n�쳣���� = %8x\n", pExcp->ExceptionCode);
			break;
		default:
			sprintf (szExceptionInfo, "�����쳣\n�쳣���� = %8x\n", pExcp->ExceptionCode);
			break;
		}
		
		// �쳣��ַ
		lstrcatA (szFileInfo, szExceptionInfo);
		sprintf (szExceptionInfo, "\n�쳣��ַ = 0x%.8x \n�쳣ģ��: ", pExcp->ExceptionAddress);
		lstrcatA (szFileInfo, szExceptionInfo);
		
		// �õ��쳣���ڵ�module
		MEMORY_BASIC_INFORMATION mem;
		VirtualQuery (pExcp->ExceptionAddress, &mem, sizeof (MEMORY_BASIC_INFORMATION));
		GetModuleFileNameA ((HMODULE)mem.AllocationBase, szExceptionInfo, sizeof (szExceptionInfo));
		lstrcatA (szFileInfo, szExceptionInfo);
		
		// ��λ�쳣��ƫ��λ��(��Ե�ַ)
		PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)(mem.AllocationBase);
		PIMAGE_NT_HEADERS pNts = (PIMAGE_NT_HEADERS)((PBYTE)pDos + pDos->e_lfanew);
		PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION (pNts);
		
		// ���ƫ��λ��(��Ե�ַ)
		DWORD dRva = (DWORD)pExcp->ExceptionAddress - (DWORD)mem.AllocationBase;
		
		//  ����ÿ��section.
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
		
		// ���û�������ļ�������Ĭ��ֵ
		if (lstrlenA (m_pszLogFile) <= 0) 
		{
			strcpy(m_pszLogFile,  CExceptionOutput::GetModuleFullPath() + "KDCException.txt");
		} 
		
		// �����ӡ���ļ�
		CExceptionOutput out(m_pszLogFile);
		out.WriteString (szFileInfo);
		out.NewLine();
		out.NewLine();
    }

	static void	ImgStackWalk(PCONTEXT pCon)
	{
		char szFileInfo[MAX_PATH * 2], szExceptionInfo[MAX_PATH];
		memset (szFileInfo, 0x00, sizeof (szFileInfo));
		
		// �Ȼ�ȡģ������
		MEMORY_BASIC_INFORMATION mem;
		VirtualQuery((PVOID)pCon->Eip, &mem, sizeof (MEMORY_BASIC_INFORMATION));
		GetModuleFileNameA((HMODULE)mem.AllocationBase, szExceptionInfo, sizeof (szExceptionInfo));
		lstrcpyA(szFileInfo, szExceptionInfo);
		
		
		if (SymInitialize(GetCurrentProcess (), NULL, TRUE)) 
		{
			STACKFRAME sf;
			memset(&sf, 0x00, sizeof (STACKFRAME));
			
			// ��ʼ��STACKFRAME����ʾ��ǰ�̵߳ĵ��ö�ջ�е�һ���������ã��ṹ��ֻ������Intel CPU
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
				
				
				// ����ջ֡���������˳�
				if ( 0 == sf.AddrFrame.Offset ) 
				{
					break;
				}
				
				// ����image����
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
		
		//���û�������ļ�������Ĭ��ֵ
		if (lstrlenA(m_pszLogFile) <= 0) 
		{
			strcpy(m_pszLogFile, CExceptionOutput::GetModuleFullPath() + "KDCException.txt");
		} 
		
		//������ļ�
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
