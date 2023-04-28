#include "Edge.h"

namespace data_structures {
    Edge::Edge(const int source, const int sink, const int capacity, const int weight) :
            source(source),
            sink(sink),
            capacity(capacity),
            weight(weight) {}


    int Edge::getSource() {
        return this->source;
    }

    int Edge::getSink() {
        return this->sink;
    }

    int Edge::getCapacity() {
        return this->capacity;
    }

    int Edge::getWeight() {
        return this->weight;
    }

    void Edge::setCapacity(int capacity) {
        this->capacity = capacity;
    }

    std::string Edge::toString() {
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