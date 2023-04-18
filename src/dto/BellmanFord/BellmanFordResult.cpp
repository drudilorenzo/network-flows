#include "BellmanFordResult.h"

namespace dto {
    BellmanFordResult::BellmanFordResult(std::shared_ptr<std::vector<int>> negative_cycle) {
        this->negative_cycle = negative_cycle;
        this->distance = std::make_shared<std::vector<int>>();
        this->parent = std::make_shared<std::vector<int>>();
    }

    BellmanFordResult::BellmanFordResult(std::shared_ptr<std::vector<int>> distance, std::shared_ptr<std::vector<int>> parent) {
        this->negative_cycle = std::make_shared<std::vector<int>>();
        this->distance = distance;
        this->parent = parent;
    }

    bool BellmanFordResult::hasNegativeCycle() {
        return !this->negative_cycle->empty();
    }

    std::shared_ptr<std::vector<int>> BellmanFordResult::getNegativeCycle() {
        return this->negative_cycle;
    }

    std::shared_ptr<std::vector<int>> BellmanFordResult::getDistance() {
        return this->distance;
    }

    std::shared_ptr<std::vector<int>> BellmanFordResult::getParent() {
        return this->parent;
    }
} 
