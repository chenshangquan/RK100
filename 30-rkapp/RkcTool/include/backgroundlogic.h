/** @defgroup �����߼���Ԫ 
 *  @version V1.0.0
 *  @author  chenshangquan
 *  @date    2018.11.23
 */
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBackGroundLogic : public CNotifyUIImpl, public Singleton<CBackGroundLogic> 
{
public:
	CBackGroundLogic();
	~CBackGroundLogic();

public:

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

    APP_DECLARE_MSG_MAP()

private:

};