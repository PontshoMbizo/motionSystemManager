cmake_minimum_required(VERSION 3.10)
project(motion_system_manager C)

set(CMAKE_C_STANDARD 99)

# Add the library
add_library(motion_system_manager_lib STATIC
    src/common/UDP.c
    src/common/processMessage.c
    src/client/client.c
    src/server/server.c
    src/manager/msm.c
)

# Include directories for the library
target_include_directories(motion_system_manager_lib PUBLIC 
    include/common
    include/client
    include/server
    include/manager
)

# Add the main executable
add_executable(motion_system_manager src/main.c)

# Link the static library to the executable
target_link_libraries(motion_system_manager motion_system_manager_lib ws2_32)
