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
    line5 >> E;

    if(E > 99) E = 99;
    if(E < 0) E = 0;

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
const string TARGET[8] = {"", "", "", "Buon Ma Thuot", "Duc Lap", "Dak Lak", "National Route 21", "National Route 14"};

string determineRightTarget(const string &target)
{
    // TODO: Implement this function
    int savedNum[3] = {}; // save maximum of 3 integers
    int countNum = -1; // quantity of integers found

    for(int i = 0; i < target.length(); i++)
    {
        if(target[i] >= '0' && target[i] <= '9') // check if the character is the digit
        {
            int num = target[i] - '0'; // convert digit to number

            // if has more digit, continue reading it
            while(i + 1 < target.length() && target[i + 1] >= '0' && target[i + 1] <= '9')
            {
                num = num * 10 + (target[++i] - '0');
            }

            if(num >= 0 && num <= 100)
            {
                countNum++;

                if(countNum < 3) savedNum[countNum] = num;
                // cout << "savedNum[0] :" << savedNum[0] << endl;
            }
            // else return "INVALID"; // if has more than 3 integers found
        }
    }

    // no integer found
    if(countNum == -1) return "INVALID";

    int ID; // ID of actual target
    
    // one integer found
    if(countNum == 0)
    {
        ID = savedNum[0];
        if(ID >= 3 && ID <= 7) return TARGET[ID];
        else if(ID >= 0 && ID <=2) return "DECOY";
        else return "INVALID";
    }
    else if(countNum == 1)
    {
        ID = ((savedNum[0] + savedNum[1]) % 5) + 3;
        return TARGET[ID];
    }
    else if(countNum == 2)
    {
        int maxNum = savedNum[0];

        if(savedNum[1] > maxNum) maxNum = savedNum[1];
        if(savedNum[2] > maxNum) maxNum = savedNum[2];

        ID = (maxNum % 5) + 3;
        return TARGET[ID];
    }

    return "INVALID"; // if has more than 3 integers found
}

const string ACTUAL_TARGET[5] = {"Buon Ma Thuot", "Duc Lap", "Dak Lak", "National Route 21", "National Route 14"};

bool isMatchedTarget(const string &decodedMessage)
{
    for(int i = 0; i < 5; i++)
    {
        if(decodedMessage == ACTUAL_TARGET[i]) return true;
    }

    return false;
}

string toLowerCase(const string &s)
{
    string lowerCaseString = s;

    for(int i = 0; i < lowerCaseString.length(); i++)
    {
        if(lowerCaseString[i] >= 'A' && lowerCaseString[i] <= 'Z')
        {
            lowerCaseString[i] = lowerCaseString[i] + 32;
        }
    }

    return lowerCaseString;
}

string CaesarCipherMethod(const string &message, int shift)
{
    string decodedMessage = "";

    for(int i = 0; i < message.length(); i++)
    {
        char ch = message[i];

        if(ch >= 'A' && ch <= 'Z')
        {
            decodedMessage += char(((ch - 'A' - shift + 26) % 26) + 'A');
        }
        else if(ch >= 'a' && ch <= 'z')
        {
            decodedMessage += char(((ch - 'a' - shift + 26) % 26) + 'a');
        }
        else if(ch == ' ')
        {
            decodedMessage += ch;
        }
        else
        {
            return "INVALID"; // if character is not A-Z, a-z, ' '
        }
    }

    return decodedMessage;
}

string reversedStringMethod(const string &message)
{
    string reversed = message;
    int len = reversed.length();

    for(int i = 0; i < len/2; i++)
    {
        char temp = reversed[i];
        reversed[i] = reversed[len - i - 1];
        reversed[len - i - 1] = temp;
    }

    return reversed;
}

string decodeTarget(const string &message, int EXP1, int EXP2)
{
    // TODO: Implement this function
    string decodedMessage;

    if(EXP1 >= 300 && EXP2 >= 300)
    {
        int shift = (EXP1 + EXP2) % 26;
        decodedMessage = CaesarCipherMethod(message, shift);
        
        if(isMatchedTarget(decodedMessage) == true) return decodedMessage;
    }
    if(EXP1 < 300 || EXP2 < 300)
    {
        decodedMessage = reversedStringMethod(message);

        for(int i = 0; i < 5; i++)
        {
            if(toLowerCase(decodedMessage) == toLowerCase(ACTUAL_TARGET[i]))
            {
                return ACTUAL_TARGET[i];
            }
        }
    }

    return "INVALID";
}

// Task 3
void manageLogistics(int LF1, int LF2, int EXP1, int EXP2, int &T1, int &T2, int E)
{
    // TODO: Implement this function
    if(LF1 > 1000) LF1 = 1000;
    if(LF1 < 0) LF1 = 0;

    if(LF2 > 1000) LF2 = 1000;
    if(LF2 < 0) LF2 = 0;

    if(E == 0)
    {
        double deltaT1, deltaT2;

        deltaT1 = ((double)(LF1/(LF1 + LF2)) * (T1 + T2)) * (1 + (double)(EXP1 - EXP2)/100);
        deltaT2 = (double)(T1 + T2) - deltaT1;

        T1 = ceil(T1 + deltaT1);
        T2 = ceil(T2 + deltaT2);

        if(T1 > 3000) T1 = 3000;
        if(T2 > 3000) T2 = 3000;
    }
    else if(E >= 1 && E <= 9)
    {
        T1 = ceil(T1 - ((double)E*1/100)*T1);
        T2 = ceil(T2 - ((double)E*1/200)*T2);
    }
    else if(E >= 10 && E <= 29)
    {
        T1 = T1 + E*50;
        T2 = T2 + E*50;
    }
    else if(E >= 30 && E <= 59)
    {
        T1 = ceil(T1 + ((double)E*1/200)*T1);
        T2 = ceil(T2 + ((double)E*1/500)*T2);
    }

    if(T1 > 3000) T1 = 3000;
    if(T1 < 0) T1 = 0;

    if(T2 > 3000) T2 = 3000;
    if(T2 < 0) T2 = 0;
}

// Task 4
int planAttack(int LF1, int LF2, int EXP1, int EXP2, int T1, int T2, int battleField[10][10])
{
    // TODO: Implement this function
    // initial total strength of 2 corps
    double S = (LF1 + LF2) + (EXP1 + EXP2)*5 + (T1 + T2)*2;
    int finalStrength;

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            // odd rows
            if(i % 2 == 0)
            {
                S -= (double)battleField[i][j]*3/2;
            }
            // even rows
            else
            {
                S -= (double)battleField[i][j]*2/3;
            }
        }
    }

    finalStrength = ceil(S);

    return finalStrength;
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
