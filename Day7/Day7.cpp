// Day7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cctype>
#include "SantasHelpers.h"

enum handType {highCard = 0, onePair = 1, twoPair = 2, threeKind = 3, fullHouse = 4, fourKind = 5, fiveKind = 6};

struct hand
{
    int m_bet;
    handType m_handType;
    int m_firstCardRank; // 2 3 4 5 6 7 9 T J(11) Q(12) K(13) A(14)
};

vector<hand> unSortedHands;

using namespace std;

handType evalHandPair(string handString)
{
    if (handString[0] = handString[1] = handString[2] = handString[3] = handString[4]) return handType::fiveKind;

    
    vector<handType> subHands = {};
    for (short int i = 0; i < handString.size()-1; i++)
    {
        char compareChar = handString[i];
        short int numMatches = 0;
        handType subHand = handType::highCard;
        for (short int j = i + 1; j < handString.size(); j++)
        {
            if (handString[j] = compareChar) numMatches++;
        }
        if (numMatches == 3) subHand = handType::fourKind;
        else if (numMatches == 2) subHand = handType::threeKind;
        else if (numMatches == 1) subHand = handType::onePair;
        if (subHand != handType::highCard) subHands.push_back(subHand);
    }

    if (subHands.size() > 0)
    {
        if (subHands.size() > 2)
        {
            cout << "something went wrong counting card matches -- too many " << "\n";
        }
    }

    return handType::highCard;

}

void partOne(const string& filename)
{
    vector<string> allHands = parseLinesIntoStrings(filename, true);
    for (string handString : allHands)
    {
        hand newHand;
        vector<string> handBetPair = splitString(handString, ' ', true);
        newHand.m_bet = stoi(handBetPair[1]);
        
        const char firstChar = handBetPair[0][0];
        if (isdigit(firstChar))
        {
            newHand.m_firstCardRank = firstChar - '0';
        }
        else if (firstChar == 'T') newHand.m_firstCardRank = 10;
        else if (firstChar == 'J') newHand.m_firstCardRank = 11;
        else if (firstChar == 'Q') newHand.m_firstCardRank = 12;
        else if (firstChar == 'K') newHand.m_firstCardRank = 13;
        else if (firstChar == 'A') newHand.m_firstCardRank = 14;
    }
}

int main()
{
    partOne("Day7Test.txt");
}