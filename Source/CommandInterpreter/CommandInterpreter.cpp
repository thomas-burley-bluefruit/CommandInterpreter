#include "CommandInterpreter.h"
#include <cstring>
#include <iostream>

CommandInterpreter::CommandInterpreter() {}

void CommandInterpreter::Interpret(Command& command)
{
    char commandName[Command::MaxRawCommandLength];
    for(size_t i = 0; i < Command::MaxRawCommandLength; i++)
    {
        commandName[i] = command.mRawCommand[i];
    }

    if (strncmp(commandName, "Id", Command::MaxRawCommandLength))
        command.SetName(CommandNames::Id);
    else
        command.SetName(CommandNames::None);

    std::cout << "command Name: " << commandName << '\n';

    // mRawCommandBegin = rawCommand.begin();
    // mRawCommandEnd = rawCommand.end();
    // ExtractName(command);
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

// void CommandInterpreter::ConsumeSpaces()
// {
//     while (*mRawCommandBegin++ == ' ' && mRawCommandBegin != mRawCommandEnd);
// }