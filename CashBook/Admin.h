#pragma once

class Admin {
private:

public:
	Admin(string user_id, string cashbook_name);
	void enrollAdministrator(string cashbook_name);
	void releaseAdministrator(string cashbook_name);

};