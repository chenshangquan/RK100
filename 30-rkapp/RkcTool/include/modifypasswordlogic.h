/** @defgroup �޸������߼���Ԫ 
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
    // ��������
    void OnResetAllInput();
    // �����뱣��
    bool OnSaveNewPwdClicked();
    // �ж��������Ƿ��޸� �޸ĺ��Ƿ񱣴�
    bool IsConfigChange();
    // �ж��������Ƿ��޸� ���޸����˳�
    bool ExitCheckChange();

    // ������������
    void OnGreatePwdHelpWind();
    // ���°�������λ��
    void OnUpdatePwdHelpWindPos();

protected:
    // ��ǰ��������
    bool OnInputCurPassword(TNotifyUI& msg);
    // ����������
    bool OnInputNewPassword(TNotifyUI& msg);
    // ȷ����������
    bool OnInputCfmPassword(TNotifyUI& msg);

    // ����������仯
    bool OnInputNewPwdChange(TNotifyUI& msg);

    // ��ǰ�����жϣ������Ƿ���ȷ
    bool OnJudgeCurPassword();
    // �������жϣ��Ƿ��������淶
    bool OnJudgeNewPassword();
    // ȷ�������жϣ��Ƿ��������淶
    bool OnJudgeCfmPassword();

    // ��ǰ����ɼ��Կ���
    bool OnCurPwdVisibleClicked(TNotifyUI& msg);
    // ������ɼ��Կ���
    bool OnNewPwdVisibleClicked(TNotifyUI& msg);
    // ȷ������ɼ��Կ���
    bool OnCfmPwdVisibleClicked(TNotifyUI& msg);

    // ������Ϣ��ʾ
    bool OnShowPasswordHelp(TNotifyUI& msg);

    // �����뱣��
    bool OnSaveNewPwdClicked(TNotifyUI& msg);

    // �����޸���Ϣ�ظ�����
    bool OnRkcPasswordModified( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnRkcDisconnected( WPARAM wparam, LPARAM lparam, bool& bHandle );

    // ��ȡ�����ļ�·��
    CString GetIniFilePath();

    APP_DECLARE_MSG_MAP()

private:
    bool m_bCurPwdIsJudged;         //�����Ƿ����ж�����淶
    bool m_bCurPwdIsRight;          //�����Ƿ��������淶
    bool m_bNewPwdIsJudged;         //�������Ƿ����ж�����淶
    bool m_bNewPwdIsStandard;       //�������Ƿ��������淶
    bool m_bPwdIsSameAsBefore;      //�������Ƿ���ԭ����һ��

    bool m_bBack2HomePage;          //�ص�Ĭ����ҳ(��������ҳ��)

    s32 m_nHelpWindLeft;            //�����������λ��
    s32 m_nHelpWindTop;             //�������ڶ���λ��
};

#endif // !defined(AFX_MODIFYPASSWORD_H_)