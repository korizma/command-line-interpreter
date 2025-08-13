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

    # Token classes
    TokenClasses/token.h
    TokenClasses/ArgumentToken.h
    TokenClasses/ArgumentToken.cpp
    TokenClasses/OptionToken.h
    TokenClasses/OptionToken.cpp
    TokenClasses/CommandToken.h
    TokenClasses/CommandToken.cpp
    TokenClasses/RedirectToken.h
    TokenClasses/RedirectToken.cpp

    # Stream classes (if needed)
    StreamClasses/inputstream.h

    # Exception classes
    ExceptionClasses/exception.h

    # Helper classes
    HelperClasses/tokenchecker.h
    HelperClasses/tokenchecker.cpp
)

# Create an executable from the specified source files
add_executable(CLIProject ${SOURCES})

# Link any libraries if needed (optional)
# target_link_libraries(CLIProject <your-libraries>)
