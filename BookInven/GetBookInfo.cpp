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

					//»èÁ¦
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

	info = m_cls_get_bookinfo_using_url.Run(isbn);

	return info;
}

///
