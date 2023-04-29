#ifndef MINIMUM_COST_FLOWS_PROBLEM_EDMONDSKARPRESULT_H
#define MINIMUM_COST_FLOWS_PROBLEM_EDMONDSKARPRESULT_H

#include "data_structures/graph/Graph.h"

namespace dto {
    /**
     * Class that represents the result of the flow's algorithms.
     * It contains the graph and the flow.
     */
    class FlowResult {
    public:
        /**
         * Constructor.
         *
         * @param graph    the graph
         * @param flow     the flow
         */
        FlowResult(std::shared_ptr<data_structures::Graph> graph, int flow);

        /**
         * Getter for the graph.
         *
         * @return the graph with the curent flow for each edge
         */
        [[nodiscard]] std::shared_ptr<data_structures::Graph> getGraph() const;

        /**
         * Getter for the flow.
         *
         * @return the flow
         */
        [[nodiscard]] int getFlow() const;

    private:
        int flow;
        std::shared_ptr<data_structures::Graph> graph;
    };
}

#endif //MINIMUM_COST_FLOWS_PROBLEM_EDMONDSKARPRESULT_H
