#include "CashBook.h"
#include "CashData.h"
#include "Pay.h"
#include "Income.h"
#include "Check.hpp"

#include <stdlib.h>
#include <ctime>

#pragma warning(disable:4996)

using namespace std;

vector<string> split(string str, char delimiter);
int get_difference_of_dates(string start_date, string end_date);

// 조회할 기간을 입력, 입력한 날짜들이 조건에 맞는지 확인.
void Cashbook::inputTerm(string user_id)
{
	string input;
	cout << "조회할 기간을 입력해주세요(최대 30일)" << endl;
InputRetry:
	cin >> input;
	if (validQCheck(input))
	{
		// 뒤로 가기
		return;
	}
	else
	{
		vector<string> dates = split(input, '/');
		// '/'로 구분된 string이 2개이고, 2개의 string 모두 유효한 날짜 데이터일 때
		if (dates.size() == 2 && validDateCheck(dates[0]) && validDateCheck(dates[1]))
		{
			// 의미규칙, 30일 사이이고, dates[1]이 dates[0]보다 뒤일때)
			int difference_of_dates = get_difference_of_dates(dates[0], dates[1]);
			cout << "두 날짜의 차이 : " << difference_of_dates << endl;
			if (difference_of_dates >= 0 && difference_of_dates <= 30)
			{
				showTotal(user_id, dates[0], dates[1]);
				return;
			}
			else goto InputError;
		}
		// 오류 출력
		else
		{
		InputError:
			cout << "입력 형식 오류" << endl;
			//이렇게 하면 오류메시지 안쌓일텐데 여기서 console clear해주면
			goto InputRetry;
		}
	}
}

// 총 수입과 지출을 보여줌.
void Cashbook::showTotal(string user_id, string start_date, string end_date)
{
	unsigned int input, total_income_price = 0, total_pay_price = 0;
	vector<Income> IncomeList;
	vector<Pay> PayList;

	// start date부터 end date까지 순회하며 리스트에 저장
	cout << "사용자 ID : " << user_id << endl;
	cout << start_date << " ~ " << end_date << " 해당 기간 내역입니다." << endl;
	cout << "총 지출 : " << total_pay_price << " 총 수입 : " << total_income_price << endl;
	cout << "1. 수입" << endl;
	cout << "2. 지출" << endl;
	cout << "3. 뒤로가기" << endl;
	cout << "조회하실 카테고리 유형을 선택해주세요." << endl;
InputRetry:
	cin >> input;
	switch (input) {
	case 1:
		searchIncomeCategory(user_id, start_date, end_date, IncomeList);
		break;
	case 2:
		searchPayCategory(user_id, start_date, end_date, PayList);
		break;
	case 3:
		inputTerm(user_id);
		break;
	default:
		cout << "입력 형식 오류" << endl;
		goto InputRetry;
	}
}

// 수입 카테고리별 수입을 보여줌.
void Cashbook::searchIncomeCategory(string user_id, string start_date, string end_date, vector<Income> IncomeList)
{
	string input;
	unsigned int income_total_money = 0, category;
	unsigned int category_income_total_money[5] = { 0, };
	vector<Income> category_incomelist[5];
	for (Income element : IncomeList)
	{
		//category = element의 카테고리 element.category
		//category_income_total_money[category] += element.m_price
		//categoty_incomelist[category].push_back(element)
		//income_total_money += element.m_price
	}
	cout << "사용자 ID : " << user_id << endl;
	cout << start_date << " ~ " << end_date << " 해당 기간 내역입니다." << endl;
	cout << "총 수입       " << income_total_money << "원" << endl;
	string printlist[5] = { "1. 월급       " , "2. 용돈       " , "3. 인센티브   " ,\
		"4. 아르바이트 " , "5. 기타(수입) " };
	for (int i = 0; i < 5; i++)
	{
		cout << printlist[i] << category_income_total_money[i] << "원" << endl;
	}
	cout << "상세 내역을 확인하시려면 카테고리 번호를 선택해주세요." << endl;
SelectCategoryNumRetry:
	cin >> input;
	if (validQCheck(input))
	{
		showTotal(user_id, start_date, end_date);
	}
	else if (validNumberRange(input, 1, 5))
	{
		vector<string> income_category = { "월급","용돈","인센티브","아르바이트","기타(수입)" };
		searchDetail(income_category[stoi(input) - 1], category_incomelist[stoi(input) - 1], {}, false);
	}
	else
	{
		cout << "입력 형식 오류" << endl;
		goto SelectCategoryNumRetry;
	}
	return;
}

