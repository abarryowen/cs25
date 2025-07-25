#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Songs.h"

using namespace std;

void Songs::loadData(int rows) {
	// Get file to load from
	ifstream inFile("favorite_music_dataset.csv");

	// Read vars
	string line;
	stringstream values;
	string val;

	// Extractor vars
	string title, artist, genre;
	int release;
	double duration;
	int i = 0;

	getline(inFile, line); // Skip first line

	while (getline(inFile, line) && i++ < rows) {
		// Read the first number of rows specified
		values.clear();
		values.str(line);

		// Save title, artist, genre, release and duration
		getline(values, val, ',');
		title = val;

		getline(values, val, ',');
		artist = val;

		getline(values, val, ',');
		genre = val;

		getline(values, val, ',');
		release = stoi(val);

		getline(values, val, ',');
		duration = stod(val);

		songs.push_back(SongData(title, artist, genre, release, duration));
	}
}

void Songs::clearData() {
	songs.clear();
}

void Songs::display() {
	cout << "-----First " << songs.size() << " row(s)-----" << endl;

	for (const auto& s : songs) {
		cout << s.artist << " released " << s.title << " in " << s.release << endl;
		cout << "This " << s.genre << " song is " << s.duration << " minutes long" << endl << endl;
	}

	cout << endl;
}

