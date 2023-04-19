#include "Edge.h"

namespace data_structures {
    Edge::Edge(const int source, const int sink, const int capacity, const int weight) :
            source(source),
            sink(sink),
            capacity(capacity),
            weight(weight) {}


    int Edge::GetSource() {
        return this->source;
    }

    int Edge::GetSink() {
        return this->sink;
    }

    int Edge::GetCapacity() {
        return this->capacity;
    }

    int Edge::GetWeight() {
        return this->weight;
    }

    void Edge::SetCapacity(int capacity) {
        this->capacity = capacity;
    }

    std::string Edge::ToString() {
        std::string s = "{";
        s += "\"Source\": " + std::to_string(this->source) + ", ";
        s += "\"Sink\": " + std::to_string(this->sink) + ", ";
        s += "\"Capacity\": " + std::to_string(this->capacity) + ", ";
        s += "\"Weight\": " + std::to_string(this->weight);
        s += "}";
        return s;
    }

    bool Edge::operator==(const Edge& other) const {
        if (this == &other) {
            return true;
        }
        if (this == nullptr || &other == nullptr) {
            return false;
        }
        return this->source == other.source && this->sink == other.sink && this->capacity == other.capacity && this->weight == other.weight;
    }

    bool Edge::operator!=(const Edge& other) const {
        return !(*this == other);
    }
}