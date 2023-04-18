#include "Edge.h"

#include <iostream>

namespace data_structures {
    Edge::Edge(const int source, const int sink, const int capacity, const int weight) :
            head(source),
            tail(sink),
            capacity(capacity),
            weight(weight) {}


    int Edge::GetSource() {
        return this->head;
    }

    int Edge::GetSink() {
        return this->tail;
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
        s += "\"Source\": " + std::to_string(this->head) + ", ";
        s += "\"Sink\": " + std::to_string(this->tail) + ", ";
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
        return this->head == other.head && this->tail == other.tail && this->capacity == other.capacity && this->weight == other.weight;
    }

    bool Edge::operator!=(const Edge& other) const {
        return !(*this == other);
    }
}