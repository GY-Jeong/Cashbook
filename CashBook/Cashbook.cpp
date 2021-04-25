#include "CashBook.h"
#include "CashData.h"
#include "Pay.h"
#include "Income.h"
#include "Check.hpp"
#include "Admin.h"

#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <io.h>
#include <string>

#pragma warning(disable:4996)
#define CLEAR system("cls")
#define INPUT cout << "> "

using namespace std;

vector<string> split(string str, char delimiter);
int get_difference_of_dates(string start_date, string end_date);
int getIndex(vector<string> v, string K);

Cashbook::Cashbook(string user_id, string cashbook_name, bool isSharedCashBook)
{
	this->isSharedCashBook = isSharedCashBook;
	this->user_id = user_id;
	this->cashbook_name = cashbook_name;
	this->user_authority = getAuthority(cashbook_name, user_id);

	cd.isSharedCashBook = isSharedCashBook;
	if (isSharedCashBook)
		cd.txt_file = "./data/public/" + cashbook_name + ".txt";
	else
		cd.txt_file = "./data/private/" + user_id + ".txt";
	cd.readTextFile(cd.txt_file);

	//cashdata setting
	menu();
}

void Cashbook::menu()
{
	string select;
	if (!isSharedCashBook) { // false - 개인 가계부
		while (1)
		{
			CLEAR;
			//user_id 출력
			//cashbook_name 출력
			cd.isDataSetting = false;
			cout << "사용자 ID: " << user_id << endl;
			cout << "1. 소비" << endl;
			cout << "2. 수입" << endl;
			cout << "3. 조회" << endl;
			cout << "4. 뒤로가기" << endl;
		InputRetry:
			INPUT;
			cin >> select;
			if (validNumberRange(select, 1, 4))
			{
				switch (stoi(select)) {
				case 1:
				{
					CLEAR;
					Pay* pay = new Pay(isSharedCashBook, user_id, cashbook_name, cd.txt_file);//user.id 생성자로 넘겨줘야함
					break;
				}
				case 2:
				{
					CLEAR;
					Income* income = new Income(isSharedCashBook, user_id, cashbook_name, cd.txt_file);
					break;
				}
				case 3:
				{
					startSearch();
					break;
				}
				case 4:
					return;
				default:
				{
					cout << "여기 들어오면 validcheck에서 문제있는거" << endl;
					break;
				}
				}
			}
			else
			{
				cout << "다시 입력해주세요" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				goto InputRetry;
			}
		}
	}
	else { // true - 공용 가계부
		while (1)
		{
			CLEAR;
			//user_id 출력
			cout << "사용자 ID: " << user_id << endl;
			//cashbook_name 출력
			cout << "가계부 이름: " << cashbook_name << endl;
			cout << "0. 관리자 설정" << endl;
			cout << "1. 소비" << endl;
			cout << "2. 수입" << endl;
			cout << "3. 조회" << endl;
			cout << "4. 가계부 삭제" << endl;
			cout << "5. 뒤로가기" << endl;
		InputRetry_public:
			INPUT;
			cin >> select;
			if (validNumberRange(select, 0, 5))
			{
				//오류처리 필요 "a"
				//권한에 따라 들어갈 수 있는 권한 설정
				switch (stoi(select)) {
				case 0:
				{
					if (user_authority != 0) {
						cout << "해당 권한이 없습니다." << endl;
						cout << "1.5초 뒤 공유 가계부 화면으로 돌아갑니다." << endl;
						Sleep(1500);
						break;			//공유 가계부 화면으로 복귀
					}
					else {
						//cout << "공유 가계부 관리자 설정" << endl;
						Admin* admin = new Admin(user_id, cashbook_name);
						break;
					}
				}
				case 1:
				{
					CLEAR;
					if (user_authority == 2) {
						cout << "해당 권한이 없습니다." << endl;
						cout << "1.5초 뒤 공유 가계부 화면으로 돌아갑니다." << endl;
						Sleep(1500);
						break;			//공유 가계부 화면으로 복귀
					}
					else {
						Pay* pay = new Pay(isSharedCashBook, user_id, cashbook_name, cd.txt_file);
						break;
					}
				}
				case 2:
				{
					CLEAR;
					if (user_authority == 2) {
						cout << "해당 권한이 없습니다." << endl;
						cout << "1.5초 뒤 공유 가계부 화면으로 돌아갑니다." << endl;
						Sleep(1500);
						break;			//공유 가계부 화면으로 복귀
					}
					else {
						Income* income = new Income(isSharedCashBook, user_id, cashbook_name, cd.txt_file);
						break;
					}
				}
				case 3:
				{
					startSearch();
					break;
				}
				case 4:
				{
					if (user_authority != 0) {
						cout << "해당 권한이 없습니다." << endl;
						cout << "1.5초 뒤 공유 가계부 화면으로 돌아갑니다." << endl;
						Sleep(1500);
						break;			//공유 가계부 화면으로 복귀
					}
					else {
						bool check = deletePublicCashbook();
						if (check) return;
						// 소멸자 호출하는게 낫나?
						break;
					}
				}
				case 5:
				{
					return;
				}
				default:
				{
					cout << "여기 들어오면 validcheck에서 문제있는거" << endl;
					break;
				}
				}
			}
			else
			{
				cout << "다시 입력해주세요" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				goto InputRetry_public;
			}
		}
	}
}

