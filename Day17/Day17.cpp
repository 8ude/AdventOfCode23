// Day17.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
using namespace std;


//naive solution:
//make a zigzag solution (turn along diagonal) as baseline score
//movesSinceTurn counter makes sure we turn (disregards current heading as valid choice)
//evaluate neighboring nodes for least value
//choose that direction
//when solution is greater than least solution, abandon it

vector<vector<int>> map;
enum Direction {north, south, east, west};

struct Point {
    int row;
    int column;

    Point(const int row, const int col) : row(row), column(col) {}

    Point operator + (const Point& p) const {
        return Point(p.row + row, p.column + column);
    }

    bool operator == (const Point& p) const {
        return p.row == row && p.column == column;
    }

};

struct moveStates {
    Direction heading = Direction(north);
    int num_moves_in_direction = 0;
};

void makeMapPt1(string filename)
{

}

int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

