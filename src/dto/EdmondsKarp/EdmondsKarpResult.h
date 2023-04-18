#ifndef MINIMUM_COST_FLOWS_PROBLEM_EDMONDSKARPRESULT_H
#define MINIMUM_COST_FLOWS_PROBLEM_EDMONDSKARPRESULT_H

#include "data_structures/graph/Graph.h"

namespace dto {
    /**
     * Class that represents the result of the Edmonds-Karp algorithm.
     *
     */
    class EdmondsKarpResult {
    public:
        /**
         * Constructor
         *
         * @param graph the graph
         * @param max_flow the maximum flow
         */
        EdmondsKarpResult(std::shared_ptr<data_structures::Graph> graph, int max_flow);

        /**
         * Getter for the graph
         *
         * @return the graph
         */
        std::shared_ptr<data_structures::Graph> getGraph() const;

        /**
         * Getter for the maximum flow
         *
         * @return the maximum flow
         */
        int getMaxFlow() const;
    private:
        std::shared_ptr<data_structures::Graph> graph;
        int max_flow;
    };
}

#endif //MINIMUM_COST_FLOWS_PROBLEM_EDMONDSKARPRESULT_H
