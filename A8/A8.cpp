#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class BankAccount {
private:
    double balance;

public:
   // Constructor
    BankAccount() : balance(0) {}; // Default

// Mutators
    // Deposit money
    void deposit(double amount) {
        // Check if amount is valid
        if (amount <= 0) {
            cout << "Invalid amount\n";
            return;
        }

        balance += amount; // Deposit

        saveTransaction("Deposit", amount); // Record
    }

    // Withdraw money
    bool withdraw(double amount) {
        // Check if amount is valid
        if (amount <= 0) {
            cout << "Invalid amount\n";
            return false;
        }
        else if (amount > balance) {
            cout << "Insufficient funds\n";
            return false;
        }

        balance -= amount; // Withdraw

        saveTransaction("Withdraw", amount); // Record

        return true; // Return success
    }

    // Purchase item
    void purchase(string item, double price) {
        // Withdraw if valid
        if (!withdraw(price)) {
            return;
        }

        // Record transaction
        saveTransaction("Purchase " + item, price);
    }

    // Return balance
    double getBalance() const {
        return balance;
    }

    // Print balance
    void printBalance() const {
        cout << "Balance: " << balance << endl;
    }

    // Save transaction
    void saveTransaction(string t_type, double amount) const {
        
        fileCheck(); // Check if file has been created yet

        fstream outFile("transactions.txt", ios::app);

        outFile << t_type << ", $" << amount <<endl;

        outFile.close();

    }

private:
    // Check if file exists
    void fileCheck() const {
        // Check if the file has been created already
        fstream checkFile("transactions.txt", ios::in);

        if (checkFile.is_open()) {
            checkFile.close();
            return;
        }

        // If not write headers
        fstream outFile("transactions.txt", ios::out);

        outFile << "Transaction Type, Amount\n";
        outFile.close();
        
    }
};

int main()
{
    // Create account
    BankAccount myAcct;
    myAcct.deposit(100);

    myAcct.withdraw(300); // Error check

    // Make purchases
    myAcct.purchase("Coffee", 5.20);
    myAcct.purchase("Groceries", 50.89);
    myAcct.purchase("Post cards", 10.12);


    return 0;
}
