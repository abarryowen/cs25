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
    // Constructor
    Item(string _name, int _quantity) : name(_name), quantity(_quantity) {}

// Accessors
    string getName() const {
        return name;
    }

    int getQuantity() const {
        return quantity;
    }

};

void dispItems(Item* [], int);

int searchItems(Item* [], int, string);

void dispSearch(Item* [], int);

int main()
{
    // Create inventory
    const int SIZE = 3;
    Item* items[SIZE];
    string name;
    int quantity;

    // Populate
    cout << "Please enter inventory items\n";

    for (int i = 0; i < SIZE; i++) {
        // Get name
        cout << "Item " << (i + 1) << endl;
        cout << "Enter name: ";
        getline(cin, name);

        // Get quantity
        cout << "Enter quantity: ";
        cin >> quantity;
        cin.ignore(1, '\n');

        // Create item
        items[i] = new Item(name, quantity);
    }

    // Display
    cout << endl;
    dispItems(items, SIZE);
    cout << endl;

    // Search
    dispSearch(items, SIZE);
    dispSearch(items, SIZE);
    dispSearch(items, SIZE);

    // Clear memory
    for (int i = 0; i < SIZE; i++) {
        delete items[i];
        items[i] = nullptr;
    }
    return 0;
}

// Display items
void dispItems(Item* items[], int size) {
    for (int i = 0; i < size; i++) {
        cout << "Name: " << items[i]->getName() << ", " 
             << "Quantity: " << items[i]->getQuantity() << endl;
    }
}

// Search for given item
int searchItems(Item* items[], int size, string name) {

    for (int i = 0; i < size; i++) {
        if (items[i]->getName() == name) {
            // if item is found then return quantity
            return items[i]->getQuantity();
        }
    }
    // Otherwise retunr -1
    return -1;
}

// Display searched item
void dispSearch(Item* items[], int size) {
    // Get item to search for
    cout << "Enter item: ";
    string name;
    getline(cin, name);

    // Call search items
    int q = searchItems(items, size, name);

    if (q < 0) {
        cout << "Item not found\n";
    }
    else {
        cout << "Name: " << name << ", Quantity: " << q << endl;
    }
}