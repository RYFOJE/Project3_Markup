#include <fstream>
#include <string>
#include <iostream>

using namespace std;

string read_from_file() {
	string tempStr;

	while (true) {
		char c = cin.get();

		if (c == EOF) {
			break;
		}

		tempStr.push_back(c);

	}

	return tempStr;
}

bool fileExists(string fileName) {
	std::ifstream infile(fileName.c_str());
	return infile.good();
}