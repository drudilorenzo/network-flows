#include "GraphUtils.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "consts/Consts.h"
#include "data_structures/Edge.h"

namespace utils {
    data_structures::Graph GraphUtils::createGraphFromFile(string file_name) {
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
}