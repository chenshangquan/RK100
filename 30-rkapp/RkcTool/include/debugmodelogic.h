/** @defgroup ����ģʽ�߼���Ԫ 
 *  @version V1.0.0
 *  @author  ylp
 *  @date    2018.11.13
 */
#if !defined(AFX_DEBUGMODE_H_)
#define AFX_DEBUGMODE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDebugModeLogic : public CNotifyUIImpl, public Singleton<CDebugModeLogic> 
{
public:
	CDebugModeLogic();
	~CDebugModeLogic();

    bool OnSaveDebugModeButClicked();
protected:
    //������水ť
    bool OnSaveDebugModeButClicked(TNotifyUI& msg);
    bool OnDebugSwitchOptSel(TNotifyUI& msg);
    //���水ť�Ƿ����
    void SetSaveBtnEnable();

    bool OnRkcDebugModeReflesh( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnRkcDebugModeChangeRsp( WPARAM wparam, LPARAM lparam, bool& bHandle );

    APP_DECLARE_MSG_MAP()

private:

};

#endif // !defined(AFX_DEBUGMODE_H_)