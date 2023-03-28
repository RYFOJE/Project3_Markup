#pragma once
#include <string>

std::string filename_no_extension(const std::filesystem::path& fpath);
std::string read_from_file(std::filesystem::path path);
bool file_exists(std::filesystem::path file);
unsigned int count_lines(std::filesystem::path path);
void write_to_file(std::filesystem::path path, std::string& text);