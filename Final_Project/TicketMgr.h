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

	/// <summary>Sort guest list by username</summary>
	/// <returns>Copy of guests</returns>
	GuestList sortGuests() const;

	/// <summary>Search guests by username</summary>
	/// <returns>Pointer to guest, nullptr if not found</returns>
	Guest* searchGuests(string username) const;

	/// <summary>Sort event list by username</summary>
	/// <returns>Copy of events</returns>
	EventList sortEvents() const;

	/// <summary>Search events by title</summary>
	/// <returns>Pointer to event, nullptr if not found</returns>
	Event* searchEvents(string title) const;

	/// <summary>Print guests</summary>
	void printGuests() const;

	/// <summary>Print events</summary>
	void printEvents() const;

// Mutators

	/// <summary>Add new guest</summary>
	void addGuest(string username, string firstName, string lastName);

	/// <summary>Add new event</summary>
	void addEvent(string _title, int totalTickets, int totalSeats, double stdPrice, double vipPrice);

	/// <summary>Add new event</summary>
	void sellTickets(Guest* g, Event* e, TicketType type, int quantity);

// Static methods
};


	/// <summary></summary>
	/// <param name=""></param>
	/// <returns></returns>