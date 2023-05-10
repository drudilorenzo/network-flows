#include "Edge.h"

namespace data_structures {
    Edge::Edge(const int source, const int sink, const int capacity, const int weight) :
            source(source),
            sink(sink),
            capacity(capacity),
            weight(weight) {}


    int Edge::getSource() const {
        return this->source;
    }

    int Edge::getSink() const {
        return this->sink;
    }

    int Edge::getCapacity() const {
        return this->capacity;
    }

    int Edge::getWeight() const {
        return this->weight;
    }

    void Edge::setCapacity(int new_capacity) {
        this->capacity = new_capacity;
    }

    void Edge::setWeight(int new_weight) {
        this->weight = new_weight;
    }

    std::string Edge::toString() const {
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
        return this->source == other.source && this->sink == other.sink && this->capacity == other.capacity && this->weight == other.weight;
    }

    bool Edge::operator!=(const Edge& other) const {
        return !(*this == other);
    }
}