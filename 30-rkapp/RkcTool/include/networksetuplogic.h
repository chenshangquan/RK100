/** @defgroup 网络设置逻辑单元 
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
    //点击检测按钮
    bool OnIPCheckBtnClicked(TNotifyUI& msg);
    //点击保存按钮
    bool OnSaveNetWorkButClicked(TNotifyUI& msg);
    //界面设备IP Edit发生变化
    bool OnDevIPEditTextChange(TNotifyUI& msg);
    //界面Edit发生变化
    bool OnEditTextChange(TNotifyUI& msg);
    //刷新网络配置
    bool OnRkcNetWorkReflesh( WPARAM wparam, LPARAM lparam, bool& bHandle );
    //修改网络配置结果
    bool OnRkcNetWorkChangeRsp( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnRkcIPChecked( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnRkcDisconnected( WPARAM wparam, LPARAM lparam, bool& bHandle );

    //保存按钮是否可用
    void SetSaveBtnEnable();

    APP_DECLARE_MSG_MAP()

private:

};

#endif // !defined(AFX_NETWORKSETUP_H_)