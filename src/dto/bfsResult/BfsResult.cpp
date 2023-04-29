#include "BfsResult.h"

#include <utility>

namespace dto {
    BfsResult::BfsResult(bool path_found, std::shared_ptr<std::vector<int>> parent) : 
        path_found(path_found),
        parent(std::move(parent)) {}

    bool BfsResult::isPathFound() const {
        return this->path_found;
    }

    std::shared_ptr<std::vector<int>> BfsResult::getParent() const {
        return this->parent;
    }
}