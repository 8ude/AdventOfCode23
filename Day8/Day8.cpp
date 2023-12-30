

#include <iostream>
#include <vector>
#include "SantasHelpers.h"
#include <map>
#include <utility>

using namespace std;
vector<string> fileStrings;

string steps;
map<string, pair<string, string>> nodes;


void partOne(bool debug = false)
{
    //parse lines -- origin; dest_R; dest_L
    //go through steps - if L is found, then next step is nodes.find(result->second->first) else if R is found then next step is nodes.find(result->second->second)
    //update step counter
    //update current step

    steps = fileStrings[0];
    for (int i = 1; i < fileStrings.size(); i++)
    {
        cout << "writing node: " << "\n";
        string nodeOrigin = fileStrings[i].substr(0, 3);
        cout << nodeOrigin << "\n";
        string nodeDestL = fileStrings[i].substr(7, 3);
        
        string nodeDestR = fileStrings[i].substr(12, 3);
        pair<string, string> nodeDestPair = make_pair(nodeDestL, nodeDestR);
        cout << "node left: " << nodeDestPair.first << " node right: " << nodeDestPair.second << "\n";
        nodes[nodeOrigin] = nodeDestPair;
    }
        



    string currentNode = "AAA";
    int stepCounter = 0;
    while (currentNode != "ZZZ")
    {
        char dir = steps[stepCounter % steps.size()];
        string nextNode;
        if (nodes.find(currentNode) == nodes.end())
        {
            cout << "key isn't in the nodes map, something went wrong ";
            return;
        }
        if (dir == 'L')
        {
            nextNode = nodes.at(currentNode).first; //the second value of the find function is the left/right map. of these, the first value corresponds to the Left... 
            if (debug) cout << "at " << currentNode << " going L to " << nextNode << "\n";
        }
        else if (dir == 'R')
        {
            nextNode = nodes.at(currentNode).second;//.. and the second value corresponds to the right
            if (debug) cout << "at " << currentNode << " going R to " << nextNode << "\n";
        }
        else
        {
            cout << "something went wrong in traversing the map" << "\n";
        }
        stepCounter++;
        cout << "steps: " << stepCounter << "\n";
        currentNode = nextNode;
    }
    
}

int main()
{
    fileStrings = parseLinesIntoStrings("Day8Full.txt");
    partOne();
    
}

