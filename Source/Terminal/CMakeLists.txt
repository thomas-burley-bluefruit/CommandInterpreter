set(NAME Terminal)

set(SOURCES
        Command.cpp
        Command.h
        CommandInterpreter.cpp
        CommandInterpreter.h
        CommandNames.cpp
        CommandNames.h
        Terminal.cpp
        Terminal.h
        )

set(INCLUDES .)

add_library(${NAME} STATIC ${SOURCES})

target_compile_options(${NAME} PRIVATE ${COMPILE_OPTIONS})
target_compile_definitions(${NAME} PRIVATE ${COMPILE_DEFINITIONS})
target_include_directories(${NAME} PUBLIC ${INCLUDES})
target_link_libraries(${NAME} PUBLIC Interfaces)
