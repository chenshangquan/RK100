
// tpad.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTpadApp:
// See tpad.cpp for the implementation of this class
//

class CRkcToolApp : public CWinApp
{
public:
	CRkcToolApp();

// Overrides
public:
	virtual BOOL InitInstance();
    virtual int ExitInstance();
// Implementation

	DECLARE_MESSAGE_MAP()

private:
    BOOL OnlyStartOne();
};

extern CRkcToolApp theApp;

///////////////////////¥Ú”°øÿ÷∆//////////////////////////////
//AIP void findeName( LPSTR name );

API void help();

API void prtlevel( u8 byLevel );

API void showver();

API void prt();

API void prtid( u32 msgID );

API void prtrange( u32 beginID, u32 endID );

API void stopprt();
/////////////////////////////////////////////////////////////////////////////
