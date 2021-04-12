#include "Check.hpp"

using namespace std;

bool validDateCheck(string input)
{
	return true;
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

bool ValidDateCheck(string data)
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

bool isLeapyear(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		return true;
	return false;
}

void printdate_err()
{
	cout << "날짜 형식 오류 " << endl;
}