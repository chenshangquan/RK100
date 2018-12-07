/** @defgroup ��¼�߼���Ԫ 
 *  @version V1.0.0
 *  @author  ylp
 *  @date    2018.9.27
 */
#if !defined(AFX_LOGINLOGIC_H_)
#define AFX_LOGINLOGIC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLoginLogic : public CNotifyUIImpl
{
public:
	CLoginLogic();
	~CLoginLogic();

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
    //�����¼��ť
    bool OnLoginBtnClicked(TNotifyUI& msg);

    //�Զ���¼
    bool OnCheckAutoLoginSel(TNotifyUI& msg);
    //��ס����
    bool OnCheckRemPassWordSel(TNotifyUI& msg);

    //��ʾ��ʾ��ʱ����Ӧ
    bool OnShowTipTimer(TNotifyUI& msg);

    bool OnRkcConnected( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnRkcDisconnected( WPARAM wparam, LPARAM lparam, bool& bHandle );

    void ShowTip(CString strTip);

    APP_DECLARE_MSG_MAP()

private:
};

#endif // !defined(AFX_LOGINLOGIC_H_)