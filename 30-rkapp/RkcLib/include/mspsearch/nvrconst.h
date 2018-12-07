/*****************************************************************************
   ģ����      : nvr
   �ļ���      : nvrconst.h
   ����ļ�    : 
   �ļ�ʵ�ֹ���: NVR��������
   ����        : ������
   �汾        : V1.0  Copyright(C) 2007-2008 KEDACOM, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2007/02/11  1.0         ������       ����
   2007/05/15  1.0         ��־��       ��������޸�
   2008/11/07  2.0         �ſ���		2.0��1.0�������޸�
******************************************************************************/

#ifndef __NVRCONST_H_
#define __NVRCONST_H_
#include "kdvtype.h"

#ifndef TEST_128
#define TEST_128  (64)
#endif
//���Ȳ�������
/*******************************���º궨��Ϊ1.0��2.0ʹ�ò���ͬ�ĺ�**************************/
//**********1.0ʹ��
//const u8     MAXNUM_DVS10                    = 16  ;    //���DVS����
const u8     MAXNUM_DEC10                = 16  ;    //NVR������������
const u8     MAXNUM_ENC10					 = 16  ;    //NVR������������        1.0��ʹ��MAXNUM_DVS��
const u8     MAXNUM_DECCHN10					 = 16  ;	//NVR������ͨ���� ???
const u8     MAXNUM_ENCCHN10                 = 16  ;    //NVR������ͨ����
const u8     MAXNUM_USER10					 = 16  ;    //����û���
const u8     DECODER_BASE_ID10               = 200 ;    //��������ʼID

///////////////////////////ҵ���ڲ�ʹ��////////////////////////////////////////////////
const u8     MAXNUM_MPUSTYLE10               = 16  ;    //���MPU�����
const u8	 MAX_RECORDER_NUM10				 = 16  ;	//¼��ͨ�����������
const u8	 MAX_PLAY_NUM10					 = 20  ;	//����ͨ�����������

//����ǽ
//const u8  MAX_TVWCHN10						  =	16 ;		//TVWALL���Կ��Ƶ����ͨ����
//const u8  MAXNUM_TVWCHN10					  =	16 ;        //MPU���Կ��Ƶ����ͨ����
//const u8  MAXNUM_TVWDVS10					  =	16 ;        //�����ѯͨ����
//const u8  MAXNUM_TVWCYCLEPROJ10				  =	16 ;        //������ѯ����󷽰��� 
//const u8  MAXNUM_TVWSCHEME10				  =	16 ;        //�����ѯ������ 
//const u8  MAXNUM_TVWPROJ10					  =	16 ;		//������ǽԤ����
//const  u8 PART_MAX_NR_NVR10					  = 16 ;		//�������������������
//const u8     MAXNUM_SCHEME10                 = 16  ;    //��󷽰�����
//const u8     MAXNUM_MPUSCHEME10              = 16  ;    //���MPU����
//const u8     MAXNUM_MPUPLAN10                = 16  ;    //���MPU��ѯ�ƻ�
//const u8     MAXNUM_MPUCHN10                 = 16  ;    //���MPUͨ����
/***************************************************************************************/
//**********2.0ʹ��
//const u8     MAXNUM_DVS                    = 64  ;    //���DVS����       ??
const u8     MAXNUM_DECCHNNUM_FORONE	   = 16	 ;	  //�������������������ͨ������ 
const u8     MAXNUM_DEC					   = 64  ;    //NVR������������
const u8     MAXNUM_ENC		               = TEST_128  ;    //NVR������������
const u8     MAXNUM_DECCHN                 = 64  ;	  //NVR������ͨ���� ???
const u8     MAXNUM_ENCCHN                 = TEST_128  ;    //NVR������ͨ����  

const u8     MAXNUM_USER                   = 65  ;    //����û���,����һ��superadmin
const u8     DECODER_BASE_ID               = 128;     //��������ʼID
/***************************************************************************************/

const u8     MAXNUM_DVSCHN                 = 16  ;    //DVS���ͨ����     �����������������������ͨ������
//const u8     MAXNUM_DECODERCHN             = 5   ;    //��������ͨ����			1.0��ʹ�á�


const u8     MAXNUM_SCHEME                 = 16  ;    //��󷽰����� //ɾ��
const u8     MAXNUM_MPUSCHEME              = 16  ;    //���MPU����
const u8     MAXNUM_MPUPLAN                = 16  ;    //���MPU��ѯ�ƻ�

const u8	 MAXNUM_TVWCHN				   = 16  ;    //TVWALL���Կ��Ƶ����ͨ����
const u8	 MAXNUM_TVWDVS				   = 16  ;    //�����ѯͨ����
const u8	 MAXNUM_TVWCYCLEPROJ		   = 16  ;    //������ѯ����󷽰��� 
const u8	 MAXNUM_TVWSCHEME			   = 16  ;    //�����ѯ������ 
const u8	 MAXNUM_TVWPROJ				   = 16  ;	  //������ǽԤ���� ����Ϊ16��Ԥ��
const u8	 MAX_SYNCPLAY_NUM			   = 4   ;	  //ͬ������ͨ�����������
const u8     MAXNUM_CAMERA                 = 16  ;   //�����ƵԴ����

const u8     MAXNUM_CHNGROUP               = 16  ;    //����豸�����



const u16    MAXLEN_PUID                   = 32  ;    //PUID��󳤶�
const u8     MAXHDMI_VIDEOOUT_NUM           = 4 ;   //D04F,HDMI�������

const u16    MAX_MATRIX_VIDEOSRC_NUM       = 16;      // ��������������˿��� 
const u16	 MAXNUM_FILE			       = 800;     //ץ������ļ��б����

const u8	 MAXLEN_NAME                   = 32  ;   //�豸����
const u8     MAXLEN_ALIAS                  = 32  ;   //��������
const u8	 MAXLEN_GUID                   = 32  ;   //GUID����
const u8     MAXLEN_PATH                   = 255 ;   //���·������
const u8     MAXLEN_USERNAME               = 32  ;   //����û�������
const u8     MAXLEN_PWD                    = 32  ;   //������볤��
const u8     MAXLEN_EMAIL                  = 63  ;   //E-mail֧������ַ�
const u8     MAXLEN_TEL                    = 23  ;   //�绰������󳤶�
const u8     MAXLEN_OSD                    = 64+1;   //����OSD����,��VSIPЭ��ջһ��
const u16    MAXLEN_MSGHDR                 = 24  ;   //�����Ϣͷ����  CNvrMsgר��
const u16    MAXLEN_MSG                    = 0x4000   ;//�����Ϣ�峤��
const u8     MAXLEN_FILELEN                = 255 ;   //����ļ�������
const u8     MAXLEN_LOG                    = 255 ;   //�����־����
const u16    MAXLEN_SELFDEFBUF             = 1024;   //�Զ������Ϣbuf����
const u8     MAXLEN_LIST                   = 255 ;   //�ʼ�����ַ�б��
const u8     MAXLEN_DESC                   = 255 ;   //��������󳤶�
const u8     MAXLEN_ENCRYPTKEY             = 128 ;   //��Կ����󳤶�
const u8     MAXNUM_NET_PORT               = 6   ;    //���������Ŀ
const u8	 MAXNUM_IP					   = 8	 ;	  //һ�����ڿ������õ�IP��
const u8     MAXNUM_MD_AREA                = 16  ;    //����ƶ�����������
const u8     MAXNUM_WEEK_DAY               = 7   ;    //һ���������
const u8     MAXNUM_DAY_TIMESEG            = 4   ;    //һ�����ʱ��Ƭ
const u8     MAXNUM_HARDDISK               = 16  ;    //���Ӳ�̸���
const u8     MAXNUM_ALARMIN                = 16  ;    //��󱨾�����
const u8     MAXNUM_ALARMOUT               = 16  ;    //��󱨾����
const u8     MAXNUM_EQP                    = 36  ;    //����豸��
const u8     NVR_MAXNUM_ALARMIN            = 18  ;    //��󱨾�����
const u8     NVR_MAXNUM_ALARMOUT           = 10  ;    //��󱨾����
const u16    REC_BACK_SECTION_TIME         = 30 * 60; //¼�񱸷ݷֶμ��ʱ�䣨s��
const u8	 BAKTYPEINIT				   = 0;		  //��ʼ���ݣ�ҵ��Ĭ����Ϊ����ASF����
const u8	 BAKTYPERAWDATA				   = 1;		  //����������
const u8	 BAKTYPEMP4					   = 2;		  //����MP4
const u8	 BAKTYPEASF					   = 3;		  //����ASF
const u8	 BAKTYPEM4A					   = 4;		  //����M4A
const u8     REC_BACK_ADJUST_TIME          = 3;       //¼�񱸷ݽ�����У��ʱ��
#if defined(_NVR2860_) || defined(_NVR2821H_)
	const u8     MAXNUM_NC                     = 68  ;    //���ͻ����� ԭ����17�����ڸ�Ϊ68
#else
	const u8     MAXNUM_NC                     = 17  ;    //���ͻ�����
#endif
	const u8	 SWITCH_ID					   =  MAXNUM_NC + 2; //���뿪��<2012_2_24 KSW>

const u8     MAXNUM_PUI                    = 2   ;    //���PUI��
//const u8     MAXNUM_NCCHN                  = 72  ;    //NC���ͨ����
const u8     MAXNUM_NCCHN                  = 128  ;    //NC���ͨ����
const u8     MAXNUM_VIDSRCCHN              = 16  ;    //DVS�����ƵԴͨ����
const u8     MAXNUM_SEARCH                 = 250 ;    //���������
const u8     MAX_VSIP_NUM_NTY_EVERYTIME    = 128 ;    //һ������ϱ���VSIP���������豸��Ŀ
const u8     MAX_ONVIF_NUM_NTY_EVERYTIME   = 25  ;    //һ������ϱ���ONVIF���������豸��Ŀ
const u8     MAXNUM_TIMESEG                = 57 ;     //��ʱ�����ڵ�ʱ�������
const u16    MAX_COMDATA_LEN               = 512 ;    //��󴮿����ݳ���
const u16	 MAX_TAG_LEN				   = 32 ;  	  //��ǩ����󳤶�
const u16	 MAXLEN_ALAMADUIOFL			   = 32 ;     //�澯��Ƶ�ļ���	
const u16	 MAXNUM_SA_AREA				   = 16 ;     //ͼ��������������
const u16	 MAX_NVR_PICFILE_PACK_LEN	   = 4096;    //ץ��ͼƬ������󳤶�
#ifdef _NVR2820L_
const u8	 MAX_DVSREC_NUM				   = 4	;	  //ǰ��¼��ͨ�����������
const u8	 MAX_DVSPLY_NUM				   = 16 ;	  //ǰ�˷���ͨ�����������
#else
const u8	 MAX_DVSREC_NUM				   = TEST_128	;	  //ǰ��¼��ͨ�����������
const u8	 MAX_DVSPLY_NUM				   = 64 ;	  //ǰ�˷���ͨ�����������
#endif
const u16    MAX_PU_LOGO_PACK_LEN          = 1024;    //���̨���ļ�������
const u16    CUR_PC_UNIT				   = 1024;	  //ͨ���Ļ��㵥λ
const u16    MAX_LANG_NUM				   = 2;       //���֧�ֵ�������
const u16    MAX_DESC_NUM                  = 1000;    //���������
const u16	 MAX_SERVNAME_LEN			   = 255;	  //PPOE���ŷ����̵����ֳ���
const u8	 MAX_AUDIOIN_PORT_NAME_LEN	   = 8 ;      //�����Ƶ����˿�������   
const u8	 MAX_VERSION_NUM_LEN		   = 64 ;     //�汾����󳤶�	
const u8	 MAX_PROOFPASSWORD_LEN		   = 64 ;	  //�����֤���볤��
const u8	 MAX_WEBUSERNAME_LEN		   = 64 ;	  //�����֤���볤��
const u16    MAX_DDNSSTATE_LEN             = 4096;     //����ddns״̬�ַ����ĳ���
const u16	 MAXNUM_CUR_ALARM			   = 255;	  //��ǰ�澯���ʱ��Ŀ
const u8	 MAXLEN_IPSTR				   = 15	;    //ip�ַ����ĳ���
const u8	 MAXLEN_FILENAME			   = 250;     //����ļ�������
const u8	 MAXLEN_FILEPATH               = 250;    //���·��������
const u8	 MAXLEN_BAKFILENAME			   = 70;	 //����ļ�������
const u16 	 MAXLEN_CONTENT  		       = 255;		//
const u8     MAX_DEV_INFO_LEN              = 128 ;    //������Ϣ��󳤶�

