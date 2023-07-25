set(NAME Doubles)

set(SOURCES
        CommandHandlerSpy.cpp
        CommandHandlerSpy.h
        UartSpy.cpp
        UartSpy.h)

set(INCLUDES .)

add_library(${NAME} STATIC ${SOURCES})
target_include_directories(${NAME} PUBLIC ${INCLUDES})
target_link_libraries(${NAME} PUBLIC Interfaces Terminal gtest_main)
