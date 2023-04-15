#include "Graph.h"

#include <vector>
#include <iostream>

namespace data_structures {

    Graph::Graph(const int V) :
        num_vertices(V) {
            this->adj_list = new vector<Edge>[num_vertices];
    }

    void Graph::AddEdge(Edge e) {
        int head = e.GetHead();
        int tail = e.GetTail();

        // Check if the head of the edge is out of range
        if (head < 0 || head >= this->num_vertices) {
            throw std::invalid_argument("head of the edge is out of range");
        }

        // Check if the tail of the edge is out of range
        if (tail < 0 || tail >= this->num_vertices) {
            throw std::invalid_argument("tail of the edge is out of range");
        }

        this->adj_list[head].push_back(e);
    }

    void Graph::PrintGraph() {
        for (int u = 0; u < this->num_vertices; u++) {
            printf("Vertex %d:\n", u);
            for (auto e : adj_list[u]) {
                e.ToString();
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
