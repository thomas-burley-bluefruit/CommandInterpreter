#include "Command.h"
#include <string>

void Command::SetName(const char *name)
{
    strncpy(mCommandName.data(), name, MaxCommandNameLength);
}

const char* Command::GetName() const
{
    return mCommandName.data();
}

void Command::SetArgument(const size_t index, const char* arg)
{
    if (index > MaxArguments)
    {
            return;
    }

    strncpy(mArguments[index].data(), arg, MaxCommandArgLength);
}

const char* Command::GetArgument(const size_t index) const
{
    if (index > mArgCount)
    {
        return "";
    }

    return mArguments[index].data();
}