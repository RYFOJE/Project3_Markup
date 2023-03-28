/*
 * File:		cmdHelper.cpp
 * Purpose:		This file contains the functions that will be used to assist 
				the program to understand command line arguments
 *
 * Author:		Ryan Jennings
*/

#include <string>
#include <vector>
#include <iostream>
#include "cmdHelper.h"

/*
 * Function:	parse_cmd
 * purpose:		Parses the command line arguments and stores them in a struct
 * 
 * accepts:		int argc - the number of arguments passed to the program
 *				char* argv[] - the arguments passed to the program
 * 
 * returns:		cmd_struct - a struct that holds the parsed values from the command line arguments
 * 
 * author: 		Ryan Jennings
*/
cmd_struct parse_cmd(int argc, char* argv[]) {

	cmd_struct commands;
	bool fileFound = false;

	for (size_t i = 1; i < argc; i++) {

		std::string curr = argv[i];

		if (commands.isKeyword) {
			// Add the keyword to the vector
			commands.keywords.push_back(curr);
			continue;
		}

		// If any return command is found, simply end the search and return that is has been found
		// this is because the program does not need to search for any other commands once --help is found
		if (curr.compare("--help") == 0) {
			commands.isHelp = true;
			break;
		}

		else if (curr.compare("--keywords") == 0) {
			commands.isKeyword = true;
			continue;
		}

		// If it's a switch
		else if (curr[0] == '-') {

			for (size_t i = 1; i < curr.length(); i++) {

				if (curr[i] == 'p') {
					commands.isParagraph = true;
				}
				else if (curr[i] == 'r') {
					commands.isReport = true;
				}

				else {
					commands.notRecognized = true;
					commands.notRecognizedChar = curr[i];
					return commands;
				}
			}
		}

		// If it's a file
		else if (curr.find(".") != std::string::npos) {
			if (commands.inputFile.empty()) {
				commands.inputFile = curr;
				fileFound = true;
			}
			else if (commands.outputFile.empty()) {
				commands.outputFile = curr;
			}

			else {
				// TODO: Add better handling for if more than 3 files have been passed
				commands.notRecognized = true;
				return commands;
			}
		}
	}

	return commands;

}

/*
 * Function:	print_help
 * purpose:		Prints the help text for the program when the --help or -h command is passed
 *
 * returns:		void
 *
 * author: 		Ryan Jennings
*/
void print_help() {
	/*
	markup v1.0.0, (c)2010 - 2023, Garth Santor

		usage : markup[--help][-rp] textFilename[htmlFilename][--keywords Args...]

		--help          display the help text for the program.
		- r              report convertion metrics
		- p              use <p> tag for paragraph breaks

		textFilename    the name of the ASCII text file to process
		htmlFilename    the name of the HTML file receiving the output.
		If not provided the text filename will be used
		with its extension changed to ".html"

		--keywords          keywords to highlight
	*/

	std::cout << "markup v1.0.0, (c)2023 - 2023, Ryan Jennings" << std::endl << std::endl;
	std::cout << "usage: markup [--help] [-r] [-p] textFilename [htmlFilename] [--keywords Args...]" << std::endl << std::endl;
	std::cout << "\t--help          display the help text for the program." << std::endl;
	std::cout << "\t-r              report conversion metrics" << std::endl;
	std::cout << "\t-p              use <p> tag for paragraph breaks" << std::endl << std::endl;
	std::cout << "\ttextFilename    the name of the ASCII text file to process" << std::endl;
	std::cout << "\thtmlFilename    the name of the HTML file receiving the output." << std::endl;
	std::cout << "\t                If not provided the text filename will be used" << std::endl;
	std::cout << "\t                with its extension changed to \".html\"" << std::endl << std::endl;
	std::cout << "\t--keywords      keywords to highlight" << std::endl;
				
}

/*
 * Function:	print_unrecognized
 * purpose:		Shows to the user that a command line argument was not recognized and prints it
 *
 * accepts:		char arg - the argument that was not recognized
 *
 * returns:		void
 *
 * author: 		Ryan Jennings
*/
void print_unrecognized(char arg) {
	std::cout << "Unrecognized argument: " << arg << std::endl;
}

/*
 * Function:	print_file_not_found
 * purpose:		Prints to the user that a file was not found
 *
 * accepts:		std::string filename - the filename that was not found
 *
 * returns:		void
 *
 * author: 		Ryan Jennings
*/
void print_file_not_found(std::string filename) {
	
	//TODO: Verify the project folder to make sure the output is correct
	std::cout << "File not found: " << filename << std::endl;

}

/*
 * Function:	find_output_file
 * purpose:		Checks to see if the user passed a file output, if not it will generate a name
 *
 * accepts:		std::string inputFilename   -	the filename that was passed in
 *				std::string &outputFilename -	the filename that will be generated or has
 *												already been passed in		
 *
 * returns:		void
 *
 * author: 		Ryan Jennings
*/
void find_output_file(std::string inputFilename, std::string &outputFilename) {
	
	// If a output filename has already been found, return
	if (outputFilename.size() != 0) {
		return;
	}

	size_t pos = inputFilename.find(".");

	if (pos == std::string::npos) {
		std::cout << "Filename invalid";
		return;
	}

	outputFilename.append(inputFilename.substr(0, pos));
	outputFilename.append(".html");

}