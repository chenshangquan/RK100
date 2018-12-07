/** @defgroup 修改密码逻辑单元 
 *  @version V1.0.0
 *  @author  csq
 *  @date    2018.10.17
 */
#if !defined(AFX_MODIFYPASSWORD_H_)
#define AFX_MODIFYPASSWORD_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define KILL_FOCUS_DELAY 200

class CModifyPasswordLogic : public CNotifyUIImpl, public Singleton<CModifyPasswordLogic> 
{
public:
	CModifyPasswordLogic();
	~CModifyPasswordLogic();

public:
    // 清空输入框
    void OnResetAllInput();
    // 新密码保存
    bool OnSaveNewPwdClicked();
    // 判断配置项是否修改 修改后是否保存
    bool IsConfigChange();
    // 判断配置项是否修改 不修改则退出
    bool ExitCheckChange();

    // 创建帮助窗口
    void OnGreatePwdHelpWind();
    // 更新帮助窗口位置
    void OnUpdatePwdHelpWindPos();

protected:
    // 当前密码输入
    bool OnInputCurPassword(TNotifyUI& msg);
    // 新密码输入
    bool OnInputNewPassword(TNotifyUI& msg);
    // 确认密码输入
    bool OnInputCfmPassword(TNotifyUI& msg);

    // 新密码输入变化
    bool OnInputNewPwdChange(TNotifyUI& msg);

    // 当前密码判断，密码是否正确
    bool OnJudgeCurPassword();
    // 新密码判断，是否符合密码规范
    bool OnJudgeNewPassword();
    // 确认密码判断，是否符合密码规范
    bool OnJudgeCfmPassword();

    // 当前密码可见性开关
    bool OnCurPwdVisibleClicked(TNotifyUI& msg);
    // 新密码可见性开关
    bool OnNewPwdVisibleClicked(TNotifyUI& msg);
    // 确认密码可见性开关
    bool OnCfmPwdVisibleClicked(TNotifyUI& msg);

    // 帮助信息显示
    bool OnShowPasswordHelp(TNotifyUI& msg);

    // 新密码保存
    bool OnSaveNewPwdClicked(TNotifyUI& msg);

    // 密码修改消息回复处理
    bool OnRkcPasswordModified( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnRkcDisconnected( WPARAM wparam, LPARAM lparam, bool& bHandle );

    // 获取配置文件路径
    CString GetIniFilePath();

    APP_DECLARE_MSG_MAP()

private:
    bool m_bCurPwdIsJudged;         //密码是否已判断密码规范
    bool m_bCurPwdIsRight;          //密码是否符合密码规范
    bool m_bNewPwdIsJudged;         //新密码是否已判断密码规范
    bool m_bNewPwdIsStandard;       //新密码是否符合密码规范
    bool m_bPwdIsSameAsBefore;      //新密码是否与原密码一致

    bool m_bBack2HomePage;          //回到默认主页(网络设置页面)

    s32 m_nHelpWindLeft;            //帮助窗口左侧位置
    s32 m_nHelpWindTop;             //帮助窗口顶部位置
};

#endif // !defined(AFX_MODIFYPASSWORD_H_)