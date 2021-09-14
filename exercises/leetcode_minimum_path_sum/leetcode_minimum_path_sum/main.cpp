// Copyright (c) 2021 Emmanuel Arias

#include <spdlog/spdlog.h>

#include <limits>
#include <numeric>
#include <vector>
#include <stack>

int recCall(const std::vector<std::vector<int>>& grid, int row, int column,
            std::vector<int> weights) {
    if (row == 0 && column == 0) {
        weights.push_back(grid[0][0]);
        return std::accumulate(weights.begin(), weights.end(), 0);
    }

    // Add current cell
    weights.push_back(grid[column][row]);

    int weightPathUp = std::numeric_limits<int>::max();
    // try move up
    if (column > 0) {
        weightPathUp = recCall(grid, row, column - 1, weights);
    }

    int weightPathLeft = std::numeric_limits<int>::max();
    // try move left
    if (row > 0) {
        weightPathLeft = recCall(grid, row - 1, column, weights);
    }

    return std::min(weightPathUp, weightPathLeft);
}

int minPathSumRecursive(std::vector<std::vector<int>>& grid) {
    return recCall(grid, grid[0].size() - 1, grid.size() - 1, {});
}

int minPathSum(std::vector<std::vector<int>>& grid) {
    // row column currentWeight
    std::stack<std::tuple<int, int, int>> lookupStack;
    int initialRow = grid[0].size() - 1;
    int initialCol = grid.size() - 1;
    lookupStack.push(
        std::make_tuple(initialRow, initialCol, grid[initialCol][initialRow]));

    int minPath = std::numeric_limits<int>::max();
    while (!lookupStack.empty()) {
        auto [row, col, currPathCost] = lookupStack.top();
        lookupStack.pop();

        if (row == 0 && col == 0) {
            // got to the center, process
            minPath = std::min(minPath, currPathCost);
            continue;
        }

        // try move up
        if (col > 0) {
            lookupStack.push(std::make_tuple(
                row, col - 1, currPathCost + grid[col - 1][row]));
        }

        // try move left
        if (row > 0) {
            lookupStack.push(std::make_tuple(
                row - 1, col, currPathCost + grid[col][row - 1]));
        }
    }

    return minPath;
}

int main(int argc, char* argv[]) {
    std::vector<std::vector<int>> grid = {{1,2}, {1, 1}};

    auto result = minPathSum(grid);
    spdlog::info("{}", result);

    return 0;
}
