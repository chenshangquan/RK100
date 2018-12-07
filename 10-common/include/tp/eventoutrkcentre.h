#ifndef _h_eventoutrkcentre_h__
#define _h_eventoutrkcentre_h__

#include "rkconst.h"

enum EmRKCENTREEVENT
{
    ev_outerrkcentre_begin = EV_TP_BGN,


/***********************<< 登陆通知 >>************************	
 *[消息体]
 + TLoginRequest                登录信息
 *[消息方向]
 *      UI => rkdevice 
 */ _event( ev_rk_Login_Req )
    _body( TLoginRequest,    1 )
    _ev_end

/***********************<< 登陆反馈 >>************************	
 *[消息体]
 + TLoginRet                    登录结果
 *[消息方向]
 *      UI <= rkdevice 
 */ _event( ev_rk_Login_Rsp )
    _body(TLoginRet,    1)
    _ev_end

/***********************<<  请求修改密码 >>********************	
 *[消息体]
 + TLoginRequest                 修改内容
 *[消息方向]
 *      UI => rkdevice 
 */ _event(  ev_rk_change_password_req )
    _body( TLoginRequest,    1 )
    _ev_end	

/***********************<<   回复修改密码  >>********************	
 *[消息体]
 + TLoginRequest                 修改内容
 + BOOL32                        修改结果
 *[消息方向]
 *      UI <= rkdevice 
 */ _event(  ev_rk_change_password_rsp )
    _body( TLoginRequest,       1 )
    _body(BOOL32,               1 )
    _ev_end	

/***********************<< 射频状态通知 >>************************	
 *[消息体]
 + TRadioFrequency              射频状态
 *[消息方向]
 *      UI <= rkdevice 
 */ _event( ev_rk_radio_frequency_nty )
    _body( TRadioFrequency,    1 )
    _ev_end

/***********************<< 射频状态操作 >>************************	
 *[消息体]
 + TRadioFrequency              射频状态
 *[消息方向]
 *      UI => rkdevice 
 */ _event( ev_rk_radio_frequency_cmd )
    _body( TRadioFrequency,    1 )
    _ev_end

/***********************<< 射频状态操作反馈 >>************************	
 *[消息体]
 + TRadioFrequency              射频状态
 + BOOL32                       射频操作结果
 *[消息方向]
 *      UI => rkdevice 
 */ _event( ev_rk_radio_frequency_ind )
    _body( TRadioFrequency,     1 )
    _body( BOOL32,              1 )
    _ev_end

/***********************<< 工作模式通知 >>************************	
 *[消息体]
 + TWorkingMode                 工作模式
 *[消息方向]
 *      UI <= rkdevice 
 */ _event( ev_rk_working_mode_nty )
    _body( TWorkingMode,    1 )
    _ev_end

/***********************<< 工作模式操作 >>************************	
 *[消息体]
 + TWorkingMode                 工作模式
 *[消息方向]
 *      UI => rkdevice 
 */ _event( ev_rk_working_mode_cmd )
    _body( TWorkingMode,    1 )
    _ev_end

/***********************<< 工作模式操作反馈 >>************************	
 *[消息体]
 + TWorkingMode                 工作模式
 + BOOL32                       工作模式结果
 *[消息方向]
 *      UI => rkdevice 
 */ _event( ev_rk_working_mode_ind )
    _body( TWorkingMode,        1 )
    _body( BOOL32,              1 )
    _ev_end

//add end

        ev_outerrkcentre_end,
};
#endif 
