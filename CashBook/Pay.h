#pragma once
#include "cashData.h"

class Pay
	:public cashData
{
private:
	vector<string>pay_category = { "�ĺ�","����","��ȭ","����","������","��Ÿ" };
	string keyword;
	vector<string> result;
	string user_id = "user_id";
	string data_format;

public:
	Pay();//user_id �Ű�����
	bool pay_category_test(string data);


	void printcategory_err();
	string printdata(vector<string> input);

};
#pragma once
