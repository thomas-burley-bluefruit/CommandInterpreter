#pragma once

#include <cstddef>

#include "Command.h"

class CommandInterpreter
{
public:
    CommandInterpreter();
    void Interpret(Command& command);

private:
    static constexpr char RawCommandTerminator = '\0';
    static constexpr char CommandArgSeparator = ' ';

    void ExtractName(Command& command);
    void ExtractArgs(Command& command);
    void ConsumeSpaces();
    std::array<char, MaxRawCommandLength>::iterator mRawCommandBegin;
    std::array<char, MaxRawCommandLength>::iterator mRawCommandEnd;
};
