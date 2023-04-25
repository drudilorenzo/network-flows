#include "GraphUtils.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>
#include "json.hpp"
#include "data_structures/graph/Edge.h"

using json = nlohmann::ordered_json;

namespace utils {
    std::shared_ptr<data_structures::Graph> GraphUtils::CreateGraphFromJSON(std::string file_name) {
        // open the file
        std::ifstream infile (file_name);

        if (infile) {
            // check if the extension is .json
            if (file_name.substr(file_name.find_last_of(".") + 1) != "json") {
                throw std::invalid_argument("File extension is not .json");
            }
            // read the file
            try {
                std::cout << "Reading file: " << file_name << std::endl;
                // parse json
                json data = json::parse(infile);

                // create graph
                int num_nodes = data["Num_nodes"];
                std::cout << "Number of nodes: " << num_nodes << std::endl;

                nlohmann::json edges = data.at("Edges");
                std::cout << "Number of edges: " << edges.size() << std::endl;
                auto graph = std::make_shared<data_structures::Graph>(num_nodes);
                int source, sink, capacity, weight;
                for (auto& e : edges) {
                    source = e.at("Source");
                    sink = e.at("Sink");
                    capacity = e.at("Capacity");
                    weight = e.at("Weight");

                    // add edge to graph
                    auto edge = data_structures::Edge(source, sink, capacity, weight);
                    graph->AddEdge(edge);
                    std::cout << "Edge added: "  << edge.ToString() << std::endl;
                }
                return graph;
                // catch json parse error
            } catch (std::exception& e) {
                throw std::invalid_argument("ERROR: File " + file_name + " is not a valid JSON file: " + std::string(e.what()));
            }
        } else {
            throw std::invalid_argument("ERROR: File " + file_name + " not found");
        }
    }

    std::shared_ptr<data_structures::Graph> GraphUtils::GetResidualGraph(std::shared_ptr<data_structures::Graph> graph) {
        auto residual_graph = std::make_shared<data_structures::Graph>(graph->GetNumNodes());

        for (int u = 0; u < graph->GetNumNodes(); u++) {
            for (auto e : *graph->GetNodeAdjList(u)) {
                int tail = e.GetSink();
                int capacity = e.GetCapacity();
                int weight = e.GetWeight();

                // the residual graph contains only the edges with positive capacity
                if (capacity <= 0) {
                    continue;
                }

                // Add the edge to the residual graph
                auto  edge = data_structures::Edge(u, tail, capacity, weight);
                residual_graph->AddEdge(edge);
            }
        }

        return residual_graph;
    }

    std::shared_ptr<data_structures::Graph> GraphUtils::GetOptimalGraph(std::shared_ptr<data_structures::Graph> graph) {
        auto optimal_graph = std::make_shared<data_structures::Graph>(graph->GetNumNodes());

        for (int u = 0; u < graph->GetNumNodes(); u++) {
            for (auto e : *graph->GetNodeAdjList(u)) {
                // Get only the graph with negative cost edges
                if (e.GetWeight() >= 0) {
                    continue;
                }
                int source = e.GetSource();
                int sink = e.GetSink();
                int capacity = e.GetCapacity();
                int weight = -e.GetWeight();

                // Add the edge to the optimal graph
                auto  rev_edge = data_structures::Edge(sink, source, capacity, weight);
                optimal_graph->AddEdge(rev_edge);
            }
        }

        return optimal_graph;
    }

    std::shared_ptr<std::vector<int>> GraphUtils::RetrievePath(std::shared_ptr<std::vector<int>> parent, int node) {
        auto path = std::make_shared<std::vector<int>>();
        int tmp = node;
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

    int GraphUtils::GetResidualCapacity(std::shared_ptr<data_structures::Graph> residual_graph, std::shared_ptr<std::vector<int>> path) {
        int path_flow = std::numeric_limits<int>::max();
        if (path->size() <= 1) {
            return 0;
        }

        for (int u = 0; u < path->size()-1; u++) {
            int v = u + 1;
            int source = path->at(u);
            int sink = path->at(v);
            path_flow = std::min(path_flow, residual_graph->GetEdge(source, sink).GetCapacity());
        }

        return path_flow;
    }

    void GraphUtils::SendFlowInPath(std::shared_ptr<data_structures::Graph> residual_graph, std::shared_ptr<std::vector<int>> path, int flow) {
        for (int u = 0; u < path->size()-1; u++) {
            int v = u + 1;
            int source = path->at(u);
            int sink = path->at(v);

            auto edge = residual_graph->GetEdge(source, sink);
            int weight = edge.GetWeight();
            int capacity = 0;

            // If the edge is traversed backword, subtract the flow
            if (weight < 0) {
                capacity = residual_graph->GetEdge(source, sink).GetCapacity() - flow;
            } else {
                capacity = residual_graph->GetEdge(source, sink).GetCapacity() + flow;
            }

            residual_graph->SetEdgeCapacity(source, sink, capacity);

            // if residual capacity is 0, remove the edge
            if (residual_graph->GetEdge(source, sink).GetCapacity() == 0) {
                residual_graph->RemoveEdge(source, sink);
            }

            // if the reverse edge does not exist, add it
            if (!residual_graph->HasEdge(sink, source)) {
                residual_graph->AddEdge(data_structures::Edge(sink, source, flow, -weight));
            } else {
                residual_graph->SetEdgeCapacity(sink, source, residual_graph->GetEdge(sink, source).GetCapacity() + flow);
            }
        }
    }

}