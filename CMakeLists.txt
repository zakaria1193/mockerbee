cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 23)  # set the C++ standard to use
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")  # set the path to the clang++ compiler


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -g")

# CMAKE_EXPORT_COMPILE_COMMANDS
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)


project(hello_library)

############################################################
# Create a library
############################################################

#Generate the static library from the library sources
add_library(mockbee_library STATIC 
    src/clusters/on_off.cpp
    src/clusters/global_commands.cpp
)

target_include_directories(mockbee_library
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)

set(CMAKE_VERBOSE_MAKEFILE ON)

############################################################
# Create an executable
############################################################

# Add an executable with the above sources
add_executable(mockbee_test_bin
    src/main.cpp
)

# link the new hello_library target with the hello_binary target
target_link_libraries( mockbee_test_bin
    PRIVATE 
        mockbee_library
)
