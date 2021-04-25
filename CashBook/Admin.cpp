#include "CashData.h"
#include "Check.hpp"
#include "Admin.h"

#include <algorithm>
#include <io.h>

#define CLEAR system("cls")
#define INPUT cout << "> "

Admin::Admin(string user_id, string cashbook_name) {
	string select;

	while (1) {
		CLEAR;
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
				enrollAdministrator(cashbook_name);
				break;
			}
			case 2:		//관리자 해제
			{
				releaseAdministrator(cashbook_name);
				break;
			}
			case 3:		//뒤로 가기
				return;

			default:	//잘못된 입력을 받았을 때
			{
				cout << "여기에 들어올 일 없음" << endl;
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

void Admin::enrollAdministrator(string cashbook_name) 
{
	CLEAR;
	string input;
	int i = 1;
	vector<string> nonAdmin = makeList(cashbook_name, 2);
	
	cout << "< 관리자가 아닌 회원들의 목록 >" << endl;

	//관리자가 아닌 회원들의 목록 출력 
	for (string element : nonAdmin) {
		cout << i << ". " << element << endl;
		i++;
	}

	cout << "관리자로 등록할 회원의 번호를 입력하세요" << endl;
EnrollAdminRetry:
	INPUT;
	cin >> input;

	if (validQCheck(input)) return;
	else
	{
		vector<string> idx2name;
		vector<string> v = split(input, '/');
		sort(v.begin(), v.end());
		v.erase(unique(v.begin(), v.end()), v.end());

		for (string element : v)
		{
			if (!validNumberRange(element, 1, 1 + nonAdmin.size()))
			{
				cout << "다시 입력해주세요" << endl;
				goto EnrollAdminRetry;
			}
			idx2name.push_back(nonAdmin[stoi(element) - 1]);
		}
		changeAuthority(cashbook_name, idx2name, 1);
	}
}

void Admin::releaseAdministrator(string cashbook_name) {
	CLEAR;
	string input;
	int i = 1;
	vector<string> admin = makeList(cashbook_name, 1);

	cout << "< 관리자인 회원들의 목록 >" << endl;

	//관리자인 회원들의 목록 출력
	for (string element : admin) {
		cout << i << ". " << element << endl;
		i++;
	}

	cout << "관리자에서 해제할 회원의 번호를 입력하세요" << endl;
ReleaseAdminRetry:
	INPUT;
	cin >> input;
	if (validQCheck(input)) return;
	else 
	{
		//삭제
		vector<string> idx2name;
		vector<string> v = split(input, '/');
		sort(v.begin(), v.end());
		v.erase(unique(v.begin(), v.end()), v.end());

		for (string element : v)
		{
			if(!validNumberRange(element, 1, 1+admin.size()))
			{
				cout << "다시 입력해주세요" << endl;
				goto ReleaseAdminRetry;
			}
			idx2name.push_back(admin[stoi(element) - 1]);
		}
		changeAuthority(cashbook_name, idx2name, 2);
	}
}

vector<string> Admin::makeList(string cashbook_name, int authority) 
{
	vector<string> list;

	string txtName = "./data/public/" + cashbook_name + "_M.txt";
	ifstream ifile;
	char line[15];

	ifile.open(txtName);
	if (ifile.is_open()) 
	{
		while (ifile.getline(line, sizeof(line)))
		{
			vector<string> data = split(line, '/');
			// 0: 생성자 / 1: 관리자 / 2: 참여자
			//data[0] => 사람이름 / data[1] => 권한
			if (stoi(data[1]) == authority)
				list.push_back(data[0]);
		}
	}
	return list;
}

void Admin::changeAuthority(string cashbook_name, vector<string> user_list, int authority)
{
	vector<string> name_list;
	vector<string> authority_list;
	string txtName = "./data/public/" + cashbook_name + "_M.txt";
	ifstream ifile;
	char line[15];

	ifile.open(txtName);
	if (ifile.is_open())
	{
		while (ifile.getline(line, sizeof(line)))
		{
			vector<string> data = split(line, '/');
			name_list.push_back(data[0]);
			if (find(user_list.begin(), user_list.end(), data[0]) != user_list.end())
				authority_list.push_back(to_string(authority));
			else
				authority_list.push_back(data[1]);
		}
	}

	// 파일에 쓰면됨
	ofstream writeFile(txtName.data());
	if (writeFile.is_open()) {
		int s = name_list.size();
		for (int i = 0; i < s; i++)
		{
			writeFile << name_list[i] << "/" << authority_list[i] << "\n";
		}
		writeFile.close();
	}

	return;
}

