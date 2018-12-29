/** @defgroup rkc常量定义 
 *  @version V1.1.4
 *  @author  叶良平
 *  @date    2017.12.19
 */
#pragma once

#if !defined(_CONSTDEF_H_)
#define _CONSTDEF_H_


#ifndef String 
typedef tstring String;	                            // String
#endif
#ifndef MbString                                    // MultiByteString 
typedef std::string MbString;
#endif

#define NOTIFY_MSG	IRkcToolCommonOp::NotifyMsg

#define WINDOW_MGR_PTR  IWindowManager::GetSingletonPtr()


#define REG_RCKTOOL_MSG_OB(ob) IRkcToolMsgManager::GetSingletonPtr()->AddObserver(ob);
#define UNREG_RCKTOOL_MSG_OB(ob) IRkcToolMsgManager::GetSingletonPtr()->RemoveObserver(ob);
#define REG_RCKTOOL_MSG_WND_OB(hwnd) IRkcToolMsgManager::GetSingletonPtr()->AddWindowObserver(hwnd);
#define UNREG_RCKTOOL_MSG_WND_OB(hwnd) IRkcToolMsgManager::GetSingletonPtr()->RemoveWindowObserver(hwnd);


#define DEFAULT_TITLE_HEIGHT   100

#define  CNSCONF_FILE_PATH		_T("/usr/conf/")				//台标存放位置
#define CFG_FILE    _T("configure.ini")							//tpad配置文件
#define CFG_PATH    _T("path")									//tpad配置文件

#define TP_TEMPFILE_PATH       _T("temp/")

#define  MAX_RADIO_COUNT      5                                 // 最大外设数
#define  MAX_NAME_LEN        32                                 // 最大名字长(宏定义避免编译有parse error)
#define  MAX_DEVICEVER_LEN   38                                 //版本号最大长度

#define RCKTOOL_VERSION_ID	   "V5.0.0.4"

#endif
