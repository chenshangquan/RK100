#include "StdAfx.h"
#include "InterfaceDef.h"

template<> IWindowManager* CSingleton<IWindowManager>::m_psSingleton = 0;
template<> IMsgManager* CSingleton<IMsgManager>::m_psSingleton = 0;
template<> IControlFactory* CSingleton<IControlFactory>::m_psSingleton = 0;
template<> IDocManager* CSingleton<IDocManager>::m_psSingleton = 0;
template<> ILogicManager* CSingleton<ILogicManager>::m_psSingleton = 0;
template<> ILogger* CSingleton<ILogger>::m_psSingleton = 0;
template<> IUserDataMngr* CSingleton<IUserDataMngr>::m_psSingleton = 0;
template<> ILogicFactory* CSingleton<ILogicFactory>::m_psSingleton = 0;

