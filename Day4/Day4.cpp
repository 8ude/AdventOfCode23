#include <vector>
#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
using namespace std;

vector<int> copiesOfCards;
vector<string> cardLines;

void dayFourPartOne(const string& filename)
{
    ifstream file(filename);
    vector<std::string> lines; //not sure if necessary
    string line;

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    int totalScore = 0;

    while (getline(file, line)) 
    {
        int colonPos = line.find(":");
        int breakPos = line.find("|");
        string cardIndex = line.substr(0, colonPos);
        
        string allNumberString = line.substr(colonPos + 1);
        string winningNumberString = line.substr(colonPos + 1, line.size() - 1 - breakPos - cardIndex.size());

        std::istringstream stream(allNumberString);
        char ch;
        int num;

        bool preBreakCharacter = true;

        vector<int> winningNumbers;
        vector<int> playerNumbers;


        while (stream >> ch)
        {
            if (ch == '|')
            {
                preBreakCharacter = false;
            }
            if (isdigit(ch))
            {
                stream.unget();
                if (stream >> num)
                {
                    preBreakCharacter ? winningNumbers.push_back(num) : playerNumbers.push_back(num);
                }
            }
        }

        int scoreCount = 0;
        
        //cout << "player number count" << playerNumbers.size() << "\n";

        for (int winNum : winningNumbers)
        {
            for (int playerNum : playerNumbers)
            {
                if (winNum == playerNum)
                {
                    //score
                    scoreCount++;
                    //cout << "scored " << "\n";
                }
            }
        }

        int cardScore = 0;

        if (scoreCount > 0)
        {
            cardScore = (int)powf(2.0, scoreCount - 1);
        }

        totalScore += cardScore;

        //cout << "card score: " << cardScore << "\n";

        //cout << cardIndex << "\n";
        //cout << winningNumberString << "\n";
        //cout << playerNumberString << "\n";
        
        lines.push_back(line);
    }

    cout << "Part One total score: " << totalScore << "\n";
        
}

//for part two
void scoreCardLine(string line, int cardCopies, int gameIndex)
{
    int score = 0;

    int colonPos = line.find(":");
    int breakPos = line.find("|");
    string cardIndex = line.substr(0, colonPos);

    string allNumberString = line.substr(colonPos + 1);
    string winningNumberString = line.substr(colonPos + 1, line.size() - 1 - breakPos - cardIndex.size());

    std::istringstream stream(allNumberString);
    char ch;
    int num;

    bool preBreakCharacter = true;

    vector<int> winningNumbers;
    vector<int> playerNumbers;


    while (stream >> ch)
    {
        if (ch == '|')
        {
            preBreakCharacter = false;
        }
        if (isdigit(ch))
        {
            stream.unget();
            if (stream >> num)
            {
                preBreakCharacter ? winningNumbers.push_back(num) : playerNumbers.push_back(num);
            }
        }
    }

    //counting up score
    for (int winNum : winningNumbers)
    {
        for (int playerNum : playerNumbers)
        {
            if (winNum == playerNum)
            {
                //score
                score++;
                //cout << "scored " << "\n";
            }
        }
    }

    //convert the score into copies of subsequent cards
    for (int i = 0; i < cardCopies; i++)
    {
        int tempScore = score;
        while (tempScore > 0)
        {
            if (gameIndex + tempScore < copiesOfCards.size())
            {
                copiesOfCards[gameIndex + tempScore] += 1;
                tempScore--;
            }
        }
    }

}

void dayFourPartTwo(const string& filename)
{
    ifstream file(filename);
    vector<std::string> lines; //not sure if necessary
    string line;

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    int totalScore = 0;

    while (getline(file, line))
    {
        cardLines.push_back(line);
        copiesOfCards.push_back(1);
    }

    for (int i = 0; i < cardLines.size(); i++)
    {
        scoreCardLine(cardLines[i], copiesOfCards[i], i);
    }

    int totalCardCopies = 0;
    for (int copies : copiesOfCards)
    {
        totalCardCopies += copies;
    }

    cout << "Part Two Total cards: " << totalCardCopies << "\n";

}

int main()
{
    //dayFourPartOne("Day4Full.txt");
    dayFourPartTwo("Day4Full.txt");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
