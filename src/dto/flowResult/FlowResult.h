#ifndef MINIMUM_COST_FLOWS_PROBLEM_EDMONDSKARPRESULT_H
#define MINIMUM_COST_FLOWS_PROBLEM_EDMONDSKARPRESULT_H

#include "data_structures/graph/Graph.h"

namespace dto {
    /**
     * Class that represents the result of the flow's algorithms.
     * It contains the graph and the flow.
     * Each edge contains the current flow. 
     */
    class FlowResult {
    public:
        /**
         * Constructor.
         *
         * @param graph    the graph
         * @param flow the flow
         */
        FlowResult(std::shared_ptr<data_structures::graph> graph, int flow);

        /**
         * Getter for the graph.
         *
         * @return the graphwith the cuurent flow for each edge
         */
        std::shared_ptr<data_structures::graph> getGraph() const;

        /**
         * Getter for the flow.
         *
         * @return the flow
         */
        int getFlow() const;

    private:
        std::shared_ptr<data_structures::graph> graph;
        int flow;
    };
}

#endif //MINIMUM_COST_FLOWS_PROBLEM_EDMONDSKARPRESULT_H
