#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <limits>
#include <thread>
#include <mutex>
using namespace std;

static vector<unsigned long long int> seeds;

static unsigned long long int lowestLocNum = ULLONG_MAX;

//for keeping track of what portion we're currently mapping
enum class mapPortion : char {none, seedSoil, soilFert, fertWater, waterLight, lightTemp, tempHumid, humidloc};
static mapPortion currentMap;

//3-int vector for map
struct mappingRange
{
    unsigned long long int m_destRangeStart;
    unsigned long long int m_sourceRangeStart;
    unsigned long long int m_rangeLength;
};

//used for seed ranges in part 2
struct seedRangeData
{
    unsigned long long int m_seedRangeStart;
    unsigned long long int m_seedRangeLength;
};

static vector<seedRangeData> seedRanges;

static vector<mappingRange> seedSoilMap, soilFertMap, fertWaterMap, waterLightMap, lightTempMap, tempHumidMap, humidLocMap;
static mutex s_CoutMutex;


//trying to make partOne more readable
//since we know the order of these, we could skip this step and use an enum to categorize the data sets 
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
    newMap.m_destRangeStart = 0;
    newMap.m_sourceRangeStart = 0;
    newMap.m_rangeLength = 0;

    istringstream intFinder(mappingLine);

    int index = 0;
    unsigned long long int num;
    while (intFinder >> num)
    {

        if (index == 0)
        {
            newMap.m_destRangeStart = num;
            
        }
        else if (index == 1)
        {
            newMap.m_sourceRangeStart = num;
        }
        else if (index == 2)
        {
            newMap.m_rangeLength = num;
        }
        index++;
    }

    cout << "map dest end: " << newMap.m_destRangeStart + newMap.m_rangeLength << "; source end: " << newMap.m_sourceRangeStart + newMap.m_rangeLength << "; range length: " << newMap.m_rangeLength <<"\n";

    return newMap;
}

void parseFilePartOne(const string& filename)
{
    //may not need
    vector<string> seedSoilMapStrings, soilFertMapStrings, fertWaterMapStrings, waterLightMapStrings, lightTempMapStrings, tempHumidMapStrings, humidLocMapStrings;

    ifstream file(filename);
    string tempLine;
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
        for (int i = 0; i < seeds.size(); i+=2)
        {
            seedRanges.push_back({ seeds[i], seeds[i + 1] });
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


const unsigned long long int deMapSeedPath(unsigned long long int inputVal, vector<mappingRange> mappingPortion)
{
    unsigned long long int outputVal = inputVal;
    for(mappingRange rMapRange : mappingPortion)
    {
        if (inputVal >= rMapRange.m_sourceRangeStart && inputVal < rMapRange.m_sourceRangeStart + rMapRange.m_rangeLength)
        {
            outputVal = (inputVal - rMapRange.m_sourceRangeStart) + rMapRange.m_destRangeStart;
        }
    }
    return outputVal;
}

const unsigned long long int traceSeedPathPartOne(unsigned long long int seedNum)
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

//Day Two
void FindLowestLocationForSeedRange(const seedRangeData& seed, unsigned long long& result) {
    unsigned long long  lowest = std::numeric_limits<unsigned long long>::max();

    {
        std::lock_guard<std::mutex> lock(s_CoutMutex);
        std::cout << "Thread started, seed range: " << seed.m_seedRangeStart << " " << seed.m_seedRangeLength << std::endl;
    }

    for (unsigned long long seed_num = seed.m_seedRangeStart; seed_num < seed.m_seedRangeStart + seed.m_seedRangeLength; ++seed_num) {
        
         unsigned long long mLocation = traceSeedPathPartOne(seed_num);

        if (mLocation < lowest) {
            lowest = mLocation;
        }
    }

    {
        std::lock_guard<std::mutex> lock(s_CoutMutex);
        std::cout << "Thread Finished, seed range: " << seed.m_seedRangeStart << " " << seed.m_seedRangeLength<< " Result: " << lowest << std::endl;
    }

    result = lowest;
}

void dayFivePartTwo(const string& filename)
{
    parseFilePartOne(filename);
    unsigned long long int lastSeedNum = 0;
    vector<thread> threads;
    vector<unsigned long long> results;
    results.resize(seedRanges.size());

    for (int i = 0; i < seedRanges.size(); ++i) {
        threads.emplace_back(FindLowestLocationForSeedRange, std::ref(seedRanges[i]), std::ref(results[i]));
    }

    for (std::thread& t : threads) {
        t.join();
    }

    unsigned long long  lowest = std::numeric_limits<unsigned long long>::max();
    for (int i = 0; i < results.size(); i++) {
        if (results[i] < lowest) {
            lowest = results[i];
        }
    }

    cout << "Lowest Destination: " << lowest << std::endl;


}

int main()
{
    dayFivePartTwo("Day5Full.txt");
}
