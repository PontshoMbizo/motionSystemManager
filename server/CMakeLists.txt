cmake_minimum_required(VERSION 3.10)
project(server C)

if (WIN32)
    message(STATUS "Building on Windows")
endif()

# Include your local headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files (relative to project root, not parent)
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true src/*.c)

# Create the executable
add_executable(server ${SOURCES})

# Target include paths
target_include_directories(server PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Link Winsock libraries for Windows
if(MSVC OR MINGW)
    target_link_libraries(server ws2_32 mswsock)
endif()

# Set C standard (C99 or C11 recommended)
set_target_properties(server PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED YES
)
