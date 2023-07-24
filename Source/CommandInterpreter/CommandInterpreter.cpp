#include "CommandInterpreter.h"
#include <string>
#include <cstdlib>

CommandInterpreter::CommandInterpreter() {}

void CommandInterpreter::Interpret(Command& command)
{
    size_t commandIndex = 0;
    auto& rawCommand = command.GetRawCommand();

    // Sender
    uint32_t sender = 0;
    if (!ExtractInteger(rawCommand, commandIndex, sender))
    {
        return;
    }
    command.SetSender(sender);

    // Skip separators
    if (!FindNextNonSeparator(commandIndex, rawCommand))
    {
        return;
    }

    // Target
    uint32_t target = 0;
    if (!ExtractInteger(rawCommand, commandIndex, target))
    {
        return;
    }
    command.SetTarget(target);

    // Skip separators
    if (!FindNextNonSeparator(commandIndex, rawCommand))
    {
        return;
    }

    // Command name
    size_t commandNamePartEndIndex = commandIndex;
    if (!FindNextSeparator(commandNamePartEndIndex, rawCommand))
    {
        return;
    }

    bool hasArguments = rawCommand[commandNamePartEndIndex] == ' ';
    rawCommand[commandNamePartEndIndex] = '\0';
    const char* commandNameString = &rawCommand[commandIndex];

    auto commandName = CommandNames::none;
    if (!StringToCommandName(commandNameString, commandName))
    {
        return;
    }
    command.SetName(commandName);

    if (!hasArguments)
    {
        return;
    }

    commandIndex = commandNamePartEndIndex;

    // Arguments
    while (commandIndex < Command::MaxRawCommandLength)
    {
        if (rawCommand[commandIndex++] == '\n')
        {
            break;
        }

        size_t argumentPartEndIndex = commandIndex;
        if (!FindNextSeparator(argumentPartEndIndex, rawCommand))
        {
            return;
        }

        rawCommand[argumentPartEndIndex] = '\0';
        command.AddArgument(commandIndex);
        commandIndex = argumentPartEndIndex;
    }
}

bool CommandInterpreter::ParseSender(Command& command, size_t& index)
{

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
