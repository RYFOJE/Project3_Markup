#include <iostream>
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

typedef struct textAndSpacing
{
	string text;
	int spacing = 0;

} textAndSpacing;

/*
 * name: htmlHeader
 *
 * description: this function will return the opening tags for an html document
 *
 * returns: a string with the opening tags for an html document
*/
string htmlHeader(string title) {

    string formattedString;

	formattedString.append("<!DOCTYPE html>\n");
	formattedString.append("<html>\n");
	formattedString.append("<head>\n");
	formattedString.append("<title>");
	formattedString.append(title);
	formattedString.append("</title>\n");
	formattedString.append("</head>\n");
	formattedString.append("<body>\n");

	return formattedString;
}

/*
 * name: htmlFooter
 *
 * description: this function will return the closing tags for an html document
 *
 * returns: a string with the closing tags for an html document
*/
string htmlFooter() {

    string formattedString;

	formattedString.append("</body>\n");
	formattedString.append("</html>\n");

    return formattedString;
}

/*
 * name: surround_p
 * 
 * description: this function will surround the text with <p> and </p> tags
 * 
 * returns: a string with the text surrounded by <p> and </p> tags
 */
string surround_p(textAndSpacing textStruct) {

	string formattedString;

    formattedString.append("<p>\n");
	formattedString.append(textStruct.text);
	formattedString.append("\n</p>\n");
    
	for (size_t i = 0; i < textStruct.spacing; i++) {
		formattedString.append("<br>\n");
	}

	return formattedString;

}

/*
 *  
*/
string insert_br(string text) {

	string formattedString = "<br>\n";
	
	return formattedString;
}

string replace_with_br() {

	string tempStr;

	while (true) {

		char c = cin.get();
		char cp = cin.peek();

		// This will add a newline char
		if (c == '\n' && (cp == '\n' || cp == EOF)) {
			tempStr.append("\n<br>");

		}
		
		else {
			// Add the current character to the file
			tempStr.push_back(c);
		}

		// If cin has hit an eof (Keep in mind this will get triggered even when cin.peek() hits an EOF)
		if (cin.eof()) {
			break;
		}

	}

	return tempStr;

}

void debug_print_buffer() {

	cout << "Start print debug:" << endl;


	streampos pos = std::cin.tellg();


	while (true) {

		char c = cin.get();

		if (c == EOF) {
			break;
		}

		else if (c == '\n') {
			cout << "\\n" << endl;
		}

		else {
			cout << c;
		}

	}

	cin.seekg(pos);

	cout << endl << "End print debug:" << endl;

}

textAndSpacing get_text_spacing() {
	
	textAndSpacing textStruct;
	string foundText;

	//debug_print_buffer();


	// This will get all the text to be surrounded by <p>
	while (true) {
		
		char c = cin.get();
		char cp = cin.peek();

		textStruct.text += c;

		// These are the Exit conditions
		if (c == '\n' && cp == '\n') {
			cin.get();
			break;
		}

		else if (cp == EOF) {
			textStruct.text.pop_back();
			return textStruct;
		}

	}

	textStruct.text.pop_back();

	// This will get the total amount of blank lines after the end of the paragraph
	while (true) {
		
		// Get the next char
		char c = cin.get();

		// If it's a newline increase count by one
		if (c == '\n') {
			textStruct.spacing++;
		}

		else {

			if (c == EOF) {
				textStruct.spacing++;
			}

			cin.unget();
			break;
		}

	}

	return textStruct;

}

string surround(string& input, string search, string opening, string closing) {

	string tempStr;
	size_t currOffset = 0;
	size_t currIndex = 0;

	size_t searchWordLen = search.length();
	size_t openingWordLen = opening.length();
	size_t closingWordLen = closing.length();

	while (true) {

		size_t pos = input.find(search, currOffset);

		if (pos == std::string::npos) {
			std::cout << "Substring not found" << std::endl;
			return input;
		}
		else {
			currOffset = pos + searchWordLen;
			std::cout << "Substring \"" << search << "\" found at position " << pos << ". offsetting to: " << currOffset << endl;

			input.insert(currOffset, closing);
			input.insert(pos, opening);

			currOffset += openingWordLen + closingWordLen;

		}

	}


}


bool fileExists(string fileName) {
	std::ifstream infile(fileName.c_str());
	return infile.good();
}

int main() {
    
	string fileName = "test.txt";

	if (fileExists(fileName)) {
		cout << "File exists" << endl;
	}

	else {
		cout << "File doesnt exist" << endl;
		return 0;
	}

	// https://stackoverflow.com/questions/10150468/how-to-redirect-cin-and-cout-to-files
	ifstream in(fileName);
	cin.rdbuf(in.rdbuf()); //redirect

	string text = replace_with_br();

	cout << text;

    return 0;
}