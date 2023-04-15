cmake_minimum_required(VERSION 3.25)
project(minimum_cost_flows_problem)

set(CMAKE_CXX_STANDARD 17)
include_directories("src")
add_executable(minimum_cost_flows_problem main.cpp src/data_structures/Graph.cpp src/data_structures/Graph.h src/utils/GraphUtils.cpp src/utils/GraphUtils.h src/consts/Consts.h src/algorithms/MinimumCostFlowAlgorithms.cpp src/algorithms/MinimumCostFlowAlgorithms.h src/algorithms/GraphBaseAlgorithms.cpp src/algorithms/GraphBaseAlgorithms.h src/algorithms/MaximumFlowAlgorithms.cpp src/algorithms/MaximumFlowAlgorithms.h src/data_structures/Edge.cpp src/data_structures/Edge.h)
