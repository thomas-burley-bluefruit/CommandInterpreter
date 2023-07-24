#pragma once
#include "Command.h"

class Terminal
{
public:
    Terminal(Command& command);
    void OnReceiveInterrupt(const uint8_t byte);

    size_t CommandIndex();

private:
    Command& mCommand;
    size_t mCommandIndex = 0;
};