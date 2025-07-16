file(GLOB_RECURSE MANAGER_SOURCES "src/*.c")
include_directories(include ${PROJECT_SOURCE_DIR}/common/include ${PROJECT_SOURCE_DIR}/client/include ${PROJECT_SOURCE_DIR}/server/include)

add_executable(manager ${MANAGER_SOURCES})

# Link manager to libraries
target_link_libraries(manager common client_lib server_lib ws2_32)
