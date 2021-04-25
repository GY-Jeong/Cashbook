#pragma once

class Admin {
public:
	Admin(string user_id, string cashbook_name);
	void enrollAdministrator(string cashbook_name);
	void releaseAdministrator(string cashbook_name);
	vector<string> makeList(string cashbook_name, int authority);
	void changeAuthority(string cashbook_name, vector<string> user_list, int authority);
};