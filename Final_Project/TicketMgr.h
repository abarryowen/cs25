#pragma once

#include <vector>
#include <iostream>
#include <string>
#include "Types.h"
#include "Guest.h"

using namespace std;

// Forward declarations

/// <summary>
/// Organizes users and events, and orchestrates the flow of tickets
///</summary>
class TicketMgr {
private:
	EventList events;
	GuestList guests;
	VenueList venues;

public:
// Constructors and destructors

	/// <summary>Default constructor</summary>
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

// Static methods
};


	/// <summary></summary>
	/// <param name=""></param>
	/// <returns></returns>