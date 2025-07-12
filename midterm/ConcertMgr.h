#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Forward declarations
class Ticket;


/**
* @brief Concert manager sells tickets and saves data
*/
class ConcertMgr {
private:
	string name;
	double revenue; // Concert revenue
	double stdPrice; // Standard ticket price
	double vipPrice; // VIP ticket price
	int remTickets; // Available tickets to purchase
	vector<Ticket*> soldTickets; // Record of sold tickets

public:
// Constructors and destructors
	/**
	 * @brief Load from file
	 */
	ConcertMgr();

	/**
	 * @brief Make new concert
	 *
	 * @param _stdPrice Standard ticket price
	 * @param _vipPrice VIP ticket price
	 * @param totalTickets Total available tickets
	 */
	ConcertMgr(string _name, double _stdPrice, double _vipPrice, int totalTickets);

	/**
	 * @brief Save to file and delete memory
	 */
	~ConcertMgr();


// Accessors
	/**
	 * @brief Get name
	 */
	string getName() const;

	/**
	 * @brief Get revenue
	 */
	double getRevenue() const;

	/**
	 * @brief Get remaning tickets
	 */
	int getRemTickets() const;

	/**
	 * @brief Get price of standard ticket
	 */
	double getStdPrice() const;

	/**
	 * @brief Get price of VIP ticket
	 */
	double getVipPrice() const;

	/**
	 * @brief Get total number of tickets sold
	 */
	int getTotalSold() const;

	/**
	 * @brief Print list of guests
	 */
	void printGuests() const;

	/**
	 * @brief Print concert details
	 */
	void printConcert() const;

	/**
	 * @brief Print box office details
	 */
	void printBoxOffice() const;

	/**
	 * @brief Search for guest based on ID
	 */
	void searchGuests(int guestId) const;

	/**
	 * @brief Save data to file
	 */
	void saveToFile() const;


// Mutators
	/**
	 * @brief Add sale to total revenue
	 */
	void addRevenue(double sale);

	/**
	 * @brief Remove quantity from remaining tickets if possible
	 * 
	 * @return Returns true if successful
	 */
	bool lowerTickets(int quantity);

	/**
	 * @brief Purchase ticket for new guest
	 * 
	 * @param ticketType Choose either "VIP" or "Standard"
	 * @param name Name of ticketholder
	 * @param quantity Number of tickets being purchased
	 */
	void sellTickets(string ticketType, string name, int quantity);

	/**
	 * @brief Load data from file
	 */
	void loadFromFile();

};