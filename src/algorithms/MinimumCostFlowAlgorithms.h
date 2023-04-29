#ifndef MINIMUM_COST_FLOWS_PROBLEM_MINIMUMCOSTFLOWALGORITHMS_H
#define MINIMUM_COST_FLOWS_PROBLEM_MINIMUMCOSTFLOWALGORITHMS_H

#include "dto/flowResult/FlowResult.h"
#include "data_structures/graph/Graph.h"

#include <memory>

namespace algorithms {
    /**
     * Class containing the following minimum weight flow algorithms:
     * - Cycle-Cancelling
     * - Successive Shortest Path
     * - Primal-Dual
     */
    class MinimumCostFlowAlgorithms {
        public:
            /**
             * Cycle-Cancelling algorithm.
             * Cycle-cancelling algorithm is a method for finding a minimum-cost flow in a flow network.
             * The cycle-canceling algorithm is one of the earliest algorithms to solve the minimum cost flow problem. 
             * This algorithm maintains a feasible solution x in the network G and proceeds by augmenting flows along negative 
             * cost directed cycles in the residual network G(x) and thereby canceling them
             * Return the residual graph and the minimum weight flow of the path between source and sink.
             *
             * (see: https://complex-systems-ai.com/en/maximum-flow-problem/cycle-canceling-algorithm/)
             * 
             * V: number of nodes
             * E: number of edges
             * U: maximum capacity
             * C: maximum absolute value of cost
             * Time complexity: O(O(V * E^2 * C * U))
             * 
             * @param graph  the graph to solve.
             * @param source the source node
             * @param sink   the sink node
             *
             * @return the residual graph and the minimum weight flow
             */
            static std::shared_ptr<dto::FlowResult> CycleCancelling(const std::shared_ptr<data_structures::Graph>& graph, int source, int sink);

            /**
             * Successive Shortest Path algorithm.
             *
             * @param graph the graph to solve
             * @param source the source node
             * @param sink the sink node
             * 
             * @return the residual graph and the minimum weight flow
             */
            static std::shared_ptr<dto::FlowResult> SuccessiveShortestPath(std::shared_ptr<data_structures::Graph> graph, int source, int sink);

            /**
             * Primal-Dual algorithm.
             *
             * @param graph the graph to solve
             * @param source the source node
             * @param sink the sink node
             * 
             * @return the minimum weight flow
             */
            static std::shared_ptr<dto::FlowResult> PrimalDual(std::shared_ptr<data_structures::Graph> graph, int source, int sink);
    };
}

#endif //MINIMUM_COST_FLOWS_PROBLEM_MINIMUMCOSTFLOWALGORITHMS_H
