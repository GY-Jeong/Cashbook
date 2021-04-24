#include "CashBook.h"
#include "CashData.h"
#include "Pay.h"
#include "Income.h"
#include "Check.hpp"
#include "user.h"
#pragma warning(disable:4996)

#include <io.h>
#include <direct.h>
using namespace std;

void setting_data_directory();

int main()
{
	//string cashbook_name = "temp_cashbook";
	//Cashbook element = Cashbook();
	//cashData cd;
	//cd.menu(false);
	//cd.readTextFile("test2.txt");
	//string user_id = "user_id";
	//element.inputTerm(user_id);

	//user ur;
	//ur.menu();
	setting_data_directory();

	string user_id = "naeun";
	string cashbook_name = "nanni";

	Cashbook cb(user_id, cashbook_name, 1);
}

void setting_data_directory()
{
	int data_directory_exists = access("./data", 00);
	if (data_directory_exists == -1)
	{
		int nResult = mkdir("./data");

		if(nResult == 0)
			cout << "������ ���丮 ����" << endl;
		else
			cout << "������ ���丮 ���� ����" << endl;
	}

	int data_public_directory_exists = access("./data/public", 00);
	if (data_public_directory_exists == -1)
	{
		int nResult = mkdir("./data/public");

		if (nResult == 0)
			cout << "public ������ ���丮 ����" << endl;
		else
			cout << "public ������ ���丮 ���� ����" << endl;
	}

	int data_private_directory_exists = access("./data/private", 00);
	if (data_private_directory_exists == -1)
	{
		int nResult = mkdir("./data/private");

		if (nResult == 0)
			cout << "private ������ ���丮 ����" << endl;
		else
			cout << "private ������ ���丮 ���� ����" << endl;
	}
}