file(GLOB_RECURSE SERVER_SOURCES "src/*.c")
include_directories(include ${PROJECT_SOURCE_DIR}/common/include)

add_library(server_lib STATIC ${SERVER_SOURCES})
target_link_libraries(server_lib common ws2_32)