//ҵ��APP�Ŷ���
const u8     AID_NVR_EQPSSN                = 15  ;		//nvr�豸�Ự  // ԭ��18==>15 ͬ[SnmpAdp][SAgtSsnInst.1]��ͻ [10/16/2008 zhangkehui]
const u8     AID_NVR_SERVICE               = 16  ;		//nvrҵ��
const u8     AID_NVR_GUARD                 = 17  ;		//nvr����
const u8     AID_NVR_EQPSSN10              = 18  ;	//nvr�豸�Ự
const u8     AID_NVR_NCSSN                 = 19  ;		//nvr���ؽ��ܿͻ�����Ϣ�ĻỰ
const u8     AID_NVR_PUISSN                = 20  ;		//nvrǰ�˽���Ự
const u8     AID_NVR_VTDUSSN               = 21  ;		//nvr�ַ�ת���Ự
const u8     AID_PUI_EXTSSN                = 22  ;		//nvr�ַ�ת���Ự
const u8	 AID_NCLIB_APP				   = 27	 ;		//nclib�Ự	
const u8	 AID_WMS_APP				   = 28  ;		//wvms�Ự
const u8     AID_NVR_EQP                   = 30  ;		//nvr�豸�Ự
//const u8   AID_NVR_NC		               = 31  ;		//nvr�ͻ��˻Ự
const u8     AID_NVR_PUI                   = 32  ;		//nvrǰ�˽���Ự
const u8     AID_NVR_VTDU                  = 33  ;		//nvr�ַ�ת���Ự
const u8	 AID_NVR_DM					   = 34  ;		//���̹���Ự
const u8     AID_NVR_CMSI                  = 35  ;      //nvrƽ̨����ģ��
const u8     AID_NVR_CMSISSN               = 36  ;      //nvrƽ̨����ģ��Ự(nvrҵ���)
const u8	 AID_NVR_PS					   = 37  ;		//����ͬ���Ự
const u8     AID_NVR_RBQ				   = 38  ;		//¼�����ݲ�ѯ����
const u8     AID_NVR_LOG                   = 40  ;      //nvr��־
const u8     AID_NVR_TEST                  = 41  ;      //nvr ����
const u8     AID_PTFIX_APP                 = 42  ;      //�����޸�
const u8     AID_NVR_PTFSSN                = 43  ;      //�����޸��Ự
const u8     AID_TEST_NVR				   = 44;		  //TEST�ĻỰ
const u8     AID_NVR_TEST2				   = 45  ;		  //NVR��TEST�����ĻỰ
const u8     AID_NVR_ANR				   = 46	 ;		 //ANRģ��APP
const u8     AID_NVR_DSCHK				   = 47	 ;		 //DSCHECKģ��APP
const u8     AID_NVR_GRB				   = 48	 ;		 //GRBģ��APP
const u8     AID_DS_KEEPALIVE			   = 49	 ;		 //DS keepalive ����ģ��APP
const u8     AID_WD_MONITOR		           = 50	 ;		 //watch dog����APP
const u8	 AID_DEVRAID_APP			   = 51	 ;		//�������з���APP
const u8     AID_PUI_EXT                   = 52  ;		//PuiEXT(Pui��չ)ģ��APP
const u8     AID_NVR_ONDS                  = 53  ;      //��nvr������־
const u8     AID_NVR_ONDSSN                = 54  ;      //��nvr������־nvr session
const u8     AID_GBPROXY_SRVNVR            = 55  ;      //��������ŷ�NVRģ��APP
const u8     AID_GBPROXY_SRVCM             = 56  ;      //��������ŷ�ƽ̨ģ��APP

const u8	 AID_VTDU	                   = 67	 ;      //VTDU
const u8	 AID_MONITOR				   = 73	 ;		// ���ӳ���
const u8	 AID_DI_APP					   = 77	 ;		//web������Ϣ�Ự
const u8	 AID_NVR_SMTP				   = 78	 ;		//web������Ϣ�Ự

const u8     LOG_MODULE_NUM                = 10  ;		//��־ģ�����Ŀ
const u8	 PUI_ID						   = 1   ;
const u8	 VTDU_ID					   = 1   ;
const u8	 PUI_EXT_ID					   = 1   ;

const u8	 ONDS_ID					   = 1   ;

//����ͼ����������ģʽ
const u8	 MODE_NONE			           = 0	 ;     //����Ƶ������
const u8	 MODE_VIDEO					   = 1	 ;     //ֻ����Ƶ
const u8	 MODE_AUDIO					   = 2	 ;     //����Ƶ
const u8	 MODE_BOTH					   = 3   ;     //����Ƶ����

//��־��ӡ����
const u8     LOGLVL_EXCEPTION	           = 1	 ;     //�쳣
const u8     LOGLVL_IMPORTANT	           = 100 ;     //��Ҫ��־
const u8     LOGLVL_DEBUG1	               = 150 ;     //һ��������Ϣ
const u8     LOGLVL_DEBUG2		           = 200 ;     //����������Ϣ

//�豸���̶���
const u8     DEVMANU_UNKNOW                = 0   ;     //δ֪
const u8     DEVMANU_KEDACOM               = 1   ;     //�ƴ�Ƽ�
const u8	 DEVMANU_SUNELL				   = 2	 ;	   //����
const u8	 DEVMANU_SONY				   = 3   ;     //����

 //������������
const u8    UNICAST                        = 1   ;      //����
const u8    DIRECTTRANS                    = 2   ;      //����ֱ��
const u8    MULTICAST                      = 3   ;      //�鲥   

//VDTU�Ľ�����������
const u8   M2P                             = 0   ;      //���1 
const u8   P2P                             = 1   ;      //��Ե�

//�澯����
//�澯����
const u8  ALARMTYPE_PININPUT               = 1   ;    //��������澯
const u8  ALARMTYPEE_MOVDET                = 2   ;    //�ƶ����澯
const u8  ALARMTYPEE_RESERVED1             = 3   ;    //�澯1[����]
const u8  ALARMTYPEE_RESERVED2             = 4   ;    //�澯2[����]

//�澯��־
const u8 ALARMRESUME                       = 0   ;    //�澯�ָ�
const u8 ALARMOCCUR                        = 1   ;    //�澯���� 

//����ͷ��������
//����ͷ�������
const u8 CAMCTRL_COMMAND_MOVEUP	=  1 ;	//�����ƶ�
const u8 CAMCTRL_COMMAND_MOVEDOWN	=  2	;	//�����ƶ�
const u8 CAMCTRL_COMMAND_MOVELEFT	=  3	;	//�����ƶ�
const u8 CAMCTRL_COMMAND_MOVERIGHT	=  4	;	//�����ƶ�
const u8 CAMCTRL_COMMAND_MOVEHOME	=  5	;	//�ع�
const u8 CAMCTRL_COMMAND_MOVESTOP	=  6	;	//ֹͣ�ƶ�
const u8 CAMCTRL_COMMAND_ZOOMTELE	=  7	;	//��������ͷ
const u8 CAMCTRL_COMMAND_ZOOMWIDE	=  8	;	//��Զ����ͷ
const u8 CAMCTRL_COMMAND_ZOOMSTOP	=  9	;	//��Ұ����ֹͣ
const u8 CAMCTRL_COMMAND_FOCUSFAR	=  10   ;	//�������Զ
const u8 CAMCTRL_COMMAND_FOCUSNEAR	=  11   ;	//���������
const u8 CAMCTRL_COMMAND_FOCUSAUTO	=  12   ;	//�Զ�����
const u8 CAMCTRL_COMMAND_FOCUSSTOP	=  13   ;	//����ֹͣ
const u8 CAMCTRL_COMMAND_PRESETSET	=  14   ;	//����ͷԤ��
const u8 CAMCTRL_COMMAND_PRESETCALL	=  15	;	//������ͷԤ��
const u8 CAMCTRL_COMMAND_CAMERASET	=  16   ;	//��ʼ������ͷ
const u8 CAMCTRL_COMMAND_BRIGHTUP	=  17   ;	//�������
const u8 CAMCTRL_COMMAND_BRIGHTDOWN	=  18   ;	//�������
const u8 CAMCTRL_COMMAND_BRIGHTSTOP	=  19   ;	//ֹͣ����
const u8 CAMCTRL_COMMAND_NEW		=  20   ;	//������
const u8 CAMCTRL_COMMAND_APPEND		=  21	;	//��������
const u8 CAMCTRL_COMMAND_QUERYPANPOS	=  22 ; //��ѯˮƽ��λ��
const u8 CAMCTRL_COMMAND_QUERYTILPOS	=  23 ; //��ѯ��ֱ��λ��
const u8 CAMCTRL_COMMAND_QUERYZOMPOS =  24  ;	//��ѯ�Ŵ���  ??

const u8 CAMCTRL_COMMAND_STARTAUTOSCAN = 24 ;   //��ʼ�Զ�Ѳ��	
const u8 CAMCTRL_COMMAND_STOPAUTOSCAN  = 25 ;   //ֹͣ�Զ�Ѳ��

const u8 CAMCTRL_COMMAND_STARTTOUR     = 26 ;    //Ѳ�ӿ�ʼ
const u8 CAMCTRL_COMMAND_ENDTOUR       = 27 ;    //Ѳ�ӽ���

const u8 CAMCTRL_COMMAND_SETHOMEPOS	   = 28 ;	 //����HOMEλ

const u8 CAMCTRL_COMMAND_MENU_UP     = 35;		//�˵���
const u8 CAMCTRL_COMMAND_MENU_DOWN   = 36;		//�˵���
const u8 CAMCTRL_COMMAND_MENU_LEFT   = 37;		//�˵���
const u8 CAMCTRL_COMMAND_MENU_RIGHT  = 38;		//�˵���

const u8 CAMCTRL_COMMAND_MENU_SHOW   = 39;		//�˵���ʾ
const u8 CAMCTRL_COMMAND_MENU_HIDE   = 40;		//�˵�����

const u8 CAMCTRL_COMMAND_MENU_ENTER  = 41;		//�˵�ȷ��
const u8 CAMCTRL_COMMAND_MENU_EXIT   = 42;		//�˵�ȡ��

const u8 CAMCTRL_COMMAND_IMAGE_SHOW  = 43;      // ͼ������ʾ
const u8 CAMCTRL_COMMAND_IMAGE_ANTISHOW = 44;   // ͼ����ʾ

const u8 CAMCTRL_COMMAND_GOTOPOINT   = 45;      // �������
const u8 CAMCTRL_COMMAND_ZOOMPART    = 46;      // �ֲ��Ŵ�
const u8 CAMCTRL_COMMAND_ZOOMWHOLE   = 47;      // �ֲ���С

const u8 CAMCTRL_COMMAND_BACKLIGHT_ON    = 48;    // ���⿪
const u8 CAMCTRL_COMMAND_BACKLIGHT_OFF   = 49;    //  �����

const u8 CAMCTRL_COMMAND_WIDEDYNAMIC_ON    = 50;    // ��̬��
const u8 CAMCTRL_COMMAND_WIDEDYNAMIC_OFF   = 51;    // ��̬��

const u8 CAMCTRL_COMMAND_DAYNIGHTMOD_ON    = 52;    // ��ҹģʽ��
const u8 CAMCTRL_COMMAND_DAYNIGHTMOD_OFF    = 53;    // ��ҹģʽ��
const u8 CAMCTRL_COMMAND_DAYNIGHTMOD_AUTO   = 54;    // ��ҹģʽ�Զ�

