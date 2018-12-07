/*****************************************************************************
   模块名      : nvr
   文件名      : nvrconst.h
   相关文件    : 
   文件实现功能: NVR常量定义
   作者        : 胡昌威
   版本        : V1.0  Copyright(C) 2007-2008 KEDACOM, All rights reserved.
-----------------------------------------------------------------------------
   修改记录:
   日  期      版本        修改人      修改内容
   2007/02/11  1.0         胡昌威       创建
   2007/05/15  1.0         何志川       进行添加修改
   2008/11/07  2.0         张开羽		2.0与1.0兼容性修改
******************************************************************************/

#ifndef __NVRCONST_H_
#define __NVRCONST_H_
#include "kdvtype.h"

#ifndef TEST_128
#define TEST_128  (64)
#endif
//长度参数定义
/*******************************以下宏定义为1.0与2.0使用不相同的宏**************************/
//**********1.0使用
//const u8     MAXNUM_DVS10                    = 16  ;    //最大DVS个数
const u8     MAXNUM_DEC10                = 16  ;    //NVR最大解码器个数
const u8     MAXNUM_ENC10					 = 16  ;    //NVR最大编码器个数        1.0中使用MAXNUM_DVS。
const u8     MAXNUM_DECCHN10					 = 16  ;	//NVR最大解码通道数 ???
const u8     MAXNUM_ENCCHN10                 = 16  ;    //NVR最大编码通道数
const u8     MAXNUM_USER10					 = 16  ;    //最大用户数
const u8     DECODER_BASE_ID10               = 200 ;    //解码器起始ID

///////////////////////////业务内部使用////////////////////////////////////////////////
const u8     MAXNUM_MPUSTYLE10               = 16  ;    //最大MPU风格数
const u8	 MAX_RECORDER_NUM10				 = 16  ;	//录像通道的最大数量
const u8	 MAX_PLAY_NUM10					 = 20  ;	//放像通道的最大数量

//电视墙
//const u8  MAX_TVWCHN10						  =	16 ;		//TVWALL可以控制的最大通道数
//const u8  MAXNUM_TVWCHN10					  =	16 ;        //MPU可以控制的最大通道数
//const u8  MAXNUM_TVWDVS10					  =	16 ;        //最大轮询通道数
//const u8  MAXNUM_TVWCYCLEPROJ10				  =	16 ;        //参与轮询的最大方案数 
//const u8  MAXNUM_TVWSCHEME10				  =	16 ;        //最大轮询方案数 
//const u8  MAXNUM_TVWPROJ10					  =	16 ;		//最大电视墙预案数
//const  u8 PART_MAX_NR_NVR10					  = 16 ;		//磁盘允许的最大分区个数
//const u8     MAXNUM_SCHEME10                 = 16  ;    //最大方案个数
//const u8     MAXNUM_MPUSCHEME10              = 16  ;    //最大MPU方案
//const u8     MAXNUM_MPUPLAN10                = 16  ;    //最大MPU轮询计划
//const u8     MAXNUM_MPUCHN10                 = 16  ;    //最大MPU通道数
/***************************************************************************************/
//**********2.0使用
//const u8     MAXNUM_DVS                    = 64  ;    //最大DVS个数       ??
const u8     MAXNUM_DECCHNNUM_FORONE	   = 16	 ;	  //单个解码器包含的最大通道数． 
const u8     MAXNUM_DEC					   = 64  ;    //NVR最大解码器个数
const u8     MAXNUM_ENC		               = TEST_128  ;    //NVR最大编码器个数
const u8     MAXNUM_DECCHN                 = 64  ;	  //NVR最大解码通道数 ???
const u8     MAXNUM_ENCCHN                 = TEST_128  ;    //NVR最大编码通道数  

const u8     MAXNUM_USER                   = 65  ;    //最大用户数,新增一个superadmin
const u8     DECODER_BASE_ID               = 128;     //解码器起始ID
/***************************************************************************************/

const u8     MAXNUM_DVSCHN                 = 16  ;    //DVS最大通道数     单个编码器，解码器的最大通道数。
//const u8     MAXNUM_DECODERCHN             = 5   ;    //最大解码器通道数			1.0中使用。


const u8     MAXNUM_SCHEME                 = 16  ;    //最大方案个数 //删除
const u8     MAXNUM_MPUSCHEME              = 16  ;    //最大MPU方案
const u8     MAXNUM_MPUPLAN                = 16  ;    //最大MPU轮询计划

const u8	 MAXNUM_TVWCHN				   = 16  ;    //TVWALL可以控制的最大通道数
const u8	 MAXNUM_TVWDVS				   = 16  ;    //最大轮询通道数
const u8	 MAXNUM_TVWCYCLEPROJ		   = 16  ;    //参与轮询的最大方案数 
const u8	 MAXNUM_TVWSCHEME			   = 16  ;    //最大轮询方案数 
const u8	 MAXNUM_TVWPROJ				   = 16  ;	  //最大电视墙预案数 需求为16个预案
const u8	 MAX_SYNCPLAY_NUM			   = 4   ;	  //同步放像通道的最大数量
const u8     MAXNUM_CAMERA                 = 16  ;   //最大视频源个数

const u8     MAXNUM_CHNGROUP               = 16  ;    //最大设备组个数



const u16    MAXLEN_PUID                   = 32  ;    //PUID最大长度
const u8     MAXHDMI_VIDEOOUT_NUM           = 4 ;   //D04F,HDMI输出个数

const u16    MAX_MATRIX_VIDEOSRC_NUM       = 16;      // 矩阵接入最大输入端口数 
const u16	 MAXNUM_FILE			       = 800;     //抓拍最多文件列表个数

const u8	 MAXLEN_NAME                   = 32  ;   //设备名字
const u8     MAXLEN_ALIAS                  = 32  ;   //别名长度
const u8	 MAXLEN_GUID                   = 32  ;   //GUID长度
const u8     MAXLEN_PATH                   = 255 ;   //最大路径长度
const u8     MAXLEN_USERNAME               = 32  ;   //最大用户名长度
const u8     MAXLEN_PWD                    = 32  ;   //最大密码长度
const u8     MAXLEN_EMAIL                  = 63  ;   //E-mail支持最大字符
const u8     MAXLEN_TEL                    = 23  ;   //电话号码最大长度
const u8     MAXLEN_OSD                    = 64+1;   //最大的OSD长度,与VSIP协议栈一致
const u16    MAXLEN_MSGHDR                 = 24  ;   //最大消息头长度  CNvrMsg专用
const u16    MAXLEN_MSG                    = 0x4000   ;//最大消息体长度
const u8     MAXLEN_FILELEN                = 255 ;   //最大文件名长度
const u8     MAXLEN_LOG                    = 255 ;   //最大日志长度
const u16    MAXLEN_SELFDEFBUF             = 1024;   //自定义的消息buf长度
const u8     MAXLEN_LIST                   = 255 ;   //邮件、地址列表等
const u8     MAXLEN_DESC                   = 255 ;   //描述的最大长度
const u8     MAXLEN_ENCRYPTKEY             = 128 ;   //密钥的最大长度
const u8     MAXNUM_NET_PORT               = 6   ;    //最大网口数目
const u8	 MAXNUM_IP					   = 8	 ;	  //一个网口可以设置的IP数
const u8     MAXNUM_MD_AREA                = 16  ;    //最大移动侦测区域个数
const u8     MAXNUM_WEEK_DAY               = 7   ;    //一周最大天数
const u8     MAXNUM_DAY_TIMESEG            = 4   ;    //一天最大时间片
const u8     MAXNUM_HARDDISK               = 16  ;    //最大硬盘个数
const u8     MAXNUM_ALARMIN                = 16  ;    //最大报警输入
const u8     MAXNUM_ALARMOUT               = 16  ;    //最大报警输出
const u8     MAXNUM_EQP                    = 36  ;    //最大设备个
const u8     NVR_MAXNUM_ALARMIN            = 18  ;    //最大报警输入
const u8     NVR_MAXNUM_ALARMOUT           = 10  ;    //最大报警输出
const u16    REC_BACK_SECTION_TIME         = 30 * 60; //录像备份分段间隔时间（s）
const u8	 BAKTYPEINIT				   = 0;		  //初始数据，业务默认作为备份ASF处理
const u8	 BAKTYPERAWDATA				   = 1;		  //备份裸数据
const u8	 BAKTYPEMP4					   = 2;		  //备份MP4
const u8	 BAKTYPEASF					   = 3;		  //备份ASF
const u8	 BAKTYPEM4A					   = 4;		  //备份M4A
const u8     REC_BACK_ADJUST_TIME          = 3;       //录像备份结束点校正时间
#if defined(_NVR2860_) || defined(_NVR2821H_)
	const u8     MAXNUM_NC                     = 68  ;    //最大客户端数 原来是17，现在改为68
#else
	const u8     MAXNUM_NC                     = 17  ;    //最大客户端数
#endif
	const u8	 SWITCH_ID					   =  MAXNUM_NC + 2; //拨码开关<2012_2_24 KSW>

