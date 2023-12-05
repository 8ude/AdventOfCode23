#include <iostream>
#include <vector>
using namespace std;

void dayTwoPartOne()
{
	std::cout << "day 2! ";
	//goal: finding "possible" games means finding the max number of each color, compare that against the reference requirement for each color
	//steps:
	//parsing each game for the subGameVectors via colon and semicolon 
	// game vector is {{gameID} {game 1} {game 2} {game 3}} etc
	// for simplicity, games go red-green-blue - if no red, then it's zero
	// make a "max value" vector for the game, append to game vector
	// foreach value in maxvalue, check against reference. if all are less than or equal, add game ID to running total
	// if not, go to the next one

}

