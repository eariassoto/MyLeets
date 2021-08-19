// Copyright (c) 2021 Emmanuel Arias
#pragma once

#include <spdlog/spdlog.h>
#include <sstream>

namespace LinkedList {

template <typename T>
struct Node {
    Node() = delete;
    ~Node() { spdlog::trace("Node dtor"); }

    Node(T&& data) : Data{data}, Next{nullptr} {}
    Node(const T& data) : Data{data}, Next{nullptr} {}

    Node(T&& data, Node* next) : Data{data}, Next{next} {}
    Node(const T& data, Node* next) : Data{data}, Next{next} {}

    T Data;
    Node* Next;
};

template <typename T>
Node<T>* InsertFront(Node<T>* root, T&& value) {
    if (root == nullptr) {
        return new Node<T>(std::move(value));
    }
    return new Node<T>(std::move(value), root);
}

template <typename T>
Node<T>* InsertEnd(Node<T>* root, T&& value) {
    if (root == nullptr) {
        return new Node<T>(std::move(value));
    }
    auto auxPtr = root;
    while (auxPtr->Next != nullptr) {
        auxPtr = auxPtr->Next;
    }

    auto newNode = new Node<T>(std::move(value));
    auxPtr->Next = newNode;

    return root;
}

template <typename T>
void DeleteList(Node<T>* root) {
    auto auxPtr = root;
    while (auxPtr != nullptr) {
        // Save next pointer before calling dtor
        auto nextNode = auxPtr->Next;
        delete auxPtr;
        auxPtr = nextNode;
    }
}

template <typename T>
void PrintList(Node<T>* root) {
    std::stringstream outStream;

    auto auxPtr = root;
    while (auxPtr != nullptr) {
        outStream << auxPtr->Data;
        if (auxPtr->Next != nullptr) {
            outStream << " -> ";
        }

        auxPtr = auxPtr->Next;
    }
    spdlog::info("{}", outStream.str());
}

template <typename T>
int Length(Node<T>* root) {
    int length = 0;

    auto auxPtr = root;
    while (auxPtr != nullptr) {
        ++length;
        auxPtr = auxPtr->Next;
    }
    return length;
}

};  // namespace LinkedList