#pragma once
#include <string>
#include <vector>
#include <sstream>

using namespace std;

std::vector<std::string> splitString(const std::string& s, char delimiter) {
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> tokens;

	while (std::getline(ss, item, delimiter)) {
		tokens.push_back(item);
	}

	return tokens;
}

vector<string> ParseString(const string& line, const string& delimiters) {
	vector<string> chunks;
	size_t start_pos = 0;
	size_t delim_pos = line.find_first_of(delimiters);

	while (delim_pos != std::string::npos) {
		std::string chunk = line.substr(start_pos, delim_pos - start_pos);
		if (chunk.length() > 0) {
			chunks.push_back(line.substr(start_pos, delim_pos - start_pos));
		}
		start_pos = delim_pos + 1;
		delim_pos = line.find_first_of(delimiters, start_pos);
	}

	if (start_pos < line.size()) {
		std::string chunk = line.substr(start_pos);
		if (chunk.length() > 0) {
			chunks.push_back(line.substr(start_pos));
		}
	}

	return chunks;
}