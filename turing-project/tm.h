#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

class transitionFunc
{
    string oldState;

    string newState;
};

class TM
{
private:
    unordered_set<string> states;      // Q
    unordered_set<char> inputSymbols;  // S
    unordered_set<char> tapeSymbols;   // G
    unordered_set<string> finalStates; // F
    string startState;                 // q0
    char BLANK;                        // B
    int tapeNumber;                    // N
    vector<transitionFunc *> func;     // transition Func
    int steps;                         // steps
    string currentState;               // current State
    bool verbose;                      // verbose mode
public:
    TM(const string &filename, bool v);
    void parseFile(const string &filename);
    void run(const string &input);
    void setValue(string &line);            // q0 B N
    void addValue(string &line, char type); // Q S G F
    void printSelf();
    void parseDelta(string &line);
};
