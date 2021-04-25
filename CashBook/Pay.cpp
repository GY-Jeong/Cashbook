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
		cout << "< 소비 >" << endl;
		cout << "1. 등록" << endl;
		cout << "2. 삭제" << endl;
		cout << "3. 뒤로가기" << endl;
		INPUT;
		cin >> select;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		switch (select)
		{
		case 1:
			CLEAR;
			cout << "날짜, 금액, 카테고리, 내용을 형식에 맞게 순서대로 입력해주세요." << endl;
			result = data_split1();//split함수 안에서 quit반응이 추가되어야함
			if (result.empty()) continue;

			if (date_test(result[0]) && price_test(result[1]) && pay_category_test(result[2]) && memo_test(result[3])) {
				data_format = Pay::printdata(result);
				//y/n 받는 자리
				cout << "저장 하시겠습니까?";
				if (yesorno()) {
					//yes
					if (!isSharedCashBook) {
						//개인 가계부
						readTextFile(txt_file);							//y->개인 가계부 그냥 저장
						writeTextFile(txt_file, data_format);
						cout << "저장이 완료되었습니다." << endl;
						readTextFile(txt_file);
					}
					else {
						//공용 가계부
						data_format = data_format + "/" + user_id;				//y->공용 가계부 user_id 붙여서 저장
						readTextFile(txt_file);
						writeTextFile(txt_file, data_format);
						cout << "저장이 완료되었습니다." << endl;
						readTextFile(txt_file);
					}
				}
				else {				//n-> 저장 안함
					cout << "저장하지 않습니다." << endl;
				}
				isDataSetting = true; //y/n상관없이 흐름도상 분기로 이동
			}
			result.clear();
			data_format.clear();
			break;
		case 2:
			CLEAR;
			cout << "시작날짜, 종료날짜, 키워드를 형식에 맞게 순서대로 입력해주세요." << endl;
			result = data_split2();
			if (result.empty()) continue;

			if (date_validation(result[0], result[1])) {
				readTextFile(txt_file);
				keyword_search(result[0], result[1], result[2], true);				//맨밑에서 y/n받음
				isDataSetting = true;//y/n 상관없이 흐름도상 분기로 이동
			}
			else {
				cout << "시작일 / 종료일 의미규칙 오류" << endl;
			}
			result.clear();
			break;
		case 3:
			break;
		default:
			cout << "다시 입력해주세요" << endl;
			break;
		}
		if (select == 3) break;
	}
}

string Pay::printdata(vector<string> input)
{
	cout << "날짜 :" << input[0] << endl;
	cout << "금액 :" << input[1] << endl;
	cout << "카테고리 :" << input[2] << endl;
	if (input[3] == "") {
		cout << "내용: 없음" << endl;
		result[3] = '*';
	}
	else
		cout << "내용: " + input[3] << endl;

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
	cout << "카테고리 형식 오류" << endl;
}