const u8     MAXNUM_PUI                    = 2   ;    //最大PUI数
//const u8     MAXNUM_NCCHN                  = 72  ;    //NC最大通道数
const u8     MAXNUM_NCCHN                  = 128  ;    //NC最大通道数
const u8     MAXNUM_VIDSRCCHN              = 16  ;    //DVS最大视频源通道数
const u8     MAXNUM_SEARCH                 = 250 ;    //最大搜索数
const u8     MAX_VSIP_NUM_NTY_EVERYTIME    = 128 ;    //一次最多上报的VSIP搜索到的设备数目
const u8     MAX_ONVIF_NUM_NTY_EVERYTIME   = 25  ;    //一次最多上报的ONVIF搜索到的设备数目
const u8     MAXNUM_TIMESEG                = 57 ;     //定时、周期的时间段总数
const u16    MAX_COMDATA_LEN               = 512 ;    //最大串口数据长度
const u16	 MAX_TAG_LEN				   = 32 ;  	  //标签的最大长度
const u16	 MAXLEN_ALAMADUIOFL			   = 32 ;     //告警音频文件名	
const u16	 MAXNUM_SA_AREA				   = 16 ;     //图像隐蔽区域数量
const u16	 MAX_NVR_PICFILE_PACK_LEN	   = 4096;    //抓拍图片包的最大长度
#ifdef _NVR2820L_
const u8	 MAX_DVSREC_NUM				   = 4	;	  //前端录像通道的最大数量
const u8	 MAX_DVSPLY_NUM				   = 16 ;	  //前端放像通道的最大数量
#else
const u8	 MAX_DVSREC_NUM				   = TEST_128	;	  //前端录像通道的最大数量
const u8	 MAX_DVSPLY_NUM				   = 64 ;	  //前端放像通道的最大数量
#endif
const u16    MAX_PU_LOGO_PACK_LEN          = 1024;    //最大台标文件包长度
const u16    CUR_PC_UNIT				   = 1024;	  //通常的换算单位
const u16    MAX_LANG_NUM				   = 2;       //最大支持的语种数
const u16    MAX_DESC_NUM                  = 1000;    //最大描述数
const u16	 MAX_SERVNAME_LEN			   = 255;	  //PPOE拨号服务商的名字长度
const u8	 MAX_AUDIOIN_PORT_NAME_LEN	   = 8 ;      //最大音频输入端口名长度   
const u8	 MAX_VERSION_NUM_LEN		   = 64 ;     //版本号最大长度	
const u8	 MAX_PROOFPASSWORD_LEN		   = 64 ;	  //最大验证密码长度
const u8	 MAX_WEBUSERNAME_LEN		   = 64 ;	  //最大验证密码长度
const u16    MAX_DDNSSTATE_LEN             = 4096;     //描述ddns状态字符串的长度
const u16	 MAXNUM_CUR_ALARM			   = 255;	  //当前告警最多时数目
const u8	 MAXLEN_IPSTR				   = 15	;    //ip字符串的长度
const u8	 MAXLEN_FILENAME			   = 250;     //最大文件名长度
const u8	 MAXLEN_FILEPATH               = 250;    //最大路径名长度
const u8	 MAXLEN_BAKFILENAME			   = 70;	 //最大文件名长度
const u16 	 MAXLEN_CONTENT  		       = 255;		//
const u8     MAX_DEV_INFO_LEN              = 128 ;    //参数信息最大长度

//业务APP号定义
const u8     AID_NVR_EQPSSN                = 15  ;		//nvr设备会话  // 原来18==>15 同[SnmpAdp][SAgtSsnInst.1]冲突 [10/16/2008 zhangkehui]
const u8     AID_NVR_SERVICE               = 16  ;		//nvr业务
const u8     AID_NVR_GUARD                 = 17  ;		//nvr守卫
const u8     AID_NVR_EQPSSN10              = 18  ;	//nvr设备会话
const u8     AID_NVR_NCSSN                 = 19  ;		//nvr本地接受客户端消息的会话
const u8     AID_NVR_PUISSN                = 20  ;		//nvr前端接入会话
const u8     AID_NVR_VTDUSSN               = 21  ;		//nvr分发转发会话
const u8     AID_PUI_EXTSSN                = 22  ;		//nvr分发转发会话
const u8	 AID_NCLIB_APP				   = 27	 ;		//nclib会话	
const u8	 AID_WMS_APP				   = 28  ;		//wvms会话
const u8     AID_NVR_EQP                   = 30  ;		//nvr设备会话
//const u8   AID_NVR_NC		               = 31  ;		//nvr客户端会话
const u8     AID_NVR_PUI                   = 32  ;		//nvr前端接入会话
const u8     AID_NVR_VTDU                  = 33  ;		//nvr分发转发会话
const u8	 AID_NVR_DM					   = 34  ;		//磁盘管理会话
const u8     AID_NVR_CMSI                  = 35  ;      //nvr平台接入模块
const u8     AID_NVR_CMSISSN               = 36  ;      //nvr平台接入模块会话(nvr业务端)
const u8	 AID_NVR_PS					   = 37  ;		//分区同步会话
const u8     AID_NVR_RBQ				   = 38  ;		//录像数据查询任务
const u8     AID_NVR_LOG                   = 40  ;      //nvr日志
const u8     AID_NVR_TEST                  = 41  ;      //nvr 测试
const u8     AID_PTFIX_APP                 = 42  ;      //分区修复
const u8     AID_NVR_PTFSSN                = 43  ;      //分区修复会话
const u8     AID_TEST_NVR				   = 44;		  //TEST的会话
const u8     AID_NVR_TEST2				   = 45  ;		  //NVR与TEST交互的会话
const u8     AID_NVR_ANR				   = 46	 ;		 //ANR模块APP
const u8     AID_NVR_DSCHK				   = 47	 ;		 //DSCHECK模块APP
const u8     AID_NVR_GRB				   = 48	 ;		 //GRB模块APP
const u8     AID_DS_KEEPALIVE			   = 49	 ;		 //DS keepalive 触发模块APP
const u8     AID_WD_MONITOR		           = 50	 ;		 //watch dog监视APP
const u8	 AID_DEVRAID_APP			   = 51	 ;		//磁盘阵列服务APP
const u8     AID_PUI_EXT                   = 52  ;		//PuiEXT(Pui扩展)模块APP
const u8     AID_NVR_ONDS                  = 53  ;      //跨nvr调度日志
const u8     AID_NVR_ONDSSN                = 54  ;      //跨nvr调度日志nvr session
const u8     AID_GBPROXY_SRVNVR            = 55  ;      //国标代理伺服NVR模块APP
const u8     AID_GBPROXY_SRVCM             = 56  ;      //国标代理伺服平台模块APP

const u8	 AID_VTDU	                   = 67	 ;      //VTDU
const u8	 AID_MONITOR				   = 73	 ;		// 监视程序
const u8	 AID_DI_APP					   = 77	 ;		//web调试信息会话
const u8	 AID_NVR_SMTP				   = 78	 ;		//web调试信息会话

const u8     LOG_MODULE_NUM                = 10  ;		//日志模块的数目
const u8	 PUI_ID						   = 1   ;
const u8	 VTDU_ID					   = 1   ;
const u8	 PUI_EXT_ID					   = 1   ;

const u8	 ONDS_ID					   = 1   ;

//传送图像声音参数模式
const u8	 MODE_NONE			           = 0	 ;     //音视频都不传
const u8	 MODE_VIDEO					   = 1	 ;     //只传视频
const u8	 MODE_AUDIO					   = 2	 ;     //传音频
const u8	 MODE_BOTH					   = 3   ;     //音视频都传

//日志打印级别
const u8     LOGLVL_EXCEPTION	           = 1	 ;     //异常
const u8     LOGLVL_IMPORTANT	           = 100 ;     //重要日志
const u8     LOGLVL_DEBUG1	               = 150 ;     //一级调试信息
const u8     LOGLVL_DEBUG2		           = 200 ;     //二级调试信息

//设备厂商定义
const u8     DEVMANU_UNKNOW                = 0   ;     //未知
const u8     DEVMANU_KEDACOM               = 1   ;     //科达科技
const u8	 DEVMANU_SUNELL				   = 2	 ;	   //景阳
const u8	 DEVMANU_SONY				   = 3   ;     //索尼

 //码流交换类型
const u8    UNICAST                        = 1   ;      //单播
const u8    DIRECTTRANS                    = 2   ;      //单播直传
const u8    MULTICAST                      = 3   ;      //组播   

//VDTU的接收码流类型
const u8   M2P                             = 0   ;      //多对1 
const u8   P2P                             = 1   ;      //点对点

//告警管理
//告警类型
const u8  ALARMTYPE_PININPUT               = 1   ;    //并口输入告警
const u8  ALARMTYPEE_MOVDET                = 2   ;    //移动侦测告警
const u8  ALARMTYPEE_RESERVED1             = 3   ;    //告警1[保留]
const u8  ALARMTYPEE_RESERVED2             = 4   ;    //告警2[保留]

//告警标志
const u8 ALARMRESUME                       = 0   ;    //告警恢复
const u8 ALARMOCCUR                        = 1   ;    //告警产生 

