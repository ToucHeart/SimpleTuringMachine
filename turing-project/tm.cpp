#include <fstream>
#include "message.h"
#include <iostream>
#include <cstring>
#include <sstream>
#include "tm.h"
using namespace std;

// #Q = {0,cp,cmp,mh,accept,accept2,accept3,accept4,halt_accept,reject,reject2,reject3,reject4,reject5,halt_reject}

// 1.Q S G F 有{} 以,分隔
// 2.q0 B N 无{}和,
// 3.delta function是5个字符串,之间以空格分隔,没有{} ,
#define DEBUG

static int lineCount = 0; //记录读取文件的行数

void removeBrackets(string &line) //得到{}中的部分 Q S G F
{
    int left = line.find('{');
    int right = line.find('}');
    line = line.substr(left + 1, right - left - 1);
}

void removeComment(string &line) // q0 N delta function   去掉行尾注释和行尾多余空格
{
    int idx = line.find(';');
    if (idx != string::npos)
        line = line.substr(0, idx);
    int len = line.size() - 1;
    while (line[len] == ' ')
        len--;
    line.resize(len + 1);
}

void getLineElement(string &line, char split, vector<string> *strs = nullptr, vector<char> *chars = nullptr) // 0 char ,1 str
{
    stringstream ss(line);
    string token;
    if (strs)
    {
        while (getline(ss, token, split))
        {
            strs->push_back(token);
        }
    }
    else if (chars)
    {
        while (getline(ss, token, split))
        {
            chars->push_back(token[0]);
        }
    }
#if 0
    for (auto &i : receiver)
        cout << i << ' ';
    cout << endl;
#endif
}

void TM::addState(string &line, unordered_set<string> &states) // case 1 & case 3
{
    vector<string> tmp;
    getLineElement(line, ',', &tmp);
    for (const auto &s : tmp)
    {
        states.insert(s);
    }
}

void TM::addSymbol(string &line, unordered_set<char> &symbols) // case 1 & case 3
{
    vector<char> tmp;
    getLineElement(line, ',', nullptr, &tmp);
    for (const auto &c : tmp)
    {
        symbols.insert(c);
    }
}

void TM::addValue(string &line)
{
    char type = line[1];
    removeBrackets(line);
    switch (type)
    {
    case 'Q':
        addState(line, this->states);
        break;
    case 'F':
        addState(line, this->finalStates);
        break;
    case 'S':
        addSymbol(line, this->inputSymbols);
        break;
    case 'G':
        addSymbol(line, this->tapeSymbols);
        break;
    }
}

void TM::setValue(string &line) // q0 N
{
    removeComment(line);
    int left = line.find('=');
    left++;
    while (left < line.size() && line[left] == ' ')
        left++;
    if (line[1] == 'q')
        startState = line.substr(left, line.size() - left);
    else if (line[1] == 'N')
    {
        int num = 0;
        while (left < line.size())
        {
            num = num * 10 + line[left] - '0';
            left++;
        }
        tapeNumber = num;
    }
}

void TM::reportDeltaError(const string &error, const string &type)
{
    printMessage(SYNTAX_ERROR, HELP_MESSAGE, false);
    if (verbose)
    {
        cerr << "line " << lineCount << ": \'" << error << "\' , No such one in " << type << endl;
    }
    exit(SYNTAX_ERROR);
}

void TM::addDelta(string &line)
{
    removeComment(line);
    vector<string> tmp;
    getLineElement(line, ' ', &tmp);

    if (tmp.size() != 5)
        printMessage(SYNTAX_ERROR, SYNTAX_ERROR);
#if 0
    for (auto &s : tmp)
        cout << s << ' ';
    cout << endl;
#endif

    //"<旧状态> <旧符号组> <新符号组> <方向组> <新状态>"，

    // check oldstate in states
    if (states.find(tmp[0]) == states.end())
    {
        reportDeltaError(tmp[0], "states");
    }
    // check oldsymbol
    for (int i = 0; i < tmp[1].size(); i++)
    {
        if (tmp[1][i] != '*' && tapeSymbols.find(tmp[1][i]) == tapeSymbols.end())
            reportDeltaError(tmp[1], "tapeSymbols");
    }
    // check newsymbol
    for (int i = 0; i < tmp[2].size(); i++)
    {
        if (tmp[2][i] != '*' && tapeSymbols.find(tmp[2][i]) == tapeSymbols.end())
            reportDeltaError(tmp[2], "tapeSymbols");
    }
    // check dir in l r *
    for (auto c : tmp[3])
    {
        if (c != 'l' && c != 'r' && c != '*')
            reportDeltaError(tmp[3], "directions");
    }
    // check newstate
    if (states.find(tmp[4]) == states.end())
    {
        reportDeltaError(tmp[4], "states");
    }
    // add to delta
    deltafunc.insert(pair<string, vector<string>>(tmp[0], {tmp[1], tmp[2], tmp[3], tmp[4]}));
}

