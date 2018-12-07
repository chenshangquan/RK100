#pragma once

#include "unicode.h"
#include "kdvtype.h"
#include "libname.h"

#pragma warning( disable : 4786 )	// 标识符名称超过255字节
#pragma warning( disable : 4503 )
#pragma warning( disable : 4800 )

#include <objbase.h>
#include <zmouse.h>
#include "UIlib.h"
#include <ShlObj.h>
using namespace DuiLib;

#include <string>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

#include "AppWindow.h"
#include "structdef.h"
#include "InterfaceDef.h"
#include "ICommonOp.h"
using namespace AppFrame;

#include "DocManager.h"
#include "MsgManager.h"
#include "WindowManager.h"
#include "LogicManager.h"
#include "Logger.h"
#include "LogicFactory.h"
#include "ControlFactory.h"

void InitAppFrame( HINSTANCE hInstance );


void QuitAppFrame();


#pragma comment(lib,LIB_DUILIB)
#pragma comment(lib,LIB_APPFRAME)

