#include "user.h"
#include <map>
#include "Windows.h"

#define SIZE 100
#pragma warning(disable:4996)

user::user() {

}

user::~user() {

}

void user::menu() {
	int sel = 4;
	cout << "1. 로그인" << endl;
	cout << "2. 회원가입" << endl;
	cout << "3. 종료" << endl;
	cout << "> ";

	while (sel < 1 || sel>3) {
		cin >> sel;
		if (sel < 1 || sel>3) {
			cout << "다시 입력해주세요" << endl;
			cout << ">";
			continue;
		}
		else {
			break;
		}
	}
	if (sel == 1) {
		user::login();
	}
	else if (sel == 2) {
		//user::signin();
	}
	else if (sel == 3) {
		user::quit();
	}
}

void user::login() {
	string idpw;
	string id;
	char idid[SIZE];
	string pw;
	char pwpw[SIZE];
	bool idfail = false;
	bool pwfail = false;
	bool diff = false;
	vector<userInfo> minfo;
	userInfo information;

	//회원정보 파일 불러오기
	ifstream mfile("memberinformation.txt");
	for (userInfo i;getline(mfile, i.infoId, '/') && getline(mfile, i.infoPw);) {
		minfo.push_back(i);
	}
	/*
	for (int i = 0;i < minfo.size();i++) {
		cout << minfo[i].infoId << " " << minfo[i].infoPw << endl;
	}
	*/
	if (user::isLoginState == false) {
		cout << "아이디와 비밀번호를 입력하세요" << endl;
		cout << ">";
		cin.clear();
		while (user::isLoginState == false) {
			idfail = false;
			pwfail = false;
			diff = false;
			vector<string> input;
			cin.clear();
			cin >> idpw;
			cin.clear();
			if (idpw == "q") {
				cin.clear();
				user::menu();
				break;
			}
			else if (idpw.find("/") == string::npos) {
				cout << "다시 입력해주세요" << endl;
				cout << ">";
				continue;
			}
			//cout << idpw << endl;
			stringstream ss(idpw);
			string token1;
			while (getline(ss, token1, '/'))
			{
				input.push_back(token1);
			}
			//cout << input[0] << endl << input[1] << endl;
			id = input[0];
			pw = input[1];
			cin.clear();
			//cout << id << pw << endl;
			cin.clear();
			if (id.size() >= 5 && id.size() <= 12) {//id길이 검사
				strcpy(idid, id.c_str());
				//cout << idid << endl;
				for (int i = 0;i < strlen(idid);i++) {
					if (idid[i] < 97 || idid[i] > 122) {//id 영어소문자검사
						idfail = true;
					}
				}
				if (idfail == true && user::isLoginState == false) {
					cout << "다시 입력해주세요" << endl;
					cout << ">";
					cin.clear();
					continue;
				}
				else {
					if (pw.size() >= 5 && pw.size() <= 12) {//pw길이 검사
						strcpy(pwpw, pw.c_str());
						//cout << pwpw << endl;
						for (int j = 0;j < strlen(pwpw);j++) {
							if (pwpw[j] < 97 || pwpw[j] > 122) {//pw 영어소문자검사
								pwfail = true;
							}
						}
						if (pwfail == true && user::isLoginState == false) {
							cout << "다시 입력해주세요" << endl;
							cout << ">";
							cin.clear();
							continue;
						}
						else {
							//id, pw 존재여부 검사
							//id 먼저 거르기
							for (int i = 0;i < minfo.size();i++) {
								if (minfo[i].infoId.compare(id) == 0 && minfo[i].infoPw.compare(pw) == 0) {//id 존재여부
									user::isLoginState = true;
									user::loginedId = id;
									//cout << "Log In!!" << endl;
									break;
								}
								diff = true;
							}

							if (diff == true && user::isLoginState == false) {
								cout << "아이디와 비밀번호가 일치하지않습니다." << endl;
								cout << "다시 입력해주세요" << endl;
								cout << ">";
								cin.clear();
								continue;
							}
							else if (user::isLoginState == true) {
								cout << "Log In!!" << endl;
								cin.clear();
								break;
							}
						}
					}
					else {
						cout << "다시 입력해주세요" << endl;
						cout << ">";
						cin.clear();
						continue;
					}
				}
			}
			else {
				cout << "다시 입력해주세요" << endl;
				cout << ">";
				cin.clear();
				continue;
			}
		}
		cout << "가계부 선택으로!!" << endl;
		//user::select_Cashbook();
		user::make_CashBook_public();
	}

}

void user::logout() {
	if (user::isLoginState == true) {
		user::isLoginState = false;
		user::loginedId = "";
		cout << "로그아웃" << endl;
	}
	user::menu();
}

