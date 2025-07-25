#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Item abstract class
class Item {
private:
	string name;
	int quantity;

public:
	// Constructor
	Item(string _name, int _quantity)
		: name(_name),
		quantity(_quantity) {
	}

	string getName() const {
		return name;
	}

	int getQuantity() const {
		return quantity;
	}

	virtual ~Item() = default; // Virtual destructor

	virtual void display() const = 0; // Pure virtual for displaying item type
};

// Perishable subclass
class Perishable : public Item {
public:
	// Constructor
	Perishable(string _name, int _quantity) : Item(_name, _quantity) {}

	// Display item type
	void display() const override {
		cout << "Perishable: " << this->getName() << ", Quantity: " << this->getQuantity() << endl;
	}
};

// Non perishable subclass
class NonPerishable : public Item {
public:
	// Constructor
	NonPerishable(string _name, int _quantity) : Item(_name, _quantity) {}

	// Display item type
	void display() const override {
		cout << "Non-Perishable: " << this->getName() << ", Quantity: " << this->getQuantity() << endl;
	}
};

int main()
{
	// Create vector of items
	vector<Item*> items;

	items.push_back(new Perishable("Apple", 3));
	items.push_back(new NonPerishable("Shampoo", 2));

	// Display
	for (const Item* i : items) {
		i->display();
	}

	// Delete memory
	for (Item* i : items) {
		delete i;
		i = nullptr;
		items.pop_back();
	}
}

