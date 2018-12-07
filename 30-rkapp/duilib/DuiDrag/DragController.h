#pragma once
#include "DragInterface.h"
#include "UIDragWnd.h"
namespace DuiLib{
class CDragController : public IDragController
{
public:
	CDragController();
	~CDragController();
	virtual LRESULT HandleMessage(LPMSG pMsg);
protected:
	//��Ϣ������
	void OnLButtonDown(LPMSG pMsg);
	void OnLButtonUp(LPMSG pMsg);
	void OnTimer(LPMSG pMsg);
	void OnMouseMove(LPMSG pMsg);
protected:
	//��ʼ�Ϸ�
	void StartDrag();
	//����
	void DoAutoScroll(CControlUI *pTraget, POINT ptMouse);
	//����treeview�Ľ��
	CTreeNodeUI* GetTreeNode(CTreeViewUI *pTree, POINT pt);
	//״̬�ָ�
	void Restore();
	//��齹��
	void CheckFocus();
	//���ݹ��λ�û�ȡԴ�ؼ�
	CControlUI* GetSourceCtrl(POINT pt);
	//���ݹ��λ�û�ȡĿ��ؼ�
	CControlUI* GetTargetCtrl(POINT pt);
	//�жϿؼ��Ƿ�����Ϸ�
	bool IsDragableCtrl(CControlUI *pCtrl, POINT pt);
protected:
	//��ȡ��Ϣ�Ĺ��ӹ���
	static LRESULT CALLBACK GetMessageProc(int nCode, WPARAM wParam, LPARAM lParam);
	static HHOOK s_hHook;
	//��ʼ��/�ͷŹ���
	void InitHook();
	void FreeHook();
protected:
	CControlUI *m_pSourceCtrl;  //Դ�ؼ�
	CControlUI *m_pTargetCtrl;  //Ŀ��ؼ�
	CDragWnd *m_pDragWnd;  //��ק��ͼ����
	bool m_bIsLBtnDown;		//����Ƿ���
	bool m_bIsDragging;		//�Ƿ�������ק
	bool m_bIsScrolling;		//�Ƿ����ڹ���
	POINT m_ptDragPoint;	//���ϵ�
	POINT m_ptOffSet;			//���϶��ؼ����Ͻǵ�ƫ��
	HWND m_hTargetWnd;	//Ŀ�괰�ھ��

};

}