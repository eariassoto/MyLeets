// Copyright (c) 2021 Emmanuel Arias

#include <spdlog/spdlog.h>

#include <vector>

/*
 * Given n non-negative integers a1, a2, ..., an , where each represents a point
 * at coordinate (i, ai). n vertical lines are drawn such that the two endpoints
 * of the line i is at (i, ai) and (i, 0). Find two lines, which, together with
 * the x-axis forms a container, such that the container contains the most
 * water. Notice that you may not slant the container.
 * 
 * We want to optimize the base first, this means, we set two pointers, one at the beginning and
 * one at the end of heights. Our base will be defined as j - i, where j is the index of the leftmost
 * point.
 * 
 * Then we want to optimize the walls, we will calculate the area, and discard the wall with the leash height.
 * 
 * We will do this until both pointers meet.
 * 
 * Then we will have the max area possible.
 * 
 */

int calculateArea(int ai, int aj, int i, int j) {
    return (j - i) * std::min<int>(ai, aj);
}

int maxArea(std::vector<int>& height) {
    int maxArea = 0;

    int i = 0;
    int j = height.size() - 1;
    while (i < j) {
        int newArea = calculateArea(height[i], height[j], i , j);
        if (newArea > maxArea) {
            maxArea = newArea;
        }

        if (height[i] > height[j]) {
            --j;
        } else {
            ++i;
        }
    }

    return maxArea;
}

int main(int argc, char* argv[]) {
    std::vector heights{1, 8, 6, 2, 5, 4, 8, 3, 7};

    auto result = maxArea(heights);
    spdlog::info("Max area is: {}", result);

    return 0;
}
