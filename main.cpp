#include <iostream>

#include "data_structures/Graph.h"
#include "utils/GraphUtils.h"
#include "consts/Consts.h"

int main(int argc, char **argv) {

    // Check if file name was given
    if (argc < 2) {
        std::cout << "ERROR: No file name given" << std::endl;
        return 1;
    }
    const string filename = argv[1];
    data_structures::Graph g = utils::GraphUtils::createGraphFromFile(filename);

    if (g == EMPTY_GRAPH) {
        return 1;
    }

    g.PrintGraph();

    return 0;
}
