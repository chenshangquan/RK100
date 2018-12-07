/** @defgroup ���������߼���Ԫ 
 *  @version V1.0.0
 *  @author  ylp
 *  @date    2018.10.17
 */
#if !defined(AFX_RADIOSETUP_H_)
#define AFX_RADIOSETUP_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRadioSetupLogic : public CNotifyUIImpl, public Singleton<CRadioSetupLogic> 
{
public:
	CRadioSetupLogic();
	~CRadioSetupLogic();

    bool OnSaveRadioButClicked();
protected:
     /** ��ʼ����Ϣ 
	 *  @param[in] 
	 *  @node 
	 *  @return 
     */
    bool OnInit(TNotifyUI& msg);

    //ɾ�����谴ť
    bool OnItemDelBtnClicked(TNotifyUI& msg);
    //�������谴ť
    bool OnItemAddBtnClicked(TNotifyUI& msg);
    //����
    bool OnRadioSwitchOptSel(TNotifyUI& msg);
    //�������谴ť
    bool OnOpenRadioOptSel(TNotifyUI& msg);
    //�������谴ť
    bool OnCloseRadioOptSel(TNotifyUI& msg);
    //������水ť
    bool OnSaveRadioButClicked(TNotifyUI& msg);
    //����Edit�����仯
    bool OnEditTextChange(TNotifyUI& msg);

    void RefreshRadioList();
    //ˢ������
    bool OnRkcRadioReflesh( WPARAM wparam, LPARAM lparam, bool& bHandle );
    //�޸����ý��
    bool OnRkcWorkModeChangeRsp( WPARAM wparam, LPARAM lparam, bool& bHandle );

    //���水ť�Ƿ����
    void SetSaveBtnEnable();

    APP_DECLARE_MSG_MAP()

private:
    CListUI* m_pPeripheralList; //����list
};

#endif // !defined(AFX_RADIOSETUP_H_)