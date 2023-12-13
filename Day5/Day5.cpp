#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <thread>
using namespace std;

vector<unsigned long long int> seeds;

vector<unsigned long long int> locations;
unsigned long long int lowestLocNum = ULLONG_MAX;

//for keeping track of what portion we're currently mapping
enum class mapPortion : char {none, seedSoil, soilFert, fertWater, waterLight, lightTemp, tempHumid, humidloc};
mapPortion currentMap;

//3-int vector for map
struct mappingRange
{
    unsigned long long int destRangeStart;
    unsigned long long int sourceRangeStart;
    unsigned long long int rangeLength;
};

vector<mappingRange> seedSoilMap, soilFertMap, fertWaterMap, waterLightMap, lightTempMap, tempHumidMap, humidLocMap;

//trying to make partOne more readable
mapPortion evalCurrentMapPortion(string lineString)
{
    if (lineString == "seed-to-soil map:")
    {
        return mapPortion::seedSoil;
    }
    else if (lineString == "soil-to-fertilizer map:")
    {
        return mapPortion::soilFert;
    }
    else if (lineString == "fertilizer-to-water map:")
    {
        return mapPortion::fertWater;
    }
    else if (lineString == "water-to-light map:")
    {
        return mapPortion::waterLight;
    }
    else if (lineString == "light-to-temperature map:")
    {
        return mapPortion::lightTemp;
    }
    else if (lineString == "temperature-to-humidity map:")
    {
        return mapPortion::tempHumid;
    }
    else if (lineString == "humidity-to-location map:")
    {
        return mapPortion::humidloc;
    }

    else
    {
        return mapPortion::none;
    }
}

mappingRange getMapRangeFromLine(string mappingLine)
{
    mappingRange newMap;
    newMap.destRangeStart = 0;
    newMap.sourceRangeStart = 0;
    newMap.rangeLength = 0;

    istringstream intFinder(mappingLine);

    int index = 0;
    unsigned long long int num;
    while (intFinder >> num)
    {

        if (index == 0)
        {
            newMap.destRangeStart = num;
            
        }
        else if (index == 1)
        {
            newMap.sourceRangeStart = num;
        }
        else if (index == 2)
        {
            newMap.rangeLength = num;
        }
        index++;
    }

    cout << "map dest end: " << newMap.destRangeStart + newMap.rangeLength << "; source end: " << newMap.sourceRangeStart + newMap.rangeLength << "; range length: " << newMap.rangeLength <<"\n";

    return newMap;
}

void parseFilePartOne(const string& filename)
{
    //may not need
    vector<string> seedSoilMapStrings, soilFertMapStrings, fertWaterMapStrings, waterLightMapStrings, lightTempMapStrings, tempHumidMapStrings, humidLocMapStrings;

    ifstream file(filename);
    std::string tempLine;
    currentMap = mapPortion::none;
    
    int lineIndex = 0; //why do i need so many damn indeces????

    if (!file.is_open()) {
        cout << "Could not open file";
    }

    if (getline(file, tempLine))
    {
        cout << "looking for seeds\n";
        //the seeds part seems to be fucking things up
        tempLine.erase(0, 7);
        istringstream iss(tempLine);

        unsigned long long int num;
        char ch;
        while (iss >> num)
        {

            seeds.push_back(num); //add number to seed strings
            cout << "seeds: " << num << "\n";
            
        }
        

        while (std::getline(file, tempLine))
        {
            //next, check for map delimiter strings (seed to soil, soil to fertilizer, etc)
            if (!isdigit(tempLine[0]) && !tempLine.empty())
            {

                currentMap = evalCurrentMapPortion(tempLine);
                cout << tempLine << "\n";
                continue;

            }
                //go through sequentially each step.set the enum accordingly to keep track of what map is occuring
            if (tempLine.empty()) continue;
            switch (currentMap) {

                case mapPortion::seedSoil:
                {
                    
                    mappingRange seedSoilMapRange = getMapRangeFromLine(tempLine);
                    seedSoilMap.push_back(seedSoilMapRange);
                    break;
                }
                case mapPortion::soilFert:
                {
                    mappingRange soilFertMapRange = getMapRangeFromLine(tempLine);
                    soilFertMap.push_back(soilFertMapRange);
                    break;
                }
                case mapPortion::fertWater:
                {
                    mappingRange fertWaterMapRange = getMapRangeFromLine(tempLine);
                    fertWaterMap.push_back(fertWaterMapRange);
                    break;
                }
                case mapPortion::waterLight:
                {

                    mappingRange waterLightMapRange = getMapRangeFromLine(tempLine);
                    waterLightMap.push_back(waterLightMapRange);
                    break;
                }
                case mapPortion::lightTemp:
                {
                    mappingRange lightTempMapRange = getMapRangeFromLine(tempLine);
                    lightTempMap.push_back(lightTempMapRange);
                    break;
                }
                case mapPortion::tempHumid:
                {
                    mappingRange tempHumidMapRange = getMapRangeFromLine(tempLine);
                    tempHumidMap.push_back(tempHumidMapRange);
                    break;
                case mapPortion::humidloc:
                {
                    mappingRange humidLocMapRange = getMapRangeFromLine(tempLine);
                    humidLocMap.push_back(humidLocMapRange);
                    break;
                }

                default:
                    cout << "no map yet" << "\n";
                    break;
                }
            } 
        }
    }
}

