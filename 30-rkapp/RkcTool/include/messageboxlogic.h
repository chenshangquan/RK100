/** @defgroup ��¼�߼���Ԫ 
 *  @version V1.0.0
 *  @author  ylp
 *  @date    2018.9.27
 */
#if !defined(AFX_MESSAGEBOXLOGIC_H_)
#define AFX_MESSAGEBOXLOGIC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum EmueMsgOperat
{
    Emue_None              = 0,     //�޲���
    Emue_Restore,                   //�ָ�Ĭ��
};


class CMessageBoxLogic : public CNotifyUIImpl
{
public:
	CMessageBoxLogic();
	~CMessageBoxLogic();

protected:
	/** ���ڴ��� 
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnCreate(TNotifyUI& msg);

	/** ��ʼ����Ϣ 
	 *  @param[in] 
	 *  @node 
	 *  @return 
     */
    bool OnInit(TNotifyUI& msg);

    /** �ر���Ϣ 
	 *  @param[in] 
	 *  @node 
	 *  @return 
     */
    bool OnDestroy(TNotifyUI& msg);

    //����رհ�ť
    bool OnCloseBtnClicked(TNotifyUI& msg);
    //���ȷ����ť
    bool OnOKBtnClicked(TNotifyUI& msg);
    //���ȡ����ť
    bool OnCancelBtnClicked(TNotifyUI& msg);
    //�����޸�����
    bool OnNetChangeBtnClicked(TNotifyUI& msg);
    //��������ط�
    bool OnSpaceLayoutClicked(TNotifyUI& msg);

    //�豸��������
    bool OnRkcRestone( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnRkcDisconnected( WPARAM wparam, LPARAM lparam, bool& bHandle );
    
    APP_DECLARE_MSG_MAP()

private:

    u8 m_emOperation;
};

u8 showMessageBox(LPCTSTR lpstrText, u8 byType = 1, LPCTSTR lpstrLeftText = _T("ȷ��"));//0 û�а�ť��1 ȷ����ť��2 ȷ�� ȡ����ť
#define ShowMessageBox showMessageBox

bool showBackUpBox(LPCTSTR lpstrTime, LPCTSTR lpstrModel, LPCTSTR lpstrIniPath);
#define ShowBackUpBox showBackUpBox

bool showUpDateBox(LPCTSTR lpstrModel, LPCTSTR lpstrVer, LPCTSTR lpstrVerN);
#define ShowUpDateBox showUpDateBox

#endif // !defined(AFX_MESSAGEBOXLOGIC_H_)