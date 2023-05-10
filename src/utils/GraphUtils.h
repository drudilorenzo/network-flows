#ifndef MINIMUM_COST_FLOWS_PROBLEM_GRAPHUTILS_H
#define MINIMUM_COST_FLOWS_PROBLEM_GRAPHUTILS_H

#include "data_structures/graph/Graph.h"

#include <string>

namespace  utils {
    /**
     * Graph's utility functions
     */
    class GraphUtils {
        public:
            /**
             * Create graph from json and return it.
             * USE THE FOLLOWING FORMAT:
             * {
             *  "Num_nodes": -,
             *    "Edges": [
             *        {
             *        "Source": -,
             *        "Sink": -,
             *        "Capacity": -,
             *        "Cost": -
             *       },
             *      ...
             *   ]
             * }
             * 
             * The graph is directed.
             * All the nodes must be numbered from 0 to Num_nodes - 1 using consecutive numbers.
             * All the values must be positive integer.
             * 
             * (See data folder to see some examples of json file).
             *
             * @param filename name of the file to read
             * 
             * @return graph created from the file inputs
             * 
             * @throws invalid_argument if the file does not exist
             * @throws invalid_argument if the json is not formatted correctly
             */
            static std::shared_ptr<data_structures::Graph> CreateGraphFromJSON(const std::string& filename);

            /**
             * Get the residual graph of the given graph.
             * The residual graph is a graph that indicates how much flow can be pushed through the edges.
             * For each edge u -> v, the residual graph has an edge v -> u with capacity equal to the current pushed flow.
             * Residual graph cannot contains anti-parallels edges, they are handled using artificial nodes.
             * (Anti-parallel explained: https://www.hackerearth.com/practice/algorithms/graphs/maximum-flow/tutorial/)
             * 
             * (see: https://www.hackerearth.com/practice/algorithms/graphs/maximum-flow/tutorial/)
             *
             * @param graph the graph to get the residual graph from
             * 
             * @return the residual graph
             */
            static std::shared_ptr<data_structures::Graph> GetResidualGraph(const std::shared_ptr<data_structures::Graph>& graph);

            /**
             * Get the optimal graph from a residual graph built with negative costs (see Cycle Cancelling algorithm).
             * Used for algorithms that use negative costs for detecting the residual edges.
             * The residual edges are the edge containing the current flow in the opposite edge sink-source.
             * 
             * It converts te residual graph into the optimal graph.
             * The optimal graph is the graph which contains only the starting edges. 
             *
             * (see: https://www.hackerearth.com/practice/algorithms/graphs/maximum-flow/tutorial/)
             *
             * @param residual_graph the residual graph from which get the optimal graph
             * @param graph          the original graph used for add the missing edges
             * 
             * @return the optimal graph
             */
            static std::shared_ptr<data_structures::Graph> GetOptimalGraphFromNegativeCosts(const std::shared_ptr<data_structures::Graph>& residual_graph,
                const std::shared_ptr<data_structures::Graph>& graph);

            /**
             * Get the optimal graph from a residual graph built with reduced costs (see Successive Shortest Path algorithm).
             * When algorithms (as Successive Shortest Path) use reduced costs, in the residual networks there are no
             * edges with negative costs.
             * So, to the recognize the residual edges, we need to check if, in the original graph, there is the edge.
             * If not, it means that the edge is a residual edge and the original graph contains its opposite.
             * 
             * It converts te residual graph into the optimal graph.
             * The optimal graph is the graph which contains only the starting edges. 
             *
             * (see: https://www.hackerearth.com/practice/algorithms/graphs/maximum-flow/tutorial/)
             *
             * @param residual_graph the residual graph from which get the optimal graph
             * @param graph          the original graph used for add the missing edges
             * 
             * @return the optimal graph
             */
            static std::shared_ptr<data_structures::Graph> GetOptimalGraphFromReducedCosts(const std::shared_ptr<data_structures::Graph>& residual_graph,
                const std::shared_ptr<data_structures::Graph>& graph);

            /**
             * Retrieve the path from the input node to the source (node with -1 as parent).
             *
             * @param parent the parent vector, where parent[i] is the parent of node i
             * @param source the source node of the path
             * @param sink   the sink node of the path
             * 
             * @return the path from input node to the source node (node with -1 as parent)
             */
            static std::shared_ptr<std::vector<int>> RetrievePath(const std::shared_ptr<std::vector<int>>& parent, int source, int sink);

            /**
             * Get the residual capacity of the path in the residual_graph.
             * The residual capacity is the minimum residual capacity of the edges in the path.
             *
             * @param residual_graph the residual_graph
             * @param path           the path
             * 
             * @return the residual capacity of the path
             */
            static int GetResidualCapacity(const std::shared_ptr<data_structures::Graph>& residual_graph, const std::shared_ptr<std::vector<int>>& path);

            /**
             * Send flow in a path of edges of a residual graph with negative cost edges.
             * See the function above for more details about the graph.
             *
             * @param residual_graph the residual residual_graph (IT MUST BE A RESIDUAL GRAPH WITH NEGATIVE COST EDGES, see the function above)
             * @param path           the path of the edge to update
             * @param flow           the flow to send
             * 
             * @throws invalid_argument if an edge residual capacity is less than the flow to send
             */
            static void SendFlowInPathNegativeCosts(const std::shared_ptr<data_structures::Graph>& residual_graph,
                const std::shared_ptr<std::vector<int>>& path, int flow);
    
            /**
             * Send flow in a path of edges of a residual graph with reduced cost edges.
             * See the function above for more details about the graph.
             *
             * @param residual_graph the residual residual_graph (IT MUST BE A RESIDUAL GRAPH WITH REDUCED COSTS, see the function above)
             * @param original_graph the original graph used to recognize the residual edges
             * @param path           the path of the edge to update
             * @param flow           the flow to send
             * 
             * @throws invalid_argument if an edge residual capacity is less than the flow to send
             */
            static void SendFlowInPathReducedCosts(const std::shared_ptr<data_structures::Graph>& residual_graph,
                const std::shared_ptr<data_structures::Graph>& original_graph, const std::shared_ptr<std::vector<int>>& path, int flow);
    };
}

#endif //MINIMUM_COST_FLOWS_PROBLEM_GRAPHUTILS_H
