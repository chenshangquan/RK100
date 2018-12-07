#ifndef _h_eventstruct_url_h__
#define _h_eventstruct_url_h__

#include "urlstruct.h"

//������鴫�νṹ��
typedef struct tagJoinConf
{
    s8                      m_achConf_Id[TP_MAX_ID_LEN+1];                  //�����
    s8                      m_achAccount[TP_MAX_NAME_LEN+1];
    u8                      m_wAccount_Type;
    u16                     m_wBitrate;
    u8                      m_wProtocol;
    u8                      m_wForced_call;
    
public:
    tagJoinConf()
    { 
        memset( this, 0, sizeof(struct tagJoinConf) ); 
    }
}TJoinConf;
//����ѡ�����νṹ��
typedef struct tagSelViewMid
{
    s8                      m_achConf_Id[TP_MAX_ID_LEN+1];                     //����id
    u16                     m_wMode;                                //ѡ��ģʽ1-��Ƶ��2-��Ƶ
    u16                     m_wSrcType;                             //ѡ��Դ����
    s8                      m_achSrcMt_Id[TP_MAX_ID_LEN+1];                    //ѡ��ԴID
    s8                      m_achDstMt_Id[TP_MAX_ID_LEN+1];                    //Ŀ���ն˺�

public:
    tagSelViewMid()
    { 
        Clear();
    }

    void Clear()
    {  
        memset( this, 0, sizeof(struct tagSelViewMid) );  
    }

    bool IsClear()
    {
        return (strcmp(m_achConf_Id,"") == 0    && 
                strcmp(m_achSrcMt_Id,"") == 0   && 
                strcmp(m_achDstMt_Id,"") == 0   && 
                m_wMode == 0                    && 
                m_wSrcType == 0);
    }

}TSelViewMid;
//��ؿ������νṹ��
typedef struct tagMonitorStart
{
    s8                      m_achConf_Id[TP_MAX_ID_LEN+1];                     //����id
    u16                     m_wMode;                                //���ģʽ 0-��Ƶ 1-��Ƶ
    u16                     m_wType;                                //������� 1-�ն� 2-����ϳ� 3-����
    s8                      m_achSrcMt_Id[TP_MAX_ID_LEN+1];                    //����ն�ID typeΪ�ն�ʱ����
    u16                     m_wVedioFormat;                         //����Ƶ��ʽ 1-MPEG 2-H.261 3-H.263 4-H.264_HP 5-H.264_BP 6-H.265
    u16                     m_wVedioResolution;                     //����Ƶ�ֱ��� 1-QCIF 2-CIF 3-4CIF 12-720P 13-1080P 14-WCIF 15-W4CIF 16-4k
    u16                     m_wFrame;                               //����Ƶ֡��
    u16                     m_wBitrate;                             //����Ƶ����
    u16                     m_wAudioFormat;                         //����Ƶ���� 1-MP3 2-G722.1.C 3-G719 4-G.711(Alaw) 5-G.711(Ulaw) 6-G.721 7-G.722 8-G.7231 9-G.728 10-G.729 11-G.7221 12-OPUS 13-MPEG-4 AAC LC 14-MPEG-4 AAC LD;
    u16                     m_wChn_num;                             //�������� 1-������ 2-˫����
    s8                      m_achIP[TP_MAX_IP_LEN+1];                          //Ŀ��ip��ַ
    u16                     m_wPort;                                //Ŀ��rtp�˿�
public:
    tagMonitorStart()
    { 
        memset( this, 0, sizeof(struct tagMonitorStart) ); 
    }
}TMonitorStart;
//��ؽ������νṹ�� //�������ؼ�֡���νṹ��
typedef struct tagKeyFrame
{
    s8                      m_achConf_Id[TP_MAX_ID_LEN+1];                     //����id
    u16                     m_wPort;                                //�˿ں�
    s8                      m_achIP[TP_MAX_IP_LEN+1];                          //IP

public:
    tagKeyFrame()
    { 
        memset( this, 0, sizeof(struct tagKeyFrame) ); 
    }
}TKeyFrame;
//Զң/����/���� �Ȼ���᳡�������νṹ��
typedef struct tagSetConfMts
{
    s8                      m_achConf_Id[TP_MAX_ID_LEN+1];                        //����id
    s8                      m_achMt_Id[TP_MAX_ID_LEN+1];                          //�ն�id

public:
    tagSetConfMts()
    { 
        Clear();
    }

    void Clear()
    {  
        memset( this, 0, sizeof(struct tagSetConfMts) ); 
    }

}TSetConfMts;

//���û�����ϯ/�����˴��νṹ��
typedef struct tagConfSpecialMan
{
    s8                      m_achConf_Id[TP_MAX_ID_LEN+1];                        //����id
    s8                      m_achMt_Ip[TP_MAX_IP_LEN+1];                          //�ն�ip

public:
    tagConfSpecialMan()
    { 
        memset( this, 0, sizeof(struct tagConfSpecialMan) ); 
    }
}TConfSpecialMan;

//����ģ�崫�νṹ��
typedef struct tagConfTempOperate
{
    s8                      m_achTemp_Id[TP_MAX_ID_LEN+1];                        //ģ��id

public:
    tagConfTempOperate()
    { 
        memset( this, 0, sizeof(struct tagConfTempOperate) ); 
    }
}TConfTempOperate;

//ˢ�½���֪ͨ���ͺͽ��
enum EmSetmtsType
{
    emSetTypeQuite,     //����
    emSetTypeMute,      //����
    emSetTypeCallUp,    //����
    emSetTypeHangUp,    //�Ҷ�
};


#endif //_h_eventstruct_url_h__
