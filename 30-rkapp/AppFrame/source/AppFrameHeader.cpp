#include "stdafx.h"
#include "AppFrameHeader.h"

void InitAppFrame( HINSTANCE hInstance )
{
	CPaintManagerUI::SetInstance(hInstance);

	// ��ӡ��Ϣ��
	if (ILogger::GetSingletonPtr() == 0) new CLogger();
	// ��ʼ��xml�ı�������
	if (IDocManager::GetSingletonPtr() == 0) new CDocManager();
	// ��ʼ���߼�����
	if (ILogicFactory::GetSingletonPtr() == 0) new CLogicFactory();
	// �߼�������
	if (ILogicManager::GetSingletonPtr() == 0) new CLogicManager();
	//�ؼ�����
	if (IControlFactory::GetSingletonPtr() == 0) new CControlFactory();
	// ��ʼ�����ڹ�����
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

