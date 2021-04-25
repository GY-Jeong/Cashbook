#pragma once

#include "Pay.h"

class Income
	:public cashData
{
private:
	vector<string> income_category = { "����","�뵷","�μ�Ƽ��","�Ƹ�����Ʈ","��Ÿ" };
	string keyword;
	vector<string> result;
	string user_id = "user_id";
	string data_format;

public:
	Income();
	bool income_category_test(string& data);
	void printcategory_err();
	string printdata(vector<string> input);
};