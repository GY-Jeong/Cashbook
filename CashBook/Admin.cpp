#include "CashData.h"
#include "Check.hpp"
#include "Admin.h"

#include <algorithm>
#include <io.h>

#define CLEAR system("cls")
#define INPUT cout << "> "

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
	int i = 1;
	vector<string> nonAdmin = makeList(cashbook_name, 2);
	
	cout << "< �����ڰ� �ƴ� ȸ������ ��� >" << endl;

	//�����ڰ� �ƴ� ȸ������ ��� ��� 
	for (string element : nonAdmin) {
		cout << i << ". " << element << endl;
		i++;
	}

	cout << "�����ڷ� ����� ȸ���� ��ȣ�� �Է��ϼ���" << endl;
EnrollAdminRetry:
	INPUT;
	cin >> input;

	if (validQCheck(input)) return;
	else
	{
		vector<string> idx2name;
		vector<string> v = split(input, '/');
		sort(v.begin(), v.end());
		v.erase(unique(v.begin(), v.end()), v.end());

		for (string element : v)
		{
			if (!validNumberRange(element, 1, 1 + nonAdmin.size()))
			{
				cout << "�ٽ� �Է����ּ���" << endl;
				goto EnrollAdminRetry;
			}
			idx2name.push_back(nonAdmin[stoi(element) - 1]);
		}
		changeAuthority(cashbook_name, idx2name, 1);
	}
}

void Admin::releaseAdministrator(string cashbook_name) {
	CLEAR;
	string input;
	int i = 1;
	vector<string> admin = makeList(cashbook_name, 1);

	cout << "< �������� ȸ������ ��� >" << endl;

	//�������� ȸ������ ��� ���
	for (string element : admin) {
		cout << i << ". " << element << endl;
		i++;
	}

	cout << "�����ڿ��� ������ ȸ���� ��ȣ�� �Է��ϼ���" << endl;
ReleaseAdminRetry:
	INPUT;
	cin >> input;
	if (validQCheck(input)) return;
	else 
	{
		//����
		vector<string> idx2name;
		vector<string> v = split(input, '/');
		sort(v.begin(), v.end());
		v.erase(unique(v.begin(), v.end()), v.end());

		for (string element : v)
		{
			if(!validNumberRange(element, 1, 1+admin.size()))
			{
				cout << "�ٽ� �Է����ּ���" << endl;
				goto ReleaseAdminRetry;
			}
			idx2name.push_back(admin[stoi(element) - 1]);
		}
		changeAuthority(cashbook_name, idx2name, 2);
	}
}

vector<string> Admin::makeList(string cashbook_name, int authority) 
{
	vector<string> list;

	string txtName = "./data/public/" + cashbook_name + "_M.txt";
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

void Admin::changeAuthority(string cashbook_name, vector<string> user_list, int authority)
{
	vector<string> name_list;
	vector<string> authority_list;
	string txtName = "./data/public/" + cashbook_name + "_M.txt";
	ifstream ifile;
	char line[15];

	ifile.open(txtName);
	if (ifile.is_open())
	{
		while (ifile.getline(line, sizeof(line)))
		{
			vector<string> data = split(line, '/');
			name_list.push_back(data[0]);
			if (find(user_list.begin(), user_list.end(), data[0]) != user_list.end())
				authority_list.push_back(to_string(authority));
			else
				authority_list.push_back(data[1]);
		}
	}

	// ���Ͽ� �����
	ofstream writeFile(txtName.data());
	if (writeFile.is_open()) {
		int s = name_list.size();
		for (int i = 0; i < s; i++)
		{
			writeFile << name_list[i] << "/" << authority_list[i] << "\n";
		}
		writeFile.close();
	}

	return;
}

