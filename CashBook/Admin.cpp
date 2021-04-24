#include "CashData.h"
#include "Check.hpp"
#include "Admin.h"

#define CLEAR system("cls")
#define INPUT cout << "> "

Admin::Admin(string user_id) {
	CLEAR;

	string select;

	while (1) {

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
				enrollAdministrator();
				break;
			}
			case 2:		//������ ����
			{
				releaseAdministrator();
				break;
			}
			case 3:		//�ڷ� ����
				return;

			default:	//�߸��� �Է��� �޾��� ��
			{
				cout << "�Է� ���� ����" << endl;
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

void Admin::enrollAdministrator() 
{
	CLEAR;
	string input;
	
	cout << "< �����ڰ� �ƴ� ȸ������ ��� >" << endl;

	//�����ڰ� �ƴ� ȸ������ ��� ���
	cout << "���� ��� ������ ���̴� ���!" << endl;

	cout << "> �����ڷ� ����� ȸ���� ��ȣ�� �Է��ϼ���: ";

	cin >> input;

	if (validQCheck(input)) 
	{
		//�ڷ� ����
		return;
	}
	else 
	{
		//���
	}


}

void Admin::releaseAdministrator() {
	cout << "< �������� ȸ������ ��� >" << endl;

	//�������� ȸ������ ��� ���
	cout << "���� ��� ������ ���̴� ���!" << endl;

	cout << "�����ڿ��� ������ ȸ���� ��ȣ�� �Է��ϼ���" << endl;
	INPUT;

	string input;
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


