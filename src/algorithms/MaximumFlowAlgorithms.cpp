#include "MaximumFlowAlgorithms.h"

#include <queue>
#include <limits>
#include <memory>

#include "GraphBaseAlgorithms.h"
#include "utils/GraphUtils.h"

namespace algorithms {
    int MaximumFlowAlgorithms::EdmondsKarp(std::shared_ptr<data_structures::Graph> graph, int source, int sink) {
        int max_flow = 0; // the maximum flow
        int u, v;
        int num_nodes = graph->GetNumNodes();
        auto  parent = make_shared<vector<int>>(num_nodes); // used to reconstruct the path (filled by BFS)
        auto residual_graph = utils::GraphUtils::GetResidualGraph(graph); // the residual graph

        while (GraphBaseAlgorithms::BFS(residual_graph, source, sink, parent)) {

            // find the minimum residual capacity of the edges in the path
            int path_flow = numeric_limits<int>::max();
            for (v = sink; v != source; v = parent->at(v)) {
                u = parent->at(v);
                path_flow = min(path_flow, residual_graph->GetEdge(u, v).GetCapacity());
            }

            // update the residual capacities of the edges and reverse edges along the path
            for (v = sink; v != source; v = parent->at(v)) {
                u = parent->at(v);
                residual_graph->SetEdgeCapacity(u, v, residual_graph->GetEdge(u, v).GetCapacity() - path_flow);
                residual_graph->SetEdgeCapacity(v, u, residual_graph->GetEdge(v, u).GetCapacity() + path_flow);
            }

            // update the max flow
            max_flow += path_flow;
            }
        return max_flow;
    }
}