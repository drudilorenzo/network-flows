#include "FlowResult.h"

#include <utility>

namespace dto {
    FlowResult::FlowResult(std::shared_ptr<data_structures::Graph> graph, int flow) :
        flow(flow),
        graph(std::move(graph)) {}

    std::shared_ptr<data_structures::Graph> FlowResult::getGraph() const {
        return this->graph;
    }

    int FlowResult::getFlow() const {
        return this->flow;
    }
}