#include <iostream>
#include <string>
#include <vector>
#include <sstream>


/*
 * name: htmlHeader
 *
 * description: this function will return the opening tags for an html document
 *
 * returns: a string with the opening tags for an html document
*/
std::string htmlHeader(std::string title) {

	std::string formattedString;
	

	// TODO: Add handling for style sheets
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
std::string htmlFooter() {

	std::string formattedString;

	formattedString.append("</body>\n");
	formattedString.append("</html>\n");

	return formattedString;
}

/*
 * name: surround_p
 *
 * description: this function will surround the text with <p> and </p> tags
 *
 * returns: int representing the amount of paragraphs that were surrounded wit <p> tags
 */
unsigned int surround_p(std::string& text) {

	std::string formattedString;
	std::stringstream ss(text);
	char previousChar;
	bool isParagraph = false;
	unsigned int  runningTotal = 0;

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
			runningTotal++;
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
			if (isParagraph) {
				formattedString.append("\n</p>");
			}
			break;
		}

	}

	// Reassign the text to the formatted string
	text.assign(formattedString);
	return runningTotal;

}

unsigned int replace_with_br(std::string& text) {

	std::stringstream ss(text);
	std::string tempStr;
	unsigned int runningTotal = 0;


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

	return runningTotal;
}

std::string surround(std::string& input, std::string search, std::string opening, std::string closing) {

	std::string tempStr;
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
			std::cout << "Substring \"" << search << "\" found at position " << pos << ". offsetting to: " << currOffset << std::endl;

			input.insert(currOffset, closing);
			input.insert(pos, opening);

			currOffset += openingWordLen + closingWordLen;

		}
	}
}
