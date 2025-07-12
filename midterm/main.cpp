#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "ConcertMgr.h"
#include "Ticket.h"

using namespace std;

int main() {

	// Welcome message
	cout << "Welcome to Concert Manager!\n";
	cout << "Here you can create or load a concert and manage the tickets for it\n";
	cout << "When numbered prompts pop up, please enter the number of the option you would like to select\n";

	// Initialize concert manager pointer and select user option
	ConcertMgr* cm = nullptr;
	bool exit_flag = false; // Initialize to false
	int option; // Option

	// User input variables
	string c_name;
	double stdPrice, vipPrice;
	int tickets;

	while (!exit_flag) {
		// Continue prompting user until pick a valid option
		
		// Selection message
		cout << "Would you like to:\n";
		cout << "\t1. Load current concert\n";
		cout << "\t2. Create a new concert\n";
		cout << "\t3. Exit program\n\n";

		cout << "Selection: ";
		cin >> option;

		if (option == 1) {
			// If user selects to load current then open file

			ifstream testOpen("concert_files/concert_mgr.txt");

			if (!testOpen) {
				cout << "There is no current concert, please select again\n\n";
			}
			else {
				testOpen.close();
				cm = new ConcertMgr(); // Load concert
				exit_flag = true;
			}
		}
		else if (option == 2) {
			// If user selects to create new then enter details

			cout << "Please enter concert details\n";
			cout << "Name: ";
			cin.ignore();
			getline(cin, c_name);

			cout << "Standard ticket price: ";
			cin >> stdPrice;

			cout << "VIP ticket price: ";
			cin >> vipPrice;

			cout << "Total available tickets: ";
			cin >> tickets;

			cm = new ConcertMgr(c_name, stdPrice, vipPrice, tickets); // Create concert
			exit_flag = true;
		}
		else if (option == 3) {
			// If user chooses to exit then close
			cout << "Thank you for using Concert Manager, goodbye\n";
			return 0;
		}
		else {
			// Otherwise, they entered an invalid option, have them choose again
			cout << "Please choose a valid option\n\n";
			if (cin.fail()) {
				cin.clear();
				cin.ignore(400, '\n');
			}
		}
	}

	// Homepage message
	cout << "\nHomepage\n";
	exit_flag = false; // Return to false

	string g_name, t_str;
	int t_type, t_quantity, t_id;

	while (!exit_flag) {
		// Continue prompting user until they decide to exit
		
		cout << "Would you like to:\n";
		cout << "\t1. Sell tickets\n";
		cout << "\t2. Search for guest\n";
		cout << "\t3. Print guest list\n";
		cout << "\t4. See concert details\n";
		cout << "\t5. See box office details\n";
		cout << "\t6. Exit program\n\n";

		cout << "Selection: ";
		cin >> option;

		if (option == 1) {
			// User chose to sell tickets

			cout << "Please enter ticket details\n";
			cout << "Guest Name: ";
			cin.ignore();
			getline(cin, g_name);

			cout << "Ticket Type:\n";
			cout << "\t1. Standard\n";
			cout << "\t2. VIP\n\n";
			cout << "Selection: ";
			cin >> t_type;

			cout << "Quantity: ";
			cin >> t_quantity;

			if (t_quantity == 1) {
				t_str = "Standard";
			}
			else {
				t_str = "VIP";
			}

			cout << "\n";
			cm->sellTickets(t_str, g_name, t_quantity);
			cout << "\n";

		}
		else if (option == 2) {
			// User chose to search for ticket id

			cout << "Please enter the ticket ID of the guest you would like to search for\n";
			cout << "Ticket ID: ";
			cin >> t_id;

			cout << "\n";
			cm->searchGuests(t_id);
			cout << "\n";
		}
		else if (option == 3) {
			// User chose to print guest list
			cout << "\n";
			cm->printGuests();
			cout << "\n";
		}
		else if (option == 4) {
			// User chose to print concert details
			cout << "\n";
			cm->printConcert();
			cout << "\n";
		}
		else if (option == 5) {
			// User chose to print box office details
			cout << "\n";
			cm->printBoxOffice();
			cout << "\n";
		}
		else if (option == 6) {
			// User chose to exit
			cout << "\nThank you for using Concert Manager, goodbye\n";
			exit_flag = true;
		}
		else {
			// User chose an invalid option, have them choose again
			cout << "\nPlease choose a valid option\n\n";
			if (cin.fail()) {
				cin.clear();
				cin.ignore(400, '\n');
			}
		}
	}

	// Delete concert manager
	delete cm;
	cm = nullptr;

	return 0;
}