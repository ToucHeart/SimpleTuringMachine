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
    deque<char> tape; //支持左右添加
    int head;         //当前指向

public:
    Tape() : head(0), tape({'_'}) {}
    Tape(const string &input) : head(0), tape(input.begin(), input.end()) {}
    void moveLeft(char wirteCurrPos)
    {
        if (wirteCurrPos != '*') // new symbol is *,keep it
            tape[head] = wirteCurrPos;
        if (head == 0) // 左侧添加,head不变
        {
            tape.push_front('_');
            return;
        }
        --head;
    }
    void moveRight(char wirteCurrPos)
    {
        if (wirteCurrPos != '*')
            tape[head] = wirteCurrPos;
        if (head == tape.size() - 1) //右侧添加
        {
            tape.push_back('_');
        }
        ++head;
    }
    char getCurrVal() const { return tape[head]; }
    void printSelf(int idx) const;
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
    void printStepResult() const;
};

#endif