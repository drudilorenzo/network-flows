#include "GraphBaseAlgorithms.h"

#include <queue>
#include <cstring>
#include <limits>

#include "utils/GraphUtils.h"

namespace algorithms {
    bool GraphBaseAlgorithms::BFS(std::shared_ptr<data_structures::Graph> graph, int source, int sink, std::shared_ptr<std::vector<int>> parent) {
        int u;
        queue<int> q;
        int num_nodes = graph->GetNumNodes();
        bool visited[num_nodes];

        memset(visited, false, sizeof(visited));
        q.push(source);
        visited[source] = true;
        parent->at(source) = -1;

        while (!q.empty()) {
            u = q.front();
            q.pop();
            for (auto e : *graph->GetNodeAdjList(u)) {
                if (!visited[e.GetTail()] && e.GetCapacity() > 0) {
                    parent->at(e.GetTail()) = u;
                    if (e.GetTail() == sink) {
                        return true;
                    }
                    visited[e.GetTail()] = true;
                    q.push(e.GetTail());
                }
            }
        }
        return false;
    }

     shared_ptr<dto::BellmanFordResult> GraphBaseAlgorithms::BellmanFord(std::shared_ptr<data_structures::Graph> graph, int source) {
        int num_nodes = graph->GetNumNodes();
        auto dist = std::make_shared<std::vector<int>>(num_nodes);
        auto parent = std::make_shared<std::vector<int>>(num_nodes);

        // Initialize the distance array to infinity and the parent array to -1
        for (int i = 0; i < num_nodes; i++) {
            dist->at(i) = numeric_limits<int>::max();
            parent->at(i) = -1;
        }
        dist->at(source) = 0;

        // Relax all edges |V| - 1 times (because the shortest path from source to any other node can have at most |V| - 1 edges)
        for (int i = 0; i < num_nodes - 1; i++) {
            for (int u = 0; u < num_nodes; u++) {
                for (auto e : *graph->GetNodeAdjList(u)) {
                    int v = e.GetTail();
                    int weight = e.GetWeight();
                    if (dist->at(u) != numeric_limits<int>::max() && dist->at(u) + weight < dist->at(v)) {
                        dist->at(v) = dist->at(u) + weight;
                        parent->at(v) = u;
                    }
                }
            }
        }

        // Check for negative-weight cycles
        for (int u = 0; u < num_nodes; u++) {
            for (auto e : *graph->GetNodeAdjList(u)) {
                int v = e.GetTail();
                int weight = e.GetWeight();

                // Found a negative-weight cycle, get the cycle and return it
                if (dist->at(u) != numeric_limits<int>::max() && dist->at(u) + weight < dist->at(v)) {
                    return make_shared<dto::BellmanFordResult>(utils::GraphUtils::RetrievePath(parent, v));
                }
            }
        }

        // Result in case no negative-weight cycle was found
        return make_shared<dto::BellmanFordResult>(dist, parent);
    }
}
