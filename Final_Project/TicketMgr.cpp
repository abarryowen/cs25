#include <string>
#include <stdexcept>

#include "TicketMgr.h"
#include "Types.h"
#include "Event.h"
#include "Guest.h"
#include "Ticket.h"

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
}

// Accessors
size_t TicketMgr::numGuests() const {
	return guests.size();
}

size_t TicketMgr::numEvents() const {
	return events.size();
}

GuestList TicketMgr::sortGuests() const {

	GuestList guests_copy = guests;
	bool swap;
	Guest* temp = nullptr;

	// Only sort if there are guests
	if (numGuests() == 0) {
		return guests_copy;
	}

	do {
		swap = false; // Set to false

		// Loop through guests and check for elements out of place
		for (size_t i = 0; i < (numGuests() - 1); i++) {
			if (guests_copy[i]->getUsername() > guests_copy[i + 1]->getUsername()) {
				swap = true; // Set flag to true

				// Swap elements
				temp = guests_copy[i];
				guests_copy[i] = guests_copy[i + 1];
				guests_copy[i + 1] = temp;
			}
		}
	} while (swap);

	return guests_copy;
}

Guest* TicketMgr::searchGuests(string username) const {

	// Check if there are any guests
	if (numGuests() == 0) {
		return nullptr;
	}

	auto g = sortGuests(); // Get copy of guests sorted by username

	// Initialize min, max and middle indices
	int min_index = 0;
	int max_index = static_cast<int>(numGuests()) - 1;
	int mid_index = max_index / 2;

	bool found = false; // Initialize the found flag to false

	while (!found && min_index <= max_index) {
		// Continue searching while the item has not been found, and is still in bounds

		if (g[mid_index]->getUsername() == username) {
			// If the middle item is the one being searched for then return it
			found = true;
		}
		else if (g[mid_index]->getUsername() > username) {
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
		return nullptr;
	}
	else {
		return g[mid_index];
	}
}

EventList TicketMgr::sortEvents() const {

	EventList events_copy = events;
	bool swap;
	Event* temp = nullptr;

	// Only sort if there are guests
	if (numEvents() == 0) {
		return events_copy;
	}

	do {
		swap = false; // Set to false

		// Loop through guests and check for elements out of place
		for (size_t i = 0; i < (numEvents() - 1); i++) {
			if (events_copy[i]->getTitle() > events_copy[i + 1]->getTitle()) {
				swap = true; // Set flag to true

				// Swap elements
				temp = events_copy[i];
				events_copy[i] = events_copy[i + 1];
				events_copy[i + 1] = temp;
			}
		}
	} while (swap);

	return events_copy;
}

Event* TicketMgr::searchEvents(string title) const {

	// Check if there are any guests
	if (numEvents() == 0) {
		return nullptr;
	}

	auto e = sortEvents(); // Get copy of guests sorted by username

	// Initialize min, max and middle indices
	int min_index = 0;
	int max_index = static_cast<int>(numEvents()) - 1;
	int mid_index = max_index / 2;

	bool found = false; // Initialize the found flag to false

	while (!found && min_index <= max_index) {
		// Continue searching while the item has not been found, and is still in bounds

		if (e[mid_index]->getTitle() == title) {
			// If the middle item is the one being searched for then return it
			found = true;
		}
		else if (e[mid_index]->getTitle() > title) {
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
		return nullptr;
	}
	else {
		return e[mid_index];
	}
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

// Mutators
void TicketMgr::addGuest(string username, string firstName, string lastName) {

	// Search for guest in the registry
	Guest* g = searchGuests(username);

	if (g == nullptr) {
		// Only add guest if they don't exist already
		g = new Guest(username, firstName, lastName);
		guests.push_back(g);
		g = nullptr;
	}
	else {
		cout << "An guest with this username already exists\n";
	}
}

void TicketMgr::addEvent(string _title, int totalTickets, int totalSeats, double stdPrice, double vipPrice) {
	// Search for event in the registry
	Event* e = searchEvents(_title);

	if (e == nullptr) {
		// Only add event if it doesn't exist already
		e = new Event(_title, totalTickets, totalSeats, stdPrice, vipPrice);
		events.push_back(e);
		e = nullptr;
	}
	else {
		cout << "An event with this title already exists\n";
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
