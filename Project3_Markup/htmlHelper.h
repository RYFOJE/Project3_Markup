#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

std::string generate_html_header(std::string title, std::vector<std::string>& keywords);
std::string generate_styling_header(std::vector<std::string>& keywords);
std::string htmlFooter();
unsigned int  surround_p(std::string& text);
unsigned int  replace_with_br(std::string & text);
unsigned int surround_helper(std::string& input, std::vector<std::string> words);