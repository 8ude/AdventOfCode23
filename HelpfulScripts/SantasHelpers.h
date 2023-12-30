#pragma once
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

vector<string> parseLinesIntoStrings(const string& filename, bool debug = false)
{
	vector<string> stringVector;
    ifstream file(filename);
    string templine;
    if (!file.is_open())
    {
        cout << "could not open file";
    }
    else
    {
        while (std::getline(file, templine))
        {
            stringVector.push_back(templine);
            
        }

        file.close();
    }
    if (debug)
    {
        for (string& line : stringVector)
        {
            cout << line << "\n";
        }
    }
    
    return stringVector;
}

vector<string> splitString(const string& s, char delimiter) {
    stringstream ss(s);
    string item;
    vector<string> tokens;

    while (getline(ss, item, delimiter)) {
        tokens.push_back(item);
    }

    return tokens;
}

//Kris Hole version
std::vector<std::string> ParseString(const std::string& line, const std::string& delimiters) {
    std::vector<std::string> chunks;
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