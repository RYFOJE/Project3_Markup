#include <iostream>
#include <fstream>
#include <string>



using namespace std;



string print_whole_file() {

	string tempStr;

	while (true) {

		char c = cin.get();
		tempStr.push_back(c);


		if (cin.eof()) {
			cout << "EOF\n";
			return tempStr;
		}

		else if (c == '\n') {
			cout << "\\n\n";
		}

		else {
			cout << c;
		}

	}

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
			std::cout << "Substring \"" << search <<"\" found at position " << pos << ". offsetting to: " << currOffset << endl;

			input.insert(currOffset, closing);
			input.insert(pos, opening);

			currOffset += openingWordLen + closingWordLen;

		}

	}


}


int main() {

	string fileName = "test.txt";
	

	// https://stackoverflow.com/questions/10150468/how-to-redirect-cin-and-cout-to-files
	ifstream in(fileName);
	cin.rdbuf(in.rdbuf()); //redirect

	string text = print_whole_file();


	string formattedText = surround(text, "red", "<open>", "<close>");

	//cout << endl << endl;

	

	cout << text;


	return 0;
}