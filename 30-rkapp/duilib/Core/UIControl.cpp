#include "StdAfx.h"

namespace DuiLib {

const static LPCTSTR pMosicleft = _T("Mosic_left.png");
const static LPCTSTR pMosicmiddle = _T("Mosic_middle.png");
const static LPCTSTR pMosicright = _T("Mosic_right.png");
const static LPCTSTR pMosicSelleft = _T("MosicSel_left.png");
const static LPCTSTR pMosicSelmiddle = _T("MosicSel_middle.png");
const static LPCTSTR pMosicSelright = _T("MosicSel_right.png");
const static LPCTSTR pMosicDisableleft = _T("MosicDisable_left.png");
const static LPCTSTR pMosicDisablemiddle = _T("MosicDisable_middle.png");
const static LPCTSTR pMosicDisableright = _T("MosicDisable_right.png");

const static LPCTSTR pvMosictop = _T("MosicV_top.png");
const static LPCTSTR pvMosicmiddle = _T("MosicV_middle.png");
const static LPCTSTR pvMosicbottom = _T("MosicV_bottom.png");

CControlUI::CControlUI() : 
m_pManager(NULL), 
m_pParent(NULL), 
m_bUpdateNeeded(true),
m_bMenuUsed(false),
m_bVisible(true), 
m_bInternVisible(true),
m_bFocused(false),
m_bEnabled(true),
m_bMouseEnabled(true),
m_bKeyboardEnabled(true),
m_bFloat(false),
m_bSetPos(false),
m_chShortcut('\0'),
m_pTag(NULL),
m_dwBackColor(0),
m_dwBackColor2(0),
m_dwBackColor3(0),
m_dwBorderColor(0),
m_dwFocusBorderColor(0),
m_bColorHSL(false),
m_nBorderSize(0),
m_nBorderStyle(PS_SOLID),
m_nTooltipWidth(300),
m_bIsVerMosaicBk(false),
m_bIsAlwaysChangeBk(false),
m_bIsSetBk(false)
{
    m_cXY.cx = m_cXY.cy = 0;
    m_cxyFixed.cx = m_cxyFixed.cy = 0;
    m_cxyMin.cx = m_cxyMin.cy = 0;
    m_cxyMax.cx = m_cxyMax.cy = 9999;
    m_cxyBorderRound.cx = m_cxyBorderRound.cy = 0;

    ::ZeroMemory(&m_rcPadding, sizeof(RECT));
    ::ZeroMemory(&m_rcItem, sizeof(RECT));
    ::ZeroMemory(&m_rcPaint, sizeof(RECT));
	::ZeroMemory(&m_rcBorderSize,sizeof(RECT));
    ::ZeroMemory(&m_tRelativePos, sizeof(TRelativePosUI));
}

CControlUI::~CControlUI()
{
    if( OnDestroy ) OnDestroy(this);
    if( m_pManager != NULL ) m_pManager->ReapObjects(this);
}

CDuiString CControlUI::GetName() const
{
    return m_sName;
}

void CControlUI::SetName(LPCTSTR pstrName)
{
    m_sName = pstrName;
}

LPVOID CControlUI::GetInterface(LPCTSTR pstrName)
{
    if( _tcscmp(pstrName, DUI_CTR_CONTROL) == 0 ) return this;
    return NULL;
}

LPCTSTR CControlUI::GetClass() const
{
    return _T("ControlUI");
}

UINT CControlUI::GetControlFlags() const
{
    return 0;
}

bool CControlUI::Activate()
{
    if( !IsVisible() ) return false;
    if( !IsEnabled() ) return false;
    return true;
}

CPaintManagerUI* CControlUI::GetManager() const
{
    return m_pManager;
}

void CControlUI::SetManager(CPaintManagerUI* pManager, CControlUI* pParent, bool bInit)
{
    m_pManager = pManager;
    m_pParent = pParent;
    if( bInit && m_pParent ) Init();
}

CControlUI* CControlUI::GetParent() const
{
    return m_pParent;
}

CDuiString CControlUI::GetText() const
{
    return m_sText;
}

void CControlUI::SetText(LPCTSTR pstrText)
{
    if( m_sText == pstrText ) return;

    m_sText = pstrText;
    Invalidate();
}

DWORD CControlUI::GetBkColor() const
{
    return m_dwBackColor;
}

void CControlUI::SetBkColor(DWORD dwBackColor)
{
    if( m_dwBackColor == dwBackColor ) return;

    m_dwBackColor = dwBackColor;
    Invalidate();
}

DWORD CControlUI::GetBkColor2() const
{
    return m_dwBackColor2;
}

void CControlUI::SetBkColor2(DWORD dwBackColor)
{
    if( m_dwBackColor2 == dwBackColor ) return;

    m_dwBackColor2 = dwBackColor;
    Invalidate();
}

DWORD CControlUI::GetBkColor3() const
{
    return m_dwBackColor3;
}

void CControlUI::SetBkColor3(DWORD dwBackColor)
{
    if( m_dwBackColor3 == dwBackColor ) return;

    m_dwBackColor3 = dwBackColor;
    Invalidate();
}

LPCTSTR CControlUI::GetBkImage()
{
    return m_sBkImage;
}

void CControlUI::SetBkImage(LPCTSTR pStrImage)
{
	if( m_sBkImage == pStrImage ) return;

	m_bIsSetBk = true;
    m_sBkImage = pStrImage;
    Invalidate();
}

DWORD CControlUI::GetBorderColor() const
{
    return m_dwBorderColor;
}

void CControlUI::SetBorderColor(DWORD dwBorderColor)
{
    if( m_dwBorderColor == dwBorderColor ) return;

    m_dwBorderColor = dwBorderColor;
    Invalidate();
}

DWORD CControlUI::GetFocusBorderColor() const
{
    return m_dwFocusBorderColor;
}

void CControlUI::SetFocusBorderColor(DWORD dwBorderColor)
{
    if( m_dwFocusBorderColor == dwBorderColor ) return;

    m_dwFocusBorderColor = dwBorderColor;
    Invalidate();
}

bool CControlUI::IsColorHSL() const
{
    return m_bColorHSL;
}

void CControlUI::SetColorHSL(bool bColorHSL)
{
    if( m_bColorHSL == bColorHSL ) return;

    m_bColorHSL = bColorHSL;
    Invalidate();
}

int CControlUI::GetBorderSize() const
{
    return m_nBorderSize;
}

void CControlUI::SetBorderSize(int nSize)
{
    if( m_nBorderSize == nSize ) return;

    m_nBorderSize = nSize;
    Invalidate();
}

//************************************
// 函数名称: SetBorderSize
// 返回类型: void
// 参数信息: RECT rc
// 函数说明: 
//************************************
void CControlUI::SetBorderSize( RECT rc )
{
	m_rcBorderSize = rc;
	Invalidate();
}

SIZE CControlUI::GetBorderRound() const
{
    return m_cxyBorderRound;
}

void CControlUI::SetBorderRound(SIZE cxyRound)
{
    m_cxyBorderRound = cxyRound;
    Invalidate();
}

bool CControlUI::DrawImage(HDC hDC, LPCTSTR pStrImage, LPCTSTR pStrModify)
{
	bool IsChangeBk = false;
	if (m_bIsSetBk && m_bIsAlwaysChangeBk)//进行背景切换的时候 才强制刷新 避免每次重绘的时候都刷新
	{
		IsChangeBk = true;
		m_bIsSetBk = false;
	}
    return CRenderEngine::DrawImageString(hDC, m_pManager, m_rcItem, m_rcPaint, pStrImage, pStrModify, IsChangeBk);
}

bool CControlUI::DrawImageGDIPlus( HDC hDC, SIZE sz, Image* pImg, CPoint ptInCtl )
{
	return CRenderEngine::DrawImageGDIPlus( hDC, m_pManager, m_rcItem, m_rcPaint, sz, pImg, ptInCtl, m_rcItem );
}

bool CControlUI::DrawImageGDIPlus( HDC hDC, LPCTSTR pStrImage )
{
	const TImageInfo* tImageInfo = NULL;
	tImageInfo = const_cast<TImageInfo*>(m_pManager->GetImageEx(pStrImage));
	if( NULL == tImageInfo ) return FALSE;  
	Image* pImg = NULL;
	pImg = const_cast<Image*>(m_pManager->GetImageP(pStrImage)); 
	SIZE sz;
	sz.cx = tImageInfo->nX;
	sz.cy = tImageInfo->nY;
	if ( CPaintManagerUI::IsSelfAdaption() )
	{
		float fAdpX, fAdpY;
		CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
		sz.cy = sz.cy * fAdpY;
		sz.cx = sz.cx * fAdpX;
	}
	if ( NULL != pImg )
	{
		bool bret = DrawImageGDIPlus( hDC, sz, pImg, CPoint( 0,0 ) );
		//delete pImg;
		return bret;
	}
	return false;
}

//拼接背景
void CControlUI::DrawMosaicImage( HDC hDC, UINT uState )
{
	LPCTSTR pstrTopleft = NULL;
	LPCTSTR pstrTopmiddle = NULL;
	LPCTSTR pstrTopright = NULL; 

	if ( m_bIsVerMosaicBk )
	{
		pstrTopleft = m_sBkImage + _T("\\") + pvMosictop;
		pstrTopmiddle = m_sBkImage + _T("\\") + pvMosicmiddle;
		pstrTopright = m_sBkImage + _T("\\") + pvMosicbottom;
	}
	else if ( uState == UISTATE_DISABLED )
	{
		pstrTopleft = m_sMosImgFolder + _T("\\") + pMosicDisableleft;
		pstrTopmiddle = m_sMosImgFolder + _T("\\") + pMosicDisablemiddle;
		pstrTopright = m_sMosImgFolder + _T("\\") + pMosicDisableright;
	}
	else if ( uState == UISTATE_HOT || uState == UISTATE_FOCUSED )
	{
		pstrTopleft = m_sMosImgFolder + _T("\\") + pMosicSelleft;
		pstrTopmiddle = m_sMosImgFolder + _T("\\") + pMosicSelmiddle;
		pstrTopright = m_sMosImgFolder + _T("\\") + pMosicSelright;
	}
	else
	{
		pstrTopleft = m_sMosImgFolder + _T("\\") + pMosicleft;
		pstrTopmiddle = m_sMosImgFolder + _T("\\") + pMosicmiddle;
		pstrTopright = m_sMosImgFolder + _T("\\") + pMosicright;
	}

	int nFixedWidth = GetFixedWidth();
	int nFixedHeight = GetFixedHeight();

	if ( m_bIsVerMosaicBk )
	{
		MosaicVertImage(hDC, pstrTopleft, pstrTopright, pstrTopmiddle, nFixedHeight);
	}
	else
	{
		MosaicHoriImage(hDC, pstrTopleft, pstrTopright, pstrTopmiddle, nFixedWidth);
	}
	
}

BOOL CControlUI::MosaicHoriImage( HDC hDC, LPCTSTR pstrImgLeft, LPCTSTR pstrImgRight, LPCTSTR pstrImgMiddle,
	int nFixedWidth, BOOL bDrawCorner, CPoint ptInCtl )
{

	if ( NULL == pstrImgLeft || NULL == pstrImgRight || NULL == pstrImgMiddle )
	{
		return FALSE;
	}

	const TImageInfo* dataLeft = NULL;
	dataLeft = const_cast<TImageInfo*>(m_pManager->GetImageEx(pstrImgLeft));
	if( NULL == dataLeft ) return FALSE;  

	const TImageInfo* dataRight = NULL;
	dataRight = const_cast<TImageInfo*>(m_pManager->GetImageEx(pstrImgRight));
	if( NULL == dataRight ) return FALSE; 

	const TImageInfo* dataMiddle = NULL;
	dataMiddle = const_cast<TImageInfo*>(m_pManager->GetImageEx(pstrImgMiddle));
	if( NULL == dataMiddle ) return FALSE; 

	if ( pstrImgLeft != NULL && pstrImgRight != NULL && pstrImgMiddle != NULL && dataMiddle->nX != 0 )
	{
		Image* pImg = NULL;
		SIZE szLeft;
		szLeft.cx = dataLeft->nX ;
		szLeft.cy = dataLeft->nY;
		SIZE szRight;
		szRight.cx  = dataRight->nX ;
		szRight.cy  = dataRight->nY ;

        Graphics graphics(hDC);

		if ( bDrawCorner )
		{
			pImg = const_cast<Image*>(m_pManager->GetImageP(pstrImgLeft)); 
			if ( NULL != pImg )
			{
				// 左
				
				if ( CPaintManagerUI::IsSelfAdaption() )
				{
					float fAdpX, fAdpY;
					CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
					szLeft.cx = dataLeft->nX * fAdpX;
					szLeft.cy = dataLeft->nY * fAdpY;
				}
                
                graphics.DrawImage( pImg, m_rcItem.left + ptInCtl.x, m_rcItem.top + ptInCtl.y, szLeft.cx, szLeft.cy);
				//DrawImageGDIPlus( hDC, szLeft, pImg, CPoint( ptInCtl.x, ptInCtl.y ) );
				//delete pImg;
			}

			pImg = const_cast<Image*>(m_pManager->GetImageP(pstrImgRight));  //new Image( strFileFullPath.c_str() );
			if ( NULL != pImg )
			{
				// 右
				if ( CPaintManagerUI::IsSelfAdaption() )
				{
					float fAdpX, fAdpY;
					CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
					szRight.cx = dataRight->nX * fAdpX;
					szRight.cy = dataRight->nY * fAdpY;
				}

                graphics.DrawImage( pImg, m_rcItem.left + ptInCtl.x + nFixedWidth - szRight.cx, m_rcItem.top + ptInCtl.y, szRight.cx, szRight.cy);
				//DrawImageGDIPlus( hDC, szRight, pImg, CPoint( ptInCtl.x + nFixedWidth - szRight.cx, ptInCtl.y ) );
			}
		}
		// 中
		unsigned int nPosX = ptInCtl.x + szLeft.cx;

		unsigned int dwMiddleWidth = 0;
		if ( nFixedWidth > szLeft.cx + szRight.cx )
		{
			dwMiddleWidth = nFixedWidth - szLeft.cx - szRight.cx;
		}

		SIZE szMid;
		szMid.cx = dataMiddle->nX;
		szMid.cy = dataMiddle->nY;
		TImageInfo* pdataMiddle = NULL;
		pImg =const_cast<Image*>(m_pManager->GetImageP(pstrImgMiddle));
		if ( NULL != pImg )
		{
			if ( CPaintManagerUI::IsSelfAdaption() )
			{
				float fAdpX, fAdpY;
				CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
				szMid.cx = dataMiddle->nX * fAdpX;
				szMid.cy = dataMiddle->nY * fAdpY;
			}
			for ( unsigned int nIndex = 0; nIndex < ( dwMiddleWidth /  szMid.cx ); nIndex++ )
			{
                graphics.DrawImage( pImg, m_rcItem.left + nPosX, m_rcItem.top + ptInCtl.y, szMid.cx, szMid.cy );
				//DrawImageGDIPlus( hDC, szMid, pImg, CPoint( nPosX, ptInCtl.y ));
				nPosX += szMid.cx;
			}
		}

		if ( dwMiddleWidth % szMid.cx != 0 )
		{
			pImg =const_cast<Image*>( m_pManager->GetImageP(pstrImgMiddle));
			if ( NULL != pImg )
			{
				//Graphics graphics(hDC);
				graphics.DrawImage( pImg, m_rcItem.left + nPosX, m_rcItem.top + ptInCtl.y, dwMiddleWidth % szMid.cx, szMid.cy );
			}
		}
	}

	return TRUE;
}

BOOL CControlUI::MosaicVertImage( HDC hDC, LPCTSTR pstrImgTop, LPCTSTR pstrImgBottom, LPCTSTR pstrImgMiddle, int nFixedHeight, BOOL bDrawCorner, CPoint ptInCtl )
{
	if ( NULL == pstrImgTop || NULL == pstrImgBottom || NULL == pstrImgMiddle )
	{
		return FALSE;
	}

	const TImageInfo* dataTop = NULL;
	dataTop = const_cast<TImageInfo*>(m_pManager->GetImageEx(pstrImgTop));
	if( NULL == dataTop ) return FALSE;  

	const TImageInfo* dataMid = NULL;
	dataMid = const_cast<TImageInfo*>(m_pManager->GetImageEx(pstrImgMiddle));
	if( NULL == dataMid ) return FALSE; 

	const TImageInfo* dataBottom = NULL;
	dataBottom = const_cast<TImageInfo*>(m_pManager->GetImageEx(pstrImgBottom));
	if( NULL == dataBottom ) return FALSE; 

	if ( pstrImgTop != NULL && pstrImgBottom != NULL && pstrImgMiddle != NULL && dataMid->nY != 0 )
	{
		SIZE szTop;
		SIZE szBottom;

		szTop.cx = dataTop->nX ;
		szTop.cy = dataTop->nY ;
		szBottom.cx = dataBottom->nX ;
		szBottom.cy = dataBottom->nY ;

		if ( CPaintManagerUI::IsSelfAdaption() )
		{
			float fAdpX, fAdpY;
			CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );

			szTop.cx = szTop.cx * fAdpX;
			szTop.cy = szTop.cy * fAdpY;
			szBottom.cx = szBottom.cx * fAdpX;
			szBottom.cy = szBottom.cy * fAdpY;
		}

		Image* pImg = NULL;

		if ( bDrawCorner )
		{
			pImg = const_cast<Image*>(m_pManager->GetImageP(pstrImgTop)); 
			if ( NULL != pImg )
			{
				DrawImageGDIPlus( hDC, szTop, pImg, CPoint( ptInCtl.x, ptInCtl.y ));
			}
			pImg = const_cast<Image*>( m_pManager->GetImageP(pstrImgBottom));  
			if ( NULL != pImg )
			{
				DrawImageGDIPlus( hDC, szBottom, pImg, CPoint( ptInCtl.x, ptInCtl.y + nFixedHeight - szBottom.cy ));
			}
		}

		// 中
		unsigned int nPosY = ptInCtl.y + szTop.cy;

		unsigned int dwMiddleHeight = 0;
		if ( nFixedHeight > szTop.cy + szBottom.cy )
		{
			dwMiddleHeight = nFixedHeight -  szTop.cy -  szBottom.cy;
		}

		SIZE szMid;
		pImg = const_cast<Image*>(m_pManager->GetImageP(pstrImgMiddle)); 
		if ( NULL != pImg )
		{
			szMid.cx = dataMid->nX;
			szMid.cy = dataMid->nY;
			if ( CPaintManagerUI::IsSelfAdaption() )
			{
				float fAdpX, fAdpY;
				CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
				szMid.cx = dataMid->nX * fAdpX;
				szMid.cy = dataMid->nY * fAdpY;
			}
			for ( unsigned int nIndex = 0; nIndex < ( dwMiddleHeight /  szMid.cy ); nIndex++ )
			{
				DrawImageGDIPlus( hDC, szMid, pImg, CPoint( ptInCtl.x, nPosY ) );
				nPosY += szMid.cy;
			}

		}

		if ( dwMiddleHeight % szMid.cy != 0 )
		{
			pImg = const_cast<Image*>( m_pManager->GetImageP(pstrImgMiddle));
			if ( NULL != pImg )
			{
				Graphics graphics(hDC);
				graphics.DrawImage( pImg, m_rcItem.left + ptInCtl.x, m_rcItem.top + nPosY, szMid.cx, dwMiddleHeight % szMid.cy );
			}
		}
	}

