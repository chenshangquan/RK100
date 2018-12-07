#include "StdAfx.h"
#include "DragInterface.h"
namespace DuiLib{
template<> IDragDataMgr* DuiSingleton<IDragDataMgr>::ms_pSingleton = 0;
template<> IDragController* DuiSingleton<IDragController>::ms_pSingleton = 0;

}