const u8 CAMCTRL_COMMAND_HORIZONTAL_TURN = 55;        // ��̨ˮƽ180�ȷ�ת
const u8 CAMCTRL_COMMAND_TURNTO_MACHINEZERO = 56;           // ˮƽ���������ת������λ����λУ��,����е��λ��
const u8 CAMCTRL_COMMAND_LIMIT_HORIZONALLEFT = 57;          // ˮƽ����λ
const u8 CAMCTRL_COMMAND_LIMIT_HORIZONALRIGHT = 58;          // ˮƽ����λ
const u8 CAMCTRL_COMMAND_PRESET_REMOVE = 59;                 // ���Ԥ��λ
const u8 CAMCTRL_COMMAND_AUXILIARYSWITCH_SET = 60;           //  ������������
const u8 CAMCTRL_COMMAND_AUXILIARYSWITCH_REMOVE = 61;        // �����������
const u8 CAMCTRL_COMMAND_ALARMINPUT_QUERY = 62;              // �ƴ��ѯ����������Ϣ,�ݲ�֧��
const u8 CAMCTRL_COMMAND_VIRTUALZERO_SET  = 63;              // ������λ����
const u8 CAMCTRL_COMMAND_VIRTUALZERO_REMOVE = 64;            // ������λ���
const u8 CAMCTRL_COMMAND_PTZ_RESET = 65;                     // �ƴ﷢����̨��λ
const u8 CAMCTRL_COMMAND_ZOOMINFO_SEND =66;                 //�ƴ﷢�ͱ䱶��Ϣ 
const u8 CAMCTRL_COMMAND_CAMERATYPE_SEND = 67;               // �ƴ﷢���������
const u8 CAMCTRL_COMMAND_AUTOFLIP_ON = 68;                   // �Զ���ת��
const u8 CAMCTRL_COMMAND_AUTOFLIP_OFF = 69;                  // �Զ���ת��
const u8 CAMCTRL_COMMAND_DEPTHRATESPEED_ON = 70;              //��������ٶȿ�
const u8 CAMCTRL_COMMAND_DEPTHRATESPEED_OFF = 71;             //��������ٶȹ�
const u8 CAMCTRL_COMMAND_SCANSPEED_SET = 72;                 //ˮƽɨ���ٶȣ�Ӱ���Զ�ɨ���ٶȣ�bySpeed(1-40s)
const u8 CAMCTRL_COMMAND_MANUALLIMITSWITCH_ON = 73;           //�ֶ���λ��
const u8 CAMCTRL_COMMAND_MANUALLIMITSWITCH_OFF = 74;          //�ֶ���λ��
const u8 CAMCTRL_COMMAND_SCANLIMITSWITCH_ON = 75;             //ɨ����λ��
const u8 CAMCTRL_COMMAND_SCANLIMITSWITCH_OFF = 76;            //ɨ����λ��
const u8 CAMCTRL_COMMAND_PANPOSION_SET = 77;                  //��λ������ˮƽλ��
const u8 CAMCTRL_COMMAND_TILTPOSION_SET = 78;                 //��λ�����ø���λ��
const u8 CAMCTRL_COMMAND_PANPOSION_QUERY = 79;                //��λ����ѯˮƽλ��
const u8 CAMCTRL_COMMAND_TILTPOSION_QUERY = 80;               //��λ����ѯ����λ��
const u8 CAMCTRL_COMMAND_PANRESPONSE_QUERY = 81;              //�������ˮƽλ��
const u8 CAMCTRL_COMMAND_TILTRESPONSE_QUERY = 82;             //������ظ���λ��
const u8 CAMCTRL_COMMAND_FOCUSMODE_AUTO = 83;                 //�۽�ģʽ�Զ�
const u8 CAMCTRL_COMMAND_FOCUSMODE_MANUAL = 84;              //�۽�ģʽ�ֶ�
const u8 CAMCTRL_COMMAND_IMAGE_LEFTRIGHT_REVERSE = 85;        //ͼ�����ҷ�ת
const u8 CAMCTRL_COMMAND_IMAGE_UPDOWN_REVERSE = 86;         //ͼ�����·�ת
//const u8 CAMCTRL_COMMAND_BACKLIGHT_ON = 87;                   //���ⲹ����
//const u8 CAMCTRL_COMMAND_BACKLIGHT_OFF = 88;                  //���ⲹ����
const u8 CAMCTRL_COMMAND_STARVEMODE_ON = 89;                 //��Ƶ���Ὺ
const u8 CAMCTRL_COMMAND_STARVEMODE_OFF = 90;                 //��Ƶ�����
const u8 CAMCTRL_COMMAND_ZOOM_LIMIT = 91;                     //�䱶����(1-18)
const u8 CAMCTRL_COMMAND_ZOOMSPEED_FAST = 92;                 //�䱶�ٶȿ���
const u8 CAMCTRL_COMMAND_ZOOMSPEED_NORMAL = 93;               //�䱶�ٶ�����
const u8 CAMCTRL_COMMAND_APERTUREMODE_AUTO = 94;             //��Ȧģʽ�Զ�
const u8 CAMCTRL_COMMAND_APERTUREMODE_MANUAL_HIGHSPEED = 95;  //��Ȧģʽ�ֶ�����
const u8 CAMCTRL_COMMAND_APERTUREMODE_MANUAL_MODERATESPEED=96;//��Ȧģʽ�ֶ�����
const u8 CAMCTRL_COMMAND_APERTUREMODE_MANUAL_LOWSPEED = 97;   //��Ȧģʽ�ֶ�����
const u8 CAMCTRL_CMMMAND_SHUTTERMODE_AUTO = 98;               //����ģʽ�Զ�
const u8 CAMCTRL_COMMAND_SHUTTERMODE_MANUAL=99;             //����ģʽ�ֶ�
const u8 CAMCTRL_COMMAND_PLUSMODE_AUTO = 100 ;                 //����ģʽ�Զ�
const u8 CAMCTRL_COMMAND_PLUSMODE_MANUAL = 101;                //����ģʽ�ֶ�
const u8 CAMCTRL_COMMAND_WHITEBALANCEMODE_AUTO=102;          //��ƽ��ģʽ�Զ�
const u8 CAMCTRL_COMMAND_WHITEBALANCEMODE_MANUAL=103;        //��ƽ��ģʽ�ֶ�

const u8 CAMCTRL_COMMAND_ALL_AUTO = 104;                       //��оȫ�Զ�
const u8 CAMCTRL_COMMAND_WIPER_ON = 105;                       //��ˢ����
const u8 CAMCTRL_COMMAND_WIPER_OFF = 106;                     //��ˢ�ر�
const u8 CAMCTRL_COMMAND_IR_ON = 107;                         //���⿪��
const u8 CAMCTRL_COMMAND_IR_OFF = 108;                         //����ر�

const u8 CAMCTRL_COMMAND_MOVE_LEFTUP        =  131    ;	//�������ƶ�
const u8 CAMCTRL_COMMAND_MOVE_LEFTDOWN	    =  132    ;	//�������ƶ�
const u8 CAMCTRL_COMMAND_MOVE_RIGHTUP	    =  133    ;	//�������ƶ�
const u8 CAMCTRL_COMMAND_MOVE_RIGHTDOWN	    =  134    ;	//�������ƶ�
const u8 MAX_UPDATE_PKG_NUM  = 32 ; //����������
const u8 MAX_CHN_NUM_ONE				= 1  ;	//ͨ����Ŀ�޶�
const u8 MAX_CHN_NUM_TWO				= 2  ;	//ͨ����Ŀ�޶�

const u8 MAX_CHN_NUM_FOUR				= 4  ;	//ͨ����Ŀ�޶�
const u8 MAX_CHN_NUM_NINE				= 9  ;	//ͨ����Ŀ�޶�
const u8 MAX_CHN_NUM_SIXTEN				= 16  ;	//ͨ����Ŀ�޶�

const u8 MAX_CHN_NUM_TWOFIVE				= 25  ;	//ͨ����Ŀ�޶�
const u8 MAX_CHN_NUM_THREETWO				= 32  ;	//ͨ����Ŀ�޶�
const u8 MAX_CHN_NUM_THREESIX				= 36  ;	//ͨ����Ŀ�޶�
const u8 MAX_CHN_NUM_FOURNINE				= 49  ;	//ͨ����Ŀ�޶�
const u8 MAX_CHN_NUM_SIXFOUR				= 64  ;	//ͨ����Ŀ�޶�

const u8 MAX_CHN_NUM_EIGHT					= 8;	//ͨ����Ŀ�޶�
const u8 MAX_CHN_NUM_TWELVE					= 12;	//ͨ����Ŀ�޶�
const u8 MAX_CHN_NUM_TWITY					= 20;	//ͨ����Ŀ�޶�
const u8 MAX_CHN_NUM_TWITYFOUR				= 24;	//ͨ����Ŀ�޶�
const u8 MAX_CHN_NUM_TWITYEIGHT				= 28;	//ͨ����Ŀ�޶�

//Ӳ��code
const u8 KDM2820_4						= 0x2b ;
const u8 KDM2820_9						= 0x2c ;
const u8 KDM2820_16						= 0x2d ;
const u8 KDM2820E_9						= 0x2e ;
const u8 KDM2820E_16					= 0x2f ;

const u8 KDM2820EA_16					= 0x50 ;
const u8 KDM2820EA_9					= 0x51 ;
const u8 KDM2820EA_4					= 0x52 ;

const u8 KDM2820E_G_16					= 0x53 ;
const u8 KDM2820E_G_9					= 0x54 ;
const u8 KDM2820E_G_4					= 0x55 ;

const u8 KDM2820HND_16					= 0x56 ;

const u8 KDM2860_16						= 0x30 ;
const u8 KDM2860_32						= 0x31 ;
const u8 KDM2860_48						= 0x32 ;
const u8 KDM2860_64						= 0x33 ;

const u8 KDM2840_9						= 0x34;
const u8 KDM2840_16						= 0x35;
const u8 KDM2840_32						= 0x36;
const u8 KDM2840_4						= 0x44;
const u8 KDM2840_4HD_new				= 0x45;

const u8 KDM201s_4						= 0x37;
const u8 KDM201s_8						= 0x38;
const u8 KDM201s_16						= 0x39;
const u8 KDM201s_20						= 0x40;
const u8 KDM201s_24						= 0x41;
const u8 KDM201s_28						= 0x42;
const u8 KDM201s_12						= 0x43;

// suker modify u8->u32, the data is bigger than 0xff
const u32 KDM201se_4						= 0x2037;
const u32 KDM201se_8						= 0x2038;
const u32 KDM201se_16						= 0x2039;
const u32 KDM201se_20						= 0x2040;
const u32 KDM201se_24						= 0x2041;
const u32 KDM201se_28						= 0x2042;
const u32 KDM201se_12						= 0x2043;
const u32 KDM201se_32						= 0x2044;

//2880 8272-8275
const u32 KDM2880_16					= 0x2050;
const u32 KDM2880_32					= 0x2051;
const u32 KDM2880_48					= 0x2052;
const u32 KDM2880_64					= 0x2053;
const u32 KDM2880_128					= 0x2054;
const u32 KDM2880_96					= 0x2055;
//2860E
const u32 KDM2860E_64					= 0x2060;
const u32 KDM2860E_16					= 0x2061;
const u32 KDM2860E_32					= 0x2062;
const u32 KDM2860E_48					= 0x2063;

//1821
const u32 KDM1821_32					= 0x2070;
const u32 KDM1821_16					= 0x2071;
const u32 KDM1821_9						= 0x2072;
const u32 KDM1821_4						= 0x2073;
//1822
const u32 KDM1822_32HD					= 0x2080;
const u32 KDM1822_16HD					= 0x2081;
const u32 KDM1822_9HD					= 0x2082;
const u32 KDM1822_4HD					= 0x2083;

const u32 KDM1822_32ND					= 0x2090;
const u32 KDM1822_16ND					= 0x2091;
const u32 KDM1822_9ND					= 0x2092;

const u32 KDM1822_16HDA					= 0x2100;
const u32 KDM1822_9HDA					= 0x2101;
const u32 KDM1822_4HDA					= 0x2102;

//1825
const u32 KDM1825_9HD					= 0x2110;
const u32 KDM1825_4HD					= 0x2111;
const u32 KDM1825_9HP					= 0x2120;
const u32 KDM1825_4HP					= 0x2121;
const u32 KDM1825_4HDA					= 0x2130;
const u32 KDM1825_4HPA					= 0x2140;
const u32 KDM1825_16HD					= 0x2112; //16hd

const u32 PID_KDM201_D01F				= 0x10A5;
const u32 PID_2510_D01F					= 0x10A6;
//kdm-d01f
const u32 KDM201_D01F_NEW				= 0x2150;
const u32 KDM2510_D01F_NEW				= 0x2151;

//2821H(1037)
const u32 KDM2821H_64					= 0x2160;
const u32 KDM2821H_4					= 0x2161;
const u32 KDM2821H_9					= 0x2162;
const u32 KDM2821H_16					= 0x2163;
const u32 KDM2821H_32					= 0x2164;
const u32 KDM2821H_48					= 0x2165;

//1821(1037)
const u32 KDM1821_1037_64				= 0x2170;
const u32 KDM1821_1037_4				= 0x2171;
const u32 KDM1821_1037_9				= 0x2172;
const u32 KDM1821_1037_16				= 0x2173;
const u32 KDM1821_1037_32				= 0x2174;
const u32 KDM1821_1037_48				= 0x2175;

//Ӳ��hwid
const u32 HWID_NVR2882					= 0x01F9;
const u32 HWID_NVR2860					= 0x0101;
const u32 HWID_NVR201S					= 0x0103;
const u32 HWID_NVR2840					= 0x0107;
const u32 HWID_NVR2820L					= 0x0118;
const u32 HWID_NVR2820A					= 0x0127;

const u32 HWID_NVRD01					= 0x0112;
const u32 HWID_NVR2880 					= 0x0121;
const u32 HWID_NVR2840_4HD				= 0x0130;
const u32 HWID_NVR2840_4HD_NEW			= 0x0131;

//const u32 HWID_NVR1821_2821H			= 0x015C;		//NVR1821��NVR2821Hʹ����ͬ��HWID
//const u32 HWID_NVR1821                  = HWID_NVR1821_2821H; //�ͻ��˼���������
const u32 HWID_NVR2821H					= 0x0190;
const u32 HWID_NVR1821                  = 0x015C;
const u32 HWID_NVR1821_1037				= 0x0191;

const u32 HWID_NVR1822					= 0x016E;
const u32 HWID_NVR1825					= 0x016F;

const u32 HWID_KDMD01F					= 0x0164;

const u32 HWID_KDMD04F					= 0x018F;
const u32 PID_KDM201_D04F				= 0x10FD;
const u32 PID_KDM2510_D04F				= 0x10FE;
const u32 HWID_NVR2820EA_2860E 				= 0x0122;

const u32 HWID_NVR2820H16ND					= 0x0155;

const u32 HWID_NVR2822H_4               = 0x015F;
const u32 HWID_NVR2822H_91632           = 0x0160;
//�豸product id
const u32 PID_NVR2822H_4HD                           = 0x109B;
const u32 PID_NVR2822H_4ND                           = 0x109C;
const u32 PID_NVR2822H_4HD_P                         = 0x109D;
const u32 PID_NVR2822H_4ND_P                         = 0x109E;
const u32 PID_NVR2822H_91632HD                       = 0x109F;
const u32 PID_NVR2822H_91632ND                       = 0x10A0;