	return TRUE; 
}

// Image* CControlUI::GetImage( LPCTSTR strPath )
// {
// 	TCHAR chFile[MAX_PATH] = {0};  
// 	tString strTmpFile(strPath);
// 	wcscat( chFile, CPaintManagerUI::GetResourcePath() );
// 
// 	tString strFileFullPath;
// 	strFileFullPath += chFile;
// 	strFileFullPath += strTmpFile;
// 
// 	Image* pImg = new Image( strFileFullPath.c_str() ); 
// 
// 	return pImg;
// 
// }

const RECT& CControlUI::GetPos() const
{
    return m_rcItem;
}

void CControlUI::SetPos(RECT rc)
{
    if( rc.right < rc.left ) rc.right = rc.left;
    if( rc.bottom < rc.top ) rc.bottom = rc.top;

    CDuiRect invalidateRc = m_rcItem;
    if( ::IsRectEmpty(&invalidateRc) ) invalidateRc = rc;
 	if ( (m_rcItem.top != rc.top) ||  (m_rcItem.bottom != rc.bottom) || (m_rcItem.left != rc.left) || (m_rcItem.right != rc.right) )
 	{/*控件大小发生改变时*/
		m_rcItem = rc;
		m_pManager->SendNotify(this, DUI_MSGTYPE_CTRLSIZE, 0, 0);
	}
    
    if( m_pManager == NULL ) return;

    if( !m_bSetPos ) {
        m_bSetPos = true;
        if( OnSize ) OnSize(this);
        m_bSetPos = false;
    }
    
    if( m_bFloat ) {
        CControlUI* pParent = GetParent();
        if( pParent != NULL ) {
            RECT rcParentPos = pParent->GetPos();
            if( m_cXY.cx >= 0 ) m_cXY.cx = m_rcItem.left - rcParentPos.left;
            else m_cXY.cx = m_rcItem.right - rcParentPos.right;
            if( m_cXY.cy >= 0 ) m_cXY.cy = m_rcItem.top - rcParentPos.top;
            else m_cXY.cy = m_rcItem.bottom - rcParentPos.bottom;
            m_cxyFixed.cx = m_rcItem.right - m_rcItem.left;
            m_cxyFixed.cy = m_rcItem.bottom - m_rcItem.top;
        }
    }

    m_bUpdateNeeded = false;
    invalidateRc.Join(m_rcItem);

    CControlUI* pParent = this;
    RECT rcTemp;
    RECT rcParent;
    while( pParent = pParent->GetParent() )
    {
        rcTemp = invalidateRc;
        rcParent = pParent->GetPos();
        if( !::IntersectRect(&invalidateRc, &rcTemp, &rcParent) ) 
        {
            return;
        }
    }
    m_pManager->Invalidate(invalidateRc);
}

