cmake_minimum_required(VERSION 3.5)

project(mockerbee VERSION 1.0.0)

set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

############################################################
# Set compiler options
############################################################
# Set the C++ standard to use
set(CMAKE_CXX_STANDARD 23)

# Set the clang++ compiler
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

# Debugging options
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -g")

# Compile_commands.json generation
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

############################################################
# Create a library
############################################################
set(LIBRARY_SOURCES
    src/clusters/on_off.cpp
    src/clusters/global_commands.cpp
)

#Generate the static library from the library sources
add_library(mockbee_library STATIC 
    ${LIBRARY_SOURCES}
)

target_include_directories(mockbee_library
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)

# Set to ON to enable verbose output when building
set(CMAKE_VERBOSE_MAKEFILE OFF)

############################################################
# Create an executable
############################################################
set(EXECUTABLE_SOURCES
    src/main.cpp
)

# Add an executable with the above sources
add_executable(mockbee_test_bin
    ${EXECUTABLE_SOURCES}
)

# link the new hello_library target with the hello_binary target
target_link_libraries( mockbee_test_bin
    PRIVATE 
        mockbee_library
)


############################################################
# Add clang tidy
############################################################

# Add clang-tidy to the project
find_program(CLANG_TIDY_EXE NAMES "clang-tidy" "clang-tidy-11" "clang-tidy-10" "clang-tidy-9")


if(CLANG_TIDY_EXE)
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=*")
    add_custom_target(
        clang-tidy
        COMMAND ${DO_CLANG_TIDY} ${EXECUTABLE_SOURCES} ${LIBRARY_SOURCES}
        WORKING_DIRECTORY ${PROJECT_DIR}
        COMMENT "Running clang-tidy"
        VERBATIM
    )
endif()
