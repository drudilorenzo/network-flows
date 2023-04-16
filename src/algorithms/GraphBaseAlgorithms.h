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
             * Return the path (the edges traversed) from source to sink.
             *
             * https://en.wikipedia.org/wiki/Breadth-first_search
             *
             * @param graph the graph to solve
             * @param source the source node
             * @param sink the sink node
             * @param parent the parent of each node (used to reconstruct the path)
             * @return (vector<Edge>) the path from source to sink
             */
            static bool BFS(data_structures::Graph graph, int source, int sink, int parent[]);

            /**
             * DFS algorithm
             *
             * @param graph the graph to solve
             * @param source the source node
             * @param sink the sink node
             * @return the path from source to sink
             */
            static int DFS(data_structures::Graph graph, int source, int sink);

            /**
             * Bellman-Ford algorithm
             *
             * @param graph the graph to solve
             * @param source the source node
             * @param sink the sink node
             * @return the path from source to sink
             */
            static int BellmanFord(data_structures::Graph graph, int source, int sink);
    };
}

#endif //MINIMUM_COST_FLOWS_PROBLEM_GRAPHBASEALGORITHMS_H
