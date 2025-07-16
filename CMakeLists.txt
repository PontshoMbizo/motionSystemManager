cmake_minimum_required(VERSION 3.10)
project(DistributedSystem C)

set(CMAKE_C_STANDARD 99)

# Dependency-aware order
add_subdirectory(common)
add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(manager)


