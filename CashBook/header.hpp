#pragma once
//#include <bits/stdc++.h>
#include "Check.hpp"

using namespace std;

class Cashbook
{
public:
	void inputTerm();
	void showTotal();
	void searchIncomeCategory();
	void serchPayCategory();
	void searchDetail();
private:
	void deletePublicCashbook();
};

class Cashdata
{
public:
	//void Cashdata();
private:
	string m_date;
	string m_price;
	string m_category_pay;
	string m_category_income;
	string m_memo;
	string m_keyword;
};