#include "DijkstraResult.h"

#include <memory>
#include <utility>

namespace dto {
    DijkstraResult::DijkstraResult(std::shared_ptr<std::vector<int>> distance, std::shared_ptr<std::vector<int>> parent) :
        parent(std::move(parent)),
        distance(std::move(distance)) {}

    [[maybe_unused]] std::shared_ptr<std::vector<int>> DijkstraResult::getDistance() {
        return this->distance;
    }

    [[maybe_unused]] std::shared_ptr<std::vector<int>> DijkstraResult::getParent() {
        return this->parent;
    }
} 