void user::quit() {
	user::isQuitState = true;
	cout << "가계부 프로그램을 종료합니다" << endl;
	exit(0);
}


void user::make_CashBook_public() {
	string bookname;
	string memlist;
	char name[SIZE];
	bool namefail = false;//가계부이름 문법규칙 위반
	bool namesame = false;//가계부이름 중복
	bool nsuccess = false;//공용가계부 생성여부체크(멤버입력전 생성만)
	bool memsuccess = false;//멤버입력 성공여부체크
	bool notmem = false;//회원 아닌 경우
	bool manybook = false;//공용 가계부 개수 5개 넘는 경우
	bool onemem = false;
	vector<string> members;
	vector<userInfo> meminfo;//회원정보 id비교
	userInfo info;
	vector<pubcash> pubinfo;//공용가계부이름, 속한 멤버들 비교
	pubcash pinfo;
	vector<string> allbook;//개인+공용 가계부이름들만 모음

	//회원정보 파일 불러오기
	ifstream memfile("memberinformation.txt");
	for (userInfo i;getline(memfile, i.infoId, '/') && getline(memfile, i.infoPw);) {
		meminfo.push_back(i);
	}

	//공용가계부이름,멤버들 파일 불러오기->멤버수가 적어서 구조체 만큼 안될경우 아예 멤버넣을때 빈칸은 x로
	ifstream pubfile("makehiddenfile.txt");
	for (pubcash i;getline(pubfile, i.pubname, '/') && getline(pubfile, i.maker, '/') && getline(pubfile, i.m1, '/') && getline(pubfile, i.m2, '/') && getline(pubfile, i.m3, '/') && getline(pubfile, i.m4, '/') && getline(pubfile, i.m5, '/') && getline(pubfile, i.m6, '/') && getline(pubfile, i.m7, '/') && getline(pubfile, i.m8, '/') && getline(pubfile, i.m9);) {
		pubinfo.push_back(i);
	}

	//개인+공용 가계부 이름들만 모아놓음
	for (int j = 0;j < meminfo.size();j++) {
		allbook.push_back(meminfo[j].infoId);
	}
	for (int j = 0;j < pubinfo.size();j++) {
		allbook.push_back(pubinfo[j].pubname);
	}

	cout << "생성할 가계부 이름을 작성해주세요(영소문자 최대 5자)" << endl;
	cout << ">";
	while (nsuccess == false) {
		namefail = false;
		namesame = false;
		cin.clear();
		cin >> bookname;
		cin.clear();
		if (bookname == "q") {
			cin.clear();
			//user::select_Cashbook();
			break;
		}
		else if (bookname.size() <= 5) {
			strcpy(name, bookname.c_str());
			//cout << name << endl;
			for (int i = 0;i < strlen(name);i++) {
				if (name[i] < 97 || name[i] > 122) {//가계부이름 영어소문자검사
					namefail = true;
				}
			}
			if (namefail == true) {
				cout << "다시 입력해주세요" << endl;
				cout << ">";
				continue;
			}
			for (int i = 0;i < allbook.size();i++) {
				if (allbook[i].compare(bookname) == 0) {//가계부이름 중복여부 체크
					namesame = true;
				}
			}
			if (namesame == true) {
				cout << "다시 입력해주세요" << endl;
				cout << ">";
				continue;
			}
			nsuccess = true;
		}
		else {
			cout << "다시 입력해주세요" << endl;
			cout << ">";
			continue;
		}
	}
	stringstream sss;
	cin.clear();
	sss << bookname << ".txt";
	string sfilename = sss.str();
	char savefilename[20];
	strcpy(savefilename, sfilename.c_str());
	ofstream sfile(savefilename);
	cout << "공용가계부 생성!!" << endl;
	//멤버 입력받기
	cout << "함께 쓸 사용자의 아이디를 입력해주세요. (최대 9 명)" << endl;
	cout << ">";
	while (memsuccess == false) {
		notmem = false;
		manybook = false;
		vector<string> minput;
		pubcash pm;
		int idcount = 0;
		vector<int> bookcount;
		cin.clear();
		cin >> memlist;
		cin.clear();

		if (memlist == "x") {//멤버 추가 없는 경우 엔터만 누르는 것으로 설정해놓음
			onemem = true;
			memsuccess = true;
			break;
		}

		stringstream sss(memlist);
		string token2;

		if (memlist.find("/") == string::npos) {//'/'없이 입력-1명의 멤버아이디
			while (getline(sss, token2, '\n'))
			{
				minput.push_back(token2);
			}
		}

		else {
			while (getline(sss, token2, '/'))
			{
				minput.push_back(token2);
			}
		}
		for (int i = 0;i < minput.size();i++) {
			bookcount.push_back(0);
		}

		if (minput.size() > 9) {//9명 초과
			cout << "다시 입력해주세요" << endl;
			cout << ">";
			continue;
		}
		else {//회원정보에 없는 경우, 공용 가계부 이미 5개 있는 경우
			for (int i = 0;i < minput.size();i++) {///회원 여부 확인
				for (int j = 0;j < meminfo.size();j++) {
					if (minput[i].compare(meminfo[j].infoId) == 0) {
						idcount += 1;
					}
				}
			}
			if (idcount == minput.size()) {
				idcount = 0;
				for (int i = 0;i < minput.size();i++) {///공용가계부 5개 이상 여부 확인
					for (int j = 0;j < pubinfo.size();j++) {
						if (minput[i].compare(pubinfo[j].maker) == 0) {
							bookcount[i] += 1;
						}
						if (minput[i].compare(pubinfo[j].m1) == 0) {
							bookcount[i] += 1;
						}
						if (minput[i].compare(pubinfo[j].m2) == 0) {
							bookcount[i] += 1;
						}
						if (minput[i].compare(pubinfo[j].m3) == 0) {
							bookcount[i] += 1;
						}
						if (minput[i].compare(pubinfo[j].m4) == 0) {
							bookcount[i] += 1;
						}
						if (minput[i].compare(pubinfo[j].m5) == 0) {
							bookcount[i] += 1;
						}
						if (minput[i].compare(pubinfo[j].m6) == 0) {
							bookcount[i] += 1;
						}
						if (minput[i].compare(pubinfo[j].m7) == 0) {
							bookcount[i] += 1;
						}
						if (minput[i].compare(pubinfo[j].m8) == 0) {
							bookcount[i] += 1;
						}
						if (minput[i].compare(pubinfo[j].m9) == 0) {
							bookcount[i] += 1;
						}
					}
				}
				for (int i = 0;i < bookcount.size();i++) {
					if (bookcount[i] >= 5) {
						manybook = true;
					}
				}
				if (manybook == true) {
					cout << "다시 입력해주세요" << endl;
					cout << ">";
					continue;
				}
				for (int i = 0;i < minput.size();i++) {
					members.push_back(minput[i]);
				}
				memsuccess = true;
			}
			else {
				notmem = true;
				idcount = 0;
				cout << "다시 입력해주세요" << endl;
				cout << ">";
				continue;
			}
		}
	}
	//멤버 없는 경우, 있는 경우(9명, 9명 미만인 경우-makehiddenfile.txt 나머지 x로 채워야함) 파일 생성
	if (onemem == true) {
		string sstr = bookname + "_M";
		stringstream save;
		save << sstr << ".txt";
		string smfilename = save.str();
		char savemfilename[20];
		strcpy(savemfilename, smfilename.c_str());
		ofstream smfile(savemfilename);

		if (smfile.is_open()) {
			smfile << user::loginedId;
			smfile << "/";
			smfile << "0";
			smfile << "\n";

			smfile.close();
		}
	}
	else {
		string ssstr = bookname + "_M";
		stringstream savem;
		savem << ssstr << ".txt";
		string ssmfilename = savem.str();
		char ssavemfilename[20];
		strcpy(ssavemfilename, ssmfilename.c_str());
		ofstream ssmfile(ssavemfilename);

		if (ssmfile.is_open()) {
			ssmfile << user::loginedId;
			ssmfile << "/";
			ssmfile << "0";
			ssmfile << "\n";
			if (!members.empty()) {
				for (vector<string>::iterator iter = members.begin(); iter != members.end(); iter++) {
					ssmfile << *iter << "/" << "2" << "\n";
				}
			}
			ssmfile.close();
		}
	}
	//가계부개수 체크를 위해 사용하는 파일 작성
	if (members.size() == 9) {
		ofstream spub("makehiddenfile.txt", ios::out | ios::app);

		spub << bookname << "/" << loginedId << "/";
		for (int i = 0;i < members.size() - 1;i++) {
			spub << members[i] << "/";
		}
		spub << members[8] << endl;

		spub.close();
	}
	else {
		ofstream sspub("makehiddenfile.txt", ios::out | ios::app);

		sspub << bookname << "/" << loginedId << "/";
		if (!members.empty()) {
			for (vector<string>::iterator it = members.begin(); it != members.end(); it++) {
				sspub << *it << "/";
			}
		}
		for (int i = 0;i < 8 - members.size();i++) {
			sspub << "x" << "/";
		}
		sspub << "x" << endl;

		sspub.close();
	}
}