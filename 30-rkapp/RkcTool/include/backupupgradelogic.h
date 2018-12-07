/** @defgroup 升级更新逻辑单元 
 *  @version V1.0.0
 *  @author  ylp
 *  @date    2018.10.17
 */
#if !defined(AFX_BACKUPGRADE_H_)
#define AFX_BACKUPGRADE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum EmBackupUpgradeTabID
{
    emTabID_ConfigurationBackup = 0,
    emTabID_EquipmentUpgrading,
    emTabID_RestoredOriginal,
};

class CBackupUpgradeLogic : public CNotifyUIImpl, public Singleton<CBackupUpgradeLogic> 
{
public:
	CBackupUpgradeLogic();
	~CBackupUpgradeLogic();

    //开启Tftp后 延时发送升级第一步消息
    void SendUpdateFirst();

protected:
    //配置备份/升级
    bool OnTabConfigurationBackup(TNotifyUI& msg);
    //设备升级
    bool OnTabEquipmentUpgrading(TNotifyUI& msg);
    //恢复出厂
    bool OnTabRestoredOriginal(TNotifyUI& msg);

    //备份文件按钮
    bool OnBackupsBtnClick(TNotifyUI& msg);
    //导入文件按钮
    bool OnImportBtnClick(TNotifyUI& msg);
    //选择升级文件按钮
    bool OnUpgradeFilePathBtnClick(TNotifyUI& msg);
    //上传按钮
    bool OnUpLoadFileBtnClick(TNotifyUI& msg);
    //恢复出厂按钮
    bool OnRestoreRkBtnClick(TNotifyUI& msg);
    //密码框发生变化
    bool OnPWEditTextChange(TNotifyUI& msg);

    bool OnUpLoadFileFirst();

    bool OnRkcRestone( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnRkcUpdateFirstAck( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnRkcUpdateFirstNty( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnRkcUpdateSecondNty( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnRkcDisconnected( WPARAM wparam, LPARAM lparam, bool& bHandle );

    APP_DECLARE_MSG_MAP()

private:
    CString m_strTftpFilePath;//TFtp文件路径
};

#endif // !defined(AFX_BACKUPGRADE_H_)