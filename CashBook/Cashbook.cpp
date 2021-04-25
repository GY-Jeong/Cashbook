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
					Pay* pay = new Pay(isSharedCashBook, user_id, cashbook_name, cd.txt_file);//user.id �����ڷ� �Ѱ������
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
					if (user_authority != 0) {
						cout << "�ش� ������ �����ϴ�." << endl;
						cout << "1.5�� �� ���� ����� ȭ������ ���ư��ϴ�." << endl;
						Sleep(1500);
						break;			//���� ����� ȭ������ ����
					}
					else {
						//cout << "���� ����� ������ ����" << endl;
						Admin* admin = new Admin(user_id, cashbook_name);
						break;
					}
				}
				case 1:
				{
					CLEAR;
					if (user_authority == 2) {
						cout << "�ش� ������ �����ϴ�." << endl;
						cout << "1.5�� �� ���� ����� ȭ������ ���ư��ϴ�." << endl;
						Sleep(1500);
						break;			//���� ����� ȭ������ ����
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
						cout << "�ش� ������ �����ϴ�." << endl;
						cout << "1.5�� �� ���� ����� ȭ������ ���ư��ϴ�." << endl;
						Sleep(1500);
						break;			//���� ����� ȭ������ ����
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
						cout << "�ش� ������ �����ϴ�." << endl;
						cout << "1.5�� �� ���� ����� ȭ������ ���ư��ϴ�." << endl;
						Sleep(1500);
						break;			//���� ����� ȭ������ ����
					}
					else {
						bool check = deletePublicCashbook();
						if (check) return;
						// �Ҹ��� ȣ���ϴ°� ����?
						break;
					}
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
	cd.readTextFile(cd.txt_file);
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
		if(income_total_money != 0)
			cout << printlist[i] << category_income_total_money[i] << "�� (" << int(double(category_income_total_money[i]) / double(income_total_money) * 100) << "%)" << endl;
		else
			cout << printlist[i] << category_income_total_money[i] << "�� (0%)" << endl;
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
	cout << categoty_name << "�� �� �����Դϴ�." << endl;
	for (vector<string> element : category_list)
	{
		for (int i = 0; i < 4; i++) {
			// ���� ���� ����ζ�� �ø� ����� �÷��ߵ�
			// �����϶��� i==4 (�ø� ���) ���� ���, �� �κ� �׽�Ʈ �ʿ�
			if (!isSharedCashBook && i == 3) continue;
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
bool Cashbook::deletePublicCashbook()
{
	string txt_name = "./data/public/" + cashbook_name + ".txt";
	string M_txt_name = "./data/public/" + cashbook_name + "_M.txt";

	CLEAR;
	string input;
	cout << "���� �Ͻðڽ��ϱ�? (Y/N or y/n)" << endl;
SelectYNRetry_delete:
	INPUT;
	cin >> input;

	if (input == "y" or input == "Y") {
		// ���� ���� ����� ����
		char* c_txt_name = new char[txt_name.length() + 1];		// string�� char * ���� ����
		strcpy(c_txt_name, txt_name.c_str());

		char* c_M_txt_name = new char[M_txt_name.length() + 1];		// string�� char * ���� ����
		strcpy(c_M_txt_name, M_txt_name.c_str());

		bool check = true;

		if (access(c_txt_name, 00) == -1)
		{
			cout << c_txt_name << "�� �������� ����" << endl;
		}
		else
		{
			if (remove(c_txt_name) == 0) {							// ������ ���� ����� ���
				cout << c_txt_name << "���� ����" << endl;
			}
			else {
				// ����� ������ �������� ���� ��Ȳ
				cout << c_txt_name << "���� ����" << endl;
			}
		}

		if (access(c_M_txt_name, 00) == -1)
		{
			cout << c_M_txt_name << "�� �������� ����" << endl;
		}
		else
		{
			if (remove(c_M_txt_name) == 0) {							// ������ ���� ����� ���
				cout << c_M_txt_name << "���� ����" << endl;
			}
			else {
				// ����� ������ �������� ���� ��Ȳ
				cout << c_M_txt_name << "���� ����" << endl;
			}
		}

		//hidden �о�ͼ� �ش� line ���� �ʿ�
		modify_hidden_file();

		cout << "���� ����θ� �����߽��ϴ�." << endl;
		cout << "2�� �� ���� ����� ���� ȭ������ ���ư��ϴ�." << endl;
		Sleep(2000);
		return true;
		// ���� �� ���� ����� ���� ȭ������ ���ư���
	}
	else if (input == "n" or input == "N") {
		// ���� ����� �޴� �������� ���ư�
		cout << "2�� �� ���� �� ���� ����� ȭ������ ���ư��ϴ�." << endl;
		Sleep(2000);
		return false;
	}
	else
	{
		cout << "�Է� ���� ����" << endl;
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

	// ���Ͽ� �����
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
		