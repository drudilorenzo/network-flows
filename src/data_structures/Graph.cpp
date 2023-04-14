#include <vector>
#include <iostream>
#include "Graph.h"

using namespace std;

namespace data_structures {

    Graph::Graph(int V) :
        num_vertices(V) {
            adj_list = new vector<int>[num_vertices];
    }

    void Graph::AddEdge(int u, int v) {
        adj_list[u].push_back(v);
    }

    void Graph::PrintGraph() {
        for (int u = 0; u < num_vertices; u++) {
            printf("Vertex %d:", u);
            for (auto v : adj_list[u]) {
                printf("-> %d ", v);
            }
            printf("\n");
        }
    }

    bool Graph::operator==(const data_structures::Graph &other) const {
        if (this == &other) {
            return true;
        }
        if (this == nullptr || &other == nullptr) {
            return false;
        }
        if (num_vertices != other.num_vertices) {
            return false;
        }
        for (int u = 0; u < num_vertices; u++) {
            if (adj_list[u].size() != other.adj_list[u].size()) {
                return false;
            }
            for (int i = 0; i < adj_list[u].size(); i++) {
                if (adj_list[u][i] != other.adj_list[u][i]) {
                    return false;
                }
            }
        }
        return true;
    }
}
