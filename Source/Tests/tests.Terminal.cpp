#include "gtest/gtest.h"
#include "Terminal.h"
#include "Command.h"

TEST(TerminalTests, OnReceiveInterrupt_adds_char_to_command_buffer)
{
    // Given
    Command command;
    Terminal terminal(command);
    const uint8_t uartChar = 'c';

    // When
    terminal.OnReceiveInterrupt(uartChar);

    // Then
    const size_t startIndex = 0;
    ASSERT_EQ(command.GetRawCommand()[startIndex], uartChar);
}

TEST(TerminalTests, OnReceiveInterrupt_increments_index_each_call)
{
    // Given
    Command command;
    Terminal terminal(command);

    const size_t startIndex = 0;
    ASSERT_EQ(terminal.CommandIndex(), startIndex);

    // When Then
    terminal.OnReceiveInterrupt('h');
    ASSERT_EQ(terminal.CommandIndex(), startIndex + 1);

    // When Then
    terminal.OnReceiveInterrupt('i');
    ASSERT_EQ(terminal.CommandIndex(), startIndex + 2);
}