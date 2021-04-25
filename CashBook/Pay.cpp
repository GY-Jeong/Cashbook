#include "Pay.h"

#define CLEAR system("cls")
#define INPUT cout << "> "

Pay::Pay(bool isShared, string user_id, string cashbook_name, string txt_file)
{
	this->isSharedCashBook = isShared;
	this->user_id = user_id;
	this->cashbook_name = cashbook_name;

	int select;
	while (1)
	{
		CLEAR;
		if (isDataSetting) break;
		cout << "< �Һ� >" << endl;
		cout << "1. ���" << endl;
		cout << "2. ����" << endl;
		cout << "3. �ڷΰ���" << endl;
		INPUT;
		cin >> select;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		switch (select)
		{
		case 1:
			CLEAR;
			cout << "��¥, �ݾ�, ī�װ�, ������ ���Ŀ� �°� ������� �Է����ּ���." << endl;
			result = data_split1();//split�Լ� �ȿ��� quit������ �߰��Ǿ����
			if (result.empty()) continue;

			if (date_test(result[0]) && price_test(result[1]) && pay_category_test(result[2]) && memo_test(result[3])) {
				data_format = Pay::printdata(result);
				//y/n �޴� �ڸ�
				cout << "���� �Ͻðڽ��ϱ�?";
				if (yesorno()) {
					//yes
					if (!isSharedCashBook) {
						//���� �����
						readTextFile(txt_file);							//y->���� ����� �׳� ����
						writeTextFile(txt_file, data_format);
						cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
						readTextFile(txt_file);
					}
					else {
						//���� �����
						data_format = data_format + "/" + user_id;				//y->���� ����� user_id �ٿ��� ����
						readTextFile(txt_file);
						writeTextFile(txt_file, data_format);
						cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
						readTextFile(txt_file);
					}
				}
				else {				//n-> ���� ����
					cout << "�������� �ʽ��ϴ�." << endl;
				}
				isDataSetting = true; //y/n������� �帧���� �б�� �̵�
			}
			result.clear();
			data_format.clear();
			break;
		case 2:
			CLEAR;
			cout << "���۳�¥, ���ᳯ¥, Ű���带 ���Ŀ� �°� ������� �Է����ּ���." << endl;
			result = data_split2();
			if (result.empty()) continue;

			if (date_validation(result[0], result[1])) {
				readTextFile(txt_file);
				keyword_search(result[0], result[1], result[2], true);				//�ǹؿ��� y/n����
				isDataSetting = true;//y/n ������� �帧���� �б�� �̵�
			}
			else {
				cout << "������ / ������ �ṉ̀�Ģ ����" << endl;
			}
			result.clear();
			break;
		case 3:
			break;
		default:
			cout << "�ٽ� �Է����ּ���" << endl;
			break;
		}
		if (select == 3) break;
	}
}

string Pay::printdata(vector<string> input)
{
	cout << "��¥ :" << input[0] << endl;
	cout << "�ݾ� :" << input[1] << endl;
	cout << "ī�װ� :" << input[2] << endl;
	if (input[3] == "") {
		cout << "����: ����" << endl;
		result[3] = '*';
	}
	else
		cout << "����: " + input[3] << endl;

	return result[0] + "/" + result[1] + "/" + result[2] + "/" + result[3];

}

bool Pay::pay_category_test(string data)
{
	int test = 0;
	cout << "category testing ";
	for (int i = 0; i < pay_category.size(); i++)
		if (pay_category[i] == data) {
			test++;
		}

	if (test == 1)
		return true;
	else {
		printcategory_err();
		return false;
	}
}

void Pay::printcategory_err()
{
	cout << "ī�װ� ���� ����" << endl;
}