#include <fstream>
#include <string>
#include <iostream>

std::string read_from_file() {
	std::string tempStr;

	while (true) {
		char c = std::cin.get();

		if (c == EOF) {
			break;
		}

		tempStr.push_back(c);
	}
	return tempStr;
}

bool fileExists(std::string fileName) {
	std::ifstream infile(fileName.c_str());
	return infile.good();
}

unsigned int count_lines() {

	unsigned int lineCount = 0;
	std::string tempStr;

	while (getline(std::cin, tempStr)) {
		lineCount++;
	}
	
	// Reset cin to the begining of the file
	std::cin.seekg(0);

	return lineCount;
}