//摄像头控制命令
//摄像头命令参数
const u8 CAMCTRL_COMMAND_MOVEUP	=  1 ;	//向上移动
const u8 CAMCTRL_COMMAND_MOVEDOWN	=  2	;	//向下移动
const u8 CAMCTRL_COMMAND_MOVELEFT	=  3	;	//向左移动
const u8 CAMCTRL_COMMAND_MOVERIGHT	=  4	;	//向右移动
const u8 CAMCTRL_COMMAND_MOVEHOME	=  5	;	//回归
const u8 CAMCTRL_COMMAND_MOVESTOP	=  6	;	//停止移动
const u8 CAMCTRL_COMMAND_ZOOMTELE	=  7	;	//拉近摄像头
const u8 CAMCTRL_COMMAND_ZOOMWIDE	=  8	;	//拉远摄像头
const u8 CAMCTRL_COMMAND_ZOOMSTOP	=  9	;	//视野调节停止
const u8 CAMCTRL_COMMAND_FOCUSFAR	=  10   ;	//将焦距调远
const u8 CAMCTRL_COMMAND_FOCUSNEAR	=  11   ;	//将焦距调近
const u8 CAMCTRL_COMMAND_FOCUSAUTO	=  12   ;	//自动调焦
const u8 CAMCTRL_COMMAND_FOCUSSTOP	=  13   ;	//调焦停止
const u8 CAMCTRL_COMMAND_PRESETSET	=  14   ;	//摄象头预存
const u8 CAMCTRL_COMMAND_PRESETCALL	=  15	;	//调摄象头预存
const u8 CAMCTRL_COMMAND_CAMERASET	=  16   ;	//初始化摄像头
const u8 CAMCTRL_COMMAND_BRIGHTUP	=  17   ;	//画面调亮
const u8 CAMCTRL_COMMAND_BRIGHTDOWN	=  18   ;	//画面调暗
const u8 CAMCTRL_COMMAND_BRIGHTSTOP	=  19   ;	//停止调亮
const u8 CAMCTRL_COMMAND_NEW		=  20   ;	//新命令
const u8 CAMCTRL_COMMAND_APPEND		=  21	;	//附加命令
const u8 CAMCTRL_COMMAND_QUERYPANPOS	=  22 ; //查询水平方位角
const u8 CAMCTRL_COMMAND_QUERYTILPOS	=  23 ; //查询垂直方位角
const u8 CAMCTRL_COMMAND_QUERYZOMPOS =  24  ;	//查询放大倍数  ??

const u8 CAMCTRL_COMMAND_STARTAUTOSCAN = 24 ;   //开始自动巡航	
const u8 CAMCTRL_COMMAND_STOPAUTOSCAN  = 25 ;   //停止自动巡航

const u8 CAMCTRL_COMMAND_STARTTOUR     = 26 ;    //巡视开始
const u8 CAMCTRL_COMMAND_ENDTOUR       = 27 ;    //巡视结束

const u8 CAMCTRL_COMMAND_SETHOMEPOS	   = 28 ;	 //设置HOME位

const u8 CAMCTRL_COMMAND_MENU_UP     = 35;		//菜单上
const u8 CAMCTRL_COMMAND_MENU_DOWN   = 36;		//菜单下
const u8 CAMCTRL_COMMAND_MENU_LEFT   = 37;		//菜单左
const u8 CAMCTRL_COMMAND_MENU_RIGHT  = 38;		//菜单右

const u8 CAMCTRL_COMMAND_MENU_SHOW   = 39;		//菜单显示
const u8 CAMCTRL_COMMAND_MENU_HIDE   = 40;		//菜单隐藏

const u8 CAMCTRL_COMMAND_MENU_ENTER  = 41;		//菜单确定
const u8 CAMCTRL_COMMAND_MENU_EXIT   = 42;		//菜单取消

const u8 CAMCTRL_COMMAND_IMAGE_SHOW  = 43;      // 图像正显示
const u8 CAMCTRL_COMMAND_IMAGE_ANTISHOW = 44;   // 图像反显示

const u8 CAMCTRL_COMMAND_GOTOPOINT   = 45;      // 点击居中
const u8 CAMCTRL_COMMAND_ZOOMPART    = 46;      // 局部放大
const u8 CAMCTRL_COMMAND_ZOOMWHOLE   = 47;      // 局部缩小

const u8 CAMCTRL_COMMAND_BACKLIGHT_ON    = 48;    // 背光开
const u8 CAMCTRL_COMMAND_BACKLIGHT_OFF   = 49;    //  背光关

const u8 CAMCTRL_COMMAND_WIDEDYNAMIC_ON    = 50;    // 宽动态开
const u8 CAMCTRL_COMMAND_WIDEDYNAMIC_OFF   = 51;    // 宽动态关

const u8 CAMCTRL_COMMAND_DAYNIGHTMOD_ON    = 52;    // 日夜模式开
const u8 CAMCTRL_COMMAND_DAYNIGHTMOD_OFF    = 53;    // 日夜模式关
const u8 CAMCTRL_COMMAND_DAYNIGHTMOD_AUTO   = 54;    // 日夜模式自动

const u8 CAMCTRL_COMMAND_HORIZONTAL_TURN = 55;        // 云台水平180度翻转
const u8 CAMCTRL_COMMAND_TURNTO_MACHINEZERO = 56;           // 水平、俯仰电机转动到零位（零位校正,到机械零位）
const u8 CAMCTRL_COMMAND_LIMIT_HORIZONALLEFT = 57;          // 水平左限位
const u8 CAMCTRL_COMMAND_LIMIT_HORIZONALRIGHT = 58;          // 水平右限位
const u8 CAMCTRL_COMMAND_PRESET_REMOVE = 59;                 // 清除预置位
const u8 CAMCTRL_COMMAND_AUXILIARYSWITCH_SET = 60;           //  辅助开关设置
const u8 CAMCTRL_COMMAND_AUXILIARYSWITCH_REMOVE = 61;        // 辅助开关清除
const u8 CAMCTRL_COMMAND_ALARMINPUT_QUERY = 62;              // 科达查询报警输入信息,暂不支持
const u8 CAMCTRL_COMMAND_VIRTUALZERO_SET  = 63;              // 虚拟零位设置
const u8 CAMCTRL_COMMAND_VIRTUALZERO_REMOVE = 64;            // 虚拟零位清除
const u8 CAMCTRL_COMMAND_PTZ_RESET = 65;                     // 科达发送云台复位
const u8 CAMCTRL_COMMAND_ZOOMINFO_SEND =66;                 //科达发送变倍信息 
const u8 CAMCTRL_COMMAND_CAMERATYPE_SEND = 67;               // 科达发送相机类型
const u8 CAMCTRL_COMMAND_AUTOFLIP_ON = 68;                   // 自动翻转开
const u8 CAMCTRL_COMMAND_AUTOFLIP_OFF = 69;                  // 自动翻转关
const u8 CAMCTRL_COMMAND_DEPTHRATESPEED_ON = 70;              //景深比例速度开
const u8 CAMCTRL_COMMAND_DEPTHRATESPEED_OFF = 71;             //景深比例速度关
const u8 CAMCTRL_COMMAND_SCANSPEED_SET = 72;                 //水平扫描速度（影响自动扫描速度）bySpeed(1-40s)
const u8 CAMCTRL_COMMAND_MANUALLIMITSWITCH_ON = 73;           //手动限位开
const u8 CAMCTRL_COMMAND_MANUALLIMITSWITCH_OFF = 74;          //手动限位关
const u8 CAMCTRL_COMMAND_SCANLIMITSWITCH_ON = 75;             //扫描限位开
const u8 CAMCTRL_COMMAND_SCANLIMITSWITCH_OFF = 76;            //扫描限位关
const u8 CAMCTRL_COMMAND_PANPOSION_SET = 77;                  //上位机设置水平位置
const u8 CAMCTRL_COMMAND_TILTPOSION_SET = 78;                 //上位机设置俯仰位置
const u8 CAMCTRL_COMMAND_PANPOSION_QUERY = 79;                //上位机查询水平位置
const u8 CAMCTRL_COMMAND_TILTPOSION_QUERY = 80;               //上位机查询俯仰位置
const u8 CAMCTRL_COMMAND_PANRESPONSE_QUERY = 81;              //球机返回水平位置
const u8 CAMCTRL_COMMAND_TILTRESPONSE_QUERY = 82;             //球机返回俯仰位置
const u8 CAMCTRL_COMMAND_FOCUSMODE_AUTO = 83;                 //聚焦模式自动
const u8 CAMCTRL_COMMAND_FOCUSMODE_MANUAL = 84;              //聚焦模式手动
const u8 CAMCTRL_COMMAND_IMAGE_LEFTRIGHT_REVERSE = 85;        //图像左右翻转
const u8 CAMCTRL_COMMAND_IMAGE_UPDOWN_REVERSE = 86;         //图像上下翻转
//const u8 CAMCTRL_COMMAND_BACKLIGHT_ON = 87;                   //背光补偿开
//const u8 CAMCTRL_COMMAND_BACKLIGHT_OFF = 88;                  //背光补偿关
const u8 CAMCTRL_COMMAND_STARVEMODE_ON = 89;                 //视频冻结开
const u8 CAMCTRL_COMMAND_STARVEMODE_OFF = 90;                 //视频冻结关
const u8 CAMCTRL_COMMAND_ZOOM_LIMIT = 91;                     //变倍限制(1-18)
const u8 CAMCTRL_COMMAND_ZOOMSPEED_FAST = 92;                 //变倍速度快速
const u8 CAMCTRL_COMMAND_ZOOMSPEED_NORMAL = 93;               //变倍速度正常
const u8 CAMCTRL_COMMAND_APERTUREMODE_AUTO = 94;             //光圈模式自动
const u8 CAMCTRL_COMMAND_APERTUREMODE_MANUAL_HIGHSPEED = 95;  //光圈模式手动高速
const u8 CAMCTRL_COMMAND_APERTUREMODE_MANUAL_MODERATESPEED=96;//光圈模式手动中速
const u8 CAMCTRL_COMMAND_APERTUREMODE_MANUAL_LOWSPEED = 97;   //光圈模式手动低速
const u8 CAMCTRL_CMMMAND_SHUTTERMODE_AUTO = 98;               //快门模式自动
const u8 CAMCTRL_COMMAND_SHUTTERMODE_MANUAL=99;             //快门模式手动
const u8 CAMCTRL_COMMAND_PLUSMODE_AUTO = 100 ;                 //增益模式自动
const u8 CAMCTRL_COMMAND_PLUSMODE_MANUAL = 101;                //增益模式手动
const u8 CAMCTRL_COMMAND_WHITEBALANCEMODE_AUTO=102;          //白平衡模式自动
const u8 CAMCTRL_COMMAND_WHITEBALANCEMODE_MANUAL=103;        //白平衡模式手动

