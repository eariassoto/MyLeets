// Copyright (c) 2021 Emmanuel Arias

#include "common_lib/linked_list.hpp"
#include <spdlog/spdlog.h>

#include <stack>

/*
 * What we can do here is to iterate the list, fill a stack with the first half
 * of the list, and then compare the rest of the list against the stack.
 *
 * Without knowing the length of the list, we need a strategy to avoid iterating
 * twice. For this we can use a secondary pointer that advances twice as fast
 *
 * For example, lets start with our two pointers
 *
 * a -> b -> b -> a
 * $
 * &
 * Stack: a
 *
 * we add 'a' and move pointers
 *
 * a -> b -> b -> a
 *      $
 *           &
 * Stack: a -> b
 *
 * We move the pointers again and add b
 *
 * a -> b -> b -> a
 *           $
 *                   &
 * Stack: a -> b
 *
 * The second pointer is out of the list so we now try to pop the queue and
 * check that each item is equals
 *
 * a -> b -> b -> a
 *           $
 *                   &
 * Stack: a
 *
 * b canceled b
 *
 * a -> b -> b -> a
 *                $
 *                   &
 * Stack:
 *
 * And then a canceled a
 *
 * If the list length is odd:
 *
 * q w e r t
 * $
 * &
 * Queue: q
 *
 * q w e r t
 *   $
 *     &
 * Queue: q -> w
 *
 * q w e r t
 *     $
 *         &
 * Queue: q -> w
 *
 * We reach the end but did not go out of the list, this means we skip
 * the middle item and do not put it in the queue
 *
 */

bool IsPalindrome(LinkedList::Node<char>* list) {
    std::stack<char> lookUpQueue;

    LinkedList::Node<char>* slowPtr = list;
    LinkedList::Node<char>* runnerPtr = list;

    // runnerPtr == nullptr will happen if the list length is even
    // if odd, then we will have runnerPtr->Next == nullptr
    while (runnerPtr != nullptr && runnerPtr->Next != nullptr) {
        lookUpQueue.push(slowPtr->Data);

        slowPtr = slowPtr->Next;
        runnerPtr = runnerPtr->Next->Next;
    }

    // We reached the end, for odd lists, the middle will not be in the queue
    // so we need to skip it
    if (runnerPtr != nullptr) {
        slowPtr = slowPtr->Next;
    }

    while (slowPtr != nullptr) {
        char top = lookUpQueue.top();
        if (top != slowPtr->Data) {
            return false;
        }
        lookUpQueue.pop();
        slowPtr = slowPtr->Next;
    }
    return true;
}

int main(int argc, char* argv[]) {
    LinkedList::Node<char>* my_list = nullptr;

    my_list = LinkedList::InsertEnd(my_list, 'a');
    my_list = LinkedList::InsertEnd(my_list, 'b');
    my_list = LinkedList::InsertEnd(my_list, 'l');
    my_list = LinkedList::InsertEnd(my_list, 'b');
    my_list = LinkedList::InsertEnd(my_list, 'a');

    LinkedList::PrintList(my_list);

    spdlog::info("Is the list a palindrom: {}", IsPalindrome(my_list));

    return 0;
}
