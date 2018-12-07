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
	//消息处理函数
	void OnLButtonDown(LPMSG pMsg);
	void OnLButtonUp(LPMSG pMsg);
	void OnTimer(LPMSG pMsg);
	void OnMouseMove(LPMSG pMsg);
protected:
	//开始拖放
	void StartDrag();
	//滚动
	void DoAutoScroll(CControlUI *pTraget, POINT ptMouse);
	//查找treeview的结点
	CTreeNodeUI* GetTreeNode(CTreeViewUI *pTree, POINT pt);
	//状态恢复
	void Restore();
	//检查焦点
	void CheckFocus();
	//根据光标位置获取源控件
	CControlUI* GetSourceCtrl(POINT pt);
	//根据光标位置获取目标控件
	CControlUI* GetTargetCtrl(POINT pt);
	//判断控件是否可以拖放
	bool IsDragableCtrl(CControlUI *pCtrl, POINT pt);
protected:
	//截取消息的钩子过程
	static LRESULT CALLBACK GetMessageProc(int nCode, WPARAM wParam, LPARAM lParam);
	static HHOOK s_hHook;
	//初始化/释放钩子
	void InitHook();
	void FreeHook();
protected:
	CControlUI *m_pSourceCtrl;  //源控件
	CControlUI *m_pTargetCtrl;  //目标控件
	CDragWnd *m_pDragWnd;  //拖拽截图窗口
	bool m_bIsLBtnDown;		//鼠标是否按下
	bool m_bIsDragging;		//是否正在拖拽
	bool m_bIsScrolling;		//是否正在滚动
	POINT m_ptDragPoint;	//起拖点
	POINT m_ptOffSet;			//与拖动控件左上角的偏移
	HWND m_hTargetWnd;	//目标窗口句柄

};

}