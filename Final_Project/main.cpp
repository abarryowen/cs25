#include <vector>
#include <iostream>
#include <string>

#include "Types.h"
#include "TicketMgr.h"
#include "Guest.h"
#include "Event.h"
#include "Venue.h"

using namespace std;

int main() {

	// I have added some guests and some events
	TicketMgr tm;

	tm.addGuest("jseinfeld11", "Jerry", "Seinfeld");
	tm.addGuest("elaine78", "Elaine", "Benes");

	tm.addVenue("Planterie");
	tm.addVenue("Oracle Park");

	Venue* v = tm.searchVenues("Planterie");
	Venue* u = tm.searchVenues("Oracle Park");

	tm.addEvent("Music Festival", u, 200, 20, 10, 20);
	tm.addEvent("Sculpy Event", v, 10, 5, 10, 20);
	tm.addEvent("Cooking Class", v, 20, 0, 10, 0);
	
	// Test abstract functions

	// Test purchasing tickets
	Guest* g = tm.searchGuests("jseinfeld11");
	Guest* f = tm.searchGuests("elaine78");

	Event* d = tm.searchEvents("Cooking Class");
	Event* e = tm.searchEvents("Music Festival");

	tm.sellTickets(g, e, TicketType::Standard, 3);
	tm.sellTickets(g, e, TicketType::Standard, 1);
	tm.sellTickets(g, e, TicketType::VIP, 1);
	tm.sellTickets(f, e, TicketType::VIP, 5);
	tm.sellTickets(g, d, TicketType::Standard, 2);
	
	g->printEvents();
	f->printEvents();

	v->printEvents();
	//e->printGuests();

	//cout << endl;
	//e->printEvent();

	return 0;
}