#ifndef MINIMUM_COST_FLOWS_PROBLEM_MINIMUMCOSTFLOWALGORITHMS_H
#define MINIMUM_COST_FLOWS_PROBLEM_MINIMUMCOSTFLOWALGORITHMS_H

#include <memory>

#include "data_structures/graph/Graph.h"

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
             * Cycle-Cancelling algorithm
             *
             * @param graph the graph to solve
             * @return the minimum weight flow
             */
            static int CycleCancelling(std::shared_ptr<data_structures::Graph> graph);

            /**
             * Successive Shortest Path algorithm
             *
             * @param graph the graph to solve
             * @return the minimum weight flow
             */
            static int SuccessiveShortestPath(std::shared_ptr<data_structures::Graph> graph);

            /**
             * Primal-Dual algorithm
             *
             * @param graph the graph to solve
             * @return the minimum weight flow
             */
            static int PrimalDual(std::shared_ptr<data_structures::Graph> graph);
    };
}

#endif //MINIMUM_COST_FLOWS_PROBLEM_MINIMUMCOSTFLOWALGORITHMS_H
