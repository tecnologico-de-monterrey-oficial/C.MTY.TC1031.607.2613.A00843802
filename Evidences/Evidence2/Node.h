//Isis Krystal Agramón Leal 
//A0843802
#pragma once

template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(const T& value) : data(value), next(nullptr) {}
    Node(const T& value, Node<T>* nextNode) : data(value), next(nextNode) {} 
};