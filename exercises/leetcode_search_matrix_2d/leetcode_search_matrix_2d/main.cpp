// Copyright (c) 2021 Emmanuel Arias

#include <spdlog/spdlog.h>

#include <algorithm>
#include <vector>

/*
 * An iterative search is not efficient enough. Given that the rows are
 * guaranteed to go in ascending order (The first integer of each row is greater
 * than the last integer of the previous row.) we can use binary search to find
 * the row where the element to find might be
 *
 * Example:
 *
 *  1, 3, 5, 7
 * 10,11,16,20
 * 23,30,34,60
 *
 * Target 3
 *
 * binary search
 * first index: 0
 * last index: 2
 *
 * We start checking the middle row, (1).
 *
 *  1, 3, 5, 7
 * 10,11,16,20
 * %%       %%
 * 23,30,34,60
 *
 * the target 3 is smaller than 10, so we know we need to look in the lower half
 * If the target were bigger than the last item of the row, we need to look in
 * the higher half
 *
 *
 *  1, 3, 5, 7
 * %%       %%
 * 10,11,16,20
 * 23,30,34,60
 *
 * target 3
 *
 * 3 is higher than 1, but less than 7, this is our row to search
 *
 * the target 3 is in the row 1, 3, 5, 7, so we return true, in all other cases
 * we return false
 *
 * Matrix N Rows and M columns
 * Time complexity O(log(N) + M)
 * Memory complexity O(1)
 */

bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
    int lowIndex = 0;
    int highIndex = matrix.size() - 1;
    int middle = 0;

    if (matrix.size() == 1) {
        return std::find(matrix[0].begin(), matrix[0].end(), target) !=
               matrix[0].end();
    }

    while (lowIndex <= highIndex) {
        middle = lowIndex + (highIndex - lowIndex) / 2;

        const std::vector<int>& rowToFind = matrix[middle];

        if (target == rowToFind[0]) {
            return true;
        } else if (target < rowToFind[0]) {
            highIndex = middle - 1;
            continue;
        } else if (target == rowToFind[rowToFind.size() - 1]) {
            return true;
        } else if (target > rowToFind[rowToFind.size() - 1]) {
            lowIndex = middle + 1;
            continue;
        } else {
            // we found our target row
            return std::find(rowToFind.begin(), rowToFind.end(), target) !=
                   rowToFind.end();
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    std::vector<std::vector<int>> matrix = {
        {1}, {3}};

    auto result = searchMatrix(matrix, 3);
    spdlog::info("{}", result);

    return 0;
}
