#pragma once

#include <string>
#include <unordered_map>

#include "Types.h"

using namespace std;

class Event {
private:
	// Identifiers
	int id;
	static int nextId;
	string title;

	Venue* venue; // Venue that is holding it

	// Tickets and seats
	const int totalSeats; // Total available seats to reserve
	int reservedSeats; // Seats reserved so far
	int unsoldTickets; // Remaining tickets
	TicketList soldTickets; // List of tickets sold
	TicketHash ticketDetails; // Pricing and other info for various ticket types

	double revenue; // Revenue generated
	

public:
// Constructors and destructors

	/// <summary>Create new event</summary>
	/// <param name="_title">Unique title of event</param>
	/// <param name="totalTickets">Total tickets</param>
	/// <param name="totalSeats">Total seats that can be reserved</param>
	/// <param name="stdPrice">Price of standard tickets</param>
	/// <param name="vipPrice">Price of vip tickets</param>
	Event(
		string _title, Venue* _venue, int totalTickets, 
		int _totalSeats, double stdPrice, double vipPrice
	);

	/// <summary>Load event from file</summary>
	Event(
		int _id, string _title, double _revenue,
		int _unsoldTickets, int _totalSeats, int _reservedSeats, TicketHash details
	);


// Accessors
	
	/// <summary>Get event id</summary>
	int getId() const { return id; };

	/// <summary>Get event title</summary>
	string getTitle() const { return title; };

	/// <summary>Get event title</summary>
	Venue* getVenue() const { return venue; };
	
	/// <summary>Get number of unsold tickets</summary>
	int getUnsoldTickets() const { return unsoldTickets; };

	/// <summary>Get number of unsold tickets</summary>
	const TicketList& getSoldTickets() const { return soldTickets; };

	/// <summary>Get number of open seats remaining</summary>
	int getOpenSeats() const { return totalSeats - reservedSeats; };

	/// <summary>Gets the next available seat number</summary>
	int getNextSeat() const { return reservedSeats + 1; };

	/// <summary>Get revenue</summary>
	double getRevenue() const { return revenue; };

	/// <summary>Print event info</summary>
	void printEvent() const;

	/// <summary>Pring guests attending</summary>
	void printGuests() const;

	/// <summary>
	/// Get read only access to the ticket details of the given type
	/// </summary>
	const TicketHash& getTicketDetails() const;

	/// <summary>
	/// Check if there are enough tickets and seats (if applicable) for the given purchase.
	/// </summary>
	/// <param name="type">Ticket type, determines whether seats will also be reserved</param>
	/// <param name="quantity">Number of tickets attempting to be sold</param>
	bool saleValid(TicketType type, int quantity) const;

// Mutators

	/// <summary>
	/// Add ticket to soldTickets registry and update ticket and seat metrics
	/// </summary>
	void addTicket(Ticket* t);

	/// <summary>Load ticket</summary>
	void loadTicket(Ticket* t);

	/// <summary>Load venue</summary>
	void loadVenue(Venue* v);

// Static methods
	/// <summary>Set next id</summary>
	static void setNextId(int id);

	/// <summary>Get id number for next event</summary>
	static int getNextId();
};