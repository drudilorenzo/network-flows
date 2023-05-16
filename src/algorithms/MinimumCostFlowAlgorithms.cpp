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
        
        // get the residual graph
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

       // get the optimal graph
        auto optimal_graph = utils::GraphUtils::GetOptimalGraph(residual_graph, graph);

        // get minimum cost
        int minimum_cost { MinimumCostFlowAlgorithms::getMinimumCost(optimal_graph) };

        return std::make_shared<dto::FlowResult>(optimal_graph, minimum_cost);
    }

    std::shared_ptr<dto::FlowResult> MinimumCostFlowAlgorithms::SuccessiveShortestPath(const std::shared_ptr<data_structures::Graph>& graph,
        int source, int sink) {

        // get the residual graph
        auto residual_graph = utils::GraphUtils::GetResidualGraph(graph);

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

            auto dijkstra_result = GraphBaseAlgorithms::Dijkstra(residual_graph, k);
            auto distance = dijkstra_result->getDistance();
            auto parent = dijkstra_result->getParent();

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
            for (int u = 0; u < num_nodes; u++) {
                potential.at(u) = potential.at(u) - distance->at(u);
            }
            
            // send the flow in the path and update the residual graph
            utils::GraphUtils::SendFlowInPathReducedCosts(residual_graph, path, augment_flow); 
            
            // update reduced costs
            for (int u = 0; u < num_nodes; u++) {
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

        auto optimal_graph = utils::GraphUtils::GetOptimalGraph(residual_graph, graph);
        int minimum_cost { MinimumCostFlowAlgorithms::getMinimumCost(optimal_graph) };

        return std::make_shared<dto::FlowResult>(optimal_graph, minimum_cost);
    }

    std::shared_ptr<dto::FlowResult> MinimumCostFlowAlgorithms::PrimalDual(const std::shared_ptr<data_structures::Graph>& graph, int source, int sink) {
        
        // get the residual graph
        auto residual_graph = utils::GraphUtils::GetResidualGraph(graph);

        // check if there is a negative cycle, if so Successive Shortest Path cannot be applied
        auto bellman_ford_result = GraphBaseAlgorithms::BellmanFord(residual_graph, source);
        if (bellman_ford_result->hasNegativeCycle()) {
            throw std::invalid_argument("The graph has a negative cycle, Successive Shortest Path cannot be applied");
        }

        // get the maximum flow using Edmonds-Karp
        auto edmonds_karps_result = MaximumFlowAlgorithms::EdmondsKarp(residual_graph, source, sink);

        int num_nodes { residual_graph->getNumNodes() + 2 };

        int current_imbalance { edmonds_karps_result->getFlow() };  // current imbalance
        std::vector<int> potential(num_nodes, 0);                   // potential of each node 
        int flow {};                                                // current flow

        // add source edge
        auto new_source { num_nodes - 2 };
        residual_graph->addEdge(new_source, source, current_imbalance, 0);

        // add sink edge
        auto new_sink { num_nodes - 1 };
        residual_graph->addEdge(sink, new_sink, current_imbalance, 0);

        // get the original graph
        auto original_graph = std::make_shared<data_structures::Graph>(residual_graph);

        while (current_imbalance > 0) {
            // get the shortest path from source to sink
            auto dijkstra_result = GraphBaseAlgorithms::Dijkstra(residual_graph, new_source);
            auto distance = dijkstra_result->getDistance();
            auto parent = dijkstra_result->getParent();

            for (int u = 0; u < num_nodes; u++) {
                potential.at(u) = potential.at(u) - distance->at(u);
            }
            
            // update reduced costs
            for (int u = 0; u < num_nodes; u++) {
                for (auto edge: *residual_graph->getNodeAdjList(u)) {
                    if (edge.getCost() <= 0) {
                        continue;
                    }
                    int new_weight { edge.getCost() - potential.at(u) + potential.at(edge.getSink()) };
                    residual_graph->setEdgeCost(u, edge.getSink(), new_weight);
                }
            }
            // get admissible network 
            auto admissible_graph = utils::GraphUtils::GetAdmissibleGraph(residual_graph);
            
            auto flow_result = MaximumFlowAlgorithms::EdmondsKarp(admissible_graph, new_source, new_sink);
            int admissible_flow { flow_result->getFlow() };

            auto flow_graph =  utils::GraphUtils::GetOptimalGraph(flow_result->getGraph(), residual_graph);
            flow += admissible_flow;

            // update current imbalance
            current_imbalance -= admissible_flow;

            // update residual graph with the flow found
            // iterate over all the edges of flow_graph
            for (int u = 0; u < num_nodes; u++) {
                for (auto edge: *flow_graph->getNodeAdjList(u)) {

                    int source { edge.getSource() };
                    int sink { edge.getSink() };
                    int edge_flow { edge.getCapacity() };

                    // subtract flow from the residual capacity of the edge
                    int capacity { residual_graph->getEdge(source, sink).getCapacity() };

                    if (capacity < edge_flow) {
                        throw std::invalid_argument("The flow is greater than the residual capacity of the edge");
                    }

                    capacity -= edge_flow;
                    // if residual capacity is 0, remove the edge
                    if (!capacity) {
                        residual_graph->removeEdge(source, sink);
                    } else {
                        residual_graph->setEdgeCapacity(source, sink, capacity);
                    }

                    // if the reverse edge does not exist, add it
                    if (edge_flow) {
                        if (!residual_graph->hasEdge(sink, source)) {
                            residual_graph->addEdge(sink, source, edge_flow, 0);
                        } else {
                            residual_graph->setEdgeCapacity(sink, source, residual_graph->getEdge(sink, source).getCapacity() + edge_flow);
                        }
                    }
                }
            }
        }

        if (flow != edmonds_karps_result->getFlow()) {
            throw std::runtime_error("Max flow not reached");
        }

        // remove the source and sink edges (both directions)
        if (residual_graph->hasEdge(new_source, source)) {
            residual_graph->removeEdge(new_source, source);
        }
        if (residual_graph->hasEdge(source, new_source)) {
            residual_graph->removeEdge(source, new_source);
        }
        if (residual_graph->hasEdge(sink, new_sink)) {
            residual_graph->removeEdge(sink, new_sink);
        }
        if (residual_graph->hasEdge(new_sink, sink)) {
            residual_graph->removeEdge(new_sink, sink);
        }

        auto optimal_graph = utils::GraphUtils::GetOptimalGraph(residual_graph, graph);
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