#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>

#include "Types.h"
#include "TicketMgr.h"
#include "Guest.h"
#include "Event.h"
#include "Venue.h"
#include "Ticket.h"

using namespace std;

void welcomeMessage();
void mainMenu();
void guestMenu();
void venueMenu();
void adminMenu();
void invalidOption();

int main() {

	// Initialize ticket manager and load data from file
	TicketMgr* tm = new TicketMgr();
	bool exit_flag = false; // Initialize to false
	bool save_flag = true; // Determines if the data should load to file
	int option; // For user options
	
	welcomeMessage(); // Welcome message

	while (!exit_flag) {
		// Continue prompting user until they decide to exit

		mainMenu(); // Main menu options

		cout << "Selection: ";
		cin >> option;

		if (option == 1) {
			// Add guest
			string username, firstName, lastName;

			// Get guest details
			cout << "Please enter guest details\n";
			
			cout << "First Name: ";
			cin.ignore();
			getline(cin, firstName);

			cout << "Last Name: ";
			getline(cin, lastName);

			cout << "Username: ";
			getline(cin, username);

			if (tm->searchGuests(username) != nullptr) {
				// Check if already taken
				cout << "This username is already taken, returning to main menu\n\n";
				continue;
			}

			tm->addGuest(username, firstName, lastName); // Add
			cout << "Guest added!\n\n";

		}
		else if (option == 2) {
			// Add venue
			string name;

			// Get venue details
			cout << "Please enter venue details\n";

			cout << "Name: ";
			cin.ignore();
			getline(cin, name);

			if (tm->searchVenues(name) != nullptr) {
				// Check if already taken
				cout << "This name is already taken, returning to main menu\n\n";
				continue;
			}

			tm->addVenue(name); // Add
			cout << "Venue added!\n\n";
		
		}
		else if (option == 3) {
			// Act on behalf of guest

			// Get username
			cout << "Enter guest username: ";

			string username;
			cin.ignore();
			getline(cin, username);

			// Find guest
			Guest* g = tm->searchGuests(username);

			if (g == nullptr) {
				// Check if valid
				cout << "Invalid username, returning to main menu\n\n";
				continue;
			}

			// Guest submenu options
			bool exit_guest = false;
			int option_guest;

			while (!exit_guest) {
				// Display menu
				guestMenu();

				cout << "Selection: ";
				cin >> option_guest;

				if (option_guest == 1) {
					tm->printEvents(); // Show events
				}
				else if (option_guest == 2) {
					// Purchase ticket

					// Get event
					cout << "Enter event title you would like to attend: ";

					string title;
					cin.ignore();
					getline(cin, title);

					Event* e = tm->searchEvents(title);

					if (e == nullptr) {
						// Check if valid
						cout << "Invalid event, returning to guest menu\n";
						continue;
					}

					// Print event details
					e->printEvent();

					// Get ticket details
					// Type
					cout << "Which ticket type would you like to purchase (enter number)?\n";
					cout << "\t1. Standard\n";
					cout << "\t2. VIP\n\n";
					cout << "Selection: ";
					int type;
					cin >> type;

					// Quantity
					cout << "Enter quantity: ";
					int quantity;
					cin >> quantity;

					if (quantity <= 0 || type < 1 || type > 2) {
						// Check sale is valid
						cout << "Invalid ticket details, returning to guest menu\n";
						continue;
					}

					tm->sellTickets(g, e, static_cast<TicketType>(type), quantity); // Sell
					cout << "Tickets purchased!\n\n";

				}
				else if (option_guest == 3) {
					g->printEvents(); // Show guest events

				}
				else if (option_guest == 4) {
					exit_guest = true; // Exit

				}
				else {
					// User chose an invalid option, have them choose again
					invalidOption();
				}
			}
			
		}
		else if (option == 4) {
			// Act on behalf of venue
			
			// Get name
			cout << "Enter venue name: ";

			string name;
			cin.ignore();
			getline(cin, name);

			// Find guest
			Venue* v = tm->searchVenues(name);

			if (v == nullptr) {
				// Check if valid
				cout << "Invalid name, returning to main menu\n\n";
				continue;
			}

			// Guest submenu options
			bool exit_venue = false;
			int option_venue;

			while (!exit_venue) {
				// Display menu
				venueMenu();

				cout << "Selection: ";
				cin >> option_venue;

				if (option_venue == 1) {
					// Add event

					string title;
					int tickets, seats;
					double stdPrice, vipPrice;

					// Get guest details
					cout << "Please enter event details\n";

					cout << "Title: ";
					cin.ignore();
					getline(cin, title);

					if (v->searchEvents(title) != nullptr) {
						// Check if already taken
						cout << "This name is already taken, returning to main menu\n\n";
						continue;
					}

					cout << "Total tickets: ";
					cin >> tickets;

					cout << "Total seats available for reservation (enter 0 if none): ";
					cin >> seats;

					cout << "Standard ticket price: ";
					cin >> stdPrice;

					cout << "VIP ticket price (enter 0 if no available seats): ";
					cin >> vipPrice;

					if (tickets <= 0 || seats < 0 || stdPrice <= 0 || vipPrice < 0) {
						// Check sale is valid
						cout << "Invalid event details, returning to guest menu\n\n";
						continue;
					}

					tm->addEvent(title, v, tickets, seats, stdPrice, vipPrice); // Add
					cout << "Event added!\n\n";

				}
				else if (option_venue == 2) {
					// See events
					v->printEvents();
				}
				else if (option_venue == 3) {
					// See revenue
					cout << "Total Revenue: " << v->getRevenue() << endl << endl;
				}
				else if (option_venue == 4) {
					exit_venue = true; // Exit
				}
				else {
					// User chose an invalid option, have them choose again
					invalidOption();
				}
			}
			
		}
		else if (option == 5) {
			// See admin options

			bool exit_admin = false;
			int option_admin;

			while (!exit_admin) {
				// Show menu
				adminMenu();

				// Get selection
				cout << "Selection: ";
				cin >> option_admin;

				if (option_admin == 1) {
					tm->printGuests();
				}
				else if (option_admin == 2) {
					tm->printVenues();
				}
				else if (option_admin == 3) {
					cout << "This will clear all data and end the program.\n" 
						 << "Are you sure you want to continue?\n"
						 << "\t1. Yes\n"
						 << "\t2. No\n\n"
						 << "Selection: ";

					int choice;
					cin >> choice;

					if (choice == 1) {
						tm->overrideFile();
						save_flag = false;
						exit_admin = true;
						exit_flag = true;

						cout << "\nThank you for using Ticket Manager, goodbye\n";
					}
					
				}
				else if (option_admin == 4) {
					exit_admin = true;
				}
				else {
					// User chose an invalid option, have them choose again
					invalidOption();
				}
			}
		}
		else if (option == 6) {
			// Exit program
			cout << "\nThank you for using Ticket Manager, goodbye\n";
			exit_flag = true;
		}
		else {
			// User chose an invalid option, have them choose again
			invalidOption();
		}
	}

	// Save and delete
	if (save_flag) {
		tm->saveAll();
	}
	
	delete tm;
	tm = nullptr;

	return 0;
}



