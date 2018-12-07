#include "stdafx.h"
#include "rkclib.h"
#include "rkcsession.h"
#include "rkcConst.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CRckLib::CRckLib()
{

}

CRckLib::~CRckLib()
{

}

/*=============================================================================
  �� �� ���� CreateSession
  ��    �ܣ� ����ʵ���˽ӿ�CRckSessionCtrlIF�Ķ���
  �㷨ʵ�֣� �ӿ�ʹ����ɺ�,����DestroyInstance�������ٶ���
  ȫ�ֱ����� 
  ��    ���� CRckSessionCtrlIF **ppICnt �ɹ�����CRckSessionCtrlIF�ӿ�,ʧ�ܷ���NULL
  �� �� ֵ�� u16 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��        �汾        �޸���        �߶���    �޸�����
 2018.02.26     1.0             ylp                     ����
=============================================================================*/
u16 CRckLib::CreateSession(CRkcSessionCtrlIF **ppICnt)
{
    CRkcSession *pConnect = new CRkcSession();
    if(pConnect == NULL)
    {
        *ppICnt = NULL;
        return ERR_RK_CREATINSTANCE;
    }
    else
    {
        *ppICnt = pConnect;
        return NO_ERROR;
    }
}

/*=============================================================================
  �� �� ���� DestroySession
  ��    �ܣ� ����ʵ���˽ӿ�CRckSessionCtrlIF�Ķ���
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� CRckSessionCtrlIF **ppICnt ����ӿ�CRckSessionCtrlIF,�ɹ��󷵻�NULL
  �� �� ֵ�� u16 
  ˵    ���� ֻ��������CreateInstance���������Ķ���
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��        �汾        �޸���        �߶���    �޸�����
 2018.02.26     1.0              ylp                    ����
=============================================================================*/
u16 CRckLib::DestroySession(CRkcSessionCtrlIF **ppICnt)
{
    CRkcSession *pConnect = dynamic_cast<CRkcSession*>(*ppICnt);
    if(pConnect == NULL)
    {
        return ERR_RK_INTERFACE;
    }
    delete pConnect;
    *ppICnt = NULL;
    return NO_ERROR;
}