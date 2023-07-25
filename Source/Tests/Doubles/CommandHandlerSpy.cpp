#include "CommandHandlerSpy.h"

CommandNames CommandHandlerSpy::Name() const
{
    return CommandNames::test;
}

void CommandHandlerSpy::Run(Command& command)
{
    RunCalled = true;
    RunCommand = command;
}
