#include <bits/stdc++.h>
#include "Header.hpp"
#include "Check.hpp"

using namespace std;

vector<string> split(string str, char delimiter);

Check c = Check();

// ��ȸ�� �Ⱓ�� �Է�, �Է��� ��¥���� ���ǿ� �´��� Ȯ��.
void Cashbook::inputTerm()
{
	string input;
	cout << "��ȸ�� �Ⱓ�� �Է����ּ���(�ִ� 30��)" << endl;
	cin >> input;
	cout << input;
	if (c.validQCheck(input))
	{
		// �ڷ� ����
	}
	else
	{
		// split �Լ��� header�� ����
		vector<string> dates = split(input, '/');
		// '/'�� ���е� string�� 2���̰�, 2���� string ��� ��ȿ�� ��¥ �������� ��
		if (dates.size() == 2 && c.validDateCheck(dates[0]) && c.validDateCheck(dates[1]))
		{

		}
		// ���� ���
		else
		{

		}
	}
}

// �� ���԰� ������ ������.
void Cashbook::showTotal()
{

}

// ���� ī�װ��� ������ ������.
void Cashbook::searchIncomeCategory()
{

}

// ���� ī�װ��� ������ ������.
void Cashbook::serchPayCategory()
{

}

// �Է� ���� '�� ������ ��ȸ�� ī�װ�'�� �� ������ ������.
void Cashbook::searchDetail()
{

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
