#pragma once

#include <cstddef>

#include "Command.h"

class CommandInterpreter
{
public:
    static constexpr size_t MaxRawCommandLength = 128;

    CommandInterpreter();
    Command Interpret(std::array<char, MaxRawCommandLength> rawCommand);

private:
    static constexpr char RawCommandTerminator = '\0';
    static constexpr char CommandArgSeparator = ' ';

    void ExtractName(Command& command);
    void ExtractArgs(Command& command);
    void ConsumeSpaces();
    std::array<char, MaxRawCommandLength>::iterator mRawCommandBegin;
    std::array<char, MaxRawCommandLength>::iterator mRawCommandEnd;
};
