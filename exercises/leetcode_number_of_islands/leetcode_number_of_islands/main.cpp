// Copyright (c) 2021 Emmanuel Arias

#include <spdlog/spdlog.h>

#include <set>
#include <stack>
#include <utility>
#include <vector>

std::pair<int, int> getFirstIslandGrid(
    const std::vector<std::vector<char>>& grid) {
    int y = 0;
    int x = 0;
    for (; y < (int)grid.size(); ++y) {
        const std::vector<char>& row = grid[y];
        for (x = 0; x < (int)row.size(); ++x) {
            if (row[x] == '1') {
                return {x, y};
            }
        }
    }
    return {x, y};
}

void addNeighborsToStack(const std::pair<int, int>& cellPos,
                         std::set<std::pair<int, int>>& islandGrids,
                         std::stack<std::pair<int, int>>& lookupStack) {
    const int x = cellPos.first;
    const int y = cellPos.second;

    // top
    auto it = islandGrids.find({x, y - 1});
    if (it != islandGrids.end()) {
        lookupStack.push({x, y - 1});
        islandGrids.erase(it);
    }

    // bottom
    it = islandGrids.find({x, y + 1});
    if (it != islandGrids.end()) {
        lookupStack.push({x, y + 1});
        islandGrids.erase(it);
    }

    // left
    it = islandGrids.find({x - 1, y});
    if (it != islandGrids.end()) {
        lookupStack.push({x - 1, y});
        islandGrids.erase(it);
    }

    // right
    it = islandGrids.find({x + 1, y});
    if (it != islandGrids.end()) {
        lookupStack.push({x + 1, y});
        islandGrids.erase(it);
    }
}

int numIslands(std::vector<std::vector<char>>& grid) {
    // First we add into a lookup set all the possible islands
    std::set<std::pair<int, int>> islandGrids;
    for (int y = 0; y < (int)grid.size(); ++y) {
        const std::vector<char>& row = grid[y];
        for (int x = 0; x < (int)row.size(); ++x) {
            if (row[x] == '1') {
                islandGrids.insert({x, y});
            }
        }
    }

    int numIslands = 0;
    std::stack<std::pair<int, int>> lookupStack;

    while (!islandGrids.empty()) {
        auto nextGrid = *islandGrids.begin();

        lookupStack.push(nextGrid);
        islandGrids.erase(islandGrids.begin());

        // Try to add all of the grid neighbors
        while (!lookupStack.empty()) {
            auto cellPos = lookupStack.top();
            lookupStack.pop();

            // Try to add neighbors
            addNeighborsToStack(cellPos, islandGrids, lookupStack);
        }

        ++numIslands;
    }

    return numIslands;
}

int main(int argc, char* argv[]) {
    std::vector<std::vector<char>> grid{{'1', '1', '1', '1', '0'},
                                        {'1', '1', '0', '1', '0'},
                                        {'1', '1', '0', '0', '1'},
                                        {'0', '0', '1', '0', '1'}};
    int n = numIslands(grid);

    spdlog::info("{}", n);
    return 0;
}
