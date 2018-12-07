#ifndef __APPWINDOW_H__
#define __APPWINDOW_H__

#pragma once
namespace AppFrame {

//������ʾ/���ش��� TIMER�ú�
#define TIMERID_SHOWWND_LEFT    1
#define TIMERID_HIDEWND_LEFT    2
#define TIMERID_SHOWWND_BOTTOM  3
#define TIMERID_HIDEWND_BOTTOM  4
#define TIMERID_SHOWWND_TOP     7
#define TIMERID_HIDEWND_TOP     8
#define TIMERID_SHOWMAINWND_LEFT  5
#define TIMERID_HIDEMAINWND_LEFT  6
#define WINDOW_TIMER_ELAPSE     10
#define WINDOW_MOVE_SPEED       100
#define WINDOW_MOVESTEP_COUNT   10

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

	virtual LRESULT OnActive(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	void SetPaintOnWindow( bool bPaint );

	void SetAutoHide( bool bAutoHide );
	void SetIsDelSelOnClose( bool bIsDelSelOnClose );

    /** ���ڴ��������Ƴ���ʾ������Ϊ�Ӵ��� 
	*  @param[in] bShow  ��ʾ/����
	*  @author  xcr
	*/
	void ShowWindowFromLeftToRight(bool bShow = true);
	void ShowWindowFromBottomToTop(bool bShow = true);
    void ShowWindowFromTopToBottom(bool bShow = true);
    /** �����ڴ��������Ƴ���ʾ 
	*  @param[in] bShow  ��ʾ/����
	*  @author  xcr
	*/
    void ShowMainWindowFromLeftToRight(bool bShow = true);
	//����ƶ���ʾ�Ĵ��� �ƻ�ԭ����λ�� dyy 
	void ShowWindowInitLocation();

	CPaintManagerUI m_pm;
    CDuiString		m_strSkin;
	CStdPtrArray m_aNotifiers;
	LPVOID m_pData;
	bool            m_bAutoHide;  //ʧȥ�����Զ�����
	bool            m_bIsDelSelOnClose;  //�Ƿ�close��ʱdelete���Լ� Ĭ��ɾ�� ����SetIsDelSelOnClose�����޸� dyy 2015-3-6
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
	emFunc_vv = 0,		//����void ����void
	emFunc_bn,			//����bool ����TNOTIFYUI
	emFunc_uwlb,		//����UINT ����WAPRAM LPARAM bool
};

#define MAX_EVENT_NAME_LEN		100
#define MAX_CONTROL_NAME_LEN	255
#define MAX_FUNC_NAME_LEN		255
struct MSGMAP_ENTRY
{
	unsigned int	m_dwEvent;	// ���Զ�����Ϣ���˱���Ϊ0
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
	virtual CPaintManagerUI* GetPaintManagerUI(){ return m_pm; }
	virtual LRESULT PreMessageHandler(MSG* pMsg);
	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	virtual LRESULT TranslateAccelerator(MSG *pMsg);
	virtual void SetData(LPVOID lpData){ return; }

