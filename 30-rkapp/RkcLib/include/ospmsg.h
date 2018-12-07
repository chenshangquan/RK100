

#ifndef _h_ospmsg_h__
#define _h_ospmsg_h__

#include "osp.h"

const int   KDV_MAXLEN_MESSAGE       =   65532; //1024*64,  ��Ϣ��󳤶�64K   


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
		CODEC_FLAG        = 0, //���ֽ� = 0��ʾδ���� = 1��ʾ�������� = 2��ʾxml����
		CODEC_HOMEPLACE   = 1,
		CODEC_User        = 2,
		CODEC_RESERVER3   = 3,
		CODEC_BODY		  = 4,

	};
	enum EmMsgCodecFlagStatus
	{
		CODEC_NONE         = 0,
		CODEC_XML_MARSHAL = 2,//���ݾɵ��ն�xml����2��ʼ
		CODEC_XML_COMPRESS,
	};
	enum EmMsgDataType
	{
		emRawData     = 0 ,//δ��������ԭʼ����
		emCodeData         //������������
	};
	//��Ϣ�Ƿ񾭹�����
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
	

	//������Ϣ
	int Post(u32 dstid,
		     u32 dstnode =0,	
			 u32 srciid  = MAKEIID(INVALID_APP, INVALID_INS), 
			 u32 srcnode = INVALID_NODE );


	//�����Ϣ��ָ��
	u8*	GetBody(){	return m_abyMsg+CODEC_BODY;}
	
	//�����Ϣ�峤��
	u16	GetBodyLen() {	return m_wBodyLen; 	}

	//�����Ϣָ��
	u8*	GetMsg(){	return m_abyMsg;}
	
	//�����Ϣ����
	u16	GetMsgLen() {	return m_wBodyLen+4; 	}

	//������Ϣ������
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

	//�����Ϣ������
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

	//��ȡ��Ϣ�ķ�����
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
