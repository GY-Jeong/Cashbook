#include <bits/stdc++.h>
#include "Header.hpp"
#include "Check.hpp"

using namespace std;

vector<string> split(string str, char delimiter);

Check c = Check();

// 조회할 기간을 입력, 입력한 날짜들이 조건에 맞는지 확인.
void Cashbook::inputTerm()
{
	string input;
	cout << "조회할 기간을 입력해주세요(최대 30일)" << endl;
	cin >> input;
	cout << input;
	if (c.validQCheck(input))
	{
		// 뒤로 가기
	}
	else
	{
		// split 함수는 header에 구현
		vector<string> dates = split(input, '/');
		// '/'로 구분된 string이 2개이고, 2개의 string 모두 유효한 날짜 데이터일 때
		if (dates.size() == 2 && c.validDateCheck(dates[0]) && c.validDateCheck(dates[1]))
		{

		}
		// 오류 출력
		else
		{

		}
	}
}

// 총 수입과 지출을 보여줌.
void Cashbook::showTotal()
{

}

// 수입 카테고리별 수입을 보여줌.
void Cashbook::searchIncomeCategory()
{

}

// 지출 카테고리별 지출을 보여줌.
void Cashbook::serchPayCategory()
{

}

// 입력 받은 '상세 내역을 조회할 카테고리'의 상세 내역을 보여줌.
void Cashbook::searchDetail()
{

}

void Cashbook::deletePublicCashbook()
{

}

vector<string> split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str);
	string temp;

	while (getline(ss, temp, delimiter)) {
		internal.push_back(temp);
	}

	return internal;
}
