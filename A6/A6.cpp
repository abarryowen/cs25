#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


class Item {
private:
    string name;
    int quantity;

public:
    // Constructor
    Item(string _name, int _quantity) : name(_name), quantity(_quantity) {}

    // Save contents to file
    void saveToFile() {
        fstream outFile("items.txt", ios::app); // Open file for writing

        outFile << name << "," << quantity << endl; // Write

        outFile.close(); // Close

        cout << "Item saved to file\n"; // Notify user
    }

};

void readFromFile(string f_name) {
    
    ifstream inFile(f_name); // Open file for reading

    if (!inFile) {
        // Notify user if file does not exist and exit
        cout << "File does not exist\n";
        return;
    }

    string line;
    stringstream values;
    string val;

    while (getline(inFile, line)) {
        // Loop through each item
        values.clear();
        values.str(line);

        // Print name
        getline(values, val, ',');
        cout << "Name: " << val << ", ";

        // Print quantity
        getline(values, val, ',');
        cout << "Quantity: " << val << endl;
    }
}

int main() {

    readFromFile("items.txt");

    Item t1("Hammer", 5);
    Item t2("Pipe", 3);

    t1.saveToFile();
    t2.saveToFile();

    readFromFile("items.txt");


    return 0;
}