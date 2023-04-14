#include "GraphUtils.h"
#include "consts/Consts.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace utils {
    data_structures::Graph GraphUtils::createGraphFromFile(string file_name) {
        ifstream infile (file_name);

        if (infile) {
            string line;
            int num_vertices;

            getline(infile, line);
            istringstream iss (line);

            if ( !(iss >> num_vertices) ) {
                cout << "ERROR: Wrong file formatting";
                return EMPTY_GRAPH;
            }

            data_structures::Graph g = data_structures::Graph(num_vertices);
            int u, v;
            while (getline(infile, line)) {
                iss.clear();
                iss.str(line);
                if ( !(iss >> u >> v) ) {
                    cout << "ERROR: Wrong file formatting";
                    return EMPTY_GRAPH;
                }
                g.AddEdge(u, v);
            }
            return g;
        } else {
            cout << "ERROR: File " << file_name << " not found!";
            return EMPTY_GRAPH;
        }

    }
}