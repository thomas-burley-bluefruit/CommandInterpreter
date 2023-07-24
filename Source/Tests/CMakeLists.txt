set(NAME Tests.Terminal)

set(SOURCES
        tests.Terminal.cpp
        tests.CommandInterpreter.cpp)

set(INCLUDES .)

add_executable(${NAME} ${SOURCES})
target_include_directories(${NAME} PRIVATE ${INCLUDES})
target_link_libraries(${NAME} PUBLIC Terminal gtest_main)

include(GoogleTest)
gtest_discover_tests(${NAME})