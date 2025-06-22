#include <iostream>
using namespace std;

int menuOptions();

void menuChoice(int);

int main()
{
    int choice;

    do {
        // Continue to run until the user chooses to exit

        choice = menuOptions(); // Get menu option
        menuChoice(choice); // Print message

    } while (choice != 3);
    
    return 0;
}

int menuOptions() {
// This functions displays the menu and returns the user choice

    cout << "Choose from the following menu:\n";
    cout << "\t1. Add items\n";
    cout << "\t2. Pull items\n";
    cout << "\t3. Exit menu\n";

    cout << "Enter your choice: ";
    int op;
    cin >> op;

    return op;
}

void menuChoice(int choice) {
// This function prints the choice based on the option chosen from menuOptions
    switch (choice) {
    case 1:
        cout << "Okay, we can go ahead and add items\n\n";
        break;

    case 2:
        cout << "Lets grab the itemss\n\n";
        break;

    case 3:
        cout << "Have a nice day\n\n";
        break;

    default:
        cout << "Please select a valid option (1,2 or 3)\n\n";
        break;

    }
}
