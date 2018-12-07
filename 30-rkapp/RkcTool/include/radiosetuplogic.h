/** @defgroup 外设设置逻辑单元 
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
     /** 初始化消息 
	 *  @param[in] 
	 *  @node 
	 *  @return 
     */
    bool OnInit(TNotifyUI& msg);

    //删除外设按钮
    bool OnItemDelBtnClicked(TNotifyUI& msg);
    //增加外设按钮
    bool OnItemAddBtnClicked(TNotifyUI& msg);
    //启用
    bool OnRadioSwitchOptSel(TNotifyUI& msg);
    //启用外设按钮
    bool OnOpenRadioOptSel(TNotifyUI& msg);
    //禁用外设按钮
    bool OnCloseRadioOptSel(TNotifyUI& msg);
    //点击保存按钮
    bool OnSaveRadioButClicked(TNotifyUI& msg);
    //界面Edit发生变化
    bool OnEditTextChange(TNotifyUI& msg);

    void RefreshRadioList();
    //刷新配置
    bool OnRkcRadioReflesh( WPARAM wparam, LPARAM lparam, bool& bHandle );
    //修改配置结果
    bool OnRkcWorkModeChangeRsp( WPARAM wparam, LPARAM lparam, bool& bHandle );

    //保存按钮是否可用
    void SetSaveBtnEnable();

    APP_DECLARE_MSG_MAP()

private:
    CListUI* m_pPeripheralList; //外设list
};

#endif // !defined(AFX_RADIOSETUP_H_)