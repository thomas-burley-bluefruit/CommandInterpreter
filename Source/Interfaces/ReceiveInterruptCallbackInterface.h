#pragma once

#include <cstddef>
#include <cstdint>

class ReceiveInterruptCallbackInterface
{
public:
    virtual ~ReceiveInterruptCallbackInterface() = default;

    virtual void OnReceiveInterrupt(uint8_t byte) = 0;
};
