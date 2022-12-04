#ifndef __TM__
#define __TM__

#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <deque>
using namespace std;

class Tape
{
private:
    string rightHalf; //右半部分
    string leftHalf;  //左半部分
    int head;         //当前指向
public:
    Tape() : head(0), rightHalf(1, '_') {}
    Tape(const string &input) : head(0), rightHalf(input)
    {
        if (rightHalf.size() == 0)
            rightHalf = string(1, '_');
    }
    void getBorder(int &leftbeg, int &leftend, int &rightbeg, int &rightend) const;
    void printTapeContent(const int &leftbeg, const int &leftend, const int &rightbeg, const int &rightend, string &ans, bool printBlank = true) const;
    void printResult();
    void move(char dir)
    {
        if (dir == 'l')
        {
            --head;
            if (-head > leftHalf.size())
                leftHalf.push_back('_');
        }
        else if (dir == 'r')
        {
            ++head;
            if (head == rightHalf.size()) //右侧添加
            {
                rightHalf.push_back('_');
            }
        }
    }
    char getCurrVal() const
    {
        if (head >= 0)
            return rightHalf[head];
        else
            return leftHalf[-head - 1];
    }
    void printSelf(int idx) const;
    void setNewSym(char wirteCurrPos)
    {
        if (wirteCurrPos != '*') // new symbol is *,keep it
        {
            if (head >= 0)
                rightHalf[head] = wirteCurrPos;
            else
                leftHalf[-head - 1] = wirteCurrPos;
        }
    }
};

class TM
{
private:
    unordered_set<string> states;               // Q
    unordered_set<char> inputSymbols;           // S
    unordered_set<char> tapeSymbols;            // G
    unordered_set<string> finalStates;          // F
    string startState;                          // q0
    char BLANK;                                 // B
    int tapeNumber;                             // N
    vector<Tape *> tapes;                       // tapes
    multimap<string, vector<string>> deltafunc; // transition Func
    int steps;                                  // steps
    string currentState;                        // current State
    bool verbose;                               // verbose mode
public:
    TM(const string &filename, bool v);
    void run(const string &input);
    void setValue(string &line); // q0 B N
    void addValue(string &line); // Q S G F
    void printSelf() const;
    void addDelta(string &line);
    void addState(string &line, unordered_set<string> &receiver); // case 1 & case 3
    void addSymbol(string &line, unordered_set<char> &receiver);  // case 1 & case 3
    void reportDeltaError(const string &error, const string &type);
    void checkInput(const string &input) const;
    void setTapes(const string &input);
    void printId() const;
    void findFunc(multimap<string, vector<string>>::iterator &it);
    void Move(const string &newSym, const string &dir);
    void printResult();
};

#endif