// 조회할 기간을 입력, 입력한 날짜들이 조건에 맞는지 확인.
void Cashbook::startSearch()
{
	cd.readTextFile(cd.txt_file);
	CLEAR;
	string input;
	cout << "조회할 기간을 입력해주세요(최대 30일)" << endl;

InputRetry:
	INPUT;
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
			string start_year = split(dates[0], '-')[0];
			string end_year = split(dates[1], '-')[0];

			if (start_year.size() == 2)
			{
				int s_year = stoi(start_year);
				if (s_year <= 99 && s_year >= 70)
					dates[0] = "19" + dates[0];
				else if (s_year <= 69 && s_year >= 0)
					dates[0] = "20" + dates[0];
			}

			if (end_year.size() == 2)
			{
				int e_year = stoi(end_year);
				if (e_year <= 99 && e_year >= 70)
					dates[1] = "19" + dates[1];
				else if (e_year <= 69 && e_year >= 0)
					dates[1] = "20" + dates[1];
			}

			// 의미규칙, 30일 사이이고, dates[1]이 dates[0]보다 뒤일때)
			int difference_of_dates = get_difference_of_dates(dates[0], dates[1]);
			// cout << "두 날짜의 차이 : " << difference_of_dates << endl;
			if (difference_of_dates >= 0 && difference_of_dates <= 30)
			{
				showTotal(dates[0], dates[1]);
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
void Cashbook::showTotal(string start_date, string end_date)
{
	CLEAR;
	unsigned int input, total_income_price = 0, total_pay_price = 0;
	vector<vector<string>> income_list;
	vector<vector<string>> pay_list;
	vector<string> temp;
	// 날짜, 금액, 카테고리, 메모 순서
	for (string pay_string : cd.pay_file_data)
	{
		temp = split(pay_string, '/');
		if (get_difference_of_dates(start_date, temp[0]) >= 0 && get_difference_of_dates(end_date, temp[0]) <= 0) {
			if (temp[3] == "*") temp[3] = "";
			pay_list.push_back(temp);
			total_pay_price += stoi(temp[1]);
		}
		temp.clear();
	}

	for (string income_string : cd.income_file_data)
	{
		temp = split(income_string, '/');
		if (get_difference_of_dates(start_date, temp[0]) >= 0 && get_difference_of_dates(end_date, temp[0]) <= 0) {
			temp[2] = cd.remove_mark(temp[2]);
			if (temp[3] == "*") temp[3] = "";
			income_list.push_back(temp);
			total_income_price += stoi(temp[1]);
		}
		temp.clear();
	}

	cout << "사용자 ID : " << user_id << endl;
	cout << start_date << " ~ " << end_date << " 해당 기간 내역입니다." << endl;
	cout << "총 수입 : " << total_income_price << "원" << endl;
	cout << "총 지출 : " << total_pay_price << "원" << endl;
	cout << "1. 수입" << endl;
	cout << "2. 지출" << endl;
	cout << "3. 뒤로가기" << endl;
	cout << "조회하실 카테고리 유형을 선택해주세요." << endl;

InputRetry:
	INPUT;
	cin >> input;
	switch (input) {
	case 1:
		searchIncomeCategory(start_date, end_date, income_list);
		break;
	case 2:
		searchPayCategory(start_date, end_date, pay_list);
		break;
	case 3:
		startSearch();
		break;
	default:
		cout << "입력 형식 오류" << endl;
		//여기서 숫자가 아닌 알파벳이 입력되면 계속 "입력 형식 오류"가 떠서 추가한 내용이에요!
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		goto InputRetry;
	}
}

// 수입 카테고리별 수입을 보여줌.
void Cashbook::searchIncomeCategory(string start_date, string end_date, vector<vector<string>> income_list)
{
	CLEAR;
	string input;
	unsigned int income_total_money = 0, category;
	unsigned int category_income_total_money[5] = { 0, };
	vector<vector<string>> category_incomelist[5];
	vector<string> income_category = { "월급","용돈","인센티브","아르바이트","기타" };

	for (vector<string> element : income_list)
	{
		category = getIndex(income_category, element[2]);
		category_income_total_money[category] += stoi(element[1]);
		category_incomelist[category].push_back(element);
		income_total_money += stoi(element[1]);
	}
	//cout << "사용자 ID : " << user_id << endl;
	cout << start_date << " ~ " << end_date << " 해당 기간 수입 내역입니다." << endl;
	cout << "총 수입       " << income_total_money << "원" << endl;
	string printlist[5] = { "1. 월급       " , "2. 용돈       " , "3. 인센티브   " ,\
		"4. 아르바이트 " , "5. 기타       " };
	for (int i = 0; i < 5; i++)
	{
		if(income_total_money != 0)
			cout << printlist[i] << category_income_total_money[i] << "원 (" << int(double(category_income_total_money[i]) / double(income_total_money) * 100) << "%)" << endl;
		else
			cout << printlist[i] << category_income_total_money[i] << "원 (0%)" << endl;
	}
	cout << "상세 내역을 확인하시려면 카테고리 번호를 선택해주세요." << endl;

SelectCategoryNumRetry:
	INPUT;
	cin >> input;
	if (validQCheck(input))
	{
		showTotal(start_date, end_date);
	}
	else if (validNumberRange(input, 1, 5))
	{
		searchDetail(start_date, end_date, income_category[stoi(input) - 1], category_incomelist[stoi(input) - 1], income_list, false);
	}
	else
	{
		cout << "입력 형식 오류" << endl;
		goto SelectCategoryNumRetry;
	}
	return;
}

// 지출 카테고리별 지출을 보여줌.
void Cashbook::searchPayCategory(string start_date, string end_date, vector<vector<string>> pay_list)
{
	CLEAR;
	string input;
	unsigned int pay_total_money = 0, category;
	unsigned int category_pay_total_money[7] = { 0, };
	vector<vector<string>> category_paylist[7];
	vector<string> pay_category = { "식비", "교통", "문화", "오락", "편의점", "카페", "기타" };

	for (vector<string> element : pay_list)
	{
		category = getIndex(pay_category, element[2]);
		category_pay_total_money[category] += stoi(element[1]);
		category_paylist[category].push_back(element);
		pay_total_money += stoi(element[1]);
	}
	//cout << "사용자 ID : " << user_id << endl;
	cout << start_date << " ~ " << end_date << " 해당 기간 지출 내역입니다." << endl;
	cout << "총 지출       " << pay_total_money << "원" << endl;
	string printlist[7] = { "1. 식비       " , "2. 교통       " , "3. 문화       " ,\
		"4. 오락       ", "5. 편의점     ", "6. 카페       ",  "7. 기타       " };
	for (int i = 0; i < 7;i++)
	{
		cout << printlist[i] << category_pay_total_money[i] << "원 (" << int(double(category_pay_total_money[i]) / double(pay_total_money) * 100) << "%)" << endl;
	}
	cout << "상세 내역을 확인하시려면 카테고리 번호를 선택해주세요." << endl;
SelectCategoryNumRetry:
	INPUT;
	cin >> input;

	if (validQCheck(input))
	{
		showTotal(start_date, end_date);
	}
	else if (validNumberRange(input, 1, 7))
	{
		searchDetail(start_date, end_date, pay_category[stoi(input) - 1], category_paylist[stoi(input) - 1], pay_list, true);
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
void Cashbook::searchDetail(string start_date, string end_date, string categoty_name, vector<vector<string>> category_list, \
	vector<vector<string>> total_list, bool is_pay) {
	CLEAR;
	cout << categoty_name << "의 상세 내역입니다." << endl;
	for (vector<string> element : category_list)
	{
		for (int i = 0; i < 4; i++) {
			// 만약 공유 가계부라면 올린 사람도 올려야됨
			// 공유일때만 i==4 (올린 사람) 내역 출력, 이 부분 테스트 필요
			if (!isSharedCashBook && i == 3) continue;
			if (i == 2) continue;
			cout << element[i] << "\t";
		}
		cout << endl;
	}
	cout << "메인 메뉴로 돌아가시겠습니까? (Y/N or y/n)" << endl;
	string input;
SelectYNRetry:
	INPUT;
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
			searchPayCategory(start_date, end_date, total_list);
		}
		else
		{
			searchIncomeCategory(start_date, end_date, total_list);
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
bool Cashbook::deletePublicCashbook()
{
	string txt_name = "./data/public/" + cashbook_name + ".txt";
	string M_txt_name = "./data/public/" + cashbook_name + "_M.txt";

	CLEAR;
	string input;
	cout << "삭제 하시겠습니까? (Y/N or y/n)" << endl;
SelectYNRetry_delete:
	INPUT;
	cin >> input;

	if (input == "y" or input == "Y") {
		// 현재 공유 가계부 삭제
		char* c_txt_name = new char[txt_name.length() + 1];		// string을 char * 으로 변경
		strcpy(c_txt_name, txt_name.c_str());

		char* c_M_txt_name = new char[M_txt_name.length() + 1];		// string을 char * 으로 변경
		strcpy(c_M_txt_name, M_txt_name.c_str());

		bool check = true;

		if (access(c_txt_name, 00) == -1)
		{
			cout << c_txt_name << "이 존재하지 않음" << endl;
		}
		else
		{
			if (remove(c_txt_name) == 0) {							// 삭제할 공유 가계부 경로
				cout << c_txt_name << "삭제 성공" << endl;
			}
			else {
				// 가계부 파일을 삭제하지 못한 상황
				cout << c_txt_name << "삭제 실패" << endl;
			}
		}

		if (access(c_M_txt_name, 00) == -1)
		{
			cout << c_M_txt_name << "이 존재하지 않음" << endl;
		}
		else
		{
			if (remove(c_M_txt_name) == 0) {							// 삭제할 공유 가계부 경로
				cout << c_M_txt_name << "삭제 성공" << endl;
			}
			else {
				// 가계부 파일을 삭제하지 못한 상황
				cout << c_M_txt_name << "삭제 실패" << endl;
			}
		}

		//hidden 읽어와서 해당 line 삭제 필요
		modify_hidden_file();

		cout << "공유 가계부를 삭제했습니다." << endl;
		cout << "2초 후 공유 가계부 선택 화면으로 돌아갑니다." << endl;
		Sleep(2000);
		return true;
		// 삭제 후 공유 가계부 선택 화면으로 돌아가기
	}
	else if (input == "n" or input == "N") {
		// 공유 가계부 메뉴 선택으로 돌아감
		cout << "2초 후 개인 및 공유 가계부 화면으로 돌아갑니다." << endl;
		Sleep(2000);
		return false;
	}
	else
	{
		cout << "입력 형식 오류" << endl;
		goto SelectYNRetry_delete;
	}
}

void Cashbook::modify_hidden_file()
{
	vector<string> writelist;
	ifstream search_file;	
	string line;
	string txt_name = "./data/makehiddenfile.txt";
	search_file.open(txt_name);
	if (search_file.is_open() == true) {
		while (!search_file.eof()) {
			getline(search_file, line);
			cout << line << endl;
			if (line != "" && split(line, '/')[0] == cashbook_name) continue;
			writelist.push_back(line);
		}
	}
	search_file.close();

	// 파일에 쓰면됨
	ofstream writeFile(txt_name.data());
	if (writeFile.is_open()) {
		for (string element : writelist)
		{
			cout << element << endl;
			writeFile << element << "\n";
		}
	}
	writeFile.close();
	return;
}

int Cashbook::getAuthority(string cashbook_name, string user_id)
{
	int user_authority = 0;

	string txtName = "./data/public/" + cashbook_name + "_M.txt";
	ifstream ifile;
	char line[15];

	ifile.open(txtName);
	if (ifile.is_open())
	{
		while (ifile.getline(line, sizeof(line)))
		{
			vector<string> data = split(line, '/');

			if (data[0] == user_id)
				user_authority = stoi(data[1]);
		}
	}
	return user_authority;
}
		