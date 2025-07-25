#pragma once

#include <iostream>
#include "Types.h"

using namespace std;

/// <summary>Guest class</summary>
class Guest {
private:
	int id;
	static int nextId;
	string username;
	string name;
	TicketList purchasedTickets;

public:
// Constructors and destructors

	/// <summary>Create new guest</summary>
	Guest(string _username, string firstName, string lastName)
		: id(nextId++),
		  username(_username),
		  name(firstName + " " + lastName) {}

	/// <summary>Load guest from file</summary>
	Guest(int _id, string _username, string _name)
		: id(_id), username(_username), name(_name) {}

// Accessors

	/// <summary>Get guest id</summary>
	int getId() const { return id; };

	/// <summary>Get guest username</summary>
	string getUsername() const { return username; };

	/// <summary>Get guest name</summary>
	string getName() const { return name; };

	/// <summary>Get purchased tickets</summary>
	const TicketList& getTickets() const { return purchasedTickets; };

	/// <summary>Print guest info</summary>
	void printGuest() const;

	/// <summary>Print events attended</summary>
	void printEvents() const;

// Mutators

	/// <summary>Add ticket to purchased tickets registry</summary>
	void addTicket(Ticket* t);

// Static methods

	/// <summary>Set id number for next guest</summary>
	static void setNextId(int id);

	/// <summary>Get id number for next guest</summary>
	static int getNextId();
};