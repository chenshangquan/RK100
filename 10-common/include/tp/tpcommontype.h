#ifndef _h_tpcommontype_h__
#define _h_tpcommontype_h__

//��¼��Ϣ
enum EmTpLoginUmsRet
{
    tp_LoginUms_sucess,
    tp_LoginUms_NameError,          //�û�������
    tp_LoginUms_PwdError,           //�������
    tp_LoginUms_MaxLogin,           //�ﵽ�û���¼����
    tp_LoginUms_Logged,             //�û��Ѿ���¼
    tp_LoginUms_steals_sucess,      //���ϳɹ�
    tp_LoginUms_steals_quit,        //��������
};

//�豸����
enum EmEquipmentType
{
    em_SinglePassiveWireless,       //��Ԫ��Դ���߿������
};

//����ģʽ
enum EmWorkingMode
{
    em_RoutineTerminal,             //�����ն�ģʽ
};

//��������
enum EmSerialPort
{
    em_com1,             //COM1
    em_com2,             //COM2
    em_com3,             //COM3
};

//��������
enum EmInfraRed
{
    em_irsent1,             //IR SENT1
    em_irsent2,             //IR SENT2
};



#endif // _h_tpcommontype_h__