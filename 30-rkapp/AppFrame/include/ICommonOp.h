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
	���ò����࣬����һЩ��̬����
*/
class ICommonOp  
{
public:

	/**  ���ҿؼ�
	 *  @param[in] ���ƹ��������ؼ���������/����
	 *  @node 
	 *  @return �ؼ�ָ��
	 */
	template< typename T>
	static T FindControlEx(CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL )
	{
		CControlUI* pControl = FindControl(pManager, lpszControlName, pParent);
		return dynamic_cast<T>(pControl);
	}
	static CControlUI* FindControl(CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL );

	/**  ����/���ÿؼ�
	 *  @param[in] ����/���ã����ƹ��������ؼ��������ؼ�
	 *  @node 
	 *  @return �Ƿ�ɹ�
	 */
	static bool ShowControl(bool bVisible, CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL);

	/**  ��ʾ/���ؿؼ�
	 *  @param[in] ��ʾ/���أ����ƹ��������ؼ��������ؼ�
	 *  @node 
	 *  @return �Ƿ�ɹ�
	 */
	static bool EnableControl(bool bEnabled, CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL);

	/**  ���ÿؼ�����
	 *  @param[in] ���֣����ƹ��������ؼ��������ؼ�
	 *  @node 
	 *  @return �Ƿ�ɹ�
	 */
	static bool SetControlText( LPCTSTR lpszText, CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL);

	/**  ��ȡ�ؼ�����
	 *  @param[in] ���ƹ��������ؼ��������ؼ�
	 *  @node 
	 *  @return �����ַ���
	 */
	static tstring GetControlText(CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL);

	/**  ���ÿؼ�����ͼƬ
	 *  @param[in] ����ͼƬ�ļ��������ƹ��������ؼ��������ؼ�
	 *  @node 
	 *  @return �����ַ���
	 */
	static bool SetControlBkImg(LPCTSTR lpszFile, CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL);
	/**  ���ÿؼ�������ɫ
	 *  @param[in] ������ɫ�����ƹ��������ؼ��������ؼ�
	 *  @node 
	 *  @return �����ַ���
	 */
	static bool SetControlBkColor(LPCTSTR lpszColor, CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL);
	
	/**  ����������ɫ  dyy 2015-6-18
	 *  @param[in] ��ɫֵ�����ƹ��������ؼ��������ؼ�
	 *  @node 
	 *  @return �����ַ���
	 */
	static bool SetControlTextColor(LPCTSTR lpszColor, CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL);

    /**  ����Option�ؼ�ѡ��״̬
	 *  @param[in] �Ƿ�ѡ�У����ƹ��������ؼ��������ؼ�
	 *  @node 
	 *  @return �Ƿ�ɹ�
	 */
	static bool OptionSelectNoMsg(bool bSelect, CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL);

	/**  ����Option�ؼ�ѡ��״̬
	 *  @param[in] �Ƿ�ѡ�У����ƹ��������ؼ��������ؼ�
	 *  @node 
	 *  @return �Ƿ�ɹ�
	 */
	static bool OptionSelect(bool bSelect, CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL);

    /**  ��ȡOption�ؼ�ѡ��״̬
	 *  @param[in] ���ƹ��������ؼ��������ؼ�
	 *  @node 
	 *  @return �Ƿ�ѡ��
	 */
	static bool IsOptionSelected(CPaintManagerUI *pManager, LPCTSTR lpszControlName, CControlUI *pParent = NULL);

	
	/**  ��ȡXML�ڵ������ַ���
	 *  @param[in] �ڵ㣬��ǩ
	 *  @node 
	 *  @return �����ַ���
	 */
	static tstring GetNodeValueStr(DocNode Node, LPCTSTR lpszTag);

	/**  �ж��ַ����Ƿ�Ϊ����
	 *  @param[in] �ַ���
	 *  @node 
	 *  @return �Ƿ�Ϊ����
	 */
	static bool IsDigit( LPCTSTR lpszDig );

	/**  ���ͽ�����Ϣ
	 *  @param[in] ��ϢId����Ϣ����ָ��
	 *  @node 
	 *  @return �Ƿ�ɹ�
	 */
//	static bool NotifyUI( u16 wMsgId, UINT_PTR pData = NULL);

	/**  ��ȡ�ļ�·��
	 *  @param[in] ��ʾ�ַ���
	 *  @node 
	 *  @return �ļ�·���ַ���
	 */
	static tstring GetFolderDir(const tstring strNotify = _T("ѡ���ļ�") );

	static void StringSplit( const tstring& str, const tstring& delim, std::vector< tstring >& ret );

	static BOOL32 ModifyStyle( HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags);

	/**  ���ÿؼ�tag
	*  @param[in] pControl			�ؼ�ָ��
	*  @param[in] tag				tag
	*  @param[in] bRecursion		�Ƿ�ݹ�����
	*  @node
	*  @return �ļ�·���ַ���
	*/
	static void SetTag(CControlUI* pControl, UINT_PTR tag, bool bRecursion = false);
};

} // namespace AppFrame end 

#endif // !defined(AFX_ICOMMONOP_H__DBC77325_3262_4246_BCB1_51CF05288BE7__INCLUDED_)