const u8 CAMCTRL_COMMAND_ALL_AUTO = 104;                       //机芯全自动
const u8 CAMCTRL_COMMAND_WIPER_ON = 105;                       //雨刷开启
const u8 CAMCTRL_COMMAND_WIPER_OFF = 106;                     //雨刷关闭
const u8 CAMCTRL_COMMAND_IR_ON = 107;                         //红外开启
const u8 CAMCTRL_COMMAND_IR_OFF = 108;                         //红外关闭

const u8 CAMCTRL_COMMAND_MOVE_LEFTUP        =  131    ;	//向左上移动
const u8 CAMCTRL_COMMAND_MOVE_LEFTDOWN	    =  132    ;	//向左下移动
const u8 CAMCTRL_COMMAND_MOVE_RIGHTUP	    =  133    ;	//向右上移动
const u8 CAMCTRL_COMMAND_MOVE_RIGHTDOWN	    =  134    ;	//向右下移动
const u8 MAX_UPDATE_PKG_NUM  = 32 ; //升级包个数
const u8 MAX_CHN_NUM_ONE				= 1  ;	//通道数目限定
const u8 MAX_CHN_NUM_TWO				= 2  ;	//通道数目限定

const u8 MAX_CHN_NUM_FOUR				= 4  ;	//通道数目限定
const u8 MAX_CHN_NUM_NINE				= 9  ;	//通道数目限定
const u8 MAX_CHN_NUM_SIXTEN				= 16  ;	//通道数目限定

const u8 MAX_CHN_NUM_TWOFIVE				= 25  ;	//通道数目限定
const u8 MAX_CHN_NUM_THREETWO				= 32  ;	//通道数目限定
const u8 MAX_CHN_NUM_THREESIX				= 36  ;	//通道数目限定
const u8 MAX_CHN_NUM_FOURNINE				= 49  ;	//通道数目限定
const u8 MAX_CHN_NUM_SIXFOUR				= 64  ;	//通道数目限定

const u8 MAX_CHN_NUM_EIGHT					= 8;	//通道数目限定
const u8 MAX_CHN_NUM_TWELVE					= 12;	//通道数目限定
const u8 MAX_CHN_NUM_TWITY					= 20;	//通道数目限定
const u8 MAX_CHN_NUM_TWITYFOUR				= 24;	//通道数目限定
const u8 MAX_CHN_NUM_TWITYEIGHT				= 28;	//通道数目限定

//硬件code
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

//硬件hwid
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

//const u32 HWID_NVR1821_2821H			= 0x015C;		//NVR1821和NVR2821H使用相同的HWID
//const u32 HWID_NVR1821                  = HWID_NVR1821_2821H; //客户端兼容性问题
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
//设备product id
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

//2840E没有定义HWID 自选一个
const u32 NVR2840E_9						= 0x2034;
const u32 NVR2840E_16						= 0x2035;
const u32 NVR2840E_32						= 0x2036;
const u32 NVR2840E_4						= 0x2031;
const u32 NVR2840E_4_NEW					= 0x2032;

//录像文件类型
const u8	MD_ALARM		= 0x01 ;        //移动侦测告警文件
const u8	VIDEOLOST_ALARM = 0x02 ;        //信号丢失告警文件
const u8	SHADE_ALARM		= 0x04 ;        //图像遮挡告警文件
const u8	INPUT_ALARM		= 0x08 ;		//电平输入告警文件
const u8	CYC_RECORD		= 0x10 ;		//周期录像
const u8	HANDM_RECORD	= 0x20 ;		//手动录像
const u8	SELF_TAG1		= 0x40 ;		//自定义标签1
const u8	SELF_TAG2		= 0x80 ;		//自定义标签2
const u16	SELF_TAG3		= 0x100 ;		//自定义标签3

//磁盘分区
const u8	MAX_PARTITION_NUM		=	64	;		//最大分区数
const u8	MAX_HARDDISK_NUM		=	32	;		//最大磁盘数
const u8	MAX_PARTITION_NAME_LEN  =	128 ;		//分区的最大路径名

const u8	USER_DATA_LENGTH		=	128 ;		//用户自定义数据最大长度

const u16	MAX_CMD_LENGTH			=	512 ;       //最大命令长度

const u8	DEL_FOR_DVSID           =	1 ;			//以设备ID为删除条件 
const u8	DEL_FOR_DVSALIAS        =	2 ;			//以设备别名
const u8	DEL_FOR_DVSGUID         =	3 ;			//以设备的Guid
const u8	DEL_FOR_DVSENCNUM       =	4 ;			//以设备编码通道数目
const u8	DEL_FOR_DVSDECNUM       =	5 ;			//以设备解码通道数目
const u8	DEL_FOR_DVSIPADD        =	6 ;			//以设备的IP
const u8	DEL_FOR_DVSTYPE         =	7 ;			//以设备型号
const u8	DEL_FOR_DVSMUID         =	8 ;			//以设备厂商代码

const u8	TEST_INSERT				=	11;         //数据库插入测试

//VTDU 相关常量
#if defined(_NVR2820_) || defined(_NVR2820L_)
const u8 MAX_SWITCH_CHANNEL			=250;
#else
const u16 MAX_SWITCH_CHANNEL			=1000;
#endif
const u8 MAX_IP_ADDR				=16 ;
const u8 MAX_MP_NUM					=16 ;
const u8 MAX_MP_MTNUM				=TEST_128 ;			//最大支持转发64个终端码流
const u8 MAXNUM_NVR_CHANNEL			=16 ;			//最大NVR间码流路数
               
///---------NVR启动时NVR内嵌模块启动配置-----------------------------
const u8 STARTUP_NONE				=0	;	//不启动任何模块
const u8 STARTUP_MP					=1	;	//只启动mp模块
const u8 STARTUP_BOTH	 			=3	;	//两模块同时启动
const u8 MODE_NVR					=1	;	//附属于NVR
const u8 MODE_ABSOLUTE				=255;   //独立
//----------------------NVR外设类型定义------------------------------
const u8 TYPE_MATRIX				=4 ;    //视频矩阵
const u8 TYPE_KEYBOARD				=6 ;    //键盘处理
const u8 TYPE_DRS					=11;	//录像机
const u8 TYPE_SOCKET				=12;	//标准socket
const u8 TYPE_VPU					=13;	//VPU外设类型
const u8 MC_TYPE_DEFAULT			=1 ;    //控制台标识

// Fd limit [1/21/2013 wangtianling]
const s32 NVR_FD_LIMIT = 4096;

const u16 PING_DVS_INTERVAL  = 0x0A; // 默认前端断链检测时间间隔 10 S
const u16 PING_DVS_BREAK_NUM = 0x06; // 默认前端断链次数 6 次

//码流传输方式
const u8 TRANS_NORTCP =2;	//UDP传输模式(不接受/发送rtcp码流)
const u8 TRANS_UDP =0;		//UDP传输模式
const u8 TRANS_TCP =1;		//TCP传输模式

//MATRIX
const u8 MIN_MATRIX_ID   = 48 ;      //MATRIX的最小ID号
const u8  MAX_MATRIX_ID  = 64 ;      //MATRIX的最大ID号
const u8  MAXNUM_MATRIX  = 16 ;      //最大MATRIX数
const u8  MAX_MATRIX_IN_CHNNUM	=  255 ;//最大矩阵输入通道数
const u8  MAX_MATRIX_OUT_CHNNUM	=  255 ;//最大矩阵输入通道数
const u8  MAXLEN_MATRIX_ALIAS   =  7  ;  //矩阵假名最多7个字母，3个汉字

//组播
const u8  MAX_MULTI_NUM    =    128 ; //MCU最大组播组数量
const u8  MAX_MULTIRECV_NUM  =  32  ; //一个组播组允许最多接收者数量