int CControlUI::GetWidth() const
{
    return m_rcItem.right - m_rcItem.left;
}

int CControlUI::GetHeight() const
{
    return m_rcItem.bottom - m_rcItem.top;
}

int CControlUI::GetX() const
{
    return m_rcItem.left;
}

int CControlUI::GetY() const
{
    return m_rcItem.top;
}

RECT CControlUI::GetPadding() const
{
    return m_rcPadding;
}

void CControlUI::SetPadding(RECT rcPadding)
{
	if ( CPaintManagerUI::IsSelfAdaption() )
	{
		float fAdpX, fAdpY;
		CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
		m_rcPadding.left = rcPadding.left * fAdpX;
		m_rcPadding.right = rcPadding.right * fAdpX;
		m_rcPadding.top = rcPadding.top * fAdpY;
		m_rcPadding.bottom = rcPadding.bottom * fAdpY;
	}
	else
	{
		m_rcPadding = rcPadding;
	}
 
    NeedParentUpdate();
}

SIZE CControlUI::GetFixedXY() const
{
    return m_cXY;
}

void CControlUI::SetFixedXY(SIZE szXY)
{
	if ( CPaintManagerUI::IsSelfAdaption() )
	{
		float fAdpX, fAdpY;
		CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
		m_cXY.cx = szXY.cx * fAdpX;
		m_cXY.cy = szXY.cy * fAdpY;
	}
	else
	{
		m_cXY.cx = szXY.cx;
		m_cXY.cy = szXY.cy;
	}
    if( !m_bFloat ) NeedParentUpdate();
    else NeedUpdate();
}

