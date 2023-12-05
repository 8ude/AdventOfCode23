// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <vector>
#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>

using namespace std;

static const vector<string> numbersStrings{ "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

std::vector<std::string> readFileIntoVector(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> lines;
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }
    else {
        // Optional: Handle error here when unable to open the file
        std::cout << "Unable to open file" << "\n";
    }

    return lines;
}

std::vector<int> parseDigitsFromString(std::string str) {
    std::vector<int> intVector;

    for (char c : str) {
        if (isdigit(c)) {
            intVector.push_back(c - '0'); // Subtract '0' to convert char digit to int
        }
    }

    return intVector;
}

//concatanate vectors
int concat(int a, int b)
{

    // Convert both the integers to string 
    string s1 = to_string(a);
    string s2 = to_string(b);

    // Concatenate both strings 
    string s = s1 + s2;

    // Convert the concatenated string 
    // to integer 
    int c = stoi(s);

    // return the formed integer 
    return c;
}


void dayOnePartOne() {
    //steps: 
    //parse file via newline into a resizable array (i guess a vector is best for cpp?)
    //parse each element for integers ===> new vector
    //concatenate the first and last element of that integer vector into an integer (double it if only one int for the string)
    //find the sum of all of them


    const auto filename = "Day1Pt1.txt.txt";
    auto allLines = readFileIntoVector(filename);
    int total = 0;

    for (auto line : allLines)
    {
        auto numbers = parseDigitsFromString(line);
        auto first = numbers[0];
        auto last = numbers[numbers.size() - 1];
        int lineResult = concat(first, last);
        // per-line sanity check --- std::cout << lineResult << "\n";
        total += lineResult;
        std::cout << "running total: " << total << "\n";
    }

}


int findFirstNumber(std::string str) {
   
    //checking a substring of that length at every position
    for (size_t pos = 0; pos <= str.size() - 1; ++pos)
    {
        //first check for integers
        if (isdigit(str[pos]))
            return str[pos] - '0';
        //go through every possible length of characters - max is five characters
        for (size_t len = 3; len <= 5; ++len)
        {
            
            if (len + pos > str.size())
            {
                continue;
            }
            //checking against the number strings 
            for (size_t numIndex = 0; numIndex < numbersStrings.size(); numIndex++)
            {
                //std::cout << "looking for text: " << pos << " " << len << "number: " << numbersStrings[numIndex] << "\n";
                if (str.substr(pos, len) == numbersStrings[numIndex])
                    return numIndex;
            }
        }
    }
    return 0;
}

int findLastNumber(std::string str)
{
    //checking a substring of that length at every position -- going backwards
    for (int pos = str.size(); pos >= 0; --pos)
    {
        //first check for integers
        if (isdigit(str[pos]))
            return str[pos] - '0';
        //go through every possible length of characters - min is three, max is five characters
        for (int len = 3; len <= 5; ++len)
        {
            
            //check if we're at the end
            if (pos - len < 0)
            {
                continue;
            }
            //checking against the number strings 
            for (int numIndex = 0; numIndex < numbersStrings.size(); numIndex++)
            {
                //std::cout << "looking for last number: " << pos << " " << len << " " << "number: " << numbersStrings[numIndex] << "\n";
                if (str.substr(pos-len, len) == numbersStrings[numIndex])
                    return numIndex;
            }
        }
    }
    return 0;
}

void dayOnePartTwo() {
    //steps: 
    //parse file via newline into a resizable array (i guess a vector is best for cpp?)
    //parse each element for integers ===> new vector
    //concatenate the first and last element of that integer vector into an integer (double it if only one int for the string)
    //find the sum of all of them


    const auto filename = "Day1Pt1.txt.txt";
    auto allLines = readFileIntoVector(filename);
    int total = 0;

    for (auto line : allLines)
    {
        auto first = findFirstNumber(line);
        auto last = findLastNumber(line);
        int lineResult = 10 * first + last;
        //per-line sanity check --- 
        std::cout << lineResult << "\n";
        total += lineResult;
        std::cout << "running total: " << total << "\n";
    }

}


int main() {
    //dayOnePartOne();
    dayOnePartTwo();

    return 0;
}
