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
	bool isLoginState = false;//�α��� ���� üũ
	
public:
	struct userInfo {//ȸ������ ���� �ҷ��� �� ���
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
	string loginedId;//���� �α����� �̿��� id ǥ��
	bool isQuitState = false;//���� ���� üũ
	user();
	~user();
	void menu();//��������Ʈ �߰��� �κ�
	void login();
	void logout();
	void quit();
	void make_CashBook_public();
};