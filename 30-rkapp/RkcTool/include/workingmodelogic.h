/** @defgroup ����ģʽ�߼���Ԫ 
 *  @version V1.0.0
 *  @author  ylp
 *  @date    2018.10.17
 */
#if !defined(AFX_WORKINGMODE_H_)
#define AFX_WORKINGMODE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum EmRedayTabID
{
    emTabID_OpenReday = 0,
    emTabID_CloseReday,
};

class CWorkingModeLogic : public CNotifyUIImpl, public Singleton<CWorkingModeLogic> 
{
public:
	CWorkingModeLogic();
	~CWorkingModeLogic();

    bool OnSaveWorkModeButClicked();
protected:
    //����
    bool OnTabOpenRelay(TNotifyUI& msg);
    //�ػ�
    bool OnTabCloseRelay(TNotifyUI& msg);
    //������水ť
    bool OnSaveWorkModeButClicked(TNotifyUI& msg);
    //����Edit�����仯
    bool OnEditTextChange(TNotifyUI& msg);

    bool OnRkcWorkModeReflesh( WPARAM wparam, LPARAM lparam, bool& bHandle );

    //���水ť�Ƿ����
    void SetSaveBtnEnable();

    APP_DECLARE_MSG_MAP()

private:

};

#endif // !defined(AFX_WORKINGMODE_H_)