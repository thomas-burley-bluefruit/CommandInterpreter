#include "Terminal.h"

#include <cassert>

Terminal::Terminal(UartInterface& uart) : mUart(uart)
{}

void Terminal::OnReceiveInterrupt(const uint8_t byte)
{
    // fill buffer
    char character = static_cast<char>(byte);
    mCommand.GetRawCommand()[mCommandIndex] = character;
    if (character != '\n')
    {
        mCommandIndex++;
        return;
    }

    // set command name
    mCommand.GetRawCommand()[mCommandIndex] = '\0';
    CommandNames extractedName = CommandNames::none;
    if (!StringToCommandName(mCommand.GetRawCommand().data(), extractedName))
    {
        return; // TODO
    }
    mCommand.SetName(extractedName);

    // run command
    for (CommandHandlerInterface* handler : mCommandHandlers)
    {
        if(handler->Name() == mCommand.GetName())
        {
            handler->Run(mCommand);
            return;
        }
    }
}

void Terminal::RegisterCommandHandler(CommandHandlerInterface* handler)
{
    assert(mCommandHandlerCount < MaxCommandHandlers);
    mCommandHandlers[mCommandHandlerCount++] = handler;
}
