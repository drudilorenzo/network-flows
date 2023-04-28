#ifndef MINIMUM_COST_FLOWS_PROBLEM_GRAPH_H
#define MINIMUM_COST_FLOWS_PROBLEM_GRAPH_H

#include <vector>
#include <map>
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
             * Graph empty constructor.
             */
            Graph();

            /**
             * Return the number of nodes of the graph.
             * Max node id + 1.
             * The node's id are added consecutively without missing numbers.
             *
             * @param num_nodes the number of nodes
             */
            int getNumNodes() const;

            /**
             * Get the graph.
             *
             * @return the graph
             */
            [[maybe_unused]] std::shared_ptr<std::map<int, std::shared_ptr<std::vector<Edge>>>> getGraph() const;

            /**
             * Get the adjacent list of the node i.
             *
             * @param i the node
             * 
             * @return the adjacent list of the node u
             * 
             * @throws invalid_argument if the node does not exist
             */
            std::shared_ptr<std::vector<Edge>> getNodeAdjList(int i) const;

            /**
             * Check if the edge source -> tail exists.
             *
             * @param source the source node
             * @param sink   the tail node
             * 
             * @return true if the edge exists, false otherwise
             * 
             * @throws invalid_argument if the node does not exist
             */
            bool hasEdge(int source, int sink) const;

            /**
             * Get the edge between the nodes u and v.
             *
             * @param source the first node
             * @param sink   the second node
             * 
             * @return the edge between the nodes u and v
             * 
             * @throws invalid_argument if the edge does not exist
             */
            data_structures::Edge getEdge(int source, int sink) const;

            /**
             * Set the capacity of the edge between the nodes u and v.
             *
             * @param source   the first node
             * @param sink     the second node
             * @param capacity the new capacity of the edge
             * 
             * @throws invalid_argument if the edge does not exist
             */
            void setEdgeCapacity(int source, int sink, int capacity);

            /**
            * Add the direct edge to the graph.
            *
            * @param e The edge to add
            * 
            * @throws invalid_argument if the nodes are negative
            * @throws invalid_argument if the edge already exists
            */
            void addEdge(Edge e);

            /**
             * Remove the direct edge source -> sink from the graph.
             *
             * @param source the source node
             * @param sink   the sink node
             * 
             * @throws invalid_argument if the edge does not exist
             */
            void removeEdge(int source, int sink);

            /**
            * Print the graph in JSON format.
            */
            std::string toString();

            /**
             * Overload of the == operator.
             *
             * @param other the other graph to compare.
             * 
             * @return true if the two graphs are equal, false otherwise
             */
            bool operator==(const Graph& other) const;

            /**
             * Overload of the != operator.
             *
             * @param other the other graph to compare
             * 
             * @return true if the two graphs are not equal, false otherwise
             */
            bool operator!=(const Graph& other) const;

        private:
            /**
             * Get the string representing the no-edge message between the nodes u and v.
             *
             * @param source the source node
             * @param sink   the sink node
             * 
             * @return the string representing the no-edge message between the nodes u and v
             */
            static std::string getNoEdgeString(int source, int sink) ;

            /**
             * Get the string representing the no-node message.
             *
             * @param node the node
             * 
             * @return the string representing the no-node message
             */
            static std::string getNoNodeString(int node) ;

            // graph represented using map of adjacent list
            std::shared_ptr<std::map<int, std::shared_ptr<std::vector<Edge>>>> g;
    };
}
#endif //MINIMUM_COST_FLOWS_PROBLEM_GRAPH_H
