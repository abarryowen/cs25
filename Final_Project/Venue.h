#pragma once

#include <string>
#include "Types.h"

using namespace std;

class Venue {
private:
	int id;
	static int nextId;
	string name;
	EventList events;
	double revenue;

public:
// Constructors and destructors
	/// <summary>Create new venue</summary>
	Venue(string _name);

// Accessors

	/// <summary>Get venue id</summary>
	int getId() const { return id; };

	/// <summary>Get venue name</summary>
	string getName() const { return name; };

	/// <summary>Get events list </summary>
	EventList getEvents() const { return events; };

	/// <summary>Get venue name</summary>
	double getRevenue() const { return revenue; };

	/// <summary>Print venue info</summary>
	void printVenue() const;

	/// <summary>Print events listing</summary>
	void printEvents() const;

	/// <summary>Print events listing</summary>
	Event* searchEvents(string title) const;

// Mutators
	/// <summary>Add event</summary>
	void addEvent(Event* e);

// Static methods
	/// <summary>Set id number for next venue</summary>
	static void setNextId(int id);
};