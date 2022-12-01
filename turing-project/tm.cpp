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

void TM::setValue(string &line) // q0 B N
{
    
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
            {
                removeBrackets(line);
                split(line, this->states, ',');
            }
            break;
            case 'S':
            {
                removeBrackets(line);
                split(line, this->inputSymbols, ',');
            }
            break;
            case 'G':
            {
                removeBrackets(line);
                split(line, this->tapeSymbols, ',');
            }
            break;
            case 'F':
            {
                removeBrackets(line);
                split(line, this->finalStates, ',');
            }
            break;
            case 'B':
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
        }
    }
    input.close();
}

TM::TM(const string &filename, bool v) : verbose(v)
{
    parseFile(filename);
    steps = 0;
    currentState = startState;
}
void TM::run(const string &input)
{
}