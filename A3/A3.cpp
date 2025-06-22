#include <iostream>
using namespace std;

int main()
{
// Part 1 - Menu
    // Welcome message
    cout << "Choose from the following menu:\n";
    cout << "\t1. Add items\n";
    cout << "\t2. Check inventory\n";
    cout << "\t3. Pull items\n";

    // Get user choice
    cout << "Select 1, 2 or 3 as your option: ";
    int choice;
    cin >> choice;

    // Select item from menu
    switch (choice) {
    case 1:
        cout << "Okay, we can go ahead and add items";
        break;

    case 2:
        cout << "Lets check the quantity of items";
        break;

    case 3:
        cout << "Lets grab the items";
        break;

    default:
        cout << "Please select a valid option (1,2 or 3)";
        break;
        
    }

// Part 2 - Largest Number
    // Welcome message
    cout << "\n\nThis program determines the largest of three numbers" << endl;
    
    // Get user data
    cout << "Enter your three numbers: ";
    float a, b, c;
    cin >> a >> b >> c;

    // Find largest
    if (a > b && a > c) {
        cout << a << " is the largest";
    }
    else if (b > a && b > c) {
        cout << b << " is the largest";
    }
    else if (c > a && c > b) {
        cout << c << " is the largest";
    }
    else {
        // Otherwise there is no single largest
        cout << "There is no single largest number";
    }
}

