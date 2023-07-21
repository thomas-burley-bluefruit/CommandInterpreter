#include "Command.h"
#include <string>

void Command::SetName(CommandNames name)
{
    mCommandName = name;
}

CommandNames Command::GetName() const
{
    return mCommandName;
}

void Command::SetArgument(const size_t index, char* arg)
{
    if (index > MaxArguments)
    {
        return;
    }

    mArguments[index] = arg;
}

const char* Command::GetArgument(const size_t index) const
{
    if (index > mArgCount)
    {
        return "";
    }

    return mArguments[index];
}