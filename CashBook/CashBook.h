#pragma once

#include "CashData.h"
#include "Pay.h"
#include "Income.h"

using namespace std;

class Cashbook
{
public:
	void inputTerm(string user_id);
	void showTotal(string user_id, string start_date, string end_date);
	void searchIncomeCategory(string user_id, string start_date, string end_date, vector<Income> IncomeList);
	void searchPayCategory(string user_id, string start_date, string end_date, vector<Pay> PayList);
	void searchDetail(string categoty_name, vector<cashData> category_list);
private:
	void deletePublicCashbook(string txt_name);
};