const u32 MP_TIMESPACE_TASK_CHECK  =  10000; //单位(毫秒)  
const u32 MP_TIMESPACE_PING        =   8000; //单位(毫秒)  

const u32 MAX_SERDATA_BUF_LEN	   =  14*1024;
#define  MIN_MULTIIP          inet_addr("224.0.0.0")
#define  MAX_MULTIIP          inet_addr("239.255.255.255")

const u8  UNUSED_TIMELINE_NO_LIMIT       = 0;   //使用截止时间标志：不限制

const u8  SMALL_RECFILE_LENGTH			 = 150; //小录像文件持续时间 单位秒

const u8	TIME_INTERVAL	  = 150;
const u8    MPU_DEF_SCHID     = 255;			//默认MPU方案ID  		

const u8	MAX_BACKUP_USER	  = 16;				//最大备份用户数   
const u8	BAK_SUBNAME_LEN	  = 40;				//录像备份自文件名的长度

//前端录像文件查询条件
const u8	DVS_QUIEY_ALL_EVENT  =                0  ;  //查询所有事件
const u8	DVS_TYPE_PIN_ALARM   =              1    ;//并口告警录象
const u8	DVS_TYPE_MOTION_DETECT_ALARM   =    2    ;//移动侦测告警录象
const u8	DVS_TYPE_MANUAL        =            3    ;//手动录象
const u8	DVS_TYPE_TIMELY        =            4    ;//定时录象
const u8	DVS_TYPE_PERIODLY      =            5    ;//周期录象
const u8	DVS_QUIEY_FILE         =            6    ;//按文件查询

//----------------------NVR缺省端口号-------------------
const u16   NVR_SWITCH_STARTPORT  =   12000 ;   //接收 DVS码流端口号[12000---12096]
const u16   NVR_OFFSETPORT  =   1024 ;          //NVR接收/发送端口偏移量

const u16   NVR_DECSWITCH_STARTPORT  = 13000 ;	//解码器码流输出端口号
const u16	NVR_RTSP_LOCAL_PORT		 = 15000 ;	//RTSP的本地端口

const u16   NVR_DVSNATDETECT_PORTOFFSET  =   8 ;    //NVR接收DVS穿NAT探测包端口偏移量
const u16   NVR_NCNATDETECT_PORTOFFSET   =   12 ;   //NVR接收NC穿NAT探测包端口偏移量
const u16   NVR_RCVNCAUDIO_PORTOFFSET    =   512;   //接收NC音频码流的起始端口号偏移量
const u16   NVR_DOWNLOADTRANS_PORTOFFSET =   20 ;   //下载中转端口号


const u16	LOCAL_BACKUP_PORT = 34000;			//本地录像备份使用的起始端口34000~34064
const u16	FTP_SERVICE_PORT  = 35000;			//FTP下载端口   35000 ==> 1730 CU和NVR客户端使用同一个端口下载  
const u16	MPU_REC_PORT_BASE = 35500;			//本地默认的MPU接收端口号 35500 ~ 35800
const u16	REC_PLY_PORT_BASE = 36000;			//放像开始端口
const u16   DVS_REC_RESTORE_PORT = 37000;		//本地接收前端转存的端口

const u16   GB_TRANS_LOCALRCV_PORT = 40000;		//接国标平台，码流转至本地转码起始端口 

const u16   DVS_RCVAUD_PORT              =   60066; //DVS接收音频的端口
const u16   DVS_SENDVIDEO_RTPSTARTPORT   =   59000; //DVS发送视频RTP起始端口
const u16   DVS_SENDAUDIO_RTPSTARTPORT   =   59002; //DVS发送音频RTP起始端口
const u16   DVS_SENDVIDEO_RTCPSTARTPORT  =   60000; //DVS发送视频RTCP起始端口
const u16   DVS_SENDAUDIO_RTCPSTARTPORT  =   60002; //DVS发送音频RTCP起始端口
const u16   DVS_PLAYVIDEO_STARTPORT      =   60068; //DVS放像视频起始端口
const u16   DVS_PLAYAUDIO_STARTPORT      =   60070; //DVS放像音频起始端口
const u16   DVS_RCVAUD_PORT_2			 =   60102;	//DVS第二路接收音频端口

const u16   NVR_STARTRS_PORT             =	  50000;	//开启重传时使用端口
const u16   NC_STARTRS_PORT				 =    51000;	//开启nc重传时端口使用

const u16   NVR_STARTRS_RTSP_PORT        =   55000; //开启第三方设备重传时起始端口

const u16   NVR_STARTRS_ONVIF_SUBSCRIBE_PORT   =   56000; //ONVIF Subscribe port

const u16   DEC_RS_START_PORT			 = 61000;		//用于解码器重传使用的起始端口

const u16	DEFAULT_TELNET_PORT			 =   4000;	//
const u16	 DEFAULT_D01F_TELNET_PORT			 =   17230;	//


const u16	AUDIO_CYCLE_PORT_LOCAL		 =    30000;
const u16   AUDIO_CYCLE_PORT_REMOTE		 =    30010;
const u16   SEC_RECV_PORT				 =	  30020;	//辅显示解码器固定接收码流的端口

const u16   NVR_SNTP_SERVER_PORT		 =    34567;			

const u16   NVR_DEFAULT_PORT               = 1730;     //NVR缺省侦听端口号
const u16   PU_EDCPORT_INTERVAL            = 1000;     //PU的发送通道与接受码流通道的码流间隔
const u8	MAX_RECQUERY_NUM			   = 20;		//一次录像文件查询查询的最多的记录数
const u32   MAX_URL_DOWN_TIMEOUT           = 3600;      //下载超时时间60分钟，保护

// Intelligent Grid Search
const u16   MAX_INTELLIGENT_SEARCH_RESULT_NUM  = 1024;		//智能录像检索最大结果数
const u16   MAX_INTELLIGENT_SEARCH_AREA_WIGHT  = 22;		//最大智能录像检索方格宽
const u16   MAX_INTELLIGENT_SEARCH_AREA_HEIGHT = 18;		//最大智能录像检索方格高
const u32   MAX_INTELLIGENT_SEARCH_TIME_SCOPE  = 24*60*60;  //最大智能录像检索时间跨度(s)
const u16   MAX_INTELL_QUERY_GRID_INFO_BYTES   = 1600;		// 智能录像检索方格最大数据量（Byte）
															// INTELLIGENT_SEARCH_AREA_WIGHT*2 * INTELLIGENT_SEARCH_AREA_HEIGHT*2

#ifdef _NVR2820L_
    // use value 0xFFFFFFFF, sleep() exception -- suker.joe 20100730
    const u32   INFINITE_TIME   =         0xFFFFFFF  ; // this value is OK
#else
    const u32   INFINITE_TIME   =         0xFFFFFFFF  ;// Infinite timeout
#endif
const u16   MSG_PRINT_BUF   =			16*512; //打印输出缓冲

//图像输出模式
const u8    OUTPUT_MODE_VGA    =     0;   //VGA输出
const u8    OUTPUT_MODE_NTSC   =     1;   //NTSC输出
const u8    OUTPUT_MODE_PAL    =     2;   //PAL输出
const u8    OUTPUT_MODE_HDMI   =     3;	  //HDMI输出

const float ONE_PIC_SIZE	   =	 18/1024;  //前段抓拍的图片大小，18km单位为兆
//VGA模式
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
//HDMI 模式
const u8    HDMIMODE_HD1080_60HZ = 13;	//1920*1080  60HZ
const u8    HDMIMODE_HD720_60HZ  = 14;	//1280*720  60HZ 
const u8	HDMIMODE_XGA_60HZ  = 15;	//1024*768  60HZ                       
const u8    VGAMODE_NONE       =     0xff;   

const u32   DEFAULT_RECRESERSIZE =    500;  //录像缺省的预留空间

const u32	DEFAULT_GRRESERSIZE_1 =		500; //系统分区下抓拍预留空间
const u32   GRBSIZE_FULL_LIMIT_1 =      20;	//系统分区下抓拍剩余告警空间
#ifdef _NVR2820L_
const u32   DEFAULT_GRRESERSIZE_2 =     5;	//无系统分区下抓拍预留空间
const u32   GRBSIZE_FULL_LIMIT_2 =      1;	//无系统分区下抓拍剩余告警空间
const u32	SYSPT_FREESIZE_LIMIT =		1;  //抓拍空间空闲大小限制
#else
const u32   DEFAULT_GRRESERSIZE_2 =     50;	//无系统分区下抓拍预留空间
const u32   GRBSIZE_FULL_LIMIT_2 =      5;	//无系统分区下抓拍剩余告警空间
const u32	SYSPT_FREESIZE_LIMIT =		25; //抓拍空间空闲大小限制
#endif

const u8	DEFAULT_GRINTERVAL =     10;	//缺省的抓拍间隔
const u8    DEFAULT_GRPICNUM  =       1;    //缺省时抓拍图片数目

#ifdef _NVR2820_
const u32	MAX_ALARM_NUM	=		  15000;
#else
const u32   MAX_ALARM_NUM	=		  20000;	//告警数据库里数据多于MAX_ALARM_NUM就该删除了
#endif
#define     ACTIONFAIL	-1


