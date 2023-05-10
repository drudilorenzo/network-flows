#include <iostream>

#include "utils/GraphUtils.h"
#include "algorithms/MaximumFlowAlgorithms.h"
#include "algorithms/MinimumCostFlowAlgorithms.h"

int main(int argc, char **argv) {

    std::string filename {};

    // Check if file name was given else ask for it
    if (argc < 2) {
        // Filename must be with extension and without spaces
        // If the file is not in the same directory as the executable, the full path must be given
        std::cout << "Insert input filename: ";
        std::cin >> filename;
    } else {
        filename = argv[1];
    }

    try {
        // read graph from file
        auto graph = utils::GraphUtils::CreateGraphFromJSON(filename);

        std::cout << "Select the network flow problem:" << std::endl;
        std::cout << "1. Maximum flow (EdmondsKarp)" << std::endl;
        std::cout << "2. Minimum cost flow (Choose algorithm...)" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        int choice {};
        std::cin >> choice;
        std::cout << std::endl;

        // for semplicity we assume that the source is the first node and the sink is the last node
        int source {};
        int sink { graph->getNumNodes() - 1 };
        std::shared_ptr<dto::FlowResult> result;

        switch (choice) {
            case 1: {
                result = algorithms::MaximumFlowAlgorithms::EdmondsKarp(graph, source, sink);
                std::cout << "Graph with flow: " << std::endl;
                auto opt_graph = utils::GraphUtils::GetOptimalGraphFromNegativeWeights(result->getGraph(), graph);
                std::cout << opt_graph->toString() << std::endl;
                std::cout << "Maximum flow: " << result->getFlow() << std::endl << std::endl;
                break;
            }
            case 2: {
                std::cout << "Select the algorithm:" << std::endl;
                std::cout << "1. Cycle-cancelling" << std::endl;
                std::cout << "2. Successive shortest path" << std::endl;
                std::cout << "3. Primal-dual" << std::endl;
                std::cout << "4. Exit" << std::endl;
                std::cout << "Enter your choice: ";
                std::cin >> choice;
                std::cout << std::endl;

                int minimum_cost {};
                switch (choice) {
                    case 1 : {
                        std::cout << "Cycle-cancelling selected!" << std::endl;
                        result = algorithms::MinimumCostFlowAlgorithms::CycleCancelling(graph, source, sink);
                        break;
                    }
                    case 2 : {
                        std::cout << "Successive shortest path selected!" << std::endl;
                        result = algorithms::MinimumCostFlowAlgorithms::SuccessiveShortestPath(graph, source, sink);
                        break;
                    }
                    case 3 : {
                        std::cout << "Primal-dual selected!" << std::endl;
                        //minimum_cost = algorithms::MinimumCostFlowAlgorithms::PrimalDual(graph);
                        std::cout << "Minimum cost flow: " << minimum_cost << std::endl;
                        break;
                    }
                    case 4: {
                        break;
                    }
                    default: {
                        throw std::invalid_argument("Invalid choice!");
                    }
                }
                std::cout << "Graph with flow: " << std::endl;
                std::cout << result->getGraph()->toString() << std::endl;
                std::cout << "Minimum cost flow: " << result->getFlow() << std::endl << std::endl;
                break;
            }
            case 3: {
                break;
            }
            default: {
                throw std::invalid_argument("Invalid choice");
            }
        }
    } catch (std::invalid_argument& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "EXIT" << std::endl;
    return EXIT_SUCCESS;
}
