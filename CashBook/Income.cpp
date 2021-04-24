#include "Income.h"

Income::Income()
{
	int select;

	while (1)
	{
		if (isDataSetting) break;
		cout << "<����>" << endl;
		cout << "1. ���" << endl;
		cout << "2. ����" << endl;
		cout << "3. �ڷΰ���" << endl;
		cin >> select;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		switch (select)
		{
		case 1:
			cout << "��¥ , �ݾ�, ī�װ�, ������ ���Ŀ� �°� ������� �Է����ּ���." << endl;
			result = data_split1();//split�Լ� �ȿ��� quit������ �߰��Ǿ����
			if (result.empty()) continue;

			if (date_test(result[0]) && price_test(result[1]) && income_category_test(result[2]) && memo_test(result[3])) {
				data_format = Income::printdata(result);
				//y/n �޴� �ڸ�
				//if (result[2] == "��Ÿ") result[2] = "��Ÿ^"; //data �����̾ȴ� �Ф�; ȭ������� ^ �Ⱥ��̰�����
				cout << "���� �Ͻðڽ��ϱ�?";
				if (yesorno()) {
					//yes
					if (!isSharedCashBook) {
						//���� �����
						readTextFile("test.txt");							//y->���� ����� �׳� ����
						writeTextFile("test.txt", data_format);
						cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
					}
					else {
						//���� �����
						data_format = data_format + user_id;				//y->���� ����� user_id �ٿ��� ����
						readTextFile("test.txt");
						writeTextFile("test.txt", data_format);
						cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
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
			cout << "���۳�¥, ���ᳯ¥, Ű���带 ���Ŀ� �°� ������� �Է����ּ���." << endl;
			result = data_split2();
			if (result.empty()) continue;

			if (date_validation(result[0], result[1])) {
				readTextFile("test.txt");
				keyword_search(result[0], result[1], result[2],false);				//�ǹؿ��� y/n����
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



string Income::printdata(vector<string> input)
{
	cout << "��¥ :" << input[0] << endl;
	cout << "�ݾ� :" << input[1] << endl;
	if (input[2] == "��Ÿ^") {
		cout << "ī�װ� :" << "��Ÿ" << endl;
	}
	if (input[3] == "") {
		cout << "����: ����" << endl;
		result[3] = '*';
	}
	else
		cout << "����: " + input[3] << endl;

	return result[0] + "/" + result[1] + "/" + result[2] + "/" + result[3];

}

bool Income::income_category_test(string& data)
{
	int test = 0;
	cout << "category testing ";
	for (int i = 0; i < income_category.size(); i++)
		if (income_category[i] == data) {
			test++;
			if (i == income_category.size() - 1)
				data = "��Ÿ^";
		}

	if (test == 1)
		return true;
	else {
		printcategory_err();
		return false;
	}
}

void Income::printcategory_err()
{
	cout << "ī�װ� ���� ����" << endl;
}