#include "CommandInterpreter.h"
#include <string>

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

    rawCommand[commandNamePartEndIndex] = '\0';
    const char* commandNameString = &rawCommand[commandIndex];
    auto commandName = CommandNames::none;

    if (!StringToCommandName(commandNameString, commandName))
    {
        return;
    }
    command.SetName(commandName);

    // command.SetArgument(command.GetArgCount(), commandIndex);
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
    try
    {
        outInt = std::stoi(&command[index], &index);
    }
    catch ([[maybe_unused]]int e)
    {
        return false;
    }

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
