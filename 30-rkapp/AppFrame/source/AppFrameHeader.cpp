#include "stdafx.h"
#include "AppFrameHeader.h"

void InitAppFrame( HINSTANCE hInstance )
{
	CPaintManagerUI::SetInstance(hInstance);

	// 打印信息类
	if (ILogger::GetSingletonPtr() == 0) new CLogger();
	// 初始化xml文本管理器
	if (IDocManager::GetSingletonPtr() == 0) new CDocManager();
	// 初始化逻辑工厂
	if (ILogicFactory::GetSingletonPtr() == 0) new CLogicFactory();
	// 逻辑管理器
	if (ILogicManager::GetSingletonPtr() == 0) new CLogicManager();
	//控件工厂
	if (IControlFactory::GetSingletonPtr() == 0) new CControlFactory();
	// 初始化窗口管理器
	if (IWindowManager::GetSingletonPtr() == 0) new CWindowManager();
}

void QuitAppFrame()
{
	delete IWindowManager::GetSingletonPtr();
	delete ILogger::GetSingletonPtr();
	delete IControlFactory::GetSingletonPtr();
	delete ILogicManager::GetSingletonPtr();
	delete ILogicFactory::GetSingletonPtr();
	delete IDocManager::GetSingletonPtr();
}

