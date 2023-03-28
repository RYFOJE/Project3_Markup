#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>


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

/*
 * name: generate_html_header
 *
 * description: this function will return the opening tags for an html document
 *
 * returns: a string with the opening tags for an html document
*/
bool fileExists(std::string fileName) {
	return std::filesystem::exists(fileName);
}

/*
 * name: count_line
 *
 * description: this function will count the total amount of lines in the file given to the program
 *
 * returns: an unsigned int representing the total amount of lines in the file
*/
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