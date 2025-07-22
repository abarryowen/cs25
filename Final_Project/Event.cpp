#include <iostream>
#include <stdexcept>

#include "Types.h"
#include "Ticket.h"
#include "Event.h"
#include "Guest.h"

using namespace std;

// Forward declarations

// Static variables
int Event::nextId = 1;

// Constructors and destructors
Event::Event(string _title, int totalTickets, int _totalSeats, double stdPrice, double vipPrice)
	: id(nextId++),
	  title(_title),
	  totalSeats(_totalSeats), 
      reservedSeats(0),
	  unsoldTickets(totalTickets), 
	  revenue(0),
	  ticketDetails{
		  {TicketType::Standard, TicketInfo(stdPrice)},
	      {TicketType::VIP, TicketInfo(vipPrice)}
	  }
    {}

Event::~Event() {
	for (Ticket*& t : soldTickets) {
		delete t;
		t = nullptr;
	}
}

// Accessors
int Event::getId() const {
	return id;
}

string Event::getTitle() const {
	return title;
}

int Event::getUnsoldTickets() const {
	return unsoldTickets;
}

int Event::getNextSeat() const {
	return reservedSeats + 1;
}

int Event::getOpenSeats() const {
	return totalSeats - reservedSeats;
}

void Event::printEvent() const {
	cout << "Title: " << getTitle() << endl
		<< "ID: " << getId() << endl
		<< "Tickets Remaining: " << getUnsoldTickets() << endl
		<< "Seats Remaining: " << getOpenSeats() << endl
		<< "Revenue: " << revenue << endl << endl;
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

const TicketInfo& Event::getTicketInfo(TicketType type) const {
	return ticketDetails.at(type);
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
	
	addRevenue(t->getPrice()); // Add revenue
	soldTickets.push_back(t); // Add ticket to registry
	unsoldTickets--; // Decrement unsoldtickets


	// Increment reserved seats if vip ticket
	if (t->getType() == TicketType::VIP) {
		reservedSeats++;
	}
}

void Event::addRevenue(double amount) {

	// Add revenue if amount is positive
	if (amount >= 0) {
		revenue += amount;
	}
	else {
		throw std::invalid_argument("Revenue amount cannot be negative");
	}
}

// Static methods
void Event::setNextId(int id) {
	nextId = id;
}