    //
    virtual bool OnMsgNotify(TNotifyUI& msg);
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

// ��������
#define APP_DECLARE_MSG_MAP() \
private: \
	static const MSGMAP_ENTRY _messageEntries[]; \
protected: \
	static const MSGMAP messageMap; \
virtual const MSGMAP* GetMessageMap() const; \


// ��Ϣ�����ʼ�� ͬ APP_END_MSG_MAP����ʹ�� 
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

// �����Ϣ
#define MSG_CLICK( name, func ) \
	{ 0, DUI_MSGTYPE_CLICK, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

// WM_LBUTTONDOWN��Ϣ dyy 2015-3-9
#define MSG_BUTTONDOWN( name, func ) \
{ 0, DUI_MSGTYPE_BUTTONDOWN, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

// �س���Ϣ dyy 2015-4-29
#define MSG_RETURN( name, func ) \
{ 0, DUI_MSGTYPE_RETURN, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },
//letter������Ϣ
#define MSG_LETTERINDEX_CLICK( name, func ) \
{ 0, DUI_MSGTYPE_LETTERINDEX_CLICK, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },
// �ؼ���С�ı���Ϣ
#define MSG_CTRLSIZE( name, func ) \
{ 0, DUI_MSGTYPE_CTRLSIZE, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_WINDOWSIZE( name, func ) \
	{ 0, DUI_MSGTYPE_WINDOWSIZE, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_WINDOWDESTORY( name, func ) \
{ 0, DUI_MSGTYPE_WINDOWDESTROY, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_WINDOWMOVE( name, func ) \
{ 0, DUI_MSGTYPE_WINDOWMOVE, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

//˫���¼�
#define MSG_ITEMDBLCLICK( name, func ) \
{ 0, DUI_MSGTYPE_ITEMDBCLICK, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

//���Ԫ���¼�
#define MSG_ITEMCLICK( name, func )\
{ 0, DUI_MSGTYPE_ITEMCLICK, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func},

//	���Ԫ����Ϣ����������ƶ���
#define DUI_ITEMBECLICK( name, func ) \
{ 0, DUI_MSGTYPE_ITEMBECLICK, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

//���Ԫ���¼�
#define MSG_ITEMDOWN( name, func )\
{ 0, DUI_MSGTYPE_ITEMDOWN, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func},

// ��ʼ����Ϣ�������״λ���ʱ�յ�����Ϣ
#define MSG_INIWINDOW( name, func ) \
	{ 0, DUI_MSGTYPE_WINDOWINIT, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

// ��ʼ����Ϣ,���ڴ���ʱ�յ�����Ϣ
#define MSG_CREATEWINDOW( name, func ) \
{ 0, DUI_MSGTYPE_WINDOWCREATE, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

//	ѡ��Ԫ����Ϣ
#define MSG_ITEMSELECTD( name, func ) \
	{ 0, DUI_MSGTYPE_ITEMSELECT, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

//	���ֱ仯��Ϣ
#define MSG_TEXTCHANGED( name, func ) \
{ 0, DUI_MSGTYPE_TEXTCHANGED, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_MOUSEENTER( name, func ) \
{ 0, DUI_MSGTYPE_MOUSEENTER, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

//	��ý���
#define MSG_SETFOCUS( name, func ) \
{ 0, DUI_MSGTYPE_SETFOCUS, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },
//	ʧȥ����
#define MSG_KILLFOCUS( name, func ) \
{ 0, DUI_MSGTYPE_KILLFOCUS, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

//�Ҽ�
#define MSG_MENU( name, func ) \
{ 0, DUI_MSGTYPE_MENU, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

//	ѡ��ı���Ϣ
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

//ֵ�ı���Ϣ������ȣ�
#define MSG_VALUECHANGED( name, func ) \
	{ 0, DUI_MSGTYPE_VALUECHANGED, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

//ֵ������Ϣ������ȣ�
#define MSG_VALUECHANGING( name, func ) \
	{ 0, DUI_MSGTYPE_VALUECHANGING, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

//˫����Ϣ
#define MSG_DBCLICK( name, func ) \
	{ 0, DUI_MSGTYPE_DBCLICK, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func}, 

//tab��Ϣ
#define MSG_TABSELECT( name, func ) \
	{ 0, DUI_MSGTYPE_TABSELECT, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func}, 
}

#define MSG_MOUSEENTER( name, func ) \
	{ 0, DUI_MSGTYPE_MOUSEENTER, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_MOUSELEAVE( name, func ) \
	{ 0, DUI_MSGTYPE_MOUSELEAVE, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_MOUSEMOVE( name, func ) \
	{ 0, DUI_MSGTYPE_MOUSEMOVE, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

//�����ر�
#define MSG_MOVECLOSE( name, func ) \
    { 0, DUI_MSGTYPE_MOVECLOSE, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

//��ק
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

#define MSG_EDITCHANGE( name, func ) \
{ 0, DUI_MSGTYPE_TEXTCHANGED, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_DRAGENTER( name, func ) \
{ 0, DUI_MSGTYPE_DRAGENTER, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#define MSG_DRAGLEAVE( name, func ) \
{ 0, DUI_MSGTYPE_DRAGLEAVE, name, _T(#func), emFunc_bn, (MSG_FUNC)(bool (CNotifyUIImpl::*)(TNotifyUI&))&func },

#endif // __UIACTIVEX_H__