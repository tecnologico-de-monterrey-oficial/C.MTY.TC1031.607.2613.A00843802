#pragma once

template <typename>
    struct node{
        T data;
        share_ptr<Node<T>> next;

        Node(const T& value) : data(value), next (nullptr);

        Node(const T& value <Node<T>>nextNode) : data(value), next
    };