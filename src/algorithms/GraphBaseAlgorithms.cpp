#include "GraphBaseAlgorithms.h"

#include <queue>

namespace algorithms {
    int GraphBaseAlgorithms::BFS(data_structures::Graph graph, int source, int sink) {
        int u;
        queue<int> q;
        int num_nodes = graph.GetNumNodes();
        bool visited[num_nodes];

        for (int i = 0; i < num_nodes; i++) {
            visited[i] = false;
        }
        visited[source] = true;
        q.push(source);

        while (!q.empty()) {
            u = q.front();
            q.pop();
            for (auto e : graph.GetNodeAdjList(u)) {
                if (!visited[e.GetTail()]) {
                    visited[e.GetTail()] = true;
                    q.push(e.GetTail());
                }
            }
        }
    }

    int GraphBaseAlgorithms::DFS(data_structures::Graph graph, int source, int sink) {

    }

    int GraphBaseAlgorithms::BellmanFord(data_structures::Graph graph, int source, int sink) {

    }
}