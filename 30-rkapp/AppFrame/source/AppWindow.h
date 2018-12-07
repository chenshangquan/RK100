#ifndef __APPWINDOW_H__
#define __APPWINDOW_H__

#pragma once
namespace AppFrame {
class CNotifyUIImpl;
class UILIB_API CAppWindow : public CWindowWnd
{
public:
	CAppWindow(LPCTSTR lpstrUI, LPVOID pData = NULL);
	~CAppWindow();
	LPCTSTR GetWindowClassName() const;
	UINT GetClassStyle() const;
	void OnFinalMessage(HWND /*hWnd*/);

	virtual void Init();
	virtual void Close(UINT nRet = IDOK);

	void	MoveWindow( int x, int y, int nWidth, int nHeight, bool bRepaint = true );
	bool	AddNotifier( CNotifyUIImpl* pNotifier );


	virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void SetPaintOnWindow( bool bPaint );

	CPaintManagerUI m_pm;
    CDuiString		m_strSkin;
	CStdPtrArray m_aNotifiers;
	LPVOID m_pData;
}; 


typedef void (CNotifyUIImpl::*MSG_FUNC)(void);
typedef bool(CNotifyUIImpl::*BN_FUNC)(TNotifyUI& msg);
typedef bool(CNotifyUIImpl::*UWLB_FUNC)(WPARAM wParam, LPARAM lParam, bool& bHandled);
union MessageMapFuncs
{
	MSG_FUNC pfn;   // generic member function pointer
	BN_FUNC pfn_bn;
	UWLB_FUNC pfn_uwlb;
};

enum EMFuncType
{
	emFunc_vv = 0,		//返回void 参数void
	emFunc_bn,			//返回bool 参数TNOTIFYUI
	emFunc_uwlb,		//返回UINT 参数WAPRAM LPARAM bool
};

#define MAX_EVENT_NAME_LEN		100
#define MAX_CONTROL_NAME_LEN	255
#define MAX_FUNC_NAME_LEN		255
struct MSGMAP_ENTRY
{
	unsigned int	m_dwEvent;	// 非自定义消息，此变量为0
	TCHAR			m_chEvent[MAX_EVENT_NAME_LEN];
	TCHAR			m_chControl[MAX_CONTROL_NAME_LEN];
	TCHAR			m_chFunc[MAX_FUNC_NAME_LEN];
	unsigned int	m_wSig;
	MSG_FUNC		m_pfn;   
};

struct MSGMAP
{
	const MSGMAP* pBaseMap;
	const MSGMAP_ENTRY* lpEntries;
};

class CNotifyUIImpl : public INotifyUI, public IMessageFilterUI,
	public IPreMessageFilterUI, public ITranslateAccelerator
{
public:
	CNotifyUIImpl() : m_pm(0) {}
	virtual void Notify(TNotifyUI& msg);
	virtual void SetPaintManagerUI(CPaintManagerUI* pPaintManagerUI){ m_pm = pPaintManagerUI; }
	virtual LRESULT PreMessageHandler(MSG* pMsg);
	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	virtual LRESULT TranslateAccelerator(MSG *pMsg);
	virtual void SetData(LPVOID lpData){ return; }
protected:
	virtual const MSGMAP* GetMessageMap() const;
	void Invoke(const MSGMAP* pMsg, TNotifyUI& msg);
	void Invoke(const MSGMAP* pMsg, UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
private:
	static const MSGMAP_ENTRY _messageEntries[];
protected:
	static const MSGMAP messageMap;
	CPaintManagerUI* m_pm;
};

// 变量定义
#define APP_DECLARE_MSG_MAP() \
private: \
	static const MSGMAP_ENTRY _messageEntries[]; \
protected: \
	static const MSGMAP messageMap; \
virtual const MSGMAP* GetMessageMap() const; \


// 消息数组初始化 同 APP_END_MSG_MAP配套使用 
#define APP_BEGIN_MSG_MAP(theClass, baseClass) \
	const MSGMAP* theClass::GetMessageMap() const \
{ return &theClass::messageMap; } \
	const MSGMAP theClass::messageMap = \
{ &baseClass::messageMap, &theClass::_messageEntries[0] }; \
	const MSGMAP_ENTRY theClass::_messageEntries[] = \
{ \
	

#define APP_END_MSG_MAP() \
{ \
	0,_T(""),_T(""), 0,  0 } \
}; \

// 点击消息
#define MSG_CLICK( name, func ) \
	{ 0, DUI_MSGTYPE_CLICK, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

// 控件大小改变消息
#define MSG_CTRLSIZE( name, func ) \
{ 0, DUI_MSGTYPE_CTRLSIZE, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_WINDOWSIZE( name, func ) \
	{ 0, DUI_MSGTYPE_WINDOWSIZE, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_WINDOWDESTORY( name, func ) \
{ 0, DUI_MSGTYPE_WINDOWDESTROY, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_WINDOWMOVE( name, func ) \
{ 0, DUI_MSGTYPE_WINDOWMOVE, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

//双击事件
#define MSG_ITEMDBLCLICK( name, func ) \
{ 0, DUI_MSGTYPE_ITEMDBCLICK, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

//点击元素事件
#define MSG_ITEMCLICK( name, func )\
{ 0, DUI_MSGTYPE_ITEMCLICK, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func},

// 初始化消息
#define MSG_INIWINDOW( name, func ) \
	{ 0, DUI_MSGTYPE_WINDOWINIT, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

//	选中元素消息
#define MSG_ITEMSELECTD( name, func ) \
	{ 0, DUI_MSGTYPE_ITEMSELECT, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

//	文字变化消息
#define MSG_TEXTCHANGED( name, func ) \
{ 0, DUI_MSGTYPE_TEXTCHANGED, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_MOUSEENTER( name, func ) \
{ 0, DUI_MSGTYPE_MOUSEENTER, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },
//	失去焦点
#define MSG_KILLFOCUS( name, func ) \
{ 0, DUI_MSGTYPE_KILLFOCUS, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

//右键
#define MSG_MENU( name, func ) \
{ 0, DUI_MSGTYPE_MENU, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

//	选择改变消息
#define MSG_SELECTCHANGE( name, func ) \
{ 0, DUI_MSGTYPE_SELECTCHANGED, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

// PreTranslateMessage
#define PRETRANSLATE_MSG( name, func) \
	{ name, _T(""), _T(""), _T(#func), emFunc_pre_umsg, (MSG_FUNC)(UMSG_FUNC)&func },

// TranslateAccelerator
#define TRANSLATEACC_MSG( name, func) \
	{ name, _T(""), _T(""), _T(#func), emFunc_acc_umsg, (MSG_FUNC)(UMSG_FUNC)&func },

#define USER_MSG( name, func ) \
	{ name, _T(""), _T(""), _T(#func), emFunc_uwlb, (MSG_FUNC)(bool (CNotifyUIImpl::*)(WPARAM,LPARAM,bool&))&func },

#define MSG_TIMER( name, func ) \
	{ 0, DUI_MSGTYPE_TIMER, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

//值改变消息（如进度）
#define MSG_VALUECHANGED( name, func ) \
	{ 0, DUI_MSGTYPE_VALUECHANGED, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

//值正在消息（如进度）
#define MSG_VALUECHANGING( name, func ) \
	{ 0, DUI_MSGTYPE_VALUECHANGING, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

//双击消息
#define MSG_DBCLICK( name, func ) \
	{ 0, DUI_MSGTYPE_DBCLICK, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func}, 
}

#define MSG_MOUSEENTER( name, func ) \
	{ 0, DUI_MSGTYPE_MOUSEENTER, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_MOUSELEAVE( name, func ) \
	{ 0, DUI_MSGTYPE_MOUSELEAVE, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_MOUSEMOVE( name, func ) \
	{ 0, DUI_MSGTYPE_MOUSEMOVE, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },


//拖拽
#define MSG_DRAGSTART( name, func ) \
{ 0, DUI_MSGTYPE_DRAGSTART, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_DRAGDONE( name, func ) \
{ 0, DUI_MSGTYPE_DRAGDONE, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_DRAGDROP( name, func ) \
{ 0, DUI_MSGTYPE_DRAGDROP, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_DRAGOVER( name, func ) \
{ 0, DUI_MSGTYPE_DRAGOVER, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_DRAGCANCEL( name, func ) \
{ 0, DUI_MSGTYPE_DRAGCANCEL, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_DRAGLEAVE( name, func ) \
{ 0, DUI_MSGTYPE_DRAGLEAVE, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_DRAGSCROLL( name, func ) \
{ 0, DUI_MSGTYPE_DRAGSCROLL, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },
#endif // __UIACTIVEX_H__