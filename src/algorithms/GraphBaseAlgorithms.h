#ifndef MINIMUM_COST_FLOWS_PROBLEM_GRAPHBASEALGORITHMS_H
#define MINIMUM_COST_FLOWS_PROBLEM_GRAPHBASEALGORITHMS_H

#include "data_structures/graph/Graph.h"

namespace algorithms {
    /**
     * Class containing the following graph base algorithms:
     * - BFS
     * - DFS
     * - Bellman-Ford
     */
    class GraphBaseAlgorithms {
        public:
            /**
             * BFS algorithm.
             * Breadth-first search (BFS) is an algorithm for traversing
             * or searching tree or graph data structures.
             *
             * @param graph the graph to solve
             * @param source the source node
             * @param sink the sink node
             * @return the path from source to sink
             */
            int BFS(data_structures::Graph graph, int source, int sink);

            /**
             * DFS algorithm
             *
             * @param graph the graph to solve
             * @param source the source node
             * @param sink the sink node
             * @return the path from source to sink
             */
            int DFS(data_structures::Graph graph, int source, int sink);

            /**
             * Bellman-Ford algorithm
             *
             * @param graph the graph to solve
             * @param source the source node
             * @param sink the sink node
             * @return the path from source to sink
             */
            int BellmanFord(data_structures::Graph graph, int source, int sink);

    };
}

#endif //MINIMUM_COST_FLOWS_PROBLEM_GRAPHBASEALGORITHMS_H
