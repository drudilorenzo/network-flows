#ifndef MINIMUM_COST_FLOWS_PROBLEM_GRAPH_H
#define MINIMUM_COST_FLOWS_PROBLEM_GRAPH_H

#include <vector>
#include <memory>
#include <string>

#include "data_structures/graph/Edge.h"

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
             * Get the number of nodes.
             *
             * @return the num of nodes of the graph
             */
            int GetNumNodes() const;

            /**
             * Get the adjacent list of the graph.
             *
             * @return the adjacent list of the graph
             */
            std::vector<std::shared_ptr<std::vector<Edge>>> GetAdjList() const;

            /**
             * Get the adjacent list of the node u.
             *
             * @param u the node
             * @return the adjacent list of the node u
             * @throws invalid_argument if the node does not exist
             */
            std::shared_ptr<std::vector<Edge>> GetNodeAdjList(int i) const;

            /**
             * Check if the edge source -> tail exists.
             *
             * @param source the source node
             * @param tail the tail node
             * @return true if the edge exists, false otherwise
             */
            bool HasEdge(int source, int tail) const;

            /**
             * Get the edge between the nodes u and v.
             *
             * @param u the first node
             * @param b the second node
             * @return the edge between the nodes u and v
             * @throws invalid_argument if the edge does not exist
             */
            data_structures::Edge GetEdge(int u, int v) const;

            /**
             * Set the capacity of the edge between the nodes u and v.
             *
             * @param u the first node
             * @param v the second node
             * @param capacity the new capacity of the edge
             * @throws invalid_argument if the edge does not exist
             */
            void SetEdgeCapacity(int u, int v, int capacity);

            /**
            * Add the direct edge to the graph.
            *
            * @param e The edge to add
            */
            void AddEdge(Edge e);

            /**
             * Remove the direct edge source -> sink from the graph.
             *
             * @param source the source node
             * @param sink the sink node
             * @throws invalid_argument if the edge does not exist
             */
            void RemoveEdge(int source, int sink);

            /**
            * Print the graph in JSON format.
            */
            std::string ToString();

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
             * @param other the other graparc.flow === flow) {
            node.removeArc(adjacentNode.id)h to compare
             * @return true if the two graphs are not equal, false otherwise
             */
            bool operator!=(const Graph& other) const;

        private:
            int num_nodes; // num of vertices of the graph
            std::vector<std::shared_ptr<std::vector<Edge>>> adj_list; // adjacent list used to store the graph
    };
}
#endif //MINIMUM_COST_FLOWS_PROBLEM_GRAPH_H
