#pragma once

#include "UartInterface.h"
#include <array>

class UartSpy : public UartInterface
{
public:
    void Init() override;
    void Transmit(const uint8_t *txData, size_t size) const override;
    void SetCallback(ReceiveInterruptCallbackInterface *callback) const override;

private:
    static constexpr size_t TransmitBufferSize = 128;

public:
    mutable bool SetCallbackCalled = false;
    mutable ReceiveInterruptCallbackInterface * Callback;

    mutable bool TransmitCalled = false;
    size_t TransmitSize = 0;
    mutable std::array<uint8_t, TransmitBufferSize> TxData {};
};
