#include "UartSpy.h"

void UartSpy::Init()
{
}

void UartSpy::Transmit(const uint8_t *txData, size_t size) const
{
    TransmitCalled = true;
    
    if (size > TransmitBufferSize)
    {
        return;
    }
    
    for (size_t i = 0; i < size; ++i)
    {
        TxData[i] = txData[i];
    }
}

void UartSpy::SetCallback(ReceiveInterruptCallbackInterface *callback) const
{
    SetCallbackCalled = true;
    Callback = callback;
}
