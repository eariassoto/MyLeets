// Copyright (c) 2021 Emmanuel Arias

#include <common_lib/linked_list.hpp>
#include <spdlog/spdlog.h>

/*
 * This exercise feels a lot like the quicksort partitioning algorithm
 *
 * What we want to do is to put all nodes less than the partition at the
 * beginning of the linked list. The rest will be properly swapped at the end.
 *
 * Suppose we have
 *
 * 1 -> 19 -> 3 -> 14 -> 5 -> 2    [partition 5]
 *
 * Let's put two pointers, one at the root, and one at the second item
 *
 * 1 -> 19 -> 3 -> 14 -> 5 -> 2
 * $    #
 *
 * is the value at $ less than the partition? yes, move both pointers
 *
 * 1 -> 19 -> 3 -> 14 -> 5 -> 2
 *      $     #
 *
 * is the value at $ less than the partition? no. For this case, we need to move
 * # until we find the next value that is less than the partition.
 *
 * In this case we do not move. After we find the next value to swap, do the
 * swap
 *
 * 1 -> 19 -> 3 -> 14 -> 5 -> 2
 *      $     #
 *
 * 1 -> 3 -> 19 -> 14 -> 5 -> 2
 *      $     #
 *
 * And move the pointers
 *
 * 1 -> 3 -> 19 -> 14 -> 5 -> 2
 *           $     #
 *
 * Again, $ needs to be swapped, this time we go all the way to the end
 *
 * 1 -> 3 -> 19 -> 14 -> 5 -> 2
 *           $                #
 *
 * and swap
 *
 * 1 -> 3 -> 2 -> 14 -> 5 -> 19
 *           $               #
 *
 * the next move
 *
 * 1 -> 3 -> 2 -> 14 -> 5 -> 19
 *                $             #
 *
 * here we can see that $ needs to be swapped but the # pointer already
 * overflow, this means the list is partitioned
 *
 */

LinkedList::Node<int>* FindNextValueLessThan(LinkedList::Node<int>* inputList,
                                             int partition) {
    auto auxPtr = inputList;
    while (auxPtr != nullptr && auxPtr->Data >= partition) {
        auxPtr = auxPtr->Next;
    }
    return auxPtr;
}

void PartitionList(LinkedList::Node<int>* inputList, int partition) {
    LinkedList::Node<int>* swapPointer = inputList;
    LinkedList::Node<int>* lookupPointer = inputList->Next;

    while (swapPointer != nullptr && lookupPointer != nullptr) {
        // check if current value is less than the partition
        if (swapPointer->Data >= partition) {
            // the current node needs to be swapped for the next value that is
            // less than the partition, if exists
            lookupPointer = FindNextValueLessThan(lookupPointer, partition);
            if (lookupPointer == nullptr) {
                // a value less than the partition does not exists, we have completed
                // the partitioning
                return;
            } else {
                // we need to swap values and move pointers
                int tmp = swapPointer->Data;
                swapPointer->Data = lookupPointer->Data;
                lookupPointer->Data = tmp;
            }
        }
        swapPointer = swapPointer->Next;
        lookupPointer = lookupPointer->Next;
    }
}

int main(int argc, char* argv[]) {
    LinkedList::Node<int>* my_list = nullptr;

    my_list = LinkedList::InsertEnd(my_list, 5);
    my_list = LinkedList::InsertEnd(my_list, 12);
    my_list = LinkedList::InsertEnd(my_list, 6);
    my_list = LinkedList::InsertEnd(my_list, 8);
    my_list = LinkedList::InsertEnd(my_list, 14);
    my_list = LinkedList::InsertEnd(my_list, -9);
    my_list = LinkedList::InsertEnd(my_list, 2235);
    my_list = LinkedList::InsertEnd(my_list, 24);

    LinkedList::PrintList(my_list);

    int partition = 14;
    spdlog::info("Partitioning list around {}", partition);

    PartitionList(my_list, partition);

    LinkedList::PrintList(my_list);

    partition = 6;
    spdlog::info("Partitioning list around {}", partition);

    PartitionList(my_list, partition);

    LinkedList::PrintList(my_list);

    partition = 2235;
    spdlog::info("Partitioning list around {}", partition);

    PartitionList(my_list, partition);

    LinkedList::PrintList(my_list);

    LinkedList::DeleteList(my_list);

    return 0;
}
