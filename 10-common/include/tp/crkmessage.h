/******************************************************************************
模块名  : scoketmanager
文件名  : crkmessahe.h
功能    : 消息格式头文件
版本    ：1.0.0
******************************************************************************/
#ifndef __CRKMESSAGE_H__
#define __CRKMESSAGE_H__

#include "rk100_msg.h"

#define   RK_MAXLEN_MESSAGE          65535 //1024*64,  消息最大长度64K   

class CRkMessage
{
public:
    //消息体
    u8  m_abyMsg[RK_MAXLEN_MESSAGE];
    u16 m_wabyMsgLen;

    //获得消息体指针
    u8*	GetBody(){ return m_abyMsg;}
    //获得消息体长度
    u16	GetBodyLen() { return m_wabyMsgLen; }

    //设置消息体内容
    BOOL SetBody(const void* buf ,u16 len )
    { 
        if( len > (u16)(RK_MAXLEN_MESSAGE) )
            return FALSE;
        if( NULL == buf || 0 == len )
        {
            m_wabyMsgLen = 0;
            return TRUE;
        }
        memcpy(m_abyMsg ,buf ,len);
        m_wabyMsgLen = len;
        return TRUE;
    }
    //添加消息体内容
    BOOL CatBody(const void* buf ,u16 len )
    {
        if( len + m_wabyMsgLen > (u16)(RK_MAXLEN_MESSAGE) )
            return FALSE;

        memcpy( m_abyMsg + m_wabyMsgLen ,buf ,len);
        m_wabyMsgLen += len;
        return TRUE;
    }

};
#endif