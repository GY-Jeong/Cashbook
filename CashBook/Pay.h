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
	string data_format;

public:
	Pay();//user_id 매개변수
	Pay(string date, string price, string category, string memo);
	bool pay_category_test(string data);


	void printcategory_err();
	string printdata(vector<string> input);

};
#pragma once
