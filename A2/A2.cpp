#include <iostream>
#include <string>
using namespace std;

int main()
{
    string item_name;
    int quantity;
    float cost;

    // Intro message
    cout << "This program calculates the total cost for a given amount of the chosen item" << endl;
    
    // Get data
    cout << "Enter item name: ";
    getline(cin, item_name);

    cout << "Enter item cost: ";
    cin >> cost;

    cout << "Enter quantity of item: ";
    cin >> quantity;

    // Calculate and display total cost
    float total_cost = cost * quantity;

    cout << "The total cost of " << quantity << " units of " << item_name << " is " << total_cost << endl;

    return 0;
}

