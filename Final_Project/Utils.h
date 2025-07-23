#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <functional>

#include "Types.h"

using namespace std;

namespace utils{

	///<summary>Generic sort function</summary>
	/// <param name="ptrs">Vector of pointers</param>
	/// <param name="keyFunc">
	/// Function that takes a pointer and returns a string.
	/// Enter a class method as an argument.
	/// </param>
	/// <returns>Sorted vector of pointers</returns>
	template <typename T, typename CallFunc>
	vector<T*> sortPtrs(const vector<T*>& ptrs, CallFunc keyFunc) {

		vector<T*> ptrs_cpy = ptrs; // Copy ptrs
		bool swap; // Used to determine if any swaps were made
		T* temp = nullptr;

		// Only sort if there are guests
		if (ptrs_cpy.size() == 0) {
			return ptrs_cpy;
		}

		do {
			swap = false; // Set to false

			// Iterate through guests and check for elements out of place
			for (size_t i = 0; i < (ptrs_cpy.size() - 1); i++) {
				if (keyFunc(ptrs_cpy[i]) > keyFunc(ptrs_cpy[i + 1])) {
					swap = true;

					// Swap elements
					temp = ptrs_cpy[i];
					ptrs_cpy[i] = ptrs_cpy[i + 1];
					ptrs_cpy[i + 1] = temp;
				}
			}
		} while (swap); // Continue sorting until no swaps are made

		return ptrs_cpy;
	}

	///<summary>Generic binary sort function</summary>
	/// <param name="ptrs">Vector of pointers sorted by the key being searched on</param>
	/// <param name="keyFunc">
	/// Function that takes a pointer and returns a string.
	/// Enter a class method as an argument.
	/// </param>
	/// <returns>Pointer being searched for, if found. Otherwise nullptr</returns>
	template <typename T, typename CallFunc>
	T* searchPtrs(const vector<T*>& ptrs, CallFunc keyFunc, string key) {

		// Check if there are any guests
		if (ptrs.size() == 0) {
			return nullptr;
		}

		// Create a copy of ptrs to sort
		vector<T*> ptrs_cpy = sortPtrs(ptrs, keyFunc);

		// Initialize min, max and middle indices
		int min_index = 0;
		int max_index = static_cast<int>(ptrs_cpy.size()) - 1;
		int mid_index = max_index / 2;

		bool found = false; // Initialize the found flag to false

		while (!found && min_index <= max_index) {
			// Continue searching while the item has not been found, and is still in bounds

			if (keyFunc(ptrs_cpy[mid_index]) == key) {
				// If the middle item is the one being searched for then return it
				found = true;
			}
			else if (keyFunc(ptrs_cpy[mid_index]) > key) {
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

		// Let user know if guest is in attendance
		if (!found) {
			return nullptr;
		}
		else {
			return ptrs_cpy[mid_index];
		}
	}
}