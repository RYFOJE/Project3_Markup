#include <iostream>
#include <fstream>
#include <string>



using namespace std;


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
	cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

	textAndSpacing text = get_text_spacing();

	string calculatedStr = surround_p(text);

	cout << calculatedStr;

    return 0;
}