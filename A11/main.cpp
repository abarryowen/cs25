#include <iostream>
#include <string>
#include "User.h"

using namespace std;

int main() {

	User* u;

	u = new InventoryMgr("Teddy");
	u->accessLevel();

	delete u;
	u = nullptr;

	return 0;
}