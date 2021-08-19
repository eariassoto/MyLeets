// Copyright (c) 2021 Emmanuel Arias

#include <common_lib/linked_list.hpp>
#include <spdlog/spdlog.h>

#include <utility>
/*
 * Case: Most significant digits first
 *
 * For this exercise, we can think about going backwards. We can have a
 * recursion function that goes all the way to the least significant
 * digit in both lists. From there on we can do the sums.
 *
 * There is one catch, one list may be shorter than the other. To resolve this
 * we can pad the shorter list with zeroes
 *
 * Let's take:
 *
 * 0 -> 2 -> 1 -> 7
 * 4 -> 0 -> 9 -> 3
 *
 * We adjust the list1 to be
 *
 * 0 -> 2 -> 1 -> 7
 * 4 -> 0 -> 9 -> 3
 *
 * First recursive call:
 *
 * 0 -> 2 -> 1 -> 7
 * 4 -> 0 -> 9 -> 3
 * $
 *
 * Next we go to
 *
 * 0 -> 2 -> 1 -> 7
 * 4 -> 0 -> 9 -> 3
 *      $
 *
 * then
 *
 * 0 -> 2 -> 1 -> 7
 * 4 -> 0 -> 9 -> 3
 *           $
 *
 * Finally we get to
 *
 * 0 -> 2 -> 1 -> 7
 * 4 -> 0 -> 9 -> 3
 *                $
 *
 * Then we call the function with 2 nullptr
 *
 * * * recursiveFun(nullptr, nullptr)
 * 0 -> 2 -> 1 -> 7
 * 4 -> 0 -> 9 -> 3
 *                  $
 *
 * This means we are in the last step. we can return 0 for the first carry
 *
 * In each step we will sum, add to the list, then return the carry
 *
 * 0 -> 2 -> 1 -> 7
 * 4 -> 0 -> 9 -> 3
 *                $
 * carry: 1
 * Out: 0
 *
 * 0 -> 2 -> 1 -> 7
 * 4 -> 0 -> 9 -> 3
 *           $
 * carry: 1
 * Out: 1 -> 0
 *
 * notice that we are adding to the front
 *
 * 0 -> 2 -> 1 -> 7
 * 4 -> 0 -> 9 -> 3
 *      $
 * carry: 0
 * Out: 3 -> 1 -> 0
 *
 * 0 -> 2 -> 1 -> 7
 * 4 -> 0 -> 9 -> 3
 * $
 * carry: 0
 * Out: 4 -> 3 -> 1 -> 0
 *
 * Finally, we check if the carry is 1, if so we add a final 1
 *
 * Verify the example:
 * 217 + 4093 = 4310
 *
 */

LinkedList::Node<int>* PadListWithZeroes(LinkedList::Node<int>* root, int n) {
    LinkedList::Node<int>* auxPtr = root;
    for (int i = 0; i < n; ++i) {
        auxPtr = LinkedList::InsertFront(auxPtr, 0);
    }
    return auxPtr;
}

std::pair<LinkedList::Node<int>*, int> SumListsHelper(
    LinkedList::Node<int>* list1, LinkedList::Node<int>* list2) {
    if (list1 == nullptr) {
        // assert list2 == nullptr
        return {nullptr, 0};
    }
    auto [outRootNode, carry] = SumListsHelper(list1->Next, list2->Next);

    int sum = list1->Data + list2->Data + carry;
    outRootNode = LinkedList::InsertFront(outRootNode, sum % 10);

    return {outRootNode, sum / 10};
}

LinkedList::Node<int>* SumLists(LinkedList::Node<int>* list1,
                                LinkedList::Node<int>* list2) {
    int len1 = LinkedList::Length(list1);
    int len2 = LinkedList::Length(list2);
    if (len1 < len2) {
        list1 = PadListWithZeroes(list1, len2 - len1);
    } else if (len2 < len1) {
        PadListWithZeroes(list2, len1 - len2);
    }

    auto [outRootNode, carry] = SumListsHelper(list1, list2);

    if(carry == 1) {
        outRootNode = LinkedList::InsertFront(outRootNode, 1);
    }

    return outRootNode;
}

int main(int argc, char* argv[]) {
    LinkedList::Node<int>* list_1 = nullptr;
    list_1 = LinkedList::InsertEnd(list_1, 2);
    list_1 = LinkedList::InsertEnd(list_1, 5);

    LinkedList::Node<int>* list_2 = nullptr;
    list_2 = LinkedList::InsertEnd(list_2, 9);
    list_2 = LinkedList::InsertEnd(list_2, 9);
    list_2 = LinkedList::InsertEnd(list_2, 9);
    list_2 = LinkedList::InsertEnd(list_2, 9);

    LinkedList::PrintList(list_1);
    LinkedList::PrintList(list_2);

    spdlog::info("Adding lists");

    auto sumList = SumLists(list_1, list_2);

    LinkedList::PrintList(sumList);

    LinkedList::DeleteList(list_1);
    LinkedList::DeleteList(list_2);
    LinkedList::DeleteList(sumList);

    return 0;
}
