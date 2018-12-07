#pragma once

#include "rkcSessionCtrlIF.h"

class CRckLib  
{

public:
	CRckLib();
	virtual ~CRckLib();

	/*功能	创建实现了接口CCnsSessionCtrlIF的对象
	参数	ppICnt	[out]成功返回CCnsSessionCtrlIF接口,失败返回NULL
	返回值	成功返回0,失败返回非0错误码
	说明	接口使用完成后,调用DestroyInstance方法销毁对象*/
	static u16 CreateSession(CRkcSessionCtrlIF **ppICnt);
	/*功能	销毁实现了接口CCnsSessionCtrlIF的对象
	参数	ppICnt	[in, out]接口CCnsSessionCtrlIF,成功后返回NULL
	返回值	成功返回0,失败返回非0错误码
	说明	只能销毁由CreateInstance方法创建的对象*/
	static u16 DestroySession(CRkcSessionCtrlIF **ppICnt);

};

