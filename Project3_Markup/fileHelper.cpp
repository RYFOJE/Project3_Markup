#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>

/*
 * Function:	read_from_file
 * purpose:		this function will read the contents of a file and return it as a string
 *
 * accepts:		std::filesystem::path path - the path to the file to be read
 *
 * returns:		std::string - the contents of the file
 *
 * author: 		Ryan Jennings
*/
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
 * Function:	file_exists
 * purpose:		this function will check if a file exists. I couldve implemented it in the main
 *				but it was more readable doing it this way
 *
 * accepts:		std::string fileName - the name of the file to be checked
 *
 * returns:		bool - true if the file exists, false if it does not
 *
 * author: 		Ryan Jennings
*/
bool file_exists(std::string fileName) {
	return std::filesystem::exists(fileName);
}

/*
 * Function:	count_lines
 * purpose:		Counts the amount of lines in a file
 *
 * accepts:		std::filesystem::path path - the path to the file to be read
 *
 * returns:		unsigned int - the number of lines in the file
 *
 * author: 		Ryan Jennings
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

/*
 * Function:	write_to_file
 * purpose:		This function will write the contents of a string to a file
 *
 * accepts:		std::filesystem::path path - the path to the file to be written to
 *				std::string &text - the text to be written to the file
 *
 * returns:		void
 *
 * author: 		Ryan Jennings
*/
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