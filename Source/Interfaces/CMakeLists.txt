set(NAME Interfaces)

set(SOURCES
    CommandHandlerInterface.h    
    ReceiveInterruptCallbackInterface.h
    UartInterface.h
    )

set(INCLUDES .)

add_library(${NAME} INTERFACE ${SOURCES})
target_include_directories(${NAME} INTERFACE ${INCLUDES})