#pragma once

static constexpr size_t MaxCommandNameLength = 16;

enum class CommandNames
{
    none,
    id,
    foo,
    bar,
    count
};

bool StringToCommandName(const char* string, CommandNames& command);