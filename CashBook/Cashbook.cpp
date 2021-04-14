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

// Check c = Check();

// ��ȸ�� �Ⱓ�� �Է�, �Է��� ��¥���� ���ǿ� �´��� Ȯ��.
void Cashbook::inputTerm(string user_id)
{
InputRetry:
	string input;
	cout << "��ȸ�� �Ⱓ�� �Է����ּ���(�ִ� 30��)" << endl;
	cin >> input;
	cout << input;
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
			
			// �ṉ̀�Ģ, 30�� �����̰�, dates[1]�� dates[0]���� ���϶�)
			int difference_of_dates = get_difference_of_dates(dates[0], dates[1]);
			cout << "�� ��¥�� ���� : " << difference_of_dates << endl;
			if (difference_of_dates>= 0 && difference_of_dates <=30)
			{
				showTotal(user_id, dates[0], dates[1]);
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
void Cashbook::showTotal(string user_id, string start_date, string end_date)
{
ShowRetry:
	unsigned int input, total_income_price = 0, total_pay_price = 0;
	vector<Income> IncomeList;
	vector<Pay> PayList;
	// start date���� end date���� ��ȸ�ϸ� ����Ʈ�� ����
	cout << "����� ID : " << user_id << endl;
	cout << start_date << " ~ " << end_date << " �ش� �Ⱓ �����Դϴ�." << endl;
	cout << "�� ���� : " << total_pay_price << " �� ���� : " << total_income_price << endl;
	cout << "1. ����" << endl;
	cout << "2. ����" << endl;
	cout << "3. �ڷΰ���" << endl;
	cout << "��ȸ�Ͻ� ī�װ� ������ �������ּ���." << endl;
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
		cout << "�Է� ���� ����" << endl;
		break;
	}
}

// ���� ī�װ��� ������ ������.
void Cashbook::searchIncomeCategory(string user_id, string start_date, string end_date, vector<Income> IncomeList)
{
	string input;
	unsigned int income_total_money = 0;
	vector<unsigned int> category_income_total_money(5);
	for (cashData element : IncomeList)
	{
		// price�� ������ string(,����)�̰�, private�̶� �ܺ� ���� �Ұ�
		// �ǳ� �ʿ�
		// income_total_money += stoi(element.m_price);
	}
	cout << "����� ID : " << user_id << endl;
	cout << start_date << " ~ " << end_date << " �ش� �Ⱓ �����Դϴ�." << endl;
	cout << "�� ���� : " << income_total_money << endl;
	cout << "1. ����       " << endl;
	cout << "2. �뵷       " << endl;
	cout << "3. �μ�Ƽ��   " << endl;
	cout << "4. �Ƹ�����Ʈ " << endl;
	cout << "5. ��Ÿ       " << endl;
	cout << "�� ������ Ȯ���Ͻ÷��� ī�װ� ��ȣ�� �������ּ���." << endl;
	cin >> input;

	if (validQCheck(input))
	{
		showTotal(user_id, start_date, end_date);
	}
	else if (validNumberRange(input, 1, 5))
	{
		//searchDetail(pay_category[stoi(input) - 1], );
	}
	else
	{

	}
	return;
}

// ���� ī�װ��� ������ ������.
void Cashbook::searchPayCategory(string user_id, string start_date, string end_date, vector<Pay> PayList)
{
	string input;
	vector<cashData> category_paylist[7];
	for (cashData element : PayList)
	{
		//element
	}
	cout << "����� ID : " << user_id << endl;
	cout << start_date << " ~ " << end_date << " �ش� �Ⱓ �����Դϴ�." << endl;
	cout << "�� ���� : " << endl;
	cout << "1. �ĺ�       " << endl;
	cout << "2. ����       " << endl;
	cout << "3. ��ȭ       " << endl;
	cout << "4. ����       " << endl;
	cout << "5. ������     " << endl;
	cout << "6. ī��       " << endl;
	cout << "7. ��Ÿ       " << endl;
	cout << "�� ������ Ȯ���Ͻ÷��� ī�װ� ��ȣ�� �������ּ���." << endl;
	cin >> input;

	if (validQCheck(input))
	{

	}
	else if (validNumberRange(input, 1, 7))
	{
		//serchDetail(pay_category[stoi(input) - 1], );
		return;
	}
}

// �Է� ���� '�� ������ ��ȸ�� ī�װ�'�� �� ������ ������.
void Cashbook::searchDetail(string categoty_name, vector<cashData> category_list)
{
	cout << categoty_name << "�� �� �����Դϴ�." << endl;
	for (cashData element : category_list)
	{
		//cout << element.m_date << " " << element.m_price << " " << element.m_memo << endl;
	}
	cout << "���� �޴��� ���ư��ðڽ��ϱ�? (Y/N or y/n)";
}

// ���� ����� ����
void Cashbook::deletePublicCashbook(string txt_name)
{
	cashData yn;
	cout << "���� �Ͻðڽ��ϱ�? (Y/N or y/n)" << endl;
	if (yn.yesorno()) {	//y�� ���� ��� yesorno()�� true
		// ���� ���� ����� ����
		char* c_txt_name = new char[txt_name.length() + 1];		// string�� char * ���� ����
		strcpy(c_txt_name, txt_name.c_str());

		if (remove(c_txt_name) == 0) {							// ������ ���� ����� ���
			cout << "���� ����θ� �����߽��ϴ�." << endl;
			cout << "2�� �� ���� ����� ���� ȭ������ ���ư��ϴ�." << endl;

			// ������ _sleep ���� ���ͼ� Sleep���� �ٲ��! Ȯ�εǸ� �ּ� �����ּ���
			Sleep(2000);
			// ���� �� ���� ����� ���� ȭ������ ���ư���
		}
		else {
			// ����� ������ �������� ���� ��Ȳ
		}
	}
	else {					// n�� ���� ��� yesorno()�� false
		// ���� ����� �޴� �������� ���ư�
		cout << "2�� �� ���� �� ���� ����� ȭ������ ���ư��ϴ�." << endl;

		// ������ _sleep ���� ���ͼ� Sleep���� �ٲ��! Ȯ�εǸ� �ּ� �����ּ���
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

	printf("%d %d %d %d %d %d\n", s_year, s_month, s_day, e_year, e_month, e_day);
	start = mktime(&stime);
	end = mktime(&etime);

	double diff = difftime(end, start);
	cout << diff << endl;
	tm_day = diff / (60 * 60 * 24);

	return tm_day;
}