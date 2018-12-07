/** @defgroup ���������߼���Ԫ 
 *  @version V1.0.0
 *  @author  ylp
 *  @date    2018.10.17
 */
#if !defined(AFX_NETWORKSETUP_H_)
#define AFX_NETWORKSETUP_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNetworkSetupLogic : public CNotifyUIImpl, public Singleton<CNetworkSetupLogic> 
{
public:
	CNetworkSetupLogic();
	~CNetworkSetupLogic();

    bool OnSaveNetWorkButClicked();
protected:
    //�����ⰴť
    bool OnIPCheckBtnClicked(TNotifyUI& msg);
    //������水ť
    bool OnSaveNetWorkButClicked(TNotifyUI& msg);
    //�����豸IP Edit�����仯
    bool OnDevIPEditTextChange(TNotifyUI& msg);
    //����Edit�����仯
    bool OnEditTextChange(TNotifyUI& msg);
    //ˢ����������
    bool OnRkcNetWorkReflesh( WPARAM wparam, LPARAM lparam, bool& bHandle );
    //�޸��������ý��
    bool OnRkcNetWorkChangeRsp( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnRkcIPChecked( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnRkcDisconnected( WPARAM wparam, LPARAM lparam, bool& bHandle );

    //���水ť�Ƿ����
    void SetSaveBtnEnable();

    APP_DECLARE_MSG_MAP()

private:

};

#endif // !defined(AFX_NETWORKSETUP_H_)