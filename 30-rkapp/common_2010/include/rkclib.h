#pragma once

#include "rkcSessionCtrlIF.h"

class CRckLib  
{

public:
	CRckLib();
	virtual ~CRckLib();

	/*����	����ʵ���˽ӿ�CCnsSessionCtrlIF�Ķ���
	����	ppICnt	[out]�ɹ�����CCnsSessionCtrlIF�ӿ�,ʧ�ܷ���NULL
	����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
	˵��	�ӿ�ʹ����ɺ�,����DestroyInstance�������ٶ���*/
	static u16 CreateSession(CRkcSessionCtrlIF **ppICnt);
	/*����	����ʵ���˽ӿ�CCnsSessionCtrlIF�Ķ���
	����	ppICnt	[in, out]�ӿ�CCnsSessionCtrlIF,�ɹ��󷵻�NULL
	����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
	˵��	ֻ��������CreateInstance���������Ķ���*/
	static u16 DestroySession(CRkcSessionCtrlIF **ppICnt);

};

