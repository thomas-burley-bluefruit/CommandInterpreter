#include "CommandInterpreter.h"
#include <string>
#include <cstdlib>

CommandInterpreter::CommandInterpreter() {}

void CommandInterpreter::Interpret(Command& command)
{
    size_t commandIndex = 0;

    if (CharIsNumeric(command.GetRawCommand()[0]))
    {
        if (!ParseSender(command, commandIndex))
        {
            return;
        }

        if (!ParseTarget(command, commandIndex))
        {
            return;
        }
    }

    if (!ParseCommand(command, commandIndex))
    {
        return;
    }

    if (!ParseArguments(command, commandIndex))
    {
        return;
    }

    command.SetIsValid(true);
}

bool CommandInterpreter::ParseSender(Command& command, size_t& index)
{
    uint32_t sender = 0;
    auto& rawCommand = command.GetRawCommand();

    if (!ExtractInteger(rawCommand, index, sender))
    {
        return false;
    }
    command.SetSender(sender);

    return true;
}

bool CommandInterpreter::ParseTarget(Command& command, size_t& index)
{
    auto& rawCommand = command.GetRawCommand();

    // Skip separators
    if (!FindNextNonSeparator(index, rawCommand))
    {
        return false;
    }

    uint32_t target = 0;

    if (!ExtractInteger(rawCommand, index, target))
    {
        return false;
    }
    command.SetTarget(target);

    return true;
}

bool CommandInterpreter::ParseCommand(Command& command, size_t& index)
{
    auto& rawCommand = command.GetRawCommand();

    // Skip separators
    if (!FindNextNonSeparator(index, rawCommand))
    {
        return false;
    }

    size_t commandNamePartEndIndex = index;

    // Find end of word
    if (!FindNextSeparator(commandNamePartEndIndex, rawCommand))
    {
        return false;
    }

    rawCommand[commandNamePartEndIndex] = '\0';

    const char* commandNameString = &rawCommand[index];
    auto commandName = CommandNames::none;
    if (!StringToCommandName(commandNameString, commandName))
    {
        return false;
    }
    command.SetName(commandName);

    index = commandNamePartEndIndex + 1;
    return true;
}

bool CommandInterpreter::ParseArguments(Command& command, size_t& index)
{
    auto& rawCommand = command.GetRawCommand();
    while (index < Command::MaxRawCommandLength)
    {
        size_t argumentPartEndIndex = index;
        if (!FindNextSeparator(argumentPartEndIndex, rawCommand))
        {
            break;
        }

        bool endOfCommand = false;
        if (rawCommand[argumentPartEndIndex] == CommandTerminator)
        {
            endOfCommand = true;
        }

        rawCommand[argumentPartEndIndex] = '\0';
        
        if (!command.AddArgument(index))
        {
            return false;
        }

        index = argumentPartEndIndex + 1;

        if (endOfCommand)
        {
            break;
        }
    }
    return true;
}


bool CommandInterpreter::FindNextNonSeparator(size_t& startIndex, Command::RawCommand& command) const
{
    if (startIndex >= Command::MaxRawCommandLength)
    {
        return false;
    }

    for (; startIndex < Command::MaxRawCommandLength; ++startIndex)
    {
        if (!IsSeparator(command[startIndex]))
        {
            return true;
        }
    }

    return false;
}

bool CommandInterpreter::FindNextSeparator(size_t& startIndex, Command::RawCommand& command) const
{
    if (startIndex >= Command::MaxRawCommandLength)
    {
        return false;
    }

    for (; startIndex < Command::MaxRawCommandLength; ++startIndex)
    {
        const auto currentChar = command[startIndex];
        if (currentChar == '\0')
        {
            return false;
        }

        if (IsSeparator(currentChar) || currentChar == CommandTerminator)
        {
            return true;
        }
    }

    return false;
}

bool CommandInterpreter::IsSeparator(char c) const
{
    return c == Separator;
}

bool CommandInterpreter::ExtractInteger(Command::RawCommand& command, size_t& index, uint32_t& outInt)
{
    if (!CharIsNumeric(command[index]))
    {
        return false;
    }

    char* nextCharacter = nullptr;
    outInt = strtol(&command[index], &nextCharacter, 10);
    index += (nextCharacter - &command[index]);

    // Ensure integer is not part of a word
    if (!IsSeparator(command[index]))
    {
        return false;
    }

    return true;
}

bool CommandInterpreter::CharIsNumeric(const char c) const
{
    return c >= '0' && c <= '9';
}
