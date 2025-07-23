#include <string>
#include <iostream>
#include <stdexcept>

#include "Types.h"
#include "Utils.h"
#include "Venue.h"
#include "Event.h"

using namespace std;

// Forward declarations

// Static variables
int Venue::nextId = 1;

// Constructors and destructors
Venue::Venue(string _name) : name(_name), id(nextId++), revenue(0) {}

// Accessors

void Venue::printVenue() const {
	cout << "Name: " << getName() << endl
		<< "ID: " << getId() << endl
		<< "Total Events: " << events.size() << endl
		<< "Total Revenue: " << revenue << endl << endl;
}

void Venue::printEvents() const {

	cout << "\n-----Events-----\n\n";

	// Print title and ticket info
	for (Event* e : events) {
		e->printEvent();
		cout << endl;
	}
}

Event* Venue::searchEvents(string title) const {

	Event* e_ptr = utils::searchPtrs(
		events,
		[](const Event* e) { return e->getTitle(); },
		title
	);

	return e_ptr;
}

// Mutators
void Venue::addEvent(Event* e) {
	events.push_back(e);
}

// Static methods
void Venue::setNextId(int id) {
	nextId = id;
}