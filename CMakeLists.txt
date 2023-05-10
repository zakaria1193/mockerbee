############################################################
# Build types definitions
############################################################
get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

if(isMultiConfig)
# Necessary for multi-configuration generators such as Ninja Multi-Config
  set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
  set(CMAKE_DEFAULT_BUILD_TYPE "Debug")
  message(STATUS "Multi-configuration generator used, append --config <Debug|Release> "
  "to build the desired configuration.")

else()
# Only relevant for Makefile/Ninja generators (And other single-configuration generators)
# Manually set the default build type to Debug
  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
    message(STATUS "Setting build type to 'Debug' as none was specified.")
  endif()
# Print the build type and flags
  message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
endif()

############################################################
# Set compiler, language and flags
# Keep before project() call
############################################################
# Set the C++ standard to use
set(CMAKE_CXX_STANDARD 23)

# Set the clang++ compiler
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_SIZE "/usr/bin/size")

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    -Wall \
    -Wextra \
    -Wno-unused-parameter \
    -Wno-unused-private-field")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS}")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=output.map")

# Colorize output
# Warning: Build specific (clang/gcc), necessary for ninja
# Only works for clang++ calls, not for clang-tidy etc...
set(CMAKE_COLOR_DIAGNOSTICS ON)

# Debugging flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
    -ggdb \
    -fdebug-macro \
    -fparse-all-comments \
    -fno-omit-frame-pointer \
    -fno-optimize-sibling-calls \
    -fsanitize=address,undefined")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

# Release flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} \
    -O2 \
    -march=native \
    -flto")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

# print the compiler flags (including release or debug flags)
message(STATUS "CXX flags: ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}}")
message(STATUS "C flags: ${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE}}")

############################################################
# CMake options
############################################################
cmake_minimum_required(VERSION 3.9)

project(mockerbee VERSION 1.0.0)

# Compile_commands.json generation
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Set to ON to enable verbose output when building
set(CMAKE_VERBOSE_MAKEFILE OFF)

set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})


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
target_link_libraries(mockbee_test_bin
    PRIVATE 
    mockbee_library
)

############################################################
# Post build commands
############################################################

# Generate the .bin
add_custom_command(TARGET mockbee_test_bin POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:mockbee_test_bin> $<TARGET_FILE:mockbee_test_bin>.bin
    COMMENT "Generating .bin"
)

# Print the size
add_custom_command(TARGET mockbee_test_bin POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:mockbee_test_bin>
    COMMENT "Size of the executable"
)

############################################################
# Gen vars for include files
############################################################

file(GLOB_RECURSE
  PRIVATE_INCLUDE_FILES
  "${CMAKE_SOURCE_DIR}/src/include/*"
)

file(GLOB_RECURSE
  PUBLIC_INCLUDE_FILES
  "${CMAKE_SOURCE_DIR}/include/*"
)

############################################################
# Add clang tidy
############################################################

# Add clang-tidy to the project
find_program(CLANG_TIDY_EXE NAMES "clang-tidy-17")

if(CLANG_TIDY_EXE)
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(DO_CLANG_TIDY
      "${CLANG_TIDY_EXE}"
      --use-color # Colorize output
      -p ${CMAKE_BINARY_DIR}/compile_commands.json
      )
    add_custom_target(
        clang-tidy
        COMMAND ${DO_CLANG_TIDY} ${EXECUTABLE_SOURCES} ${LIBRARY_SOURCES}
        WORKING_DIRECTORY ${PROJECT_DIR}
        COMMENT "Running clang-tidy"
        VERBATIM
    )
    add_custom_target(
        clang-tidy-fix
        COMMAND ${DO_CLANG_TIDY} -fix ${EXECUTABLE_SOURCES} ${LIBRARY_SOURCES}
        WORKING_DIRECTORY ${PROJECT_DIR}
        COMMENT "Running clang-tidy fix"
        VERBATIM
    )
else()
    message(STATUS "clang-tidy not found.")
endif()

############################################################
# Add clang format
############################################################

# Add clang-format to the project only if version >= 17
# using --version
find_program(CLANG_FORMAT "clang-format-17")

if(CLANG_FORMAT)
  message(STATUS "clang-format found: ${CLANG_FORMAT}")
  # Add a custom target to run Clang-Format on all relevant files
  file(GLOB_RECURSE FORMAT_FILES
    ${PUBLIC_INCLUDE_FILES}
    ${PRIVATE_INCLUDE_FILES}
    ${EXECUTABLE_SOURCES}
    ${LIBRARY_SOURCES})

  set(CLANG_FORMAT_CONFIG_FILE "${CMAKE_SOURCE_DIR}/.clang-format")
  add_custom_target(clang-format
    COMMAND ${CLANG_FORMAT}
    -style=file # Look for the .clang-format file in the WORKING_DIRECTORY
    -i # In-place editing of the files
    ${FORMAT_FILES} # Files to format
    COMMENT "Running Clang-Format"
    WORKING_DIRECTORY ${PROJECT_DIR}
    VERBATIM
  )
else()
  message(STATUS "clang-format not found.")
endif()

############################################################
# Add cppcheck
############################################################

find_program(CPPCHECK "cppcheck")

if(CPPCHECK)
  message(STATUS "cppcheck found: ${CPPCHECK}")
  # Add a custom target to run Clang-Format on all relevant files
  file(GLOB_RECURSE CPPCHECK_FILES
    ${PUBLIC_INCLUDE_FILES}
    ${PRIVATE_INCLUDE_FILES}
    ${EXECUTABLE_SOURCES}
    ${LIBRARY_SOURCES})

  add_custom_target(cppcheck
    COMMAND ${CPPCHECK}
    --enable=all
    ${CPPCHECK_FILES} # Files to format
    COMMENT "Running cppcheck"
    WORKING_DIRECTORY ${PROJECT_DIR}
  )
else()
  message(STATUS "cppcheck not found.")
endif()
