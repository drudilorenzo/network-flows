#ifndef MINIMUM_COST_FLOWS_PROBLEM_EDGE_H
#define MINIMUM_COST_FLOWS_PROBLEM_EDGE_H

namespace data_structures {
    /**
     * Class representing an edge of the graph.
     * All the value are integer.
     * Each edge has:
     *  - head (the start node)
     *  - tail (the end node)
     *  - capacity (maximum amount that can flow on the edge)
     *  - cost (cost per unit flow on the edge).
     */
    class Edge {
    public:
        /**
         * Edge constructor.
         *
         * @param head The head of the edge
         * @param tail The tail of the edge
         * @param capacity The capacity of the edge
         * @param cost The cost of the edge
         */
        Edge(const int head, const int tail, const int capacity, const int cost);

        /**
         * Get the head of the edge.
         *
         * @return the head of the edge
         */
        int GetHead();

        /**
         * Get the tail of the edge.
         *
         * @return the tail of the edge
         */
        int GetTail();

        /**
         * Get the capacity of the edge.
         *
         * @return the capacity of the edge
         */
        int GetCapacity();

        /**
         * Get the cost of the edge.
         *
         * @return the cost of the edge
         */
        int GetCost();

        /**
         * Set the capacity of the edge.
         *
         * @param capacity the new capacity of the edge
         */
        void SetCapacity(int capacity);

        /**
         * Pretty print the edge.
         */
        void ToString();

        /**
         * Overload of the == operator
         *
         * @param other the other edge to compare
         * @return true if the two edges are equal, false otherwise
         */
        bool operator==(const Edge& other) const;

        /**
         * Overload of the != operator
         *
         * @param other the other edge to compare
         * @return true if the two edges are not equal, false otherwise
         */
        bool operator!=(const Edge& other) const;

    private:
        int head; // head of the edge
        int tail; // tail of the edge
        int capacity; // capacity of the edge
        int cost; // cost of the edge
    };
}

#endif //MINIMUM_COST_FLOWS_PROBLEM_EDGE_H
