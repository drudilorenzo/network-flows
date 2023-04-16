#include "GraphBaseAlgorithms.h"

#include <queue>
#include <cstring>

namespace algorithms {
    bool GraphBaseAlgorithms::BFS(data_structures::Graph graph, int source, int sink, int parent[]) {
        int u;
        queue<int> q;
        int num_nodes = graph.GetNumNodes();
        bool visited[num_nodes];



        memset(visited, false, sizeof(visited));
        q.push(source);
        visited[source] = true;
        parent[source] = -1;

        while (!q.empty()) {
            u = q.front();
            q.pop();
            for (auto e : graph.GetNodeAdjList(u)) {
                if (!visited[e.GetTail()] && e.GetCapacity() > 0) {
                    parent[e.GetTail()] = u;
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

    int GraphBaseAlgorithms::DFS(data_structures::Graph graph, int source, int sink) {

    }

    int GraphBaseAlgorithms::BellmanFord(data_structures::Graph graph, int source, int sink) {

    }
}