/// <summary>Display welcome message</summary>
void welcomeMessage() {
	cout << "Welcome to Ticket Manager!\n"
	     << "Here you can add venues that hold events, and guests who want to attend those events.\n"
		 << "From there, you can facilitate buying tickets, and looking at box office data.\n\n"
		 << "When numbered prompts pop up, please enter the number of the option you would like to select\n";
}

/// <summary>Display main menu</summary>
void mainMenu() {
	cout << "Would you like to?\n"
		<< "\t1. Add guest\n"
		<< "\t2. Add venue\n"
		<< "\t3. Act on behalf of guest\n"
		<< "\t4. Act on behalf of venue\n"
		<< "\t5. See admin options\n"
		<< "\t6. Exit program\n\n";
}

/// <summary>Display guest submenu</summary>
void guestMenu() {
	cout << "Would you like to?\n"
		 << "\t1. See upcoming events\n"
		 << "\t2. Purchase tickets\n"
		 << "\t3. See your events\n"
		 << "\t4. Exit guest\n\n";
}

/// <summary>Display venue submenu</summary>
void venueMenu() {
	cout << "Would you like to?\n"
		 << "\t1. Add event\n"
		 << "\t2. See events for this venue\n"
		 << "\t3. See revenue\n"
		 << "\t4. Exit venue\n\n";
}

/// <summary>Display admin submenu</summary>
void adminMenu() {
	cout << "Would you like to?\n"
		 << "\t1. See all guests\n"
		 << "\t2. See all venues\n"
		 << "\t3. Clear all data\n"
		 << "\t4. Exit admin\n\n";
}

/// <summary>Actions for invalid option</summary>
void invalidOption() {
	cout << "\nPlease choose a valid option\n\n";
	if (cin.fail()) {
		cin.clear();
		cin.ignore(400, '\n');
	}
}


