#include "BellmanFordResult.h"

#include <utility>

namespace dto {
    BellmanFordResult::BellmanFordResult(std::shared_ptr<std::vector<int>> negative_cycle) :
        negative_cycle(std::move(negative_cycle)) {
            this->distance = std::make_shared<std::vector<int>>();
            this->parent = std::make_shared<std::vector<int>>();
    }

    BellmanFordResult::BellmanFordResult(std::shared_ptr<std::vector<int>> distance, std::shared_ptr<std::vector<int>> parent) :
        parent(std::move(parent)),
        distance(std::move(distance)) {
            this->negative_cycle = std::make_shared<std::vector<int>>();
    }

    bool BellmanFordResult::hasNegativeCycle() {
        return !this->negative_cycle->empty();
    }

    std::shared_ptr<std::vector<int>> BellmanFordResult::getNegativeCycle() {
        return this->negative_cycle;
    }

    [[maybe_unused]] std::shared_ptr<std::vector<int>> BellmanFordResult::getDistance() {
        return this->distance;
    }

    [[maybe_unused]] std::shared_ptr<std::vector<int>> BellmanFordResult::getParent() {
        return this->parent;
    }
} 
