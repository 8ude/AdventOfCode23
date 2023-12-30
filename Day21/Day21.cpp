// Day21.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

struct gardenSpace
{
    int row;
    int col;
    char space; //each one can be S (first step only) . 0 or #
};

vector<vector<gardenSpace>> gardenMap; 
vector<gardenSpace> potentialSpaces; //every space that was a 0 on this step 
vector<gardenSpace> spacesToFlip; //every space that needs to flip from '.' to '0' or vice versa on the next step

void parseFilePtOne(const string& filename)
{
    ifstream file(filename);
    string tempLine;
    int lineIndex = 0; //why do i need so many damn indeces????

    if (!file.is_open()) {
        cout << "Could not open file";
    }
    else
    {
        while (std::getline(file, tempLine))
        {
            for (int i = 0; i < tempLine.size(); i++)
            {
                gardenSpace newSpace;
                newSpace.row = lineIndex;
                newSpace.col = i;
                newSpace.space = tempLine[i];
            }
            lineIndex++;
        }
    }
}

void partOne()
{
    //brute-forcer:
    //build grid of char
    //
    //First step:
    //go through 4 spaces around S
    //if space is not #, make it an 0
    //flip S to .
    //Steps 2-end:
    //go through each(??) or maybe 4 around each potential space?
    //if # then skip
    //if . then check surrounding spaces for 0, if one is found then mark it as a potential space and spaceToFlip
    //if 0 then mark it as spaceToFlip;
    //flip spacesToFlip

    parseFilePtOne("Day21Full.txt");
}

int main()
{
    partOne();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
