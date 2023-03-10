#include <iostream>
#include <fstream>
#include <string>

#include "htmlHelper.h"
#include "cmdHelper.h"
#include "fileHelper.h"

using namespace std;

int main(int argc, char* argv[]) {

	string fileName = "test.txt";

	// https://stackoverflow.com/questions/10150468/how-to-redirect-cin-and-cout-to-files
	ifstream in(fileName);
	cin.rdbuf(in.rdbuf()); //redirect



	// Introduction to the program, Parse command line arguments
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
	if (!fileExists(cmd.inputFile)) {
		print_file_not_found(cmd.inputFile);
		return EXIT_FAILURE;
	}



	// Read text from file and store it in a string for further processing
	string text = read_from_file();
	
	if (cmd.isParagraph) {
		//surround_paragraph(text);
		cout << text;
	}


	

	
	
	surround_p(text);
	consume_nl(text);

	cout << text;


    return 0;
}