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
        cout << "Okay, we can go ahead and add items\n";
        break;

    case 2:
        cout << "Lets check the quantity of items\n";
        break;

    case 3:
        cout << "Lets grab the items\n";
        break;

    default:
        cout << "Please select a valid option (1,2 or 3)\n";
        break;
        
    }

// Part 2 - Largest Number
    float n1, n2, n3;

    cout << "Enter three numbers: ";
    cin >> n1 >> n2 >> n3;

    if (n1 == n2 && n1 >= n3) 
    {
        cout << "Largest number: " << n1;
    }
        

    if (n2 == n1 && n2 >= n3)
    {
        cout << "Largest number: " << n2;
    }

    if (n3 >= n1 && n3 >= n2)
    {
        cout << "Largest number: " << n3;
    }

    return 0;

}

