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
    static constexpr size_t SeparatorCount = 2;
    const std::array<char, SeparatorCount> Separators = { ' ', '\n' };

    bool ParseSender(Command& command, size_t& index);
    bool ParseTarget(Command& command, size_t& index);
    bool ParseCommand(Command& command, size_t& index);
    bool ParseArguments(Command& command, size_t& index);

    bool FindNextNonSeparator(size_t& startIndex, Command::RawCommand& command) const;
    bool FindNextSeparator(size_t& startIndex, Command::RawCommand& command) const;
    bool IsSeparator(char c) const;
    bool ExtractInteger(Command::RawCommand& command, size_t& index, uint32_t& outInt);
    // void ExtractName(Command& command);
    // void ExtractArgs(Command& command);
};
