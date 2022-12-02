#include <string>
#include <vector>
#include <map>
#include <unordered_set>
using namespace std;

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
    multimap<string, vector<string>> deltafunc; // transition Func
    int steps;                                  // steps
    string currentState;                        // current State
    bool verbose;                               // verbose mode
public:
    TM(const string &filename, bool v);
    void run(const string &input);
    void setValue(string &line); // q0 B N
    void addValue(string &line); // Q S G F
    void printSelf();
    void addDelta(string &line);
    void addState(string &line, unordered_set<string> &receiver); // case 1 & case 3
    void addSymbol(string &line, unordered_set<char> &receiver);  // case 1 & case 3
    void reportDeltaError(const string &error, const string &type);
    void checkInput(const string &input);
};
