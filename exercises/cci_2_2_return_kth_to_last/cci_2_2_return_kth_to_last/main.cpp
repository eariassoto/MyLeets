// Copyright (c) 2021 Emmanuel Arias

#include <common_lib/linked_list.hpp>
#include <spdlog/spdlog.h>

#include <set>

/*
 * For this exercise we can use offset pointers. What we want to do here is to
 * try to move a pointer k positions. If we cannot do it we do an early return.
 * his will give us the offset distance we want to move all the way to the end.
 * After this we will put the second pointer to the head of the list and move both
 * pointers until the first one reaches the end.
 *
 * Time complexity: O(N)
 * Space complexity: O(1)
 */

LinkedList::Node<int>* FindKthToLast(LinkedList::Node<int>* root, int k) {
    int currentIndex = 0;

    LinkedList::Node<int>* offsetPointer = root;
    LinkedList::Node<int>* kthNodePtr = root;

    for (int i = 0; i < k; ++i) {
        if (offsetPointer == nullptr) {
            return nullptr;
        }
        offsetPointer = offsetPointer->Next;
    }

    while (offsetPointer != nullptr) {
        offsetPointer = offsetPointer->Next;

        // This is safe given that we already when through these nodes
        kthNodePtr = kthNodePtr->Next;
    }

    return kthNodePtr;
}

int main(int argc, char* argv[]) {
    LinkedList::Node<int>* my_list = nullptr;

    my_list = LinkedList::InsertEnd(my_list, 1);
    my_list = LinkedList::InsertEnd(my_list, 2);
    my_list = LinkedList::InsertEnd(my_list, 2);
    my_list = LinkedList::InsertEnd(my_list, 2);
    my_list = LinkedList::InsertEnd(my_list, 3);
    my_list = LinkedList::InsertEnd(my_list, 4);
    my_list = LinkedList::InsertEnd(my_list, 5);
    my_list = LinkedList::InsertEnd(my_list, 4);

    LinkedList::PrintList(my_list);

    int kth = 3;
    auto result = FindKthToLast(my_list, kth);
    if (result != nullptr) {
        spdlog::info(
            "The {}th element from the last element of the list is: {}", kth,
            result->Data);
    } else {
        spdlog::info(
            "The {}th element from the last element of the list does not "
            "exists",
            kth);
    }

    kth = 7;
    result = FindKthToLast(my_list, kth);
    if (result != nullptr) {
        spdlog::info(
            "The {}th element from the last element of the list is: {}", kth,
            result->Data);
    } else {
        spdlog::info(
            "The {}th element from the last element of the list does not "
            "exists",
            kth);
    }

    kth = 18;
    result = FindKthToLast(my_list, kth);
    if (result != nullptr) {
        spdlog::info(
            "The {}th element from the last element of the list is: {}", kth,
            result->Data);
    } else {
        spdlog::info(
            "The {}th element from the last element of the list does not "
            "exists",
            kth);
    }

    LinkedList::DeleteList(my_list);

    return 0;
}
