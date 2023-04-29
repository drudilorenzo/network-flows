#ifndef NETWORK_FLOWS_BFSRESULT_H
#define NETWORK_FLOWS_BFSRESULT_H

#include <vector>
#include <memory>

namespace dto {
    /**
     * Class that represents the result of the bfs algorithm.
     * It contains the parent of each traversed node and a boolean that indicates if a path between bfs's input source and sink was found.
     */
    class BfsResult {
        public:
            /**
             * Construct a new Bfs Result object
             * 
             * @param path_found true if a path between bfs's input source and sink was found, false otherwise
             * @param parent     the parent of each traversed node
             */
            BfsResult(bool path_found, std::shared_ptr<std::vector<int>> parent);

            /**
             * Returns true if a path between bfs's input source and sink was found, false otherwise
             * 
             * @return true if a path between bfs's input source and sink was found, false otherwise
             */
            [[nodiscard]] bool isPathFound() const;

            /**
             * Returns the parent of each traversed node
             * 
             * @return the parent of each traversed node
             */
            [[nodiscard]] std::shared_ptr<std::vector<int>> getParent() const;
            
    private:
            bool path_found; 
            std::shared_ptr<std::vector<int>> parent;
    };
}

#endif //NETWORK_FLOWS_BFSRESULT_H
