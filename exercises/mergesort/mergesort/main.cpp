// Copyright (c) 2021 Emmanuel Arias

#include <common_lib/input_casting.h>
#include <spdlog/spdlog.h>
#include <vector>

void merge_sort(std::vector<int>& list, std::vector<int>& helper, int low,
                int high);
void merge(std::vector<int>& list, std::vector<int>& helper, int low,
           int middle, int high);

void merge_sort(std::vector<int>& list) {
    std::vector<int> helper(list.size());
    merge_sort(list, helper, 0, list.size() - 1);
}

void merge_sort(std::vector<int>& list, std::vector<int>& helper, int low,
                int high) {
    if (low < high) {
        int middle = low + (high - low) / 2;
        // Go left
        merge_sort(list, helper, low, middle);

        // Go right
        merge_sort(list, helper, middle + 1, high);

        merge(list, helper, low, middle, high);
    }
}

void merge(std::vector<int>& list, std::vector<int>& helper, int low,
           int middle, int high) {
    for (int i = low; i <= high; ++i) {
        helper[i] = list[i];
    }

    int helperLeft = low;
    int helperRight = middle + 1;
    int current = low;

    while (helperLeft <= middle && helperRight <= high) {
        if (helper[helperLeft] <= helper[helperRight]) {
            list[current] = helper[helperLeft];
            ++helperLeft;
        } else {
            list[current] = helper[helperRight];
            ++helperRight;
        }
        ++current;
    }

    int remaining = middle - helperLeft;
    for (int i = 0; i <= remaining; ++i) {
        list[current + i] = helper[helperLeft + i];
    }
}

int main(int argc, char* argv[]) {
    std::vector<int> my_list = {1, 4, 7, 12, 43, -1};
    merge_sort(my_list);
    return 0;
}
