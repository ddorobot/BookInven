#include "CDrawToHDC.h"



CDrawToHDC::CDrawToHDC()
{
}


CDrawToHDC::~CDrawToHDC()
{
}

CV_INLINE RECT NormalizeRect(RECT r);
CV_INLINE RECT NormalizeRect(RECT r)
{
	int t;
	if (r.left > r.right)
	{
		t = r.left;
		r.left = r.right;
		r.right = t;
	}
	if (r.top > r.bottom)
	{
		t = r.top;

		r.top = r.bottom;
		r.bottom = t;
	}

	return r;
}

CV_INLINE cv::Rect RectToCvRect(RECT sr);
CV_INLINE cv::Rect RectToCvRect(RECT sr)
{
	sr = NormalizeRect(sr);
	return cv::Rect(sr.left, sr.top, sr.right - sr.left, sr.bottom - sr.top);
}

void  FillBitmapInfo(BITMAPINFO* bmi, int width, int height, int bpp, int origin)
{
	assert(bmi && width >= 0 && height >= 0 && (bpp == 8 || bpp == 24 || bpp == 32));

	BITMAPINFOHEADER* bmih = &(bmi->bmiHeader);

	memset(bmih, 0, sizeof(*bmih));
	bmih->biSize = sizeof(BITMAPINFOHEADER);
	bmih->biWidth = width;
	bmih->biHeight = origin ? abs(height) : -abs(height);
	bmih->biPlanes = 1;
	bmih->biBitCount = (unsigned short)bpp;
	bmih->biCompression = BI_RGB;
	if (bpp == 8)
	{
		RGBQUAD* palette = bmi->bmiColors;
		int i;
		for (i = 0; i < 256; i++)
		{
			palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
			palette[i].rgbReserved = 0;
		}
	}
}

void  CDrawToHDC::Show(cv::Mat image, HDC dc, int x, int y, int w, int h, int from_x, int from_y)
{
	if (!image.empty() && image.depth() == CV_8U)
	{
		uchar buffer[sizeof(BITMAPINFOHEADER) + 1024];
		BITMAPINFO* bmi = (BITMAPINFO*)buffer;
		int bmp_w = image.cols, bmp_h = image.rows;
		FillBitmapInfo(bmi, bmp_w, bmp_h, Bpp(image), 0);
		from_x = MIN(MAX(from_x, 0), bmp_w - 1);
		from_y = MIN(MAX(from_y, 0), bmp_h - 1);
		int sw = MAX(MIN(bmp_w - from_x, w), 0);
		int sh = MAX(MIN(bmp_h - from_y, h), 0);
		SetDIBitsToDevice(
			dc, x, y, sw, sh, from_x, from_y, from_y, sh,
			image.data + from_y * image.cols,
			bmi, DIB_RGB_COLORS);
	}
}

void CDrawToHDC::DrawToHDC(cv::Mat image, HDC hDCDst, RECT* pDstRect)
{
	if (pDstRect && !image.empty() && image.depth() == CV_8U)
	{
		uchar buffer[sizeof(BITMAPINFOHEADER) + 1024];
		BITMAPINFO* bmi = (BITMAPINFO*)buffer;
		int bmp_w = image.cols, bmp_h = image.rows;
		cv::Rect roi = cv::Rect(0,0,image.cols, image.rows);
		cv::Rect dst = RectToCvRect(*pDstRect);
		if (roi.width == dst.width && roi.height == dst.height)
		{
			Show(image, hDCDst, dst.x, dst.y, dst.width, dst.height, roi.x, roi.y);
			return;
		}
		if (roi.width > dst.width)
		{
			SetStretchBltMode(
				hDCDst,           // handle to device context
				HALFTONE);
		}
		else
		{
			SetStretchBltMode(
				hDCDst,           // handle to device context
				COLORONCOLOR);
		}

		FillBitmapInfo(bmi, bmp_w, bmp_h, Bpp(image), 0);
		::StretchDIBits(
			hDCDst,
			dst.x, dst.y, dst.width, dst.height,
			roi.x, roi.y, roi.width, roi.height,
			image.data, bmi, DIB_RGB_COLORS, SRCCOPY);
	}
}