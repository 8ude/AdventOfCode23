// Day7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>
#include "SantasHelpers.h"

enum handType : int {highCard = 0, onePair = 1, twoPair = 2, threeKind = 3, fullHouse = 4, fourKind = 5, fiveKind = 6};

struct hand
{
    int m_bet;
    handType m_handType;
    int m_firstCardRank; // 2 3 4 5 6 7 9 T J(11) Q(12) K(13) A(14)
    string m_handstring; //sanity check and debug
};

vector<hand> unSortedHands;

using namespace std;

handType evalHandPair(string handString)
{
    cout << "for hand: " << handString << "\n";
    if (handString[0] == handString[1] == handString[2] == handString[3] == handString[4])
    {
        cout << "five of a kind \n";
        return handType::fiveKind;
    }

    
    vector<handType> subHands = {};
    vector<char> handVector = {handString[0], handString[1], handString[2], handString[3], handString[4], handString[5]};
    for (short int i = 0; i < handString.size()-1; i++)
    {
        char compareChar = handString[i];
        short int numMatches = 0;
        handType subHand = handType::highCard;
        for (short int j = i + 1; j < handString.size(); j++)
        {
            if (handString[j] == compareChar) numMatches++;
        }
        cout << "num matches for " << handString << " " << numMatches << "\n";


        if (numMatches == 3)
        {
            cout << "four of a kind \n";
            return handType::fourKind; //no reason to go through subhands
        }
        else if (numMatches == 2) subHand = handType::threeKind;
        else if (numMatches == 1) subHand = handType::onePair;

        if (subHand != handType::highCard) subHands.push_back(subHand);
    }

    if (subHands.size() == 0)
    {
        cout << "no matches for " << handString << " returning high card \n";
    }
    //count up sub-hands
    int countPairs = count_if(subHands.begin(), subHands.end(), [](handType h) {return h == handType::onePair; });
    if (countPairs == 2)
    {
        cout << "two pair \n";
        return handType::twoPair;
    }

    int countThreeKind = count_if(subHands.begin(), subHands.end(), [](handType h) {return h == handType::threeKind; });
    
    if (countThreeKind > 0)
    {
        if (countPairs > 0)
        {
            cout << "full house /n";
            return handType::fullHouse;
        }
        cout << "three kind /n";
        return handType::threeKind;
    }
    else if (countPairs == 1)
    {
        cout << "one pair /n";
        return handType::onePair;
    }
    

    cout << "something went wrong parsing hand: " << handString << "\n";

    return handType::highCard;

}

int findCardRank(const char& c)
{
    if (isdigit(c))
    {
        return c - '0';
    }
    else if (c == 'T') return 10;
    else if (c == 'J') return 11;
    else if (c == 'Q') return 12;
    else if (c == 'K') return 13;
    else if (c == 'A') return 14;

    cout << "something went wrong in finding card rank \n";
    return 0;
}

bool isFirstHandLowerThanSecond(const hand& h1, const hand& h2)
{
    if (h1.m_handType < h2.m_handType) return true;
    for (int i = 0; i < 5; i++)
    {
        if (h1.m_handstring[i] != h2.m_handstring[i])
        {
            int h1cardint = findCardRank(h1.m_handstring[i]);
            int h2cardint = findCardRank(h1.m_handstring[i]);
            return h1cardint < h2cardint;
        }
    }
    cout << "something went wrong comparing hands \n";
    return false;
}

void partOne(const string& filename)
{
    vector<string> allHands = parseLinesIntoStrings(filename, true);
    for (string handString : allHands)
    {
        hand newHand;
        newHand.m_handstring = handString;
        vector<string> handBetPair = splitString(handString, ' ', true);
        newHand.m_bet = stoi(handBetPair[1]);

        newHand.m_handType = evalHandPair(handString);
        unSortedHands.push_back(newHand);
    }

    std::sort(unSortedHands.begin(), unSortedHands.end(), isFirstHandLowerThanSecond);

    int totalWinnings = 0;
    for (short i = 0; i < unSortedHands.size(); i++)
    {
        cout << "next hand: " << unSortedHands[i].m_handstring << " hand type int: " << static_cast<int>(unSortedHands[i].m_handType) << " ranking: " << i + 1 << "\n";
        totalWinnings += (unSortedHands[i].m_bet * (i + 1));
        cout << "total winnings: " << totalWinnings << "\n";
    }
}

int main()
{
    partOne("Day7Test.txt");
}