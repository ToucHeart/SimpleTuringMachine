#include "message.h"
#include <iostream>

static const char *message[] = {
    [NORMAL] = "usage: turing [-v|--verbose] [-h|--help] <tm> <input>",
    [LACK_FILE] = "lack TM",
    [FILE_OPEN_ERROR] = ", file open failed",
    [ARG_FORMAT_ERROR] = "arg format error,expecting *.tm",
    [LACK_INPUT] = "lack input for TM",
    [UNKNOWN_GRAMMAR] = "unknown grammar in input file",
    [SYNTAX_ERROR] = "syntax error",
    [ILLEGAL_INPUT] = "illegal input",
    [RUNTIME_ERROR] = "runtime error",
    [NO_BRACKETS] = "no brackets found in states or symbols",
};

void printMessage(Message m, Message exit_code, bool endline)
{
    std::cout << message[m];
    if (endline)
        std::cout << std::endl;
    if (exit_code != 0)
        exit(exit_code);
}