#include <vector>
#include <iostream>
#include <string>

#include "Types.h"
#include "TicketMgr.h"
#include "Guest.h"
#include "Event.h"

using namespace std;

int main() {

	// I have added some guests and some events
	TicketMgr tm;

	tm.addGuest("jseinfeld11", "Jerry", "Seinfeld");
	tm.addGuest("elaine78", "Elaine", "Benes");

	tm.addEvent("Music Festival", 200, 20, 10, 20);
	tm.addEvent("Concert", 10, 5, 10, 20);
	tm.addEvent("Cooking Class", 20, 0, 10, 0);

	// See event listing
	//tm.printEvents();
	//tm.printGuests();
	
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
	e->printGuests();

	cout << endl;
	e->printEvent();
	return 0;
}