void parseFile(const string &filename, TM *tm)
{
    ifstream input(filename, ios::in);
    if (!input)
    {
        cout << strerror(errno) << ": " << filename;
        printMessage(FILE_OPEN_ERROR, FILE_OPEN_ERROR);
    }
    string line;
    while (getline(input, line))
    {
        lineCount++;
        if (line.empty() || line[0] == ';')
            continue;
        if (line[0] == '#')
        {
            switch (line[1])
            {
            case 'Q':
            case 'S':
            case 'G':
            case 'F':
            {
                tm->addValue(line);
            }
            break;
            case 'B':
                break;
            case 'q':
            case 'N':
                tm->setValue(line);
                break;
            default:
                printMessage(UNKNOWN_GRAMMAR, UNKNOWN_GRAMMAR);
                break;
            }
        }
        else // delta functions
        {
            tm->addDelta(line);
        }
    }
    input.close();
}

void TM::checkInput(const string &input) const
{
    for (int i = 0; i < input.length(); ++i)
    {
        if (inputSymbols.find(input[i]) == inputSymbols.end())
        {
            if (verbose)
            {
                cout << "Input: " << input << endl;
                cout << "==================== ERR ====================" << endl;
                cout << "error: \'" << input[i] << "\' was not declared in the set of input symbols" << endl;
                cout << "Input: " << input << endl;
                cout << string(7 + i, ' ') << '^' << endl;
                cout << "==================== END ====================" << endl;
                exit(ILLEGAL_INPUT);
            }
            else
            {
                printMessage(ILLEGAL_INPUT, ILLEGAL_INPUT);
            }
        }
    }
    cout << "Input:" << input << endl;
    cout << "==================== RUN ====================" << endl;
}

void TM::setTapes(const string &input)
{
    Tape *first = new Tape(input);
    tapes.push_back(first);
    for (int i = 1; i < tapeNumber; ++i)
    {
        Tape *p = new Tape();
        tapes.push_back(p);
    }
}

TM::TM(const string &filename, bool v) : verbose(v), steps(0), BLANK('_')
{
    parseFile(filename, this);
    currentState = startState;
    printSelf();
}
/*
Step   : 0
Index0 : 0 1 2 3 4 5 6
Tape0  : 1 0 0 1 0 0 1
Head0  : ^
Index1 : 0
Tape1  : _
Head1  : ^
State  : 0
*/
void Tape::getBorder(int &leftbeg, int &rightbeg, int &end) const
{
    while (leftbeg < 0 && leftHalf[-leftbeg - 1] == '_' && leftbeg != head)
        leftbeg++;
    while (end >= 0 && rightHalf[end] == '_' && end != head)
        --end;
    if (leftbeg >= 0)
    {
        while (rightbeg < end && rightHalf[rightbeg] == '_' && rightbeg != head)
            rightbeg++;
    }
}

void Tape::printTapeContent(const int &leftbeg, const int &rightbeg, const int &end, bool printBlank) const
{
    for (int i = -leftbeg - 1; i >= 0; --i)
    {
        cout << leftHalf[i];
        if (printBlank)
        {
            cout << string(to_string(i).size(), ' '); //上下对齐
        }
    }
    for (int i = rightbeg; i <= end; ++i)
    {
        cout << rightHalf[i];
        if (printBlank)
        {
            cout << string(to_string(i).size(), ' ');
        }
    }
}

