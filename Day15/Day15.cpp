#include <iostream>
#include <vector>
#include <fstream>
#include "SantasHelpers.h"

static vector<string> hashSteps;

void parseLinePartOne()
{
    int runningTotal = 0;
    for (string& step : hashSteps)
    {
        int stepValue = 0;
        for (char& c : step)
        {
            stepValue += (int)c;
            stepValue *= 17;
            stepValue %= 256;
        }
        runningTotal += stepValue;
    }
    cout << "total hash: " << runningTotal;
}

void DayFifteenPartOne()
{
    //parse input
    ifstream file("Day15Full.txt");
    string templine;
    if (!file.is_open())
    {
        cout << "could not open file";
    }
    else
    {
        while (std::getline(file, templine))
        {
            hashSteps = splitString(templine, ',');
        }
        parseLinePartOne();
        file.close();
    }

    //char to ascii value
    //that *17 
    //that % 256
    //add next char to ascii value
}

void DayFifteenPartTwo()
{

}

int main()
{
    int part;
    std::cout << "Which Part?\n";
    std::cin >> part;
    if (part == 1)
    {
        DayFifteenPartOne();
    }
    else if (part == 2)
    {
        DayFifteenPartTwo();
    }
    else
    {
        std::cout << "invalid input";
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

