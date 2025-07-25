#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>

#include "Types.h"
#include "TicketMgr.h"
#include "Guest.h"
#include "Event.h"
#include "Venue.h"
#include "Ticket.h"

using namespace std;

int main() {

	TicketMgr tm;
	tm.loadAll();

	Guest* g = tm.searchGuests("jseinfeld11");
	Guest* f = tm.searchGuests("elaine78");

	Event* d = tm.searchEvents("Cooking Class");
	Event* e = tm.searchEvents("Music Festival");

	Venue* v = tm.searchVenues("Planterie");
	Venue* u = tm.searchVenues("Oracle Park");

	g->printEvents();
	f->printEvents();

	v->printEvents();
	cout << v->getName() << " " << v->getRevenue() << endl << endl;
	e->printGuests();

	tm.addVenue("Bakery");

	tm.saveAll();

	//// Load file data
	//ifstream loadFile("tm_data.json");

	//if (!loadFile.is_open()) {
	//	// Check file is valid
	//	throw std::runtime_error("File does not exist");
	//}

	//json jData;
	//loadFile >> jData;
	//loadFile.close();

	//tm.loadAll();

	//tm.printEvents();
	//tm.printGuests();
	//tm.printVenues();

	//Guest* g = tm.searchGuests("jseinfeld11");
	//Guest* f = tm.searchGuests("elaine78");

	//Event* d = tm.searchEvents("Cooking Class");
	//Event* e = tm.searchEvents("Music Festival");

	//Venue* v = tm.searchVenues("Planterie");
	//Venue* u = tm.searchVenues("Oracle Park");

	//g->printEvents();
	//f->printEvents();

	//v->printEvents();
	//e->printGuests();

//------TEST LOAD----------------------------------
	// Load file data
	//ifstream loadFile("tm_data.json");

	//if (!loadFile.is_open()) {
	//	// Check file is valid
	//	throw std::runtime_error("File does not exist");
	//}

	//json jData;
	//loadFile >> jData;
	//loadFile.close();

	//// load venues test
	//unordered_map<int, Venue*> vLoad = tm.loadVenues(jData["venues"]);

	//for (auto& it : vLoad) {
	//	cout << it.first << " " << it.second->getName();

	//	cout << endl;
	//}

	//cout << endl << endl;

	//tm.numTest();

	//// load tickets test
	//unordered_map<int, Ticket*> tLoad = tm.loadTickets(jData["tickets"]);

	//for (auto& it : tLoad) {
	//	cout << it.first << " " << it.second->getPrice()
	//		<< " " << static_cast<int>(it.second->getType());

	//	cout << endl;
	//}

	//cout << endl << endl;

	//tm.testTickets();

	// load events test
	//vector<load::EventLoad> eLoad = tm.loadEvents(jData["events"]);

	//for (auto& it : eLoad) {
	//	cout << it.event->getId() << " " << it.event->getTitle() << endl;

	//	for (auto& i : it.ticketIds) {
	//		cout << i << ", ";
	//	}
	//	cout << endl;

	//	cout 
	//		<< "Tickets Left: " << it.event->getUnsoldTickets() << ", Seats Left: " << it.event->getOpenSeats() << endl
	//		<< "Revenue Test: " << it.event->getRevenue() << endl << endl;
	//}

	//cout << endl << endl;

	//tm.numTest();

	//// load guests test
	//unordered_map<int, load::GuestLoad> gLoad = tm.loadGuests(jData["guests"]);

	//for (auto& it : gLoad) {
	//	cout << it.first << " " << it.second.guest->getName() << " ";
	//	for (auto& i : it.second.ticketIds) {
	//		cout << i << ", ";
	//	}

	//	cout << endl;
	//}

	//cout << endl << endl;

	//tm.printGuests();

//--------END-----------------

	//tm.addGuest("jseinfeld11", "Jerry", "Seinfeld");
	//tm.addGuest("elaine78", "Elaine", "Benes");
	//tm.addGuest("jconst123", "George", "Costanza");
	//tm.addGuest("cosmos78", "Cosmo", "Kramer");

	//tm.addVenue("Planterie");
	//tm.addVenue("Oracle Park");

	//Venue* v = tm.searchVenues("Planterie");
	//Venue* u = tm.searchVenues("Oracle Park");

	//tm.addEvent("Music Festival", u, 200, 20, 10, 20);
	//tm.addEvent("Sculpy Event", v, 10, 5, 10, 20);
	//tm.addEvent("Cooking Class", v, 20, 0, 10, 0);
	//
	//// Test abstract functions

	////Test purchasing tickets
	//Guest* g = tm.searchGuests("jseinfeld11");
	//Guest* f = tm.searchGuests("elaine78");

	//Event* d = tm.searchEvents("Cooking Class");
	//Event* e = tm.searchEvents("Music Festival");

	//tm.sellTickets(g, e, TicketType::Standard, 3);
	//tm.sellTickets(g, e, TicketType::Standard, 1);
	//tm.sellTickets(g, e, TicketType::VIP, 1);
	//tm.sellTickets(f, e, TicketType::VIP, 5);
	//tm.sellTickets(g, d, TicketType::Standard, 2);

	//tm.saveAll();

	
	//g->printEvents();
	//f->printEvents();

	//v->printEvents();
	//e->printGuests();

	//cout << endl;
	//e->printEvent();

	return 0;
}