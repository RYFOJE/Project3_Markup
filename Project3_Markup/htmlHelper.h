#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "htmlHelper.h"


typedef struct keyword_struct {

	std::string keyword = "";
	unsigned int count = 0;

	// This is the color associated with the keyword
	std::string associatedColor = "";

} keyword_struct;

std::string generate_html_header(std::string title, std::vector<keyword_struct>& keywords);
std::string generate_styling_header(std::vector<std::string>& keywords);
std::string generate_html_footer();
unsigned int  surround_p(std::string& text);
unsigned int  replace_with_br(std::string & text);
unsigned int surround_helper(std::string& input, std::vector<keyword_struct> &words);
void print_keyword_count(std::vector<keyword_struct> keywords);
void print_keyword_count(std::vector<keyword_struct> keywords);
keyword_struct create_keyword_struct(std::string keyword);
