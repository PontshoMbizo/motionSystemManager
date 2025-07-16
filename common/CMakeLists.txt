file(GLOB_RECURSE COMMON_SOURCES "src/*.c")
include_directories(include)

add_library(common STATIC ${COMMON_SOURCES})
target_link_libraries(common ws2_32)
