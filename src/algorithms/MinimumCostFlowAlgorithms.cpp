#include "MinimumCostFlowAlgorithms.h"

#include "MaximumFlowAlgorithms.h"
#include "GraphBaseAlgorithms.h"
#include "utils/GraphUtils.h"

#include <iostream>

namespace algorithms {
    int MinimumCostFlowAlgorithms::CycleCancelling(std::shared_ptr<data_structures::Graph> graph) {
        int source = 0;
        int sink = graph->GetNumNodes()-1;
        auto edmonds_karps_result = MaximumFlowAlgorithms::EdmondsKarp(graph, source, sink);
        auto residual_graph = edmonds_karps_result->getGraph();

        auto bellman_ford_result = GraphBaseAlgorithms::BellmanFord(graph, source);
        while (bellman_ford_result->hasNegativeCycle()) {
            std::cout << "Negative cycle found" << std::endl;
            auto negative_cycle = bellman_ford_result->getNegativeCycle();
            int residual_capacity = utils::GraphUtils::GetResidualCapacity(residual_graph, negative_cycle);

            utils::GraphUtils::SendFlowInPath(residual_graph, negative_cycle, residual_capacity);

            bellman_ford_result = GraphBaseAlgorithms::BellmanFord(residual_graph, source);
        }

        std::cout << residual_graph->ToString() << std::endl;

        // get minimum cost
        int minimum_cost = 0;
        for (int u = 0; u < residual_graph->GetNumNodes(); u++) {
            for (auto edge: *residual_graph->GetNodeAdjList(u)) {
                if (edge.GetWeight() < 0) {
                    int weight = edge.GetWeight();
                    minimum_cost -= weight;
                }
            }
        }
        return minimum_cost;
    }

}