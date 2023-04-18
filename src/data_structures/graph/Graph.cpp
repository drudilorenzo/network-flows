#include "Graph.h"

#include <vector>
#include <memory>
#include <stdexcept>
#include <utils/json.hpp>
#include <iostream>
using json = nlohmann::ordered_json;

namespace data_structures {

    Graph::Graph(const int V) :
            num_nodes(V) {
            this->adj_list = std::vector<std::shared_ptr<std::vector<Edge>>>(num_nodes);

            for (int i = 0; i < num_nodes; i++) {
                this->adj_list[i] = std::make_shared<std::vector<Edge>>();
            }
    }

    int Graph::GetNumNodes() const {
        return this->num_nodes;
    }

    std::vector<std::shared_ptr<std::vector<Edge>>> Graph::GetAdjList() const {
        return this->adj_list;
    }

    std::shared_ptr<std::vector<Edge>> Graph::GetNodeAdjList(int i) const {
        if (i < 0 || i >= this->num_nodes) {
            throw std::invalid_argument("node is out of range");
        }
        return this->adj_list.at(i);
    }

    Edge Graph::GetEdge(int u, int v) const {
        for (auto e : *this->adj_list.at(u)) {
            if (e.GetSink() == v) {
                return e;
            }
        }
        throw std::invalid_argument("no edge between u and v");
    }

    void Graph::SetEdgeCapacity(int u, int v, int capacity) {
        for (auto &e : *this->adj_list.at(u)) {
            if (e.GetSink() == v) {
                e.SetCapacity(capacity);
                return;
            }
        }
        throw std::invalid_argument("no edge between u and v");
    }

    void Graph::AddEdge(Edge e) {
        int head = e.GetSource();
        int tail = e.GetSink();

        // Check if the head of the edge is out of range
        if (head < 0 || head >= this->num_nodes) {
            throw std::invalid_argument("head of the edge is out of range");
        }

        // Check if the tail of the edge is out of range
        if (tail < 0 || tail >= this->num_nodes) {
            throw std::invalid_argument("tail of the edge is out of range");
        }

        this->adj_list[head]->push_back(e);
    }

    std::string Graph::ToString() {
        string s = "{";
        s += "\"Num_nodes\": " + std::to_string(this->num_nodes) + ", ";
        s += "\"Edges\": [";
        for (int u = 0; u < this->num_nodes; u++) {
            for (auto e : *this->adj_list.at(u)) {
                s += e.ToString();
                s += ", ";
            }
        }
        // Remove the last comma
        s = s.substr(0, s.size() - 2);
        s += "]}";
        // Beautify the json
        s = json::parse(s).dump(4);
        return s;
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
            if (this->adj_list[u]->size() != other.adj_list[u]->size()) {
                return false;
            }
            for (int i = 0; i < this->adj_list[u]->size(); i++) {
                if (this->adj_list.at(u)->at(i) != other.adj_list.at(u)->at(i)) {
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
