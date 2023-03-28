#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "htmlHelper.h"
#include "cmdHelper.h"
#include "fileHelper.h"

int main(int argc, char* argv[]) {

	/*
	 * Explanation of the program in steps
	 * 
	 * 1.	The program will read the command line arguments passed to the program
	 *		it will store the arguments in a struct called cmd_struct
	 * 
	 * 2.	The program will check for exiting conditions immediatly, it will check
	 *		to see if the user wants to access the help, or if the user passed
	 *		an invalid command.
	 * 
	 * 3.	The program will then check to see if the input file exists on the disk
	 *		and is readable.
	 * 
	 * 4.	The program then creates a string that will be used to store the formatted
	 *		output that will be written to the file
	 * 
	 * 5.	It will read the input file line by line and store the line in a string
	 * 
	 * 6.	It will then check to see if the user wants to surround paragraphs with
	 *		<p> tags. If so, it will add the surrounding tags to paragraphs
	 * 
	 * 7.	Once done the previous step, it will replace all blank lines with <br>
	 *		
	 * 8.	It will then check to see if the user has any keywords that they want to
	 *		surround with color tags. If so, it will surround the keywords with the
	 *		given color tags and will append the whole body text to the formatted string
	 * 
	 * 9.	It will then generate the footer for the html file and append it to the
	 *		formatted string
	 * 
	 * 10.	It will then write the whole formatted text to the output file
	 * 
	 * 11.	If the user wants a report, it will print the information to the console
	 * 
	*/

	// STEP 1 - Read command line arguments
	// Parse command line arguments
	cmd_struct cmd = parse_cmd(argc, argv);

	// STEP 2 - Check to see if there are any exiting conditions
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


	// STEP 3 - Check to see if the input file exists
	// If the input file does not exist
	if (!file_exists(cmd.inputFile)) {
		print_file_not_found(cmd.inputFile);
		return EXIT_FAILURE;
	}

	// STEP 4 - Create a string to store the formatted output
	std::string formattedString = "";
	
	// Generate the header for the html file
	std::string headerStr = generate_html_header("filename", cmd.keywords); //TODO: Change it so the name of the file is used
	formattedString.append(headerStr);

	
	// STEP 5 - Read the input file line by line and store it in a string
	// Create a filesystem path to the input file
	std::filesystem::path path(cmd.inputFile);
	std::string bodyText = read_from_file(path);

	unsigned int total_paragraphs = 0;

	// STEP 6 - Check to see if the user wants to surround paragraphs with <p> tags
	// If the flag -p has been used
	if (cmd.isParagraph) {
		total_paragraphs = surround_p(bodyText);
	}
	
	
	// STEP 7 - Replace all blank lines with <br>
	unsigned int total_br = 0;
	total_br = replace_with_br(bodyText);
	
	// STEP 8 - Check to see if the user has any keywords that they want to surround with color tags
	unsigned int total_surround = 0;
	total_surround = surround_helper(bodyText, cmd.keywords);
	
	formattedString.append(bodyText);
	
	
	// STEP 9 - Generate the footer for the html file and append it to the formatted string
	std::string footerStr = generate_html_footer();
	formattedString.append(footerStr);

	
	// STEP 10 - Write the whole formatted text to the output file
	find_output_file(cmd.inputFile, cmd.outputFile);
	std::filesystem::path output_path = cmd.outputFile;
	write_to_file(cmd.outputFile, formattedString);
	
	
	// STEP 10 - If the user wants a report, it will print the information to the console
	if (cmd.isReport) {
		
		unsigned int lineCount = count_lines(path);
		std::cout << "# lines input = " << lineCount << std::endl;
		
		if (total_paragraphs != 0) {
			std::cout << "# paragraphs output = " << total_paragraphs << std::endl;
		}
		
		if (total_surround != 0) {
			std::cout << "# tags = " << total_surround << std::endl;
			print_keyword_count(cmd.keywords);
		}
	}
	
	return EXIT_SUCCESS;
}