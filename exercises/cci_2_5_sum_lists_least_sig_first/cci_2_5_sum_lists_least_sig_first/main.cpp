// Copyright (c) 2021 Emmanuel Arias

#include <common_lib/linked_list.hpp>
#include <spdlog/spdlog.h>

/*
 * First case: Least significant digit first
 *
 * Let's go with and example
 *
 * 2 -> 4 -> 5
 * $
 * 9 -> 2 -> 5
 * $
 *
 * Out:
 *
 * We have 542 and 529. Since digits go from least significant to most
 * significant, we can sum node elements, keeping the carry and addint the
 * result to the end of the list.
 *
 * carry = 0
 *
 * First we sum the root nodes
 *
 * sum = (2 + 9 + carry) = (2 + 9 + 0) = 11
 * new value: sum % 10 = 1
 * carry = sum / 10 = 1
 *
 * lets add 1 to our output list and move along
 *
 * carry 1
 * 2 -> 4 -> 5
 *      $
 * 9 -> 2 -> 5
 *      $
 *
 * Out: 1
 *
 * Now we sum:
 *
 * sum = (4 + 2 + carry) = (4 + 2 + 1) = 7
 * new value: sum % 10 = 7
 * carry = sum / 10 = 0
 *
 * We add 7 to the out list and move on
 *
 * * carry 0
 * 2 -> 4 -> 5
 *           $
 * 9 -> 2 -> 5
 *           $
 *
 * Out: 1 -> 7
 *
 * sum = (5 + 5 + carry) = (5 + 5 + 0) = 10
 * new value: sum % 10 = 0
 * carry = sum / 10 = 1
 *
 * We add 0 to the lsit and move om
 *
 * * carry 1
 * 2 -> 4 -> 5
 *             $
 * 9 -> 2 -> 5
 *             $
 *
 * Out: 1 -> 7 -> 0
 *
 * We reached the end, now we check if there is a left over carry,
 * since out carry = 1 we add it to the out list
 *
 * Out: 1 -> 7 -> 0 -> 1
 *
 * lets verify:
 * 542 + 529 = 1071
 *
 * In case that one list is bigger than the other, we need to add this digits,
 * assuming that the other digits are just 0
 *
 * example
 *
 * carry = 0
 * List1: 9
 *        $
 * List2: 4 -> 1 -> 2
 *        $
 *
 * Out:
 *
 * We sum 9 and 4
 *
 * carry = 1
 * List1: 9
 *          $
 * List2: 4 -> 1 -> 2
 *             $
 * Out: 3
 *
 * List1 is over, but List2 has elements, continue
 *
 * carry = 0
 * List1: 9
 *          $
 * List2: 4 -> 1 -> 2
 *             $
 * Out: 3 -> 2
 *
 * carry = 0
 * List1: 9
 *          $
 * List2: 4 -> 1 -> 2
 *                  $
 * Out: 3 -> 2 -> 2
 *
 * carry = 0
 * List1: 9
 *          $
 * List2: 4 -> 1 -> 2
 *                    $
 * Out: 3 -> 2 -> 2
 *
 * Verify: 9 + 214 = 223
 *
 */

LinkedList::Node<int>* SumLists(LinkedList::Node<int>* list1,
                                LinkedList::Node<int>* list2) {
    LinkedList::Node<int>* rootNode = nullptr;
    LinkedList::Node<int>* auxTail = nullptr;

    LinkedList::Node<int>* digit1 = list1;
    LinkedList::Node<int>* digit2 = list2;

    auto AddNewDigit = [&rootNode, &auxTail](int newDigit) {
        auto newNode = new LinkedList::Node<int>(newDigit);
        if (rootNode == nullptr) {
            // first element, save the root node and start building the tail
            rootNode = newNode;
            auxTail = newNode;
        } else {
            auxTail->Next = newNode;
            auxTail = newNode;
        }
    };

    int carry = 0;

    // First we try to sum from both lists
    while (digit1 != nullptr && digit2 != nullptr) {
        int sum = digit1->Data + digit2->Data + carry;
        int newDigit = sum % 10;
        carry = sum / 10;

        AddNewDigit(newDigit);

        digit1 = digit1->Next;
        digit2 = digit2->Next;
    }

    if (digit1 != nullptr && digit2 != nullptr) {
        if (carry == 1) {
            AddNewDigit(carry);
        }
        return rootNode;
    }

    if (digit1 == nullptr) {
        // Means digit2 is the one with digits left, let's use digit1 for the
        // next step
        digit1 = digit2;
    }

    while (digit1 != nullptr) {
        int sum = digit1->Data + carry;
        int newDigit = sum % 10;
        carry = sum / 10;

        AddNewDigit(newDigit);

        digit1 = digit1->Next;
    }

    if (carry == 1) {
        AddNewDigit(carry);
    }

    return rootNode;
}

int main(int argc, char* argv[]) {
    LinkedList::Node<int>* list_1 = nullptr;
    list_1 = LinkedList::InsertEnd(list_1, 5);
    list_1 = LinkedList::InsertEnd(list_1, 2);

    LinkedList::Node<int>* list_2 = nullptr;
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
}
