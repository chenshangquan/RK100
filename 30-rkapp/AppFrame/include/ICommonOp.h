// ICommonOp.h: interface for the ICommonOp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ICOMMONOP_H__DBC77325_3262_4246_BCB1_51CF05288BE7__INCLUDED_)
#define AFX_ICOMMONOP_H__DBC77325_3262_4246_BCB1_51CF05288BE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace AppFrame
{

/*
	常用操作类，都是一些静态函数
*/
class ICommonOp  
{
public:

	/**  查找控件
	 *  @param[in] 绘制管理器，控件名，启用/禁用
	 *  @node 
	 *  @return 控件指针
	 */
	template< typename T>
	static T FindControlEx(CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL )
	{
		CControlUI* pControl = FindControl(pManager, lpszControlName, pParent);
		return dynamic_cast<T>(pControl);
	}
	static CControlUI* FindControl(CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL );

	/**  启用/禁用控件
	 *  @param[in] 启用/禁用，绘制管理器，控件名，父控件
	 *  @node 
	 *  @return 是否成功
	 */
	static bool ShowControl(bool bVisible, CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL);

	/**  显示/隐藏控件
	 *  @param[in] 显示/隐藏，绘制管理器，控件名，父控件
	 *  @node 
	 *  @return 是否成功
	 */
	static bool EnableControl(bool bEnabled, CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL);

	/**  设置控件文字
	 *  @param[in] 文字，绘制管理器，控件名，父控件
	 *  @node 
	 *  @return 是否成功
	 */
	static bool SetControlText( LPCTSTR lpszText, CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL);

	/**  获取控件文字
	 *  @param[in] 绘制管理器，控件名，父控件
	 *  @node 
	 *  @return 文字字符串
	 */
	static tstring GetControlText(CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL);

	/**  设置控件背景图片
	 *  @param[in] 背景图片文件名，绘制管理器，控件名，父控件
	 *  @node 
	 *  @return 文字字符串
	 */
	static bool SetControlBkImg(LPCTSTR lpszFile, CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL);
	/**  设置控件背景颜色
	 *  @param[in] 背景颜色，绘制管理器，控件名，父控件
	 *  @node 
	 *  @return 文字字符串
	 */
	static bool SetControlBkColor(LPCTSTR lpszColor, CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL);
	
	/**  设置文字颜色  dyy 2015-6-18
	 *  @param[in] 颜色值，绘制管理器，控件名，父控件
	 *  @node 
	 *  @return 文字字符串
	 */
	static bool SetControlTextColor(LPCTSTR lpszColor, CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL);

    /**  设置Option控件选择状态
	 *  @param[in] 是否选中，绘制管理器，控件名，父控件
	 *  @node 
	 *  @return 是否成功
	 */
	static bool OptionSelectNoMsg(bool bSelect, CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL);

	/**  设置Option控件选择状态
	 *  @param[in] 是否选中，绘制管理器，控件名，父控件
	 *  @node 
	 *  @return 是否成功
	 */
	static bool OptionSelect(bool bSelect, CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL);

    /**  获取Option控件选择状态
	 *  @param[in] 绘制管理器，控件名，父控件
	 *  @node 
	 *  @return 是否选中
	 */
	static bool IsOptionSelected(CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL);

	
	/**  获取XML节点属性字符串
	 *  @param[in] 节点，标签
	 *  @node 
	 *  @return 属性字符串
	 */
	static tstring GetNodeValueStr(DocNode Node, LPCTSTR lpszTag);

	/**  判断字符串是否为数字
	 *  @param[in] 字符串
	 *  @node 
	 *  @return 是否为数字
	 */
	static bool IsDigit( LPCTSTR lpszDig );

	/**  发送界面消息
	 *  @param[in] 消息Id，消息内容指针
	 *  @node 
	 *  @return 是否成功
	 */
//	static bool NotifyUI( u16 wMsgId, UINT_PTR pData = NULL);

	/**  获取文件路径
	 *  @param[in] 提示字符串
	 *  @node 
	 *  @return 文件路径字符串
	 */
	static tstring GetFolderDir(const tstring strNotify = _T("选择文件") );

	static void StringSplit( const tstring& str, const tstring& delim, std::vector< tstring >& ret );

	static BOOL32 ModifyStyle( HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags);

	/**  设置控件tag
	*  @param[in] pControl			控件指针
	*  @param[in] tag				tag
	*  @param[in] bRecursion		是否递归设置
	*  @node
	*  @return 文件路径字符串
	*/
	static void SetTag(CControlUI* pControl, UINT_PTR tag, bool bRecursion = false);
};

} // namespace AppFrame end 

#endif // !defined(AFX_ICOMMONOP_H__DBC77325_3262_4246_BCB1_51CF05288BE7__INCLUDED_)
