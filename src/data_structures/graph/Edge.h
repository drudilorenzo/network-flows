#ifndef MINIMUM_COST_FLOWS_PROBLEM_EDGE_H
#define MINIMUM_COST_FLOWS_PROBLEM_EDGE_H

#include <string>

namespace data_structures {
    /**
     * Class representing an edge of the graph.
     * All the value are integer.
     * Each edge has:
     *  - source (the start node)
     *  - sink (the end node)
     *  - capacity (maximum amount that can flow on the edge)
     *  - weight (weight per unit flow on the edge).
     */
    class edge {
    public:
        /**
         * Edge constructor.
         *
         * @param source   The source of the edge
         * @param sink     The sink of the edge
         * @param capacity The capacity of the edge
         * @param cost     The weight of the edge
         */
        edge(const int source, const int sink, const int capacity, const int cost);

        /**
         * Get the source of the edge.
         *
         * @return the source of the edge
         */
        int getSource();

        /**
         * Get the sink of the edge.
         *
         * @return the sink of the edge
         */
        int getSink();

        /**
         * Get the capacity of the edge.
         *
         * @return the capacity of the edge
         */
        int getCapacity();

        /**
         * Get the weight of the edge.
         *
         * @return the weight of the edge
         */
        int getWeight();

        /**
         * Set the capacity of the edge.
         *
         * @param capacity the new capacity of the edge
         */
        void setCapacity(int capacity);

        /**
         * Print the edge in JSON format.
         */
        std::string toString();

        /**
         * Overload of the == operator.
         *
         * @param other the other edge to compare
         * 
         * @return true if the two edges are equal, false otherwise
         */
        bool operator==(const edge& other) const;

        /**
         * Overload of the != operator.
         *
         * @param other the other edge to compare
         * 
         * @return true if the two edges are not equal, false otherwise
         */
        bool operator!=(const edge& other) const;

    private:
        int source; // source of the edge
        int sink; // sink of the edge
        int capacity; // capacity of the edge
        int weight; // weight of the edge
    };
}

#endif //MINIMUM_COST_FLOWS_PROBLEM_EDGE_H
