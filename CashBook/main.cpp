#include "CashBook.h"
#include "CashData.h"
#include "Pay.h"
#include "Income.h"
#include "Check.hpp"

using namespace std;

int main()
{
	string cashbook_name = "temp_cashbook";
	Cashbook element = Cashbook();
	cashData cd;
	cd.menu(false);
	string user_id = "user_id";
	element.inputTerm(user_id);
}