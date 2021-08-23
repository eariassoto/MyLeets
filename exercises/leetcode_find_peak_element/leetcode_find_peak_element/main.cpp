// Copyright (c) 2021 Emmanuel Arias

#include <spdlog/spdlog.h>

#include <vector>

/*
 * For this exercise we will do a local binary search. This vector is not
 * sorted, and we do not need it to be because we need to find any peak.
 *
 * A peak is an number that is strictly greater than its left and left and right
 * neighbors. Because of the problem's descriptions, we are ensured to have an
 * answer.
 *
 * We will put an index pointer to the center of the array. If the left neighbor
 * is greater than the current index, we continue iterating and set the new
 * pointer to
 *
 */

int findPeakElement(std::vector<int>& nums) {
    if (nums.size() == 1) {
        return 0;
    }
    if (nums.size() == 2) {
        if (nums[0] > nums[1]) {
            return 0;
        } else {
            return 1;
        }
    }
    if (nums.size() == 3) {
        if (nums[1] > nums[0]) {
            if (nums[1] > nums[2]) {
                return 1;
            } else {
                return 2;
            }
        } else {
            return 0;
        }
    }
    // do binary search
    int lowIndex = 0;
    int endIndex = nums.size();
    int middleIndex = (lowIndex + endIndex) / 2;

    while (true) {
        if (middleIndex == 0 || middleIndex == nums.size() - 1) {
            return middleIndex;
        }
        if (nums[middleIndex - 1] > nums[middleIndex]) {
            endIndex = middleIndex;
            middleIndex = (lowIndex + endIndex) / 2;
            continue;
        }
        if (nums[middleIndex + 1] > nums[middleIndex]) {
            lowIndex = middleIndex;
            middleIndex = (lowIndex + endIndex) / 2;
            continue;
        }
        return middleIndex;
    }
}

int main(int argc, char* argv[]) {
    std::vector<int> input{1, 2, 3, 4};
    auto result = findPeakElement(input);
    spdlog::info("findPeakElement: {}", result);

    return 0;
}
