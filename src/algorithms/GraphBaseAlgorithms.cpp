#include "GraphBaseAlgorithms.h"

#include "utils/GraphUtils.h"

#include <queue>
#include <limits>

namespace algorithms {
    bool GraphBaseAlgorithms::BFS(std::shared_ptr<data_structures::Graph> graph, int source, int sink, std::shared_ptr<std::vector<int>> parent) {
        int u {};
        std::queue<int> q {};
        int num_nodes { graph->getNumNodes() };
        bool* visited { new bool[num_nodes] };

        q.push(source);
        visited[source] = true;
        parent->at(source) = -1;

        // Standard BFS loop, with the modification that we exit the loop as soon as we find the sink
        while (!q.empty()) {
            u = q.front();
            q.pop();

            for (auto e : *graph->getNodeAdjList(u)) {

                if (!visited[e.getSink()]) {
                    parent->at(e.getSink()) = u;

                    if (e.getSink() == sink) {
                        delete[] visited;
                        return true;
                    }

                    visited[e.getSink()] = true;
                    q.push(e.getSink());
                }
            }
        }

        // If we reach here, then there is no path from source to sink
        delete[] visited;
        return false;
    }

     std::shared_ptr<dto::BellmanFordResult> GraphBaseAlgorithms::BellmanFord(std::shared_ptr<data_structures::Graph> graph, int source) {
        int num_nodes { graph->getNumNodes() };
        auto dist = std::make_shared<std::vector<int>>(num_nodes);
        auto parent = std::make_shared<std::vector<int>>(num_nodes);

        // Initialize the distance array to infinity and the parent array to -1
        for (int i = 0; i < num_nodes; i++) {
            dist->at(i) = std::numeric_limits<int>::max();
            parent->at(i) = -1;
        }
        dist->at(source) = 0;

        // Relax all edges |V| - 1 times (because the shortest path from source to any other node can have at most |V| - 1 edges)
        for (int i = 0; i < num_nodes - 1; i++) {
            for (int u = 0; u < num_nodes; u++) {
                for (auto e : *graph->getNodeAdjList(u)) {
                    int v = e.getSink();
                    int weight = e.getWeight();

                    // Update dist[v] if dist[u] + weight < dist[v]
                    if (dist->at(u) != std::numeric_limits<int>::max() && dist->at(u) + weight < dist->at(v)) {
                        dist->at(v) = dist->at(u) + weight;
                        parent->at(v) = u;
                    }
                }
            }
        }

        // Check for negative-weight cycles
        for (int u = 0; u < num_nodes; u++) {
            for (auto e : *graph->getNodeAdjList(u)) {
                int v = e.getSink();
                int weight = e.getWeight();

                // Found a negative-weight cycle, get the cycle and return it
                if (dist->at(u) != std::numeric_limits<int>::max() && dist->at(u) + weight < dist->at(v)) {

                    // Result in case a negative-weight cycle was found
                    // It contains the negative-weight cycle
                    return std::make_shared<dto::BellmanFordResult>(utils::GraphUtils::RetrievePath(parent, v));
                }
            }
        }

        // Result in case no negative-weight cycle was found
        // It contains the distance from source to every other node and the parent array
        return std::make_shared<dto::BellmanFordResult>(dist, parent);
    }
}
