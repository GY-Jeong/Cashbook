#include "CashBook.h"
#include "CashData.h"
#include "Pay.h"
#include "Income.h"

using namespace std;

vector<string> split(string str, char delimiter);

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
			if ()
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
	unsigned int input, total_income_price, total_pay_price;
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
		serchPayCategory(user_id, start_date, end_date, PayList);
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
		income_total_money += stoi(element.m_price);
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
		serchDetail(pay_category[stoi(input) - 1], );
	}
	else
	{

	}
	return;
}

// ���� ī�װ��� ������ ������.
void Cashbook::serchPayCategory(string user_id, string start_date, string end_date, vector<Pay> PayList)
{
	string input;
	vector<cashData> category_paylist[7];
	for (cashData element : PayList)
	{
		element
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
		serchDetail(pay_category[stoi(input) - 1], );
		return;
	}
}

// �Է� ���� '�� ������ ��ȸ�� ī�װ�'�� �� ������ ������.
void Cashbook::searchDetail(string categoty_name, vector<cashData> category_list)
{
	cout << categoty_name << "�� �� �����Դϴ�." << endl;
	for (cashData element : category_list)
	{
		cout << element.m_date << " " << element.m_price << " " element.m_memo << endl;
	}
	cout << "���� �޴��� ���ư��ðڽ��ϱ�? (Y/N or y/n)"
}

void Cashbook::deletePublicCashbook()
{

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
