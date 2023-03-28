/*
 * File:		htmlHelper.cpp
 * Purpose:		This file contains the functions that will be used to generate the html document
 * 
 * Author:		Ryan Jennings
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "htmlHelper.h"

// This vector holds all the colors that can be selected for coloring the text
std::vector<std::string> colorList = { "Aqua", "Blue", "Green", "BlueViolet", "Crimson", "Red", "DarkBlue", "DarkOrange",
										"Fuchsia", "Lime", "Magenta", "Maroon", "Navy", "SeaGreen", "Tomato" };




/*
 * Function:	generate_styling_header
 * purpose:		This function will generate the styling header for the html document
 *
 * accepts:		std::vector<std::string>& keywords - a vector of keywords that will be used to generate the styling
 *
 * returns:		std::string - a string with the styling header
 *
 * author: 		Ryan Jennings
*/
std::string generate_styling_header(std::vector<keyword_struct> &keywords) {

	std::string formattedString;

	if (keywords.size() == 0) {
		return formattedString;
	}

	formattedString.append("<style>\n");

	// Iterate through the color list and add each one to a style list
	for (size_t i = 0; i < keywords.size(); i++) {
		std::string color = colorList.at(i);

		formattedString.append("key-" + color + " { color: " + color + " }\n");
	}

	formattedString.append("</style>\n");

	return formattedString;
}

/*
 * Function:	generate_html_header
 * purpose:		This function will generate the header for the html document
 *
 * accepts:		std::string title - the title of the html document
 *				std::vector<std::string>& keywords - a vector of keywords that will be used to generate the styling
 * 
 * returns:		std::string - a string with the header for the html document
 *
 * author: 		Ryan Jennings
*/
std::string generate_html_header(std::string title, std::vector<keyword_struct> &keywords) {

	std::string formattedString;
	

	// TODO: Add handling for style sheets
	formattedString.append("<!DOCTYPE html>\n");
	formattedString.append("<html>\n");
	formattedString.append("<head>\n");
	formattedString.append("<title>");
	formattedString.append(title);
	formattedString.append("</title>\n");
	formattedString.append(generate_styling_header(keywords));
	formattedString.append("</head>\n");
	formattedString.append("<body>\n");

	return formattedString;
}

/*
 * Function:	genereate_html_footer
 * purpose:		This function will generate the footer for the html document
 * 
 * accepts:		none
 *
 * returns:		std::string - a string with the footer for the html document
 *
 * author: 		Ryan Jennings
*/
std::string generate_html_footer() {

	std::string formattedString;

	formattedString.append("\n</body>\n");
	formattedString.append("</html>");

	return formattedString;
}

/*
 * Function:	surround_p
 * purpose:		surrounds all paragraphs with <p> tags
 *
 * accepts:		std::string& text - the text to be formatted
 *
 * returns:		usigned int - the number of paragraphs that were found
 *
 * author: 		Ryan Jennings
*/
unsigned int surround_p(std::string& text) {

	std::string formattedString;
	std::stringstream ss(text);
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

/*
 * Function:	replace_with_br
 * purpose:		replaces all blank lines with <br> tags
 *
 * accepts:		std::string &text - the text to be formatted
 *
 * returns:		unsigned int - the number of blank lines that were found
 *
 * author: 		Ryan Jennings
*/
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

/*
 * Function:	surround_with_tags
 * purpose:		surrounds all instances of a word with a given tag
 *
 * accepts:		std::string& input - the text to be formatted
 *				std::string search - the word to be searched for
 *				std::string opening - the opening tag
 *				std::string closing - the closing tag
 *
 * returns:		unsigned int - the number of times the word was found
 *
 * author: 		Ryan Jennings
*/
unsigned int surround_with_tags(std::string& input, std::string search, std::string opening, std::string closing) {

	std::string tempStr;
	size_t currOffset = 0;
	size_t currIndex = 0;
	unsigned int runningTotal = 0;

	size_t searchWordLen = search.length();
	size_t openingWordLen = opening.length();
	size_t closingWordLen = closing.length();

	while (true) {

		size_t pos = input.find(search, currOffset);

		if (pos == std::string::npos) {
			return runningTotal;
		}
		else {
			currOffset = pos + searchWordLen;
			runningTotal++;

			input.insert(currOffset, closing);
			input.insert(pos, opening);

			currOffset += openingWordLen + closingWordLen;

		}
	}
}

/*
 * Function:	surround_helper
 * purpose:		this is a helper function for surround_with_tags
 *
 * accepts:		std:::string &input - the text to be formatted
 *				std::vector<std::string> words - the words to be searched for
 *
 * returns:		unsigned int - the number of times the words were found
 *
 * author: 		Ryan Jennings
*/
unsigned int surround_helper(std::string& input, std::vector<keyword_struct> &words) {

	unsigned int runningTotal = 0;

	// Iterate through the whole array of words that need to be stylized
	for (size_t i = 0; i < words.size(); i++) {

		size_t color_index = i % colorList.size();

		words.at(i).associatedColor = colorList[color_index];

		std::string openingTag = "<key-" + colorList[color_index] + ">";
		std::string closingTag = "</key-" + colorList[color_index] + ">";

		unsigned int totalFound = surround_with_tags(input, words.at(i).keyword, openingTag, closingTag);

		// Associate the amount of words found and add it to the running total
		words.at(i).count = totalFound;
		runningTotal += totalFound;
	}

	return runningTotal;

}

/*
 * Function:	print_keyword_count
 * purpose:		prints the number of times a keyword was found
 *
 * accepts:		 std::vector<keyword_struct> keywords - the vector of keywords
 *
 * returns:		void
 *
 * author: 		Ryan Jennings
*/
void print_keyword_count(std::vector<keyword_struct> keywords) {

	for (size_t i = 0; i < keywords.size(); i++) {

		std::cout << "\t# " << keywords.at(i).keyword << "(" << keywords.at(i).associatedColor << ")" <<
			" = " << keywords.at(i).count << std::endl;

	}

}

/*
 * Function:	create_keyword_struct
 * purpose:		creates a struct for a keyword
 *
 * accepts:		std::string keyword - the keyword to be added
 *
 * returns:		keywords_struct - the struct that was created
 *
 * author: 		Ryan Jennings
*/
keyword_struct create_keyword_struct(std::string keyword) {

	keyword_struct temp;
	temp.keyword = keyword;
	temp.count = 0;

	return temp;
}