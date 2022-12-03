#ifndef __MESSAGE__
#define __MESSAGE__

typedef enum Message
{
    NORMAL,
    LACK_FILE,
    FILE_OPEN_ERROR,
    ARG_FORMAT_ERROR,
    LACK_INPUT,
    UNKNOWN_GRAMMAR,
    SYNTAX_ERROR,
    ILLEGAL_INPUT,
    RUNTIME_ERROR,
    NO_BRACKETS,
} Message;

void printMessage(Message m, Message exit_code, bool endline = true);

#endif