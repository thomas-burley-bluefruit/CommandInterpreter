#include "CommandNames.h"

#include <cstring>

const char* CommandNameStrings[static_cast<size_t>(CommandNames::count)]
{
    "none",
    "test",
    "id",
    "help"
};

bool StringToCommandName(const char* string, CommandNames& command)
{
    for (size_t i = 0; i < static_cast<size_t>(CommandNames::count); ++i)
    {
        if (strncmp(string, CommandNameStrings[i], MaxCommandNameLength) == 0)
        {
            command = static_cast<CommandNames>(i);
            return true;
        }
    }

    return false;
}