const u32 PID_NVR1822_91632HD                        = 0x10B1;
const u32 PID_NVR1822_91632ND                        = 0x10B2;
const u32 PID_NVR1822_4916HDA                        = 0x10B3;

const u32 PID_NVR1825_49HD                           = 0x10B4;
const u32 PID_NVR1825_49HP                           = 0x10B5;
const u32 PID_NVR1825_4HDA                           = 0x10B6;
const u32 PID_NVR1825_4HPA                           = 0x10B7;
const u32 PID_NVR1825_16HD							 = 0x111d;

const u32 PID_NVR2821H						= 0x10FF;
const u32 PID_NVR1821_1037					= 0x1100;

//2840Eû�ж���HWID ��ѡһ��
const u32 NVR2840E_9						= 0x2034;
const u32 NVR2840E_16						= 0x2035;
const u32 NVR2840E_32						= 0x2036;
const u32 NVR2840E_4						= 0x2031;
const u32 NVR2840E_4_NEW					= 0x2032;

//¼���ļ�����
const u8	MD_ALARM		= 0x01 ;        //�ƶ����澯�ļ�
const u8	VIDEOLOST_ALARM = 0x02 ;        //�źŶ�ʧ�澯�ļ�
const u8	SHADE_ALARM		= 0x04 ;        //ͼ���ڵ��澯�ļ�
const u8	INPUT_ALARM		= 0x08 ;		//��ƽ����澯�ļ�
const u8	CYC_RECORD		= 0x10 ;		//����¼��
const u8	HANDM_RECORD	= 0x20 ;		//�ֶ�¼��
const u8	SELF_TAG1		= 0x40 ;		//�Զ����ǩ1
const u8	SELF_TAG2		= 0x80 ;		//�Զ����ǩ2
const u16	SELF_TAG3		= 0x100 ;		//�Զ����ǩ3

//���̷���
const u8	MAX_PARTITION_NUM		=	64	;		//��������
const u8	MAX_HARDDISK_NUM		=	32	;		//��������
const u8	MAX_PARTITION_NAME_LEN  =	128 ;		//���������·����

const u8	USER_DATA_LENGTH		=	128 ;		//�û��Զ���������󳤶�

const u16	MAX_CMD_LENGTH			=	512 ;       //��������

const u8	DEL_FOR_DVSID           =	1 ;			//���豸IDΪɾ������ 
const u8	DEL_FOR_DVSALIAS        =	2 ;			//���豸����
const u8	DEL_FOR_DVSGUID         =	3 ;			//���豸��Guid
const u8	DEL_FOR_DVSENCNUM       =	4 ;			//���豸����ͨ����Ŀ
const u8	DEL_FOR_DVSDECNUM       =	5 ;			//���豸����ͨ����Ŀ
const u8	DEL_FOR_DVSIPADD        =	6 ;			//���豸��IP
const u8	DEL_FOR_DVSTYPE         =	7 ;			//���豸�ͺ�
const u8	DEL_FOR_DVSMUID         =	8 ;			//���豸���̴���

const u8	TEST_INSERT				=	11;         //���ݿ�������

//VTDU ��س���
#if defined(_NVR2820_) || defined(_NVR2820L_)
const u8 MAX_SWITCH_CHANNEL			=250;
#else
const u16 MAX_SWITCH_CHANNEL			=1000;
#endif
const u8 MAX_IP_ADDR				=16 ;
const u8 MAX_MP_NUM					=16 ;
const u8 MAX_MP_MTNUM				=TEST_128 ;			//���֧��ת��64���ն�����
const u8 MAXNUM_NVR_CHANNEL			=16 ;			//���NVR������·��
               
///---------NVR����ʱNVR��Ƕģ����������-----------------------------
const u8 STARTUP_NONE				=0	;	//�������κ�ģ��
const u8 STARTUP_MP					=1	;	//ֻ����mpģ��
const u8 STARTUP_BOTH	 			=3	;	//��ģ��ͬʱ����
const u8 MODE_NVR					=1	;	//������NVR
const u8 MODE_ABSOLUTE				=255;   //����
//----------------------NVR�������Ͷ���------------------------------
const u8 TYPE_MATRIX				=4 ;    //��Ƶ����
const u8 TYPE_KEYBOARD				=6 ;    //���̴���
const u8 TYPE_DRS					=11;	//¼���
const u8 TYPE_SOCKET				=12;	//��׼socket
const u8 TYPE_VPU					=13;	//VPU��������
const u8 MC_TYPE_DEFAULT			=1 ;    //����̨��ʶ

// Fd limit [1/21/2013 wangtianling]
const s32 NVR_FD_LIMIT = 4096;

const u16 PING_DVS_INTERVAL  = 0x0A; // Ĭ��ǰ�˶������ʱ���� 10 S
const u16 PING_DVS_BREAK_NUM = 0x06; // Ĭ��ǰ�˶������� 6 ��

//�������䷽ʽ
const u8 TRANS_NORTCP =2;	//UDP����ģʽ(������/����rtcp����)
const u8 TRANS_UDP =0;		//UDP����ģʽ
const u8 TRANS_TCP =1;		//TCP����ģʽ

//MATRIX
const u8 MIN_MATRIX_ID   = 48 ;      //MATRIX����СID��
const u8  MAX_MATRIX_ID  = 64 ;      //MATRIX�����ID��
const u8  MAXNUM_MATRIX  = 16 ;      //���MATRIX��
const u8  MAX_MATRIX_IN_CHNNUM	=  255 ;//����������ͨ����
const u8  MAX_MATRIX_OUT_CHNNUM	=  255 ;//����������ͨ����
const u8  MAXLEN_MATRIX_ALIAS   =  7  ;  //����������7����ĸ��3������

//�鲥
const u8  MAX_MULTI_NUM    =    128 ; //MCU����鲥������
const u8  MAX_MULTIRECV_NUM  =  32  ; //һ���鲥������������������


const u32 MP_TIMESPACE_TASK_CHECK  =  10000; //��λ(����)  
const u32 MP_TIMESPACE_PING        =   8000; //��λ(����)  

const u32 MAX_SERDATA_BUF_LEN	   =  14*1024;
#define  MIN_MULTIIP          inet_addr("224.0.0.0")
#define  MAX_MULTIIP          inet_addr("239.255.255.255")

const u8  UNUSED_TIMELINE_NO_LIMIT       = 0;   //ʹ�ý�ֹʱ���־��������

const u8  SMALL_RECFILE_LENGTH			 = 150; //С¼���ļ�����ʱ�� ��λ��

const u8	TIME_INTERVAL	  = 150;
const u8    MPU_DEF_SCHID     = 255;			//Ĭ��MPU����ID  		

const u8	MAX_BACKUP_USER	  = 16;				//��󱸷��û���   
const u8	BAK_SUBNAME_LEN	  = 40;				//¼�񱸷����ļ����ĳ���

//ǰ��¼���ļ���ѯ����
const u8	DVS_QUIEY_ALL_EVENT  =                0  ;  //��ѯ�����¼�
const u8	DVS_TYPE_PIN_ALARM   =              1    ;//���ڸ澯¼��
const u8	DVS_TYPE_MOTION_DETECT_ALARM   =    2    ;//�ƶ����澯¼��
const u8	DVS_TYPE_MANUAL        =            3    ;//�ֶ�¼��
const u8	DVS_TYPE_TIMELY        =            4    ;//��ʱ¼��
const u8	DVS_TYPE_PERIODLY      =            5    ;//����¼��
const u8	DVS_QUIEY_FILE         =            6    ;//���ļ���ѯ

//----------------------NVRȱʡ�˿ں�-------------------
const u16   NVR_SWITCH_STARTPORT  =   12000 ;   //���� DVS�����˿ں�[12000---12096]
const u16   NVR_OFFSETPORT  =   1024 ;          //NVR����/���Ͷ˿�ƫ����

const u16   NVR_DECSWITCH_STARTPORT  = 13000 ;	//��������������˿ں�
const u16	NVR_RTSP_LOCAL_PORT		 = 15000 ;	//RTSP�ı��ض˿�

const u16   NVR_DVSNATDETECT_PORTOFFSET  =   8 ;    //NVR����DVS��NAT̽����˿�ƫ����
const u16   NVR_NCNATDETECT_PORTOFFSET   =   12 ;   //NVR����NC��NAT̽����˿�ƫ����
const u16   NVR_RCVNCAUDIO_PORTOFFSET    =   512;   //����NC��Ƶ��������ʼ�˿ں�ƫ����
const u16   NVR_DOWNLOADTRANS_PORTOFFSET =   20 ;   //������ת�˿ں�


const u16	LOCAL_BACKUP_PORT = 34000;			//����¼�񱸷�ʹ�õ���ʼ�˿�34000~34064
const u16	FTP_SERVICE_PORT  = 35000;			//FTP���ض˿�   35000 ==> 1730 CU��NVR�ͻ���ʹ��ͬһ���˿�����  
const u16	MPU_REC_PORT_BASE = 35500;			//����Ĭ�ϵ�MPU���ն˿ں� 35500 ~ 35800
const u16	REC_PLY_PORT_BASE = 36000;			//����ʼ�˿�
const u16   DVS_REC_RESTORE_PORT = 37000;		//���ؽ���ǰ��ת��Ķ˿�

const u16   GB_TRANS_LOCALRCV_PORT = 40000;		//�ӹ���ƽ̨������ת������ת����ʼ�˿� 

const u16   DVS_RCVAUD_PORT              =   60066; //DVS������Ƶ�Ķ˿�
const u16   DVS_SENDVIDEO_RTPSTARTPORT   =   59000; //DVS������ƵRTP��ʼ�˿�
const u16   DVS_SENDAUDIO_RTPSTARTPORT   =   59002; //DVS������ƵRTP��ʼ�˿�
const u16   DVS_SENDVIDEO_RTCPSTARTPORT  =   60000; //DVS������ƵRTCP��ʼ�˿�
const u16   DVS_SENDAUDIO_RTCPSTARTPORT  =   60002; //DVS������ƵRTCP��ʼ�˿�
const u16   DVS_PLAYVIDEO_STARTPORT      =   60068; //DVS������Ƶ��ʼ�˿�
const u16   DVS_PLAYAUDIO_STARTPORT      =   60070; //DVS������Ƶ��ʼ�˿�
const u16   DVS_RCVAUD_PORT_2			 =   60102;	//DVS�ڶ�·������Ƶ�˿�

const u16   NVR_STARTRS_PORT             =	  50000;	//�����ش�ʱʹ�ö˿�
const u16   NC_STARTRS_PORT				 =    51000;	//����nc�ش�ʱ�˿�ʹ��

const u16   NVR_STARTRS_RTSP_PORT        =   55000; //�����������豸�ش�ʱ��ʼ�˿�

const u16   NVR_STARTRS_ONVIF_SUBSCRIBE_PORT   =   56000; //ONVIF Subscribe port

const u16   DEC_RS_START_PORT			 = 61000;		//���ڽ������ش�ʹ�õ���ʼ�˿�

const u16	DEFAULT_TELNET_PORT			 =   4000;	//
const u16	 DEFAULT_D01F_TELNET_PORT			 =   17230;	//


const u16	AUDIO_CYCLE_PORT_LOCAL		 =    30000;
const u16   AUDIO_CYCLE_PORT_REMOTE		 =    30010;
const u16   SEC_RECV_PORT				 =	  30020;	//����ʾ�������̶����������Ķ˿�

const u16   NVR_SNTP_SERVER_PORT		 =    34567;			

const u16   NVR_DEFAULT_PORT               = 1730;     //NVRȱʡ�����˿ں�
const u16   PU_EDCPORT_INTERVAL            = 1000;     //PU�ķ���ͨ�����������ͨ�����������
const u8	MAX_RECQUERY_NUM			   = 20;		//һ��¼���ļ���ѯ��ѯ�����ļ�¼��
const u32   MAX_URL_DOWN_TIMEOUT           = 3600;      //���س�ʱʱ��60���ӣ�����

// Intelligent Grid Search
const u16   MAX_INTELLIGENT_SEARCH_RESULT_NUM  = 1024;		//����¼������������
const u16   MAX_INTELLIGENT_SEARCH_AREA_WIGHT  = 22;		//�������¼����������
const u16   MAX_INTELLIGENT_SEARCH_AREA_HEIGHT = 18;		//�������¼����������
const u32   MAX_INTELLIGENT_SEARCH_TIME_SCOPE  = 24*60*60;  //�������¼�����ʱ����(s)
const u16   MAX_INTELL_QUERY_GRID_INFO_BYTES   = 1600;		// ����¼��������������������Byte��
															// INTELLIGENT_SEARCH_AREA_WIGHT*2 * INTELLIGENT_SEARCH_AREA_HEIGHT*2

#ifdef _NVR2820L_
    // use value 0xFFFFFFFF, sleep() exception -- suker.joe 20100730
    const u32   INFINITE_TIME   =         0xFFFFFFF  ; // this value is OK
#else
    const u32   INFINITE_TIME   =         0xFFFFFFFF  ;// Infinite timeout
#endif
const u16   MSG_PRINT_BUF   =			16*512; //��ӡ�������

