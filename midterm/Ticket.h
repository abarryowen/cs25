#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
* @brief Virtual ticket class
*/
class Ticket {
private:
	int id;
	string name;
	double price;
	int quantity;

	static int nextId;

public:
// Constructors and destructors
	/**
	 * @brief Create new ticket
	 */
	Ticket(int _id, string _name, double _price, int _quantity);

	/**
	 * @brief Virtual destructor
	 */
	virtual ~Ticket();


// Accessors
	/**
	 * @brief Get ticket id
	 */
	int getId() const;

	/**
	 * @brief Get name of ticket holder
	 */
	string getName() const;

	/**
	 * @brief Get price of ticket
	 */
	double getPrice() const;

	/**
	 * @brief Get number of people attending on ticket
	 */
	int getQuantity() const;

	/**
	 * @brief Pure virtual function for ticket type
	 */
	virtual string getType() const = 0;

	/**
	 * @brief Print ticket to console
	 */
	void printTicket() const;

	/**
	 * @brief Convert ticket to string, for saving to file
	 */
	string toString() const;


// Static methods
	/**
	 * @brief Static method to set next id
	 */
	static void setNextId(int _id);
	
	/**
	 * @brief Static method to get id for the next ticket created
	 */
	static int getNextId();

	/**
	 * @brief Static method to get id for the next ticket created and increment it
	 */
	static int incNextId();

};


/**
* @brief Standard Ticket subclass
*/
class StandardTicket : public Ticket {
public:
	/**
	 * @brief Create new standard ticket
	 */
	StandardTicket(int _id, string _name, double _price, int _quantity);

	/**
	 * @brief Get ticket type
	 */
	string getType() const;
};

/**
* @brief VIP Ticket subclass
*/
class VipTicket : public Ticket {
public:
	/**
	 * @brief Create new ticket
	 */
	VipTicket(int _id, string _name, double _price, int _quantity);

	/**
	 * @brief Get ticket type
	 */
	string getType() const;
};

	/**
	 * @brief
	 *
	 * @param
	 * @return
	 */
