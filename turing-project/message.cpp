#include "message.h"
#include <string>
#include <iostream>

static std::string message[] = {
    "usage: turing [-v|--verbose] [-h|--help] <tm> <input>",
    "lack TM",
    ", file open failed",
    "arg format error,expecting *.tm",
    "lack input for TM",
    "unknown grammar in input file",
};

void printMessage(Message m, Message exit_code)
{
    std::cout << message[m] << std::endl;
    if (exit_code != 0)
        exit(exit_code);
}