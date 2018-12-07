// MsgManager.h: interface for the CMsgManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGMANAGER_H__E8EC0DCD_D913_4433_81A2_296403F52F07__INCLUDED_)
#define AFX_MSGMANAGER_H__E8EC0DCD_D913_4433_81A2_296403F52F07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace AppFrame
{

class CMsgManager : public IMsgManager
{
public:
	CMsgManager(){}
	virtual ~CMsgManager();
	virtual void SendMsg( TMsgParam& tMsgParam );
	virtual void PostMsg(TMsgParam& tMsgParam);
	virtual void AddObserver( IObserver_MsgPrama* pOb );
	virtual void RemoveObserver( IObserver_MsgPrama* pOb );
protected:
/** 找到观察者 
 *  @param[in] 
 *  @node 
 *  @return 迭代器
 */
	vector<IObserver_MsgPrama*>::iterator FindObserver( IObserver_MsgPrama* pObserver );

/*
	ob队列
*/
	typedef vector<IObserver_MsgPrama*> ObserverList;
	ObserverList m_observers;
};

} // namespace AppFrame end 

#endif // !defined(AFX_MSGMANAGER_H__E8EC0DCD_D913_4433_81A2_296403F52F07__INCLUDED_)
