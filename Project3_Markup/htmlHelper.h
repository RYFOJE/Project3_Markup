#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

string htmlHeader(string title);
string htmlFooter();
void surround_p(string& text);
void consume_nl(string& text);
string replace_with_br(string& text);
string surround(string& input, string search, string opening, string closing);