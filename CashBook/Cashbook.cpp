#include "CashBook.h"
#include "CashData.h"
#include "Pay.h"
#include "Income.h"
#include "Check.hpp"
#include "Admin.h"

#include <stdlib.h>
#include <ctime>

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
	
	//cd = cashData();
	cd.isSharedCashBook = isSharedCashBook;

	//cashdata setting

	menu();
}

void Cashbook::menu()
{
	string select;
	if (!isSharedCashBook) { // false - ���� �����
		while (1)
		{
			CLEAR;
			//user_id ���
			//cashbook_name ���
			cd.isDataSetting = false;
			cout << "����� ID: " << user_id << endl;
			cout << "1. �Һ�" << endl;
			cout << "2. ����" << endl;
			cout << "3. ��ȸ" << endl;
			cout << "4. �ڷΰ���" << endl;
		InputRetry:
			INPUT;
			cin >> select;
			if (validNumberRange(select, 1, 4))
			{
				switch (stoi(select)) {
				case 1:
				{
					CLEAR;
					Pay* pay = new Pay();//user.id �����ڷ� �Ѱ������
					break;
				}
				case 2:
				{
					CLEAR;
					Income* income = new Income();
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
					cout << "���� ������ validcheck���� �����ִ°�" << endl;
					break;
				}
				}
			}
			else
			{
				cout << "�ٽ� �Է����ּ���" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				goto InputRetry;
			}
		}
	}
	else { // true - ���� �����
		while (1)
		{
			CLEAR;
			//user_id ���
			cout << "����� ID: " << user_id << endl;
			//cashbook_name ���
			cout << "����� �̸�: " << cashbook_name << endl;
			cout << "0. ������ ����" << endl;
			cout << "1. �Һ�" << endl;
			cout << "2. ����" << endl;
			cout << "3. ��ȸ" << endl;
			cout << "4. ����� ����" << endl;
			cout << "5. �ڷΰ���" << endl;
		InputRetry_public:
			INPUT;
			cin >> select;
			if (validNumberRange(select, 0, 5))
			{
				//����ó�� �ʿ� "a"
				//���ѿ� ���� �� �� �ִ� ���� ����
				switch (stoi(select)) {
				case 0:
				{
					//cout << "���� ����� ������ ����" << endl;
					Admin* admin = new Admin(user_id);
					break;
				}
				case 1:
				{
					Pay* pay = new Pay();
					break;
				}
				case 2:
				{
					Income* income = new Income();
					break;
				}
				case 3:
				{
					startSearch();
					break;
				}
				case 4:
				{
					cout << "����� ����" << endl;
					break;
				}
				case 5:
				{
					return;
				}
				default:
				{
					cout << "���� ������ validcheck���� �����ִ°�" << endl;
					break;
				}
				}
			}
			else
			{
				cout << "�ٽ� �Է����ּ���" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				goto InputRetry_public;
			}
		}
	}
}

// ��ȸ�� �Ⱓ�� �Է�, �Է��� ��¥���� ���ǿ� �´��� Ȯ��.
void Cashbook::startSearch()
{
	CLEAR;
	string input;
	cout << "��ȸ�� �Ⱓ�� �Է����ּ���(�ִ� 30��)" << endl;

InputRetry:
	INPUT;
	cin >> input;
	if (validQCheck(input))
	{
		// �ڷ� ����
		return;
	}
	else
	{
		vector<string> dates = split(input, '/');
		// '/'�� ���е� string�� 2���̰�, 2���� string ��� ��ȿ�� ��¥ �������� ��
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

			// �ṉ̀�Ģ, 30�� �����̰�, dates[1]�� dates[0]���� ���϶�)
			int difference_of_dates = get_difference_of_dates(dates[0], dates[1]);
			// cout << "�� ��¥�� ���� : " << difference_of_dates << endl;
			if (difference_of_dates >= 0 && difference_of_dates <= 30)
			{
				showTotal(dates[0], dates[1]);
				return;
			}
			else goto InputError;
		}
		// ���� ���
		else
		{
		InputError:
			cout << "�Է� ���� ����" << endl;
			//�̷��� �ϸ� �����޽��� �Ƚ����ٵ� ���⼭ console clear���ָ�
			goto InputRetry;
		}
	}
}

// �� ���԰� ������ ������.
void Cashbook::showTotal(string start_date, string end_date)
{
	CLEAR;
	unsigned int input, total_income_price = 0, total_pay_price = 0;
	vector<vector<string>> income_list;
	vector<vector<string>> pay_list;
	vector<string> temp;
	// ��¥, �ݾ�, ī�װ�, �޸� ����
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

	cout << "����� ID : " << user_id << endl;
	cout << start_date << " ~ " << end_date << " �ش� �Ⱓ �����Դϴ�." << endl;
	cout << "�� ���� : " << total_income_price << "��" << endl;
	cout << "�� ���� : " << total_pay_price << "��" << endl;
	cout << "1. ����" << endl;
	cout << "2. ����" << endl;
	cout << "3. �ڷΰ���" << endl;
	cout << "��ȸ�Ͻ� ī�װ� ������ �������ּ���." << endl;

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
		cout << "�Է� ���� ����" << endl;
		//���⼭ ���ڰ� �ƴ� ���ĺ��� �ԷµǸ� ��� "�Է� ���� ����"�� ���� �߰��� �����̿���!
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		goto InputRetry;
	}
}

