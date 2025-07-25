#include <iostream>
#include <string>

using namespace std;

// Item struct
struct Item {
    int id = -1;
    string name = "empty";
};

// Functions
void sortItems(Item[], int);
void searchItems(Item [], int, int);

int main()
{
    const int SIZE = 9; // Init constant size
    
    Item* items = new Item[SIZE]; // Declare dynamic array

    // Init values
    items[0] = { 314, "Toothpaste" };
    items[1] = { 654, "Tweezers" };
    items[2] = { 915, "Crackers" };
    items[3] = { 205, "Nails" };
    items[4] = { 386, "Goldfish" };
    items[5] = { 252, "Blow-up Pool" };
    items[6] = { 182, "Barbeque" };
    items[7] = { 414, "Hammock" };
    items[8] = { 430, "Oven Mits" };

    sortItems(items, SIZE); // Sort by id
    searchItems(items, SIZE, 414); // Search for given id

    // De-allocate memory
    delete[] items;
    items = nullptr;

    return 0;
}

void sortItems(Item arr[], int size) {
    // This function sorts an array of Items
    
    bool swap;
    Item temp;

    do {
        swap = false; // Set to false

        // Loop through array and check for elements out of place
        for (int i = 0; i < (size - 1); i++) {
            if (arr[i].id > arr[i + 1].id) {
                swap = true; // Set flag to true

                // Swap elements
                temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }
    } while (swap);

}

void searchItems(Item arr[], int size, int look) {
    // This function performs a binary search on id number for an array of Items

    // Initialize min, max and middle indices
    int min_index = 0;
    int max_index = size - 1;
    int mid_index = max_index / 2;

    bool found = false; // Initialize the found flag to false

    while (!found && min_index <= max_index) {
        // Continue searching while the item has not been found, and is still in bounds

        if (arr[mid_index].id == look) {
            // If the middle item is the one being searched for then return it
            found = true;
        }
        else if (arr[mid_index].id > look) {
            // If larger then resize down
            max_index = mid_index - 1;
            mid_index = (max_index + min_index) / 2;
        }
        else {
            // Otherwise resize up
            min_index = mid_index + 1;
            mid_index = (max_index + min_index) / 2;
        }
    }

    // Let user know if the item wasn't found
    if (!found) {
        cout << "Item not found" << endl;
    }
    else {
        cout << "id: " << arr[mid_index].id << ", name: " << arr[mid_index].name << endl;
    }
}


