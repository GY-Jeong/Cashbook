#include "CashData.h"
#include "Check.hpp"
#include "Admin.h"

#define CLEAR system("cls")
#define INPUT cout << "> "

Admin::Admin(string user_id) {
	CLEAR;

	string select;

	while (1) {

		cout << "사용자 ID: " << user_id << endl;
		cout << "1. 관리자 등록" << endl;
		cout << "2. 관리자 해제" << endl;
		cout << "3. 뒤로 가기" << endl;

	InputRetry_admin:
		INPUT;
		cin >> select;
		//cin.clear();
		//cin.ignore(INT_MAX, '\n');
	
		if (validNumberRange(select, 1, 3)) {
			switch (stoi(select)) {
			case 1:		//관리자 등록
			{
				enrollAdministrator();
				break;
			}
			case 2:		//관리자 해제
			{
				releaseAdministrator();
				break;
			}
			case 3:		//뒤로 가기
				return;

			default:	//잘못된 입력을 받았을 때
			{
				cout << "입력 형식 오류" << endl;
				break;
			}
			}
		}
		else {
			cout << "다시 입력해주세요" << endl;
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
	
	cout << "< 관리자가 아닌 회원들의 목록 >" << endl;

	//관리자가 아닌 회원들의 목록 출력
	cout << "착한 사람 눈에만 보이는 목록!" << endl;

	cout << "> 관리자로 등록할 회원의 번호를 입력하세요: ";

	cin >> input;

	if (validQCheck(input)) 
	{
		//뒤로 가기
		return;
	}
	else 
	{
		//등록
	}


}

void Admin::releaseAdministrator() {
	cout << "< 관리자인 회원들의 목록 >" << endl;

	//관리자인 회원들의 목록 출력
	cout << "착한 사람 눈에만 보이는 목록!" << endl;

	cout << "관리자에서 해제할 회원의 번호를 입력하세요" << endl;
	INPUT;

	string input;
	cin >> input;

	if (validQCheck(input)) 
	{
		//뒤로 가기
		return;
	}
	else 
	{
		//삭제
	}
}


