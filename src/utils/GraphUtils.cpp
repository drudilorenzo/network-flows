#include "GraphUtils.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "consts/Consts.h"
#include "data_structures/graph/Edge.h"

namespace utils {
    data_structures::Graph GraphUtils::CreateGraphFromFile(string file_name) {
        ifstream infile (file_name);

        if (infile) {
            string line;
            int num_vertices;

            getline(infile, line);
            istringstream iss (line);

            if ( !(iss >> num_vertices) ) {
                throw std::invalid_argument("Wrong file formatting (num vertices)");
            }

            data_structures::Graph g = data_structures::Graph(num_vertices);
            int h, t, ca, cs;
            while (getline(infile, line)) {
                iss.clear();
                iss.str(line);
                if ( !(iss >> h >> t >> ca >> cs) ) {
                    throw std::invalid_argument("Wrong file formatting (edge)");
                }
                data_structures::Edge e = data_structures::Edge(h, t, ca, cs);
                try {
                    g.AddEdge(e);
                } catch (std::invalid_argument& e) {
                    throw std::invalid_argument("Wrong edge parameters");
                }
            }
            return g;
        } else {
            throw std::invalid_argument("File not found");
        }
    }

    data_structures::Graph GraphUtils::GetResidualGraph(data_structures::Graph graph) {
        data_structures::Graph residual_graph = data_structures::Graph(graph.GetNumNodes());

        for (int u = 0; u < graph.GetNumNodes(); u++) {
            for (auto e : graph.GetNodeAdjList(u)) {
                int head = e.GetHead();
                int tail = e.GetTail();
                int ca = e.GetCapacity();
                int cs = e.GetCost();

                // Add the edge to the residual graph
                data_structures::Edge edge = data_structures::Edge(head, tail, ca, cs);
                residual_graph.AddEdge(edge);

                // Add the reverse edge to the residual graph
                data_structures::Edge rev_edge = data_structures::Edge(tail, head, 0, -cs);
                residual_graph.AddEdge(rev_edge);
            }
        }

        return residual_graph;
    }
}