int CControlUI::GetFixedWidth() const
{
    return m_cxyFixed.cx;
}

void CControlUI::SetFixedWidth(int cx)
{
    if( cx < 0 ) return; 

	if ( CPaintManagerUI::IsSelfAdaption() )
	{
		float fAdpX, fAdpY;
		CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
		m_cxyFixed.cx = cx * fAdpX;
        if ( cx > 0 && m_cxyFixed.cx < 1 )
        {
            m_cxyFixed.cx = 1; //防止缩小后为0
        }
	}
	else
	{
		m_cxyFixed.cx = cx;
	}
    if( !m_bFloat ) NeedParentUpdate();
    else NeedUpdate();
}

void CControlUI::SetFixedWidthDirect(int cx)
{
	if( cx < 0 ) return; 

	m_cxyFixed.cx = cx;

	if( !m_bFloat ) NeedParentUpdate();
	else NeedUpdate();
}

int CControlUI::GetFixedHeight() const
{
    return m_cxyFixed.cy;
}

void CControlUI::SetFixedHeight(int cy)
{
    if( cy < 0 ) return; 

	if ( CPaintManagerUI::IsSelfAdaption() )
	{
		float fAdpX, fAdpY;
		CPaintManagerUI::GetAdpResolution( &fAdpX, &fAdpY );
		m_cxyFixed.cy = cy * fAdpY;
		if ( cy > 0 && m_cxyFixed.cy < 1 )
		{
			m_cxyFixed.cy = 1;
		}
	}
	else
	{
		m_cxyFixed.cy = cy;
	}
    if( !m_bFloat ) NeedParentUpdate();
    else NeedUpdate();
}

int CControlUI::GetMinWidth() const
{
    return m_cxyMin.cx;
}

void CControlUI::SetMinWidth(int cx)
{
    if( m_cxyMin.cx == cx ) return;

    if( cx < 0 ) return; 
    m_cxyMin.cx = cx;
    if( !m_bFloat ) NeedParentUpdate();
    else NeedUpdate();
}

int CControlUI::GetMaxWidth() const
{
    return m_cxyMax.cx;
}

void CControlUI::SetMaxWidth(int cx)
{
    if( m_cxyMax.cx == cx ) return;

    if( cx < 0 ) return; 
    m_cxyMax.cx = cx;
    if( !m_bFloat ) NeedParentUpdate();
    else NeedUpdate();
}

int CControlUI::GetMinHeight() const
{
    return m_cxyMin.cy;
}

void CControlUI::SetMinHeight(int cy)
{
    if( m_cxyMin.cy == cy ) return;

    if( cy < 0 ) return; 
    m_cxyMin.cy = cy;
    if( !m_bFloat ) NeedParentUpdate();
    else NeedUpdate();
}

