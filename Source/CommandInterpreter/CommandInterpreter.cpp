#include "CommandInterpreter.h"
#include <string>
#include <cstdlib>

CommandInterpreter::CommandInterpreter() {}

void CommandInterpreter::Interpret(Command& command)
{
    size_t commandIndex = 0;

    if (!ParseSender(command, commandIndex))
    {
        return;
    }

    if (!ParseTarget(command, commandIndex))
    {
        return;
    }

    if (!ParseCommand(command, commandIndex))
    {
        return;
    }

    if (!ParseArguments(command, commandIndex))
    {
        return;
    }
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

    // Skip separators
    if (!FindNextNonSeparator(index, rawCommand))
    {
        return false;
    }

    return true;
}

bool CommandInterpreter::ParseTarget(Command& command, size_t& index)
{
    uint32_t target = 0;
    auto& rawCommand = command.GetRawCommand();

    if (!ExtractInteger(rawCommand, index, target))
    {
        return false;
    }
    command.SetTarget(target);

    // Skip separators
    if (!FindNextNonSeparator(index, rawCommand))
    {
        return false;
    }

    return true;
}

bool CommandInterpreter::ParseCommand(Command& command, size_t& index)
{
    size_t commandNamePartEndIndex = index;
    auto& rawCommand = command.GetRawCommand();

    if (!FindNextSeparator(commandNamePartEndIndex, rawCommand))
    {
        return false;
    }

    bool hasArguments = rawCommand[commandNamePartEndIndex] == ' ';
    rawCommand[commandNamePartEndIndex] = '\0';

    const char* commandNameString = &rawCommand[index];
    auto commandName = CommandNames::none;
    if (!StringToCommandName(commandNameString, commandName))
    {
        return false;
    }
    command.SetName(commandName);

    if (!hasArguments)
    {
        return false;
    }

    index = commandNamePartEndIndex;
    return true;
}

bool CommandInterpreter::ParseArguments(Command& command, size_t& index)
{
    auto& rawCommand = command.GetRawCommand();
    while (index < Command::MaxRawCommandLength)
    {
        if (rawCommand[index++] == '\n')
        {
            break;
        }

        size_t argumentPartEndIndex = index;
        if (!FindNextSeparator(argumentPartEndIndex, rawCommand))
        {
            return false;
        }

        rawCommand[argumentPartEndIndex] = '\0';
        command.AddArgument(index);
        index = argumentPartEndIndex;
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
        if (IsSeparator(command[startIndex]))
        {
            return true;
        }
    }

    return false;
}

bool CommandInterpreter::IsSeparator(char c) const
{
    for (auto& separator : Separators)
    {
        if (c == separator)
        {
            return true;
        }
    }
    return false;
}

bool CommandInterpreter::ExtractInteger(Command::RawCommand& command, size_t& index, uint32_t& outInt)
{
    char* nextCharacter = nullptr;
    outInt = strtol(&command[index], &nextCharacter, 10);
    index += (nextCharacter - &command[index]);

    return true;
}

// void CommandInterpreter::ExtractName(Command& command)
// {
//     std::array<char, Command::MaxCommandNameLength> commandName;
//     commandName.fill(0);
//     for (auto& ch : commandName)
//     {
//         auto commandChar = *mRawCommandBegin;
//         if (commandChar == RawCommandTerminator || 
//             commandChar == CommandArgSeparator)
//         {
//             break;
//         }

//         ch = *mRawCommandBegin++;
//     }

//     command.SetName(commandName.data());
// }

// void CommandInterpreter::ExtractArgs(Command& command)
// {
//     ConsumeSpaces();
//     size_t argIndex = 0;
//     while (mRawCommandBegin != mRawCommandEnd)
//     {

//     }
// }
