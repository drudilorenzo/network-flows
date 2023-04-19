#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "utils/GraphUtils.h"
#include "algorithms/MaximumFlowAlgorithms.h"
#include "algorithms/MinimumCostFlowAlgorithms.h"
#include "algorithms/GraphBaseAlgorithms.h"

int main(int argc, char **argv) {

    std::string filename;

    // Check if file name was given else ask for it
    if (argc < 2) {
        std::cout << "Insert input file name: ";
        std::cin >> filename;
    } else {
        filename = argv[1];
    }

    // Read graph from file
    try {
        auto graph = utils::GraphUtils::CreateGraphFromJSON(filename);

        std::cout << std::endl;
        std::cout << "What do you want to do?" << std::endl;
        std::cout << "1. Maximum flow (EdmondsKarp)" << std::endl;
        std::cout << "2. Minimum cost flow (Choose algorithm...)" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;
        std::cout << std::endl;

        switch (choice) {
            case 1: {
                int source = 0;
                int sink = graph->GetNumNodes()-1;
                auto result = algorithms::MaximumFlowAlgorithms::EdmondsKarp(graph, source, sink);
                std::cout << "Maximum flow: " << result->getMaxFlow() << std::endl;

                //std::cout << "Graph with flow: " << std::endl;
                // std::cout << result->getGraph()->ToString() << std::endl;
                break;
            }
            case 2: {
                std::cout << std::endl;
                std::cout << "Select the algorithm" << std::endl;
                std::cout << "1. Cycle-cancelling" << std::endl;
                std::cout << "2. Successive shortest path" << std::endl;
                std::cout << "3. Primal-dual" << std::endl;
                std::cout << "4. Exit" << std::endl;
                std::cout << "Enter your choice: ";
                std::cin >> choice;
                std::cout << std::endl;

                int minimum_cost;
                switch (choice) {
                    case 1 : {
                        std::cout << "Cycle-cancelling selected" << std::endl;
                        minimum_cost = algorithms::MinimumCostFlowAlgorithms::CycleCancelling(graph);
                        std::cout << "Minimum cost flow: " << minimum_cost << std::endl;
                        break;
                    }
                    case 2 : {
                        std::cout << "Successive shortest path selected" << std::endl;
                        //minimum_cost = algorithms::MinimumCostFlowAlgorithms::SuccessiveShortestPath(graph);
                        std::cout << "Minimum cost flow: " << minimum_cost << std::endl;
                        break;
                    }
                    case 3 : {
                        std::cout << "Primal-dual selected" << std::endl;
                        //minimum_cost = algorithms::MinimumCostFlowAlgorithms::PrimalDual(graph);
                        std::cout << "Minimum cost flow: " << minimum_cost << std::endl;
                        break;
                    }
                    case 4: {
                        return 0;
                    }
                    default: {
                        std::cout << "ERROR: Invalid choice" << std::endl;
                        return 1;
                    }
                }
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
