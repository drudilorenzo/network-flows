#include "Graph.h"

#include <vector>
#include <memory>
#include <stdexcept>
#include <utils/json.hpp>

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

    bool Graph::HasEdge(int source, int tail) const {
        for (auto e : *this->adj_list.at(source)) {
            if (e.GetSink() == tail) {
                return true;
            }
        }
        return false;
    }

    Edge Graph::GetEdge(int u, int v) const {
        for (auto e : *this->adj_list.at(u)) {
            if (e.GetSink() == v) {
                return e;
            }
        }
        std::string s = "no edge between " + std::to_string(u) + " and " + std::to_string(v);
        throw std::invalid_argument(s);
    }

    void Graph::SetEdgeCapacity(int u, int v, int capacity) {
        for (auto &e : *this->adj_list.at(u)) {
            if (e.GetSink() == v) {
                e.SetCapacity(capacity);
                return;
            }
        }
        std::string s = "no edge between " + std::to_string(u) + " and " + std::to_string(v);
        throw std::invalid_argument(s);
    }

    void Graph::AddEdge(Edge e) {
        int head = e.GetSource();
        int tail = e.GetSink();

        // Check if the source of the edge is out of range
        if (head < 0 || head >= this->num_nodes) {
            throw std::invalid_argument("source of the edge is out of range");
        }

        // Check if the sink of the edge is out of range
        if (tail < 0 || tail >= this->num_nodes) {
            throw std::invalid_argument("sink of the edge is out of range");
        }

        this->adj_list[head]->push_back(e);
    }

    void Graph::RemoveEdge(int source, int sink) {
        auto adj_list = this->GetNodeAdjList(source);
        for (int i = 0; i < adj_list->size(); i++) {
            auto e = adj_list->at(i);
            if (e.GetSink() == sink) {
                // remove edge
                adj_list->erase(adj_list->begin() + i);
                return;
            }
        }
        std::string s = "no edge between " + std::to_string(source) + " and " + std::to_string(sink);
        throw std::invalid_argument(s);    }

    std::string Graph::ToString() {
        std::string s = "{";
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
