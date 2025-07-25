#pragma once

#include <vector>
#include <unordered_map>

using namespace std;

// Forward declarations
class Ticket;
class Guest;
class Event;
class Venue;

// Enums and structs

/// <summary>Ticket type enum for Standard or VIP</summary>
enum class TicketType {
	Standard = 1,
	VIP = 2
};

/// <summary>Ticket info struct</summary>
struct TicketInfo {
	double price;

	TicketInfo(double _price) : price(_price) {}
};

/// <summary>Struct for grouping tickets</summary>
struct TicketGroup {
	string owner;
	unordered_map<TicketType, int> ticketCount;
	vector<int> seats;

	// Earlier it was just quantity

	TicketGroup() : owner("") {}
};

namespace load {
	/// <summary>Struct for loading guests</summary>
	struct GuestLoad {
		Guest* guest;
		vector<int> ticketIds;

		GuestLoad(Guest* g, vector<int> ids)
			: guest(g), ticketIds(ids) {}
	};

	/// <summary>Struct for loading events</summary>
	struct EventLoad {
		Event* event;
		int venue;
		vector<int> ticketIds;

		EventLoad(Event* e, int _venue, vector<int> ids)
			: event(e), venue(_venue), ticketIds(ids) {
		}
	};
}

// Aliases
using TicketList = vector<Ticket*>;
using GuestList = vector<Guest*>;
using EventList = vector<Event*>;
using VenueList = vector<Venue*>;
using IntList = vector<int>;
using TicketHash = unordered_map<TicketType, TicketInfo>;
using TicketPivot = unordered_map<int, TicketGroup>;