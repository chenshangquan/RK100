#ifndef _h_eventoutrkcentre_h__
#define _h_eventoutrkcentre_h__

#include "rkconst.h"

enum EmRKCENTREEVENT
{
    ev_outerrkcentre_begin = EV_TP_BGN,


/***********************<< ��½֪ͨ >>************************	
 *[��Ϣ��]
 + TLoginRequest                ��¼��Ϣ
 *[��Ϣ����]
 *      UI => rkdevice 
 */ _event( ev_rk_Login_Req )
    _body( TLoginRequest,    1 )
    _ev_end

/***********************<< ��½���� >>************************	
 *[��Ϣ��]
 + TLoginRet                    ��¼���
 *[��Ϣ����]
 *      UI <= rkdevice 
 */ _event( ev_rk_Login_Rsp )
    _body(TLoginRet,    1)
    _ev_end

/***********************<<  �����޸����� >>********************	
 *[��Ϣ��]
 + TLoginRequest                 �޸�����
 *[��Ϣ����]
 *      UI => rkdevice 
 */ _event(  ev_rk_change_password_req )
    _body( TLoginRequest,    1 )
    _ev_end	

/***********************<<   �ظ��޸�����  >>********************	
 *[��Ϣ��]
 + TLoginRequest                 �޸�����
 + BOOL32                        �޸Ľ��
 *[��Ϣ����]
 *      UI <= rkdevice 
 */ _event(  ev_rk_change_password_rsp )
    _body( TLoginRequest,       1 )
    _body(BOOL32,               1 )
    _ev_end	

/***********************<< ��Ƶ״̬֪ͨ >>************************	
 *[��Ϣ��]
 + TRadioFrequency              ��Ƶ״̬
 *[��Ϣ����]
 *      UI <= rkdevice 
 */ _event( ev_rk_radio_frequency_nty )
    _body( TRadioFrequency,    1 )
    _ev_end

/***********************<< ��Ƶ״̬���� >>************************	
 *[��Ϣ��]
 + TRadioFrequency              ��Ƶ״̬
 *[��Ϣ����]
 *      UI => rkdevice 
 */ _event( ev_rk_radio_frequency_cmd )
    _body( TRadioFrequency,    1 )
    _ev_end

/***********************<< ��Ƶ״̬�������� >>************************	
 *[��Ϣ��]
 + TRadioFrequency              ��Ƶ״̬
 + BOOL32                       ��Ƶ�������
 *[��Ϣ����]
 *      UI => rkdevice 
 */ _event( ev_rk_radio_frequency_ind )
    _body( TRadioFrequency,     1 )
    _body( BOOL32,              1 )
    _ev_end

/***********************<< ����ģʽ֪ͨ >>************************	
 *[��Ϣ��]
 + TWorkingMode                 ����ģʽ
 *[��Ϣ����]
 *      UI <= rkdevice 
 */ _event( ev_rk_working_mode_nty )
    _body( TWorkingMode,    1 )
    _ev_end

/***********************<< ����ģʽ���� >>************************	
 *[��Ϣ��]
 + TWorkingMode                 ����ģʽ
 *[��Ϣ����]
 *      UI => rkdevice 
 */ _event( ev_rk_working_mode_cmd )
    _body( TWorkingMode,    1 )
    _ev_end

/***********************<< ����ģʽ�������� >>************************	
 *[��Ϣ��]
 + TWorkingMode                 ����ģʽ
 + BOOL32                       ����ģʽ���
 *[��Ϣ����]
 *      UI => rkdevice 
 */ _event( ev_rk_working_mode_ind )
    _body( TWorkingMode,        1 )
    _body( BOOL32,              1 )
    _ev_end

//add end

        ev_outerrkcentre_end,
};
#endif 
