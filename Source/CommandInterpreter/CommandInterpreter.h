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
    static constexpr size_t SeparatorCount = 3;
    const std::array<char, SeparatorCount> Separators = { '.', ':', ' ' };

    bool FindNextNonSeparator(size_t& startIndex, Command::RawCommand& command) const;
    bool FindNextSeparator(size_t& startIndex, Command::RawCommand& command) const;
    bool IsSeparator(char c) const;
    bool ExtractInteger(Command::RawCommand& command, size_t& index, uint32_t& outInt);
    // void ExtractName(Command& command);
    // void ExtractArgs(Command& command);
};
