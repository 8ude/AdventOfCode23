// Day19.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include "SantasHelpers.h"

using namespace std;

struct partVector
{
    int x;
    int m;
    int a;
    int s;
};

struct rule
{
    char specialChar;
    char m_compVar;
    char m_comparitor;
    int m_compValue;
    string m_dest;
};

struct step
{
    string m_stepID;
    vector<rule> stepRules;
};

vector<partVector> parts;

void splitRuleString(const std::string& str) {
    

    std::istringstream ss(str);
    std::string token;

    string ruleString;

    while (std::getline(ss, token, ',')) {
        // Check if token contains '{' or '}', remove them
        if (token.find('{') != std::string::npos || token.find('}') != std::string::npos) {

            // Remove '{'
            size_t pos = token.find('{');
            if (pos != string::npos)
                token.erase(pos, 1);

            // Remove '}'
            pos = token.find('}');
            if (pos != string::npos)
                token.erase(pos, 1);
        }

        rule newRule;
        newRule.m_comparitor = '=';
        newRule.m_compValue = 0;
        newRule.m_compVar = 'x';

        if (token.size() == 1)
        {
            newRule.specialChar = token[0];
            if (newRule.specialChar == 'R')
            {
                //reject
            }
        }

        if(token.find('<') != string::npos) {
            size_t pos = token.find('<');
            size_t destDelim = token.find(':');
            newRule.m_compVar = token[0];
            newRule.m_compValue = stoi(token.substr(pos, token.size()-pos))
        }

        // print tokens without { and }
        std:cout << "Token: " << token << "\n";
    }
}

void splitPartString(const std::string& str)
{

}

void parseFile(const string& filename)
{
    //if the string starts with a letter - rule
    //if it starts with curly bracket - partVector

    ifstream file(filename);
    string tempLine;

    if (!file.is_open()) {
        cout << "Could not open file";
    }
    while (std::getline(file, tempLine))
    {
}

void partOne()
{
    
    /* 
    parsing step rules:
    regex to get comparitor statement and destination
    foreach part in parts
    foreach step in steps
    trace path:
    if */
}

/*
int main()
{
    const auto input_str = "rfg{s<537:gd,x>2440:R,A}";
    split_string(input_str);

}
*/

int main() {

    std::string line = ;
    const std::regex exp_regex("(\\w+)\\s*([<>]=?)\\s*(\\d+)");

    while (std::getline(inFile, line)) {
        std::smatch match_results;

        if (std::regex_search(line, match_results, exp_regex)) {

            // The first matching group will have the variable name 
            auto var_name = match_results[1].str();

            // Second matching group is operator 
            auto op = match_results[2].str();

            // Third matching group is value
            int value = stoi(match_results[3]);

            /* Here you can decide what exactly you want to do with your translated expressions,
               For instance in this case we are generating function call */

            cout << "compareFunction(\"" << var_name << "\", \"" << op << "\"," << value << ");" << endl;

        }
    }

    return 0;
}
