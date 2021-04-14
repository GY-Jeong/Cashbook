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
	string m_date;
	string m_price;
	string m_memo;
	vector<string> file_data;
	//User current_user;
	//CashBook current_cashbook;

public:
	bool isSharedCashBook;
	bool isDataSetting;
	cashData();
	void menu(bool flag);
	vector<string> data_split1();
	vector<string> data_split2();
	bool date_test(string& data);
	bool price_test(string& data);
	bool memo_test(string data);
	bool date_validation(string& startdate, string& enddate);
	bool keyword_search(string startdate, string enddate, string data);

	bool is3digit(string data);
	void printdate_err();
	void printprice_err();
	void printmemo_err();

	void readTextFile(string txt_name); //파일 읽어오기
	void writeTextFile(string txt_name, string data); //파일 내용 추가시 사용
	void reWriteTextFile(string txt_name); //파일 수정시 사용

	bool yesorno();
	bool isquit(string& data);
	vector<string> split(string str, char delimiter);
	string& trimString(string& str, string& chars);
	string& rightTrim(string& str, string& chars);
	string& leftTrim(string& str, string& chars);
};
