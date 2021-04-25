#pragma once

#include "CashData.h"
#include "Pay.h"
#include "Income.h"

using namespace std;

class Cashbook
{
public:
	Cashbook(string user_id, string cashbook_name, bool isSharedCashBook);
	cashData cd;
	void menu();
	bool isSharedCashBook;
	string user_id;
	string cashbook_name;
	void startSearch();
	void showTotal(string start_date, string end_date);
	void searchIncomeCategory(string start_date, string end_date, vector<vector<string>> income_list);
	void searchPayCategory(string start_date, string end_date, vector<vector<string>> pay_list);
	void searchDetail(string start_date, string end_date, string categoty_name, vector<vector<string>> category_list, vector<vector<string>> total_list, \
		bool is_pay);
	void modify_hidden_file();
	int getAuthority(string cashbook_name, string user_id);
private:
	int user_authority;
	bool deletePublicCashbook();
};