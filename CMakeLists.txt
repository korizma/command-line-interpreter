cmake_minimum_required(VERSION 3.10)

# Define the project name
project(CLIProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# List the source files explicitly
set(SOURCES
    main.cpp
    terminal.cpp
    terminal.h
    config.h

    # Command classes
    CommandClasses/command.h
    CommandClasses/command.cpp
    CommandClasses/echocommand.h
    CommandClasses/echocommand.cpp
    CommandClasses/timecommand.h
    CommandClasses/timecommand.cpp
    CommandClasses/datecommand.h
    CommandClasses/datecommand.cpp
    CommandClasses/touchcommand.h
    CommandClasses/touchcommand.cpp
    CommandClasses/wccommand.h
    CommandClasses/wccommand.cpp
    CommandClasses/exitcommand.h
    CommandClasses/exitcommand.cpp
    CommandClasses/batchcommand.h
    CommandClasses/batchcommand.cpp
    CommandClasses/headcommand.h
    CommandClasses/headcommand.cpp
    CommandClasses/trcommand.h
    CommandClasses/trcommand.cpp
    CommandClasses/trunicatecommand.h
    CommandClasses/trunicatecommand.cpp
    CommandClasses/promptcommand.h
    CommandClasses/promptcommand.cpp
    CommandClasses/rmcommand.h
    CommandClasses/rmcommand.cpp

    # Helper classes
    HelperClasses/iohelper.h
    HelperClasses/iohelper.cpp

    # Parser classes
    ParserClasses/parser.h
    ParserClasses/parser.cpp
    ParserClasses/validitychecker.cpp
    ParserClasses/validitychecker.h

    # Token classes
    TokenClasses/token.h
    TokenClasses/token.cpp
    TokenClasses/argumenttoken.h
    TokenClasses/optiontoken.h
    TokenClasses/commandtoken.h
    TokenClasses/redirecttoken.h

    # Stream classes
    StreamClasses/InStream/inputstream.h
    StreamClasses/InStream/arginstream.h
    StreamClasses/InStream/commandinstream.h
    StreamClasses/InStream/commandinstream.cpp
    StreamClasses/InStream/fileinstream.h
    StreamClasses/InStream/stdinstream.h

    StreamClasses/OutStream/outstream.h
    StreamClasses/OutStream/outstream.cpp
    StreamClasses/OutStream/fileoutstream.h
    StreamClasses/OutStream/commandoutstream.h
    StreamClasses/OutStream/commandoutstream.cpp
    StreamClasses/OutStream/stdoutstream.h

    # Exception classes
    ExceptionClasses/exception.h
)

# Create an executable from the specified source files
add_executable(CLIProject ${SOURCES})

# Link any libraries if needed (optional)
# target_link_libraries(CLIProject <your-libraries>)
