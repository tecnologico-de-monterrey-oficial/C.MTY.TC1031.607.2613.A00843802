//Isis Krystal Agramón Leal
//A00843802

#pragma once

template <typename T>
struct NodeS {
    T data;
    NodeS<T>* next;

    NodeS(const T& value) : data(value), next(nullptr) {}
    NodeS(const T& value, NodeS<T>* nextNode) : data(value), next(nextNode) {}
};