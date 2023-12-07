// Day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
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

//part two
multimap<int, int> gearMap; //first int is the gear position, second int is the ratio number

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

//for part two
//returns the index of the gear
int checkPartGearValidity(puzzlePartNumber part)
{

    int gearIndex = 0;

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
            if (puzzleLine[j] == '*')
            {
                char specialChar = puzzleLine[j];
                cout << specialChar;
                std::cout << "found valid part: " << "Line " << part.partLine << "; " << "Number " << part.partNumber << "\n";
                
                gearIndex = i * puzzleLine.size() + j;

                return gearIndex;
            }
        }

    }

    return gearIndex;
}

//for part one - parses string for integer part numbers and creates part
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
            if (stream >> num) //this attempts to extract an integer from the stream. If successful, it evaluates true, sets num to the int extracted, and advances index to the end of the int)
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

void parsePartNumbersPartTwo(const std::string& str, int puzzleLineIndex)
{
    std::istringstream stream(str);
    char ch;
    int num;

    while (stream >> ch)
    {
        if (isdigit(ch))
        {
            stream.unget();
            if (stream >> num) //this attempts to extract an integer from the stream. If successful, it evaluates true, sets num to the int extracted, and advances index to the end of the int)
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
                int gear = checkPartGearValidity(partNo);
                
                gearMap.insert({ gear, partNo.partNumber });

                puzzleParts.push_back(partNo);
                
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
    cout << "Part 1 Total: " << runningTotal;

    return 0;
}

int dayThreePartTwo()
{
    //only look for numbers adjacent to *
    //when one is found, add it to a multimap with key value equivalent to the index of * (index is found by row*column)
    //when all numbers are found, do a for each (?) in the multimap and look for equivalent keys
    //if two are found, multiply the values together, add to the running sum


    parsePuzzleLines("Day3.txt");
    runningTotal = 0;
    for (int i = 0; i < puzzleLines.size(); i++)
    {
        parsePartNumbersPartTwo(puzzleLines[i], i);
    }

    vector<int> countedGears = {};

    for (auto it = gearMap.begin(); it != gearMap.end(); ++it) 
    {
        int gearNumCount = 0;

        int gearIndex = it->first;

        //check that there are only two values for this gear index
        if (gearMap.count(gearIndex) != 2) continue;

        //making sure we don't count gears twice
        if (find(countedGears.begin(), countedGears.end(), gearIndex) != countedGears.end()) continue;

        countedGears.push_back(gearIndex);

        auto range = gearMap.equal_range(gearIndex);
        int gearRatio = 1;

        for (auto i = range.first; i != range.second; ++i) {
            gearRatio *= i->second;
            std::cout << i->first << " index gear has number: " << i->second << '\n';
        }
        runningTotal += gearRatio;
    }

    std::cout << "gear total: " << runningTotal;
    return 0;
}

int main()
{
    //dayThreePartOne();
    dayThreePartTwo();

}


