#ifndef MINIMUM_COST_FLOWS_PROBLEM_GRAPH_H
#define MINIMUM_COST_FLOWS_PROBLEM_GRAPH_H

#include <vector>
using namespace std;

namespace data_structures {
    /**
     * Class representing a graph stored using adjacent list
     */
    class Graph {
        public:
            /**
             * graph constructor
             *
             * @param V Number of vertices
             */
            Graph(int V);

            /**
             * Add the direct edge from u to v (u, v).
             * It adds the node v to the u's adjacent list
             *
             * @param u The head node of the edge
             * @param v The tail node of the edge
             */
            void AddEdge(int u, int v);

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

        private:
            int num_vertices; // num of vertices of the graph
            vector<int> *adj_list; // adjacent list used to store the graph
    };
}
#endif //MINIMUM_COST_FLOWS_PROBLEM_GRAPH_H
