// Logger.h: interface for the CLogger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGGER_H__8CCFF54C_F2BB_4FDA_AC8B_DD7522FC03E3__INCLUDED_)
#define AFX_LOGGER_H__8CCFF54C_F2BB_4FDA_AC8B_DD7522FC03E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace AppFrame
{
/*
	打印类，尽量用宏LOGEVENT
*/
class CLogger : public ILogger
{
public:
	CLogger();
	virtual ~CLogger();
	virtual bool LogEvent( LPCTSTR lpszEvent, LogLevel emLoglv = Standard );
};

} // namespace AppFrame end 

#endif // !defined(AFX_LOGGER_H__8CCFF54C_F2BB_4FDA_AC8B_DD7522FC03E3__INCLUDED_)
