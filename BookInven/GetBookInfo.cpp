#include "stdafx.h"
#include "GetBookInfo.h"


GetBookInfo::GetBookInfo()
{
}


GetBookInfo::~GetBookInfo()
{
}

std::string GetBookInfo::GetISBNInfo(const UINT nChar)
{
	std::string str_isbn;

	boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
	//boost::gregorian::date d = now.date();                      /* Extract date */
	//boost::posix_time::time_duration t = now.time_of_day();     /* Extract time */

	//cout << d.year() << "/" << (int)d.month() << "/" << d.day() << " " << t.hours() << ":" << t.minutes() << ":" << t.seconds() << endl;

	StreamInfo stream;
	stream.nChar = nChar;
	stream.gettime = now;

	m_strem.push_back(stream);

	int stream_size = m_strem.size();

	if (stream_size > 0)
	{
		int stream_last_index = stream_size - 1;

		if (stream_last_index >= ISBN_CODE_SIZE)
		{
			if (m_strem[stream_last_index].nChar == 13 /*Enter*/)
			{
				int stream_start_index = stream_last_index - ISBN_CODE_SIZE;

				std::string temp_isbn;
				for (int i = stream_start_index; i < stream_last_index; i++)
				{
					//check num
					if (m_strem[i].nChar >= 48 && m_strem[i].nChar <= 57)
					{
						temp_isbn += (char)(m_strem[i].nChar);
					}
					else
					{
						break;
					}
				}

				if (temp_isbn.size() == ISBN_CODE_SIZE)
				{
					str_isbn = temp_isbn;

					//삭제
					for (int i = 0; i <= stream_last_index; i++)
					{
						m_strem.pop_front();
					}
				}
			}
		}
	}

	return str_isbn;
}

BookInfo GetBookInfo::GetInfo(const std::string isbn)
{ 
	BookInfo info; 

	if (isbn.empty()) return info;

	//DB에 정보가 있는지 확인
	int ret = m_cls_get_bookinfo_using_db.GetBookInfo(isbn, &info);

	if (ret <= 0)		//DB에 정보가 없다면 서지정보를 인터넷을 통하여 얻는다.
	{
		printf("Search From Internet : code=%s\n", isbn.c_str());

		ret = m_cls_get_bookinfo_using_url.GetBookInfo(isbn, &info);

		if (ret > 0)
		{
			//DB에 저장.
			if (!info.title_url.empty())
			{
				CImageLoadUrl cls_image_load_url;
				cv::Mat read_title_image = cls_image_load_url.Load(info.title_url.c_str());

				if (!read_title_image.empty())
				{
					CDataBaseImageSave cls_image_save;
					std::string image_save_file_name = info.isbn;
					image_save_file_name += ".png";

					std::string str_save_file_path = cls_image_save.Save(read_title_image, image_save_file_name);

					//url의 주소를 실제로 local에 저장한 path로 변경 한다.
					info.title_url = str_save_file_path;
				}
			}

			m_cls_get_bookinfo_using_db.AddBookInfo(info);

			m_cls_get_bookinfo_using_db.Print();		//test
		}
	}
	else
	{
		printf("Search From DB\n");
	}

	return info;
}

///
