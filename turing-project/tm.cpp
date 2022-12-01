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

void removeBrackets(string &line) //得到{}中的部分
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

void split(string &line, vector<string> &receiver, char split) // case 1 & case 3
{
    stringstream ss(line);
    string token;
    while (getline(ss, token, split))
    {
        receiver.push_back(token);
    }
#if 0
    for (auto &i : receiver)
        cout << i << ' ';
    cout << endl;
#endif
}

void TM::addValue(string &line, char type)
{
    switch (type)
    {
    case 'Q':
        split(line, this->states, ',');
        break;
    case 'S':
        split(line, this->inputSymbols, ',');
        break;
    case 'G':
        split(line, this->tapeSymbols, ',');
        break;
    case 'F':
        split(line, this->finalStates, ',');
        break;
    }
}
void TM::parseDelta(string &line)
{
    removeComment(line);
    vector<string> tmp;
    split(line, tmp, ' ');
}
void TM::parseFile(const string &filename)
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
                char c = line[1];
                removeBrackets(line);
                addValue(line, c);
            }
            break;
            case 'B':
                break;
            case 'q':
            case 'N':
                setValue(line);
                break;
            default:
                printMessage(UNKNOWN_GRAMMAR, UNKNOWN_GRAMMAR);
                break;
            }
        }
        else // delta functions
        {
            parseDelta(line);
        }
    }
    input.close();
}

TM::TM(const string &filename, bool v) : verbose(v)
{
    parseFile(filename);
    steps = 0;
    currentState = startState;
    BLANK = '_';
    printSelf();
}
void TM::run(const string &input)
{
}

void TM::printSelf()
{
    cout << "states :" << endl;
    for (auto &i : states)
        cout << i << ' ';
    cout << endl
         << "inputSymbols" << endl; // Q
    for (auto &i : inputSymbols)
        cout << i << ' ';
    cout << endl
         << "tapeSymbols" << endl; // S
    for (auto &i : tapeSymbols)
        cout << i << ' ';
    cout << endl
         << "finalStates" << endl; // G
    for (auto &i : finalStates)
        cout << i << ' '; // F
    cout << endl
         << "startState " << startState << endl;
    cout << "BLANK: " << BLANK << endl;           // B
    cout << "tapeNumber: " << tapeNumber << endl; // N

    cout << "steps: " << steps << endl;               // steps
    cout << "currentState: " << currentState << endl; //
    cout << "verbose: " << verbose << endl;
}