//ͼ�����ģʽ
const u8    OUTPUT_MODE_VGA    =     0;   //VGA���
const u8    OUTPUT_MODE_NTSC   =     1;   //NTSC���
const u8    OUTPUT_MODE_PAL    =     2;   //PAL���
const u8    OUTPUT_MODE_HDMI   =     3;	  //HDMI���

const float ONE_PIC_SIZE	   =	 18/1024;  //ǰ��ץ�ĵ�ͼƬ��С��18km��λΪ��
//VGAģʽ
const u8    VGAMODE_VGA_60HZ   =     0;    //640*480 60HZ  
const u8    VGAMODE_VGA_75HZ   =     1;    //640*480 75HZ  
const u8    VGAMODE_VGA_85HZ   =     2;    //640*480 85HZ  
const u8    VGAMODE_SVGA_60HZ  =     3;    //800*600 60HZ  
const u8    VGAMODE_SVGA_75HZ  =     4;    //800*600 75HZ  
const u8    VGAMODE_SVGA_85HZ  =     5;    //800*600 85HZ                         
const u8    VGAMODE_XGA_60HZ   =     6;    //1024*768 60HZ                         
const u8    VGAMODE_XGA_75HZ   =     7;    //1024*768 75HZ                         
const u8    VGAMODE_XGA_85HZ   =     8;    //1024*768 85HZ                          
const u8    VGAMODE_SXGA_60HZ  =     9;    //1280*1024 60HZ                          
const u8    VGAMODE_SXGA_75HZ  =     10;   //1280*1024 75HZ 
const u8	VGAMODe_WXGA_60HZ  =     11;   //1280*800  60HZ
const u8	VGAMODe_WXGA_75HZ  =     12;   //1280*800  75HZ
//HDMI ģʽ
const u8    HDMIMODE_HD1080_60HZ = 13;	//1920*1080  60HZ
const u8    HDMIMODE_HD720_60HZ  = 14;	//1280*720  60HZ 
const u8	HDMIMODE_XGA_60HZ  = 15;	//1024*768  60HZ                       
const u8    VGAMODE_NONE       =     0xff;   

const u32   DEFAULT_RECRESERSIZE =    500;  //¼��ȱʡ��Ԥ���ռ�

const u32	DEFAULT_GRRESERSIZE_1 =		500; //ϵͳ������ץ��Ԥ���ռ�
const u32   GRBSIZE_FULL_LIMIT_1 =      20;	//ϵͳ������ץ��ʣ��澯�ռ�
#ifdef _NVR2820L_
const u32   DEFAULT_GRRESERSIZE_2 =     5;	//��ϵͳ������ץ��Ԥ���ռ�
const u32   GRBSIZE_FULL_LIMIT_2 =      1;	//��ϵͳ������ץ��ʣ��澯�ռ�
const u32	SYSPT_FREESIZE_LIMIT =		1;  //ץ�Ŀռ���д�С����
#else
const u32   DEFAULT_GRRESERSIZE_2 =     50;	//��ϵͳ������ץ��Ԥ���ռ�
const u32   GRBSIZE_FULL_LIMIT_2 =      5;	//��ϵͳ������ץ��ʣ��澯�ռ�
const u32	SYSPT_FREESIZE_LIMIT =		25; //ץ�Ŀռ���д�С����
#endif

const u8	DEFAULT_GRINTERVAL =     10;	//ȱʡ��ץ�ļ��
const u8    DEFAULT_GRPICNUM  =       1;    //ȱʡʱץ��ͼƬ��Ŀ

#ifdef _NVR2820_
const u32	MAX_ALARM_NUM	=		  15000;
#else
const u32   MAX_ALARM_NUM	=		  20000;	//�澯���ݿ������ݶ���MAX_ALARM_NUM�͸�ɾ����
#endif
#define     ACTIONFAIL	-1


//ddns���ó���
const u8	DDNS_USER_LEN = 			128;
const u8    DDNS_PWD_LEN =				128;
const u8    DDNS_DOM_LEN =				128;
const u8    DDNS_IP_LEN =				16;

const u8 DEC_TYPE_D1  =  0;
const u8 DEC_TYPE_CIF =  1;
const u8 DEC_TYPE_QCIF = 2;
const u8 DEC_TYPE_1080P  =  3;
const u8 DEC_TYPE_720P  =  4;
const u8 DEC_TYPE_QXGA  =  5;
const u8 DEC_TYPE_500W  =  6;

/*
const u8 ENC_RESOLUTION_NONE = 0;
const u8 ENC_RESOLUTION_AUTO = 1;
const u8 ENC_RESOLUTION_QCIF = 2;
const u8 ENC_RESOLUTION_CIF  = 3;
const u8 ENC_RESOLUTION_2CIF = 4;
const u8 ENC_RESOLUTION_D1   = 5;
const u8 ENC_RESOLUTION_VGA  = 7;
const u8 ENC_RESOLUTION_QVGA = 8;
const u8 ENC_RESOLUTION_720P  = 9;
const u8 ENC_RESOLUTION_1080P = 10;*/


//ͼ��ֱ���
const  u8 VIDEO_RESOLUTION_NONE	=		0x00;
const  u8 VIDEO_RESOLUTION_AUTO	=		0x01;
const  u8 VIDEO_RESOLUTION_QCIF	=		0x02;     //192*128
const  u8 VIDEO_RESOLUTION_CIF	=		0x03;     //352*256
const  u8 VIDEO_RESOLUTION_2CIF	=		0x04;     //704*256
const  u8 VIDEO_RESOLUTION_4CIF	=		0x05;     //704*400
const  u8 VIDEO_RESOLUTION_SQCIF=		0x06;     //96*80;
const  u8 VIDEO_RESOLUTION_VGA  =       0x07;     //640*480
const  u8 VIDEO_RESOLUTION_QVGA =       0x08;     //320*240
const  u8 VIDEO_RESOLUTION_720P =       0x09;     //1280*720         
const  u8 VIDEO_RESOLUTION_1080P=       0x0A;	  //1920*1080
const  u8 VIDEO_RESOLUTION_QXGA	=	 	0x0B;     //2048*1536
const  u8 VIDEO_RESOLUTION_XGA	=		0x0C;     //1024*768
const  u8 VIDEO_RESOLUTION_SVGA	=		0x0D;     //800*600

const  u8 VIDEO_RESOLUTION_CGA =		73; //320*200
const  u8 VIDEO_RESOLUTION_WQVGA =		74; //400*240
const  u8 VIDEO_RESOLUTION_NTSC =		75; //720*480
const  u8 VIDEO_RESOLUTION_PAL =		76; //768*576
const  u8 VIDEO_RESOLUTION_WVGA =		77; //800*480
const  u8 VIDEO_RESOLUTION_WSVGA =		78; //1024*600
const  u8 VIDEO_RESOLUTION_WSVGA2 =		79; //1152*768
const  u8 VIDEO_RESOLUTION_WXGA =		80; //1280*768
const  u8 VIDEO_RESOLUTION_WXGA2 =		81; //1280*800
const  u8 VIDEO_RESOLUTION_SXGA2 =		82; //1280*854
const  u8 VIDEO_RESOLUTION_SXGA =		83; //1280*1024
const  u8 VIDEO_RESOLUTION_WXGAPLUS =	84; //1440*900
const  u8 VIDEO_RESOLUTION_WXGAPLUS2 =	85; //1440*960
const  u8 VIDEO_RESOLUTION_SXGAPLUS =	86; //1400*1050
const  u8 VIDEO_RESOLUTION_WSXGAPLUS =	87; //1680*1050
const  u8 VIDEO_RESOLUTION_WUXGA =		88; //1920*1200
const  u8 VIDEO_RESOLUTION_2K =			89; //2048*1080
const  u8 VIDEO_RESOLUTION_WQXGA =		90; //2560*1536
const  u8 VIDEO_RESOLUTION_WQXGA2 =		91; //2560*1600
const  u8 VIDEO_RESOLUTION_QSXGA =		92; //2560*2048
const  u8 VIDEO_RESOLUTION_QCIF2 =		93; //176*144
const  u8 VIDEO_RESOLUTION_CIF3 =		94; //352*240
const  u8 VIDEO_RESOLUTION_CIF2 =		95; //352*288
const  u8 VIDEO_RESOLUTION_2CIF2 =		96; //704*288
const  u8 VIDEO_RESOLUTION_4CIF2 =		97; //704*576
const  u8 VIDEO_RESOLUTION_1080P2 =		98; //1600*1200
const  u8 VIDEO_RESOLUTION_720P2 =		99; //1280*960


const  u8 PT_NAME_LEN  = 128; //�������ֵĳ���
const  u8 DISK_MAX_NR  = 32; //ϵͳ�ɲ��ҵ���������
const  u8 UUID_LEN	   = 37; //UUID	����	

const  u8 TOTAL_SPACE_POLICY = 1;
const  u8 CHN_SPACE_POLICY = 0;

const u8 MAXNUM_PTZ_DEFCMD		  = 8;	// ����Զ�������
const u8 MAXLEN_PTZ_DEFCMD_CMNT   = 16;	// �Զ�������ע����ַ�����16�ַ���8�����֣�
const u8 MAXLEN_PTZ_DEFCMD_DATA   = 32;  // �Զ��������֣��Կո������2��ֵ�����32�ַ���


const u8 MAX_ROUTE_NUM   = 8;			//���徲̬·�ɵ���Ŀ
// ��־������
const u8 MAXNUM_LOG	 =			  10 ; // �����־ʵ����

// ��־����
const u8 LOG_TYPE_USER_LOG   =      0 ;  // �û���½/�ǳ���־
const u8 LOG_TYPE_USER_OPER    =    1 ;  // �û�������־
const u8 LOG_TYPE_EQP          =    2 ;  // �豸(�豸ע��,���ߵ�)��־
const u8 LOG_TYPE_ALARM        =    3  ; // �澯��־
const u8 LOG_TYPE_BAKEUP       =    4 ;  // ������־
const u8 LOG_TYPE_UPDATE       =    5 ;  // ������־
 
//��־����
const u8   LOG_LEVEL_INVALID                   =  (u8)0;//��Ч��־�ȼ�
const u8   LOG_LEVEL_GERNERAL                  =  (u8)1;//һ������־
const u8   LOG_LEVEL_SECONDARY                 =  (u8)2;//��Ҫ����־
const u8   LOG_LEVEL_IMPORT                    =  (u8)3;//��Ҫ����־

//��־��ѯʱ������˳���趨
const u8   LOG_QUERY_ORDERBY_ASC               =  (u8)0;//����
const u8   LOG_QUERY_ORDERBY_DESC              =  (u8)1;//����

// ��־��������
const u8  LANGUAGE_TYPE_CHINESE                =  (u8)1;
const u8  LANGUAGE_TYPE_ENGLISH                =  (u8)2;
const u8  LANGUAGE_TYPE_LANGUAGE1              =  (u8)3;
const u8  LANGUAGE_TYPE_LANGUAGE2              =  (u8)4;

const u8 LOG_LANG_TYPE_CHINESE                 =  0;  // ��������
const u8 LOG_LANG_TYPE_ENGLISH                 =  1;  // Ӣ��
const u8 LOG_LAND_TYPE_CHINESE_TRADITIONAL     =  2;  // ��������
const u8 LOG_LAND_TYPE_ITALY                   =  3;  // �������
//¼������   ��TRpTask�е�¼�����ͱ���һ��
const u8  RECTYPE_MANU                        =    0x01;//�ֶ�¼��
const u8  RECTYPE_TIMER                       =    0x02;//��ʱ���¼��
const u8  RECTYPE_ALARM_MOTION                =    0x04;//�ƶ����澯¼��
const u8  RECTYPE_ALARM_INPUT                 =    0x08;//��ƽ����澯¼��
const u8  RECTYPE_ALARM_SHADE                 =    0x10;//ͼ���ڱθ澯¼��
const u8  RECTYPE_ALARM_VIDLOSE               =    0x20;//��ƵԴ��ʧ�澯¼��

//¼��ģʽ ��TRecordParam�е�¼��ģʽ����һ��
const u8  RECMODE_STOP                         =   0x00;//	�ر�
const u8  RECMODE_MANU                         =   0x01;//	�ֶ�
const u8  RECMODE_AUTO                         =   0x02;//�Զ�
const u8  RECMODE_PRE1                         =   0x03;//����
const u8  RECMODE_PRE2                         =   0x04;//����
const u8  RECMODE_TIMER                        =   0x08;//��ʱ���¼��
const u8  RECMODE_ALARM_MOTION                 =	0x10;//�ƶ����澯¼��
const u8  RECMODE_ALARM_INPUT                  =	0x20;//��ƽ����澯¼��
const u8  RECMODE_ALARM_SHADE                  =	0x40;//ͼ���ڱθ澯¼��
const u8  RECMODE_ALARM_VIDLOSE                =   0x80;//��ƵԴ��ʧ�澯¼��

//DVD��¼
const u8  MAX_RECORD_NUM					   =	20; //һ�ο�¼������¼����
#define  USERBAKDBPATH							"/tmp"
#define  USERBAKDBNAME							"/tmp/bak.dat"
#define  SYS_DB_NAME							"Nvr.dat"
#define  LANGUAGE_DB_NAME						"NvrLanguage.dat"
#define  DVS_DB_NAME						    "Dvs.dat"

