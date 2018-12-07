/** @defgroup ����仯��ʾ*/
#pragma once

class CNetChangeLogic : public CNotifyUIImpl
{
public:
	CNetChangeLogic(void);
	~CNetChangeLogic(void);

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
	
public:
	/** ����λ��
	*  @param[in] ���Ͻ�����
	*  @return 
	*/
	bool SetPos();

	APP_DECLARE_MSG_MAP()
		
private:
	 
};

bool showNetChange(POINT pt, LPCTSTR lpstrIniPath);
#define ShowNetChange showNetChange

