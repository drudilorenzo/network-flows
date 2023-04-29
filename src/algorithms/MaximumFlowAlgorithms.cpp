#include "MaximumFlowAlgorithms.h"

#include "utils/GraphUtils.h"
#include "GraphBaseAlgorithms.h"

#include <memory>

namespace algorithms {
     std::shared_ptr<dto::FlowResult> MaximumFlowAlgorithms::EdmondsKarp(const std::shared_ptr<data_structures::Graph>& graph, int source, int sink) {
        int max_flow {};

        // the residual graph (if needed anti-parallel edges are removed using artificial nodes)
        auto residual_graph = utils::GraphUtils::GetResidualGraph(graph);

        auto bfs_result = GraphBaseAlgorithms::BFS(residual_graph, source, sink);

        // while there is a path from source to sink
        while (bfs_result->isPathFound()) {

            auto parent = bfs_result->getParent();
            
            // reconstruct the path from source to sink
            auto path = utils::GraphUtils::RetrievePath(parent, sink);

            // find the minimum residual capacity of the edges in the path
            auto path_flow = utils::GraphUtils::GetResidualCapacity(residual_graph, path);

            // update the residual capacities and the current flow
            utils::GraphUtils::SendFlowInPath(residual_graph, path, path_flow);

            // update the max flow
            max_flow += path_flow;

            // find a new path from source to sink
            bfs_result = GraphBaseAlgorithms::BFS(residual_graph, source, sink);
        }

        // Build the result with residual graph and max flow
        return std::make_shared<dto::FlowResult>(residual_graph, max_flow);
    }
}