#include "CashData.h"
#include "Check.hpp"

using namespace std;

bool isLeapyear(int);

vector<string> split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str);
	string temp;

	while (getline(ss, temp, delimiter)) {
		internal.push_back(temp);
	}

	return internal;
}

int getIndex(vector<string> v, string K)
{
	auto it = find(v.begin(), v.end(), K);

	// If element was found
	if (it != v.end())
	{
		// calculating the index
		// of K
		int index = it - v.begin();
		return index;
	}
	else {
		// If the element is not
		// present in the vector
		return -1;
	}
}

int get_difference_of_dates(string start_date, string end_date)
{
	time_t start, end;
	struct tm stime, etime;
	int tm_day;
	int s_year, s_month, s_day, e_year, e_month, e_day;

	vector<string> start_date_list = split(start_date, '-');

	//if (start_date_list[0].size() == 2)
	//{
	//	//YY-MM-DD
	//	s_year = stoi(start_date_list[0]);
	//	if (s_year <= 99 && s_year >= 70)
	//		s_year += 1900;
	//	else if (s_year <= 69 && s_year >= 0)
	//		s_year += 2000;
	//}
	//else
	//{
	//	s_year = stoi(start_date_list[0]);
	//}

	s_year = stoi(start_date_list[0]);
	s_month = stoi(start_date_list[1]);
	s_day = stoi(start_date_list[2]);

	stime.tm_year = s_year - 1900;
	stime.tm_mon = s_month - 1;
	stime.tm_mday = s_day;
	stime.tm_hour = 0;
	stime.tm_min = 0;
	stime.tm_sec = 0;
	stime.tm_isdst = 0; //썸머타임 사용안함

	vector<string> end_date_list = split(end_date, '-');

	//if (end_date_list[0].size() == 2)
	//{
	//	//YY-MM-DD
	//	e_year = stoi(end_date_list[0]);
	//	if (e_year <= 99 && e_year >= 70)
	//		e_year += 1900;
	//	else if (e_year <= 69 && e_year >= 0)
	//		e_year += 2000;
	//}
	//else
	//{
	//	e_year = stoi(end_date_list[0]);
	//}

	e_year = stoi(end_date_list[0]);
	e_month = stoi(end_date_list[1]);
	e_day = stoi(end_date_list[2]);

	etime.tm_year = e_year - 1900;
	etime.tm_mon = e_month - 1;
	etime.tm_mday = e_day;
	etime.tm_hour = 0;
	etime.tm_min = 0;
	etime.tm_sec = 0;
	etime.tm_isdst = 0; //썸머타임 사용안함

	//printf("%d %d %d %d %d %d\n", s_year, s_month, s_day, e_year, e_month, e_day);
	start = mktime(&stime);
	end = mktime(&etime);

	double diff = difftime(end, start);
	// cout << diff << endl;
	tm_day = diff / double(86400);

	return tm_day;
}

bool validQCheck(string input)
{
	return input == "q";
}

bool validNumberRange(string number, int start, int end)
{
	if (number.size() == 1 && isdigit(number[0]))
	{
		int number2int = stoi(number);
		return number2int >= start && number2int <= end;
	}
	return false;
}

bool validDateCheck(string data)
{
	int year = 0, month = 0, day = 0;
	cout << "date testing ";
	regex ex1("(\\d{2})-(\\d{2})-(\\d{2})");
	regex ex2("(\\d{4})-(\\d{2})-(\\d{2})");
	smatch matches;

	if (regex_match(data, matches, ex1)) {
		//연도 2자리 매칭
		year = stoi(matches[1]);
		month = stoi(matches[2]);
		day = stoi(matches[3]);
		if (year <= 99 && year >= 70)
			year += 1900;
		else if (year <= 69 && year >= 0)
			year += 2000;
		else {
			printdate_err();
			return false;
		}
		data = to_string(year) + "-" + (string)matches[2] + "-" + (string)matches[3];
	}
	else if (regex_match(data, matches, ex2)) {
		//연도 4자리 매칭
		year = stoi(matches[1]);
		if (year == 0) {
			printdate_err();
			return false;
		}
		else if (year < 1900 || year > 2100) {
			printdate_err();
			return false;
		}
		month = stoi(matches[2]);
		day = stoi(matches[3]);
	}
	else {
		cout << "date matching fail" << endl;
		printdate_err();
		return false;
	}

	//기본 날짜 검사
	if (month <= 0 || month > 12) {
		printdate_err();
		return false;
	}
	if (day <= 0 || day > 31) {
		printdate_err();
		return false;
	}

	//정규식 통과 후 윤년검사
	switch (month)
	{
	case 4:
	case 6:
	case 9:
	case 11:
		if (day == 31) {
			printdate_err();
			return false;
		}
		break;
	case 2:
		if (isLeapyear(year)) {//윤년이면
			if (day == 30 || day == 31) {
				printdate_err();
				return false;
			}
		}
		else {//윤년이 아니면 
			if (day == 29 || day == 30 || day == 31) {
				printdate_err();
				return false;
			}
		}
		break;
	default:
		break;
	}
	//result = to_string(year) + "-" + (string)matches[2] + "-" + (string)matches[3];
	//cout << "result " << result << endl;
	return true;
}

void printdate_err()
{
	cout << "날짜 형식 오류 " << endl;
}

