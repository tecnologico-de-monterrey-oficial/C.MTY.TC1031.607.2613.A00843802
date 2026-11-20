//Isis Krystal Agramón Leal
//A0843802

#pragma once

template <typename T>
struct NodeT {
    T data;
    int count;
    NodeT<T>* left;
    NodeT<T>* right;

    NodeT(const T& value) : data(value), count(1), left(nullptr), right(nullptr) {}
    NodeT(const T& value, NodeT<T>* leftNode, NodeT<T>* rightNode) : data(value), count(1), left(leftNode), right(rightNode) {}
};