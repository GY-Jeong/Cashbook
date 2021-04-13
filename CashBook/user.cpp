#include "user.h"
#include <map>
#include "Windows.h"
#define SIZE 100
user::user() {

}

user::~user() {

}

void user::menu() {
	int sel = 4;
	cout << "1. �α���" << endl;
	cout << "2. ȸ������" << endl;
	cout << "3. ����" << endl;
	cout << "> ";
	
	while (sel < 1 || sel>3) {
		cin >> sel;
		if (sel < 1 || sel>3) {
			cout << "�ٽ� �Է����ּ���" << endl;
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

	//ȸ������ ���� �ҷ�����
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
		cout << "���̵�� ��й�ȣ�� �Է��ϼ���" << endl;
		cout << ">";
		cin.clear();
		while (user::isLoginState==false) {
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
				cout << "�ٽ� �Է����ּ���" << endl;
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
			if (id.size() >= 5 && id.size() <= 12) {//id���� �˻�
				strcpy(idid, id.c_str());
				//cout << idid << endl;
				for (int i = 0;i < strlen(idid);i++) {
					if (idid[i] < 97 || idid[i] > 122) {//id ����ҹ��ڰ˻�
						idfail = true;
					}
				}
				if (idfail == true && user::isLoginState == false) {
					cout << "�ٽ� �Է����ּ���" << endl;
					cout << ">";
					cin.clear();
					continue;
				}
				else {
					if (pw.size() >= 5 && pw.size() <= 12) {//pw���� �˻�
						strcpy(pwpw, pw.c_str());
						//cout << pwpw << endl;
						for (int j = 0;j < strlen(pwpw);j++) {
							if (pwpw[j] < 97 || pwpw[j] > 122) {//pw ����ҹ��ڰ˻�
								pwfail = true;
							}
						}
						if (pwfail == true && user::isLoginState == false) {
							cout << "�ٽ� �Է����ּ���" << endl;
							cout << ">";
							cin.clear();
							continue;
						}
						else {
							//id, pw ���翩�� �˻�
							//id ���� �Ÿ���
							for (int i = 0;i < minfo.size();i++) {
								if (minfo[i].infoId.compare(id) == 0 && minfo[i].infoPw.compare(pw) == 0) {//id ���翩��
									user::isLoginState = true;
									user::loginedId = id;
									//cout << "Log In!!" << endl;
									break;
								}
								diff = true;
							}

							if (diff == true && user::isLoginState == false) {
								cout << "���̵�� ��й�ȣ�� ��ġ�����ʽ��ϴ�." << endl;
								cout << "�ٽ� �Է����ּ���" << endl;
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
						cout << "�ٽ� �Է����ּ���" << endl;
						cout << ">";
						cin.clear();
						continue;
					}
				}
			}
			else {
				cout << "�ٽ� �Է����ּ���" << endl;
				cout << ">";
				cin.clear();
				continue;
			}
		}
		cout << "����� ��������!!" << endl;
		//user::select_Cashbook();
		user::make_CashBook_public();
	}

}

void user::logout() {
	if (user::isLoginState == true) {
		user::isLoginState = false;
		user::loginedId = "";
		cout<<"�α׾ƿ�"<<endl;
	}
	user::menu();
}

void user::quit() {
	user::isQuitState = true;
	cout << "����� ���α׷��� �����մϴ�" << endl;
	exit(0);
}


void user::make_CashBook_public() {
	string bookname;
	string memlist;
	char name[SIZE];
	bool namefail = false;//������̸� ������Ģ ����
	bool namesame = false;//������̸� �ߺ�
	bool nsuccess = false;//���밡��� ��������üũ(����Է��� ������)
	bool memsuccess = false;//����Է� ��������üũ
	bool notmem = false;//ȸ�� �ƴ� ���
	bool manybook = false;//���� ����� ���� 5�� �Ѵ� ���
	bool onemem = false;
	vector<string> members;
	vector<userInfo> meminfo;//ȸ������ id��
	userInfo info;
	vector<pubcash> pubinfo;//���밡����̸�, ���� ����� ��
	pubcash pinfo;
	vector<string> allbook;//����+���� ������̸��鸸 ����

	//ȸ������ ���� �ҷ�����
	ifstream memfile("memberinformation.txt");
	for (userInfo i;getline(memfile, i.infoId, '/') && getline(memfile, i.infoPw);) {
		meminfo.push_back(i);
	}

	//���밡����̸�,����� ���� �ҷ�����->������� ��� ����ü ��ŭ �ȵɰ�� �ƿ� ��������� ��ĭ�� x��
	ifstream pubfile("makehiddenfile.txt");
	for (pubcash i;getline(pubfile, i.pubname, '/') && getline(pubfile, i.maker, '/') && getline(pubfile, i.m1, '/') && getline(pubfile, i.m2, '/') && getline(pubfile, i.m3, '/') && getline(pubfile, i.m4, '/') && getline(pubfile, i.m5, '/') && getline(pubfile, i.m6, '/') && getline(pubfile, i.m7, '/') && getline(pubfile, i.m8, '/') && getline(pubfile, i.m9);) {
		pubinfo.push_back(i);
	}
	
	//����+���� ����� �̸��鸸 ��Ƴ���
	for (int j = 0;j < meminfo.size();j++) {
		allbook.push_back(meminfo[j].infoId);
	}
	for (int j = 0;j < pubinfo.size();j++) {
		allbook.push_back(pubinfo[j].pubname);
	}

	cout << "������ ����� �̸��� �ۼ����ּ���(���ҹ��� �ִ� 5��)" << endl;
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
				if (name[i] < 97 || name[i] > 122) {//������̸� ����ҹ��ڰ˻�
					namefail = true;
				}
			}
			if (namefail == true) {
				cout << "�ٽ� �Է����ּ���" << endl;
				cout << ">";
				continue;
			}
			for (int i = 0;i < allbook.size();i++) {
				if (allbook[i].compare(bookname) == 0) {//������̸� �ߺ����� üũ
					namesame = true;
				}
			}
			if (namesame == true) {
				cout << "�ٽ� �Է����ּ���" << endl;
				cout << ">";
				continue;
			}
			nsuccess = true;
		}
		else {
			cout << "�ٽ� �Է����ּ���" << endl;
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
	cout << "���밡��� ����!!" << endl;
	//��� �Է¹ޱ�
	cout << "�Բ� �� ������� ���̵� �Է����ּ���. (�ִ� 9 ��)" << endl;
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
		
		if (memlist=="x") {//��� �߰� ���� ��� ���͸� ������ ������ �����س���
			onemem = true;
			memsuccess = true;
			break;
		}

		stringstream sss(memlist);
		string token2;
		
		if (memlist.find("/") == string::npos) {//'/'���� �Է�-1���� ������̵�
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

		if (minput.size() > 9) {//9�� �ʰ�
			cout << "�ٽ� �Է����ּ���" << endl;
			cout << ">";
			continue;
		}
		else {//ȸ�������� ���� ���, ���� ����� �̹� 5�� �ִ� ���
			for (int i = 0;i < minput.size();i++) {///ȸ�� ���� Ȯ��
				for (int j = 0;j < meminfo.size();j++) {
					if (minput[i].compare(meminfo[j].infoId) == 0) {
						idcount += 1;
					}
				}
			}
			if (idcount == minput.size()) {
				idcount = 0;
				for (int i = 0;i < minput.size();i++) {///���밡��� 5�� �̻� ���� Ȯ��
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
					cout << "�ٽ� �Է����ּ���" << endl;
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
				cout << "�ٽ� �Է����ּ���" << endl;
				cout << ">";
				continue;
			}
		}
	}
	//��� ���� ���, �ִ� ���(9��, 9�� �̸��� ���-makehiddenfile.txt ������ x�� ä������) ���� ����
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
	//����ΰ��� üũ�� ���� ����ϴ� ���� �ۼ�
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