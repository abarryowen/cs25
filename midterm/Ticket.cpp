#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include "Ticket.h"

using namespace std;

// Static variables
int Ticket::nextId = 1;


// Constructors and destructors
Ticket::Ticket(int _id, string _name, double _price, int _quantity)
	: id(_id), name(_name), price(_price), quantity(_quantity) {}

Ticket::~Ticket() {}


// Accessors
int Ticket::getId() const {
	return id;
}

string Ticket::getName() const {
	return name;
}

double Ticket::getPrice() const {
	return price;
}

int Ticket::getQuantity() const {
	return quantity;
}

void Ticket::printTicket() const {

	// Determine formatting of Ticket(s)
	string ticket_num;

	if (getQuantity() == 1) {
		ticket_num = "Ticket";
	}
	else {
		ticket_num = "Tickets";
	}

	cout << getName() << ", " << getQuantity() << " " << getType() << " " << ticket_num << "\n";
}

string Ticket::toString() const {
	
	ostringstream ticket_s;

	// Convert ticket to string
	ticket_s << getId() << "," << getType() << "," << getName() << ",";
	ticket_s << fixed << setprecision(2) << getPrice() << ",";
	ticket_s << getQuantity() << "\n";

	return ticket_s.str();
}


// Static methods
void Ticket::setNextId(int _id) {
	nextId = _id;
}

int Ticket::getNextId() {
	return nextId;
}

int Ticket::incNextId() {
	return nextId++;
}


// Standard Ticket
StandardTicket::StandardTicket(int _id, string _name, double _price, int _quantity)
	: Ticket(_id, _name, _price, _quantity) {
}

string StandardTicket::getType() const {
	return "Standard";
}

// VIP Ticket
VipTicket::VipTicket(int _id, string _name, double _price, int _quantity)
	: Ticket(_id, _name, _price, _quantity) {}

string VipTicket::getType() const {
	return "VIP";
}