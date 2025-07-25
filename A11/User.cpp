#include <iostream>
#include <string>
#include "User.h"

using namespace std;

void User::accessLevel() const {
	cout << "General access" << endl;
}

void Employee::accessLevel() const {
	cout << "Employee access" << endl;
}

void InventoryMgr::accessLevel() const {
	cout << "Manager access" << endl;
}