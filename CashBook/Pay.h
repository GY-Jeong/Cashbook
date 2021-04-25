#pragma once

#include "cashData.h"

class Pay
	:public cashData
{
private:
	vector<string>pay_category = { "식비","교통","문화","오락","편의점","기타" };
	string keyword;
	vector<string> result;
	string user_id = "user_id";
	string cashbook_name = "";
	string data_format;

public:
	Pay(bool isShared, string user_id, string cashbook_name, string txt_file);//user_id 매개변수
	bool pay_category_test(string data);
	void printcategory_err();
	string printdata(vector<string> input);
};
#pragma once