int CControlUI::GetMaxHeight() const
{
    return m_cxyMax.cy;
}

void CControlUI::SetMaxHeight(int cy)
{
    if( m_cxyMax.cy == cy ) return;

    if( cy < 0 ) return; 
    m_cxyMax.cy = cy;
    if( !m_bFloat ) NeedParentUpdate();
    else NeedUpdate();
}

void CControlUI::SetRelativePos(SIZE szMove,SIZE szZoom)
{
    m_tRelativePos.bRelative = TRUE;
    m_tRelativePos.nMoveXPercent = szMove.cx;
    m_tRelativePos.nMoveYPercent = szMove.cy;
    m_tRelativePos.nZoomXPercent = szZoom.cx;
    m_tRelativePos.nZoomYPercent = szZoom.cy;
}

void CControlUI::SetRelativeParentSize(SIZE sz)
{
    m_tRelativePos.szParent = sz;
}

TRelativePosUI CControlUI::GetRelativePos() const
{
    return m_tRelativePos;
}

bool CControlUI::IsRelativePos() const
{
    return m_tRelativePos.bRelative;
}

CDuiString CControlUI::GetToolTip() const
{
    return m_sToolTip;
}

void CControlUI::SetToolTip(LPCTSTR pstrText)
{
	CDuiString strTemp(pstrText);
	strTemp.Replace(_T("<n>"),_T("\r\n"));
	m_sToolTip=strTemp;
}

void CControlUI::SetToolTipWidth( int nWidth )
{
	m_nTooltipWidth=nWidth;
}

int CControlUI::GetToolTipWidth( void )
{
	return m_nTooltipWidth;
}

TCHAR CControlUI::GetShortcut() const
{
    return m_chShortcut;
}

void CControlUI::SetShortcut(TCHAR ch)
{
    m_chShortcut = ch;
}

bool CControlUI::IsContextMenuUsed() const
{
    return m_bMenuUsed;
}

void CControlUI::SetContextMenuUsed(bool bMenuUsed)
{
    m_bMenuUsed = bMenuUsed;
}

const CDuiString& CControlUI::GetUserData()
{
    return m_sUserData;
}

void CControlUI::SetUserData(LPCTSTR pstrText)
{
    m_sUserData = pstrText;
}

UINT_PTR CControlUI::GetTag() const
{
    return m_pTag;
}

void CControlUI::SetTag(UINT_PTR pTag)
{
    m_pTag = pTag;
}

bool CControlUI::IsVisible() const
{

    return m_bVisible && m_bInternVisible;
}

void CControlUI::SetVisible(bool bVisible)
{
    if( m_bVisible == bVisible ) return;

    bool v = IsVisible();
    m_bVisible = bVisible;
    if( m_bFocused ) m_bFocused = false;
	if (!bVisible && m_pManager && m_pManager->GetFocus() == this) {
		m_pManager->SetFocus(NULL) ;
	}
    if( IsVisible() != v ) {
        NeedParentUpdate();
    }
}

void CControlUI::SetInternVisible(bool bVisible)
{
    m_bInternVisible = bVisible;
	if (!bVisible && m_pManager && m_pManager->GetFocus() == this) {
		m_pManager->SetFocus(NULL) ;
	}
}

bool CControlUI::IsEnabled() const
{
    return m_bEnabled;
}

void CControlUI::SetEnabled(bool bEnabled)
{
    if( m_bEnabled == bEnabled ) return;

    m_bEnabled = bEnabled;
    Invalidate();
}

bool CControlUI::IsMouseEnabled() const
{
    return m_bMouseEnabled;
}

void CControlUI::SetMouseEnabled(bool bEnabled)
{
    m_bMouseEnabled = bEnabled;
}

bool CControlUI::IsKeyboardEnabled() const
{
	return m_bKeyboardEnabled ;
}
void CControlUI::SetKeyboardEnabled(bool bEnabled)
{
	m_bKeyboardEnabled = bEnabled ; 
}

bool CControlUI::IsFocused() const
{
    return m_bFocused;
}

void CControlUI::SetFocus()
{
    if( m_pManager != NULL ) m_pManager->SetFocus(this);
}

bool CControlUI::IsFloat() const
{
    return m_bFloat;
}

void CControlUI::SetFloat(bool bFloat)
{
    if( m_bFloat == bFloat ) return;

    m_bFloat = bFloat;
    NeedParentUpdate();
}

CControlUI* CControlUI::FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags)
{
    if( (uFlags & UIFIND_VISIBLE) != 0 && !IsVisible() ) return NULL;
    if( (uFlags & UIFIND_ENABLED) != 0 && !IsEnabled() ) return NULL;
	if( (uFlags & UIFIND_HITTEST) != 0 && (!m_bMouseEnabled || !::PtInRect(&m_rcItem, * static_cast<LPPOINT>(pData))) ) return NULL;
    return Proc(this, pData);
}

void CControlUI::Invalidate()
{
    if( !IsVisible() ) return;

    RECT invalidateRc = m_rcItem;

    CControlUI* pParent = this;
    RECT rcTemp;
    RECT rcParent;
    while( pParent = pParent->GetParent() )
    {
        rcTemp = invalidateRc;
        rcParent = pParent->GetPos();
        if( !::IntersectRect(&invalidateRc, &rcTemp, &rcParent) ) 
        {
            return;
        }
    }

    if( m_pManager != NULL ) m_pManager->Invalidate(invalidateRc);
}

bool CControlUI::IsUpdateNeeded() const
{
    return m_bUpdateNeeded;
}

void CControlUI::NeedUpdate()
{
    if( !IsVisible() ) return;
    m_bUpdateNeeded = true;
    Invalidate();

    if( m_pManager != NULL ) m_pManager->NeedUpdate();
}

void CControlUI::NeedParentUpdate()
{
    if( GetParent() ) {
        GetParent()->NeedUpdate();
        GetParent()->Invalidate();
    }
    else {
        NeedUpdate();
    }

    if( m_pManager != NULL ) m_pManager->NeedUpdate();
}

DWORD CControlUI::GetAdjustColor(DWORD dwColor)
{
    if( !m_bColorHSL ) return dwColor;
    short H, S, L;
    CPaintManagerUI::GetHSL(&H, &S, &L);
    return CRenderEngine::AdjustColor(dwColor, H, S, L);
}

void CControlUI::Init()
{
    DoInit();
    if( OnInit ) OnInit(this);
}

void CControlUI::DoInit()
{

}

void CControlUI::Event(TEventUI& event)
{
    if( OnEvent(&event) ) DoEvent(event);
}

