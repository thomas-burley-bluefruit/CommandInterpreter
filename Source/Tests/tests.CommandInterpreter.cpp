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
    auto command = CreateRawCommand("1 2 id\n");
    CommandInterpreter interpreter;

    // When
    interpreter.Interpret(command);

    // Then
    ASSERT_TRUE(command.GetIsValid());
    ASSERT_EQ(1, command.GetSender());
}

TEST(CommandInterpreterTests, double_digit_sender_id_parsed_correctly)
{
    // Given
    auto command = CreateRawCommand("12 2 id\n");
    CommandInterpreter interpreter;

    // When
    interpreter.Interpret(command);

    // Then
    ASSERT_TRUE(command.GetIsValid());
    ASSERT_EQ(12, command.GetSender());
}

TEST(CommandInterpreterTests, target_id_parsed_correctly)
{
    // Given
    auto command = CreateRawCommand("12 2 id\n");
    CommandInterpreter interpreter;

    // When
    interpreter.Interpret(command);

    // Then
    ASSERT_TRUE(command.GetIsValid());
    ASSERT_EQ(2, command.GetTarget());
}

TEST(CommandInterpreterTests, too_many_int_arguments)
{
    // Given
    auto command = CreateRawCommand("12 2 3 id\n");
    CommandInterpreter interpreter;

    // When
    interpreter.Interpret(command);

    // Then
    ASSERT_FALSE(command.GetIsValid());
}

TEST(CommandInterpreterTests, too_few_int_arguments)
{
    // Given
    auto command = CreateRawCommand("12 id\n");
    CommandInterpreter interpreter;

    // When
    interpreter.Interpret(command);

    // Then
    ASSERT_FALSE(command.GetIsValid());
}

TEST(CommandInterpreterTests, no_separator_between_target_and_command_name)
{
    // Given
    auto command = CreateRawCommand("1 23id\n");
    CommandInterpreter interpreter;

    // When
    interpreter.Interpret(command);

    // Then
    ASSERT_FALSE(command.GetIsValid());
}

TEST(CommandInterpreterTests, command_name_parsed_correctly)
{
    // Given
    auto command = CreateRawCommand("1 2 id\n");
    CommandInterpreter interpreter;

    // When
    interpreter.Interpret(command);

    // Then
    ASSERT_TRUE(command.GetIsValid());
    ASSERT_EQ(command.GetName(), CommandNames::id);
}

TEST(CommandInterpreterTests, command_name_parsed_correctly_without_sender_and_target)
{
    // Given
    auto command = CreateRawCommand("id\n");
    CommandInterpreter interpreter;

    // When
    interpreter.Interpret(command);

    // Then
    ASSERT_TRUE(command.GetIsValid());
    ASSERT_EQ(command.GetName(), CommandNames::id);
}

TEST(CommandInterpreterTests, one_argument_parsed_correctly)
{
    // Given
    auto command = CreateRawCommand("1 2 id test\n");
    CommandInterpreter interpreter;

    // When
    interpreter.Interpret(command);

    // Then
    ASSERT_TRUE(command.GetIsValid());
    ASSERT_STREQ(command.GetArgument(0), "test");
}

TEST(CommandInterpreterTests, two_arguments_parsed_correctly)
{
    // Given
    auto command = CreateRawCommand("1 2 id test two\n");
    CommandInterpreter interpreter;

    // When
    interpreter.Interpret(command);

    // Then
    ASSERT_TRUE(command.GetIsValid());
    ASSERT_STREQ(command.GetArgument(0), "test");
    ASSERT_STREQ(command.GetArgument(1), "two");
}

TEST(CommandInterpreterTests, three_arguments_parsed_correctly)
{
    // Given
    auto command = CreateRawCommand("1 2 id test two three\n");
    CommandInterpreter interpreter;

    // When
    interpreter.Interpret(command);

    // Then
    ASSERT_TRUE(command.GetIsValid());
    ASSERT_STREQ(command.GetArgument(0), "test");
    ASSERT_STREQ(command.GetArgument(1), "two");
    ASSERT_STREQ(command.GetArgument(2), "three");
}

TEST(CommandInterpreterTests, target_and_sender_are_optional)
{
    // Given
    auto command = CreateRawCommand("id one two three\n");
    CommandInterpreter interpreter;

    // When
    interpreter.Interpret(command);

    // Then
    ASSERT_TRUE(command.GetIsValid());
    ASSERT_EQ(command.GetName(), CommandNames::id);
    ASSERT_STREQ(command.GetArgument(0), "one");
    ASSERT_STREQ(command.GetArgument(1), "two");
    ASSERT_STREQ(command.GetArgument(2), "three");
}

TEST(CommandInterpreterTests, wrong_separator)
{
    // Given
    auto command = CreateRawCommand("id.one\n");
    CommandInterpreter interpreter;

    // When
    interpreter.Interpret(command);

    // Then
    ASSERT_FALSE(command.GetIsValid());
}

TEST(CommandInterpreterTests, too_many_arguments)
{
    // Given
    std::string rawCommand = "id ";
    for (size_t i = 0; i < Command::MaxArguments + 1; ++i)
    {
        rawCommand += "arg ";
    }
    rawCommand += "\n";

    auto command = CreateRawCommand(rawCommand);

    CommandInterpreter interpreter;

    // When
    interpreter.Interpret(command);

    // Then
    ASSERT_FALSE(command.GetIsValid());
}

TEST(CommandInterpreterTests, max_valid_command_length)
{
    // Given
    std::string commandName = "id ";
    std::string maxLengthArg(Command::MaxRawCommandLength - (commandName.length() + 1), 'a');
    std::string rawCommand = commandName + maxLengthArg + "\n";

    auto command = CreateRawCommand(rawCommand);
    CommandInterpreter interpreter;

    // When
    interpreter.Interpret(command);

    // Then
    ASSERT_TRUE(command.GetIsValid());
    ASSERT_EQ(CommandNames::id, command.GetName());
    ASSERT_STREQ(maxLengthArg.c_str(), command.GetArgument(0));
}

TEST(CommandInterpreterTests, unterminated_command)
{
    // Given
    auto command = CreateRawCommand("id");
    CommandInterpreter interpreter;

    // When
    interpreter.Interpret(command);

    // Then
    ASSERT_FALSE(command.GetIsValid());
}