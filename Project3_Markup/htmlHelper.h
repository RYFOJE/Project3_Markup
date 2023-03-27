#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

std::string htmlHeader(std::string title);
std::string htmlFooter();
unsigned int  surround_p(std::string& text);
void consume_nl(std::string& text);
unsigned int  replace_with_br(std::string & text);
std::string surround(std::string& input, std::string search, std::string opening, std::string closing);