unsigned long long int deMapSeedPath(unsigned long long int inputVal, vector<mappingRange> mappingPortion)
{
    unsigned long long int outputVal = inputVal;
    for(mappingRange rMapRange : mappingPortion)
    {
        if (inputVal >= rMapRange.sourceRangeStart && inputVal < rMapRange.sourceRangeStart + rMapRange.rangeLength)
        {
            outputVal = (inputVal - rMapRange.sourceRangeStart) + rMapRange.destRangeStart;
        }
    }
    return outputVal;
}

unsigned long long int traceSeedPathPartOne(unsigned long long int seedNum)
{
    unsigned long long int locNum = seedNum;
    unsigned long long int soilNum = deMapSeedPath(seedNum, seedSoilMap);
    unsigned long long int fertNum = deMapSeedPath(soilNum, soilFertMap);
    unsigned long long int waterNum = deMapSeedPath(fertNum, fertWaterMap);
    unsigned long long int lightNum = deMapSeedPath(waterNum, waterLightMap);
    unsigned long long int tempNum = deMapSeedPath(lightNum, lightTempMap);
    unsigned long long int humNum = deMapSeedPath(tempNum, tempHumidMap);
    locNum = deMapSeedPath(humNum, humidLocMap);
    return locNum;
}

void dayFivePartOne(const string& filename)
{
    parseFilePartOne(filename);
    unsigned long long int lowestLocNum = ULLONG_MAX;
    for (unsigned long long int seedNumber : seeds)
    {
        unsigned long long int locNumber = traceSeedPathPartOne(seedNumber);
        cout << "seed number: " << seedNumber << "\n";
        cout << "loc number: " << locNumber << "\n";

        if (locNumber < lowestLocNum) lowestLocNum = locNumber;

    }
    cout << "lowest location number: " << lowestLocNum << "\n";
}

void seedThread(int vectorIndex, unsigned long long int lastSeedNum)
{
    unsigned long long int locNumber = ULLONG_MAX;
    //even number index -- seed range
    for (long long unsigned int seed_j = lastSeedNum; seed_j < lastSeedNum + seeds[vectorIndex]; seed_j++)
    {
        locNumber = traceSeedPathPartOne(seed_j);
        if (locNumber < lowestLocNum) lowestLocNum = locNumber;
    }
}

void dayFivePartTwo(const string& filename)
{
    parseFilePartOne(filename);
    unsigned long long int lastSeedNum = 0;
    for (int i = 0; i < seeds.size(); i++)
    {
        unsigned long long int locNumber; 
        if (i % 2 == 0) {
            
            //odd number index -- seed start
            lastSeedNum = seeds[i];
            locNumber = traceSeedPathPartOne(seeds[i]);
            if (locNumber < lowestLocNum) lowestLocNum = locNumber;
        }
        else
        {
            thread t(seedThread, i, lastSeedNum);
            //even number index -- seed range
            t.join();
        }

        cout << "last seed number: " << lastSeedNum << "\n";
        cout << "lowest loc number: " << lowestLocNum << "\n";


    }
    cout << "lowest location number: " << lowestLocNum << "\n";

}

int main()
{
    dayFivePartTwo("Day5Full.txt");
}
