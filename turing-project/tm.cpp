#include <fstream>
#include "message.h"
#include <iostream>
#include <cstring>
#include "tm.h"
using namespace std;

int TAPENUM;
static const char BLANK = '_';

void analyseFile(const string &filename)
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
        switch (line[1])
        {
        case 'Q':
            break;
        case 'S':
            break;
        case 'G':
            break;
        case 'B':
            break;
        case 'q':
            break;
        case 'F':
            break;
        case 'N':
            break;
        }
    }
    input.close();
}