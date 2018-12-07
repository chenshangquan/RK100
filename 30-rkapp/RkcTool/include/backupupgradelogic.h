/** @defgroup ���������߼���Ԫ 
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

    //����Tftp�� ��ʱ����������һ����Ϣ
    void SendUpdateFirst();

protected:
    //���ñ���/����
    bool OnTabConfigurationBackup(TNotifyUI& msg);
    //�豸����
    bool OnTabEquipmentUpgrading(TNotifyUI& msg);
    //�ָ�����
    bool OnTabRestoredOriginal(TNotifyUI& msg);

    //�����ļ���ť
    bool OnBackupsBtnClick(TNotifyUI& msg);
    //�����ļ���ť
    bool OnImportBtnClick(TNotifyUI& msg);
    //ѡ�������ļ���ť
    bool OnUpgradeFilePathBtnClick(TNotifyUI& msg);
    //�ϴ���ť
    bool OnUpLoadFileBtnClick(TNotifyUI& msg);
    //�ָ�������ť
    bool OnRestoreRkBtnClick(TNotifyUI& msg);
    //��������仯
    bool OnPWEditTextChange(TNotifyUI& msg);

    bool OnUpLoadFileFirst();

    bool OnRkcRestone( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnRkcUpdateFirstAck( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnRkcUpdateFirstNty( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnRkcUpdateSecondNty( WPARAM wparam, LPARAM lparam, bool& bHandle );

    bool OnRkcDisconnected( WPARAM wparam, LPARAM lparam, bool& bHandle );

    APP_DECLARE_MSG_MAP()

private:
    CString m_strTftpFilePath;//TFtp�ļ�·��
};

#endif // !defined(AFX_BACKUPGRADE_H_)