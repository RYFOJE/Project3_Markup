#pragma once
#include <string>

std::string read_from_file(std::filesystem::path path);
bool file_exists(std::string fileName); //TODO Change to file 
unsigned int count_lines(std::filesystem::path path);
void write_to_file(std::filesystem::path path, std::string& text);