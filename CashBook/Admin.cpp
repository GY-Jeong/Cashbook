#include "CashData.h"
#include "Admin.h"

Admin::Admin() {
	int select;

	cout << "(����� ID)" << endl;
	cout << "1. ������ ���" << endl;
	cout << "2. ������ ����" << endl;
	cout << "3. �ڷ� ����" << endl;
	cout << "> ";

InputRetry:
	cin >> select;
	//cin.clear();
	//cin.ignore(INT_MAX, '\n');
	
	switch (select) {
	case 1:		//������ ���
		enrollAdministrator();

	case 2:		//������ ����
		releaseAdministrator();
		
	case 3:		//�ڷ� ����
		break;

	default:	//�߸��� �Է��� �޾��� ��
		cout << "�Է� ���� ����" << endl;
		goto InputRetry;
	}


}

void Admin::enrollAdministrator() {
	cout << "< �����ڰ� �ƴ� ȸ������ ��� >" << endl;

	cout << "> �����ڷ� ����� ȸ���� ��ȣ�� �Է��ϼ���: ";

}

void Admin::releaseAdministrator() {
	cout << "< �������� ȸ������ ��� >" << endl;

	cout << "�����ڿ��� ������ ȸ���� ��ȣ�� �Է��ϼ���" << endl;
	cout << "> ";
}


