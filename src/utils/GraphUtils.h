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
             * Create graph from file and return it.
             * (See example.txt to see how to format the file)
             *
             * @param file_name name of the file to read
             * @return (data_structure::Graph) graph created from the file inputs
             * @throws invalid_argument if the file does not exist
             * @throws invalid_argument if the file is not formatted correctly
             */
            static data_structures::Graph CreateGraphFromFile(string file_name);

            /**
             * Get the residual graph of the given graph.
             *
             * (see https://www.hackerearth.com/practice/algorithms/graphs/maximum-flow/tutorial/)
             *
             * @param graph the graph to get the residual graph from
             * @return (data_structure::Graph) the residual graph
             */
            static data_structures::Graph GetResidualGraph(data_structures::Graph graph);
    };
}

#endif //MINIMUM_COST_FLOWS_PROBLEM_GRAPHUTILS_H
