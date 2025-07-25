#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

// Song data struct to store info
struct SongData {
	string title, artist, genre;
	int release;
	double duration;

	SongData(string _title, string _artist, string _genre, int _release, double _duration)
		: title(_title), artist(_artist), genre(_genre), release(_release), duration(_duration) {}
};

using SongList = vector<SongData>;

class Songs {
private:
	SongList songs; // List of songs

public:
	Songs() = default; // Default constructor

	// Load from file
	void loadData(int rows);

	// Clear data
	void clearData();

	// Display data
	void display();


};