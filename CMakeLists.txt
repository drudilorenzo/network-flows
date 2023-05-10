cmake_minimum_required(VERSION 3.20)
project(network_flows)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("src")
file(GLOB network_flows_main_SRC ${PROJECT_SOURCE_DIR} "*.h" "*.hpp" "*.cpp")
file(GLOB_RECURSE network_flows_src_SRC  "src/*/*.h" "src/*/*.hpp" "src/*/*.cpp")

set(network_flows_SRC ${network_flows_main_SRC} ${network_flows_src_SRC})

add_executable(network_flows ${network_flows_SRC})

target_compile_options(
    ${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)