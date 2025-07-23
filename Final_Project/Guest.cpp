#include <iostream>
#include <sstream>
#include <string>
#include <functional>

#include "Ticket.h"
#include "Event.h"
#include "Guest.h"
#include "Types.h"

using namespace std;

// Static variables
int Guest::nextId = 1;

// Constructors
Guest::Guest(string _username, string firstName, string lastName)
	: id(nextId++),
	  username(_username),
	  name(firstName + " " + lastName) {}

// Accessors
void Guest::printGuest() const {
	cout << "Name: " << getName() << endl
		<< "Username: " << getUsername() << endl;
}

void Guest::printEvents() const {
	// Print header
	cout << "\n--" << name << ": Events Attended--\n";

	// Create a ticket pivot for getting event details
	TicketPivot t_piv = Ticket::groupTickets(
		purchasedTickets,
		[](const Ticket* t) { return t->getEvent()->getId(); }, // Return id
		[](const Ticket* t) { return t->getEvent()->getTitle(); } // Return title
	);

	stringstream ss;
	bool first_flag; // Determines if commas are needed

	// Print info
	for (const auto& op : t_piv) {
		ss << (op.second).owner << endl; // Title

		// Print ticket counts
		first_flag = true;

		for (const auto& ip : op.second.ticketCount) {
			if (!first_flag) { ss << ", "; }

			ss << "x" << ip.second << " "
			   << Ticket::typeToString(ip.first) << " Ticket(s)"; 

			first_flag = false;
		}
		
		auto& seats = op.second.seats; // Get seats list
		bool seats_flag = (seats.size() != 0); // See if there are seats

		if (seats_flag) {
			// Print seat info if it exists

			ss << endl << "Seats Reserved ";

			first_flag = true;
			for (auto i : seats) {
				if (!first_flag) { ss << ", "; }
				ss << i;

				first_flag = false;
			}
		}
		
		cout << ss.str() << endl << endl; // Print string
		ss.str(""); // Clear
	}
}

// Mutators
void Guest::addTicket(Ticket* t) {
	purchasedTickets.push_back(t);
}

// Static methods
void Guest::setNextId(int id) {
	nextId = id;
}