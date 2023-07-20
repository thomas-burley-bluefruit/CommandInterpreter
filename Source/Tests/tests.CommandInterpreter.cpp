#include "gtest/gtest.h"
#include "CommandInterpreter.h"

#include <array>
#include <string>

std::array<char, CommandInterpreter::MaxRawCommandLength> CreateRawCommand(std::string command)
{
    std::array<char, CommandInterpreter::MaxRawCommandLength> rawCommand;
    strncpy(rawCommand.data(), command.data(), CommandInterpreter::MaxRawCommandLength);
    return rawCommand;
}

TEST(CommandInterpreterTests, command_name_extraced_correctly)
{
    // Given
    auto rawCommand = CreateRawCommand("foo");
    CommandInterpreter interpreter;

    // When
    auto command = interpreter.Interpret(rawCommand);

    // Then
    ASSERT_STREQ("foo", command.GetName());
}

TEST(CommandInterpreterTests, first_argument_extracted_correctly)
{
    // Given
    auto rawCommand = CreateRawCommand("foo bar");
    CommandInterpreter interpreter;

    // When
    auto command = interpreter.Interpret(rawCommand);

    // Then
    ASSERT_STREQ("foo", command.GetName());
    ASSERT_STREQ("bar", command.GetArgument(0));
}