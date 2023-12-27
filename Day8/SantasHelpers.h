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
            if (!templine.empty()) stringVector.push_back(templine);
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