// 지출 카테고리별 지출을 보여줌.
void Cashbook::searchPayCategory(string user_id, string start_date, string end_date, vector<Pay> PayList)
{
	string input;
	unsigned int pay_total_money = 0, category;
	unsigned int category_pay_total_money[7] = { 0, };
	vector<Pay> category_paylist[7];
	for (Pay element : PayList)
	{
		//category = element의 카테고리
		//category_pay_total_money[category] += element.m_price
		//category_paylist[category].push_back(element)
		//pay_total_money += element.m_price
	}
	cout << "사용자 ID : " << user_id << endl;
	cout << start_date << " ~ " << end_date << " 해당 기간 내역입니다." << endl;
	cout << "총 지출       " << pay_total_money << "원" << endl;
	string printlist[7] = { "1. 식비       " , "2. 교통       " , "3. 문화       " ,\
		"4. 오락       ", "5. 편의점     ", "6. 카페       ",  "7. 기타(지출) " };
	for (int i = 0; i < 7;i++)
	{
		cout << printlist[i] << category_pay_total_money[i] << "원" << endl;
	}
	cout << "상세 내역을 확인하시려면 카테고리 번호를 선택해주세요." << endl;
SelectCategoryNumRetry:
	cin >> input;

	if (validQCheck(input))
	{
		showTotal(user_id, start_date, end_date);
	}
	else if (validNumberRange(input, 1, 7))
	{
		vector<string> pay_category = { "식비", "교통", "문화", "오락", "편의점", "카페", "기타(지출)" };
		searchDetail(pay_category[stoi(input) - 1], {}, category_paylist[stoi(input) - 1], true);
		return;
	}
	else
	{
		cout << "입력 형식 오류" << endl;
		goto SelectCategoryNumRetry;
	}
	return;
}

// 입력 받은 '상세 내역을 조회할 카테고리'의 상세 내역을 보여줌.
void Cashbook::searchDetail(string categoty_name, vector<Income> category_incomelist, vector<Pay> category_paylist, bool is_pay)
{
	cout << categoty_name << "의 상세 내역입니다." << endl;
	if (is_pay)
	{
		for (Pay element : category_paylist)
		{
			//cout << element.m_date << " " << element.m_price << " " << element.m_memo << endl;
		}
	}
	else
	{
		for (Income element : category_incomelist)
		{
			//cout << element.m_date << " " << element.m_price << " " << element.m_memo << endl;
		}
	}
	cout << "메인 메뉴로 돌아가시겠습니까? (Y/N or y/n)";
	string input;
SelectYNRetry:
	cin >> input;
	if (input == "y" or input == "Y")
	{
		// 메인 메뉴로
		return;
	}
	else if (input == "n" or input == "N")
	{
		if (is_pay)
		{
			//parameter 넣기가 빡센데?
			//searchPayCategory();
			cout << "searchPayCategory()" << endl;
		}
		else
		{
			//parameter 넣기가 빡센데?
			//searchIncomeCategory(,);
			cout << "searchIncomeCategory()" << endl;
		}
		return;
	}
	else
	{
		cout << "입력 형식 오류" << endl;
		goto SelectYNRetry;
	}
}

// 공용 가계부 삭제
void Cashbook::deletePublicCashbook(string txt_name)
{
	cashData yn;
	cout << "삭제 하시겠습니까? (Y/N or y/n)" << endl;
	if (yn.yesorno()) {	//y를 누른 경우 yesorno()가 true
		// 현재 공유 가계부 삭제
		char* c_txt_name = new char[txt_name.length() + 1];		// string을 char * 으로 변경
		strcpy(c_txt_name, txt_name.c_str());

		if (remove(c_txt_name) == 0) {							// 삭제할 공유 가계부 경로
			cout << "공유 가계부를 삭제했습니다." << endl;
			cout << "2초 후 공유 가계부 선택 화면으로 돌아갑니다." << endl;

			Sleep(2000);
			// 삭제 후 공유 가계부 선택 화면으로 돌아가기
		}
		else {
			// 가계부 파일을 삭제하지 못한 상황
		}
	}
	else {					// n을 누른 경우 yesorno()가 false
		// 공유 가계부 메뉴 선택으로 돌아감
		cout << "2초 후 개인 및 공유 가계부 화면으로 돌아갑니다." << endl;

		Sleep(2000);
	}
}

vector<string> split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str);
	string temp;

	while (getline(ss, temp, delimiter)) {
		internal.push_back(temp);
	}

	return internal;
}

int get_difference_of_dates(string start_date, string end_date)
{
	time_t start, end;
	struct tm stime, etime;
	int tm_day;
	int s_year, s_month, s_day, e_year, e_month, e_day;

	vector<string> start_date_list = split(start_date, '-');

	if (start_date_list[0].size() == 2)
	{
		//YY-MM-DD
		s_year = stoi(start_date_list[0]);
		if (s_year <= 99 && s_year >= 70)
			s_year += 1900;
		else if (s_year <= 69 && s_year >= 0)
			s_year += 2000;
	}
	else
	{
		s_year = stoi(start_date_list[0]);
	}

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

	if (end_date_list[0].size() == 2)
	{
		//YY-MM-DD
		e_year = stoi(end_date_list[0]);
		if (e_year <= 99 && e_year >= 70)
			e_year += 1900;
		else if (e_year <= 69 && e_year >= 0)
			e_year += 2000;
	}
	else
	{
		e_year = stoi(end_date_list[0]);
	}

	e_month = stoi(end_date_list[1]);
	e_day = stoi(end_date_list[2]);

	etime.tm_year = e_year - 1900;
	etime.tm_mon = e_month - 1;
	etime.tm_mday = e_day;
	etime.tm_hour = 0;
	etime.tm_min = 0;
	etime.tm_sec = 0;
	etime.tm_isdst = 0; //썸머타임 사용안함

	printf("%d %d %d %d %d %d\n", s_year, s_month, s_day, e_year, e_month, e_day);
	start = mktime(&stime);
	end = mktime(&etime);

	double diff = difftime(end, start);
	cout << diff << endl;
	tm_day = diff / (60.0f * 60.0f * 24.0f);

	return tm_day;
}