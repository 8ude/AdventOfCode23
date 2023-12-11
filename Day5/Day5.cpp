#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

vector<int> seeds;

//for keeping track of what portion we're currently mapping
enum mapPortion {none, seedSoil, soilFert, fertWater, waterLight, lightTemp, tempHumid, humidloc};
mapPortion currentMap;

//3-int vector for map
struct mappingRange
{
    int destRangeStart;
    int sourceRangeStart;
    int rangeLength;
};

vector<mappingRange> seedSoilMap, soilFertMap, fertWaterMap, waterLightMap, lightTempMap, tempHumidMap, humidLocMap;



vector<int> parseMaps(vector<string> mapLines)
{
    return { 0, 0, 0 };
}

void parseFilePartOne(const string& filename)
{
    //may not need
    vector<string> seedSoilMapStrings, soilFertMapStrings, fertWaterMapStrings, waterLightMapStrings, lightTempMapStrings, tempHumidMapStrings, humidLocMapStrings;

    ifstream file(filename);
    std::string tempLine;
    currentMap = none;
    
    int lineIndex = 0;

    try
    {
        if (!file.is_open()) {
            throw ("Could not open file");
        }
        while (std::getline(file, tempLine))
        {
            //line 0 are the seed numbers
            if (lineIndex == 0)
            {
                istringstream iss(tempLine);

                string chunk;
                vector<std::string> results;

                while (getline(iss, chunk)) {
                    results.push_back(chunk);
                }
            }
            if (tempLine == "seed-to-soil map :")
            {

            }
        }
    }
    catch (string errorString)
    {
        std::cout << errorString;
    }
}

void dayFivePartOne(const string& filename)
{
    parseFilePartOne(filename);
}

int main()
{
    std::cout << "Hello World!\n";
}
