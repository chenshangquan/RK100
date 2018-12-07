#ifndef _TFTP_H_
#define _TFTP_H_

#define CMD_LINE_LEN   30
#define EV_P_C_CLOSE			1
#define EV_P_C_CHNG_TFTP_PATH	2
#define EV_P_C_CHNG_DHCP_FILE	3


typedef struct tagTftpCtrlMsg
{
	DWORD dwMsgId;
	char achContent[MAX_PATH];
}TTftpCtrlMsg;

 
class CTftpOp
{
public:

	/**打开tftp  
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	static bool Open();
	/**关闭tftp  
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	static bool Close();
	/**设置tftp共享路径  
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	static bool SetTftpPath( LPCTSTR pchPath );
	/**设置Dhcp boot文件  
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	static bool SetDhcpBootFile( const s8 *pchFileName );
	/**异常关闭后杀死Tftp进程 
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	static bool KillTftpProcess();
private:
	/** 给子进程发送消息
	 *  @param[in] dwMsgId: 消息号
	 *  @param[in] pContent: 消息内容	    
	 *  @node 
	 *  @return 
	 */
	static bool SendMsgToChildProc( u32 dwMsgId, LPCSTR pContent = NULL );

private:
	/*
		匿名通道读句柄	
	*/
	static HANDLE s_hRead;
	/*
		匿名通道写句柄
	*/
	static HANDLE s_hWrite;
	/*
	    Tftp程序的目录	
	*/
	static CString s_StrTftpDir;
	/*
	    Tftp程序命令字符串
	*/
	static CString s_StrCmdLine;


};

#endif