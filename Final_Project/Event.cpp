#include <iostream>
#include <stdexcept>

#include "Types.h"
#include "Ticket.h"
#include "Event.h"
#include "Guest.h"
#include "Venue.h"

using namespace std;

// Forward declarations

// Static variables
int Event::nextId = 1;

// Constructors and destructors
Event::Event(
	string _title, Venue* _venue, int _totalTickets, 
	int _totalSeats, double stdPrice, double vipPrice
)
	: id(nextId++),
	  title(_title),
	  venue(_venue),
	  totalSeats(_totalSeats), 
      reservedSeats(0),
	  unsoldTickets(_totalTickets), 
	  revenue(0),
	  ticketDetails{
		  {TicketType::Standard, TicketInfo(stdPrice)},
	      {TicketType::VIP, TicketInfo(vipPrice)}
	  }
    {}

Event::Event(
	int _id, string _title, double _revenue, int _unsoldTickets,
	int _totalSeats, int _reservedSeats, TicketHash details
)
	: id(_id),
	  title(_title),
	  venue(nullptr),
	  totalSeats(_totalSeats),
	  reservedSeats(_reservedSeats),
	  unsoldTickets(_unsoldTickets),
	  revenue(_revenue),
	  ticketDetails(details)
	  {}

// Accessors
void Event::printEvent() const {
	cout << getTitle() << " at " << getVenue()->getName() << endl
		<< "Tickets Left: " << getUnsoldTickets() << ", Seats Left: " << getOpenSeats() << endl << endl;
}

void Event::printGuests() const {
	// Print header
	cout << "\n--" << title << ": Guests Attending--\n";

	// Create a ticket pivot of event details
	TicketPivot t_piv = Ticket::groupTickets(
		soldTickets,
		[](const Ticket* t) { return t->getGuest()->getId(); },
		[](const Ticket* t) { return t->getGuest()->getName(); }
	);

	Ticket::printTicketPivot(t_piv);
}

const TicketHash& Event::getTicketDetails() const {
	return ticketDetails;
}

bool Event::saleValid(TicketType type, int quantity) const {
	
	bool check_flag = true;

	// Check if there are enough tickets remaining
	if (quantity > unsoldTickets) {
		check_flag = false;
		cout << "Not enough tickets left\n";
	}

	// Check if there are enough seats remaining
	if (type == TicketType::VIP && quantity > getOpenSeats()) {
		check_flag = false;
		cout << "Not enough seats left\n";
	}

	return check_flag;
}

// Mutators
void Event::addTicket(Ticket* t) {
	
	revenue += (t->getPrice()); // Add revenue
	soldTickets.push_back(t); // Add ticket to registry
	unsoldTickets--; // Decrement unsoldtickets


	// Increment reserved seats if vip ticket
	if (t->getType() == TicketType::VIP) {
		reservedSeats++;
	}
}

void Event::loadTicket(Ticket* t) {
	// Only load venue if null
	if (venue == nullptr) {
		soldTickets.push_back(t);
	}
	else {
		cout << "Tickets already loaded" << endl;
	}
}

void Event::loadVenue(Venue* v) {
	// Only load venue if null
	if (venue == nullptr) {
		venue = v;
	}
	else {
		cout << "Venue already loaded" << endl;
	}
}

// Static methods
void Event::setNextId(int id) {
	nextId = id;
}

int Event::getNextId() {
	return nextId;
}