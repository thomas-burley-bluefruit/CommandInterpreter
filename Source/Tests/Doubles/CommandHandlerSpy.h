#pragma once

#include "CommandHandlerInterface.h"

class CommandHandlerSpy : public CommandHandlerInterface
{
public:
    CommandNames Name() const override;
    void Run(Command& command) override;

    bool RunCalled = false;
    Command RunCommand {};
};