void CControlUI::DoEvent(TEventUI& event)
{
    if( event.Type == UIEVENT_SETCURSOR )
    {
        ::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)));
        return;
    }
    if( event.Type == UIEVENT_SETFOCUS ) 
    {
        m_bFocused = true;
        Invalidate();
        return;
    }
    if( event.Type == UIEVENT_KILLFOCUS ) 
    {
        m_bFocused = false;
        Invalidate();
        return;
    }
    if( event.Type == UIEVENT_TIMER )
    {
        m_pManager->SendNotify(this, DUI_MSGTYPE_TIMER, event.wParam, event.lParam);
        return;
    }
    if( event.Type == UIEVENT_CONTEXTMENU )
    {
        if( IsContextMenuUsed() ) {
            m_pManager->SendNotify(this, DUI_MSGTYPE_MENU, event.wParam, event.lParam);
            return;
        }
    }
	//Add by zh.
	if ( event.Type == UIEVENT_MOUSEENTER)
	{
		m_pManager->SendNotify(this,DUI_MSGTYPE_MOUSEENTER);
	}

	if ( event.Type == UIEVENT_MOUSELEAVE)
	{
		m_pManager->SendNotify(this,DUI_MSGTYPE_MOUSELEAVE);
	}
	if ( event.Type == UIEVENT_MOUSEMOVE)
	{
		m_pManager->SendNotify(this, DUI_MSGTYPE_MOUSEMOVE);
	}
    if ( event.Type == UIEVENT_BUTTONUP)
    {/*增加双击界面显示*/
        m_pManager->SendNotify(this, DUI_MSGTYPE_CLICK);
    }
	if ( event.Type == UIEVENT_DBLCLICK)
	{/*增加双击界面显示*/
		m_pManager->SendNotify(this, DUI_MSGTYPE_DBCLICK);
	}

	CDuiDragControlUI::DoEvent(event);
    if( m_pParent != NULL ) m_pParent->DoEvent(event);
}


void CControlUI::SetVirtualWnd(LPCTSTR pstrValue)
{
	m_sVirtualWnd = pstrValue;
	m_pManager->UsedVirtualWnd(true);
}

CDuiString CControlUI::GetVirtualWnd() const
{
	CDuiString str;
	if( !m_sVirtualWnd.IsEmpty() ){
		str = m_sVirtualWnd;
	}
	else{
		CControlUI* pParent = GetParent();
		if( pParent != NULL){
			str = pParent->GetVirtualWnd();
		}
		else{
			str = _T("");
		}
	}
	return str;
}

void CControlUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
    if( _tcscmp(pstrName, _T("pos")) == 0 ) {
        RECT rcPos = { 0 };
        LPTSTR pstr = NULL;
        rcPos.left = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
        rcPos.top = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);    
        rcPos.right = _tcstol(pstr + 1, &pstr, 10);  ASSERT(pstr);    
        rcPos.bottom = _tcstol(pstr + 1, &pstr, 10); ASSERT(pstr);    
        SIZE szXY = {rcPos.left >= 0 ? rcPos.left : rcPos.right, rcPos.top >= 0 ? rcPos.top : rcPos.bottom};
        SetFixedXY(szXY);
        SetFixedWidth(rcPos.right - rcPos.left);
        SetFixedHeight(rcPos.bottom - rcPos.top);
    }
    else if( _tcscmp(pstrName, _T("relativepos")) == 0 ) {
        SIZE szMove,szZoom;
        LPTSTR pstr = NULL;
        szMove.cx = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
        szMove.cy = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);    
        szZoom.cx = _tcstol(pstr + 1, &pstr, 10);  ASSERT(pstr);    
        szZoom.cy = _tcstol(pstr + 1, &pstr, 10); ASSERT(pstr); 
        SetRelativePos(szMove,szZoom);
    }
    else if( _tcscmp(pstrName, _T("padding")) == 0 ) {
        RECT rcPadding = { 0 };
        LPTSTR pstr = NULL;
        rcPadding.left = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
        rcPadding.top = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);    
        rcPadding.right = _tcstol(pstr + 1, &pstr, 10);  ASSERT(pstr);    
        rcPadding.bottom = _tcstol(pstr + 1, &pstr, 10); ASSERT(pstr);    
        SetPadding(rcPadding);
    }
    else if( _tcscmp(pstrName, _T("bkcolor")) == 0 || _tcscmp(pstrName, _T("bkcolor1")) == 0 ) {
        while( *pstrValue > _T('\0') && *pstrValue <= _T(' ') ) pstrValue = ::CharNext(pstrValue);
        if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
        LPTSTR pstr = NULL;
        DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
        SetBkColor(clrColor);
    }
    else if( _tcscmp(pstrName, _T("bkcolor2")) == 0 ) {
        while( *pstrValue > _T('\0') && *pstrValue <= _T(' ') ) pstrValue = ::CharNext(pstrValue);
        if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
        LPTSTR pstr = NULL;
        DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
        SetBkColor2(clrColor);
    }
    else if( _tcscmp(pstrName, _T("bkcolor3")) == 0 ) {
        while( *pstrValue > _T('\0') && *pstrValue <= _T(' ') ) pstrValue = ::CharNext(pstrValue);
        if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
        LPTSTR pstr = NULL;
        DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
        SetBkColor3(clrColor);
    }
    else if( _tcscmp(pstrName, _T("bordercolor")) == 0 ) {
        if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
        LPTSTR pstr = NULL;
        DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
        SetBorderColor(clrColor);
    }
    else if( _tcscmp(pstrName, _T("focusbordercolor")) == 0 ) {
        if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
        LPTSTR pstr = NULL;
        DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
        SetFocusBorderColor(clrColor);
    }
    else if( _tcscmp(pstrName, _T("colorhsl")) == 0 ) SetColorHSL(_tcscmp(pstrValue, _T("true")) == 0);
	else if( _tcscmp(pstrName, _T("bordersize")) == 0 ) {
		CDuiString nValue = pstrValue;
		if(nValue.Find(',') < 0)
		{
			SetBorderSize(_ttoi(pstrValue));
			RECT rcPadding = {0};
			SetBorderSize(rcPadding);
		}
		else
		{
			RECT rcPadding = { 0 };
			LPTSTR pstr = NULL;
			rcPadding.left = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);
			rcPadding.top = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);
			rcPadding.right = _tcstol(pstr + 1, &pstr, 10);  ASSERT(pstr);
			rcPadding.bottom = _tcstol(pstr + 1, &pstr, 10); ASSERT(pstr);
			SetBorderSize(rcPadding);
		}
	}
	else if( _tcscmp(pstrName, _T("leftbordersize")) == 0 ) SetLeftBorderSize(_ttoi(pstrValue));
	else if( _tcscmp(pstrName, _T("topbordersize")) == 0 ) SetTopBorderSize(_ttoi(pstrValue));
	else if( _tcscmp(pstrName, _T("rightbordersize")) == 0 ) SetRightBorderSize(_ttoi(pstrValue));
	else if( _tcscmp(pstrName, _T("bottombordersize")) == 0 ) SetBottomBorderSize(_ttoi(pstrValue));
	else if( _tcscmp(pstrName, _T("borderstyle")) == 0 ) SetBorderStyle(_ttoi(pstrValue));
    else if( _tcscmp(pstrName, _T("borderround")) == 0 ) {
        SIZE cxyRound = { 0 };
        LPTSTR pstr = NULL;
        cxyRound.cx = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
        cxyRound.cy = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);     
        SetBorderRound(cxyRound);
    }
    else if( _tcscmp(pstrName, _T("bkimage")) == 0 ) SetBkImage(pstrValue);
    else if( _tcscmp(pstrName, _T("width")) == 0 ) SetFixedWidth(_ttoi(pstrValue));
    else if( _tcscmp(pstrName, _T("height")) == 0 ) SetFixedHeight(_ttoi(pstrValue));
    else if( _tcscmp(pstrName, _T("minwidth")) == 0 ) SetMinWidth(_ttoi(pstrValue));
    else if( _tcscmp(pstrName, _T("minheight")) == 0 ) SetMinHeight(_ttoi(pstrValue));
    else if( _tcscmp(pstrName, _T("maxwidth")) == 0 ) SetMaxWidth(_ttoi(pstrValue));
    else if( _tcscmp(pstrName, _T("maxheight")) == 0 ) SetMaxHeight(_ttoi(pstrValue));
    else if( _tcscmp(pstrName, _T("name")) == 0 ) SetName(pstrValue);
    else if( _tcscmp(pstrName, _T("text")) == 0 ) SetText(pstrValue);
    else if( _tcscmp(pstrName, _T("tooltip")) == 0 ) SetToolTip(pstrValue);
    else if( _tcscmp(pstrName, _T("userdata")) == 0 ) SetUserData(pstrValue);
    else if( _tcscmp(pstrName, _T("enabled")) == 0 ) SetEnabled(_tcscmp(pstrValue, _T("true")) == 0);
    else if( _tcscmp(pstrName, _T("mouse")) == 0 ) SetMouseEnabled(_tcscmp(pstrValue, _T("true")) == 0);
	else if( _tcscmp(pstrName, _T("keyboard")) == 0 ) SetKeyboardEnabled(_tcscmp(pstrValue, _T("true")) == 0);
    else if( _tcscmp(pstrName, _T("visible")) == 0 ) SetVisible(_tcscmp(pstrValue, _T("true")) == 0);
    else if( _tcscmp(pstrName, _T("float")) == 0 ) SetFloat(_tcscmp(pstrValue, _T("true")) == 0);
	else if( _tcscmp(pstrName, _T("alwayschangebk")) == 0 ) SetIsAlwaysChangeBk(_tcscmp(pstrValue, _T("true")) == 0);
    else if( _tcscmp(pstrName, _T("shortcut")) == 0 ) SetShortcut(pstrValue[0]);
    else if( _tcscmp(pstrName, _T("menu")) == 0 ) SetContextMenuUsed(_tcscmp(pstrValue, _T("true")) == 0);
	else if( _tcscmp(pstrName, _T("virtualwnd")) == 0 ) SetVirtualWnd(pstrValue);
    else if( _tcscmp(pstrName, _T("tag")) == 0 ) SetTag(_ttoi(pstrValue));
	else if( _tcscmp(pstrName, _T("isvermosaicbk")) == 0 ) SetVerMosaicBk( 0 == _tcscmp(pstrValue, _T("true")) );//背景拼接属性 dyy
	else if( _tcscmp(pstrName, _T("mosimgfolfer")) == 0 ) SetMosImgFolder(pstrValue);//背景拼接属性 dyy
	CDuiDragControlUI::SetAttribute(pstrName,pstrValue);
}

