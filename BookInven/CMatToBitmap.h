#pragma once

#include "opencv2/opencv.hpp"													//eyedea - opencv lib.
#include "opencv2/freetype.hpp"

#include "use_opencv_lib.h"

#include "CDrawToHDC.h"

class CMatToBitmap
{
public:
	CMatToBitmap();
	~CMatToBitmap();

	CBitmap* Cvt(cv::Mat image);
	void Release(CBitmap* bmp);
};

