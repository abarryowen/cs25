#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Item {
private:
    string name;
    int quantity;

public:
    // Constructors and destructors
    Item();

    Item(string _name, int _quantity);

    // Accessors
    string getName() const;

    int getQuantity() const;

    void display() const;
};