#pragma once

#include <afxwin.h>

#include "opencv2/opencv.hpp"													//eyedea - opencv lib.
#include "opencv2/freetype.hpp"

#include "use_opencv_lib.h"

class CLoadBitmap
{
public:
	CLoadBitmap();
	~CLoadBitmap();

	void Load(const int idb_bitmap, const float scale, cv::Mat* out_mat);
};

