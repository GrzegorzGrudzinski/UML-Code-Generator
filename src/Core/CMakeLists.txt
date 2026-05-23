file(GLOB_RECURSE CORE_SOURCES "*.cpp" "*.hpp")

add_library(CoreLib STATIC ${CORE_SOURCES})

target_include_directories(CoreLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})