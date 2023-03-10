/* #include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

typedef struct cmd_struct {

	bool isHelp = false;
	bool isParagraph = false;
	bool isReport = false;

	string inputFile = "";
	string outputFile = "";

	bool isKeyword = false;
	vector<string> keywords;
	
	bool notRecognized = false;
	char notRecognizedChar = '0';

} cmd_struct;

void print_cmd_struct(cmd_struct cmds) {
	
	cout << "isHelp: " << cmds.isHelp << endl;
	cout << "isParagraph: " << cmds.isParagraph << endl;
	cout << "isReport: " << cmds.isReport << endl;
	cout << "inputFile: " << cmds.inputFile << endl;
	cout << "outputFile: " << cmds.outputFile << endl;
	cout << "isKeyword: " << cmds.isKeyword << endl;
	cout << "keywords: ";
	for (size_t i = 0; i < cmds.keywords.size(); i++) {
		cout << ", " << cmds.keywords[i];
	}

	cout << endl;
	cout << "notRecognized: " << cmds.notRecognized << endl;
	cout << "notRecognizedChar: " << cmds.notRecognizedChar << endl;

}

cmd_struct find_args(int argc, char* argv[]) {

	cmd_struct commands;
	bool fileFound = false;

	for (size_t i = 1; i < argc; i++) {
		
		string curr = argv[i];

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
		else if (curr.find(".") != string::npos) {
			if (!fileFound) {
				commands.inputFile = curr;
				fileFound = true;
			}
			else {
				commands.outputFile = curr;
			}
		}
	}

	return commands;

}


int main(int argc, char* argv[]) {

	cmd_struct cmds = find_args(argc, argv);

	print_cmd_struct(cmds);
	
}*/