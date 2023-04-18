#ifndef MINIMUM_COST_FLOWS_PROBLEM_GRAPHUTILS_H
#define MINIMUM_COST_FLOWS_PROBLEM_GRAPHUTILS_H

#include <string>
#include "data_structures/graph/Graph.h"

using namespace std;

namespace  utils {
    /**
     * Graph's utility function
     */
    class GraphUtils {
        public:
            /**
             * Create graph from json and return it.
             * (See graph.json to see how to format the file)
             *
             * @param file_name name of the file to read
             * @return graph created from the file inputs
             * @throws invalid_argument if the file does not exist
             * @throws invalid_argument if the json is not formatted correctly
             */
            static std::shared_ptr<data_structures::Graph> CreateGraphFromJSON(string file_name);

            /**
             * Get the residual graph of the given graph.
             *
             * (see https://www.hackerearth.com/practice/algorithms/graphs/maximum-flow/tutorial/)
             *
             * @param graph the graph to get the residual graph from
             * @return the residual graph
             */
            static std::shared_ptr<data_structures::Graph> GetResidualGraph(std::shared_ptr<data_structures::Graph> graph);

            /**
             * Get the optimal graph of the given graph.
             *
             * (see https://www.hackerearth.com/practice/algorithms/graphs/maximum-flow/tutorial/)
             *
             * @param graph the graph to get the optimal graph from
             * @return the optimal graph
             */
            static std::shared_ptr<data_structures::Graph> GetOptimalGraph(std::shared_ptr<data_structures::Graph> graph);

            /**
             * Retrieve the path from the node to the source (node with -1 as parent).
             *
             * @param parent
             * @param node
             * @return the path from node to the source node
             */
            static shared_ptr<vector<int>> RetrievePath(shared_ptr<vector<int>> parent, int node);
    };
}

#endif //MINIMUM_COST_FLOWS_PROBLEM_GRAPHUTILS_H
