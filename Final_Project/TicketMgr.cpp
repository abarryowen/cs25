#include <string>
#include <stdexcept>
#include <fstream>
#include "json.hpp"

#include "Types.h"
#include "Utils.h"
#include "TicketMgr.h"
#include "Event.h"
#include "Guest.h"
#include "Ticket.h"
#include "Venue.h"

using namespace std;
using json = nlohmann::json;

// Forward declarations

// Static variables

// Constructors and destructors
TicketMgr::TicketMgr() {
	loadAll();
}

TicketMgr::~TicketMgr() {
	// Delete guests
	for (Guest*& g : guests) {
		delete g; 
		g = nullptr;
	}

	// Delete events
	for (Event*& e : events) {
		delete e; 
		e = nullptr;
	}

	// Delete tickets
	for (Ticket*& t : tickets) {
		delete t;
		t = nullptr;
	}

	// Delete venues
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
	double price = e->getTicketDetails().at(type).price;
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
		tickets.push_back(t); // Add ticket to registry
	}

	t = nullptr;
}

// File functions
json TicketMgr::saveGuests() const {
	json jGuests = json::array(); // Create guests json object

	for (Guest* g : guests) {
		json jGuest;

		// Get primitive info
		jGuest["id"] = g->getId();
		jGuest["username"] = g->getUsername();
		jGuest["name"] = g->getName();

		// Add ticket ids
		IntList ticketIds;
		for (auto& t : g->getTickets()) {
			ticketIds.push_back(t->getId());
		}

		jGuest["tickets"] = ticketIds;

		jGuests.push_back(jGuest); 
	}

	return jGuests;
}

json TicketMgr::saveEvents() const {
	json jEvents = json::array(); // Create events json object

	for (Event* e : events) {
		json jEvent;

		// Get primitive info
		jEvent["id"] = e->getId();
		jEvent["title"] = e->getTitle();
		jEvent["venue"] = e->getVenue()->getId();
		jEvent["reservedSeats"] = (e->getNextSeat() - 1);
		jEvent["totalSeats"] = e->getOpenSeats() + jEvent["reservedSeats"];
		jEvent["unsoldTickets"] = e->getUnsoldTickets();
		jEvent["revenue"] = e->getRevenue();

		// Add ticket ids
		IntList ticketIds;
		for (auto& t : e->getSoldTickets()) {
			ticketIds.push_back(t->getId());
		}

		jEvent["soldTickets"] = ticketIds;

		// Add ticket details
		json jDetails = json::array();
		for (auto& td : e->getTicketDetails()) {
			jDetails.push_back({
				{"type", static_cast<int>(td.first)},
				{ "price", td.second.price }
			});
		}

		jEvent["ticketDetails"] = jDetails;

		// Add event
		jEvents.push_back(jEvent); 
	}

	return jEvents;
}

json TicketMgr::saveTickets() const {
	json jTickets = json::array(); // Create tickets json object

	for (Ticket* t : tickets) {
		json jTicket;

		// Get primitive info
		jTicket["id"] = t->getId();
		jTicket["sellPrice"] = t->getPrice();
		jTicket["guest"] = t->getGuest()->getId();
		jTicket["event"] = t->getEvent()->getId();
		jTicket["type"] = static_cast<int>(t->getType());

		// Get seat number
		int seatNum;
		if (t->hasSeat()) {
			seatNum = t->getSeat();
		}
		else {
			seatNum = -1;
		}

		jTicket["seatNumber"] = seatNum;

		// Add ticket
		jTickets.push_back(jTicket); 
	}

	return jTickets;
}

json TicketMgr::saveVenues() const {
	json jVenues = json::array(); // Create venues json object

	for (Venue* v : venues) {
		json jVenue;

		// Get primitive info
		jVenue["id"] = v->getId();
		jVenue["name"] = v->getName();

		// Add ticket ids
		IntList eventIds;
		for (auto& e : v->getEvents()) {
			eventIds.push_back(e->getId());
		}

		jVenue["events"] = eventIds;

		jVenues.push_back(jVenue); // Add venue
	}

	return jVenues;
}

json TicketMgr::saveNextIds() const {

	json jId;

	jId["guest"] = Guest::getNextId();
	jId["event"] = Event::getNextId();
	jId["venue"] = Venue::getNextId();
	jId["ticket"] = Ticket::getNextId();

	return jId;
}

void TicketMgr::saveAll() const {
	json jRoot;

	// Add all data
	jRoot["guests"] = saveGuests();
	jRoot["events"] = saveEvents();
	jRoot["tickets"] = saveTickets();
	jRoot["venues"] = saveVenues();
	jRoot["ids"] = saveNextIds();

	// Save to file
	ofstream saveFile("tm_data.json");
	saveFile << jRoot.dump(4);
	saveFile.close();
}

vector<load::GuestLoad> TicketMgr::loadGuests(const json& jGuests) {

	// Capture guests and their ticket ids, to later be linked as pointers
	vector<load::GuestLoad> gLoad;

	// Create guests
	for (const auto& jGuest : jGuests) {
		// Get guest data
		int id = jGuest["id"];
		string username = jGuest["username"];
		string name = jGuest["name"];
		IntList gTickets = jGuest["tickets"];

		// Add guest to guest registry attribute, and to load struct
		Guest* g = nullptr;
		g = new Guest(id, username, name);

		guests.push_back(g);
		gLoad.push_back(load::GuestLoad(g, gTickets));
	}

	return gLoad;
}

