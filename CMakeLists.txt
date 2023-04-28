cmake_minimum_required(VERSION 3.25)
project(minimum_cost_flows_problem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("src")
file(GLOB minimum_cost_flows_problem_main_SRC ${PROJECT_SOURCE_DIR} "*.h" "*.hpp" "*.cpp")
file(GLOB_RECURSE minimum_cost_flows_problem_src_SRC  "src/*/*.h" "src/*/*.hpp" "src/*/*.cpp")

set(minimum_cost_flows_problem_SRC ${minimum_cost_flows_problem_main_SRC} ${minimum_cost_flows_problem_src_SRC})

add_executable(minimum_cost_flows_problem ${minimum_cost_flows_problem_SRC})

target_compile_options(
    ${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)