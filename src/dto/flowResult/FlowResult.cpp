#include "FlowResult.h"

namespace dto {
    FlowResult::FlowResult(std::shared_ptr<data_structures::graph> graph, int flow) {
        this->graph = graph;
        this->flow = flow;
    }

    std::shared_ptr<data_structures::graph> FlowResult::getGraph() const {
        return this->graph;
    }

    int FlowResult::getFlow() const {
        return this->flow;
    }
}