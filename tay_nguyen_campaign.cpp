#include "tay_nguyen_campaign.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

const int MAX_LINES = 5;         
const int MAX_LINE_LENGTH = 100;

// Task 0: Read input file
bool readFile(const string &filename, int LF1[], int LF2[], int &EXP1, int &EXP2, int &T1, int &T2, int &E)
{
    char data[MAX_LINES][MAX_LINE_LENGTH];
    int numLines = 0;

    ifstream ifs(filename);
    if(!ifs.is_open())
    {
        return false;
    }

    while(numLines < MAX_LINES && ifs.getline(data[numLines], MAX_LINE_LENGTH))
    {
        numLines++;
    }
    ifs.close();

    if(numLines < MAX_LINES)
    {
        return false;
    }

    // TODO: Extract values from the data array and store them in respective variables

    // handle first line from input file
    stringstream line1(data[0]);
    char ch;
    line1 >> ch; // remove the character '['

    for(int i = 0; i < 17; i++)
    {
        line1 >> LF1[i];
        if(i < 16) line1 >> ch; // remove the character ','
        
        if(LF1[i] > 1000) LF1[i] = 1000;
        if(LF1[i] < 0) LF1[i] = 0;
    }

    // handle second line from input file
    stringstream line2(data[1]);
    line2 >> ch; // remove the character '['

    for(int i = 0; i < 17; i++)
    {
        line2 >> LF2[i];
        if(i < 16) line2 >> ch; // remove the character ','

        if(LF2[i] > 1000) LF2[i] = 1000;
        if(LF2[i] < 0) LF2[i] = 0;
    }

    // handle third line from input file
    stringstream line3(data[2]);
    line3 >> EXP1 >> EXP2;

    if(EXP1 > 600) EXP1 = 600;
    if(EXP1 < 0) EXP1 = 0;

    if(EXP2 > 600) EXP2 = 600;
    if(EXP2 < 0) EXP2 = 0;

    // handle fourth line from input file
    stringstream line4(data[3]);
    line4 >> T1 >> T2;

    if(T1 > 3000) T1 = 3000;
    if(T1 < 0) T1 = 0;

    if(T2 > 3000) T2 = 3000;
    if(T2 < 0) T2 = 0;

    // handle fifth line from input file
    stringstream line5(data[4]);
    line5 >> E; // how about the condition for E

    return true;
}

// Task 1
const int NUM_RANK = 17;
const int RANK_WEIGHT[NUM_RANK] = {1, 2, 3, 4, 5, 7, 8, 9, 10, 12, 15, 18, 20, 30, 40, 50, 70};

int gatherForces(int LF1[], int LF2[])
{
    // TODO: Implement this function
    int LF1Strength = 0, LF2Strength = 0;

    for(int i = 0; i < NUM_RANK; i++)
    {
        LF1Strength += LF1[i]*RANK_WEIGHT[i];
    }
    for(int i = 0; i < NUM_RANK; i++)
    {
        LF2Strength += LF2[i]*RANK_WEIGHT[i];
    }

    return LF1Strength + LF2Strength;
}

// Task 2
string determineRightTarget(const string &target)
{
    // TODO: Implement this function
    return "INVALID";
}

string decodeTarget(const string &message, int EXP1, int EXP2)
{
    // TODO: Implement this function
    return "INVALID";
}

// Task 3
void manageLogistics(int LF1, int LF2, int EXP1, int EXP2, int &T1, int &T2, int E)
{
    // TODO: Implement this function
}

// Task 4
int planAttack(int LF1, int LF2, int EXP1, int EXP2, int T1, int T2, int battleField[10][10])
{
    // TODO: Implement this function
    return 0;
}

// Task 5
int resupply(int shortfall, int supply[5][5])
{
    // TODO: Implement this function
    return 0;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