//ddns所用常量
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


//图像分辨率
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


const  u8 PT_NAME_LEN  = 128; //分区名字的长度
const  u8 DISK_MAX_NR  = 32; //系统可查找的最大磁盘数
const  u8 UUID_LEN	   = 37; //UUID	长度	

const  u8 TOTAL_SPACE_POLICY = 1;
const  u8 CHN_SPACE_POLICY = 0;

const u8 MAXNUM_PTZ_DEFCMD		  = 8;	// 最大自定义命令
const u8 MAXLEN_PTZ_DEFCMD_CMNT   = 16;	// 自定义命令注释最长字符串（16字符，8个汉字）
const u8 MAXLEN_PTZ_DEFCMD_DATA   = 32;  // 自定义命令字（以空格隔开的2进值流，最长32字符）


const u8 MAX_ROUTE_NUM   = 8;			//定义静态路由的数目
// 日志管理定义
const u8 MAXNUM_LOG	 =			  10 ; // 最大日志实例数

// 日志类型
const u8 LOG_TYPE_USER_LOG   =      0 ;  // 用户登陆/登出日志
const u8 LOG_TYPE_USER_OPER    =    1 ;  // 用户操作日志
const u8 LOG_TYPE_EQP          =    2 ;  // 设备(设备注册,掉线等)日志
const u8 LOG_TYPE_ALARM        =    3  ; // 告警日志
const u8 LOG_TYPE_BAKEUP       =    4 ;  // 备份日志
const u8 LOG_TYPE_UPDATE       =    5 ;  // 升级日志
 
//日志级别
const u8   LOG_LEVEL_INVALID                   =  (u8)0;//无效日志等级
const u8   LOG_LEVEL_GERNERAL                  =  (u8)1;//一般性日志
const u8   LOG_LEVEL_SECONDARY                 =  (u8)2;//次要性日志
const u8   LOG_LEVEL_IMPORT                    =  (u8)3;//重要性日志

//日志查询时的排序顺序设定
const u8   LOG_QUERY_ORDERBY_ASC               =  (u8)0;//升序
const u8   LOG_QUERY_ORDERBY_DESC              =  (u8)1;//降序

// 日志语言类型
const u8  LANGUAGE_TYPE_CHINESE                =  (u8)1;
const u8  LANGUAGE_TYPE_ENGLISH                =  (u8)2;
const u8  LANGUAGE_TYPE_LANGUAGE1              =  (u8)3;
const u8  LANGUAGE_TYPE_LANGUAGE2              =  (u8)4;

const u8 LOG_LANG_TYPE_CHINESE                 =  0;  // 简体中文
const u8 LOG_LANG_TYPE_ENGLISH                 =  1;  // 英语
const u8 LOG_LAND_TYPE_CHINESE_TRADITIONAL     =  2;  // 繁体中文
const u8 LOG_LAND_TYPE_ITALY                   =  3;  // 意大利语
//录像类型   和TRpTask中的录像类型保持一致
const u8  RECTYPE_MANU                        =    0x01;//手动录像
const u8  RECTYPE_TIMER                       =    0x02;//按时间表录像
const u8  RECTYPE_ALARM_MOTION                =    0x04;//移动侦测告警录像
const u8  RECTYPE_ALARM_INPUT                 =    0x08;//电平输入告警录像
const u8  RECTYPE_ALARM_SHADE                 =    0x10;//图像遮蔽告警录像
const u8  RECTYPE_ALARM_VIDLOSE               =    0x20;//视频源丢失告警录像

//录像模式 和TRecordParam中的录像模式保持一致
const u8  RECMODE_STOP                         =   0x00;//	关闭
const u8  RECMODE_MANU                         =   0x01;//	手动
const u8  RECMODE_AUTO                         =   0x02;//自动
const u8  RECMODE_PRE1                         =   0x03;//保留
const u8  RECMODE_PRE2                         =   0x04;//保留
const u8  RECMODE_TIMER                        =   0x08;//按时间表录像
const u8  RECMODE_ALARM_MOTION                 =	0x10;//移动侦测告警录像
const u8  RECMODE_ALARM_INPUT                  =	0x20;//电平输入告警录像
const u8  RECMODE_ALARM_SHADE                  =	0x40;//图像遮蔽告警录像
const u8  RECMODE_ALARM_VIDLOSE                =   0x80;//视频源丢失告警录像

//DVD刻录
const u8  MAX_RECORD_NUM					   =	20; //一次刻录的最大记录数量
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

const u8  ASCIIA_BASE_VALUE						= 	65; //ASCII 码表中字符A的码值

const u16 TWO_HOUR_SPACE                        =  11520; //两小时的存储空间(2*360*16) 

const u8  MAX_TVWCHN2860						= 64;

// 用户权限管理
// 权限控制宏定义
// 2680新的设计
// NcType定义


// 2820以下无用
#define PRI_NVR_CFG         1    // NVR配置参数
#define PRI_NVR_FUN_OPE     2    // NVR功能操作

#define PRI_NVR_FUN_DEV_MGR 21   // 设备管理
#define PRI_NVR_FUN_REC     22   // 录像
#define PRI_NVR_FUN_PLAY    23   // 放像
#define PRI_NVR_FUN_TVWALL  24   // 电视墙
#define PRI_NVR_FUN_SNAP    25   // 抓拍
#define PRI_NVR_FUN_ALARM   26   // 告警
#define PRI_NVR_FUN_MPU     27   // MPU管理

#define PRI_NVR_SYS_OPE      3   // NVR系统操作

#define PRI_DVS_CFG          4   // DVS配置
#define PRI_DVS_FUN_OPE      5   // DVS功能操作
#define PRI_DVS_FUN_MONITOR  51  // 视频浏览
#define PRI_DVS_FUN_AUDIO    52  // 语音呼叫
#define PRI_DVS_FUN_PTZ      53  // ptz控制
#define PRI_DVS_FUN_REBOOT   54  // 重启
#define PRI_DVS_FUN_REC      55  // 前端录放像等      

#define DEFAULT_NVRID		 8  //默认NVRID     

#define FREETAG				"free"       //磁盘中空闲区块的标志     

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

#define MAXRECQUERYNUM	    20  //一次录像查询,查询的最大纪录数

#define MAXUSERNAMELEN		16  //调试端口的最大用户名长
#define MAXPASSWORDLEN		16  //调试端口的最大密码长

#define NORMALWORKING		0  //系统正常工作
#define SYSSLEEPING			1  //系统软关机中
#define SYSSLEEPED			2  //系统软关机
#define MULTIMPUPLY			0  //多路放像
#define SYNCMPUPLY			1  //同步放像

#define SYNCPTRECNUM		200  //录像分区同步操作中一次操作的记录数
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

//以下是2820 2.0版本中新增及修改的宏
#define MAXNUM_RECORDS_PERPAGE  1000
#define MAXNUM_ETH  3

//业务内部使用
const u8 BUF_LEN						   = 255;
const u8 MAXNUM_RECTRANSLATE_NUM		   = 4;	    //nvr系统支持的最大转存路数
const u8 CPU_AVERAGE_COUNT_NUM			   = 10;	    //nvr系统中计算平均值使用的最大采样次数

#define	 MAX_EXT_MPUSCHEME 23

#if defined(_NVR2860_)  || defined( _NVR2821H_)
	const u8     MAXNUM_MPUCHN                 = 70  ;    //最大MPU通道数
	const u8	 RESTROR_START_REC_ID		   = 64;
	const u8     MAXNUM_SYNCMULTI              = 34;	//最多同时有34个组组同步回放
	const u8 	 MAX_TVWCHN					   = 64  ;	  //TVWALL可以控制的最大通道数
	const u8     MAXNUM_RECBAKER               = 1;	//最多同时有1个备份机
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
	// 1825最多接入9路 [5/3/2013 wangtianling]
	#define  MAXNUM_DVS_SERV	  16
	#define  MAXNUM_ENCCHN_SERV   16
	#define  MAXNUM_DECODER_SERV  16
	#define	 MAX_RECORDER_NUM_SERV  MAX_RECORDER_NUM/4+MAXNUM_RECTRANSLATE_NUM
	// 1825最多接入9路 [5/3/2013 wangtianling]
	#define	 MAX_GUI_PLAY_NUM	 4 // 支持本地MPU放像最大数
	#define	 MAX_NC_PLAY_NUM	 4 // 支持NC放像最大数	
	#if defined(_NVR1825_9HD_)
		#define	 MAX_GUI_PLAY_NUM	 9  // 支持本地MPU放像最大数
		#define	 MAX_NC_PLAY_NUM	 16 // 支持NC放像最大数
	#endif	
#elif defined(_NVR1822_)
	#define	 MAX_GUI_PLAY_NUM	 16 // 支持本地MPU放像最大数
	#define	 MAX_NC_PLAY_NUM	 16 // 支持NC放像最大数	
#else
	#define	 MAX_GUI_PLAY_NUM	 16 // 支持本地MPU放像最大数
	#define	 MAX_NC_PLAY_NUM	 16 // 支持NC放像最大数	
