#ifndef MINIMUM_COST_FLOWS_PROBLEM_GRAPH_H
#define MINIMUM_COST_FLOWS_PROBLEM_GRAPH_H

#include <vector>

#include "data_structures/Edge.h"

using namespace std;

namespace data_structures {
    /**
     * Class representing a graph stored using adjacent list.
     */
    class Graph {
        public:
            /**
             * Graph constructor.
             *
             * @param V Number of vertices
             */
            Graph(const int V);

            /**
             * Add the direct edge to the graph.
             *
             * @param e The edge to add
             */
            void AddEdge(Edge e);

            /**
             * Pretty print the graph.
             */
            void PrintGraph();

            /**
             * Overload of the == operator
             *
             * @param other the other graph to compare
             * @return true if the two graphs are equal, false otherwise
             */
            bool operator==(const Graph& other) const;

            /**
             * Overload of the != operator
             *
             * @param other the other graph to compare
             * @return true if the two graphs are not equal, false otherwise
             */
            bool operator!=(const Graph& other) const;

        private:
            int num_vertices; // num of vertices of the graph
            vector<Edge> *adj_list; // adjacent list used to store the graph
    };
}
#endif //MINIMUM_COST_FLOWS_PROBLEM_GRAPH_H
