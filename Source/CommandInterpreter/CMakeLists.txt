set(NAME CommandInterpreter)

set(SOURCES
        Command.cpp
        Command.h        
        CommandInterpreter.cpp
        CommandInterpreter.h
        CommandNames.h
        )

set(INCLUDES .)

add_library(${NAME} STATIC ${SOURCES})

target_compile_options(${NAME} PRIVATE ${COMPILE_OPTIONS})
target_compile_definitions(${NAME} PRIVATE ${COMPILE_DEFINITIONS})
target_include_directories(${NAME} PUBLIC ${INCLUDES})
