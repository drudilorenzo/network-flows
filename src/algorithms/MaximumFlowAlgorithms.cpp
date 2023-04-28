#include "MaximumFlowAlgorithms.h"

#include "GraphBaseAlgorithms.h"
#include "utils/GraphUtils.h"

#include <queue>
#include <memory>

namespace algorithms {
     std::shared_ptr<dto::FlowResult> MaximumFlowAlgorithms::EdmondsKarp(std::shared_ptr<data_structures::Graph> graph, int source, int sink) {
        int max_flow {};
        int num_nodes { graph->getNumNodes() };
         // used to reconstruct the path (filled by BFS)
        auto parent = std::make_shared<std::vector<int>>(num_nodes);
        // the residual graph (at the beginning it is the same as the original graph)
        auto residual_graph = utils::GraphUtils::GetResidualGraph(graph); 

        while (GraphBaseAlgorithms::BFS(residual_graph, source, sink, parent)) {
            
            // reconstruct the path from source to sink
            auto path = utils::GraphUtils::RetrievePath(parent, sink);

            // find the minimum residual capacity of the edges in the path
            auto path_flow = utils::GraphUtils::GetResidualCapacity(residual_graph, path);

            // update the residual capacities and the current flow
            utils::GraphUtils::SendFlowInPath(residual_graph, path, path_flow);

            // update the max flow
            max_flow += path_flow;
        }

        // Build the result with residual graph and max flow
        return std::make_shared<dto::FlowResult>(residual_graph, max_flow);
    }
}