// rkcstruct.h: interface for the cmsstruct class.
//
//////////////////////////////////////////////////////////////////////
#ifndef _h_rkcstruct_h__
#define _h_rkcstruct_h__

#include "rkcconst.h"
#include "crkmessage.h"

//µÇÂ¼ÐÅÏ¢
typedef struct tagLoginInfo
{
	s8      m_achIp[MAX_IP_LENGTH+1];
	u16     m_wPort;
	s8      m_achName[MAX_ALIAS_LENGTH+1];
	s8      m_achPswd[MAX_ALIAS_LENGTH+1];

	tagLoginInfo()
	{
		memset( this, 0, sizeof(tagLoginInfo) );
	}
}TLoginInfo;


#endif 
