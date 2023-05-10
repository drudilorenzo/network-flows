#include "GraphUtils.h"

#include "json.hpp"
#include "consts/Consts.h"
#include "data_structures/graph/Edge.h"

#include <string>
#include <memory>
#include <fstream>
#include <stdexcept>
#include <algorithm>

using json = nlohmann::ordered_json;

namespace utils {
    std::shared_ptr<data_structures::Graph> GraphUtils::CreateGraphFromJSON(const std::string& filename) {
        // open the file
        std::ifstream infile { filename };

        if (infile) {
            // check if the extension is .json
            if (filename.substr(filename.find_last_of('.') + 1) != "json") {
                throw std::invalid_argument("File extension is not .json");
            }

            // read the json file
            try {
                json data = json::parse(infile);

                // create graph
                int num_nodes { data["Num_nodes"] };

                // create edges
                nlohmann::json edges = data.at("Edges");
                auto graph = std::make_shared<data_structures::Graph>(num_nodes);

                for (auto& e : edges) {
                    int source { e.at("Source") };
                    int sink { e.at("Sink") };
                    int capacity { e.at("Capacity") };
                    int cost { e.at("Cost") };

                    // add edge to graph
                    graph->addEdge(source, sink, capacity, cost);
                }
                return graph;
                
                // catch json parse error
            } catch (std::exception& e) {
                throw std::invalid_argument("File " + filename + " is not a valid JSON file: " + std::string(e.what()));
            }
        } else {
            throw std::invalid_argument("File " + filename + " not found");
        }
    }

    std::shared_ptr<data_structures::Graph> GraphUtils::GetResidualGraph(const std::shared_ptr<data_structures::Graph>& graph) {
        auto residual_graph = std::make_shared<data_structures::Graph>(graph->getNumNodes());

        for (int source = 0; source < graph->getNumNodes(); source++) {
            for (auto e : *graph->getNodeAdjList(source)) {
                int sink { e.getSink() };
                int capacity { e.getCapacity() };
                int cost { e.getCost() };

                // the residual graph contains only the edges with positive capacity
                if (capacity <= 0) {
                    continue;
                }

                // handle anti-parallel edges adding an artificial node between source and sink.
                // the value of the artificial node is the value of source node plus the number of nodes,
                // it will be easy to retrieve the original source node from the artificial node doing a simple subtraction

                // check if the edge is anti-parallel, and it is not already in the residual graph (source < sink)
                if (source < sink && graph->hasEdge(sink, source)) {
                    // add the artificial node
                    int artificial_node { residual_graph->getNumNodes() };
                    residual_graph->addEdge(source, artificial_node, capacity, cost);
                    residual_graph->addEdge(artificial_node, sink, capacity, cost);
                } else {
                    // else simply add the edge to the residual graph
                    residual_graph->addEdge(source, sink, capacity, cost);
                }
            }
        }

        return residual_graph;
    }

    std::shared_ptr<data_structures::Graph> GraphUtils::GetOptimalGraph(const std::shared_ptr<data_structures::Graph>& residual_graph,
        const std::shared_ptr<data_structures::Graph>& graph) {
        
        auto optimal_graph = std::make_shared<data_structures::Graph>(residual_graph->getStartingNumNodes());

        for (int sink = 0; sink < residual_graph->getStartingNumNodes(); sink++) {
            for (auto e : *residual_graph->getNodeAdjList(sink)) {
                
                int source { e.getSink() };
                
                // discard the edges present in the original graph
                // since they contain the remaining capacity of the edge.
                if (graph->hasEdge(sink, source)) {
                    continue;
                }

                int capacity { e.getCapacity() };
                int start_cost { graph->getEdge(source, sink).getCost() };
                int start_node { source };

                // remove the artificial node added to handle anti-parallel edges
                if (source >= residual_graph->getStartingNumNodes()) {
                    // get the original source node by getting the sink of
                    // the only edge of the artificial node
                    start_node = residual_graph->getNodeAdjList(source)->at(0).getSink();
                }

                // add the edge to the optimal graph
                optimal_graph->addEdge(start_node, sink, capacity, start_cost);
            }
        }

        // add the edges of the original graph that are not in the residual graph
        for (int source = 0; source < graph->getNumNodes(); source++) {
            for (auto e : *graph->getNodeAdjList(source)) {
                // if the optimal graph does not contain the edge, add it with 0 flow
                if ( !optimal_graph->hasEdge(source, e.getSink()) ) {
                    optimal_graph->addEdge(source, e.getSink(), 0, e.getCost());
                }
            }
        }

        return optimal_graph;
    }

    std::shared_ptr<std::vector<int>> GraphUtils::RetrievePath(const std::shared_ptr<std::vector<int>>& parent, int source, int sink) {
        auto path = std::make_shared<std::vector<int>>();
        int tmp { sink };
        path->push_back(tmp);
        tmp = parent->at(tmp);

        // loop until the source node is reached or the node is already in the path
        while (tmp != source && std::find(path->begin(), path->end(), tmp) == path->end()) {
            path->push_back(tmp);
            tmp = parent->at(tmp);
        }

        // if source is not -1, add it to the path
        if (source != consts::source_parent) {
            path->push_back(tmp);
        }

        reverse(path->begin(), path->end());
        return path;
    }

    int GraphUtils::GetResidualCapacity(const std::shared_ptr<data_structures::Graph>& residual_graph, const std::shared_ptr<std::vector<int>>& path) {
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

    void GraphUtils::SendFlowInPathNegativeCosts(const std::shared_ptr<data_structures::Graph>& residual_graph, const std::shared_ptr<std::vector<int>>& path, int flow) {
        for (unsigned u = 0; u < path->size()-1; u++) {
            int v { static_cast<int>(u + 1) };
            int source { path->at(u) };
            int sink { path->at(v) };

            auto edge = residual_graph->getEdge(source, sink);
            int cost { edge.getCost() };
            int capacity;

            // if the edge is traversed backward, subtract the flow
            if (cost < 0) {
                capacity = residual_graph->getEdge(source, sink).getCapacity() + flow;
            } else {
                // check if the flow is greater than the residual capacity of the edge
                if (residual_graph->getEdge(source, sink).getCapacity() < flow) {
                    throw std::invalid_argument("The flow is greater than the residual capacity of the edge");
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
                residual_graph->addEdge(sink, source, flow, -cost);
            } else {
                residual_graph->setEdgeCapacity(sink, source, residual_graph->getEdge(sink, source).getCapacity() + flow);
            }
        }
    }

    void GraphUtils::SendFlowInPathReducedCosts(const std::shared_ptr<data_structures::Graph>& residual_graph,
        const std::shared_ptr<data_structures::Graph>& original_graph, const std::shared_ptr<std::vector<int>>& path, int flow) {
            for (unsigned u = 0; u < path->size()-1; u++) {
                int v { static_cast<int>(u + 1) };
                int source { path->at(u) };
                int sink { path->at(v) };
                int capacity;

                // if the edge is traversed backward, subtract the flow
                if (!original_graph->hasEdge(source, sink)) {
                    capacity = residual_graph->getEdge(source, sink).getCapacity() + flow;
                } else {
                    // check if the flow is greater than the residual capacity of the edge
                    if (residual_graph->getEdge(source, sink).getCapacity() < flow) {
                        throw std::invalid_argument("The flow is greater than the residual capacity of the edge");
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
                    residual_graph->addEdge(sink, source, flow, 0);
                } else {
                    residual_graph->setEdgeCapacity(sink, source, residual_graph->getEdge(sink, source).getCapacity() + flow);
                }
            }
    }

}