#if defined(_KDMD01F_)              
#define  SYS_LOGRES_PATH     "/usr/bin/appres/logres" 
#define  SYS_PT_PATH		  "/usr/syspt"
#endif
#if defined(_NVR1825_) || defined( _NVR1822_)               //add zq 2013.4.12
   #define  SYS_LOGRES_PATH     "/usr/bin/appres/logres"   
#endif
#if defined(_NVR2820L_) || defined( _NVR2821H_)
	#define  CFG_PATH								"/usr/config/"
	#define	 LOG_PATH								"/usr/config/log/"
	#define  DB_PATH								"/usr/config/"
	#define  EXCEPTION_PATH							"/usr/config/exception/"
	#define  SYS_UPDATEPKG_PATH						"/usr/bin/"
	#define  SYS_UPDATEPKGDB_PATH					"/usr/bin/config/"
	#define  MOUNTROOT								"/usr/disk"
	#define  TMP_DB_PATH							"/ramdisk/"
	#define  MAINDB_BACKUP_PATH						"/usr/"
    #define  SYS_LOGRES_PATH                        "/usr/bin/appres/logres"  //add zq 2013.4.12
	#define  SYS_PT_PATH							"/usr/syspt"
	#define  VSI_PRINT_PATH                         "/usr/config/vsipinit.log"
	#define	 TEST_DB_PATH							"/usr/config/test.dat"
	#define HWINFO_CFG_NAME							"/usr/bin/hwinfo"
	#define HWINFO_CFG_NAME_BK						"/usr/bin/hwinfo-bak"
	#define SYS_BAK_NVR_LOG_CMD		"\\cp -rf /ramdisk/log/ /usr/config/"
	#define SYS_GET_NVR_LOG_CMD		"cp -f /usr/config/log/* /ramdisk/log"
	#define SYS_RM_NVR_LOG_CMD      "find /usr/config/log/ -size +256 -exec rm {} \\;"
	#define SYS_RM_RAMDISK_LOG_CMD  "find /ramdisk/log -size +128 -exec rm {} \\;"
	#define SYS_RM_UPDATE_FLAG_FILE  "rm -rf /usr/.update"
	#define SYS_MOUNT_MTDBLOCK0		 "mount -t  yaffs2 /dev/mtdblock0 /mnt"
	#define SYS_MOUNT_MTDBLOCK1		 "mount -t  yaffs2 /dev/mtdblock1 /mnt"
	#define SYS_RM_MNT_FILES		"rm -rf /mnt/*"
	#define SYS_CREATE_UPDATE_FLAG_FILE		"touch /usr/.update"
	#define UPDATE_FLAG_FILE	"/usr/.update"
#ifndef _NVR1825_
	#define UPDATE_FILE_NAME	"/mnt/sysimage.gz"
#else
	#define UPDATE_FILE_NAME	"/usr/sysimage.gz"
#endif
	#define FTP_USERNAME		"admin"
	#define FTP_PASSWORD		"kedacomIPC"
#else
	#define  CFG_PATH								"/NVR2860/config/"
	#define	 LOG_PATH								"/NVR2860/config/log/"
	#define  DB_PATH								"/NVR2860/config/"
	#define  EXCEPTION_PATH							"/NVR2860/config/exception/"
	#define  SYS_UPDATEPKG_PATH						"/NVR2860/bin/"
	#define  SYS_UPDATEPKGDB_PATH					"/NVR2860/bin/config/"
	#define  MOUNTROOT								"/NVR2860/disk"
	#define  TMP_DB_PATH							"/ramdisk/"
	#define  MAINDB_BACKUP_PATH						"/NVR2860/"
	#define  SYS_LOGRES_PATH                        "/NVR2860/bin/logres"
	#define  SYS_PT_PATH							"/NVR2860/syspt"
	#define  VSI_PRINT_PATH                         "/NVR2860/config/log/vsipinit.log"
	#define	 TEST_DB_PATH							"/NVR2860/config/test.dat"
	#define HWINFO_CFG_NAME							"/home/hwinfo"
	#define HWINFO_CFG_NAME_BK						"/home/hwinfo-bak"
	#define SYS_BAK_NVR_LOG_CMD		"\\cp -rf /ramdisk/log/ /NVR2860/config/"
	#define SYS_GET_NVR_LOG_CMD		"cp -f /NVR2860/config/log/* /ramdisk/log"
	#define SYS_RM_NVR_LOG_CMD      "find /NVR2860/config/log/ -size +256 -delete"
	#define SYS_RM_RAMDISK_LOG_CMD  "find /ramdisk/log/ -size +128 -delete"
#endif

#define HWINFO_CFG_2860_NAME					"/NVR2860/bin/hwinfo"
#define HWINFO_CFG_2821H_NAME					"/usr/bin/hwinfo"

const u8  ASCIIA_BASE_VALUE						= 	65; //ASCII ������ַ�A����ֵ

const u16 TWO_HOUR_SPACE                        =  11520; //��Сʱ�Ĵ洢�ռ�(2*360*16) 

const u8  MAX_TVWCHN2860						= 64;

// �û�Ȩ�޹���
// Ȩ�޿��ƺ궨��
// 2680�µ����
// NcType����


// 2820��������
#define PRI_NVR_CFG         1    // NVR���ò���
#define PRI_NVR_FUN_OPE     2    // NVR���ܲ���

#define PRI_NVR_FUN_DEV_MGR 21   // �豸����
#define PRI_NVR_FUN_REC     22   // ¼��
#define PRI_NVR_FUN_PLAY    23   // ����
#define PRI_NVR_FUN_TVWALL  24   // ����ǽ
#define PRI_NVR_FUN_SNAP    25   // ץ��
#define PRI_NVR_FUN_ALARM   26   // �澯
#define PRI_NVR_FUN_MPU     27   // MPU����

#define PRI_NVR_SYS_OPE      3   // NVRϵͳ����

#define PRI_DVS_CFG          4   // DVS����
#define PRI_DVS_FUN_OPE      5   // DVS���ܲ���
#define PRI_DVS_FUN_MONITOR  51  // ��Ƶ���
#define PRI_DVS_FUN_AUDIO    52  // ��������
#define PRI_DVS_FUN_PTZ      53  // ptz����
#define PRI_DVS_FUN_REBOOT   54  // ����
#define PRI_DVS_FUN_REC      55  // ǰ��¼�����      

#define DEFAULT_NVRID		 8  //Ĭ��NVRID     

#define FREETAG				"free"       //�����п�������ı�־     

#define PING_MAXPACKET		4096	/* max packet size */    
#define PING_INTERVAL		1	/* default packet interval in seconds */
#define PING_TMO	    	1	/* default packet timeout in 100 ms */
#define PING_DECTIMES	   	3	/* default ping packet nums*/
#define ICMP_PROTO		    1	/* icmp socket proto id */
#define ICMP_TYPENUM		20	/* icmp proto type identifier */
#define TASK_NAME_LEN	20	/* max ping Tx task name length */
#define	PING_OPT_SILENT		0x1	/* work silently */
#define	PING_OPT_DONTROUTE	0x2	/* dont route option */
#define	PING_OPT_DEBUG		0x4	/* print debugging messages */
#define INET_ADDR_LEN		20

#define MAXRECQUERYNUM	    20  //һ��¼���ѯ,��ѯ������¼��

#define MAXUSERNAMELEN		16  //���Զ˿ڵ�����û�����
#define MAXPASSWORDLEN		16  //���Զ˿ڵ�������볤

#define NORMALWORKING		0  //ϵͳ��������
#define SYSSLEEPING			1  //ϵͳ��ػ���
#define SYSSLEEPED			2  //ϵͳ��ػ�
#define MULTIMPUPLY			0  //��·����
#define SYNCMPUPLY			1  //ͬ������

#define SYNCPTRECNUM		200  //¼�����ͬ��������һ�β����ļ�¼��
#define SYS_UP_FILE_NAME	"/ramdisk/nvr.pkg"
#define SYS_UP_GZFILE_NAME  "/ramdisk/nvr.pkg.gz"
#define RES_FILE_NAME		"/ramdisk/nvrgui.res"
#define SYS_MK_LOG_DIR_CMD		"mkdir -p /ramdisk/log/"
#define SYS_RM_LOG_DIR_CMD		"rm -rf /ramdisk/log/*"
#define NVR2820H_HW_VER "/tmp/.2820H_hw_ver"
#define GET2820H_HW_VER "lspci|grep -c 'SiI 3114 \\[SATALink/SATARaid] Serial ATA Controller' 1>"NVR2820H_HW_VER

#define RECO_FAC_PWD_TAB_NAME "recofacpwd"
#define PROC_MOUNTS "/proc/mounts"
#define PROC_CMDLINE "/proc/cmdline"

//������2820 2.0�汾���������޸ĵĺ�
#define MAXNUM_RECORDS_PERPAGE  1000
#define MAXNUM_ETH  3

//ҵ���ڲ�ʹ��
const u8 BUF_LEN						   = 255;
const u8 MAXNUM_RECTRANSLATE_NUM		   = 4;	    //nvrϵͳ֧�ֵ����ת��·��
const u8 CPU_AVERAGE_COUNT_NUM			   = 10;	    //nvrϵͳ�м���ƽ��ֵʹ�õ�����������

#define	 MAX_EXT_MPUSCHEME 23

#if defined(_NVR2860_)  || defined( _NVR2821H_)
	const u8     MAXNUM_MPUCHN                 = 70  ;    //���MPUͨ����
	const u8	 RESTROR_START_REC_ID		   = 64;
	const u8     MAXNUM_SYNCMULTI              = 34;	//���ͬʱ��34������ͬ���ط�
	const u8 	 MAX_TVWCHN					   = 64  ;	  //TVWALL���Կ��Ƶ����ͨ����
	const u8     MAXNUM_RECBAKER               = 1;	//���ͬʱ��1�����ݻ�
	#define  MAXNUM_DVS_SERV	MAXNUM_ENC
	#define  MAXNUM_DECODER_SERV  MAXNUM_DEC
	#define  MAXNUM_ENCCHN_SERV   MAXNUM_ENCCHN
	#define  MAXNUM_MPUCHN_SERV   MAXNUM_MPUCHN
	#define  MAXNUM_MPUSTYLE_SERV MAXNUM_MPUSTYLE*2
	#define  MAXNUM_SCHEME_SERV   64
	#define  MAXNUM_MPUSCHEME_SERV  64
	#define  MAXNUM_MPUPLAN_SERV    64
	#define	 MAX_RECORDER_NUM_SERV  MAX_RECORDER_NUM+MAXNUM_RECTRANSLATE_NUM
#if defined(_NVR1825_)
	// 1825������9· [5/3/2013 wangtianling]
	#define  MAXNUM_DVS_SERV	  16
	#define  MAXNUM_ENCCHN_SERV   16
	#define  MAXNUM_DECODER_SERV  16
	#define	 MAX_RECORDER_NUM_SERV  MAX_RECORDER_NUM/4+MAXNUM_RECTRANSLATE_NUM
	// 1825������9· [5/3/2013 wangtianling]
	#define	 MAX_GUI_PLAY_NUM	 4 // ֧�ֱ���MPU���������
	#define	 MAX_NC_PLAY_NUM	 4 // ֧��NC���������	
	#if defined(_NVR1825_9HD_)
		#define	 MAX_GUI_PLAY_NUM	 9  // ֧�ֱ���MPU���������
		#define	 MAX_NC_PLAY_NUM	 16 // ֧��NC���������
	#endif	
#elif defined(_NVR1822_)
	#define	 MAX_GUI_PLAY_NUM	 16 // ֧�ֱ���MPU���������
	#define	 MAX_NC_PLAY_NUM	 16 // ֧��NC���������	
#else
	#define	 MAX_GUI_PLAY_NUM	 16 // ֧�ֱ���MPU���������
	#define	 MAX_NC_PLAY_NUM	 16 // ֧��NC���������	
#endif
	#define	 MAX_PLAY_NUM_SERV	 MAX_GUI_PLAY_NUM + MAX_NC_PLAY_NUM // ֧�ַ�������

    #define  MAX_TVWCHN_SERV	 MAX_TVWCHN	
	#define	 MAXNUM_TVWCHN_SERV  MAXNUM_TVWCHN
	#define	 MAXNUM_TVWDVS_SERV  MAXNUM_TVWDVS
	#define	 MAXNUM_TVWCYCLEPROJ_SERV 64
	#define	 MAXNUM_TVWSCHEME_SERV MAXNUM_TVWSCHEME
	#define	 MAXNUM_TVWPROJ_SERV MAXNUM_TVWPROJ
	#define  MAXNUM_USER_SERV    MAXNUM_USER
