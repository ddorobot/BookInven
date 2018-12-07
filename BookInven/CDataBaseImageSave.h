#pragma once

#include <afxwin.h>

#include <string>

#include <boost/thread.hpp>

#include "boost\thread\detail\thread.hpp"
#include "boost\property_tree\ptree.hpp"
#include "boost\property_tree\ini_parser.hpp"
#include "boost\filesystem\operations.hpp"
#include "boost\range\iterator_range.hpp"

#include "boost\system\error_code.hpp"

#include "opencv2/opencv.hpp"
#include "use_opencv_lib.h"

#define BASE_SAVE_PATH	"./data/"
#define BASE_SAVE_FOLDER	"image/"

class CDataBaseImageSave
{
public:
	CDataBaseImageSave();
	~CDataBaseImageSave();

	std::string Save(cv::Mat image, const std::string name);
};

