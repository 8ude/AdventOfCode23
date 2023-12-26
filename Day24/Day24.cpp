
// Day24.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "SantasHelpers.h"
using namespace std;

struct hailstone
{
    vector<long long> pos;
    vector<long long> velocity;
};

vector<hailstone> viableHailstones;

bool checkHSInTestArea(const hailstone& hs, vector<long long>  bbUL, vector<long long>  bbLR)
{
    if (hs.pos[0] < bbUL[0] && hs.velocity[0] < 0) return false;
    if (hs.pos[0] > bbLR[0] && hs.velocity[0] > 0) return false;
    if (hs.pos[1] < bbLR[1] && hs.velocity[1] < 0) return false;
    if (hs.pos[1] > bbUL[1] && hs.velocity[1] > 0) return false;
    return true;
}

bool checkCollideInSquareTestArea(const hailstone& hsA, const hailstone& hsB, vector<long long> bbUL, vector <long long> bbLR)
{
    //formula for checking collision of two vectors
    //check inside bounding box
    return false;
}

void partOne()
{
    //create vector of viable Hailstones
    //early out every hailstone that doesn't go into the test area at all

}

int main()
{
    std::cout << "Hello World!\n";
}