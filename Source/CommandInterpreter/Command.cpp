#include "Command.h"
#include <string>


Command::RawCommand& Command::GetRawCommand()
{
    return mRawCommand;
}

void Command::SetName(CommandNames name)
{
    mCommandName = name;
}

CommandNames Command::GetName() const
{
    return mCommandName;
}

void Command::SetSender(uint32_t id)
{
    mSender = id;
}

uint32_t Command::GetSender() const
{
    return mSender;
}

void Command::SetTarget(uint32_t id)
{
    mTarget = id;
}

uint32_t Command::GetTarget() const
{
    return mTarget;
}


bool Command::AddArgument(const size_t rawCommandPositionIndex)
{
    if (rawCommandPositionIndex > MaxRawCommandLength || mArgCount >= MaxArguments)
    {
        return false;
    }

    mArguments[mArgCount++] = &mRawCommand[rawCommandPositionIndex];

    return true;
}

const char* Command::GetArgument(const size_t index) const
{
    if (index > mArgCount)
    {
        return "";
    }

    return mArguments[index];
}

size_t Command::GetArgCount() const
{
    return mArgCount;
}

void Command::SetIsValid(const bool valid)
{
    mIsValid = valid;
}

bool Command::GetIsValid() const
{
    return mIsValid;
}