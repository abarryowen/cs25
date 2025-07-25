#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Songs.h"

using namespace std;

int main() {
	
	Songs s;

	// Display first row
	s.loadData(1);
	s.display();
	s.clearData();

	// Display first 20 rows
	s.loadData(20);
	s.display();

	return 0;
}