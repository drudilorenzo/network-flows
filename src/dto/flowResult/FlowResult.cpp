#include "FlowResult.h"

#include <utility>

namespace dto {
    FlowResult::FlowResult(std::shared_ptr<data_structures::Graph> graph, int flow) {
        this->graph = std::move(graph);
        this->flow = flow;
    }

    std::shared_ptr<data_structures::Graph> FlowResult::getGraph() const {
        return this->graph;
    }

    int FlowResult::getFlow() const {
        return this->flow;
    }
}