CControlUI* CControlUI::ApplyAttributeList(LPCTSTR pstrList)
{
    CDuiString sItem;
    CDuiString sValue;
    while( *pstrList != _T('\0') ) {
        sItem.Empty();
        sValue.Empty();
        while( *pstrList != _T('\0') && *pstrList != _T('=') ) {
            LPTSTR pstrTemp = ::CharNext(pstrList);
            while( pstrList < pstrTemp) {
                sItem += *pstrList++;
            }
        }
        ASSERT( *pstrList == _T('=') );
        if( *pstrList++ != _T('=') ) return this;
        ASSERT( *pstrList == _T('\"') );
        if( *pstrList++ != _T('\"') ) return this;
        while( *pstrList != _T('\0') && *pstrList != _T('\"') ) {
            LPTSTR pstrTemp = ::CharNext(pstrList);
            while( pstrList < pstrTemp) {
                sValue += *pstrList++;
            }
        }
        ASSERT( *pstrList == _T('\"') );
        if( *pstrList++ != _T('\"') ) return this;
        SetAttribute(sItem, sValue);
        if( *pstrList++ != _T(' ') ) return this;
    }
    return this;
}

SIZE CControlUI::EstimateSize(SIZE szAvailable)
{
    return m_cxyFixed;
}

void CControlUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
    if( !::IntersectRect(&m_rcPaint, &rcPaint, &m_rcItem) ) return;

    // 绘制循序：背景颜色->背景图->状态图->文本->边框
    if( m_cxyBorderRound.cx > 0 || m_cxyBorderRound.cy > 0 ) {
        CRenderClip roundClip;
        CRenderClip::GenerateRoundClip(hDC, m_rcPaint,  m_rcItem, m_cxyBorderRound.cx, m_cxyBorderRound.cy, roundClip);
        PaintBkColor(hDC);
        PaintBkImage(hDC);
        PaintStatusImage(hDC);
        PaintText(hDC);
        PaintBorder(hDC);
    }
    else {
        PaintBkColor(hDC);
        PaintBkImage(hDC);
        PaintStatusImage(hDC);
        PaintText(hDC);
        PaintBorder(hDC);
    }
}

void CControlUI::PaintBkColor(HDC hDC)
{
    if( m_dwBackColor != 0 ) {
        if( m_dwBackColor2 != 0 ) {
            if( m_dwBackColor3 != 0 ) {
                RECT rc = m_rcItem;
                rc.bottom = (rc.bottom + rc.top) / 2;
                CRenderEngine::DrawGradient(hDC, rc, GetAdjustColor(m_dwBackColor), GetAdjustColor(m_dwBackColor2), true, 8);
                rc.top = rc.bottom;
                rc.bottom = m_rcItem.bottom;
                CRenderEngine::DrawGradient(hDC, rc, GetAdjustColor(m_dwBackColor2), GetAdjustColor(m_dwBackColor3), true, 8);
            }
            else 
                CRenderEngine::DrawGradient(hDC, m_rcItem, GetAdjustColor(m_dwBackColor), GetAdjustColor(m_dwBackColor2), true, 16);
        }
        else if( m_dwBackColor >= 0xFF000000 ) CRenderEngine::DrawColor(hDC, m_rcPaint, GetAdjustColor(m_dwBackColor));
        else CRenderEngine::DrawColor(hDC, m_rcItem, GetAdjustColor(m_dwBackColor));
    }
}

