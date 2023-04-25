#include "MaximumFlowAlgorithms.h"

#include <queue>
#include <memory>

#include "GraphBaseAlgorithms.h"
#include "utils/GraphUtils.h"

namespace algorithms {
     std::shared_ptr<dto::EdmondsKarpResult> MaximumFlowAlgorithms::EdmondsKarp(std::shared_ptr<data_structures::Graph> graph, int source, int sink) {
        int max_flow = 0; // the maximum flow
        int num_nodes = graph->GetNumNodes();
        auto parent = std::make_shared<std::vector<int>>(num_nodes); // used to reconstruct the path (filled by BFS)
        auto residual_graph = utils::GraphUtils::GetResidualGraph(graph); // the residual graph

        while (GraphBaseAlgorithms::BFS(residual_graph, source, sink, parent)) {
            // construct the path from the parent array
            auto path = utils::GraphUtils::RetrievePath(parent, sink);

            // find the minimum residual capacity of the edges in the path
            auto path_flow = utils::GraphUtils::GetResidualCapacity(residual_graph, path);

            // update the residual capacities of the edges and reverse edges along the path
            utils::GraphUtils::SendFlowInPath(residual_graph, path, path_flow);

            // update the max flow
            max_flow += path_flow;
        }

        // Build the result with: residual graph and max flow
        return std::make_shared<dto::EdmondsKarpResult>(residual_graph, max_flow);
    }
}