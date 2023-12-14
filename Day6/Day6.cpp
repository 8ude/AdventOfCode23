#include <iostream>
#include <vector>
using namespace std;

//steps:

//set up the quadratic formula for the race. 
//general distance formula is D = (0.5*a*t^2) + (v*t) where a = accel, v = velocity, t = time
//a in this case is 0
//v in this case is TimeHeld (Th)
//since distance traveled is 0 until Th, we can simplify t as Total Race time (Tt) - Th
//therefore our equation becomes D = Th * (Tt - Th) expanding out to 0 = -Th^2 + Tt*Th - D
//the roots of that equation will be (-Tt + sqrt((Tt*Th)^2 - 4*(-Th * -D))/(2*-Th) and (- Tt - sqrt((Tt*Th)^2 - 4*(-Th * -D))/(2*-Th)
//integers between that range will be acceptable - the integer range equals the number of ways to win


vector<float> times = { 57, 72, 69, 92 };
vector<float> distances = { 291, 1172, 1176, 2026 };

//part two
long long timePartTwo = 71530;
long long distancePartTwo = 940200;

vector<long long int> numWinningTimes;

static int runningTotal;

int quadFormulaLow(float a, float b, float c)
{
    float quadLow = (-b + sqrt(pow(b, 2) - (4 * a * c))) / (2 * a);
    if (ceil(quadLow) == quadLow) return quadLow + 1;
    
    return ceil(quadLow);
}
int quadFormulaHigh(float a, float b, float c)
{

    float quadHigh = (-b - sqrt(pow(b, 2.0) - (4.0 * a * c))) / (2.0 * a);
    if (floor(quadHigh) == quadHigh) return quadHigh - 1;

    return floor(quadHigh);
}

long long unsigned int quadFormulaLowPtTwo(long long a, long long b, long long c)
{
    long long quadLow = (-b + sqrt(pow(b, 2) - (4 * a * c))) / (2 * a);
    cout << "quad low: " << quadLow << "\n";
    cout << "quad low ceil: " << ceill(quadLow) << "\n";
    if (ceill(quadLow) == quadLow) return quadLow + 1;

    return ceill(quadLow);
}
long long unsigned int quadFormulaHighPtTwo(float a, float b, float c)
{

    long long quadHigh = (-b - sqrt(pow(b, 2.0) - (4.0 * a * c))) / (2.0 * a);
    cout << "quad heigh: " << quadHigh << "\n";
    cout << "quad heigh ceil: " << floorl(quadHigh) << "\n";
    if (floorl(quadHigh) == quadHigh) return quadHigh - 1;

    return floorl(quadHigh);
}

int numWaysToWin(float totalTime, float winDistance)
{
    int lowBound = quadFormulaLow(-1.0, totalTime, -1.0 * winDistance);
    int highBound = quadFormulaHigh(-1.0, totalTime, -1.0 * winDistance);
    int numWinners = highBound - lowBound + 1;
    std::cout << "num winners: " << numWinners << "\n";
    return numWinners;
}

long long unsigned int numWaysToWinPtTwo(long long totalTime, long long winDistance)
{
    long long unsigned int lowBound = quadFormulaLowPtTwo(-1.0, totalTime, -1.0 * winDistance);
    long long unsigned int highBound = quadFormulaHighPtTwo(-1.0, totalTime, -1.0 * winDistance);
    long long unsigned int numWinners = highBound - lowBound + 1;
    std::cout << "num winners: " << numWinners << "\n";
    return numWinners;
}

void partOne()
{
    for (int i = 0; i < times.size(); i++)
    {
        numWinningTimes.push_back(numWaysToWin(times[i], distances[i]));
    }
    int runningTotal = 1;
    for (int times : numWinningTimes)
    {
        runningTotal *= times;
    }

    cout << "puzzle solution part 1: " << runningTotal <<"\n";

}

void partTwo()
{
    cout << "puzzle solution part 2: " << numWaysToWinPtTwo(timePartTwo, distancePartTwo);
    //^^ I had to inexplicably add one to get the correct answer here, and it doesn't make any sense to me
}

int main()
{
    partTwo();

}