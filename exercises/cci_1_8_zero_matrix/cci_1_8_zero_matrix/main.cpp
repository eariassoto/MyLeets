// Copyright (c) 2021 Emmanuel Arias
#include <common_lib/printing.h>
#include <spdlog/spdlog.h>

#include <vector>
#include <unordered_set>

/*
 * For this exercise I will use two sets, in order to store the
 * rows and columns that need to be zeroed.
 * Why do we need to do this? Because if we start replacing as we find,
 * we will go over non-zero cells and cause false positives.
 * 
 * First we iterate the whole matrix and find the rows and cols that need
 * to be zeroed, then we walk through the matrix again 
 *
 * Time complexity: O(NxM)
 * Space complexity O(N+M)
 */

void ApplyZeroToMatrix(std::vector<std::vector<int>>& input) {
    std::unordered_set<int> rowsToZero;
    std::unordered_set<int> columnsToZero;

    for (int i = 0; i < (int)input.size(); ++i) {
        std::vector<int>& currentRow = input[i];
        for (int j = 0; j < (int)currentRow.size(); ++j) {
            if (currentRow[j] == 0) {
                rowsToZero.insert(i);
                columnsToZero.insert(j);
            }
        }
    }

    for (int i = 0; i < (int)input.size(); ++i) {
        std::vector<int>& currentRow = input[i];

        // Do not check for columns, this entire row needs to be zeroed
        if (rowsToZero.find(i) != rowsToZero.end()) {
            for (int& element : currentRow) {
                element = 0;
            }
        } else {
            for (int j = 0; j < (int)currentRow.size(); ++j) {
                if (columnsToZero.find(j) != columnsToZero.end()) {
                    currentRow[j] = 0;
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    std::vector<std::vector<int>> input = {
        {1, 2, 0, 4}, {5, 6, 7, 8}, {0, 10, 11, 12}, {13, 14, 15, 16}};
    PrintMatrix(input);

    ApplyZeroToMatrix(input);

    PrintMatrix(input);
    // ----------

    input = {{0, 2}, {3, 0}};
    PrintMatrix(input);

    ApplyZeroToMatrix(input);

    PrintMatrix(input);

    return 0;
}