void Tape::printResult()
{
    int leftbeg = -leftHalf.size(), end = rightHalf.size() - 1, rightbeg = 0;
    getBorder(leftbeg, rightbeg, end);
    printTapeContent(leftbeg, rightbeg, end, false);
}

void Tape::printSelf(int idx) const
{

#ifndef DEBUG
    cout << "leftHalf: " << leftHalf << endl;
    cout << "rightHalf: " << rightHalf << endl;
#endif

    int leftbeg = -leftHalf.size(), end = rightHalf.size() - 1, rightbeg = 0;
    getBorder(leftbeg, rightbeg, end);

    cout << "Index" << idx << " : ";
    for (int i = -leftbeg; i > 0; --i)
        cout << i << ' ';
    for (int i = rightbeg; i <= end; ++i)
        cout << i << ' ';

    cout << endl
         << "Tape" << idx << "  : ";
    printTapeContent(leftbeg, rightbeg, end);

    cout << endl
         << "Head" << idx << "  : ";
    if (leftbeg >= 0)
        leftbeg = rightbeg;
    int blankCount = 0;
    for (int j = leftbeg; j < head; ++j)
    {
        blankCount += to_string(abs(j)).size() + 1;
    }
    cout << string(blankCount, ' ') << '^' << endl;
}

void TM::printId() const
{
    cout << "Step   : " << steps << endl;
    cout << "State  : " << currentState << endl;
    for (int i = 0; i < tapes.size(); ++i)
    {
        tapes[i]->printSelf(i);
    }
    cout << "---------------------------------------------" << endl;
}

void TM::findFunc(multimap<string, vector<string>>::iterator &it) //找到合适的转移函数
{
    string curSym;
    for (int i = 0; i < tapes.size(); ++i)
    {
        curSym += tapes[i]->getCurrVal();
    }
    auto beg = deltafunc.lower_bound(currentState);
    auto end = deltafunc.upper_bound(currentState);
    for (; beg != end; ++beg)
    {
        string patternSym = beg->second[0];
        int i = 0;
        for (; i < curSym.size(); ++i)
        {
            if (patternSym[i] == curSym[i])
                continue;
            else if (patternSym[i] == '*')
            {
                if (curSym[i] != '_')
                    continue;
                else
                    break;
            }
            else
                break;
        }
        if (i == curSym.size())
            it = beg;
    }
}

void TM::Move(const string &newSym, const string &dir)
{
    for (int i = 0; i < newSym.size(); ++i)
    {
        tapes[i]->setNewSym(newSym[i]);
        tapes[i]->move(dir[i]);
    }
}

void TM::printResult()
{
    if (verbose)
        cout << "Result: ";
    tapes[0]->printResult();
    if (verbose)
        cout << endl
             << "==================== END ====================";
    cout << endl;
}

//"<旧状态> -> <旧符号组> <新符号组> <方向组> <新状态>"
void TM::run(const string &input)
{
    checkInput(input);
    setTapes(input);
    while (true)
    {
        if (verbose)
            printId();
        auto it = deltafunc.end();
        findFunc(it);
        if (it == deltafunc.end())
            break;
        string &newSym = it->second[1];
        string &dir = it->second[2];
        string &newstate = it->second[3];
        Move(newSym, dir);
        currentState = newstate;
        steps++;
    }
    printResult();
}

void TM::printSelf() const
{
    cout << "states: ";
    for (auto &i : states) // Q
        cout << i << ' ';
    cout << endl
         << "inputSymbols: ";
    for (auto &i : inputSymbols) // S
        cout << i << ' ';
    cout << endl
         << "tapeSymbols: ";
    for (auto &i : tapeSymbols) // G
        cout << i << ' ';
    cout << endl
         << "finalStates: ";
    for (auto &i : finalStates) // F
        cout << i << ' ';
    cout << endl
         << "startState: " << startState << endl;     // startState
    cout << "BLANK: " << BLANK << endl;               // B
    cout << "tapeNumber: " << tapeNumber << endl;     // N
    cout << "steps: " << steps << endl;               // steps
    cout << "currentState: " << currentState << endl; // currentState
    cout << "verbose: " << verbose << endl;           // verbose
}