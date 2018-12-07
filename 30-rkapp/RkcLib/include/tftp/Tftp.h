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

	/**��tftp  
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	static bool Open();
	/**�ر�tftp  
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	static bool Close();
	/**����tftp����·��  
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	static bool SetTftpPath( LPCTSTR pchPath );
	/**����Dhcp boot�ļ�  
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	static bool SetDhcpBootFile( const s8 *pchFileName );
	/**�쳣�رպ�ɱ��Tftp���� 
	 *  @param[in] 
	 *  @node 
	 *  @return 
	 */
	static bool KillTftpProcess();
private:
	/** ���ӽ��̷�����Ϣ
	 *  @param[in] dwMsgId: ��Ϣ��
	 *  @param[in] pContent: ��Ϣ����	    
	 *  @node 
	 *  @return 
	 */
	static bool SendMsgToChildProc( u32 dwMsgId, LPCSTR pContent = NULL );

private:
	/*
		����ͨ�������	
	*/
	static HANDLE s_hRead;
	/*
		����ͨ��д���
	*/
	static HANDLE s_hWrite;
	/*
	    Tftp�����Ŀ¼	
	*/
	static CString s_StrTftpDir;
	/*
	    Tftp���������ַ���
	*/
	static CString s_StrCmdLine;


};

#endif