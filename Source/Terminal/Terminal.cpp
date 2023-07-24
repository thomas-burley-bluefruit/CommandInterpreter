#include "Terminal.h"

Terminal::Terminal(Command& command) :
    mCommand(command)
{}

void Terminal::OnReceiveInterrupt(const uint8_t byte)
{
    char character = static_cast<char>(byte);
    mCommand.GetRawCommand()[mCommandIndex++] = character;
}

size_t Terminal::CommandIndex()
{
    return mCommandIndex;
}
