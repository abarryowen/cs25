#include <iostream>
#include <vector>
#include "Items.h"

using namespace std;

int main() {

	Item item1("Apple", 5);
	Item item2("Towel", 4);
	Item item3("Shirt", 10);

	item1.display();
	item2.display();
	item3.display();

	return 0;
}