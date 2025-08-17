cmake_minimum_required(VERSION 3.10)

# Define the project name
project(CLIProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# List the source files explicitly
set(SOURCES
    main.cpp
    terminal.cpp
    terminal.hpp
    config.hpp

    # Command classes
    CommandClasses/command.hpp
    CommandClasses/command.cpp
    CommandClasses/echocommand.hpp
    CommandClasses/echocommand.cpp
    CommandClasses/timecommand.hpp
    CommandClasses/timecommand.cpp
    CommandClasses/datecommand.hpp
    CommandClasses/datecommand.cpp
    CommandClasses/touchcommand.hpp
    CommandClasses/touchcommand.cpp
    CommandClasses/wccommand.hpp
    CommandClasses/wccommand.cpp
    CommandClasses/exitcommand.hpp
    CommandClasses/exitcommand.cpp
    CommandClasses/batchcommand.hpp
    CommandClasses/batchcommand.cpp
    CommandClasses/headcommand.hpp
    CommandClasses/headcommand.cpp
    CommandClasses/trcommand.hpp
    CommandClasses/trcommand.cpp
    CommandClasses/trunicatecommand.hpp
    CommandClasses/trunicatecommand.cpp
    CommandClasses/promptcommand.hpp
    CommandClasses/promptcommand.cpp
    CommandClasses/rmcommand.hpp
    CommandClasses/rmcommand.cpp

    # Helper classes
    HelperClasses/iohelper.hpp
    HelperClasses/iohelper.cpp

    # Parser classes
    ParserClasses/parser.hpp
    ParserClasses/parser.cpp
    ParserClasses/validitychecker.cpp
    ParserClasses/validitychecker.hpp
    ParserClasses/pipelineparser.hpp
    ParserClasses/pipelineparser.cpp

    # Token classes
    TokenClasses/token.hpp
    TokenClasses/token.cpp
    TokenClasses/argumenttoken.hpp
    TokenClasses/optiontoken.hpp
    TokenClasses/commandtoken.hpp
    TokenClasses/redirecttoken.hpp

    # Stream classes
    StreamClasses/InStream/inputstream.hpp
    StreamClasses/InStream/arginstream.hpp
    StreamClasses/InStream/commandinstream.hpp
    StreamClasses/InStream/commandinstream.cpp
    StreamClasses/InStream/fileinstream.hpp
    StreamClasses/InStream/stdinstream.hpp

    StreamClasses/OutStream/outstream.hpp
    StreamClasses/OutStream/outstream.cpp
    StreamClasses/OutStream/fileoutstream.hpp
    StreamClasses/OutStream/commandoutstream.hpp
    StreamClasses/OutStream/commandoutstream.cpp
    StreamClasses/OutStream/stdoutstream.hpp

    # Exception classes
    ExceptionClasses/exception.hpp
)

# Create an executable from the specified source files
add_executable(CLIProject ${SOURCES})

# Link any libraries if needed (optional)
# target_link_libraries(CLIProject <your-libraries>)