// ���� ī�װ��� ������ ������.
void Cashbook::searchIncomeCategory(string start_date, string end_date, vector<vector<string>> income_list)
{
	CLEAR;
	string input;
	unsigned int income_total_money = 0, category;
	unsigned int category_income_total_money[5] = { 0, };
	vector<vector<string>> category_incomelist[5];
	vector<string> income_category = { "����","�뵷","�μ�Ƽ��","�Ƹ�����Ʈ","��Ÿ" };

	for (vector<string> element : income_list)
	{
		category = getIndex(income_category, element[2]);
		category_income_total_money[category] += stoi(element[1]);
		category_incomelist[category].push_back(element);
		income_total_money += stoi(element[1]);
	}
	//cout << "����� ID : " << user_id << endl;
	cout << start_date << " ~ " << end_date << " �ش� �Ⱓ ���� �����Դϴ�." << endl;
	cout << "�� ����       " << income_total_money << "��" << endl;
	string printlist[5] = { "1. ����       " , "2. �뵷       " , "3. �μ�Ƽ��   " ,\
		"4. �Ƹ�����Ʈ " , "5. ��Ÿ       " };
	for (int i = 0; i < 5; i++)
	{
		cout << printlist[i] << category_income_total_money[i] << "�� (" << int(double(category_income_total_money[i])/double(income_total_money) * 100) << "%)" << endl;
	}
	cout << "�� ������ Ȯ���Ͻ÷��� ī�װ� ��ȣ�� �������ּ���." << endl;

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
		cout << "�Է� ���� ����" << endl;
		goto SelectCategoryNumRetry;
	}
	return;
}

// ���� ī�װ��� ������ ������.
void Cashbook::searchPayCategory(string start_date, string end_date, vector<vector<string>> pay_list)
{
	CLEAR;
	string input;
	unsigned int pay_total_money = 0, category;
	unsigned int category_pay_total_money[7] = { 0, };
	vector<vector<string>> category_paylist[7];
	vector<string> pay_category = { "�ĺ�", "����", "��ȭ", "����", "������", "ī��", "��Ÿ" };

	for (vector<string> element : pay_list)
	{
		category = getIndex(pay_category, element[2]);
		category_pay_total_money[category] += stoi(element[1]);
		category_paylist[category].push_back(element);
		pay_total_money += stoi(element[1]);
	}
	//cout << "����� ID : " << user_id << endl;
	cout << start_date << " ~ " << end_date << " �ش� �Ⱓ ���� �����Դϴ�." << endl;
	cout << "�� ����       " << pay_total_money << "��" << endl;
	string printlist[7] = { "1. �ĺ�       " , "2. ����       " , "3. ��ȭ       " ,\
		"4. ����       ", "5. ������     ", "6. ī��       ",  "7. ��Ÿ       " };
	for (int i = 0; i < 7;i++)
	{
		cout << printlist[i] << category_pay_total_money[i] << "�� (" << int(double(category_pay_total_money[i]) / double(pay_total_money) * 100) << "%)" << endl;
	}
	cout << "�� ������ Ȯ���Ͻ÷��� ī�װ� ��ȣ�� �������ּ���." << endl;
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
		cout << "�Է� ���� ����" << endl;
		goto SelectCategoryNumRetry;
	}
	return;
}

// �Է� ���� '�� ������ ��ȸ�� ī�װ�'�� �� ������ ������.
void Cashbook::searchDetail(string start_date, string end_date, string categoty_name, vector<vector<string>> category_list, \
	vector<vector<string>> total_list, bool is_pay) {
	CLEAR;
	// ���� ���� ����ζ�� �ø� ����� �÷��ߵ�
	//if(isSharedCashBook)
	cout << categoty_name << "�� �� �����Դϴ�." << endl;
	for (vector<string> element : category_list)
	{
		for (int i = 0; i < 4; i++) {
			if (i == 2) continue;
			cout << element[i] << "\t";
		}
		cout << endl;
	}
	cout << "���� �޴��� ���ư��ðڽ��ϱ�? (Y/N or y/n)" << endl;
	string input;
SelectYNRetry:
	INPUT;
	cin >> input;
	if (input == "y" or input == "Y")
	{
		// ���� �޴���
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
		cout << "�Է� ���� ����" << endl;
		goto SelectYNRetry;
	}
}

// ���� ����� ����
void Cashbook::deletePublicCashbook(string txt_name)
{
	CLEAR;
	string input;

	cout << "���� �Ͻðڽ��ϱ�? (Y/N or y/n)" << endl;
	cin >> input;

	if (input == "y" or input == "Y") {
		// ���� ���� ����� ����
		char* c_txt_name = new char[txt_name.length() + 1];		// string�� char * ���� ����
		strcpy(c_txt_name, txt_name.c_str());

		if (remove(c_txt_name) == 0) {							// ������ ���� ����� ���
			cout << "���� ����θ� �����߽��ϴ�." << endl;
			cout << "2�� �� ���� ����� ���� ȭ������ ���ư��ϴ�." << endl;

			Sleep(2000);
			// ���� �� ���� ����� ���� ȭ������ ���ư���
		}
		else {
			// ����� ������ �������� ���� ��Ȳ
			cout << "���� ����� ���� ����" << endl;
		}
	}
	else if (input == "n" or input == "N") {
		// ���� ����� �޴� �������� ���ư�
		cout << "2�� �� ���� �� ���� ����� ȭ������ ���ư��ϴ�." << endl;

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
	stime.tm_isdst = 0; //���Ÿ�� ������

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
	etime.tm_isdst = 0; //���Ÿ�� ������

	//printf("%d %d %d %d %d %d\n", s_year, s_month, s_day, e_year, e_month, e_day);
	start = mktime(&stime);
	end = mktime(&etime);

	double diff = difftime(end, start);
	// cout << diff << endl;
	tm_day = diff / double(86400);

	return tm_day;
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