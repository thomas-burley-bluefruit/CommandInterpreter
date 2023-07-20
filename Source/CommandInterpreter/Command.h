#pragma once

#include <array>
#include <cstddef>

class Command
{
public:
    void SetName(const char *name);
    const char* GetName() const;
    void SetArgument(const size_t index, const char* arg);
    const char* GetArgument(const size_t index) const;

    static constexpr size_t MaxCommandNameLength = 16;
    static constexpr size_t MaxCommandArgLength = 16;
    static constexpr size_t MaxArguments = 8;

private:
    size_t mArgCount = 0;
    std::array<char, MaxCommandNameLength> mCommandName {};
    std::array<std::array<char, MaxCommandArgLength>, MaxArguments> mArguments {};
};
