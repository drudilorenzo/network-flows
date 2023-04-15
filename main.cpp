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

    // Read graph from file
    try {
        data_structures::Graph g = utils::GraphUtils::createGraphFromFile(filename);
        g.PrintGraph();
    } catch (std::invalid_argument& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