#endif
	#define	 MAX_PLAY_NUM_SERV	 MAX_GUI_PLAY_NUM + MAX_NC_PLAY_NUM // 支持放像总数

    #define  MAX_TVWCHN_SERV	 MAX_TVWCHN	
	#define	 MAXNUM_TVWCHN_SERV  MAXNUM_TVWCHN
	#define	 MAXNUM_TVWDVS_SERV  MAXNUM_TVWDVS
	#define	 MAXNUM_TVWCYCLEPROJ_SERV 64
	#define	 MAXNUM_TVWSCHEME_SERV MAXNUM_TVWSCHEME
	#define	 MAXNUM_TVWPROJ_SERV MAXNUM_TVWPROJ
	#define  MAXNUM_USER_SERV    MAXNUM_USER
#else
	const u8     MAXNUM_MPUCHN                 = 16;    //最大MPU通道数
	const u8	 RESTROR_START_REC_ID		   = 16;
	const u8     MAXNUM_SYNCMULTI              = 3;	//最多同时有10个组组同步回放
	const u8 	 MAX_TVWCHN					   = 16;	  //TVWALL可以控制的最大通道数
	const u8     MAXNUM_RECBAKER               = 1;	//最多同时有1个备份机
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
		#define	 MAX_GUI_PLAY_NUM	 0 // 支持本地MPU放像最大数
		#define	 MAX_NC_PLAY_NUM	 12 // 支持NC放像最大数
	#else
		#define	 MAX_GUI_PLAY_NUM	 4 // 支持本地MPU放像最大数
		#define	 MAX_NC_PLAY_NUM	 16 // 支持NC放像最大数
	#endif
	#define	 MAX_PLAY_NUM_SERV	 MAX_GUI_PLAY_NUM + MAX_NC_PLAY_NUM // 支持放像总数

	#define  MAX_TVWCHN_SERV	 MAX_TVWCHN	
	#define	 MAXNUM_TVWCHN_SERV  MAXNUM_TVWCHN
	#define	 MAXNUM_TVWDVS_SERV  MAXNUM_TVWDVS
	#define	 MAXNUM_TVWCYCLEPROJ_SERV 16
	#define	 MAXNUM_TVWSCHEME_SERV MAXNUM_TVWSCHEME
	#define	 MAXNUM_TVWPROJ_SERV MAXNUM_TVWPROJ
	#define  MAXNUM_USER_SERV    MAXNUM_USER
#endif

#define DECRECVPORT			60000 //解码器解码起始端口	
#define PLAT_NVR_PLAY_REC_DSTCHN_PORT 7000
//摄像头类型定义
const u8 CAMERA_TYPE_SONY                  = 1;    //(u8)1		SONY
const u8 CAMERA_TYPE_AD                    = 2;    //(u8)2		AD
const u8 CAMERA_TYPE_PELCO                 = 3;    //(u8)3		PELCO-D
const u8 CAMERA_TYPE_PIH			       = 4;    //(u8)4		利凌
const u8 CAMERA_TYPE_PELCO_P 		       = 5;    //(u8)5		PELCO-P
const u8 CAMERA_TYPE_PARCO                 = 6;	   //(u8)6		PARCO柏高
const u8 CAMERA_TYPE_AB			           = 7;    //(u8)7		AB
const u8 CAMERA_TYPE_YUNTAI		           = 8;    //(u8)8		独立云台
const u8 CAMERA_TYPE_Samsung		       = 9;    //(u8)9		三星
const u8 CAMERA_TYPE_YAAN			       = 10;   //(u8)10	    亚安
const u8 CAMERA_TYPE_AD168                 = 11;   //(u8)11	    AD168类型
const u8 CAMERA_TYPE_KALATEL               = 12;   //(u8)12	    卡拉特
const u8 CAMERA_TYPE_JN                    = 13;   //(u8)13	    JN伟华
const u8 CAMERA_TYPE_WV_CS650              = 14;   //(u8)14	    松下,是850的老协议
const u8 CAMERA_TYPE_WV_CS850              = 15;   //(u8)15	    松下,是850的新协议
const u8 CAMERA_TYPE_ALEC                  = 16;   //(u8)16	    艾立克
const u8 CAMERA_TYPE_AB_P                  = 17;   //(u8)17	    AB-P
const u8 CAMERA_TYPE_AB_D                  = 18;   //(u8)18	    AB-D
const u8 CAMERA_TYPE_PELCO_D_JEC           = 19;   //(u8)19	    JEC PELCO-D
const u8 CAMERA_TYPE_PELCO_P_JEC           = 20;   //(u8)20	    JEC PELCO-P
const u8 CAMERA_TYPE_ROBOT                 = 21;   //(u8)21     ROBOT
const u8 CAMERA_TYPE_PELCO_D_K             = 26;   //(u8)26     PELCO_D_K
// 矩阵接入控制
const u8 CAMCTRL_COMMAND_MATRIX_SWTICH   = 29;	//切换视频
const u8 CAMCTRL_COMMAND_MATRIX_VIDMIX4  = 30;	//画面合成2×2
const u8 CAMCTRL_COMMAND_MATRIX_VIDMIX9  = 31;	//画面合成3×3
const u8 CAMCTRL_COMMAND_MATRIX_VIDMIX16 = 32;	//画面合成4×4
const u8 CAMCTRL_COMMAND_MATRIX_VIDMIXPP = 33;	//画面合成画中画
const u8 MAX_CHN_NUM_32					= 32  ;	//通道数目限定
const u8 MAX_CHN_NUM_48					= 48  ;	//通道数目限定
const u8 MAX_CHN_NUM_64					= 64  ;	//通道数目限定
const u8 MAX_CHN_NUM_128				= 128 ;	//通道数目限定
const u8 MAX_CHN_NUM_96					= 96 ; //通道数目限定
const u16   FTP_SERVICE_PORT2 = 1730;           // [11/6/2008 zhangkehui] 向前兼容
const u16   CMSI_PLY_PORT_BASE = 59260;         //平台接入前端放像起始端口
                                                // 59068==>59260  59000 + (64/16 + 1) *4 [平台端口分配规则6/11/2009 zhangkehui]
#if defined(_NVR2821H_) || defined(_NVR1037_)
const u8 SMOOTH_DEFAULT_VALUE = 10;				//NVR1821/NVR2821H流畅度默认值<2013_3_12 SYT>
#else
const u8 SMOOTH_DEFAULT_VALUE = 3;				//流畅度默认值<2012_3_23 KSW>
#endif

const  u8 PART_MAX_NR_NVR  = 4; //磁盘允许的最大分区个数

const u8 NVRMAJORVER			  = 20; // nvr主版本号
const u8 NVRMINORVER			  = 0;  // nvr次版本号

const u8 NVRMAJORVER30			  = 30; // nvr主版本号
const u8 NVRMINORVER30			  = 3;  // nvr次版本号

const u8 NVRMAJORVER40			  = 40; // nvr主版本号
const u8 NVRMINORVER40			  = 3;  // nvr次版本号
const u8 NVRMINORVER431			  = 31; // nvr次版本号

const u8 NVRMAJORVER50			  = 50; // nvr主版本号
const u8 NVRMINORVER50			  = 1;  // nvr次版本号
const u8 NVRMINORVER51			  = 11; // nvr次版本号
const u8 NVRMINORVER52			  = 12; // nvr次版本号
const u8 NVRMINORVER53			  = 13; // nvr次版本号
const u8 NVRMINORVER54			  = 14; // nvr次版本号 V4R4B1FIX1
const u8 NVRMINORVER55			  = 15; // nvr次版本号 V5R1

#define NC_TYPE_NC          0        // 客户端登陆
#define NC_TYPE_GUI         1        // GUI登陆
#define NC_TYPE_CMSI        2        // CMSI登陆
#define NC_TYPE_WEB         3        // WEB用户登陆 [10/22/2009 zhangkehui]
#define NC_TYPE_WEBDI		4		 // WEB调试信息登陆 [9/112012 songyiting]
#define NC_TYPE_BRD			5		 // 在nvr面板操作
#define NC_TYPE_D01F		6		 // d01f登录
#define NC_TYPE_D04F		7		 // d04f登录
#define NC_TYPE_GBPROXY		8		 // 国标代理登录
#define NC_TYPE_INVALID     255      // 无效类型

#define USER_STOP_INTERNAL  10*60    // 用户停用时间 10分钟
#define USER_LOG_ERR_TIMES  3        // 登陆连续失败次数

#define USER_TYPE_DEFAULT   0        // default用户
#define USER_TYPE_ADMIN     1        // admin用户
#define USER_TYPE_NORMAL    2        // 普通用户
#define USER_TYPE_ADMIN_DEFAULT 3    // 默认的admin用户
#define USER_TYPE_INVALID   4        // 无效用户类型

#define PRI_NVR_RECSNAP     0x0001   // 录像抓拍
#define PRI_NVR_DEVMGR      0x0002   // 设备管理
#define PRI_NVR_ALARMMGR    0x0004   // 告警管理
#define PRI_NVR_TVWALL      0x0008   // 电视墙
#define PRI_NVR_CFGMGR      0x0010   // 参数管理
#define PRI_NVR_USERMGR     0x0020   // 用户管理
#define PRI_NVR_LOGMGR      0x0040   // 日志管理

