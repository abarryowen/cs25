#include <string>
#include <iostream>
#include <stdexcept>

#include "Types.h"
#include "Utils.h"
#include "Venue.h"
#include "Event.h"

using namespace std;


// Static variables
int Venue::nextId = 1;


// Accessors
void Venue::printVenue() const {
	cout << "Name: " << getName() << endl
		<< "Total Events: " << events.size() << endl
		<< "Total Revenue: " << getRevenue() << endl << endl;
}

void Venue::printEvents() const {

	cout << "\n--" << name << ": Events--\n";

	// Print title and ticket info
	for (Event* e : events) {
		cout << e->getTitle() << " at " << getName() << endl
			 << "Tickets Left: " << e->getUnsoldTickets() << ", Seats Left: " << e->getOpenSeats() << endl
			 << "Revenue: " << e->getRevenue() << endl << endl;
	}

	cout << endl;
}

Event* Venue::searchEvents(string title) const {

	Event* e_ptr = utils::searchPtrs(
		events,
		[](const Event* e) { return e->getTitle(); },
		title
	);

	return e_ptr;
}

double Venue::getRevenue() const {
	
	// Sum revenue across events
	double total = 0;

	for (const Event* e : events) {
		total += e->getRevenue();
	}

	return total;
}

// Mutators
void Venue::addEvent(Event* e) {
	events.push_back(e);
}

// Static methods
void Venue::setNextId(int id) {
	nextId = id;
}

int Venue::getNextId() {
	return nextId;
}