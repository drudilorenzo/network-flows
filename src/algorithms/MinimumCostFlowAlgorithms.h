#ifndef MINIMUM_COST_FLOWS_PROBLEM_MINIMUMCOSTFLOWALGORITHMS_H
#define MINIMUM_COST_FLOWS_PROBLEM_MINIMUMCOSTFLOWALGORITHMS_H

#include "data_structures/graph/Graph.h"
#include "dto/flowResult/FlowResult.h"

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
             *
             * @param graph the graph to solve.
             *
             * @return the residual graph and the minimum weight flow
             */
            static std::shared_ptr<dto::FlowResult> CycleCancelling(std::shared_ptr<data_structures::graph> graph);

            /**
             * Successive Shortest Path algorithm.
             *
             * @param graph the graph to solve
             * 
             * @return the minimum weight flow
             */
            static int SuccessiveShortestPath(std::shared_ptr<data_structures::graph> graph);

            /**
             * Primal-Dual algorithm.
             *
             * @param graph the graph to solve
             * 
             * @return the minimum weight flow
             */
            static int PrimalDual(std::shared_ptr<data_structures::graph> graph);
    };
}

#endif //MINIMUM_COST_FLOWS_PROBLEM_MINIMUMCOSTFLOWALGORITHMS_H
