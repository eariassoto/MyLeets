// Copyright (c) 2021 Emmanuel Arias

#include <common_lib/linked_list.hpp>
#include <spdlog/spdlog.h>

/*
 *
 * If two linked lists do not intersect, such as:
 *
 * list1: 1 -> 2 -> 3 -> 10 -> 12
 *
 * list2: 20 -> 25 -> 30
 *
 * The tails' memory adress will not match, but if they do intersect, we have
 *
 * list1: 1 -> 2 -> 3 -> -> 5 -> -9 -> 10 -> 12
 *                          ^
 *                         /
 * list2:        20 -> 25 -
 *
 * So if we run pointers to both tails and the memory pointers match, we know
 * they intersect. Because they are singly linked lists, we cannot go back and
 * find the first intersection node, so for this we can play with lengths.
 *
 * If the two lists intersect and have the same size, we start in both head
 * nodes and go until the pointers have the same memory adress. If one list is
 * shorter than the other, we can see as one list having more elements before
 * the intersection. This excess we can ignore. For this we need to keep track
 * of both lengths.
 *
 */

LinkedList::Node<int>* FindIntersectionIfExists(LinkedList::Node<int>* list1,
                                                LinkedList::Node<int>* list2) {
    if (list1 == nullptr || list2 == nullptr) {
        return nullptr;
    }

    // First check whether they intersect or not
    auto FindTailForList = [](LinkedList::Node<int>* root)
        -> std::pair<LinkedList::Node<int>*, int> {
        if (root == nullptr) {
            return std::make_pair(nullptr, 0);
        }

        // Count 1 plus because we move until the tail
        int length = 1;
        LinkedList::Node<int>* auxPtr = root;
        while (auxPtr->Next != nullptr) {
            auxPtr = auxPtr->Next;
            ++length;
        }

        return std::make_pair(auxPtr, length);
    };

    auto AdvanceListNSpaces = [](LinkedList::Node<int>* node,
                                 int n) -> LinkedList::Node<int>* {
        for (int i = 0; i < n && node != nullptr; ++i) {
            node = node->Next;
        }
        return node;
    };

    auto [tail1, length1] = FindTailForList(list1);
    auto [tail2, length2] = FindTailForList(list2);

    // Comparing pointers here
    if (tail1 != tail2) {
        return nullptr;
    }

    LinkedList::Node<int>* aux1 = list1;
    LinkedList::Node<int>* aux2 = list2;

    if (length1 > length2) {
        // Need to move tail1
        aux1 = AdvanceListNSpaces(aux1, length1 - length2);
    } else if (length2 > length1) {
        aux2 = AdvanceListNSpaces(aux2, length2 - length1);
    }

    while (aux1 != aux2) {
        aux1 = aux1->Next;
        aux2 = aux2->Next;
    }

    return aux1;
}

int EvaluateExercise(int input) { return 0; }

int main(int argc, char* argv[]) {
    LinkedList::Node<int>* list_1 = nullptr;
    list_1 = LinkedList::InsertFront(list_1, 1);
    list_1 = LinkedList::InsertFront(list_1, 2);
    list_1 = LinkedList::InsertFront(list_1, 3);
    list_1 = LinkedList::InsertFront(list_1, 5);
    list_1 = LinkedList::InsertFront(list_1, 6);
    LinkedList::Node<int>* middleNode = list_1;
    list_1 = LinkedList::InsertFront(list_1, 7);
    list_1 = LinkedList::InsertFront(list_1, 8);
    list_1 = LinkedList::InsertFront(list_1, 9);
    list_1 = LinkedList::InsertFront(list_1, 10);

    LinkedList::Node<int>* a = LinkedList::InsertFront(middleNode, 10);
    LinkedList::Node<int>* list_2 = LinkedList::InsertFront(a, 20);

    LinkedList::PrintList(list_1);
    LinkedList::PrintList(list_2);

    auto intersection = FindIntersectionIfExists(list_1, list_2);
    if (intersection == nullptr) {
        spdlog::info("Could not find intersection");
    } else {
        spdlog::info("Intersection for lists is: {}", intersection->Data);
    }

    delete a;
    delete list_2;
    LinkedList::DeleteList(list_1);

    return 0;
}
