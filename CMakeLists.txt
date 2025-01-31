

cmake_minimum_required(VERSION 3.13)

# Project information
project(shell VERSION 1.0 LANGUAGES CXX)

# C++ standard requirement
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect source and header files recursively
file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.h src/*.hpp)

# Add executable target
# add_executable(shell ${SOURCE_FILES})

add_executable(shell
    src/main.cpp
    src/builtins/builtins.cpp
    src/utils/path_utils.cpp
    src/parser/argument_parser.cpp
    src/core/command_handler.cpp
)

# Include directories for headers (optional, but explicit)
target_include_directories(shell PRIVATE src)

# Platform-specific options (optional)
if(WIN32)
    target_compile_definitions(shell PRIVATE WINDOWS)
elseif(UNIX)
    target_compile_definitions(shell PRIVATE UNIX)
endif()

# Link any additional libraries here (if needed in the future)
# target_link_libraries(shell PRIVATE <library-name>)
