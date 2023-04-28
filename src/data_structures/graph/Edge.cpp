#include "Edge.h"

namespace data_structures {
    edge::edge(const int source, const int sink, const int capacity, const int weight) :
            source(source),
            sink(sink),
            capacity(capacity),
            weight(weight) {}


    int edge::getSource() {
        return this->source;
    }

    int edge::getSink() {
        return this->sink;
    }

    int edge::getCapacity() {
        return this->capacity;
    }

    int edge::getWeight() {
        return this->weight;
    }

    void edge::setCapacity(int capacity) {
        this->capacity = capacity;
    }

    std::string edge::toString() {
        std::string s = "{";
        s += "\"Source\": " + std::to_string(this->source) + ", ";
        s += "\"Sink\": " + std::to_string(this->sink) + ", ";
        s += "\"Capacity\": " + std::to_string(this->capacity) + ", ";
        s += "\"Weight\": " + std::to_string(this->weight);
        s += "}";
        return s;
    }

    bool edge::operator==(const edge& other) const {
        if (this == &other) {
            return true;
        }
        if (this == nullptr || &other == nullptr) {
            return false;
        }
        return this->source == other.source && this->sink == other.sink && this->capacity == other.capacity && this->weight == other.weight;
    }

    bool edge::operator!=(const edge& other) const {
        return !(*this == other);
    }
}