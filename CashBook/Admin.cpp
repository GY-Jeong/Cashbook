#include "CashData.h"
#include "Check.hpp"
#include "Admin.h"

#define CLEAR system("cls")
#define INPUT cout << "> "

vector<string> makeList(string cashbook_name, int authority);

Admin::Admin(string user_id, string cashbook_name) {
	string select;

	while (1) {
		CLEAR;
		cout << "����� ID: " << user_id << endl;
		cout << "1. ������ ���" << endl;
		cout << "2. ������ ����" << endl;
		cout << "3. �ڷ� ����" << endl;

	InputRetry_admin:
		INPUT;
		cin >> select;
		//cin.clear();
		//cin.ignore(INT_MAX, '\n');
	
		if (validNumberRange(select, 1, 3)) {
			switch (stoi(select)) {
			case 1:		//������ ���
			{
				enrollAdministrator(cashbook_name);
				break;
			}
			case 2:		//������ ����
			{
				releaseAdministrator(cashbook_name);
				break;
			}
			case 3:		//�ڷ� ����
				return;

			default:	//�߸��� �Է��� �޾��� ��
			{
				cout << "���⿡ ���� �� ����" << endl;
				break;
			}
			}
		}
		else {
			cout << "�ٽ� �Է����ּ���" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			goto InputRetry_admin;
		}
	}
}

void Admin::enrollAdministrator(string cashbook_name) 
{
	CLEAR;
	string input;
	vector<string> splitInput;
	int i = 1;
	vector<string> nonAdmin;
	nonAdmin = makeList(cashbook_name, 2);
	
	cout << "< �����ڰ� �ƴ� ȸ������ ��� >" << endl;

	//�����ڰ� �ƴ� ȸ������ ��� ��� 
	for (string element : nonAdmin) {
		cout << i << ". " << element << endl;
		i++;
	}

	cout << "> �����ڷ� ����� ȸ���� ��ȣ�� �Է��ϼ���: ";

	cin >> input;

	if (validQCheck(input)) 
	{
		//�ڷ� ����
		return;
	}
	else 
	{
		//�ذ���� ���� �κ�
		vector<string> splitInput = split(input, '/');
		//���
		//for (int data : splitInput) {			//split ������ ����
			//if()								//splitInput ���� 
			//changeAuthority(cashbook_name, nonAdmin[stoi(input) - 1], 1);
		//}
	}
}

void Admin::releaseAdministrator(string cashbook_name) {
	CLEAR;
	string input;
	int i = 1;
	vector<string> admin;
	admin = makeList(cashbook_name, 1);

	cout << "< �������� ȸ������ ��� >" << endl;

	//�������� ȸ������ ��� ���
	for (string element : admin) {
		cout << i << ". " << element << endl;
		i++;
	}

	cout << "�����ڿ��� ������ ȸ���� ��ȣ�� �Է��ϼ���" << endl;
	INPUT;

	cin >> input;

	if (validQCheck(input)) 
	{
		//�ڷ� ����
		return;
	}
	else 
	{
		//����
		
	}
}

vector<string> makeList(string cashbook_name, int authority) 
{
	vector<string> list;

	string txtName = cashbook_name + "_M.txt";
	ifstream ifile;
	char line[15];

	ifile.open(txtName);
	if (ifile.is_open()) 
	{
		while (ifile.getline(line, sizeof(line)))
		{
			vector<string> data = split(line, '/');
			// 0: ������ / 1: ������ / 2: ������
			//data[0] => ����̸� / data[1] => ����
			if (stoi(data[1]) == authority)
				list.push_back(data[0]);
		}
	}
	return list;
}

void changeAuthority(string cashbook_name, string user_id, int authority)
{
	string txtName = cashbook_name + "_M.txt";
	ifstream ifile;
	char line[15];

	ifile.open(txtName);
	if (ifile.is_open())
	{
		while (ifile.getline(line, sizeof(line)))
		{
			vector<string> data = split(line, '/');

			if (data[0] == user_id) {
				data[1] = authority;
			}
		}
	}
}

