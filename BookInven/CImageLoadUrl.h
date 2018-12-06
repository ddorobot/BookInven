#pragma once

#include "opencv2/opencv.hpp"
#include "use_opencv_lib.h"

#include <curl/curl.h>

class CImageLoadUrl
{
public:
	CImageLoadUrl();
	~CImageLoadUrl();

	cv::Mat Load(const char *img_url, int timeout = 10);

private:
	static size_t write_data(char *ptr, size_t size, size_t nmemb, void *userdata);
};

