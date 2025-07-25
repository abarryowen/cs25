#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <functional>
#include <unordered_map>

#include "Ticket.h"
#include "Types.h"
#include "Event.h"
#include "Guest.h"

using namespace std;

// Static variables
int Ticket::nextId = 1;

// Accessors
int Ticket::getSeat() const {
	throw logic_error("Ticket type has no seat");
}

string Ticket::toString() const {

	ostringstream ticket_s;

	// Convert ticket to string
	ticket_s << getId() << "," << static_cast<int>(getType()) << ",";
	ticket_s << fixed << setprecision(2) << getPrice() << "\n";

	return ticket_s.str();
}


// Static methods
void Ticket::setNextId(int _id) {
	nextId = _id;
}

int Ticket::getNextId() {
	return nextId;
}

string Ticket::typeToString(TicketType t) {

	switch (t) {
		case TicketType::Standard:
			return "Standard";
		case TicketType::VIP:
			return "VIP";
		default:
			throw std::invalid_argument("Invalid TicketType");
	}
}

void Ticket::loadGuest(Guest* g) {
	// Only load guest if null
	if (guest == nullptr) {
		guest = g;
	}
	else {
		cout << "Guest already loaded" << endl;
	}
}

void Ticket::loadEvent(Event* e) {
	// Only load event if null
	if (event == nullptr) {
		event = e;
	}
	else {
		cout << "Event already loaded" << endl;
	}
}

TicketPivot Ticket::groupTickets(
	const TicketList& t_list,
	function<int(const Ticket* t)> m_id,
	function<string(const Ticket* t)> m_owner
) {

	TicketPivot t_piv; // Create empty ticket pivot object
	int id;

	for (const Ticket* t : t_list) {
		// Iterate through the ticket list
		
		id = m_id(t); // Get id

		// Add new member if it doesn't exist already
		if (t_piv[id].owner == "") {
			t_piv[id].owner = m_owner(t);
		}

		// Increment ticket count
		t_piv[id].ticketCount[t->getType()] += 1;
		
		// Add seat number
		if (t->hasSeat()) {
			t_piv[id].seats.push_back(t->getSeat());
		}
	}

	return t_piv;
}

void Ticket::printTicketPivot(const TicketPivot& t_piv) {
	
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



