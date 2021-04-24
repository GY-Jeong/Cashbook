#pragma once

#include <cstring>
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>
#include <ctype.h>
#include <fstream>
#include <Windows.h>
#include <tchar.h>

using namespace std;

class cashData
{
private:
	//User current_user;
	//CashBook current_cashbook;

public:
	string m_date;
	string m_price;
	string m_memo;
	string m_category;
	vector<string> file_data;
	bool isSharedCashBook;
	bool isDataSetting;
	vector<string> pay_file_data;
	vector<string> income_file_data;
	cashData();
	vector<string> data_split1();
	vector<string> data_split2();
	bool date_test(string& data);
	bool price_test(string& data);
	bool memo_test(string data);
	bool date_validation(string& startdate, string& enddate);
	bool keyword_search(string startdate, string enddate, string data, bool search_what);

	bool is3digit(string data);
	void printdate_err();
	void printprice_err();
	void printmemo_err();

	void readTextFile(string txt_name); //파일 읽어오기
	void writeTextFile(string txt_name, string data); //파일 내용 추가시 사용
	void reWriteTextFile(string txt_name); //파일 수정시 사용
	string remove_mark(string data);

	bool yesorno();
	bool isquit(string& data);
	vector<string> split(string str, char delimiter);
	string& trimString(string& str, string& chars);
	string& rightTrim(string& str, string& chars);
	string& leftTrim(string& str, string& chars);
};
