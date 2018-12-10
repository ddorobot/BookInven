#pragma once

#include "afxwin.h"
#include "opencv2/opencv.hpp"

class CDrawToHDC
{
public:
	CDrawToHDC();
	~CDrawToHDC();

	void  DrawToHDC(cv::Mat image, HDC hDCDst, RECT* pDstRect);
};

