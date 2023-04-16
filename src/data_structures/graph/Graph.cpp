#include "Graph.h"

#include <vector>
#include <iostream>

namespace data_structures {

    Graph::Graph(const int V) :
            num_nodes(V) {
            this->adj_list = new vector<Edge>[num_nodes];
    }

    int Graph::GetNumNodes() const {
        return this->num_nodes;
    }

    vector<Edge> *Graph::GetAdjList() const {
        return this->adj_list;
    }

    vector<Edge> Graph::GetNodeAdjList(int i) const {
        if (i < 0 || i >= this->num_nodes) {
            throw std::invalid_argument("node is out of range");
        }
        return this->adj_list[i];
    }

    Edge Graph::GetEdge(int u, int v) const {
        for (auto e : this->adj_list[u]) {
            if (e.GetTail() == v) {
                return e;
            }
        }
        throw std::invalid_argument("no edge between u and v");
    }

    void Graph::SetEdgeCapacity(int u, int v, int capacity) {
        for (auto &e : this->adj_list[u]) {
            if (e.GetTail() == v) {
                e.SetCapacity(capacity);
                return;
            }
        }
        throw std::invalid_argument("no edge between u and v");
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

    bool Graph::operator!=(const data_structures::Graph &other) const {
        return !(*this == other);
    }
}
