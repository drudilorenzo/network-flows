#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

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
        auto graph = utils::GraphUtils::CreateGraphFromJSON(filename);

        std::cout << endl;
        std::cout << "What do you want to do?" << endl;
        std::cout << "1. Maximum flow" << endl;
        std::cout << "2. Minimum cost flow" << endl;
        std::cout << "3. Exit" << endl;
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;
        std::cout << endl;

        switch (choice) {
            case 1: {
                int source = 0;
                int sink = 5;
                auto result = algorithms::MaximumFlowAlgorithms::EdmondsKarp(graph, source, sink);

                std::cout << "Maximum flow: " << result->getMaxFlow() << std::endl;

                std::cout << "Graph with flow: " << std::endl;
                std::cout << result->getGraph()->ToString() << std::endl;
                break;
            }
            case 2: {
                std::cout << "Minimum cost flow: " << std::endl;
                break;
            }
            case 3: {
                return 0;
            }
            default: {
                std::cout << "ERROR: Invalid choice" << std::endl;
                return 1;
            }
        }
    } catch (std::invalid_argument& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
