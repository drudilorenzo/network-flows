#include "Edge.h"

#include <iostream>

namespace data_structures {
    Edge::Edge(const int head, const int tail, const int capacity, const int weight) :
            head(head),
            tail(tail),
            capacity(capacity),
            weight(weight) {}


    int Edge::GetHead() {
        return this->head;
    }

    int Edge::GetTail() {
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

    void Edge::ToString() {
        printf("Edge: head = %d, tail = %d, capacity = %d, weight = %d\n", head, tail, capacity, weight);
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