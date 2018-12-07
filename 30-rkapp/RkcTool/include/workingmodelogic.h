/** @defgroup 工作模式逻辑单元 
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
    //开机
    bool OnTabOpenRelay(TNotifyUI& msg);
    //关机
    bool OnTabCloseRelay(TNotifyUI& msg);
    //点击保存按钮
    bool OnSaveWorkModeButClicked(TNotifyUI& msg);
    //界面Edit发生变化
    bool OnEditTextChange(TNotifyUI& msg);

    bool OnRkcWorkModeReflesh( WPARAM wparam, LPARAM lparam, bool& bHandle );

    //保存按钮是否可用
    void SetSaveBtnEnable();

    APP_DECLARE_MSG_MAP()

private:

};

#endif // !defined(AFX_WORKINGMODE_H_)