#include <iostream>
#include <vector>
#include <string>
#include "Items.h"

using namespace std;


Item::Item() : name(""), quantity(0) {}

Item::Item(string _name, int _quantity) : name(_name), quantity(_quantity) {}

// Accessors
string Item::getName() const {
    return name;
}

int Item::getQuantity() const {
    return quantity;
}

void Item::display() const {
    cout << "Name: " << getName() << ", "
        << "Quantity: " << getQuantity() << endl;
}