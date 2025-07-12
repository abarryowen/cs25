#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "ConcertMgr.h"
#include "Ticket.h"

using namespace std;

// Constructors and destructors
ConcertMgr::ConcertMgr() {
	loadFromFile();
}

ConcertMgr::ConcertMgr(string _name, double _stdPrice, double _vipPrice, int totalTickets)
	: name(_name),
	  revenue(0),
	  stdPrice(_stdPrice),
	  vipPrice(_vipPrice),
	  remTickets(totalTickets) {}

ConcertMgr::~ConcertMgr() {

	saveToFile(); // Save data to file

	// Delete memory
	for (auto t : soldTickets) {
		delete t;
		t = nullptr;
	}
}


// Accessors
string ConcertMgr::getName() const {
	return name;
}

double ConcertMgr::getRevenue() const {
	return revenue;
}

int ConcertMgr::getRemTickets() const {
	return remTickets;
}

double ConcertMgr::getStdPrice() const {
	return stdPrice;
}

double ConcertMgr::getVipPrice() const {
	return vipPrice;
}

int ConcertMgr::getTotalSold() const {

	int total = 0; // Start at 0

	for (const Ticket* t : soldTickets) {
		total += t->getQuantity();
	}

	return total;
}

void ConcertMgr::printGuests() const {

	// Print guest list
	cout << "Guests List:\n";

	for (const Ticket* t : soldTickets) {
		cout << t->getName() << ", " << t->getType() << "\n";
	}
}

void ConcertMgr::printConcert() const {

	// Print concert name and ticket prices
	cout << "Tonight's Event: " << name << "\n";
	cout << "Standard Tickets: $" << fixed << setprecision(2) << getStdPrice() << "\n";
	cout << "VIP Tickets: $" << fixed << setprecision(2) << getVipPrice() << "\n";
}

void ConcertMgr::printBoxOffice() const {
	
	// Print revenue, tickets sold and remaining tickets
	cout << "Revenue: $" << fixed << setprecision(2) << getRevenue() << "\n";
	cout << "Tickets Sold: " << getTotalSold() << "\n";
	cout << "Remaining Tickets: " << getRemTickets() << "\n";

}

void ConcertMgr::searchGuests(int guestId) const {
	// Initialize min, max and middle indices
	size_t min_index = 0;
	size_t max_index = soldTickets.size() - 1;
	size_t mid_index = max_index / 2;

	bool found = false; // Initialize the found flag to false

	while (!found && min_index <= max_index) {
		// Continue searching while the item has not been found, and is still in bounds

		if (soldTickets[mid_index]->getId() == guestId) {
			// If the middle item is the one being searched for then return it
			found = true;
		}
		else if (soldTickets[mid_index]->getId() > guestId) {
			// If larger then resize down
			max_index = mid_index - 1;
			mid_index = (max_index + min_index) / 2;
		}
		else {
			// Otherwise resize up
			min_index = mid_index + 1;
			mid_index = (max_index + min_index) / 2;
		}
	}

	// Let user know if guest is in attendance
	if (!found) {
		cout << "Guest not in attendance\n" << endl;
	}
	else {
		soldTickets[mid_index]->printTicket();
	}

}

void ConcertMgr::saveToFile() const {

	// Get file
	ofstream outFile("concert_files/concert_mgr.txt");

	// Save concert info
	outFile << "Concert Info\n";
	outFile << getName() << "," << getRevenue() << "," << getStdPrice() << ",";
	outFile << getVipPrice() << "," << getRemTickets() << "," << Ticket::getNextId() << "\n\n";

	// Save ticket sales
	outFile << "Sold Tickets\n";

	for (const Ticket* t : soldTickets) {
		outFile << t->toString();
	}
}


// Mutators
void ConcertMgr::addRevenue(double sale) {
	revenue += sale;
}

bool ConcertMgr::lowerTickets(int quantity) {

	if (quantity <= remTickets) {
		// If quantity is valid then lower
		remTickets -= quantity;
		return true;
	}
	else {
		// Otherwise, return message to user
		cout << "Not enough tickets remaining to complete transaction\n";
		return false;
	}
}

void ConcertMgr::sellTickets(string ticketType, string name, int quantity) {
	
	// Only complete sale if quantity is valid
	if (!lowerTickets(quantity)) {
		return;
	}

	// Create new ticket depending on type selected
	if (ticketType == "VIP") {
		// VIP
		soldTickets.push_back(new VipTicket(Ticket::incNextId(), name, vipPrice, quantity));
		addRevenue(vipPrice);
	}
	else {
		// Standard ticket
		soldTickets.push_back(new StandardTicket(Ticket::incNextId(), name, stdPrice, quantity));
		addRevenue(stdPrice);
	}

}

void ConcertMgr::loadFromFile() {

	ifstream inFile("concert_files/concert_mgr.txt"); // Get file to load from

	string line;
	stringstream values;
	string val;

	getline(inFile, line); // Skip first line

	// Concert data
	getline(inFile, line);
	values.str(line);

	// Set attributes
	getline(values, val, ','); // Name
	name = val;

	getline(values, val, ','); // Revenue
	revenue = stod(val);

	getline(values, val, ','); // Standard ticket price
	stdPrice = stod(val);

	getline(values, val, ','); // VIP ticket price
	vipPrice = stod(val);

	getline(values, val, ','); // Remaining tickets
	remTickets = stoi(val);

	getline(values, val, ','); // Next id for ticket sales
	int nextId = stoi(val);
	Ticket::setNextId(nextId);

	// Ticket data
	getline(inFile, line); // Skip two lines
	getline(inFile, line);

	int t_id;
	string t_type;
	string t_name;
	double t_price;
	int t_quantity;

	while (getline(inFile, line)) {
		// Get current line
		values.clear();
		values.str(line);

		// Save id, type, name, price and quantity
		getline(values, val, ',');
		t_id = stoi(val);

		getline(values, val, ',');
		t_type = val;

		getline(values, val, ',');
		t_name = val;

		getline(values, val, ',');
		t_price = stod(val);

		getline(values, val, ',');
		t_quantity = stoi(val);

		// Create ticket
		if (t_type == "VIP") {
			soldTickets.push_back(new VipTicket(t_id, t_name, t_price, t_quantity));
		}
		else {
			soldTickets.push_back(new StandardTicket(t_id, t_name, t_price, t_quantity));
		}
		
	}

}