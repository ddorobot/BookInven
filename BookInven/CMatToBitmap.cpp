#include "CMatToBitmap.h"



CMatToBitmap::CMatToBitmap()
{
}

CMatToBitmap::~CMatToBitmap()
{
}

CBitmap* CMatToBitmap::Cvt(cv::Mat image)
{
	CBitmap* bmp = NULL;

	CDC dc;
	CDC memDC;

	if (!dc.CreateDC("DISPLAY", NULL, NULL, NULL))
		return NULL;

	if (!memDC.CreateCompatibleDC(&dc))
		return NULL;

	if (image.empty())
		return NULL;

	bmp = new CBitmap();
	CBitmap* pOldBitmap;

	bmp->CreateCompatibleBitmap(&dc, image.cols, image.rows);
	pOldBitmap = memDC.SelectObject(bmp);

	CDrawToHDC cls_draw_to_hdc;

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = image.cols;
	rect.bottom = image.rows;

	cls_draw_to_hdc.DrawToHDC(image, memDC.m_hDC, &rect);

	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	dc.DeleteDC();

	return bmp;
}

void CMatToBitmap::Release(CBitmap* bmp)
{
	if (bmp)
	{
		delete bmp;
		bmp = NULL;
	}
}