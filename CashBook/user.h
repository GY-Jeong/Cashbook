#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class user {
private:
	bool isLoginState = false;//로그인 여부 체크
	
public:
	struct userInfo {//회원정보 파일 불러올 때 사용
		string infoId = "";
		string infoPw = "";
	};
	struct pubcash {
		string pubname = "";
		string maker = "";
		string m1 = "";
		string m2 = "";
		string m3 = "";
		string m4 = "";
		string m5 = "";
		string m6 = "";
		string m7 = "";
		string m8 = "";
		string m9 = "";
	};
	string loginedId;//현재 로그인한 이용자 id 표시
	bool isQuitState = false;//종료 여부 체크
	user();
	~user();
	void menu();// 주프롬프트 추가된 부분
	void login(); // 로그인
	void logout(); // 로그 아웃
	void quit(); // 종료
	void sign_In(); // 회원가입
	bool select_CashBook(string user_id); // 가계부 선택
	string select_CashBook_public(string user_id); // 공용 가계부 선택
	void make_CashBook_public(); // 공용 가계부 만들기
};