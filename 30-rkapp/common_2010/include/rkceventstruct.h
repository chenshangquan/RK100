#ifndef _h_eventstruct_url_h__
#define _h_eventstruct_url_h__

#include "urlstruct.h"

//加入会议传参结构体
typedef struct tagJoinConf
{
    s8                      m_achConf_Id[TP_MAX_ID_LEN+1];                  //会议号
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
//中屏选看传参结构体
typedef struct tagSelViewMid
{
    s8                      m_achConf_Id[TP_MAX_ID_LEN+1];                     //会议id
    u16                     m_wMode;                                //选看模式1-视频，2-音频
    u16                     m_wSrcType;                             //选看源类型
    s8                      m_achSrcMt_Id[TP_MAX_ID_LEN+1];                    //选看源ID
    s8                      m_achDstMt_Id[TP_MAX_ID_LEN+1];                    //目的终端号

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
//监控开启传参结构体
typedef struct tagMonitorStart
{
    s8                      m_achConf_Id[TP_MAX_ID_LEN+1];                     //会议id
    u16                     m_wMode;                                //监控模式 0-视频 1-音频
    u16                     m_wType;                                //监控类型 1-终端 2-画面合成 3-混音
    s8                      m_achSrcMt_Id[TP_MAX_ID_LEN+1];                    //监控终端ID type为终端时必填
    u16                     m_wVedioFormat;                         //主视频格式 1-MPEG 2-H.261 3-H.263 4-H.264_HP 5-H.264_BP 6-H.265
    u16                     m_wVedioResolution;                     //主视频分辨率 1-QCIF 2-CIF 3-4CIF 12-720P 13-1080P 14-WCIF 15-W4CIF 16-4k
    u16                     m_wFrame;                               //主视频帧率
    u16                     m_wBitrate;                             //主视频码率
    u16                     m_wAudioFormat;                         //主音频类型 1-MP3 2-G722.1.C 3-G719 4-G.711(Alaw) 5-G.711(Ulaw) 6-G.721 7-G.722 8-G.7231 9-G.728 10-G.729 11-G.7221 12-OPUS 13-MPEG-4 AAC LC 14-MPEG-4 AAC LD;
    u16                     m_wChn_num;                             //声轨数量 1-单声道 2-双声道
    s8                      m_achIP[TP_MAX_IP_LEN+1];                          //目的ip地址
    u16                     m_wPort;                                //目的rtp端口
public:
    tagMonitorStart()
    { 
        memset( this, 0, sizeof(struct tagMonitorStart) ); 
    }
}TMonitorStart;
//监控结束传参结构体 //监控请求关键帧传参结构体
typedef struct tagKeyFrame
{
    s8                      m_achConf_Id[TP_MAX_ID_LEN+1];                     //会议id
    u16                     m_wPort;                                //端口号
    s8                      m_achIP[TP_MAX_IP_LEN+1];                          //IP

public:
    tagKeyFrame()
    { 
        memset( this, 0, sizeof(struct tagKeyFrame) ); 
    }
}TKeyFrame;
//远遥/哑音/静音 等会议会场操作传参结构体
typedef struct tagSetConfMts
{
    s8                      m_achConf_Id[TP_MAX_ID_LEN+1];                        //会议id
    s8                      m_achMt_Id[TP_MAX_ID_LEN+1];                          //终端id

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

//设置会议主席/发言人传参结构体
typedef struct tagConfSpecialMan
{
    s8                      m_achConf_Id[TP_MAX_ID_LEN+1];                        //会议id
    s8                      m_achMt_Ip[TP_MAX_IP_LEN+1];                          //终端ip

public:
    tagConfSpecialMan()
    { 
        memset( this, 0, sizeof(struct tagConfSpecialMan) ); 
    }
}TConfSpecialMan;

//会议模板传参结构体
typedef struct tagConfTempOperate
{
    s8                      m_achTemp_Id[TP_MAX_ID_LEN+1];                        //模板id

public:
    tagConfTempOperate()
    { 
        memset( this, 0, sizeof(struct tagConfTempOperate) ); 
    }
}TConfTempOperate;

//刷新界面通知类型和结果
enum EmSetmtsType
{
    emSetTypeQuite,     //静音
    emSetTypeMute,      //哑音
    emSetTypeCallUp,    //呼叫
    emSetTypeHangUp,    //挂断
};


#endif //_h_eventstruct_url_h__
