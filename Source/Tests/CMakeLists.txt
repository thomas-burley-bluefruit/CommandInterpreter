set(NAME Tests.CommandInterpreter)

set(SOURCES
        tests.CommandInterpreter.cpp)

set(INCLUDES .)

add_executable(${NAME} ${SOURCES})
target_include_directories(${NAME} PRIVATE ${INCLUDES})
target_link_libraries(${NAME} PUBLIC CommandInterpreter gtest_main)

include(GoogleTest)
gtest_discover_tests(${NAME})