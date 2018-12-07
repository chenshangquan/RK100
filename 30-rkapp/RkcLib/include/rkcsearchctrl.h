#pragma once
#include "rkcsession.h"

class CRkcSearchCtrl : public CRkcSearchCtrlIF 
{
    friend class CRkcSession;
public:
    CRkcSearchCtrl(CRkcSession &cSession);
    virtual ~CRkcSearchCtrl();

    //start Search
    virtual u16 StartSearch();
    //end Search
    virtual u16 EndSearch();
    //set type
    virtual u16 SetSearchType(EmSearchType emtype , u32 dwStartip , u32 dwEndip);
    //reset
    virtual void ReSet();
protected:
    void BuildEventsMap();

    void OnDicconnected(const CMessage& cMsg);

    void OnRkcDevReflesh(const CMessage& cMsg);

    virtual const vector<TDevItem>& GetDevList() const;

    virtual void DispEvent(const CMessage &cMsg);
    virtual void OnTimeOut(u16 wEvent);

private:
    CRkcSession                     *m_pSession;
    std::vector<TDevItem>           m_vecDevItem;//�����������
    EmSearchType                    m_EmSearchType;//��������
    u32                             m_dwStartIP;//������ʼIP
    u32                             m_dwEndIP;//������ֹIP
};
