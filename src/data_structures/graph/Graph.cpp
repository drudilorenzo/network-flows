#include "Graph.h"

#include <vector>
#include <iostream>

namespace data_structures {

    Graph::Graph(const int V) :
            num_nodes(V) {
            this->adj_list = new vector<Edge>[num_nodes];
    }

    void Graph::AddEdge(Edge e) {
        int head = e.GetHead();
        int tail = e.GetTail();

        // Check if the head of the edge is out of range
        if (head < 0 || head >= this->num_nodes) {
            throw std::invalid_argument("head of the edge is out of range");
        }

        // Check if the tail of the edge is out of range
        if (tail < 0 || tail >= this->num_nodes) {
            throw std::invalid_argument("tail of the edge is out of range");
        }

        this->adj_list[head].push_back(e);
    }

    void Graph::PrintGraph() {
        for (int u = 0; u < this->num_nodes; u++) {
            printf("Vertex %d:\n", u);
            for (auto e : adj_list[u]) {
                e.ToString();
            }
            printf("\n");
        }
    }

    int Graph::GetNumNodes() const {
        return this->num_nodes;
    }

    bool Graph::operator==(const data_structures::Graph &other) const {
        if (this == &other) {
            return true;
        }
        if (this == nullptr || &other == nullptr) {
            return false;
        }
        if (this->num_nodes != other.num_nodes) {
            return false;
        }
        for (int u = 0; u < this->num_nodes; u++) {
            if (this->adj_list[u].size() != other.adj_list[u].size()) {
                return false;
            }
            for (int i = 0; i < this->adj_list[u].size(); i++) {
                if (this->adj_list[u][i] != other.adj_list[u][i]) {
                    return false;
                }
            }
        }
        return true;
    }
}
