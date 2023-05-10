#include "GraphBaseAlgorithms.h"

#include "consts/Consts.h"
#include "utils/GraphUtils.h"

#include <set>
#include <queue>
#include <vector>
#include <memory>
#include <limits>

namespace algorithms {
    std::shared_ptr<dto::BfsResult> GraphBaseAlgorithms::BFS(const std::shared_ptr<data_structures::Graph>& graph, int source, int sink) {
        int num_nodes { graph->getNumNodes() };
        auto parent = std::make_shared<std::vector<int>>(num_nodes);

        std::vector<bool> visited(num_nodes, false);
        visited.at(source) = true;
        
        std::queue<int> q {};
        q.push(source);
        parent->at(source) = consts::source_parent;

        // Standard BFS loop, with the modification that we exit the loop as soon as we find the sink
        while (!q.empty()) {
            int current_node { q.front() };
            q.pop();

            for (auto e : *graph->getNodeAdjList(current_node)) {

                if (!visited.at(e.getSink())) {
                    parent->at(e.getSink()) = current_node;

                    if (e.getSink() == sink) {
                        return std::make_shared<dto::BfsResult>(true, parent);
                    }

                    visited.at(e.getSink()) = true;
                    q.push(e.getSink());
                }
            }
        }

        // If we reach here, then there is no path from source to sink
        return std::make_shared<dto::BfsResult>(false, parent);
    }

     std::shared_ptr<dto::BellmanFordResult> GraphBaseAlgorithms::BellmanFord(const std::shared_ptr<data_structures::Graph>& graph, int source) {
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
            for (int node = 0; node < num_nodes; node++) {
                for (auto e : *graph->getNodeAdjList(node)) {
                    int sink { e.getSink() };
                    int cost { e.getCost() };

                    // Update dist[v] if dist[u] + weight < dist[v]
                    if (dist->at(node) != std::numeric_limits<int>::max() && dist->at(node) + cost < dist->at(sink)) {
                        dist->at(sink) = dist->at(node) + cost;
                        parent->at(sink) = node;
                    }
                }
            }
        }

        // Check for negative-cost cycles
        for (int node = 0; node < num_nodes; node++) {
            for (auto e : *graph->getNodeAdjList(node)) {
                int sink { e.getSink() };
                int cost { e.getCost() };

                // Found a negative-weight cycle, get the cycle and return it
                if (dist->at(node) != std::numeric_limits<int>::max() && dist->at(node) + cost < dist->at(sink)) {

                    // Result in case a negative-weight cycle was found
                    // It contains the negative-weight cycle
                    return std::make_shared<dto::BellmanFordResult>(utils::GraphUtils::RetrievePath(parent, consts::source_parent, sink));
                }
            }
        }

        // Result in case no negative-weight cycle was found
        // It contains the distance from source to every other node and the parent array
        return std::make_shared<dto::BellmanFordResult>(dist, parent);
    }

    std::shared_ptr<dto::DijkstraResult> GraphBaseAlgorithms::Dijkstra(const std::shared_ptr<data_structures::Graph>& graph, int source) {
        int num_nodes { graph->getNumNodes() };

        auto dist = std::make_shared<std::vector<int>>(num_nodes);
        auto parent = std::make_shared<std::vector<int>>(num_nodes);
        std::vector<int> q {};    // q contains all the nodes that have not been visited yet
        std::set<int> visited {}; // visited contains all the nodes that have been visited

        // Initialize the distance array to infinity and the parent array to -1
        for (int i = 0; i < num_nodes; i++) {
            dist->at(i) = std::numeric_limits<int>::max();
            parent->at(i) = -1;
            q.push_back(i);
        }
        
        // Set source distance and parent
        dist->at(source) = 0;
        parent->at(source) = consts::source_parent;

        while (!q.empty()) {

            // Find the node with the minimum distance
            int min_dist { std::numeric_limits<int>::max() };
            int current_node { -1 };  // node
            int current_index { -1 }; // node index
            for (unsigned i=0; i < q.size(); i++) {
                int node { q.at(i) };
                if (dist->at(node) < min_dist) {
                    min_dist = dist->at(node);
                    current_node = node;
                    current_index = i;
                }
            }

            // remove the node from the queue
            q.erase(q.begin() + current_index);

            // Mark the node as visited
            visited.insert(current_node);

            // Relax all edges going out of the current node
            for (auto e : *graph->getNodeAdjList(current_node)) {
                int sink { e.getSink() };
                int cost { e.getCost() };

                // Update dist[v] if dist[u] + weight < dist[v]
                if (dist->at(current_node) != std::numeric_limits<int>::max() && dist->at(current_node) + cost < dist->at(sink)) {
                    dist->at(sink) = dist->at(current_node) + cost;
                    parent->at(sink) = current_node;
                }
            }
        }

        return std::make_shared<dto::DijkstraResult>(dist, parent);
    }
}
