#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <fstream>

#include "Types.h"
#include "Guest.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

/// <summary>
/// Organizes users and events, and orchestrates the flow of tickets
///</summary>
class TicketMgr {
private:
	EventList events;
	GuestList guests;
	VenueList venues;
	TicketList tickets;

public:
// Constructors and destructors

	/// <summary>Load data from file</summary>
	TicketMgr();

	/// <summary>Delete allocated memory</summary>
	~TicketMgr();

// Accessors

	/// <summary>Number of guests in the guests list</summary>
	size_t numGuests() const;

	/// <summary>Number of events in the events list</summary>
	size_t numEvents() const;

	/// <summary>Search guests by username</summary>
	/// <returns>Pointer to guest, nullptr if not found</returns>
	Guest* searchGuests(string username) const;

	/// <summary>Search events by title</summary>
	/// <returns>Pointer to event, nullptr if not found</returns>
	Event* searchEvents(string title) const;

	/// <summary>Search venues by name</summary>
	/// <returns>Pointer to venue, nullptr if not found</returns>
	Venue* searchVenues(string name) const;

	/// <summary>Print guests</summary>
	void printGuests() const;

	/// <summary>Print events</summary>
	void printEvents() const;

	/// <summary>Print venues</summary>
	void printVenues() const;

// Mutators

	/// <summary>Add new guest</summary>
	void addGuest(string username, string firstName, string lastName);

	/// <summary>Add new event</summary>
	void addEvent(string title, Venue* venue, int totalTickets, int totalSeats, double stdPrice, double vipPrice);

	/// <summary>Add new venue</summary>
	void addVenue(string _name);

	/// <summary>Add new event</summary>
	void sellTickets(Guest* g, Event* e, TicketType type, int quantity);

// File functions

	/// <summary>Create guests json object</summary>
	json saveGuests() const;

	/// <summary>Create events json object</summary>
	json saveEvents() const;

	/// <summary>Create tickets json object</summary>
	json saveTickets() const;

	/// <summary>Create venues json object</summary>
	json saveVenues() const;

	/// <summary>Create nextIds json object</summary>
	json saveNextIds() const;

	/// <summary>Save all data to json file</summary>
	void saveAll() const;

	/// <summary>Load guests from json file</summary>
	/// <param name="jGuests">Json data for guests</param>
	/// <returns>vector of structs with guest pointer and list of ticket ids</returns>
	vector<load::GuestLoad> loadGuests(const json& jGuests);

	/// <summary>Load events from json file</summary>
	/// <param name="jEvents">Json data for events</param>
	/// <returns>Vector of structs with event pointer, venue pointer, and list of ticket ids</returns>
	vector<load::EventLoad> loadEvents(const json& jEvents);

	/// <summary>Load tickets from json file</summary>
	/// <param name="jTickets">Json data for tickets</param>
	/// <returns>Map of ids, and ticket pointers</returns>
	unordered_map<int, Ticket*> loadTickets(const json& jTickets);

	/// <summary>Load venues from json file</summary>
	/// <param name="jVenues">Json data for venues</param>
	/// <returns>Map of ids, and venue pointers</returns>
	unordered_map<int, Venue*> loadVenues(const json& jVenues);

	/// <summary>Load all data from json file</summary>
	void loadAll();

	/// <summary>Load all data from json file</summary>
	void overrideFile();

};
