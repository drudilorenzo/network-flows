#ifndef MINIMUM_COST_FLOWS_PROBLEM_DIJKSTRARESULT_H
#define MINIMUM_COST_FLOWS_PROBLEM_DIJKSTRARESULT_H

#include <vector>
#include <memory>

namespace dto {
    /**
     * Class that represents the result of the Dijkstra algorithm.
     * The result contains the distance and the parent of each node.
     */
    class DijkstraResult {
    public:
        /**
         * Dijkstra result constructor.
         * 
         * @param distance the distance of each vertex from the source node
         * @param parent   the parent of each node
         */
        DijkstraResult(std::shared_ptr<std::vector<int>> distance, std::shared_ptr<std::vector<int>> parent);

        /**
         * Returns the distance of each vertex from the source vertex.
         * 
         * @return the distance of each vertex from the source vertex
         */
        [[maybe_unused]] std::shared_ptr<std::vector<int>> getDistance();

        /**
         * Returns the parent of each vertex.
         * 
         * @return the the parent of each vertex
         */
        [[maybe_unused]] std::shared_ptr<std::vector<int>> getParent();
        
    private:
        std::shared_ptr<std::vector<int>> parent;
        std::shared_ptr<std::vector<int>> distance;
    };
}

#endif //MINIMUM_COST_FLOWS_PROBLEM_DIJKSTRARESULT_H
