cmake_minimum_required(VERSION 3.25)
project(minimum_cost_flows_problem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("src")

add_executable(minimum_cost_flows_problem main.cpp src/data_structures/graph/Graph.cpp src/data_structures/graph/Graph.h src/utils/GraphUtils.cpp src/utils/GraphUtils.h src/consts/Consts.h src/algorithms/MinimumCostFlowAlgorithms.cpp src/algorithms/MinimumCostFlowAlgorithms.h src/algorithms/GraphBaseAlgorithms.cpp src/algorithms/GraphBaseAlgorithms.h src/algorithms/MaximumFlowAlgorithms.cpp src/algorithms/MaximumFlowAlgorithms.h src/data_structures/graph/Edge.cpp src/data_structures/graph/Edge.h src/dto/BellmanFord/BellmanFordResult.cpp src/dto/BellmanFord/BellmanFordResult.h src/dto/EdmondsKarp/EdmondsKarpResult.cpp src/dto/EdmondsKarp/EdmondsKarpResult.h src/utils/json.hpp)

target_compile_options(
    ${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)