#define PRI_DVS_PTZCTRL     0x01     // PTZ控制
#define PRI_DVS_MONITOR     0x02     // 视频浏览
#define PRI_DVS_PLAYER      0x04     // 视频回放

// 平台接入类型定义 [11/6/2008 zhangkehui]
#define PLAT_TYPE_SP2       0        // sp2平台
#define PLAT_TYPE_2800      1        // 2800E平台
#define PLAT_TYPE_SP2_64    2        // sp2平台,支持64通道 [7/13/2009 zhangkehui]
#define PLAT_TYPE_2800_64   3        // 2800E平台,支持64通道 [7/13/2009 zhangkehui]
#define PLAT_TYPE_HD_64     4        // 支持64路高清平台 [9/24/2009 zhangkehui]
#define PLAT_TYPE_DEC    5        // 支持64路高清平台 [9/24/2009 zhangkehui]

#define REG_CMS_TYPE_NORMAL 0        // 正常注册
#define REG_CMS_TYPE_LDS    1        // 负载均衡


// 输入告警定义
#define PIN_DECT_STATE_NONE   0        // 不检测
#define PIN_DECT_STATE_ONE    1        // 只检测一个周期
#define PIN_DECT_STATE_CYCLE  2        // 每周循环检测
#define PIN_DECT_STATE_ALWAYS 3        // 始终检测

#define PIN_RELATE_ENCID_DISABLE	0xFF    //告警关联视频编码通道无效值
#define PIN_OUTPUT_DISABLE			0xFF	//告警控制输出无效值

#define PIN_OSD_DISABLE				0
#define PIN_OSD_ENABLE				1

#define MAX_DEV_OSDNAME_NUM 3  //前端支持的最大OSD字幕数

/////////////////////业务内部使用//////////////////////////////////////////////
const u8	 MAX_RECORDER_NUM			   = TEST_128	 ;	  //录像通道的最大数量
const u8	 MAX_PLAY_NUM				   = 64  ;	  //放像通道的最大数量//2860目前最多为64
const u8     MAXNUM_MPUSTYLE               = 17  ;    //最大MPU风格数

const u8 PTCHKOK = 200;			// 分区正常,并且挂接成功
const u8 PTCHKNEEDRP = 201;		// 分区建议修复,并且挂接成功
const u8 PTCHKOPTFAIL = 202;		// 脚本运行失败
const u8 PTCHKLOGERROR = 203;		// 分区必须修复,并且挂接失败

const u16 ALARMSTATEZERO = 10000;  //前端告警联动字幕零状态

const u8 USERDATANAMELEN = 32;		//用户自定义数据名称长度
const u8 USERDATACONTENTLEN = 255;	//用户自定义数据内容长度

const u16 NVR_MAX_FILE_PATH_LEN = 255;
const u16 NVR_MAX_FILE_NAME_LEN = 255;
const u16 NVR_MAX_PARTION_NAME_LEN = 255;

// 告警，图片转存最大记录条数
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
const float F_EPSINON = 1/100000; //十万分之一

// 外产商类型定义,两种型号IPCam-MSeries， GNC-700Series统一为VT-200 Series
//#define VtcpSeries       "VT-200 Series"
#define VT200Series      "Vitor VT-200 series"
#define IPCamMSeries     "IPCam-MSeries"
#define GNC700Series     "GNC-700Series"

#define RTSPSeries       "RTSP"
#define RTSPSeries2      "ANNA"

#define KDM201_D01H      "KDM201-D01H"

// 增加onvif设备类型
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
const u8 MAX_SYSTARGET_NUM = 32;        //系统中可接入的TARGET总数
//const u8 MAX_TARGETINONEPOTRAL_NUM = 32;        //一个PORTAL中TARGET的最大数量
const u8 MAX_TARGETINONEPOTRAL_NUM = 10;        //一个PORTAL中TARGET的最大数量 
//解决portal列表通知消息结构体太大，防止超出磁盘表 <2011_11_2 KSW>

const u8 MAX_TARGET_NAME = 100;        //系统中可接入的TARGET总数

const u8 MAX_SYSTARGETPORTAL_NUM = 10;	//系统中可接入的TARGETPORTAL总数		

const u8 MAX_PLAY_KFPIC_NUM = 10;	//放像关键帧 最大截图

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
#define NVR_RESET_TIMES           3  // 超过3次则认为reset按键生效

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
#define NVR_MEDIA_VIDEO     (u8)1 // 只传视频
#define NVR_MEDIA_AUDIO     (u8)2 // 只传音频
#define NVR_MEDIA_UNKNOW    (u8)3 // 字符串未知信息
#define NVR_MEDIA_MAX_NUM   (u8)3 // 字符串未知信息


/* 预录时长 - Pre-recorded duration*/
#if (defined _NVR1037_)
    #define NVR_PRE_REC_DURATION         6	//NVR2821H预录时间
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

// 接ONVIF内存不足，改小 [8/12/2013 wangtianling]
#define NVR_PRE_REC_DURATION_2820HND     NVR_PRE_REC_DURATION/*60*/

/* 录像比特率 */
#define NVR_REC_BITRATE                  2048*1024

/* 2820L 协议初始化链路个数 4路存在问题 */
#ifdef _NVR2820L_
    #define NVR_PUI_INIT_LINK_NUM          32
#else
    #define NVR_PUI_INIT_LINK_NUM          128
#endif

/* 默认的主流 码率 */
    #define NVR_ENC_MAIN_BITRATE         2048
/* 默认的主流1080P 码率 */
    #define NVR_ENC_MAIN1080P_BITRATE    6144
/* 默认的QCIF辅流 码率 */
    #define NVR_ENC_SECQ_BITRATE          192
/* 默认的CIF辅流 码率 */
#ifndef _NVR1822_
	#define NVR_ENC_SECC_BITRATE          1024
#else
	#define NVR_ENC_SECC_BITRATE          384
#endif

/* 删除NVR升级包 - 系统启动时会做此动作 */
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

#define NVR_TRUE     (u8)1 // 为真
#define NVR_FALSE    (u8)0 // 为假

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
const u8  MAXNUM_DISC_TASK_LIST	= 64;		//光盘上最大刻录任务个数
const u16   MAXLEN_CASE_NAME	= 64;		//案件名称的最大长


const u8 MAXNUM_ONDS	 =    64 ; // 最大Onds
#define MAXNUM_ONDSINS		128	// 一个nc可以连接的最大的NVR的数量

#define ONDS_TIME_RECONNECTNVR		10*1000	// 间隔5s后重新连接
#define ONDS_TIME_RELOGIN_NVR		60*1000	// 间隔60s后开始登录

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
#define MAX_D01F_DECRECVPORT_SEQ  4   //D01F解码器,接收端口，每个解码器port间隔4

#define D01F_MODE_G7221   0
#define D01F_MODE_ADPCM  1
#define D01F_MODE_PCMA    2
#define D01F_MODE_PCMU    3


#define D01F_AUDIO_INPUTTYPE_LINEIN                 0x00
#define D01F_AUDIO_INPUTTYPE_MIC                    0x01

const u8 NVR_RP_VER_BASE = 10; //录像分区版本基数，nvr与nc使用
#define  LINK_CLEAR_WIN_PATH                                                                     "/usr/bin/appres/clearpic/"

const u16 IVIEW_RTSP_PORT = 554;
const u16 IVIEW_RTP_PORT = 30098;
const u16 IVIEW_RTCP_PORT = 30099;

const u16 MAX_D04F_CHN_NUM = 64; //D04F最大解码通道
const u16 MAX_BOARD_CHN_NUM = 32; //处理器最大解码通道
const u8 MAX_D04F_HMDI_NUM = 4;   //最大HDMI个数
const u8 MAX_HMDI_CHN_NUM = 16;   //每个HMDI对应最大解码通道
const u8 MAX_DEC_PARAM_CHN =64;  //最大解码器通道数
const u8 MAX_AUD_NUM =5;  

const u32 BAK_NORMAL_SPEED = 800;
const u16 PLAT_PLY_CMD		= 1;
const u8 MAX_EMAIL_NUM   = 8;	//定义最大目标邮箱数目
const u8 MAX_EMAIL_BUF_LEN = 128; //定义邮箱域名与密码的最大长度
//1037使用
#define APACHE_DIR "/etc/apache2"
#define APACHE_PORT_CONF "/etc/apache2/ports.conf"
#define APACHE_TMP_PORT_CONF "/etc/apache2/.ports.conf"
#define SITES_ENABLED_DEFAULT "/etc/apache2/sites-enabled/000-default"
#define TMP_SITES_ENABLED_DEFAULT "/etc/apache2/sites-enabled/.000-default"
#define SMTP_DNS_SER_USRID	100       //首选DNS服务器

/********macro definition for GB****************/
#define  GB_MAX_URI_LEN 256
#define  GB_MAX_DOMAIN_NAME_LEN 256
#define  GB_MAX_REGISTER_USERNAME_LEN 64    //用户名最大长度
#define  GB_MAX_REGISTER_PASSWORD_LEN 128   //口令的最大长度
#define  GB_MAX_IP_ADDR_LEN           15    //IP地址字符串表示的最大长度
#define  GB_ID_NO_LEN             (u8)20    //国标ID的长度
#endif

