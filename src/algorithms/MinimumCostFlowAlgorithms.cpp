#include "MinimumCostFlowAlgorithms.h"

#include "utils/GraphUtils.h"
#include "GraphBaseAlgorithms.h"
#include "MaximumFlowAlgorithms.h"

#include <map>
#include <queue>
#include <memory>
#include <stdexcept>

namespace algorithms {
    std::shared_ptr<dto::FlowResult> MinimumCostFlowAlgorithms::CycleCancelling(const std::shared_ptr<data_structures::Graph>& graph,
        int source, int sink) {
        // get the maximum flow using Edmonds-Karp (feasible flow)
        auto edmonds_karps_result = MaximumFlowAlgorithms::EdmondsKarp(graph, source, sink);
        auto residual_graph = edmonds_karps_result->getGraph();

        // get the negative cycle using Bellman-Ford
        auto bellman_ford_result = GraphBaseAlgorithms::BellmanFord(residual_graph, source);

        // while there is a negative cycle in the residual graph augment the flow
        while (bellman_ford_result->hasNegativeCycle()) {
            auto negative_cycle = bellman_ford_result->getNegativeCycle();
            int residual_capacity { utils::GraphUtils::GetResidualCapacity(residual_graph, negative_cycle) };

            // update the residual capacities and the current flow (augment flow)
            utils::GraphUtils::SendFlowInPathNegativeCosts(residual_graph, negative_cycle, residual_capacity);

            bellman_ford_result = GraphBaseAlgorithms::BellmanFord(residual_graph, source);
        }

        auto optimal_graph = utils::GraphUtils::GetOptimalGraphFromNegativeCosts(residual_graph, graph);

        // get minimum cost
        int minimum_cost { MinimumCostFlowAlgorithms::getMinimumCost(optimal_graph) };

        return std::make_shared<dto::FlowResult>(optimal_graph, minimum_cost);
    }

    std::shared_ptr<dto::FlowResult> MinimumCostFlowAlgorithms::SuccessiveShortestPath(const std::shared_ptr<data_structures::Graph>& graph,
        int source, int sink) {

        // get the residual graph
        auto residual_graph = utils::GraphUtils::GetResidualGraph(graph);
        // get the original graph
        auto original_graph = utils::GraphUtils::GetResidualGraph(graph);
        
        // check if there is a negative cycle, if so Successive Shortest Path cannot be applied
        auto bellman_ford_result = GraphBaseAlgorithms::BellmanFord(residual_graph, source);
        if (bellman_ford_result->hasNegativeCycle()) {
            throw std::invalid_argument("The graph has a negative cycle, Successive Shortest Path cannot be applied");
        }

        // get the maximum flow using Edmonds-Karp (feasible flow)
        auto edmonds_karps_result = MaximumFlowAlgorithms::EdmondsKarp(residual_graph, source, sink);

        int num_nodes { residual_graph->getNumNodes() };
        std::vector<int> imbalance(num_nodes, 0); // imbalance of each node
        imbalance.at(source) = edmonds_karps_result->getFlow(); // imbalance of the source node is the max flow
        imbalance.at(sink) = -edmonds_karps_result->getFlow(); // imbalance of the sink node is the negative max flow

        std::vector<int> potential(num_nodes, 0); // potential of each node 

        // container for the nodes with imbalance > 0
        std::vector<int> positive_imbalance;
        positive_imbalance.push_back(source);

        // container for the nodes with imbalance < 0
        std::vector<int> negative_imbalance;
        negative_imbalance.push_back(sink);

        int flow {};

        // if there are nodes with imbalance > 0 there also must be nodes with imbalance < 0
        while (!positive_imbalance.empty()) {
            int k { positive_imbalance.back() };
            positive_imbalance.pop_back();
            int l { negative_imbalance.back() };
            negative_imbalance.pop_back();

            // determine the shortest path from k to l using Bellman-Ford
            bellman_ford_result = GraphBaseAlgorithms::BellmanFord(residual_graph, k);

            // if a negative cycle is found, throw an exception
            if (bellman_ford_result->hasNegativeCycle()) {
                throw std::runtime_error("Negative cycle found in the residual graph");
            }

            auto distance = bellman_ford_result->getDistance();
            auto parent = bellman_ford_result->getParent();

            // get path between k and l
            auto path = utils::GraphUtils::RetrievePath(parent, k, l);

            // get the minimum residual capacity in the path
            int residual_capacity { utils::GraphUtils::GetResidualCapacity(residual_graph, path) };
            int k_imbalance { imbalance.at(k) };
            int l_imbalance { imbalance.at(l) };

            // get the minimum imbalance between k and l
            int min_imbalance { std::min(k_imbalance, -l_imbalance) };

            // get the augment flow
            int augment_flow { std::min(residual_capacity, min_imbalance) }; 

            // update imbalances
            imbalance.at(k) -= augment_flow;
            if ( imbalance.at(k) != 0) {
                positive_imbalance.push_back(k);
            }
            imbalance.at(l) += augment_flow;
            if (imbalance.at(l)) {
                negative_imbalance.push_back(l);
            }

            // update node potentials
            for (int u = 0; u < residual_graph->getNumNodes(); u++) {
                potential.at(u) = potential.at(u) - distance->at(u);
            }
            
            // send the flow in the path and update the residual graph
            utils::GraphUtils::SendFlowInPathReducedCosts(residual_graph, original_graph, path, augment_flow); 
            
            // update reduced costs
            for (int u = 0; u < residual_graph->getNumNodes(); u++) {
                for (auto edge: *residual_graph->getNodeAdjList(u)) {
                    if (edge.getCost() <= 0) {
                        continue;
                    }
                    int new_weight { edge.getCost() - potential.at(u) + potential.at(edge.getSink()) };
                    residual_graph->setEdgeCost(u, edge.getSink(), new_weight);
                }
            }

            flow += augment_flow;
        }

        if (flow != edmonds_karps_result->getFlow()) {
            throw std::runtime_error("Max flow not reached");
        }

        auto optimal_graph = utils::GraphUtils::GetOptimalGraphFromReducedCosts(residual_graph, original_graph);
        int minimum_cost { MinimumCostFlowAlgorithms::getMinimumCost(optimal_graph) };

        return std::make_shared<dto::FlowResult>(optimal_graph, minimum_cost);
    }

    int MinimumCostFlowAlgorithms::getMinimumCost(const std::shared_ptr<data_structures::Graph>& graph) {
        int minimum_cost {};
        // compute the minimum cost using the optimal graph
        for (int u = 0; u < graph->getNumNodes(); u++) {
            for (auto edge: *graph->getNodeAdjList(u)) {
                minimum_cost +=  edge.getCost() * edge.getCapacity();
            }
        }

        return minimum_cost;
    }

}