#include "gtest/gtest.h"
#include "CommandNames.h"
#include "CommandInterpreter.h"

#include <array>
#include <string>

// std::array<char, CommandInterpreter::MaxRawCommandLength> CreateRawCommand(std::string command)
// {
//     std::array<char, CommandInterpreter::MaxRawCommandLength> rawCommand;
//     strncpy(rawCommand.data(), command.data(), CommandInterpreter::MaxRawCommandLength);
//     return rawCommand;
// }

Command CreateRawCommand(std::string uartString)
{
    Command command{};
    std::copy(uartString.begin(), uartString.end(), command.mRawCommand.begin());
    return command;
}

// TEST(CommandInterpreterTests, command_name_extraced_correctly)
// {
//     // Given
//     auto rawCommand = CreateRawCommand("foo");
//     CommandInterpreter interpreter;

//     // When
//     auto command = interpreter.Interpret(rawCommand);

//     // Then
//     ASSERT_STREQ("foo", command.GetName());
// }

// TEST(CommandInterpreterTests, first_argument_extracted_correctly)
// {
//     // Given
//     auto rawCommand = CreateRawCommand("foo bar");
//     CommandInterpreter interpreter;

//     // When
//     auto command = interpreter.Interpret(rawCommand);

//     // Then
//     ASSERT_STREQ("foo", command.GetName());
//     ASSERT_STREQ("bar", command.GetArgument(0));
// }

TEST(CommandInterpreterTests, command_name_extracted_correctly)
{
    // Given
    auto command = CreateRawCommand("Id");
    CommandInterpreter interpreter;

    // When
    interpreter.Interpret(command);

    // Then
    ASSERT_EQ(command.GetName(), CommandNames::Id);
}

