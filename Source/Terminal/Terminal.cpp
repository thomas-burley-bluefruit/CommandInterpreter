#include "Terminal.h"

#include <cassert>

Terminal::Terminal(UartInterface& uart) : mUart(uart)
{}

void Terminal::OnReceiveInterrupt(const uint8_t byte)
{
    char character = static_cast<char>(byte);
    mCommand.GetRawCommand()[mCommandIndex++] = character;
}

void Terminal::RegisterCommandHandler(CommandHandlerInterface* handler)
{
    mCommandHandlers[mCommandHandlerCount++] = handler;
}