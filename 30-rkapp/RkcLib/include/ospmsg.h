

#ifndef _h_ospmsg_h__
#define _h_ospmsg_h__

#include "osp.h"

const int   KDV_MAXLEN_MESSAGE       =   65532; //1024*64,  消息最大长度64K   


struct TOspMsg
{
protected:
	u16 m_wEvent;
	u16 m_wBodyLen;
	u32 m_dwSrcIId;
	u32 m_dwSrcNode;

	u8  m_abyMsg[KDV_MAXLEN_MESSAGE+4];
	s32 m_nXMLIndex;

	TOspMsg()
	{
		memset(this,0,sizeof(TOspMsg));
		m_nXMLIndex = -1;
	}
};

class COspMsg : public TOspMsg
{
protected:
	enum EmMsgCodeIndex
	{
		CODEC_FLAG        = 0, //该字节 = 0表示未编码 = 1表示编码数据 = 2表示xml编码
		CODEC_HOMEPLACE   = 1,
		CODEC_User        = 2,
		CODEC_RESERVER3   = 3,
		CODEC_BODY		  = 4,

	};
	enum EmMsgCodecFlagStatus
	{
		CODEC_NONE         = 0,
		CODEC_XML_MARSHAL = 2,//兼容旧的终端xml，从2开始
		CODEC_XML_COMPRESS,
	};
	enum EmMsgDataType
	{
		emRawData     = 0 ,//未经编解码的原始数据
		emCodeData         //经编解码的数据
	};
	//消息是否经过编码
	u8 IsMsgCoder()
	{
		return m_abyMsg[0];
	}

public:
	COspMsg(){};
	COspMsg(const CMessage* ptMsg )
	{
		m_dwSrcIId  = ptMsg->srcid;
		m_dwSrcNode = ptMsg->srcnode;
        m_wEvent = ptMsg->event;
        m_wBodyLen = ptMsg->length;
        memcpy(m_abyMsg+CODEC_BODY ,ptMsg->content ,ptMsg->length);
	}

	COspMsg(u16 wEvent ,void* buf ,int len )
	{
	}
	

	//发送消息
	int Post(u32 dstid,
		     u32 dstnode =0,	
			 u32 srciid  = MAKEIID(INVALID_APP, INVALID_INS), 
			 u32 srcnode = INVALID_NODE );


	//获得消息体指针
	u8*	GetBody(){	return m_abyMsg+CODEC_BODY;}
	
	//获得消息体长度
	u16	GetBodyLen() {	return m_wBodyLen; 	}

	//获得消息指针
	u8*	GetMsg(){	return m_abyMsg;}
	
	//获得消息长度
	u16	GetMsgLen() {	return m_wBodyLen+4; 	}

	//设置消息体内容
	BOOL SetBody(const void* buf ,u16 len )
	{ 
		if( len > (u16)(KDV_MAXLEN_MESSAGE) )
			return FALSE;
		if( NULL == buf || 0 == len )
		{
			m_wBodyLen = 0;
			return TRUE;
		}
		memcpy(m_abyMsg+CODEC_BODY ,buf ,len);
		m_wBodyLen = len;
		return TRUE;
	}

	//添加消息体内容
	BOOL CatBody(const void* buf ,u16 len )
	{
		if( len + m_wBodyLen > (u16)(KDV_MAXLEN_MESSAGE) )
			return FALSE;

		memcpy( m_abyMsg +CODEC_BODY +m_wBodyLen ,buf ,len);
		m_wBodyLen += len;
		return TRUE;

	}

	void SetEvent(u16 event ) { m_wEvent = event ;}
	u16  GetEvent() { return m_wEvent; }


	u32 GetSrcIId(){ return m_dwSrcIId; }
	u32 GetSrcNode(){ return m_dwSrcNode; }

	//获取消息的发起者
	u8   GetHomeplace()
	{
		return m_abyMsg[CODEC_HOMEPLACE];
	}

	void SetHomeplace( u8 byNode )
	{
		m_abyMsg[CODEC_HOMEPLACE] = byNode;
	}

	u8   GetUserData()
	{
		return m_abyMsg[CODEC_User];
	}

	void   SetUserData(u8 byData)
	{
		m_abyMsg[CODEC_User] = byData;
	}
	
	u8   GetUserData2()
	{
		return m_abyMsg[CODEC_RESERVER3];
	}
	
	void   SetUserData2(u8 byData)
	{
		m_abyMsg[CODEC_RESERVER3] = byData;
	}
protected:
    void  DisplayMsgStream(u32 srcid , u32 dstid);
};

#endif//!_h_ospmsg_h__
