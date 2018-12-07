#pragma once

#include <gdiplus.h>

#pragma comment(lib, "gdiplus.lib")

class CGifImage
{
public:
	CGifImage(void);
	CGifImage(IStream *pStream);
	~CGifImage(void);

public:
	BOOL SaveAsFile(LPCTSTR pszFileName);
	void Destroy();
	BOOL IsAnimatedGif();
	UINT GetFrameCount();
	long GetFrameDelay(int nFramePos = -1);
	void ActiveNextFrame();
	void SelectActiveFrame(int nFramePos);
	BOOL Draw(HDC hDestDC, int xDest, int yDest, int nFramePos = -1);
	BOOL Draw(HDC hDestDC, const RECT& rectDest, int nFramePos = -1);
	int GetWidth();
	int GetHeight();
	UINT GetCurFramePos();
	BOOL GetRawFormat(GUID * lpGuid);

private:
	CLSID GetEncoderClsidByExtension(const WCHAR * lpExtension);
	BOOL LoadGifInfo();

private:
	IStream *m_pIstream;
	Gdiplus::Image* m_pImage;		// ͼƬ����ָ��
	UINT m_nFrameCnt;				// GIF������֡��
	UINT m_nFramePos;				// ��ǰ֡
	long *m_pFrameDelay;			// ÿ֡�л���ʱʱ��
};
