#pragma once

#include "CommandNames.h"

#include <array>
#include <cstddef>
#include <cstdint>

class Command
{
public:
    static constexpr size_t MaxRawCommandLength = 128;
    typedef std::array<char, MaxRawCommandLength> RawCommand;
    static constexpr size_t MaxArguments = 8;

    std::array<char, MaxRawCommandLength>& GetRawCommand();
    void SetName(CommandNames name);
    CommandNames GetName() const;
    bool AddArgument(const size_t rawCommandPositionIndex);
    const char* GetArgument(const size_t index) const;
    size_t GetArgCount() const;
    void SetSender(uint32_t id);
    uint32_t GetSender() const;
    void SetTarget(uint32_t id);
    uint32_t GetTarget() const;
    void SetIsValid(const bool valid);
    bool GetIsValid() const;

private:
    RawCommand mRawCommand {};
    bool mIsValid = false;
    CommandNames mCommandName = CommandNames::none;
    size_t mArgCount = 0;
    uint32_t mSender = 0;
    uint32_t mTarget = 0;
    std::array<char*, MaxArguments> mArguments {};
};
