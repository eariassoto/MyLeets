// Copyright (c) 2021 Emmanuel Arias

#include <common_lib/linked_list.hpp>
#include <spdlog/spdlog.h>

/*
* Because this is a singly linked list, we cannot access
* to the previous node in order to delete in place.
* We also have no access to the head, so as to iterate from the beggining,
* BUT we know where is the tail.
* 
* We need to delete one node, without memory requirements, so we can swap items
* to the right and delete the tail memory.
* 
* Take this list
* 
* 1 -> 2 -> 3 -> 4
* 
* we want to delete 2
* 
* So what we can do is swap 2 and 3
* 
* 1 -> 3 -> 2 -> 4
* 
* the we swap 2 and 4
* 
* 1 -> 3 -> 4 -> 2
* 
* and because the next one is the tail, we delete this node
* 
* 1 -> 3 -> 4
* 
*/
void DeleteMiddleNode(LinkedList::Node<int>* middleNode) { 
    auto currentNode = middleNode;
    
    while (currentNode != nullptr) {
        // This is safe because we are guaranteed to have at least a tail
        currentNode->Data = currentNode->Next->Data;
        if (currentNode->Next->Next == nullptr) {
            // next one is the tail
            delete currentNode->Next;
            currentNode->Next = nullptr;
        }
        currentNode = currentNode->Next;
    }
}

int main(int argc, char* argv[]) {
    LinkedList::Node<int>* my_list = nullptr;

    my_list = LinkedList::InsertFront(my_list, 1);
    my_list = LinkedList::InsertFront(my_list, 2);
    my_list = LinkedList::InsertFront(my_list, 2);
    my_list = LinkedList::InsertFront(my_list, 2);
    my_list = LinkedList::InsertFront(my_list, 3);

    auto middleNode = my_list;

    my_list = LinkedList::InsertFront(my_list, 4);
    my_list = LinkedList::InsertFront(my_list, 5);
    my_list = LinkedList::InsertFront(my_list, 4);

    LinkedList::PrintList(my_list);

    spdlog::info("Deleting middle node: {}", middleNode->Data);

    DeleteMiddleNode(middleNode);

    LinkedList::PrintList(my_list);

    LinkedList::DeleteList(my_list);
}
