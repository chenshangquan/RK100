#ifndef _h_tpcommontype_h__
#define _h_tpcommontype_h__

//登录信息
enum EmTpLoginUmsRet
{
    tp_LoginUms_sucess,
    tp_LoginUms_NameError,          //用户名错误
    tp_LoginUms_PwdError,           //密码错误
    tp_LoginUms_MaxLogin,           //达到用户登录上限
    tp_LoginUms_Logged,             //用户已经登录
    tp_LoginUms_steals_sucess,      //抢断成功
    tp_LoginUms_steals_quit,        //抢断下线
};

//设备类型
enum EmEquipmentType
{
    em_SinglePassiveWireless,       //单元无源无线控制面板
};

//工作模式
enum EmWorkingMode
{
    em_RoutineTerminal,             //常规终端模式
};

//串口类型
enum EmSerialPort
{
    em_com1,             //COM1
    em_com2,             //COM2
    em_com3,             //COM3
};

//红外类型
enum EmInfraRed
{
    em_irsent1,             //IR SENT1
    em_irsent2,             //IR SENT2
};



#endif // _h_tpcommontype_h__