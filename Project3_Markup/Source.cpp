#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "htmlHelper.h"
#include "cmdHelper.h"
#include "fileHelper.h"

int main(int argc, char* argv[]) {

	// Parse command line arguments
	cmd_struct cmd = parse_cmd(argc, argv);

	// If the user wants to access the help
	if (cmd.isHelp) {
		print_help();
		return EXIT_SUCCESS;
	}
	
	// If the command line arguments are not recognized
	else if(cmd.notRecognized) {
		print_unrecognized(cmd.notRecognized);
		return EXIT_FAILURE;
	}

	// If the input file does not exist
	if (!file_exists(cmd.inputFile)) {
		print_file_not_found(cmd.inputFile);
		return EXIT_FAILURE;
	}


	std::string formattedString = "";
	
	// Generate the header for the html file
	std::string headerStr = generate_html_header("filename", cmd.keywords); //TODO: Change it so the name of the file is used
	formattedString.append(headerStr);

	
	// Create a filesystem path to the input file
	std::filesystem::path path(cmd.inputFile);

	// Read bodyText from file and store it in a string for further processing
	std::string bodyText = read_from_file(path);

	unsigned int total_paragraphs = 0;

	// If the flag -p has been used
	if (cmd.isParagraph) {
		total_paragraphs = surround_p(bodyText);
	}

	// Always needs to replace newlines with <br>
	unsigned int total_br = 0;
	total_br = replace_with_br(bodyText);
	
	unsigned int total_surround = 0;
	total_surround = surround_helper(bodyText, cmd.keywords);
	
	formattedString.append(bodyText);
	
	// Generate the footer for the html file
	std::string footerStr = generate_html_footer();
	formattedString.append(footerStr);

	std::cout << formattedString;
	write_to_file(std::filesystem::path("output.txt"), formattedString); //TODO: Replace with not hardcoded file out
	
	// If the user wants a report
	if (cmd.isReport) {
		
		unsigned int lineCount = count_lines(path);
		std::cout << std::endl << "# lines input = " << lineCount << std::endl;
		
		if (total_paragraphs != 0) {
			std::cout << "# paragraphs output = " << total_paragraphs << std::endl;
		}
		
		if (total_surround != 0) {
			std::cout << "# tags = " << total_surround << std::endl;
		}
	}
	
	return EXIT_SUCCESS;
}