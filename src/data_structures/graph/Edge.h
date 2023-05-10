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
    class Edge {
    public:
        /**
         * Edge constructor.
         *
         * @param source   The source of the edge
         * @param sink     The sink of the edge
         * @param capacity The capacity of the edge
         * @param cost     The cost of the edge
         */
        Edge(int source, int sink, int capacity, int cost);

        /**
         * Get the source of the edge.
         *
         * @return the source of the edge
         */
        [[nodiscard]] int getSource() const;

        /**
         * Get the sink of the edge.
         *
         * @return the sink of the edge
         */
        [[nodiscard]] int getSink() const;

        /**
         * Get the capacity of the edge.
         *
         * @return the capacity of the edge
         */
        [[nodiscard]] int getCapacity() const;

        /**
         * Get the cost of the edge.
         *
         * @return the cost of the edge
         */
        [[nodiscard]] int getCost() const;

        /**
         * Set the capacity of the edge.
         *
         * @param new_capacity the new capacity of the edge
         */
        void setCapacity(int new_capacity);

        /**
         * Set the cost of the edge.
         *
         * @param new_weight the new cost of the edge
         */
        void setCost(int new_cost);

        /**
         * Print the edge in JSON format.
         */
        [[nodiscard]] std::string toString() const;

        /**
         * Overload of the == operator.
         *
         * @param other the other edge to compare
         * 
         * @return true if the two edges are equal, false otherwise
         */
        bool operator==(const Edge& other) const;

        /**
         * Overload of the != operator.
         *
         * @param other the other edge to compare
         * 
         * @return true if the two edges are not equal, false otherwise
         */
        bool operator!=(const Edge& other) const;

    private:
        int source; // source of the edge
        int sink; // sink of the edge
        int capacity; // capacity of the edge
        int cost; // cost of the edge
    };
}

#endif //MINIMUM_COST_FLOWS_PROBLEM_EDGE_H
