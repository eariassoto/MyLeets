// Copyright (c) 2021 Emmanuel Arias

#include <common_lib/linked_list.hpp>
#include <spdlog/spdlog.h>

#include <set>

/*
 * If we are allowed to allocate extra memory we can have a lookup set and
 * delete in place when we find the value in the set. This solution is time O(N)
 * and space O(N).
 * 
 * Because this is a single linked list we need to keep track of the previous node
 *
 * If we do not want allocation we need to iterate the entire list for every
 * item, which makes time complexity O(N^2)
 */

void DeleteDuplicatesFromList(LinkedList::Node<int>* root) {
    std::set<int> lookupSet;

    // We are safe here because the first list element will always be unique
    LinkedList::Node<int>* auxPrevPtr = nullptr;
    LinkedList::Node<int>* auxPtr = root;

    while (auxPtr != nullptr) {
        auto [it, gotInserted] = lookupSet.insert(auxPtr->Data);
        if (gotInserted) {
            // Means the value is new

            // Save previous
            auxPrevPtr = auxPtr;

            // Move to the next one
            auxPtr = auxPtr->Next;
        } else {
            // Duplicated element, need to delete auxPtr

            auxPrevPtr->Next = auxPtr->Next;

            // Delete node
            delete auxPtr;

            // We move to the next one
            auxPtr = auxPrevPtr->Next;
        }
    }
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

    DeleteDuplicatesFromList(my_list);

    LinkedList::PrintList(my_list);

    LinkedList::DeleteList(my_list);

    return 0;
}