#else
	const u8     MAXNUM_MPUCHN                 = 16;    //���MPUͨ����
	const u8	 RESTROR_START_REC_ID		   = 16;
	const u8     MAXNUM_SYNCMULTI              = 3;	//���ͬʱ��10������ͬ���ط�
	const u8 	 MAX_TVWCHN					   = 16;	  //TVWALL���Կ��Ƶ����ͨ����
	const u8     MAXNUM_RECBAKER               = 1;	//���ͬʱ��1�����ݻ�
		#ifdef _NVR2820L_
			//#define  MAXNUM_DVS_SERV	MAXNUM_ENC/8
			#define  MAXNUM_DVS_SERV	MAXNUM_ENC/16
			#define  MAXNUM_ENCCHN_SERV   MAXNUM_ENCCHN/16
			#define  MAXNUM_DECODER_SERV  MAXNUM_DEC/16
			#define	 MAX_RECORDER_NUM_SERV  MAX_RECORDER_NUM/16+MAXNUM_RECTRANSLATE_NUM
		#else
			#define  MAXNUM_DVS_SERV	MAXNUM_ENC/4
			#define  MAXNUM_ENCCHN_SERV   MAXNUM_ENCCHN/4
			#define  MAXNUM_DECODER_SERV  MAXNUM_DEC/4
			#define	 MAX_RECORDER_NUM_SERV  MAX_RECORDER_NUM/4+MAXNUM_RECTRANSLATE_NUM
		#endif
	#define  MAXNUM_MPUCHN_SERV   MAXNUM_MPUCHN
	#define  MAXNUM_MPUSTYLE_SERV MAXNUM_MPUSTYLE-1
	#define  MAXNUM_SCHEME_SERV   MAXNUM_MPUSCHEME
	#define  MAXNUM_MPUSCHEME_SERV  MAXNUM_MPUSCHEME
	#define  MAXNUM_MPUPLAN_SERV    MAXNUM_MPUPLAN
	/* 20110216- suker for 2820L save memory */
	#ifdef _NVR2820L_
		#define	 MAX_GUI_PLAY_NUM	 0 // ֧�ֱ���MPU���������
		#define	 MAX_NC_PLAY_NUM	 12 // ֧��NC���������
	#else
		#define	 MAX_GUI_PLAY_NUM	 4 // ֧�ֱ���MPU���������
		#define	 MAX_NC_PLAY_NUM	 16 // ֧��NC���������
	#endif
	#define	 MAX_PLAY_NUM_SERV	 MAX_GUI_PLAY_NUM + MAX_NC_PLAY_NUM // ֧�ַ�������

	#define  MAX_TVWCHN_SERV	 MAX_TVWCHN	
	#define	 MAXNUM_TVWCHN_SERV  MAXNUM_TVWCHN
	#define	 MAXNUM_TVWDVS_SERV  MAXNUM_TVWDVS
	#define	 MAXNUM_TVWCYCLEPROJ_SERV 16
	#define	 MAXNUM_TVWSCHEME_SERV MAXNUM_TVWSCHEME
	#define	 MAXNUM_TVWPROJ_SERV MAXNUM_TVWPROJ
	#define  MAXNUM_USER_SERV    MAXNUM_USER
#endif

#define DECRECVPORT			60000 //������������ʼ�˿�	
#define PLAT_NVR_PLAY_REC_DSTCHN_PORT 7000
//����ͷ���Ͷ���
const u8 CAMERA_TYPE_SONY                  = 1;    //(u8)1		SONY
const u8 CAMERA_TYPE_AD                    = 2;    //(u8)2		AD
const u8 CAMERA_TYPE_PELCO                 = 3;    //(u8)3		PELCO-D
const u8 CAMERA_TYPE_PIH			       = 4;    //(u8)4		����
const u8 CAMERA_TYPE_PELCO_P 		       = 5;    //(u8)5		PELCO-P
const u8 CAMERA_TYPE_PARCO                 = 6;	   //(u8)6		PARCO�ظ�
const u8 CAMERA_TYPE_AB			           = 7;    //(u8)7		AB
const u8 CAMERA_TYPE_YUNTAI		           = 8;    //(u8)8		������̨
const u8 CAMERA_TYPE_Samsung		       = 9;    //(u8)9		����
const u8 CAMERA_TYPE_YAAN			       = 10;   //(u8)10	    �ǰ�
const u8 CAMERA_TYPE_AD168                 = 11;   //(u8)11	    AD168����
const u8 CAMERA_TYPE_KALATEL               = 12;   //(u8)12	    ������
const u8 CAMERA_TYPE_JN                    = 13;   //(u8)13	    JNΰ��
const u8 CAMERA_TYPE_WV_CS650              = 14;   //(u8)14	    ����,��850����Э��
const u8 CAMERA_TYPE_WV_CS850              = 15;   //(u8)15	    ����,��850����Э��
const u8 CAMERA_TYPE_ALEC                  = 16;   //(u8)16	    ������
const u8 CAMERA_TYPE_AB_P                  = 17;   //(u8)17	    AB-P
const u8 CAMERA_TYPE_AB_D                  = 18;   //(u8)18	    AB-D
const u8 CAMERA_TYPE_PELCO_D_JEC           = 19;   //(u8)19	    JEC PELCO-D
const u8 CAMERA_TYPE_PELCO_P_JEC           = 20;   //(u8)20	    JEC PELCO-P
const u8 CAMERA_TYPE_ROBOT                 = 21;   //(u8)21     ROBOT
const u8 CAMERA_TYPE_PELCO_D_K             = 26;   //(u8)26     PELCO_D_K
// ����������
const u8 CAMCTRL_COMMAND_MATRIX_SWTICH   = 29;	//�л���Ƶ
const u8 CAMCTRL_COMMAND_MATRIX_VIDMIX4  = 30;	//����ϳ�2��2
const u8 CAMCTRL_COMMAND_MATRIX_VIDMIX9  = 31;	//����ϳ�3��3
const u8 CAMCTRL_COMMAND_MATRIX_VIDMIX16 = 32;	//����ϳ�4��4
const u8 CAMCTRL_COMMAND_MATRIX_VIDMIXPP = 33;	//����ϳɻ��л�
const u8 MAX_CHN_NUM_32					= 32  ;	//ͨ����Ŀ�޶�
const u8 MAX_CHN_NUM_48					= 48  ;	//ͨ����Ŀ�޶�
const u8 MAX_CHN_NUM_64					= 64  ;	//ͨ����Ŀ�޶�
const u8 MAX_CHN_NUM_128				= 128 ;	//ͨ����Ŀ�޶�
const u8 MAX_CHN_NUM_96					= 96 ; //ͨ����Ŀ�޶�
const u16   FTP_SERVICE_PORT2 = 1730;           // [11/6/2008 zhangkehui] ��ǰ����
const u16   CMSI_PLY_PORT_BASE = 59260;         //ƽ̨����ǰ�˷�����ʼ�˿�
                                                // 59068==>59260  59000 + (64/16 + 1) *4 [ƽ̨�˿ڷ������6/11/2009 zhangkehui]
#if defined(_NVR2821H_) || defined(_NVR1037_)
const u8 SMOOTH_DEFAULT_VALUE = 10;				//NVR1821/NVR2821H������Ĭ��ֵ<2013_3_12 SYT>
#else
const u8 SMOOTH_DEFAULT_VALUE = 3;				//������Ĭ��ֵ<2012_3_23 KSW>
#endif

const  u8 PART_MAX_NR_NVR  = 4; //�������������������

const u8 NVRMAJORVER			  = 20; // nvr���汾��
const u8 NVRMINORVER			  = 0;  // nvr�ΰ汾��

const u8 NVRMAJORVER30			  = 30; // nvr���汾��
const u8 NVRMINORVER30			  = 3;  // nvr�ΰ汾��

const u8 NVRMAJORVER40			  = 40; // nvr���汾��
const u8 NVRMINORVER40			  = 3;  // nvr�ΰ汾��
const u8 NVRMINORVER431			  = 31; // nvr�ΰ汾��

const u8 NVRMAJORVER50			  = 50; // nvr���汾��
const u8 NVRMINORVER50			  = 1;  // nvr�ΰ汾��
const u8 NVRMINORVER51			  = 11; // nvr�ΰ汾��
const u8 NVRMINORVER52			  = 12; // nvr�ΰ汾��
const u8 NVRMINORVER53			  = 13; // nvr�ΰ汾��
const u8 NVRMINORVER54			  = 14; // nvr�ΰ汾�� V4R4B1FIX1
const u8 NVRMINORVER55			  = 15; // nvr�ΰ汾�� V5R1

#define NC_TYPE_NC          0        // �ͻ��˵�½
#define NC_TYPE_GUI         1        // GUI��½
#define NC_TYPE_CMSI        2        // CMSI��½
#define NC_TYPE_WEB         3        // WEB�û���½ [10/22/2009 zhangkehui]
#define NC_TYPE_WEBDI		4		 // WEB������Ϣ��½ [9/112012 songyiting]
#define NC_TYPE_BRD			5		 // ��nvr������
#define NC_TYPE_D01F		6		 // d01f��¼
#define NC_TYPE_D04F		7		 // d04f��¼
#define NC_TYPE_GBPROXY		8		 // ��������¼
#define NC_TYPE_INVALID     255      // ��Ч����

#define USER_STOP_INTERNAL  10*60    // �û�ͣ��ʱ�� 10����
#define USER_LOG_ERR_TIMES  3        // ��½����ʧ�ܴ���

#define USER_TYPE_DEFAULT   0        // default�û�
#define USER_TYPE_ADMIN     1        // admin�û�
#define USER_TYPE_NORMAL    2        // ��ͨ�û�
#define USER_TYPE_ADMIN_DEFAULT 3    // Ĭ�ϵ�admin�û�
#define USER_TYPE_INVALID   4        // ��Ч�û�����

#define PRI_NVR_RECSNAP     0x0001   // ¼��ץ��
#define PRI_NVR_DEVMGR      0x0002   // �豸����
#define PRI_NVR_ALARMMGR    0x0004   // �澯����
#define PRI_NVR_TVWALL      0x0008   // ����ǽ
#define PRI_NVR_CFGMGR      0x0010   // ��������
#define PRI_NVR_USERMGR     0x0020   // �û�����
#define PRI_NVR_LOGMGR      0x0040   // ��־����

#define PRI_DVS_PTZCTRL     0x01     // PTZ����
#define PRI_DVS_MONITOR     0x02     // ��Ƶ���
#define PRI_DVS_PLAYER      0x04     // ��Ƶ�ط�

// ƽ̨�������Ͷ��� [11/6/2008 zhangkehui]
#define PLAT_TYPE_SP2       0        // sp2ƽ̨
#define PLAT_TYPE_2800      1        // 2800Eƽ̨
#define PLAT_TYPE_SP2_64    2        // sp2ƽ̨,֧��64ͨ�� [7/13/2009 zhangkehui]
#define PLAT_TYPE_2800_64   3        // 2800Eƽ̨,֧��64ͨ�� [7/13/2009 zhangkehui]
#define PLAT_TYPE_HD_64     4        // ֧��64·����ƽ̨ [9/24/2009 zhangkehui]
#define PLAT_TYPE_DEC    5        // ֧��64·����ƽ̨ [9/24/2009 zhangkehui]

#define REG_CMS_TYPE_NORMAL 0        // ����ע��
#define REG_CMS_TYPE_LDS    1        // ���ؾ���


// ����澯����
#define PIN_DECT_STATE_NONE   0        // �����
#define PIN_DECT_STATE_ONE    1        // ֻ���һ������
#define PIN_DECT_STATE_CYCLE  2        // ÿ��ѭ�����
#define PIN_DECT_STATE_ALWAYS 3        // ʼ�ռ��

#define PIN_RELATE_ENCID_DISABLE	0xFF    //�澯������Ƶ����ͨ����Чֵ
#define PIN_OUTPUT_DISABLE			0xFF	//�澯���������Чֵ

#define PIN_OSD_DISABLE				0
#define PIN_OSD_ENABLE				1

#define MAX_DEV_OSDNAME_NUM 3  //ǰ��֧�ֵ����OSD��Ļ��

/////////////////////ҵ���ڲ�ʹ��//////////////////////////////////////////////
const u8	 MAX_RECORDER_NUM			   = TEST_128	 ;	  //¼��ͨ�����������
const u8	 MAX_PLAY_NUM				   = 64  ;	  //����ͨ�����������//2860Ŀǰ���Ϊ64
const u8     MAXNUM_MPUSTYLE               = 17  ;    //���MPU�����

const u8 PTCHKOK = 200;			// ��������,���ҹҽӳɹ�
const u8 PTCHKNEEDRP = 201;		// ���������޸�,���ҹҽӳɹ�
const u8 PTCHKOPTFAIL = 202;		// �ű�����ʧ��
const u8 PTCHKLOGERROR = 203;		// ���������޸�,���ҹҽ�ʧ��

const u16 ALARMSTATEZERO = 10000;  //ǰ�˸澯������Ļ��״̬

const u8 USERDATANAMELEN = 32;		//�û��Զ����������Ƴ���
const u8 USERDATACONTENTLEN = 255;	//�û��Զ����������ݳ���

const u16 NVR_MAX_FILE_PATH_LEN = 255;
const u16 NVR_MAX_FILE_NAME_LEN = 255;
const u16 NVR_MAX_PARTION_NAME_LEN = 255;

// �澯��ͼƬת������¼����
#define MAX_ANR_NUM       20     
#ifdef _NVR2820L_
const u8 MAX_RECANR_NUM =  2 ;
#else
#ifdef _NVR1825_
const u8 MAX_RECANR_NUM =  1 ;
#else
const u8 MAX_RECANR_NUM =  4 ;
#endif
#endif

