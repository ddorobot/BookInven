#include "CCheckString.h"



CCheckString::CCheckString()
{
}


CCheckString::~CCheckString()
{
}

bool CCheckString::CheckString(const std::string str_data)
{
	bool check_data = false;

	//name
	std::string str_check = str_data;
	int str_len = str_check.length();
	int   ch;
	for (int ndx = 0; ndx < str_len; ndx++)
	{
		ch = str_check.at(ndx);

		if (isspace(ch) == false)		//������ �ƴ� � ���ڰ� �ִ��� üũ
		{
			check_data = true;
			break;
		}
	}

	return check_data;
}