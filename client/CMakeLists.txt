file(GLOB_RECURSE CLIENT_SOURCES "src/*.c")
include_directories(include ${PROJECT_SOURCE_DIR}/common/include)

add_library(client_lib STATIC ${CLIENT_SOURCES})
target_link_libraries(client_lib common ws2_32)


