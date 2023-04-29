#include "Graph.h"

#include <stdexcept>
#include <utils/json.hpp>

using json = nlohmann::ordered_json;

namespace data_structures {

    Graph::Graph(int num_nodes) 
        : num_nodes(num_nodes) {
        this->g = std::make_shared<std::map<int, std::shared_ptr<std::vector<Edge>>>>();

        // insert the nodes
        for (int node = 0; node < num_nodes; node++) {
            this->g->insert({node, std::make_shared<std::vector<Edge>>()});
        }
    }

    int Graph::getStartingNumNodes() const {
        return this->num_nodes;
    }

    int Graph::getNumNodes() const {
        return static_cast<int>(this->g->size());
    }

    [[maybe_unused]] std::shared_ptr<std::map<int, std::shared_ptr<std::vector<Edge>>>> Graph::getGraph() const {
        return this->g;
    }

    std::shared_ptr<std::vector<Edge>> Graph::getNodeAdjList(int node) const {
        Graph::checkNodeExistence(node);

        return this->g->at(node);
    }

    bool Graph::hasEdge(int source, int sink) const {
        Graph::checkNodeExistence(source);
        Graph::checkNodeExistence(sink);

        return std::any_of(this->g->at(source)->begin(), this->g->at(source)->end(), [sink](Edge e) {
            return e.getSink() == sink;
        });
    }

    Edge Graph::getEdge(int source, int sink) const {
        Graph::checkNodeExistence(source);
        Graph::checkNodeExistence(sink);

        for (auto e : *this->g->at(source)) {
            if (e.getSink() == sink) {
                return e;
            }
        }

        throw std::invalid_argument(data_structures::Graph::getNoEdgeString(source, sink));
    }

    void Graph::setEdgeCapacity(int source, int sink, int capacity) {
        Graph::checkNodeExistence(source);
        Graph::checkNodeExistence(sink);

        Graph::checkNegativeCapacity(capacity);

        for (auto &e : *this->g->at(source)) {
            if (e.getSink() == sink) {
                e.setCapacity(capacity);
                return;
            }
        }

        throw std::invalid_argument(data_structures::Graph::getNoEdgeString(source, sink));
    }

    void Graph::addEdge(Edge e) {
        int source { e.getSource() };
        int sink { e.getSink() };

        // check if the source of the edge is out of range
        if (source < 0 || sink < 0) {
            std::string s = "nodes must be positive integers";
            throw std::invalid_argument(s);
        }

        Graph::checkNegativeCapacity(e.getCapacity());

        // if the sink node does not exist create it
        if (this->g->find(sink) == this->g->end()) {
            this->g->insert({ sink, std::make_shared<std::vector<Edge>>() });
        }
             
        // if it is the first source edge create the adj list
        if (this->g->find(source) == this->g->end()) {
            this->g->insert({ source, std::make_shared<std::vector<Edge>>() });
        } else {
            // check if the edge already exists
            if (this->hasEdge(source, sink)) {
                std::string s = "edge " + std::to_string(source) + " -> " + std::to_string(sink) + " already exists";
                throw std::invalid_argument(s);
            }
        }

        this->g->at(source)->push_back(e);
    }

    void Graph::addEdge(int source, int sink, int capacity, int cost) {
        auto edge = data_structures::Edge(source, sink, capacity, cost);
        this->addEdge(edge);
    }

    void Graph::removeEdge(int source, int sink) {
        Graph::checkNodeExistence(source);
        Graph::checkNodeExistence(sink);

        auto adj_list = this->g->at(source);

        for (unsigned i = 0; i < adj_list->size(); i++) {
            auto e = adj_list->at(i);
            if (e.getSink() == sink) {
                // remove edge
                adj_list->erase(adj_list->begin() + i);
                return;
            }
        }

        throw std::invalid_argument(data_structures::Graph::getNoEdgeString(source, sink));
    }

    std::string Graph::toString() {
        std::string s = "{";
        s += "\"Edges\": [";

        // iterate over the adj list 
        for (auto & it : *this->g) {
            auto adj_list = it.second; // adj list of the source node
            for (auto e : *adj_list) {
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

    bool Graph::operator==(const data_structures::Graph &other) const {
        if (this == &other) {
            return true;
        }
        if (this->getNumNodes() != other.getNumNodes()) {
            return false;
        }
        for (auto & it : *this->g) {
            int source = it.first;     // source node
            auto adj_list = it.second; // adj list of the source node
            for (auto e : *adj_list) {
                if (!other.hasEdge(source, e.getSink())) {
                    return false;
                }
                if (other.getEdge(source, e.getSink()) != e) {
                    return false;
                }
            }
        }
        return true;
    }

    bool Graph::operator!=(const data_structures::Graph &other) const {
        return !(*this == other);
    }

    std::string Graph::getNoEdgeString(int source, int sink) {
        std::string s = "no edge from " + std::to_string(source) + " to " + std::to_string(sink);
        return s;
    }

    std::string Graph::getNoNodeString(int node) {
        std::string s = "no node " + std::to_string(node);
        return s;
    }
    
    void Graph::checkNodeExistence(int node) const {
        if (this->g->find(node) == this->g->end()) {
            throw std::invalid_argument(data_structures::Graph::getNoNodeString(node));
        }
    }

    void Graph::checkNegativeCapacity(int capacity) {
        if (capacity < 0) {
            throw std::invalid_argument("capacity must be positive");
        }
    }
}
