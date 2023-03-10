#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

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
 * returns: void
 */
void surround_p(string& text) {

	string formattedString;
	stringstream ss(text);
	char previousChar;
	bool isParagraph = false;

	if (ss.peek() != '\n') {
		formattedString.append("<p>\n");
		isParagraph = true;
	}

	while (true) {

		char c = ss.get();
		char cp = ss.peek();

		// If it's the end of paragraph
		if (isParagraph && c == '\n' && cp == '\n') {
			formattedString.append("\n</p>\n");
			isParagraph = false;
		}

		// If it's the start of a paragraph
		else if (!isParagraph && c == '\n' && (cp != '\n' && cp != EOF)) {
			formattedString.append("<p>\n");
			isParagraph = true;
		}

		else {
			formattedString.push_back(c);
		}

		// If it's the end of the file
		if (ss.eof()) {
			break;
		}

	}

	// Reassign the text to the formatted string
	text.assign(formattedString);

}

void consume_nl(string& text) {

	stringstream ss(text);
	string tempString;

	// If the first character is a newline, remove it
	if (ss.peek() == '\n') {
		ss.get();
	}

	while (true) {

		char c = ss.get();
		char cp = ss.peek();

		if (c == '\n' && (cp == '\n' || cp == EOF)) {
			continue;
		}

		else {
			tempString.push_back(c);
		}

		if (ss.eof()) {
			break;
		}

	}

	// Reassign emptied string
	text.assign(tempString);

}

string replace_with_br(string& text) {

	stringstream ss(text);
	string tempStr;

	while (true) {

		char c = ss.get();
		char cp = ss.peek();

		// This will add a newline char
		if (c == '\n' && (cp == '\n' || cp == EOF)) {
			tempStr.append("\n<br>");

		}

		else {
			// Add the current character to the file
			tempStr.push_back(c);
		}

		// If cin has hit an eof (Keep in mind this will get triggered even when cin.peek() hits an EOF)
		if (ss.eof()) {
			break;
		}

	}

	// Reassign the text to the formatted string
	text.assign(tempStr);
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
