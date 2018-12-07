/*=============================================================================
模   块   名: 无
文   件   名: rkcprintctrl.h
相 关  文 件: rkcprintctrl.cpp
文件实现功能: 打印控制
作        者: ylp
版        本: V1.0  Copyright(C) 2011-2012 Kedacom, All rights reserved.
-------------------------------------------------------------------------------
修改记录:
日      期  版本    修改人      修改内容
2018/03/05  1.0      ylp        创建
=============================================================================*/

#if !defined(AFX_RKCPRINTCTRL_H)
#define AFX_RKCPRINTCTRL_H
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum EmScoketEventType
{
    emEventTypeScoketSend, //Scoket Send
    emEventTypeScoketRecv, //Scoket Recv
};

class CRkcPrintCtrl  
{  

public: 

   /*=============================================================================
    函 数 名:GetPrintCtrl
    功    能:单例，获取打印类指针
    参    数:dwMsgID ：要打印的消息号，format：要打印的消息内容
    注    意:
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2011/04/23  1.0     俞锦锦  创建
    =============================================================================*/
    static const CRkcPrintCtrl*GetPrintCtrl(); 

    static const CString GetTime();

    /*=============================================================================
    函 数 名:PrintMsg
    功    能:打印某消息，如果该消息不在已设置的打印范围，则不会打印出来
    参    数:strIf ：要打印的接口名；emCurlEventType:要打印的消息类型；format：要打印的消息内容
    注    意:
    返 回 值: 
    -------------------------------------------------------------------------------
    修改纪录:
    日      期  版本    修改人  修改内容
    2018/03/05  1.0      ylp      创建
    =============================================================================*/
    static void PrintMsg(u16 dwMsgID, EmScoketEventType emScoketEventType,  char * format,... );
    static void PrintMsg(u16 dwMsgID, char * format,... );
    static void PrintMsg( char * format,... );


    static bool IsPrintMsg( u16 dwMsgID );
    //获得打印的类型
    static CString GetEventTypeDescribe(EmScoketEventType emType );
    //获得消息的描述
    static CString GetEventDescribe(u16 emType );
	//映射事件名称，同时注册到事件类别数组里面
	static void  MappingHelper(u16 wEvent, const CString& strName, u8 abyLevel = 2 );

    //打印全部消息
    static void PrintAllMsg();
    //打印级别为abyLevel的消息
    static void PrintMsgLevel( u8 abyLevel );
    //打印消息号为dwPrintEventId的消息
    static void SetPrintMsgID( const u32 dwPrintEventId );  
    //设置要打印的消息号的范围
    static void SetPrintMsgRange( const u32 dwMaxMsgID, const u32 dwMinMsgID );
    //不打印任何消息
    static void StopPrint();

    ~CRkcPrintCtrl();

protected:

    CRkcPrintCtrl();

    static map<u16, u8>        m_mapEventLevel;        // 消息级别
    static map<u16, CString>   m_mapEventsName;        // 消息名称映射表

protected:
    
    static CRkcPrintCtrl* m_pPrtCtrl;
    static BOOL32 m_bPrintAllMsg;       //是否要打印全部消息
    static u8     m_bayPrintLevel;      //打印等级
    static u32    m_dwPrintMsgID;       //要打印的消息号
    static u32    m_dwPrintRangeMax;    //要打印的消息范围 中的最大值
    static u32    m_dwPrintRangeMin;    //要打印的消息范围 中的最小值
};

#endif // !defined(AFX_RKCPRINTCTRL_H)