const u8 MAX_RECBAK_NUM = 1;
const float F_EPSINON = 1/100000; //ʮ���֮һ

// ��������Ͷ���,�����ͺ�IPCam-MSeries�� GNC-700SeriesͳһΪVT-200 Series
//#define VtcpSeries       "VT-200 Series"
#define VT200Series      "Vitor VT-200 series"
#define IPCamMSeries     "IPCam-MSeries"
#define GNC700Series     "GNC-700Series"

#define RTSPSeries       "RTSP"
#define RTSPSeries2      "ANNA"

#define KDM201_D01H      "KDM201-D01H"

// ����onvif�豸����
#define ONVIF            "ONVIF"

#ifndef _NVR2821H_
const u8 STACK_DEPTH = 128;
#else
const u8 STACK_DEPTH = 16;
#endif

const u8 MAX_TARGET_PORTAL_UN = 31;
const u8 MAX_TARGET_PORTAL_PWD = 31;
const u8 MAX_TARGET_UN = 31;
const u8 MAX_TARGET_PWD = 31;
const u8 MAX_TARGET_DEVICENAME = 31;
const u8 MAX_TARGET_IDE = 63;
const u8 MAX_SYSTARGET_NUM = 32;        //ϵͳ�пɽ����TARGET����
//const u8 MAX_TARGETINONEPOTRAL_NUM = 32;        //һ��PORTAL��TARGET���������
const u8 MAX_TARGETINONEPOTRAL_NUM = 10;        //һ��PORTAL��TARGET��������� 
//���portal�б�֪ͨ��Ϣ�ṹ��̫�󣬷�ֹ�������̱� <2011_11_2 KSW>

const u8 MAX_TARGET_NAME = 100;        //ϵͳ�пɽ����TARGET����

const u8 MAX_SYSTARGETPORTAL_NUM = 10;	//ϵͳ�пɽ����TARGETPORTAL����		

const u8 MAX_PLAY_KFPIC_NUM = 10;	//����ؼ�֡ ����ͼ

const u16 MAX_TRANSPARENT_LEN = 1024*8;
const u16 CMSI_MSG_REC_MAX_LEN = 100;
const u32 RECO_FAC_PWD_CNT  =   100; 
const u16 MAX_MSG_RCV_NUM= 10;

const u8  MAX_TIME_STRING_LEN = 32;

const u8  NVR2820H_MAX_MPU_STYLE_NUM = 10;
const u8  NVR2820H_MAX_MPU_PIC_NUM = 24;

#define UPDATE_TYPE_UBOOT	    1
#define UPDATE_TYPE_IOS		    2
#define UPDATE_TYPE_APP		    3
#define UPDATE_TYPE_SYS		    4
#define UPDATE_TYPE_ALL		    5
#define MAX_DVS_VERINFO_LEN     64
#define MAX_DVS_VER_USER_LEN    256

#define MAX_USER_DEF_DATA_LEN		 256
#define MAX_USER_DEF_DATANAME_LEN    33

#define SHARP_PARAM		"sharpparam"
#define NVRBACKUPSTATUS "nvrbackupstatus"
#define ENABLEOPERATEPSD "enableoperatepsd"

const u8 MAX_URL_LENGTH	= 255;
const u8 MAX_PKGVERSION_LEN= 128;

#ifdef _KDMD01F_
#define DEFAULT_PASSWD  "admin"
#else
#define DEFAULT_PASSWD  "admin123"
#endif

#define DEFAULT_VT_PASSWD  "vt8888"
#define DEFAULT_VT_ROOTPASSWD  "abc2813"
#define DEFAULT_SUPERADMIN  "k.e.d.a.c.o.m_n.v.r_a.d.m.i.n"
#define DEFAULT_SUPERADMIN_PASSWD "kedacomadmin123"

// enable 4 channel d1 for nvrd01
#define ENABLE_4CHANNEL_D1

#define VITOR

// for nvr2820L define
#define NVR_RESET_TIMES           3  // ����3������Ϊreset������Ч

#define NVR_CMD_LEN               128
#define NVR_FILE_PATH_LEN         128

#define NVR_MAX_ENC_NUM           4
#define NVR_MAX_LED_NUM           4

#define NVR_DVS_NOUSE             0
#define NVR_DVS_ONLINE            1
#define NVR_DVS_OFFLINE           2

// 20100915-suker-add print function macro, linux(have) or win32(no)
#ifdef WIN32
    #define _FUN_     "FUNCTION"
#else
    #define _FUN_      __FUNCTION__
#endif

// 20100916-suker-add notify pui receive media type stream
#define NVR_MEDIA_VIDEO     (u8)1 // ֻ����Ƶ
#define NVR_MEDIA_AUDIO     (u8)2 // ֻ����Ƶ
#define NVR_MEDIA_UNKNOW    (u8)3 // �ַ���δ֪��Ϣ
#define NVR_MEDIA_MAX_NUM   (u8)3 // �ַ���δ֪��Ϣ


/* Ԥ¼ʱ�� - Pre-recorded duration*/
#if (defined _NVR1037_)
    #define NVR_PRE_REC_DURATION         6	//NVR2821HԤ¼ʱ��
#elif (defined _NVR2860_)
    #define NVR_PRE_REC_DURATION         10 /*18*/ 
#elif (defined _NVR2820L_)
    #define NVR_PRE_REC_DURATION         15
#else // nvr2840 or 2820
    #define NVR_PRE_REC_DURATION         10
#endif

const u32 NVR_PRE_REC_DURATION_1821 = 20;
const u32 NVR_PRE_REC_DURATION_1822 = 10;
const u32 NVR_PRE_REC_DURATION_1825 = 5;

// ��ONVIF�ڴ治�㣬��С [8/12/2013 wangtianling]
#define NVR_PRE_REC_DURATION_2820HND     NVR_PRE_REC_DURATION/*60*/

/* ¼������� */
#define NVR_REC_BITRATE                  2048*1024

/* 2820L Э���ʼ����·���� 4·�������� */
#ifdef _NVR2820L_
    #define NVR_PUI_INIT_LINK_NUM          32
#else
    #define NVR_PUI_INIT_LINK_NUM          128
#endif

/* Ĭ�ϵ����� ���� */
    #define NVR_ENC_MAIN_BITRATE         2048
/* Ĭ�ϵ�����1080P ���� */
    #define NVR_ENC_MAIN1080P_BITRATE    6144
/* Ĭ�ϵ�QCIF���� ���� */
    #define NVR_ENC_SECQ_BITRATE          192
/* Ĭ�ϵ�CIF���� ���� */
#ifndef _NVR1822_
	#define NVR_ENC_SECC_BITRATE          1024
#else
	#define NVR_ENC_SECC_BITRATE          384
#endif

/* ɾ��NVR������ - ϵͳ����ʱ�����˶��� */
#if (defined _NVR2820_)
    #define NVR_RM_UPGRADE_FILE_CMD         (LPCSTR)"rm /usr/*.pkg.gz"
#elif (defined _NVR2820L_)
    #define NVR_RM_UPGRADE_FILE_CMD         (LPCSTR)"rm /usr/*.pkg"
#else // nvr2840 or 2860
    #define NVR_RM_UPGRADE_FILE_CMD         (LPCSTR)"rm /NVR2860/*.tar.bz2"
#endif

#define MAXLEN_E2PROM_VERSION		 		14

#define NVR_DFT_IP_ADDR                     (LPCSTR)"192.168.1.100"
#define NVR_DFT_NETMASK                     (LPCSTR)"255.255.255.0"
#define NC_DOWN_SMART_INFO_PATH				"/tmp/diskallsmart.txt"

// 20100916-suker-add pointer is NULL, print error info
#define NVR_POINTER_NULL_RTN(pointer, str) \
    if (NULL == pointer)                     \
    {                                        \
        printf("%s(): %s", _FUN_, str);      \
        NvrLog("%s(): %s", _FUN_, str);      \
        return;                              \
    }

// 20100919-suker-add pointer is NULL, print error info
#define EQP_POINTER_NULL_RTN(pointer, str) \
    if (NULL == pointer)                     \
    {                                        \
        printf("%s(): %s", _FUN_, str);      \
        EqpLog("%s(): %s", _FUN_, str);      \
        return;                              \
    }

#define NVR_TRUE     (u8)1 // Ϊ��
#define NVR_FALSE    (u8)0 // Ϊ��

#define PUI_RCV_STREAM_TVWALL_BROWSE          0
#define PUI_RCV_STREAM_TVWALL_PLAY_REC        1
#define PUI_RCV_STREAM_ONDS_TVWALL_BROWSE         2

#define SUPPORT_128	128
#define BAK_PIC_DIR_TAIL "/pic_bak/"
#define ONVIF_WMS_START_FLAG_TABLE_NAME "OnvifWmsStartFlagTable"
#define SEC_ADAPT_TABLE_NAME "SecResAdaptTable"
#define DVD_BURN_DIR "/ramdisk/dvd"
#define CLEAR_DVD_BURN_DIR "rm -rf /ramdisk/dvd/*"
const u32 DVD_BURN_MIN_MEM = 400*1024;
const u8  MAXNUM_DISC_TASK_LIST	= 64;		//����������¼�������
const u16   MAXLEN_CASE_NAME	= 64;		//�������Ƶ����


const u8 MAXNUM_ONDS	 =    64 ; // ���Onds
#define MAXNUM_ONDSINS		128	// һ��nc�������ӵ�����NVR������

#define ONDS_TIME_RECONNECTNVR		10*1000	// ���5s����������
#define ONDS_TIME_RELOGIN_NVR		60*1000	// ���60s��ʼ��¼

const u8 NVR_POWER_STAT_BRD_POWEROFF = 5;

#define NETRA_IFCFG_TMP "/usr/etc/network/.interfaces_tmp"
#define NETRA_HWINFO_TMP "/usr/bin/appres/.hwinfo_tmp"
#define NETRA_HWINFO "/usr/bin/appres/hwinfo"
#define NETRA_IFCFG "/usr/etc/network/interfaces"
#define NETRA_RM_UPDATE "rm -rf /usr/.update"
#define MK_ROOT_RW "mount -o remount,rw /"
#define MK_ROOT_RO "mount -o remount,ro /"
#define SYNC_MEM_FILES_CMD "sync_file"
#define MAX_LINK_DEC_NUM              32
#define MAX_LINK_DEC_D01F_NUM         16
#define MAX_DISPLAY_MODE_NUM         32
#define MAX_LINK_SUPPORT_RESOLUTION 5
#define MAX_D01F_DECRECVPORT_SEQ  4   //D01F������,���ն˿ڣ�ÿ��������port���4

#define D01F_MODE_G7221   0
#define D01F_MODE_ADPCM  1
#define D01F_MODE_PCMA    2
#define D01F_MODE_PCMU    3


#define D01F_AUDIO_INPUTTYPE_LINEIN                 0x00
#define D01F_AUDIO_INPUTTYPE_MIC                    0x01

const u8 NVR_RP_VER_BASE = 10; //¼������汾������nvr��ncʹ��
#define  LINK_CLEAR_WIN_PATH                                                                     "/usr/bin/appres/clearpic/"

const u16 IVIEW_RTSP_PORT = 554;
const u16 IVIEW_RTP_PORT = 30098;
const u16 IVIEW_RTCP_PORT = 30099;

const u16 MAX_D04F_CHN_NUM = 64; //D04F������ͨ��
const u16 MAX_BOARD_CHN_NUM = 32; //������������ͨ��
const u8 MAX_D04F_HMDI_NUM = 4;   //���HDMI����
const u8 MAX_HMDI_CHN_NUM = 16;   //ÿ��HMDI��Ӧ������ͨ��
const u8 MAX_DEC_PARAM_CHN =64;  //��������ͨ����
const u8 MAX_AUD_NUM =5;  

const u32 BAK_NORMAL_SPEED = 800;
const u16 PLAT_PLY_CMD		= 1;
const u8 MAX_EMAIL_NUM   = 8;	//�������Ŀ��������Ŀ
const u8 MAX_EMAIL_BUF_LEN = 128; //���������������������󳤶�
//1037ʹ��
#define APACHE_DIR "/etc/apache2"
#define APACHE_PORT_CONF "/etc/apache2/ports.conf"
#define APACHE_TMP_PORT_CONF "/etc/apache2/.ports.conf"
#define SITES_ENABLED_DEFAULT "/etc/apache2/sites-enabled/000-default"
#define TMP_SITES_ENABLED_DEFAULT "/etc/apache2/sites-enabled/.000-default"
#define SMTP_DNS_SER_USRID	100       //��ѡDNS������

/********macro definition for GB****************/
#define  GB_MAX_URI_LEN 256
#define  GB_MAX_DOMAIN_NAME_LEN 256
#define  GB_MAX_REGISTER_USERNAME_LEN 64    //�û�����󳤶�
#define  GB_MAX_REGISTER_PASSWORD_LEN 128   //�������󳤶�
#define  GB_MAX_IP_ADDR_LEN           15    //IP��ַ�ַ�����ʾ����󳤶�
#define  GB_ID_NO_LEN             (u8)20    //����ID�ĳ���
#endif

