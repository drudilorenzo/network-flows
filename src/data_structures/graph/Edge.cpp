#include "Edge.h"

namespace data_structures {
    Edge::Edge(const int source, const int sink, const int capacity, const int cost) :
            source(source),
            sink(sink),
            capacity(capacity),
            cost(cost) {}


    int Edge::getSource() const {
        return this->source;
    }

    int Edge::getSink() const {
        return this->sink;
    }

    int Edge::getCapacity() const {
        return this->capacity;
    }

    int Edge::getCost() const {
        return this->cost;
    }

    void Edge::setCapacity(int new_capacity) {
        this->capacity = new_capacity;
    }

    void Edge::setCost(int new_cost) {
        this->cost = new_cost;
    }

    std::string Edge::toString() const {
        std::string s = "{";
        s += "\"Source\": " + std::to_string(this->source) + ", ";
        s += "\"Sink\": " + std::to_string(this->sink) + ", ";
        s += "\"Capacity\": " + std::to_string(this->capacity) + ", ";
        s += "\"Cost\": " + std::to_string(this->cost);
        s += "}";
        return s;
    }

    bool Edge::operator==(const Edge& other) const {
        if (this == &other) {
            return true;
        }
        return this->source == other.source && this->sink == other.sink 
            && this->capacity == other.capacity && this->cost == other.cost;
    }

    bool Edge::operator!=(const Edge& other) const {
        return !(*this == other);
    }
}