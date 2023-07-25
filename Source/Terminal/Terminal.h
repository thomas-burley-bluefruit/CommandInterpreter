#pragma once

#include "Command.h"
#include "CommandHandlerInterface.h"
#include "CommandInterpreter.h"
#include "UartInterface.h"

class Terminal
{
public:
    Terminal(UartInterface& uart);
    void OnReceiveInterrupt(const uint8_t byte);
    void RegisterCommandHandler(CommandHandlerInterface* handler);

private:
    static constexpr size_t MaxCommandHandlers = 32;

    size_t mCommandHandlerCount = 0;
    std::array<CommandHandlerInterface*, MaxCommandHandlers> 
        mCommandHandlers { nullptr };
    UartInterface& mUart;
    Command mCommand;
    CommandInterpreter mCommandInterpreter;
    size_t mCommandIndex = 0;
};
