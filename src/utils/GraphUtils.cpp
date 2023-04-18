#include "GraphUtils.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <memory>
#include "json.hpp"
#include "data_structures/graph/Edge.h"

using json = nlohmann::json;

namespace utils {
    std::shared_ptr<data_structures::Graph> GraphUtils::CreateGraphFromJSON(string file_name) {
        // open the file
        ifstream infile (file_name);

        if (infile) {
            // check if the extension is .json
            if (file_name.substr(file_name.find_last_of(".") + 1) != "json") {
                throw std::invalid_argument("File extension is not .json");
            }
            // read the file
            try {
                std::cout << "Reading file: " << file_name << endl;
                // parse json
                json data = json::parse(infile);

                // create graph
                int num_nodes = data["Num_nodes"];
                std::cout << "Number of nodes: " << num_nodes << endl;

                nlohmann::json edges = data.at("Edges");
                std::cout << "Number of edges: " << edges.size() << endl;
                auto graph = make_shared<data_structures::Graph>(num_nodes);
                int source, sink, capacity, cost;
                for (auto& e : edges) {
                    cout << "Adding edge: " << e << endl;
                    source = e.at("Source");
                    sink = e.at("Sink");
                    capacity = e.at("Capacity");
                    cost = e.at("Cost");

                    // add edge to graph
                    auto edge = data_structures::Edge(source, sink, capacity, cost);
                    graph->AddEdge(edge);
                }
                return graph;
                // catch json parse error
            } catch (exception& e) {
                throw std::invalid_argument("ERROR: File " + file_name + " is not a valid JSON file: " + string(e.what()));
            }
        } else {
            throw std::invalid_argument("ERROR: File " + file_name + " not found");
        }
    }

    std::shared_ptr<data_structures::Graph> GraphUtils::GetResidualGraph(std::shared_ptr<data_structures::Graph> graph) {
        auto residual_graph = make_shared<data_structures::Graph>(graph->GetNumNodes());

        for (int u = 0; u < graph->GetNumNodes(); u++) {
            for (auto e : *graph->GetNodeAdjList(u)) {
                int head = e.GetSource();
                int tail = e.GetSink();
                int ca = e.GetCapacity();
                int cs = e.GetWeight();

                // Add the edge to the residual graph
                auto  edge = data_structures::Edge(head, tail, ca, cs);
                residual_graph->AddEdge(edge);

                // Add the reverse edge to the residual graph
                auto rev_edge = data_structures::Edge(tail, head, 0, -cs);
                residual_graph->AddEdge(rev_edge);
            }
        }

        return residual_graph;
    }

    std::shared_ptr<std::vector<int>> GraphUtils::RetrievePath(std::shared_ptr<std::vector<int>> parent, int node) {
        auto path = make_shared<std::vector<int>>();
        int num_nodes = parent->size();
        for (int i = 0; i <= num_nodes; i++) {
            node = parent->at(node);
        }

        int tmp = node;
        path->push_back(tmp);
        while (tmp != node || tmp != -1) {
            tmp = parent->at(tmp);
            path->push_back(tmp);
        }

        reverse(path->begin(), path->end());
        return path;
    }
}