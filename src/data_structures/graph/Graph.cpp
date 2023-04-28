#include "Graph.h"

#include <vector>
#include <memory>
#include <stdexcept>
#include <utils/json.hpp>

using json = nlohmann::ordered_json;

namespace data_structures {

    graph::graph(const int V) :
            num_nodes(V) {
            this->adj_list = std::vector<std::shared_ptr<std::vector<edge>>>(num_nodes);

            for (int i = 0; i < num_nodes; i++) {
                this->adj_list[i] = std::make_shared<std::vector<edge>>();
            }
    }

    int graph::getNumNodes() const {
        return this->num_nodes;
    }

    std::vector<std::shared_ptr<std::vector<edge>>> graph::getAdjList() const {
        return this->adj_list;
    }

    std::shared_ptr<std::vector<edge>> graph::getNodeAdjList(int i) const {
        if (i < 0 || i >= this->num_nodes) {
            throw std::invalid_argument("node is out of range");
        }
        return this->adj_list.at(i);
    }

    bool graph::hasEdge(int source, int tail) const {
        for (auto e : *this->adj_list.at(source)) {
            if (e.getSink() == tail) {
                return true;
            }
        }
        return false;
    }

    edge graph::getEdge(int u, int v) const {
        for (auto e : *this->adj_list.at(u)) {
            if (e.getSink() == v) {
                return e;
            }
        }
        std::string s = "no edge between " + std::to_string(u) + " and " + std::to_string(v);
        throw std::invalid_argument(s);
    }

    void graph::setEdgeCapacity(int u, int v, int capacity) {
        for (auto &e : *this->adj_list.at(u)) {
            if (e.getSink() == v) {
                e.setCapacity(capacity);
                return;
            }
        }
        std::string s = "no edge between " + std::to_string(u) + " and " + std::to_string(v);
        throw std::invalid_argument(s);
    }

    void graph::addEdge(edge e) {
        int head { e.getSource() };
        int tail { e.getSink() };

        // check if the source of the edge is out of range
        if (head < 0 || head >= this->num_nodes) {
            throw std::invalid_argument("source of the edge is out of range");
        }

        // check if the sink of the edge is out of range
        if (tail < 0 || tail >= this->num_nodes) {
            throw std::invalid_argument("sink of the edge is out of range");
        }

        this->adj_list[head]->push_back(e);
    }

    void graph::removeEdge(int source, int sink) {
        auto adj_list = this->getNodeAdjList(source);

        for (unsigned i = 0; i < adj_list->size(); i++) {
            auto e = adj_list->at(i);
            if (e.getSink() == sink) {
                // remove edge
                adj_list->erase(adj_list->begin() + i);
                return;
            }
        }

        std::string s = "no edge between " + std::to_string(source) + " and " + std::to_string(sink);
        throw std::invalid_argument(s);
    }

    std::string graph::toString() {
        std::string s = "{";
        s += "\"Num_nodes\": " + std::to_string(this->num_nodes) + ", ";
        s += "\"Edges\": [";
        for (int u = 0; u < this->num_nodes; u++) {
            for (auto e : *this->adj_list.at(u)) {
                s += e.toString();
                s += ", ";
            }
        }

        // remove the last comma
        s = s.substr(0, s.size() - 2);
        s += "]}";
        
        // beautify the json
        s = json::parse(s).dump(4);
        return s;
    }

    bool graph::operator==(const data_structures::graph &other) const {
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
            for (unsigned i = 0; i < this->adj_list[u]->size(); i++) {
                if (this->adj_list.at(u)->at(i) != other.adj_list.at(u)->at(i)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool graph::operator!=(const data_structures::graph &other) const {
        return !(*this == other);
    }
}
