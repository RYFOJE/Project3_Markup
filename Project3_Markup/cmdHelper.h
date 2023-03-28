#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include "htmlHelper.h"

// Struct to hold command line arguments
typedef struct cmd_struct {

	bool isHelp = false;
	bool isParagraph = false;
	bool isReport = false;

	std::filesystem::path inputFile;
	std::filesystem::path outputFile;

	bool isKeyword = false;
	std::vector<keyword_struct> keywords;

	bool notRecognized = false;
	char notRecognizedChar = '0';

} cmd_struct;

// Function prototypes
cmd_struct parse_cmd(int argc, char* argv[]);
void print_help();
void print_unrecognized(char arg);
void print_file_not_found(std::filesystem::path filename);
void find_output_file(std::filesystem::path inputFilename, std::filesystem::path& outputFilename);
