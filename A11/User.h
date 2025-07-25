#pragma once

#include <iostream>
#include <string>
#include "User.h"

using namespace std;

class User {
private:
	string name;

public:
	User(string _name) : name(_name) {}

	virtual void accessLevel() const;
};

class Employee: public User {
public:
	Employee(string name) : User(name) {}

	void accessLevel() const override;
};

class InventoryMgr : public Employee {
public:
	InventoryMgr(string name) : Employee(name) {}

	void accessLevel() const override;
};

