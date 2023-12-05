#include <iostream>
#include <vector>
#include <string.h>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

struct SHandsData {
    int red = 0;
    int blue = 0;
    int green = 0;
};

struct SGameData {
    int id = 0;
    vector<SHandsData> hands;
    int rMax = 0;
    int gMax = 0;
    int bMax = 0;
};

static vector<SGameData> s_Games;

vector<string> readFileIntoVector(const string& filename) {
    ifstream file(filename);
    vector<std::string> lines;
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }
    else {
        // Optional: Handle error here when unable to open the file
        std::cout << "Unable to open file" << "\n";
    }

    return lines;
}

vector<string> parseString(string input, char character)
{

    istringstream iss(input);

    string chunk;
    vector<std::string> results;

    while (getline(iss, chunk, character)) {
        results.push_back(chunk);
    }
    return results;
}

//only works for a string with one number in it
int extractNumber(string input)
{
    int number = 0;

    istringstream iss(input);

    do {
        std::string word;
        iss >> word;


        if (!word.empty()) {
            for (char c : word)
            {
                if (isdigit(c))
                {
                    return stoi(word);
                }       
            }
        }

    } while (iss);

    return number;
}

void parseGames(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    vector<string> parsedData;
    // Read data from the file line by line
    string line;
    while (getline(file, line)) {

        SGameData game;

        parsedData.push_back(line);
        int colonPos = line.find(":");
        string gameIndex = line.substr(0, colonPos);
        string gameData = line.substr(colonPos + 1);

        //game number is always at 6th index. Magic numbers are fine if they work :)
        int gameNumber = stoi(gameIndex.substr(5));

        game.id = gameNumber;

        vector<string> subGames = parseString(gameData, ';');

        for (string subGame : subGames)
        {

            cout << "\n"; //Debug
            vector<string> gameHands = parseString(subGame, ',');
            
            SHandsData handData;

            for (string hand : gameHands)
            {
                
                if (hand.find("red") != string::npos)
                {
                    handData.red = extractNumber(hand);
                    
                }
                if (hand.find("blue") != string::npos)
                {
                    handData.blue = extractNumber(hand);
                }
                if (hand.find("green") != string::npos)
                {
                    handData.green = extractNumber(hand);
                }
            }
            if (handData.red > game.rMax)
            {
                game.rMax = handData.red;
            }
            if (handData.green > game.gMax)
            {
                game.gMax = handData.green;
            }
            if (handData.blue > game.bMax)
            {
                game.bMax = handData.blue;
            }


            game.hands.push_back(handData);
            //cout << "red hand: " << handData.red << "\n"; //Debug
            //cout << "blue hand: " << handData.blue << "\n"; //Debug
            //cout << "green hand: " << handData.green << "\n"; //Debug
        }

        
        //cout << "red max: " << game.rMax << "\n"; //Debug
        //cout << "blue max: " << game.bMax << "\n"; //Debug
        //cout << "green max: " << game.gMax << "\n"; //Debug
        //cout << gameNumber << "\n";

        s_Games.push_back(game);

    }

}

int partOneCompareAndAccumulate(int refR, int refG, int refB)
{
    int accumulation = 0;

    for (SGameData gameData : s_Games)
    {
        if (gameData.rMax <= refR && gameData.gMax <= refG && gameData.bMax <= refB)
        {
            accumulation += gameData.id;
        }
    }

    return accumulation;
}

int partTwoHandPowerAccumulate()
{
    int accumulation = 0;
    for (SGameData gameData : s_Games)
    {
        int handPower = gameData.rMax * gameData.gMax * gameData.bMax;
        accumulation += handPower;
    }
    return accumulation;
}

int main()
{
    try {
        parseGames("Day2Part1Input.txt");
        int partOneTotal = partOneCompareAndAccumulate(12, 13, 14);
        cout << "part one total: " << partOneTotal << "\n";
        int partTwoTotal = partTwoHandPowerAccumulate();
        cout << "part two total: " << partTwoTotal;
    }
    catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
}
