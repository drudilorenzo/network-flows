#ifndef MINIMUM_COST_FLOWS_PROBLEM_GRAPHBASEALGORITHMS_H
#define MINIMUM_COST_FLOWS_PROBLEM_GRAPHBASEALGORITHMS_H

#include "data_structures/graph/Graph.h"
#include "dto/BellmanFord/BellmanFordResult.h"

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
         * @return the path from source to sink
         */
        static bool BFS(std::shared_ptr<data_structures::Graph> graph, int source, int sink, std::shared_ptr<vector<int>> parent);

        /**
         * Bellman-Ford algorithm used to detect negative cycles.
         * Bellman-Ford algorithm is an algorithm that computes shortest paths from a single source vertex.
         * In this specific case we use Bellman-Ford just to find negative cycles.
         *
         * (see https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm)
         *
         * @param graph the graph to solve
         * @param source the source node
         * @return the result of the algorithm (see BellmanFordResult.h
         */
        static shared_ptr<dto::BellmanFordResult> BellmanFord(std::shared_ptr<data_structures::Graph> graph, int source);
    };
}

#endif //MINIMUM_COST_FLOWS_PROBLEM_GRAPHBASEALGORITHMS_H
