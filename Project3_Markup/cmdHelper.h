#pragma once

#include <string>
#include <vector>
#include <iostream>

// Struct to hold command line arguments
typedef struct cmd_struct {

	bool isHelp = false;
	bool isParagraph = false;
	bool isReport = false;

	std::string inputFile = "";
	std::string outputFile = "";

	bool isKeyword = false;
	std::vector<std::string> keywords;

	bool notRecognized = false;
	char notRecognizedChar = '0';

} cmd_struct;

// Function prototypes
void print_cmd_struct(cmd_struct cmds);
cmd_struct parse_cmd(int argc, char* argv[]);
void print_help();
void print_unrecognized(char arg);
void print_file_not_found(std::string filename);
void find_output_file(const std::string inFilename, std::string &outFilename);
