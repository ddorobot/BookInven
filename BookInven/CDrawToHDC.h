#pragma once

#include "afxwin.h"
#include "opencv2/opencv.hpp"

class CDrawToHDC
{
public:
	CDrawToHDC();
	~CDrawToHDC();

	int Bpp(cv::Mat image) { return !image.empty() ? (8 & 255)*image.channels() : 0; };

	void  DrawToHDC(cv::Mat image, HDC hDCDst, RECT* pDstRect);
	void  Show(cv::Mat image, HDC dc, int x, int y, int w, int h, int from_x, int from_y);
};

