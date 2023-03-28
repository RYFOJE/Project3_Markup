#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>


std::string read_from_file(std::filesystem::path path) {
	std::string tempStr;
	std::ifstream in(path);


	while (true) {
		char c = in.get();

		if (c == EOF) {
			break;
		}

		tempStr.push_back(c);
	}
	// Close the file
	in.close();
	
	return tempStr;
}

/*
 * name: file_exists
 *
 * description: this function will see if a file exists
 *
 * returns: a string with the opening tags for an html document
*/
bool file_exists(std::string fileName) {
	return std::filesystem::exists(fileName);
}

/*
 * name: count_line
 *
 * description: this function will count the total amount of lines in the file given to the program
 *
 * returns: an unsigned int representing the total amount of lines in the file
*/
unsigned int count_lines(std::filesystem::path path) {

	unsigned int lineCount = 0;
	std::ifstream in(path);
	std::string tempStr;

	while (getline(in, tempStr)) {
		lineCount++;
	}
	
	// Reset cin to the begining of the file
	std::cin.seekg(0);

	return lineCount;
}

void write_to_file(std::filesystem::path path, std::string &text) {
	std::ofstream outFile(path);
	std::stringstream ss(text);

	char c = ss.get();

	while (!ss.fail()) {
		outFile << c;
		c = ss.get();
	}

	outFile.close();
}