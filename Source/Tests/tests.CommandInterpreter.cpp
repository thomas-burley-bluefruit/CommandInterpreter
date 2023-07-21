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
    std::copy(uartString.begin(), uartString.end(), command.GetRawCommand().begin());
    return command;
}

TEST(CommandInterpreterTests, single_digit_sender_id_parsed_correctly)
{
    // Given
    auto command = CreateRawCommand("1.2:test");
    CommandInterpreter interpreter;

    // When
    interpreter.Interpret(command);

    // Then
    ASSERT_EQ(1, command.GetSender());
}

TEST(CommandInterpreterTests, double_digit_sender_id_parsed_correctly)
{
    // Given
    auto command = CreateRawCommand("12.2:test");
    CommandInterpreter interpreter;

    // When
    interpreter.Interpret(command);

    // Then
    ASSERT_EQ(12, command.GetSender());
}

TEST(CommandInterpreterTests, target_id_parsed_correctly)
{
    // Given
    auto command = CreateRawCommand("12.2:test");
    CommandInterpreter interpreter;

    // When
    interpreter.Interpret(command);

    // Then
    ASSERT_EQ(2, command.GetTarget());
}

TEST(CommandInterpreterTests, command_name_extracted_correctly)
{
    // Given
    auto command = CreateRawCommand("1.2:id");
    CommandInterpreter interpreter;

    // When
    interpreter.Interpret(command);

    // Then
    ASSERT_EQ(command.GetName(), CommandNames::id);
}
