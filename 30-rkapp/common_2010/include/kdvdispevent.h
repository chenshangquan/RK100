#ifndef __DISPEVENT_H__
#define __DISPEVENT_H__

#include "kdvtype.h"
//#include "kdvsys.h"
#include <map>
#include "nmscommon.h"
#include "crkmessage.h"
 
using namespace std;

#define TYPE_CMESSAGE  0         // һ���CMessage��Ϣ
#define TYPE_TPMSG     1         // �շ�����ϢΪCTPMSG ,��Ҫ������Ϣ���͵�ת��

//////////////////////////////////////////////////////////////////////////
// ���ӿڻ��࣬��Ҫ���ڷַ���Ϣ
class CKdvDispEvent
{
public:
    typedef void(CKdvDispEvent::*DISPEVENT_PFUN)(const CMessage & cMsg);
public:
    CKdvDispEvent();
    virtual ~CKdvDispEvent();
    // �ж�һ��Ϣ�Ƿ��ڱ�����ע���
    BOOL HasRegEvent(u16 wEvent) const;
    // �ַ���Ϣ���������Ӧ����ĺ����ĵ��ã�������������ѵĵ���
    virtual void DispEvent(const CMessage &cMsg) = 0;
    // ��Ϣ��ʱ����Ӧ
    virtual void OnTimeOut(u16 wEvent) = 0;
    // �õ�֪ͨ���ھ��
    HWND GetNotifyWnd() { return m_hWnd; }
    // �趨֪ͨ���ھ��
    void SetNotifyWnd(HWND hWnd) { m_hWnd = hWnd; }
protected:
    // ��һ����Ϣ���䴦����ע�����
    void RegDispFunPointer(u16 wEvent, DISPEVENT_PFUN pFun);
    // ��յ�����ע�����Ϣ
    void ClearDisp();
    // ��ע��Ľ��洰�ڷ���ָ������Ϣ
    BOOL PostEvent(u32 dwEvent, WPARAM wParam = 0, LPARAM lParam = 0);
protected:
	// 4.0 �޸�Ϊֻ�����¼���Id
    map<u16, DISPEVENT_PFUN> m_mappFun;
    HWND        m_hWnd;         // ��Ϣ���ͽ���Ĵ��ھ��
};
//ע����Ϣӳ��
#if _MSC_VER <= 1200
#define REG_PFUN(event, fun)        \
    RegDispFunPointer(event, (void (CKdvDispEvent::*)(const CMessage &cMsg))fun);
#else
//֧��VS2010
#define REG_PFUN(event, fun)        \
	RegDispFunPointer(event, (void (CKdvDispEvent::*)(const CMessage &cMsg))&fun);
#endif

//�ַ���Ϣӳ��
#define DISP_FUN(clsName, cMsg)                                 \
	if(m_mappFun.find(cMsg.event) != m_mappFun.end())			\
	{															\
	   (this->*(void(clsName::*)(const CMessage &cMsg))(m_mappFun[cMsg.event]))(cMsg);	\
	}
#endif