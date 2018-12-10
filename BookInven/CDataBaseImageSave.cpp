#include "CDataBaseImageSave.h"



CDataBaseImageSave::CDataBaseImageSave()
{
}


CDataBaseImageSave::~CDataBaseImageSave()
{
}

std::string CDataBaseImageSave::Save(cv::Mat image, const std::string name)
{
	std::string str_base_path = std::string(BASE_SAVE_PATH);

	if (!(boost::filesystem::is_directory(str_base_path.c_str())))             // true - is directory
	{
		boost::filesystem::path dir(str_base_path.c_str()); 
		if (boost::filesystem::create_directory(dir))
		{
			printf("crate db image directory - %s\n", str_base_path.c_str());
		}
	}

	str_base_path += std::string(BASE_SAVE_FOLDER);

	if (!(boost::filesystem::is_directory(str_base_path.c_str())))             // true - is directory
	{
		boost::filesystem::path dir(str_base_path.c_str());
		if (boost::filesystem::create_directory(dir))
		{
			printf("crate db image directory - %s\n", str_base_path.c_str());
		}
	}

	bool b_image_file_exist = false;

	std::string image_full_path = str_base_path + name;

	if (boost::filesystem::exists(image_full_path.c_str()))
	{
		b_image_file_exist = true;
	}

	bool b_image_file_save = true;

	if (b_image_file_exist)
	{
		const int result = MessageBox(NULL, "같은 이름의 이미지가 이미 저장되어 있습니다. 덮어쓰시겠습니까?", "이미지 저장", MB_YESNO);

		switch (result)
		{
		case IDYES:
			// Do something
			b_image_file_save = true;
			break;
		case IDNO:
			b_image_file_save = false;
			// Do something
			break;
		}
	}

	if (b_image_file_save)
	{
		cv::imwrite(image_full_path, image);
	}

	return image_full_path;
}