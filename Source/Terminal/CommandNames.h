#pragma once
#include <cstddef>

static constexpr size_t MaxCommandNameLength = 16;

enum class CommandNames
{
    none,
    test,
    id,
    help,
    count
};

bool StringToCommandName(const char* string, CommandNames& command);