/*
// Get for sub menu
			bool exit_guest = false;
			int option_guest;

			while (!exit_guest) {
				if (option == 1) {

				}
				else if (option == 2) {

				}
				else if (option == 2) {
					exit = true;
				}
				else {
					// User chose an invalid option, have them choose again
					invalidOption();
				}
			}
*/

//// Load file data
//ifstream loadFile("tm_data.json");

//if (!loadFile.is_open()) {
//	// Check file is valid
//	throw std::runtime_error("File does not exist");
//}

//json jData;
//loadFile >> jData;
//loadFile.close();

//tm.loadAll();

//tm.printEvents();
//tm.printGuests();
//tm.printVenues();

//Guest* g = tm.searchGuests("jseinfeld11");
//Guest* f = tm.searchGuests("elaine78");

//Event* d = tm.searchEvents("Cooking Class");
//Event* e = tm.searchEvents("Music Festival");

//Venue* v = tm.searchVenues("Planterie");
//Venue* u = tm.searchVenues("Oracle Park");

//g->printEvents();
//f->printEvents();

//v->printEvents();
//e->printGuests();

//------TEST LOAD----------------------------------
	// Load file data
	//ifstream loadFile("tm_data.json");

	//if (!loadFile.is_open()) {
	//	// Check file is valid
	//	throw std::runtime_error("File does not exist");
	//}

	//json jData;
	//loadFile >> jData;
	//loadFile.close();

	//// load venues test
	//unordered_map<int, Venue*> vLoad = tm.loadVenues(jData["venues"]);

	//for (auto& it : vLoad) {
	//	cout << it.first << " " << it.second->getName();

	//	cout << endl;
	//}

	//cout << endl << endl;

	//tm.numTest();

	//// load tickets test
	//unordered_map<int, Ticket*> tLoad = tm.loadTickets(jData["tickets"]);

	//for (auto& it : tLoad) {
	//	cout << it.first << " " << it.second->getPrice()
	//		<< " " << static_cast<int>(it.second->getType());

	//	cout << endl;
	//}

	//cout << endl << endl;

	//tm.testTickets();

	// load events test
	//vector<load::EventLoad> eLoad = tm.loadEvents(jData["events"]);

	//for (auto& it : eLoad) {
	//	cout << it.event->getId() << " " << it.event->getTitle() << endl;

	//	for (auto& i : it.ticketIds) {
	//		cout << i << ", ";
	//	}
	//	cout << endl;

	//	cout 
	//		<< "Tickets Left: " << it.event->getUnsoldTickets() << ", Seats Left: " << it.event->getOpenSeats() << endl
	//		<< "Revenue Test: " << it.event->getRevenue() << endl << endl;
	//}

	//cout << endl << endl;

	//tm.numTest();

	//// load guests test
	//unordered_map<int, load::GuestLoad> gLoad = tm.loadGuests(jData["guests"]);

	//for (auto& it : gLoad) {
	//	cout << it.first << " " << it.second.guest->getName() << " ";
	//	for (auto& i : it.second.ticketIds) {
	//		cout << i << ", ";
	//	}

	//	cout << endl;
	//}

	//cout << endl << endl;

	//tm.printGuests();

//--------END-----------------

	//tm.addGuest("jseinfeld11", "Jerry", "Seinfeld");
	//tm.addGuest("elaine78", "Elaine", "Benes");
	//tm.addGuest("jconst123", "George", "Costanza");
	//tm.addGuest("cosmos78", "Cosmo", "Kramer");

	//tm.addVenue("Planterie");
	//tm.addVenue("Oracle Park");

	//Venue* v = tm.searchVenues("Planterie");
	//Venue* u = tm.searchVenues("Oracle Park");

	//tm.addEvent("Music Festival", u, 200, 20, 10, 20);
	//tm.addEvent("Sculpy Event", v, 10, 5, 10, 20);
	//tm.addEvent("Cooking Class", v, 20, 0, 10, 0);
	//
	//// Test abstract functions

	////Test purchasing tickets
	//Guest* g = tm.searchGuests("jseinfeld11");
	//Guest* f = tm.searchGuests("elaine78");

	//Event* d = tm.searchEvents("Cooking Class");
	//Event* e = tm.searchEvents("Music Festival");

	//tm.sellTickets(g, e, TicketType::Standard, 3);
	//tm.sellTickets(g, e, TicketType::Standard, 1);
	//tm.sellTickets(g, e, TicketType::VIP, 1);
	//tm.sellTickets(f, e, TicketType::VIP, 5);
	//tm.sellTickets(g, d, TicketType::Standard, 2);

	//tm.saveAll();


	//g->printEvents();
	//f->printEvents();

	//v->printEvents();
	//e->printGuests();

	//cout << endl;
	//e->printEvent();