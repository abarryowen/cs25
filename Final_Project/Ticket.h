#pragma once

#include <iostream>
#include <string>
#include <functional>

#include "Types.h"

using namespace std;

// Forward declarations
class Guest;
class Event;

/// <summary>Virtual ticket class</summary>
class Ticket {
private:
	int id;
	static int nextId;
	double sellPrice;
	
	Guest* guest;
	Event* event;

public:
// Constructors and destructors

	/// <summary>Create new ticket</summary>
	Ticket(Guest* g, Event* e, double price);

	/// <summary>Virtual destructor</summary>
	virtual ~Ticket();

// Accessors
	/// <summary>Get ticket id</summary>
	int getId() const { return id; };

	/// <summary>Get sell price</summary>
	double getPrice() const { return sellPrice; };

	/// <summary>Get event pointer read only</summary>
	const Event* getEvent() const { return event; };

	/// <summary>Get guest pointer read only</summary>
	const Guest* getGuest() const { return guest; };

	/// <summary>Pure virtual function for ticket type</summary>
	virtual TicketType getType() const = 0;

	/// <summary>Virtual function for if the ticket comes with reserved seating</summary>
	/// <return>Return false by default</return>
	virtual bool hasSeat() const { return false; };

	/// <summary>Virtual function to return seat number</summary>
	/// <return>Throws an error by default</return>
	virtual int getSeat() const;

	/// <summary>Extract details as string</summary>
	string toString() const;


// Static methods
	/// <summary>Set id number for next ticket</summary>
	static void setNextId(int _id);

	/// <summary>Converts a ticket type to string</summary>
	static string typeToString(TicketType t);

	/// <summary>Group ticket information</summary>
	/// <param name="t_list">Ticket list</param>
	/// <param name="m_id">Function to get the member id from the ticket (e.g. event id, guest id, etc.)</param>
	/// <param name="m_owner">Function to get the member owner from the ticket (e.g. event title, guest name, etc.)</param>
	/// <returns>Hashtable of member id and ticket info</returns>
	static TicketPivot groupTickets(
		const TicketList& t_list,
		function<int(const Ticket* t)> m_id,
		function<string(const Ticket* t)> m_owner
	);

	/// <summary>Print out given ticket pivot</summary>
	static void printTicketPivot(const TicketPivot& t_piv);

};


/// <summary>Standard ticket subclass</summary>
class StandardTicket : public Ticket {
public:
	/// <summary>Create new standard ticket</summary>
	StandardTicket(Guest* g, Event* e, double price);

	/// <summary>Get ticket type</summary>
	TicketType getType() const override { return TicketType::Standard; };
};

/// <summary>VIP Ticket subclass</summary>
class VipTicket : public Ticket {
private:
	int seatNum;

public:
	/// <summary>Create new vip ticket</summary>
	VipTicket(Guest* g, Event* e, double price, int seat);

	/// <summary>Get ticket type</summary>
	TicketType getType() const override { return TicketType::VIP; };

	/// <summary>Returns that vip tickets have seats</summary>
	bool hasSeat() const override { return true; };

	/// <summary>Get seat number</summary>
	int getSeat() const override { return seatNum; };
};

	/// <summary></summary>
	/// <param name=""></param>
	/// <returns></returns>
