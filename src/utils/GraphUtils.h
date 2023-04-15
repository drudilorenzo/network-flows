#ifndef MINIMUM_COST_FLOWS_PROBLEM_GRAPHUTILS_H
#define MINIMUM_COST_FLOWS_PROBLEM_GRAPHUTILS_H

#include <string>
#include "data_structures/Graph.h"

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
             */
            static data_structures::Graph createGraphFromFile(string file_name);
    };
}

#endif //MINIMUM_COST_FLOWS_PROBLEM_GRAPHUTILS_H
