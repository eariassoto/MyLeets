// Copyright (c) 2021 Emmanuel Arias

#include <common_lib/input_casting.h>
#include <spdlog/spdlog.h>

#include <sstream>
#include <vector>

/*
 * For this exercise, we can think of the square matrix as
 * circle layers
 *
 * For example
 *
 *  a b c d
 *  e f g h
 *  i j k l
 *
 * can be seen as two circular layers
 *
 * & & & &
 * & $ $ &
 * & $ $ &
 * & & & &
 *
 * To make a rotation in place, we can, for each layer swap the corner
 * items to the left. For example, to rotate the outper layer we do first:
 *
 * @ & & @
 * & $ $ &
 * & $ $ &
 * @ & & @
 *
 * Then we do
 *
 *  & @ & &
 * & $ $ @
 * @ $ $ &
 * & & @ &
 *
 * and so on until we complete the circle.
 *
 */

void RotateMatrix(std::vector<std::vector<int>>& input) {
    if (input.empty()) return;
    // assert to check the matrix is nxn
    const int layers = input.size() / 2;
    for (int layer = 0; layer < layers; ++layer) {
        // Every layer gets smaller by one place, move indexes accordingly
        int first = layer;
        int last = input.size() - 1 - layer;

        /*
         * 1 & & 2
         * & $ $ &
         * & $ $ &
         * 4 & & 3
         *
         * 4 & & 1
         * & $ $ &
         * & $ $ &
         * 3 & & 2
         */
        for (int i = first; i < last; ++i) {
            int offset = i - first;
            // temp for corner 1
            int auxTop = input[first][i];

            // move corner 4 to corner 1
            input[first][i] = input[last - offset][first];

            // move corner 3 to corner 4
            input[last - offset][first] = input[last][last - offset];

            // move corner 2 to corner 3
            input[last][last - offset] = input[i][last];

            // copy corner 1 to corner 2
            input[i][last] = auxTop;
        }
    }
}

void PrintMatrix(const std::vector<std::vector<int>>& matrix) {
    std::stringstream aux;
    aux << '\n';
    for (const auto& row : matrix) {
        for (const int col : row) {
            aux << col << " ";
        }
        aux << '\n';
    }
    spdlog::info("{}", aux.str());
}

int main(int argc, char* argv[]) {
    std::vector<std::vector<int>> input = {
        {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    PrintMatrix(input);

    RotateMatrix(input);

    PrintMatrix(input);
    // ----------

    input = {{1, 2}, {3, 4}};
    PrintMatrix(input);

    RotateMatrix(input);

    PrintMatrix(input);

    return 0;
}
