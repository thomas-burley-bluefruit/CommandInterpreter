#pragma once

#include "Command.h"
#include "CommandNames.h"

class CommandHandlerInterface
{
public:
    virtual CommandNames Name() const = 0;
    virtual void Run(Command& command) = 0;
};