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

public:
// Constructors and destructors

	/// <summary>Create new venue</summary>
	Venue(string _name)
		: name(_name), id(nextId++) {}

	/// <summary>Load venue from file</summary>
	Venue(int _id, string _name)
		: id(_id), name(_name) {}

// Accessors

	/// <summary>Get venue id</summary>
	int getId() const { return id; };

	/// <summary>Get venue name</summary>
	string getName() const { return name; };

	/// <summary>Get events list </summary>
	const EventList& getEvents() const { return events; };

	/// <summary>Print venue info</summary>
	void printVenue() const;

	/// <summary>Print events listing</summary>
	void printEvents() const;

	/// <summary>Print events listing</summary>
	Event* searchEvents(string title) const;

	/// <summary>Get total revenue for venue</summary>
	double getRevenue() const;

// Mutators

	/// <summary>Add event</summary>
	void addEvent(Event* e);

// Static methods

	/// <summary>Set id number for next venue</summary>
	static void setNextId(int id);

	/// <summary>Get id number for next venue</summary>
	static int getNextId();
};