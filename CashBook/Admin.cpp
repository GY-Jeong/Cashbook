#include "CashData.h"
#include "Admin.h"

Admin::Admin() {
	int select;

	cout << "(사용자 ID)" << endl;
	cout << "1. 관리자 등록" << endl;
	cout << "2. 관리자 해제" << endl;
	cout << "3. 뒤로 가기" << endl;
	cout << "> ";

InputRetry:
	cin >> select;
	//cin.clear();
	//cin.ignore(INT_MAX, '\n');
	
	switch (select) {
	case 1:		//관리자 등록
		enrollAdministrator();

	case 2:		//관리자 해제
		releaseAdministrator();
		
	case 3:		//뒤로 가기
		break;

	default:	//잘못된 입력을 받았을 때
		cout << "입력 형식 오류" << endl;
		goto InputRetry;
	}


}

void Admin::enrollAdministrator() {
	cout << "< 관리자가 아닌 회원들의 목록 >" << endl;

	cout << "> 관리자로 등록할 회원의 번호를 입력하세요: ";

}

void Admin::releaseAdministrator() {
	cout << "< 관리자인 회원들의 목록 >" << endl;

	cout << "관리자에서 해제할 회원의 번호를 입력하세요" << endl;
	cout << "> ";
}


