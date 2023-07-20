#include "CommandInterpreter.h"

CommandInterpreter::CommandInterpreter() {}

Command CommandInterpreter::Interpret(std::array<char, MaxRawCommandLength> rawCommand)
{
    Command command{};

    mRawCommandBegin = rawCommand.begin();
    mRawCommandEnd = rawCommand.end();
    ExtractName(command);

    return command;
}

void CommandInterpreter::ExtractName(Command& command)
{
    std::array<char, Command::MaxCommandNameLength> commandName;
    commandName.fill(0);
    for (auto& ch : commandName)
    {
        auto commandChar = *mRawCommandBegin;
        if (commandChar == RawCommandTerminator || 
            commandChar == CommandArgSeparator)
        {
            break;
        }

        ch = *mRawCommandBegin++;
    }

    command.SetName(commandName.data());
}

void CommandInterpreter::ExtractArgs(Command& command)
{
    ConsumeSpaces();
    size_t argIndex = 0;
    while (mRawCommandBegin != mRawCommandEnd)
    {
        
    }
}

void CommandInterpreter::ConsumeSpaces()
{
    while (*mRawCommandBegin++ == ' ' && mRawCommandBegin != mRawCommandEnd);
}