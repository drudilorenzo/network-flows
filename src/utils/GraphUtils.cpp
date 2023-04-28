#include "GraphUtils.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>
#include "json.hpp"
#include "data_structures/graph/Edge.h"

using json = nlohmann::ordered_json;

namespace utils {
    std::shared_ptr<data_structures::graph> GraphUtils::CreateGraphFromJSON(const std::string& filename) {
        // open the file
        std::ifstream infile { filename };

        if (infile) {
            // check if the extension is .json
            if (filename.substr(filename.find_last_of('.') + 1) != "json") {
                throw std::invalid_argument("File extension is not .json");
            }

            // read the json file
            try {

                std::cout << "Reading file: " << filename << std::endl;
                json data = json::parse(infile);

                // create graph
                int num_nodes { data["Num_nodes"] };
                std::cout << "Number of nodes: " << num_nodes << std::endl;

                // create edges
                nlohmann::json edges = data.at("Edges");
                std::cout << "Number of edges: " << edges.size() << std::endl;
                auto graph = std::make_shared<data_structures::graph>(num_nodes);

                for (auto& e : edges) {
                    int source { e.at("Source") };
                    int sink { e.at("Sink") };
                    int capacity { e.at("Capacity") };
                    int weight { e.at("Weight") };

                    // add edge to graph
                    auto edge = data_structures::edge(source, sink, capacity, weight);
                    graph->addEdge(edge);
                    std::cout << "Edge added: "  << edge.toString() << std::endl;
                }
                return graph;
                
                // catch json parse error
            } catch (std::exception& e) {
                throw std::invalid_argument("ERROR: File " + filename + " is not a valid JSON file: " + std::string(e.what()));
            }
        } else {
            throw std::invalid_argument("ERROR: File " + filename + " not found");
        }
    }

    std::shared_ptr<data_structures::graph> GraphUtils::GetResidualGraph(const std::shared_ptr<data_structures::graph>& graph) {
        auto residual_graph = std::make_shared<data_structures::graph>(graph->getNumNodes());

        for (int u = 0; u < graph->getNumNodes(); u++) {
            for (auto e : *graph->getNodeAdjList(u)) {
                int tail { e.getSink() };
                int capacity { e.getCapacity() };
                int weight { e.getWeight() };

                // the residual graph contains only the edges with positive capacity
                if (capacity <= 0) {
                    continue;
                }

                // add the edge to the residual graph
                auto  edge = data_structures::edge(u, tail, capacity, weight);
                residual_graph->addEdge(edge);
            }
        }

        return residual_graph;
    }

    std::shared_ptr<data_structures::graph> GraphUtils::GetOptimalGraph(const std::shared_ptr<data_structures::graph>& graph) {
        auto optimal_graph = std::make_shared<data_structures::graph>(graph->getNumNodes());

        for (int u = 0; u < graph->getNumNodes(); u++) {
            for (auto e : *graph->getNodeAdjList(u)) {
                // get only the graph with negative cost edges
                if (e.getWeight() >= 0) {
                    continue;
                }
                int source { e.getSource() };
                int sink { e.getSink() };
                int capacity { e.getCapacity() };
                int weight { e.getWeight() };

                // add the edge to the optimal graph
                auto  rev_edge = data_structures::edge(sink, source, capacity, -weight);
                optimal_graph->addEdge(rev_edge);
            }
        }

        return optimal_graph;
    }

    std::shared_ptr<std::vector<int>> GraphUtils::RetrievePath(const std::shared_ptr<std::vector<int>>& parent, int node) {
        auto path = std::make_shared<std::vector<int>>();
        int tmp { node };
        path->push_back(tmp);
        tmp = parent->at(tmp);

        // loop until the source node is reached or the node is already in the path
        while (tmp != -1 && std::find(path->begin(), path->end(), tmp) == path->end()) {
            path->push_back(tmp);
            tmp = parent->at(tmp);
        }
        reverse(path->begin(), path->end());
        return path;
    }

    int GraphUtils::GetResidualCapacity(const std::shared_ptr<data_structures::graph>& residual_graph, const std::shared_ptr<std::vector<int>>& path) {
        int path_flow { std::numeric_limits<int>::max() }; 

        // if the path is empty or has only one node, return 0
        if (path->size() <= 1) {
            return 0;
        }

        // find the minimum capacity in the path
        for (unsigned u = 0; u < path->size()-1; u++) {
            int v { static_cast<int>(u + 1) };
            int source { path->at(u) };
            int sink { path->at(v) };
            path_flow = std::min(path_flow, residual_graph->getEdge(source, sink).getCapacity());
        }

        return path_flow;
    }

    void GraphUtils::SendFlowInPath(const std::shared_ptr<data_structures::graph>& residual_graph, const std::shared_ptr<std::vector<int>>& path, int flow) {
        for (unsigned u = 0; u < path->size()-1; u++) {
            int v { static_cast<int>(u + 1) };
            int source { path->at(u) };
            int sink { path->at(v) };

            auto edge = residual_graph->getEdge(source, sink);
            int weight { edge.getWeight() };
            int capacity;

            // if the edge is traversed backward, subtract the flow
            if (weight < 0) {
                capacity = residual_graph->getEdge(source, sink).getCapacity() + flow;
            } else {
                // check if the flow is greater than the residual capacity of the edge
                if (residual_graph->getEdge(source, sink).getCapacity() < flow) {
                    throw std::invalid_argument("ERROR: The flow is greater than the residual capacity of the edge");
                }

                // if the edge is traversed forward, update the residual capacity
                capacity = residual_graph->getEdge(source, sink).getCapacity() - flow;
            }

            residual_graph->setEdgeCapacity(source, sink, capacity);

            // if residual capacity is 0, remove the edge
            if (residual_graph->getEdge(source, sink).getCapacity() == 0) {
                residual_graph->removeEdge(source, sink);
            }

            // if the reverse edge does not exist, add it
            if (!residual_graph->hasEdge(sink, source)) {
                residual_graph->addEdge(data_structures::edge(sink, source, flow, -weight));
            } else {
                residual_graph->setEdgeCapacity(sink, source, residual_graph->getEdge(sink, source).getCapacity() + flow);
            }
        }
    }

}