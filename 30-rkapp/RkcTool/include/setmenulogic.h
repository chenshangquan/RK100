/** @defgroup ���ò˵��߼���Ԫ 
 *  @version V1.0.0
 *  @author  chenshangquan
 *  @date    2018.11.9
 */
#if !defined(AFX_SETMENU_H_)
#define AFX_SETMENU_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSetMenuLogic : public CNotifyUIImpl, public Singleton<CSetMenuLogic> 
{
public:
	CSetMenuLogic();
	~CSetMenuLogic();

public:
    // ���´���λ��
    void OnUpdateWindowPos();
    // ������ʾ��ʼ��
    void OnMenuShowInit();

protected:
	/** ���ڴ��� 
	*  @param[in] ��Ϣ
	*  @return �Ƿ�ɹ�
	*/
	bool OnCreate(TNotifyUI& msg);

	/** �رմ�����Ϣ 
	 *  @param[in] 
	 *  @node 
	 *  @return 
     */
    bool OnDestory(TNotifyUI& msg);

	/** ��ʼ����Ϣ 
	 *  @param[in] 
	 *  @node 
	 *  @return 
     */
    bool OnInit(TNotifyUI& msg);

    // ����޸�����ѡ��
    bool OnMdPwdItemClicked(TNotifyUI& msg);
    // ����������
    bool OnRebootItemClicked(TNotifyUI& msg);
    // �������ѡ��
    bool OnAboutInfoItemClicked(TNotifyUI& mst);

    APP_DECLARE_MSG_MAP()

private:
    s32 m_nLeft;    //�˵����ڵ����������λ��
    s32 m_nTop;     //�˵����ڵ������ڶ���λ��
};

#endif // !defined(AFX_SETMENU_H_)