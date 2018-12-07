/*=============================================================================
ģ   ��   ��: ��
��   ��   ��: rkcprintctrl.h
�� ��  �� ��: rkcprintctrl.cpp
�ļ�ʵ�ֹ���: ��ӡ����
��        ��: ylp
��        ��: V1.0  Copyright(C) 2011-2012 Kedacom, All rights reserved.
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���      �޸�����
2018/03/05  1.0      ylp        ����
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
    �� �� ��:GetPrintCtrl
    ��    ��:��������ȡ��ӡ��ָ��
    ��    ��:dwMsgID ��Ҫ��ӡ����Ϣ�ţ�format��Ҫ��ӡ����Ϣ����
    ע    ��:
    �� �� ֵ: 
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2011/04/23  1.0     �����  ����
    =============================================================================*/
    static const CRkcPrintCtrl*GetPrintCtrl(); 

    static const CString GetTime();

    /*=============================================================================
    �� �� ��:PrintMsg
    ��    ��:��ӡĳ��Ϣ���������Ϣ���������õĴ�ӡ��Χ���򲻻��ӡ����
    ��    ��:strIf ��Ҫ��ӡ�Ľӿ�����emCurlEventType:Ҫ��ӡ����Ϣ���ͣ�format��Ҫ��ӡ����Ϣ����
    ע    ��:
    �� �� ֵ: 
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2018/03/05  1.0      ylp      ����
    =============================================================================*/
    static void PrintMsg(u16 dwMsgID, EmScoketEventType emScoketEventType,  char * format,... );
    static void PrintMsg(u16 dwMsgID, char * format,... );
    static void PrintMsg( char * format,... );


    static bool IsPrintMsg( u16 dwMsgID );
    //��ô�ӡ������
    static CString GetEventTypeDescribe(EmScoketEventType emType );
    //�����Ϣ������
    static CString GetEventDescribe(u16 emType );
	//ӳ���¼����ƣ�ͬʱע�ᵽ�¼������������
	static void  MappingHelper(u16 wEvent, const CString& strName, u8 abyLevel = 2 );

    //��ӡȫ����Ϣ
    static void PrintAllMsg();
    //��ӡ����ΪabyLevel����Ϣ
    static void PrintMsgLevel( u8 abyLevel );
    //��ӡ��Ϣ��ΪdwPrintEventId����Ϣ
    static void SetPrintMsgID( const u32 dwPrintEventId );  
    //����Ҫ��ӡ����Ϣ�ŵķ�Χ
    static void SetPrintMsgRange( const u32 dwMaxMsgID, const u32 dwMinMsgID );
    //����ӡ�κ���Ϣ
    static void StopPrint();

    ~CRkcPrintCtrl();

protected:

    CRkcPrintCtrl();

    static map<u16, u8>        m_mapEventLevel;        // ��Ϣ����
    static map<u16, CString>   m_mapEventsName;        // ��Ϣ����ӳ���

protected:
    
    static CRkcPrintCtrl* m_pPrtCtrl;
    static BOOL32 m_bPrintAllMsg;       //�Ƿ�Ҫ��ӡȫ����Ϣ
    static u8     m_bayPrintLevel;      //��ӡ�ȼ�
    static u32    m_dwPrintMsgID;       //Ҫ��ӡ����Ϣ��
    static u32    m_dwPrintRangeMax;    //Ҫ��ӡ����Ϣ��Χ �е����ֵ
    static u32    m_dwPrintRangeMin;    //Ҫ��ӡ����Ϣ��Χ �е���Сֵ
};

#endif // !defined(AFX_RKCPRINTCTRL_H)