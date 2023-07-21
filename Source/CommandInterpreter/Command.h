#pragma once

#include "CommandNames.h"

#include <array>
#include <cstddef>
#include <cstdint>

class Command
{
public:
    static constexpr size_t MaxRawCommandLength = 128;
    static constexpr size_t MaxArguments = 8;

    void SetName(CommandNames name);
    CommandNames GetName() const;
    void SetArgument(const size_t index, char* arg);
    const char* GetArgument(const size_t index) const;
    std::array<char, MaxRawCommandLength> mRawCommand {};

private:
    CommandNames mCommandName = CommandNames::None;
    size_t mArgCount = 0;
    uint32_t mSender = 0;
    uint32_t mTarget = 0;
    std::array<char*, MaxArguments> mArguments {};
};
