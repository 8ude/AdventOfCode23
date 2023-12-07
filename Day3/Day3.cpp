// Day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;



struct puzzlePartNumber
{
    int partNumber;
    int partNumLength;
    int partStartIndex;
    int partLine;
};

vector<string> puzzleLines;
vector<puzzlePartNumber> puzzleParts;

int runningTotal;

void parsePuzzleLines(const string& filePath) {
    ifstream file(filePath);
    std::string tempLine;

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    while (std::getline(file, tempLine)) 
    {
        puzzleLines.push_back(tempLine);
    }
}

int checkPartNumberValidity(puzzlePartNumber part)
{
    int partValue = 0;

    for (int i = part.partLine - 1; i <= part.partLine + 1; i++)
    {
        if (i < 0 || i >= puzzleLines.size())
        {
            continue;
        }
        string puzzleLine = puzzleLines[i];
        for (int j = part.partStartIndex - 1; j < part.partStartIndex + part.partNumLength + 1; j++)
        {
            if (j < 0 || j > puzzleLine.size())
            {
                continue;
            }
            if (!std::isdigit(puzzleLine[j]) && puzzleLine[j] != '.')
            {
                char specialChar = puzzleLine[j];
                cout << specialChar;
                std::cout << "found valid part: " << "Line " << part.partLine << "; " << "Number " << part.partNumber << "\n";
                partValue = part.partNumber;
                return partValue;
            }
        }

    }

    return partValue;
}

/// <summary>
/// parses a string for integers
/// </summary>
/// <param name="str"></param>
void parsePartNumbers(const std::string& str, int puzzleLineIndex) 
{

    std::istringstream stream(str);
    char ch;
    int num;

    while (stream >> ch) 
    {
        if (isdigit(ch)) 
        {
            stream.unget();
            if (stream >> num) //this attempts to extract an integer from the stream. If successful, it evaluates true (and also sets num to the int extracted)
            {
                puzzlePartNumber partNo;
                partNo.partNumber = num;
                partNo.partLine = puzzleLineIndex;
                partNo.partNumLength = (int)std::to_string(num).length();
                if ((int)stream.tellg() == -1) // note that stream.tellg can return -1 if it's out of bounds
                {
                    partNo.partStartIndex = str.length() - 1 - partNo.partNumLength;
                } 
                else
                {
                    partNo.partStartIndex = (int)stream.tellg() - partNo.partNumLength;
                }
                
                runningTotal += checkPartNumberValidity(partNo);
                cout << "total valid parts: " << runningTotal <<"\n";
            }
        }
       
    }
    
}


int dayThreePartOne()
{
    //basic version:
    //store each line
    //identify number start index, number end index
    //look for symbols at
    //prior line (number_start - 1) to (number_end + 1)
    //current line (number_start - 1); current line (number_end + 1)
    //next line (number_start - 1) to (number_end + 1)

    parsePuzzleLines("Day3.txt");
    runningTotal = 0;
    for (int i = 0; i < puzzleLines.size(); i++)
    {
        parsePartNumbers(puzzleLines[i], i);
    }
    return 0;
}

int dayThreePartTwo()
{
    //look for '*' instead??
    //set ratio ints to zero initially
    //scan prior and next lines in box around gear
    //when int is found, find the full int.. somehow
    //when second int is found, find full int as well 
    //if a third int is found, return 0
    //return first times second gear -- add to running total

    //OR
    //replace valid part num to look only for gear
    //when valid part is found, add to a gear struct
}

int main()
{
    dayThreePartOne();
    cout << "Final Total: " << runningTotal;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

