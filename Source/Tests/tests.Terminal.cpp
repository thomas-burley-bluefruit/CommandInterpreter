#include "gtest/gtest.h"
#include "Command.h"
#include "CommandHandlerSpy.h"
#include "Terminal.h"
#include "UartSpy.h"

class TerminalTests : public ::testing::Test
{
public:
  TerminalTests() : mTerminal(mUart)
  {}

protected:
    UartSpy mUart;
    Terminal mTerminal;
};

TEST_F(TerminalTests, command_is_passed_to_registered_handler)
{
    // Given
    std::string commandString = "test\n";
    CommandHandlerSpy handler;
    mTerminal.RegisterCommandHandler(&handler);

    // When
    for (const auto& ch : commandString)
    {
        mTerminal.OnReceiveInterrupt(ch);
    }

    // Then
    ASSERT_TRUE(handler.RunCalled);
    ASSERT_EQ(CommandNames::test, handler.RunCommand.GetName());
}

TEST_F(TerminalTests, can_not_register_above_max_commands)
{
  // Given
    CommandHandlerSpy handler;
    for (size_t i = 0; i < Terminal::MaxCommandHandlers; i++)
    {
        mTerminal.RegisterCommandHandler(&handler);
    }

    // When Then
    EXPECT_DEATH(mTerminal.RegisterCommandHandler(&handler), "");
}

// WIP
// TEST_F(TerminalTests, malformed_command_name_sets_invalid_flag)
// {
//     // Given
//     std::string commandString = "invalid\n";
//     CommandHandlerSpy handler;
//     mTerminal.RegisterCommandHandler(&handler);

//     // When
//     for (const auto& ch : commandString)
//     {
//         mTerminal.OnReceiveInterrupt(ch);
//     }

//     // Then
// }
