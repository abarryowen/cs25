#include <string>
#include <stdexcept>

#include "Types.h"
#include "Utils.h"
#include "TicketMgr.h"
#include "Event.h"
#include "Guest.h"
#include "Ticket.h"
#include "Venue.h"

using namespace std;

// Forward declarations

// Static variables

// Constructors and destructors
TicketMgr::TicketMgr() = default;

TicketMgr::~TicketMgr() {
	for (Guest*& g : guests) {
		delete g; 
		g = nullptr;
	}

	for (Event*& e : events) {
		delete e; 
		e = nullptr;
	}

	for (Venue*& v : venues) {
		delete v;
		v = nullptr;
	}
}

// Accessors
size_t TicketMgr::numGuests() const {
	return guests.size();
}

size_t TicketMgr::numEvents() const {
	return events.size();
}

Guest* TicketMgr::searchGuests(string username) const {

	Guest* g_ptr = utils::searchPtrs(
		guests,
		[](const Guest* g) { return g->getUsername(); },
		username
	);

	return g_ptr;
}

Event* TicketMgr::searchEvents(string title) const {

	Event* e_ptr = utils::searchPtrs(
		events,
		[](const Event* e) { return e->getTitle(); }, 
		title
	);

	return e_ptr;
}

Venue* TicketMgr::searchVenues(string name) const {

	Venue* v_ptr = utils::searchPtrs(
		venues,
		[](const Venue* v) { return v->getName(); },
		name
	);

	return v_ptr;
}

void TicketMgr::printGuests() const {

	cout << "\n-----Guests-----\n\n";;

	// Print username and name
	for (Guest* g : guests) {
		g->printGuest();
		cout << endl;
	}
}

void TicketMgr::printEvents() const {

	cout << "\n-----Events-----\n\n";

	// Print title and ticket info
	for (Event* e : events) {
		e->printEvent();
		cout << endl;
	}
}

void TicketMgr::printVenues() const {

	cout << "\n-----Venues-----\n\n";

	// Print title and ticket info
	for (Venue* v : venues) {
		v->printVenue();
		cout << endl;
	}
}

// Mutators
void TicketMgr::addGuest(string username, string firstName, string lastName) {

	// Search for guest in the registry
	Guest* g = searchGuests(username);

	if (g == nullptr) {
		// Only add guest if they don't exist already
		g = new Guest(username, firstName, lastName);
		guests.push_back(g);
	}
	else {
		cout << "An guest with this username already exists\n";
	}
}

void TicketMgr::addEvent(string title, Venue* venue, int totalTickets, int totalSeats, double stdPrice, double vipPrice) {
	// Search for event in the registry
	Event* e = searchEvents(title);

	if (e == nullptr) {
		// Only add event if it doesn't exist already
		e = new Event(title, venue, totalTickets, totalSeats, stdPrice, vipPrice);
		events.push_back(e);

		venue->addEvent(e); // Add to venue
	}
	else {
		cout << "An event with this title already exists\n";
	}

}

void TicketMgr::addVenue(string _name) {

	//Search for guest in the registry
	Venue* v = searchVenues(_name);

	if (v == nullptr) {
		// Only add guest if they don't exist already
		v = new Venue(_name);
		venues.push_back(v);
	}
	else {
		cout << "An venue with this name already exists\n";
	}
}

void TicketMgr::sellTickets(Guest* g, Event* e, TicketType type, int quantity) {
	
	// Check if guest and event are valid
	if (g == nullptr) {
		cout << "Guest missing\n";
		return;
	}
	else if (e == nullptr) {
		cout << "Event missing\n";
		return;
	}

	// Check the sale is valid
	if (!e->saleValid(type, quantity)) {
		return;
	}

	// Get the price of given ticket type
	double price = e->getTicketInfo(type).price;
	Ticket* t = nullptr;

	// Create new tickets
	for (int i = 0; i < quantity; i++) {
		switch (type) {
		case TicketType::Standard:
			t = new StandardTicket(g, e, price);
			break;
		case TicketType::VIP:
			t = new VipTicket(g, e, price, e->getNextSeat());
			break;
		default:
			// Throw exception if invalid ticket type passed
			cout << "Invalid ticket type entered\n";
			throw std::invalid_argument("Invalid TicketType");
		}

		g->addTicket(t); // Add the ticket to guest
		e->addTicket(t); // Add ticket to event
	}

	t = nullptr;
}