void CControlUI::PaintBkImage(HDC hDC)
{
    if( m_sBkImage.IsEmpty() ) return;

	if ( !m_bIsVerMosaicBk )
	{
		if( !DrawImage(hDC, (LPCTSTR)m_sBkImage) ) m_sBkImage.Empty();
	}
	else
	{
		DrawMosaicImage(hDC);
	}
}

void CControlUI::PaintStatusImage(HDC hDC)
{
    return;
}

void CControlUI::PaintText(HDC hDC)
{
    return;
}

void CControlUI::PaintBorder(HDC hDC)
{
	if(m_dwBorderColor != 0 || m_dwFocusBorderColor != 0)
	{
		if(m_nBorderSize > 0 && ( m_cxyBorderRound.cx > 0 || m_cxyBorderRound.cy > 0 ))//画圆角边框
		{
			if (IsFocused() && m_dwFocusBorderColor != 0)
				CRenderEngine::DrawRoundRect(hDC, m_rcItem, m_nBorderSize, m_cxyBorderRound.cx, m_cxyBorderRound.cy, GetAdjustColor(m_dwFocusBorderColor));
			else
				CRenderEngine::DrawRoundRect(hDC, m_rcItem, m_nBorderSize, m_cxyBorderRound.cx, m_cxyBorderRound.cy, GetAdjustColor(m_dwBorderColor));
		}
		else
		{
			if (IsFocused() && m_dwFocusBorderColor != 0 && m_nBorderSize > 0)
				CRenderEngine::DrawRect(hDC, m_rcItem, m_nBorderSize, GetAdjustColor(m_dwFocusBorderColor));
			else if(m_rcBorderSize.left > 0 || m_rcBorderSize.top > 0 || m_rcBorderSize.right > 0 || m_rcBorderSize.bottom > 0)
			{
				RECT rcBorder;

				if(m_rcBorderSize.left > 0){
					rcBorder		= m_rcItem;
					rcBorder.right	= m_rcItem.left;
					CRenderEngine::DrawLine(hDC,rcBorder,m_rcBorderSize.left,GetAdjustColor(m_dwBorderColor),m_nBorderStyle);
				}
				if(m_rcBorderSize.top > 0){
					rcBorder		= m_rcItem;
					rcBorder.bottom	= m_rcItem.top;
					CRenderEngine::DrawLine(hDC,rcBorder,m_rcBorderSize.top,GetAdjustColor(m_dwBorderColor),m_nBorderStyle);
				}
				if(m_rcBorderSize.right > 0){
					rcBorder		= m_rcItem;
					rcBorder.left	= m_rcItem.right;
					CRenderEngine::DrawLine(hDC,rcBorder,m_rcBorderSize.right,GetAdjustColor(m_dwBorderColor),m_nBorderStyle);
				}
				if(m_rcBorderSize.bottom > 0){
					rcBorder		= m_rcItem;
					rcBorder.top	= m_rcItem.bottom;
					CRenderEngine::DrawLine(hDC,rcBorder,m_rcBorderSize.bottom,GetAdjustColor(m_dwBorderColor),m_nBorderStyle);
				}
			}
			else if(m_nBorderSize > 0)
				CRenderEngine::DrawRect(hDC, m_rcItem, m_nBorderSize, GetAdjustColor(m_dwBorderColor));
		}
	}
}

void CControlUI::DoPostPaint(HDC hDC, const RECT& rcPaint)
{
    return;
}

//************************************
// 函数名称: GetLeftBorderSize
// 返回类型: int
// 函数说明: 
//************************************
int CControlUI::GetLeftBorderSize() const
{
	return m_rcBorderSize.left;
}

//************************************
// 函数名称: SetLeftBorderSize
// 返回类型: void
// 参数信息: int nSize
// 函数说明: 
//************************************
void CControlUI::SetLeftBorderSize( int nSize )
{
	m_rcBorderSize.left = nSize;
	Invalidate();
}

//************************************
// 函数名称: GetTopBorderSize
// 返回类型: int
// 函数说明: 
//************************************
int CControlUI::GetTopBorderSize() const
{
	return m_rcBorderSize.top;
}

//************************************
// 函数名称: SetTopBorderSize
// 返回类型: void
// 参数信息: int nSize
// 函数说明: 
//************************************
void CControlUI::SetTopBorderSize( int nSize )
{
	m_rcBorderSize.top = nSize;
	Invalidate();
}

//************************************
// 函数名称: GetRightBorderSize
// 返回类型: int
// 函数说明: 
//************************************
int CControlUI::GetRightBorderSize() const
{
	return m_rcBorderSize.right;
}

//************************************
// 函数名称: SetRightBorderSize
// 返回类型: void
// 参数信息: int nSize
// 函数说明: 
//************************************
void CControlUI::SetRightBorderSize( int nSize )
{
	m_rcBorderSize.right = nSize;
	Invalidate();
}

//************************************
// 函数名称: GetBottomBorderSize
// 返回类型: int
// 函数说明: 
//************************************
int CControlUI::GetBottomBorderSize() const
{
	return m_rcBorderSize.bottom;
}

//************************************
// 函数名称: SetBottomBorderSize
// 返回类型: void
// 参数信息: int nSize
// 函数说明: 
//************************************
void CControlUI::SetBottomBorderSize( int nSize )
{
	m_rcBorderSize.bottom = nSize;
	Invalidate();
}

//************************************
// 函数名称: GetBorderStyle
// 返回类型: int
// 函数说明: 
//************************************
int CControlUI::GetBorderStyle() const
{
	return m_nBorderStyle;
}

//************************************
// 函数名称: SetBorderStyle
// 返回类型: void
// 参数信息: int nStyle
// 函数说明: 
//************************************
void CControlUI::SetBorderStyle( int nStyle )
{
	m_nBorderStyle = nStyle;
	Invalidate();
}

void CControlUI::SetMosImgFolder( LPCTSTR pStrImage )
{
	if( m_sMosImgFolder == pStrImage ) return;

	m_sMosImgFolder = pStrImage;
}

void CControlUI::SetIsAlwaysChangeBk( bool bIsAlwaysChangeBk /*= false*/ )
{
	if( m_bIsAlwaysChangeBk == bIsAlwaysChangeBk ) return;
	m_bIsAlwaysChangeBk = bIsAlwaysChangeBk;
}

} // namespace DuiLib
