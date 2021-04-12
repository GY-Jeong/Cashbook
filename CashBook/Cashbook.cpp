#include "CashBook.h"
#include "CashData.h"
#include "Pay.h"
#include "Income.h"

using namespace std;

vector<string> split(string str, char delimiter);

// Check c = Check();

// 조회할 기간을 입력, 입력한 날짜들이 조건에 맞는지 확인.
void Cashbook::inputTerm(string user_id)
{
InputRetry:
	string input;
	cout << "조회할 기간을 입력해주세요(최대 30일)" << endl;
	cin >> input;
	cout << input;
	if (validQCheck(input))
	{
		// 뒤로 가기

		return;
	}
	else
	{
		vector<string> dates = split(input, '/');
		// '/'로 구분된 string이 2개이고, 2개의 string 모두 유효한 날짜 데이터일 때
		if (dates.size() == 2 && validDateCheck(dates[0]) && validDateCheck(dates[1]))
		{
			// 의미규칙, 30일 사이이고, dates[1]이 dates[0]보다 뒤일때)
			if ()
			{
				showTotal(user_id, dates[0], dates[1]);
				return;
			}
			else goto InputError;
		}
		// 오류 출력
		else
		{
		InputError:
			cout << "입력 형식 오류" << endl;
			//이렇게 하면 오류메시지 안쌓일텐데 여기서 console clear해주면
			goto InputRetry;
		}
	}
}

// 총 수입과 지출을 보여줌.
void Cashbook::showTotal(string user_id, string start_date, string end_date)
{
ShowRetry:
	unsigned int input, total_income_price, total_pay_price;
	vector<Income> IncomeList;
	vector<Pay> PayList;
	// start date부터 end date까지 순회하며 리스트에 저장
	cout << "사용자 ID : " << user_id << endl;
	cout << start_date << " ~ " << end_date << " 해당 기간 내역입니다." << endl;
	cout << "총 지출 : " << total_pay_price << " 총 수입 : " << total_income_price << endl;
	cout << "1. 수입" << endl;
	cout << "2. 지출" << endl;
	cout << "3. 뒤로가기" << endl;
	cout << "조회하실 카테고리 유형을 선택해주세요." << endl;
	cin >> input;
	switch (input) {
	case 1:
		searchIncomeCategory(user_id, start_date, end_date, IncomeList);
		break;
	case 2:
		serchPayCategory(user_id, start_date, end_date, PayList);
		break;
	case 3:
		inputTerm(user_id);
		break;
	default:
		cout << "입력 형식 오류" << endl;
		break;
	}
}

// 수입 카테고리별 수입을 보여줌.
void Cashbook::searchIncomeCategory(string user_id, string start_date, string end_date, vector<Income> IncomeList)
{
	string input;
	unsigned int income_total_money = 0;
	vector<unsigned int> category_income_total_money(5);
	for (cashData element : IncomeList)
	{
		// price의 형식이 string(,포함)이고, private이라 외부 접근 불가
		// 의논 필요
		income_total_money += stoi(element.m_price);
	}
	cout << "사용자 ID : " << user_id << endl;
	cout << start_date << " ~ " << end_date << " 해당 기간 내역입니다." << endl;
	cout << "총 수입 : " << income_total_money << endl;
	cout << "1. 월급       " << endl;
	cout << "2. 용돈       " << endl;
	cout << "3. 인센티브   " << endl;
	cout << "4. 아르바이트 " << endl;
	cout << "5. 기타       " << endl;
	cout << "상세 내역을 확인하시려면 카테고리 번호를 선택해주세요." << endl;
	cin >> input;

	if (validQCheck(input))
	{
		showTotal(user_id, start_date, end_date);
	}
	else if (validNumberRange(input, 1, 5))
	{
		serchDetail(pay_category[stoi(input) - 1], );
	}
	else
	{

	}
	return;
}

// 지출 카테고리별 지출을 보여줌.
void Cashbook::serchPayCategory(string user_id, string start_date, string end_date, vector<Pay> PayList)
{
	string input;
	vector<cashData> category_paylist[7];
	for (cashData element : PayList)
	{
		element
	}
	cout << "사용자 ID : " << user_id << endl;
	cout << start_date << " ~ " << end_date << " 해당 기간 내역입니다." << endl;
	cout << "총 지출 : " << endl;
	cout << "1. 식비       " << endl;
	cout << "2. 교통       " << endl;
	cout << "3. 문화       " << endl;
	cout << "4. 오락       " << endl;
	cout << "5. 편의점     " << endl;
	cout << "6. 카페       " << endl;
	cout << "7. 기타       " << endl;
	cout << "상세 내역을 확인하시려면 카테고리 번호를 선택해주세요." << endl;
	cin >> input;

	if (validQCheck(input))
	{

	}
	else if (validNumberRange(input, 1, 7))
	{
		serchDetail(pay_category[stoi(input) - 1], );
		return;
	}
}

// 입력 받은 '상세 내역을 조회할 카테고리'의 상세 내역을 보여줌.
void Cashbook::searchDetail(string categoty_name, vector<cashData> category_list)
{
	cout << categoty_name << "의 상세 내역입니다." << endl;
	for (cashData element : category_list)
	{
		cout << element.m_date << " " << element.m_price << " " element.m_memo << endl;
	}
	cout << "메인 메뉴로 돌아가시겠습니까? (Y/N or y/n)"
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
