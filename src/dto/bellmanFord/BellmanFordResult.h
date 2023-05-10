#ifndef MINIMUM_COST_FLOWS_PROBLEM_BELLMANFORDRESULT_H
#define MINIMUM_COST_FLOWS_PROBLEM_BELLMANFORDRESULT_H

#include <vector>
#include <memory>

namespace dto {
    /**
     * Class that represents the result of the Bellman-Ford algorithm.
     * In case the graph contains a negative cycle, the result contains the negative cycle.
     * Otherwise, the result contains the distance and the parent of each node.
     *  
     */
    class BellmanFordResult {
    public:
        /**
         * Constructor for the case when the graph contains a negative cycle.
         * Store the negative cycle.
         * 
         * @param negative_cycle the negative cycle
         */
        explicit BellmanFordResult(std::shared_ptr<std::vector<int>> negative_cycle);

        /**
         * Constructor for the case when the graph contains no negative cycle.
         * Normal Bellman-Ford algorithm result containing distances and parent nodes.
         * 
         * @param distance the distance of each vertex from the source node
         * @param parent   the parent of each node
         */
        BellmanFordResult(std::shared_ptr<std::vector<int>> distance, std::shared_ptr<std::vector<int>> parent);

        /**
         * Returns true if the graph contains a negative cycle.
         * 
         * @return true if the graph contains a negative cycle, false otherwise.
         */
        bool hasNegativeCycle();

        /**
         * Returns the negative cycle.
         * If the graph does not contain a negative cycle, returns an empty vector.
         * 
         * @return the negative cycle
         */
        std::shared_ptr<std::vector<int>> getNegativeCycle();

        /**
         * Returns the distance of each vertex from the source vertex.
         * If the graph contains a negative cycle, returns an empty vector.
         * 
         * @return the distance of each vertex from the source vertex
         */
        [[maybe_unused]] std::shared_ptr<std::vector<int>> getDistance();

        /**
         * Returns the parent of each vertex.
         * If the graph contains a negative cycle, returns an empty vector.
         * 
         * @return the the parent of each vertex
         */
        [[maybe_unused]] std::shared_ptr<std::vector<int>> getParent();
        
    private:
        std::shared_ptr<std::vector<int>> parent;
        std::shared_ptr<std::vector<int>> distance;
        std::shared_ptr<std::vector<int>> negative_cycle;
    };
}

#endif //MINIMUM_COST_FLOWS_PROBLEM_BELLMANFORDRESULT_H
