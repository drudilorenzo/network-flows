#include <iostream>

#include "data_structures/graph/Graph.h"
#include "utils/GraphUtils.h"
#include "algorithms/MaximumFlowAlgorithms.h"

int main(int argc, char **argv) {

    // Check if file name was given
    if (argc < 2) {
        std::cout << "ERROR: No file name given" << std::endl;
        return 1;
    }
    const string filename = argv[1];

    // Read graph from file
    try {
        data_structures::Graph graph = utils::GraphUtils::CreateGraphFromFile(filename);
        graph.PrintGraph();

        int source = 0;
        int sink = 5;
        int max_flow = algorithms::MaximumFlowAlgorithms::EdmondsKarp(graph, source, sink);

        std::cout << "Max flow: " << max_flow << std::endl;
    } catch (std::invalid_argument& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