vector<load::EventLoad> TicketMgr::loadEvents(const json& jEvents) {
	
	// Capture events and their ticket ids, to later be linked as pointers
	vector<load::EventLoad> eLoad;

	// Create events
	for (const auto& jEvent : jEvents) {
		// Get event data
		int id = jEvent["id"];
		string title = jEvent["title"];
		int venue = jEvent["venue"]; // Venue id
		int totalSeats = jEvent["totalSeats"];
		int reservedSeats = jEvent["reservedSeats"];
		int unsoldTickets = jEvent["unsoldTickets"];
		IntList eTickets = jEvent["soldTickets"]; // List of ticket ids
		double revenue = jEvent["revenue"];

		// Get ticket details and create map
		TicketHash ticketDetails;

		for (const auto& det : jEvent["ticketDetails"]) {
			TicketType type = det["type"];
			double price = det["price"];

			ticketDetails.insert({ type, TicketInfo(price) });
		}

		// Add to events registry attribute, and to load struct
		Event* e = nullptr;
		e = new Event(id, title, revenue, unsoldTickets, totalSeats, reservedSeats, ticketDetails);

		events.push_back(e);
		eLoad.push_back(load::EventLoad(e, venue, eTickets));
	}

	return eLoad;
}

unordered_map<int, Ticket*> TicketMgr::loadTickets(const json& jTickets) {
	// Capture tickets, to later be linked as pointers
	unordered_map<int, Ticket*> tLoad;

	// Create tickets
	for (const auto& jTicket : jTickets) {
		// Get ticket data
		int id = jTicket["id"];
		int seatNum = jTicket["id"];
		double price = jTicket["sellPrice"];
		TicketType type = static_cast<TicketType>(jTicket["type"]);

		// Add ticket to registry attribute, and to load struct
		Ticket* t = nullptr;

		switch (type) {
			case TicketType::Standard:
				t = new StandardTicket(id, price);
				break;
			case TicketType::VIP:
				t = new VipTicket(id, price, seatNum);
				break;
			default:
				// Throw exception if invalid ticket type passed
				cout << "Invalid ticket type entered\n";
				throw std::invalid_argument("Invalid TicketType");
		}

		tickets.push_back(t);
		tLoad.insert({ id, t });
	}

	return tLoad;
}

unordered_map<int, Venue*> TicketMgr::loadVenues(const json& jVenues) {
	// Capture venues, to later be linked as pointers
	unordered_map<int, Venue*> vLoad;

	// Create venues
	for (const auto& jVenue : jVenues) {
		// Get venue data
		int id = jVenue["id"];
		string name = jVenue["name"];

		// Add venue to registry attribute, and to load struct
		Venue* v = nullptr;
		v = new Venue(id, name);

		venues.push_back(v);
		vLoad.insert({ id, v });
	}

	return vLoad;
}

void TicketMgr::loadAll() {
	// Load file data
	ifstream loadFile("tm_data.json");

	if (!loadFile.is_open()) {
		// If the file does not exist, then start from scratch
		return;
	}

	json jData;
	loadFile >> jData;
	loadFile.close();

	// Load data
	vector<load::GuestLoad> gTemp = loadGuests(jData["guests"]);
	vector<load::EventLoad> eTemp = loadEvents(jData["events"]);
	unordered_map<int, Ticket*> tTemp = loadTickets(jData["tickets"]);
	unordered_map<int, Venue*> vTemp = loadVenues(jData["venues"]);

	// Link guests with tickets
	for (auto& gl : gTemp) {
		Guest* g = gl.guest; // Get pointer to guest

		for (int tId : gl.ticketIds) {
			Ticket* t = tTemp[tId]; // Get pointer to ticket

			// Link
			g->addTicket(t);
			t->loadGuest(g);
		}
	}

	// Link events with tickets and venues
	for (auto& el : eTemp) {
		Event* e = el.event; // Get pointer to event

		// Link tickets
		for (int tId : el.ticketIds) {
			Ticket* t = tTemp[tId]; // Get pointer to ticket

			e->loadTicket(t);
			t->loadEvent(e);
		}

		// Link venue
		Venue* v = vTemp[el.venue]; // Get pointer to venue

		e->loadVenue(v);
		v->addEvent(e);
	}

	// Load nextIds
	Guest::setNextId(jData["ids"]["guest"]);
	Event::setNextId(jData["ids"]["event"]);
	Ticket::setNextId(jData["ids"]["ticket"]);
	Venue::setNextId(jData["ids"]["venue"]);
}

void TicketMgr::overrideFile() {
	json jRoot;

	// Add all data
	jRoot["guests"] = json::array();
	jRoot["events"] = json::array();
	jRoot["tickets"] = json::array();
	jRoot["venues"] = json::array();
	jRoot["ids"] = {
		{"guest", 1},
		{"event", 1},
		{"ticket", 1},
		{"venue", 1},
	};

	// Save to file
	ofstream saveFile("tm_data.json");
	saveFile << jRoot.dump(4);
	saveFile.close();
}