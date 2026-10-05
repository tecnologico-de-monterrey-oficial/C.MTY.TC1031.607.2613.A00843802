//Isis Krystal Agramón Leal
//A00843802
#pragma once

template <typename T>
struct NodeQ {
    T data;
    NodeQ<T>* next;

    NodeQ(const T& value) : data(value), next(nullptr) {}
    NodeQ(const T& value, NodeQ<T>* nextNode) : data(value), next(nextNode) {}
};